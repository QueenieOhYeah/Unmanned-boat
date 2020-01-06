#include "VisionServoThread.h"
#include "define.h"


//for time
#include <stdlib.h>
#include <stdio.h>
//#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include "RGBDCamera.h"


//#define PREDICTION
#define MARKER_DBG
//#define ITERATE

double lasttime = 0;
//**********image processing
Rect selection; //object rectangle
Rect greenSelection; //marker rectangle
Rect trackWindow;
RotatedRect trackBox;
int hsize = 16;
int a=0;
float hranges[] = {0,180};
const float* phranges = hranges;
Mat  hsv, hue, mask, hist, histimg = Mat::zeros(200, 320, CV_8UC3), backproj;
int vmin = 10, vmax = 256, smin = 30;
Mat image;

//**********image output
Mat MyCaliDepth;
Mat MycvDepthImg;

//***********detect flag
int iscaptureObject = -1;
int iscaptureMarker = -1;
int isGreendetectObject=-1;

Point GreenroughCenter;

VisionServoThread::VisionServoThread()
{
     computedGreenX =0;//theoretical marker position
     computedGreenY =0;
     computedGreenZ =0;
     GlobalPX=0;//end point of arm we controlled
     GlobalPY=0;
     GlobalPZ=0;

    iternum =0;
    movePflag=false;
    feedbackflag =false;
    stop = false;
    tissuebagDetectflag = true;
    myCam = new MyStereoCam();

}
//void VisionServoThread::initial()
//{
//   isInitialized = GreencolorDetection(Greenimgin,Greenimgout,GreenroughCenter,greenSelection);
//   Point2i dst;
//   Point2i mysrc = Point2i(GreenroughCenter.x, GreenroughCenter.y);
//   softwareRegistrator.convertColor2Depth_Point(CaliDepth,mysrc , dst);

//}

void VisionServoThread::run()
{

    int delayTime = 100;
    cout<<"hello"<<endl;
    //************************************core algorithm
    SoftwareRegistrator softwareRegistrator;
    MyTinyAlgorithm myAlgorithm;
    Draw mDraw;

    // -----------------------------------initialization
    CRGBDCamera camera(REC_WIDTH, REC_HEIGHT);
     cout<<"hello2"<<endl;

    //--------------------------------open the device
    camera.InitializeDevice();
    int res = camera.OpenDevice(NULL);

    if (res != 0)
    {
        printf("Press any key to continue . . .\n");
        getchar();
//        return ;
    }

    camera.InitializeRGBorIRStream(true, REC_HEIGHT, REC_WIDTH);
    camera.StartRGBorIRStream();
    camera.StartDepthStream();
    camera.toggleRegister(false);

    //-------------
//    VideoCapture cap(0);
//    cap.open(0);
//    if(!cap.isOpened())
//    {
//       cout<<"fail to open cam2"<<endl;
//    }

    //----------------------------------------read the parameters
    OBCameraParams params;
    loadParams(params); //load params mannually
    softwareRegistrator.SetParams(params);
    softwareRegistrator.CalcConversionMatrix();

    emit  gripControl(0);
    QThread::msleep(200);

   emit moveToP(14,205,-10);
    QThread::msleep(1000);

    //******************************************main loop
   iscaptureMarker=-1;
   feedbackflag=false;
    while (!stop)
    {
        cout<<"collect"<<endl;
//        Mat frame2;
//        cap>>frame2;
//        if(frame2.empty())
//            break;
//       // imshow("cam2",frame);
//         emit updateCam2Frame(frame2);


        //**********collect images
        Mat     cvRGBImg(REC_HEIGHT, REC_WIDTH, CV_8UC3);
        Mat     cvBGRImg(REC_HEIGHT, REC_WIDTH, CV_8UC3);
        Mat     cvIRImg(REC_HEIGHT, REC_WIDTH, CV_16UC1);
        Mat     cvDepthImg(REC_HEIGHT, REC_WIDTH, CV_16UC1);
        Mat     CaliDepth(REC_HEIGHT, REC_WIDTH, CV_16UC1);
        Mat     CaliDepthHistogram(REC_HEIGHT, REC_WIDTH, CV_8UC3);

        camera.getNextFrame(cvRGBImg, cvIRImg, cvDepthImg);

        flip(cvRGBImg,cvRGBImg,1);
        flip(cvDepthImg,cvDepthImg,1);
        cvtColor(cvRGBImg, cvBGRImg, CV_RGB2BGR);


        //**************obtain 3D coordinates
        softwareRegistrator.MappingDepth2Color(cvDepthImg, CaliDepth, true);
        mDraw.GetDepthHistogram(CaliDepth, CaliDepthHistogram);

        //***************depth image
        int alphaColor = 100;
        double colorRatio = alphaColor / 100.0;
        Mat     registerMat = cvBGRImg.clone();

        cv::addWeighted(CaliDepthHistogram, 1 - colorRatio, cvBGRImg, colorRatio, 0.5, registerMat);

        //*************draw coordinates
        myAlgorithm.drawCoordinateSystem(registerMat,softwareRegistrator);

        //***************image proccessing
         Mat Greenimgout;
         Mat Greenimgin = cvBGRImg.clone();

       //---------feedback phase
    if(feedbackflag ==true){
        cout<<"start feedback..."<<endl;

//#ifndef MARKER_DBG
         if (iscaptureMarker == -1){
             iscaptureMarker = GreencolorDetection(Greenimgin,Greenimgout,GreenroughCenter,greenSelection);
         }
         if (iscaptureMarker == 0){
          isGreendetectObject =yellowCamshift(Greenimgin,Greenimgout,greenSelection,GreenroughCenter);
         }
//#else
//         isGreendetectObject =GreencolorDetection(Greenimgin,Greenimgout,GreenroughCenter,greenSelection);
//#endif

         cvtColor(Greenimgout,Greenimgout,CV_GRAY2BGR);
         myAlgorithm.drawCross(Greenimgout,GreenroughCenter,Scalar(0,255,0),10,2);

        //----------------draw data
#ifndef PREDICT
         for(int i=0;i<pointSet.size();i++){
            myAlgorithm.drawCross(Greenimgout,pointSet[i],Scalar(0,0,255),10,2);
            myAlgorithm.drawCross(registerMat,pointSet[i],Scalar(0,0,255),10,2);
        }
#else
         for(int i=0;i<pointSetPredict.size();i++){
            myAlgorithm.drawCross(Greenimgout,pointSetPredict[i],Scalar(0,255,0),10,2);
            myAlgorithm.drawCross(registerMat,pointSetPredict[i],Scalar(0,255,0),10,2);
        }
#endif

         if (isGreendetectObject == -1){ //fail to detect marker
             emit updateFrame(Greenimgout);//display image
             QThread::msleep(delayTime);
             continue;
         }

         int upLimit = 181;
         int downLimit = 300;//220//257;
         line(Greenimgout,Point(0,upLimit),Point(639,upLimit),Scalar(0,0,225),1);
         line(Greenimgout,Point(0,downLimit),Point(639,downLimit),Scalar(0,0,225),1);

         line(registerMat,Point(0,upLimit),Point(639,upLimit),Scalar(0,0,225),1);
         line(registerMat,Point(0,downLimit),Point(639,downLimit),Scalar(0,0,225),1);

        //---------------------project to 3D coordinate
         Point2i dst;
         Point2i mysrc = Point2i(GreenroughCenter.x, GreenroughCenter.y);
         softwareRegistrator.convertColor2Depth_Point(CaliDepth,mysrc , dst);
         //cout<<"depth_pnt: "<<dst.x<<","<<dst.y<<endl;

         float px, py, pz;
         softwareRegistrator.ConvertProjectiveToWorld(dst.x, dst.y, (int)cvDepthImg.at<unsigned short>(dst.y, dst.x), px, py, pz, true);
         // cout << "target at: " << roughCenter.x << "," << roughCenter.y <<"; px,py,pz: " << -1*(px+15) << "," << py+130+95 << "," << 615-pz << endl;

         float Px = (px+18);//15,*-1
         float Py = py+210;//+130+95
         float Pz = 615-pz-8 ;
         if(pz ==0){continue; }
        // cout<<"GreenPx,GreenPy,GreenPz: "<<Px<<","<<Py<<","<<Pz<<endl;

         float errorx = Px - computedGreenX;
         float errory = Py - computedGreenY;
         float errorz = Pz - computedGreenZ;



        //------------------iterate control
        if (Px>0) { //left side
            if(iternum<=0){ //former value is 4
                if(errorx>=10 || errorx<=-10)  GlobalPX -= 0.7*errorx;
                else  GlobalPX -= 0.1*errorx;
                GlobalPY -= 1.1*errory;
            }
            if(iternum>0){
                GlobalPZ -= 1.3*errorz;
                GlobalPY -= 0.6*errory; //0.8
            }
       }
        else{
           if(iternum<=0){ //former value is 4
               if(errorx>=10 || errorx<=-10)  GlobalPX -= 0.5*errorx;
               else  GlobalPX -= 0.1*errorx;
               GlobalPY -= 1.1*errory;
           }
           if(iternum>0){
               GlobalPZ -= 1.1*errorz;
               GlobalPY -= 0.4*errory;
           }
       }
        cout<<"iter"<<iternum<<",error: "<<(int)errorx<<","<<(int)errory<<","<<(int)errorz<<" control value: "<<(int)GlobalPX<<","<<(int)GlobalPY<<","<<(int)GlobalPZ<<endl;

        emit moveToP((int)GlobalPX,(int)GlobalPY,(int)GlobalPZ);
        QThread::msleep(150);

        emit updateFrame(Greenimgout);//display image

        iternum ++;
        if(iternum ==2){ //finish iterating
            emit  gripControl(1);
            QThread::msleep(1000);

            emit moveToP((int)GlobalPX,(int)GlobalPY,0);
            QThread::msleep(2000);

            feedbackflag =false;
            iternum =0;
            pointSet.clear();
            pointSetPredict.clear();
            pointSetDetect.clear();
            iscaptureMarker=-1;
            break;
           }

          continue;
      }//finish feedback


    //***********************tissue bag detection
    if(tissuebagDetectflag ==true){
    Mat imgout;
    Mat imgin = cvBGRImg.clone();
    Point roughCenter;

    int isdetectObject = colorDetection(imgin,imgout,roughCenter,selection);
    //int isdetectObject = detectMesh(imgin,registerMat,roughCenter);
    if (isdetectObject == -1){ //fail to detect object
        cout<<"not detect tissue"<<endl;
        cvtColor(imgout,imgout,CV_GRAY2BGR);
        emit updateFrame(imgout);//display image
        QThread::msleep(delayTime);
        continue;
    }

#ifdef MARKER_DBG
     if (iscaptureMarker == -1){
         iscaptureMarker = GreencolorDetection(Greenimgin,Greenimgout,GreenroughCenter,greenSelection);
         cout<<"still detecting..."<<endl;
         cvtColor(Greenimgout,Greenimgout,CV_GRAY2BGR);
         emit updateFrame(Greenimgout);//display image
         QThread::msleep(delayTime);
         continue;
     }
     if (iscaptureMarker == 0){
   //      cout<<"start camshift..."<<endl;
      isGreendetectObject =yellowCamshift(Greenimgin,Greenimgout,greenSelection,GreenroughCenter);
      rectangle(registerMat, greenSelection, Scalar(100, 100, 0), 2, 8);
     }
#endif

     cvtColor(Greenimgout,Greenimgout,CV_GRAY2BGR);
 //    myAlgorithm.drawCross(registerMat,GreenroughCenter,Scalar(0,255,0),2,CV_AA);

    //----------------------------draw object center
    pointSet.push_back(roughCenter);
    for(int i=0;i<pointSet.size();i++){
        myAlgorithm.drawCross(registerMat,pointSet[i],Scalar(0,0,255),10,2);

    }

    int upLimit = 181;
//    int downLimit = 240;//220;//257;
    int downLimit=300;
    line(registerMat,Point(0,upLimit),Point(639,upLimit),Scalar(0,0,225),1);
    line(registerMat,Point(0,downLimit),Point(639,downLimit),Scalar(0,0,225),1);
    //imwrite("~/a.jpg",registerMat);
    //Mat img=imread("~/8.jpg");

    //isdetectObject = detectMesh(img,registerMat,roughCenter);
    //emit updateFrame(registerMat);
    //break;

    //---------------------------outside workspace
#ifdef PREDICTION
    //with prediction
    float mx0 = pointSet[pointSet.size()-1].x;
    float my0 = pointSet[pointSet.size()-1].y;
    float mdeltax = pointSet[pointSet.size()-1].x - pointSet[pointSet.size()-2].x;
    float mdeltay = pointSet[pointSet.size()-1].y - pointSet[pointSet.size()-2].y;

    for(int n=1;n<=2;n++){
    float futureX = mx0+n*mdeltax;
    float futureY = my0+n*mdeltay;
    myAlgorithm.drawCross(registerMat,Point(futureX,futureY),Scalar(0,255,0),10,2);
    pointSetPredict.push_back(Point(futureX,futureY));
    }
    if((int)futureY>downLimit || (int)futureY<upLimit)
#else
     //without prediction
    if(roughCenter.y>downLimit || roughCenter.y<upLimit)
#endif
    {
         movePflag = false;

         //------------------------------------get the pnt3(px,py,pz), trace by bottom servo
         Point2i dst;
         Point2i mysrc = Point2i(roughCenter.x, roughCenter.y);
         softwareRegistrator.convertColor2Depth_Point(CaliDepth,mysrc , dst);
         float px, py, pz;
         softwareRegistrator.ConvertProjectiveToWorld(dst.x, dst.y, (int)cvDepthImg.at<unsigned short>(dst.y, dst.x), px, py, pz, true);

         float Px = (px+18);//15,*-1
         float Py = py+210;//+130+95
         float Pz = 615-pz-8 ;
          if(pz !=0){
                emit moveMotor1((int)Px,(int)Py,(int)Pz);
          }

        cout<<"Px,Py,Pz: "<<Px<<","<<Py<<","<<Pz<<endl;

       // cvtColor(imgout,imgout,CV_GRAY2BGR);
        emit updateFrame(registerMat);//display normal BGR image
        QThread::msleep(150);
        continue;
    }

    //---------------------------once in the workspce,get the pnt3(px,py,pz) of future pnt
    Point2i dst;
    Point2i mysrc = Point2i(roughCenter.x, roughCenter.y);
    softwareRegistrator.convertColor2Depth_Point(CaliDepth,mysrc , dst);
    float mpx, mpy, mpz;
    softwareRegistrator.ConvertProjectiveToWorld(dst.x, dst.y, (int)cvDepthImg.at<unsigned short>(dst.y, dst.x), mpx, mpy, mpz, true);
    float mPx = -1*(mpx+15);
    float mPy = mpy+130+95;
    float mPz = 615-mpz ;
    cout<<"original pnt3:"<<(int)mPx<<","<<(int)mPy<<","<<(int)mPz<<endl;

#ifndef PREDICTION
    //without prediction
    float px,py,pz;
    px = mpx;
    py=mpy;
    pz = mpz;
#else

   // with prediction
    Point2i Nextmysrc =  pointSetPredict[pointSetPredict.size()-1];
    CaliDepth.at<uint16_t>(Nextmysrc.y,Nextmysrc.x) = CaliDepth.at<uint16_t>(mysrc.y,mysrc.x);// suppose depth is fixed
    softwareRegistrator.convertColor2Depth_Point(CaliDepth,Nextmysrc , dst);
    float px, py, pz;
    softwareRegistrator.ConvertProjectiveToWorld(dst.x, dst.y, (int)CaliDepth.at<uint16_t>(mysrc.y,mysrc.x), px, py, pz, true);
    pz = mpz;

#endif

    if((int) px==0)
    {
        cout<<"no valid pnt3 "<<endl;
 //       break;
    }

    float Px = (px+18);//15,*-1
    float Py = py+210;//+130+95
    float Pz = 615-pz-8 ;
     cout<<"target position: "<<(int)Px<<","<<(int)Py<<","<<(int)(Pz)<<endl;

   //-------------------------------------move to P
   if(movePflag==false)
    {
        cout<<"moveing to P..."<<endl;
        int zzz = (int)pz;

        if(zzz!=0){
        GlobalPX = Px;
        GlobalPY = Py;
        GlobalPZ = Pz-10;

      //-----------------------------------compute the theoretical green point
        int numPx = (int)Px;
        if(numPx>-20&&numPx<20){ //middle
         float PxGreen = Px-4;
         float PyGreen = Py+62; //41
         float PzGreen = Pz+88;

         computedGreenX =PxGreen;
         computedGreenY =PyGreen;
         computedGreenZ =PzGreen;
        }
        else if(numPx<=-20){   //right
            float PxGreen = Px-11;
            float PyGreen = Py+27; //41
            float PzGreen = Pz+96;
            computedGreenX =PxGreen;
            computedGreenY =PyGreen;
            computedGreenZ =PzGreen;
        }
        else if(numPx>=20){  //left

            float PxGreen = Px-14;
            float PyGreen = Py+31; //41
            float PzGreen = Pz+114;
            computedGreenX =PxGreen;
            computedGreenY =PyGreen;
            computedGreenZ =PzGreen;
        }

       cout<<"first step: go to: "<<(int)Px<<","<<(int)Py<<","<<(int)(Pz-10)<<endl;
       emit moveToP((int)Px,(int)Py,(int)(Pz-10));
       QThread::msleep(400);

        movePflag = true;
        feedbackflag = true;
        tissuebagDetectflag = false;
        iternum =0;
        }

   }

    emit updateFrame(registerMat);//display normal BGR image
    QThread::msleep(delayTime);
    }

    }

    camera.StopRGBorIRStream();
    camera.StopDepthStream();
    camera.CloseDevice();

    cout << "bye!" << endl;
    return ;
}

void VisionServoThread::loadParams(OBCameraParams &params)
{
    params.l_intr_p[0] = 587.662;
    params.l_intr_p[1] = 590.474;
    params.l_intr_p[2] = 315.076;
    params.l_intr_p[3] = 243.267;
    params.r_intr_p[0] = 525.746;
    params.r_intr_p[1] = 527.435;
    params.r_intr_p[2] = 300.346;
    params.r_intr_p[3] = 237.728;

    params.r2l_r[0] =0.999702;
    params.r2l_r[1] =0.0021299;
    params.r2l_r[2] =0.0243313;
    params.r2l_r[3] =-0.00182891;
    params.r2l_r[4] =0.999922;
    params.r2l_r[5] =-0.0123861;
    params.r2l_r[6] =-0.0243558;
    params.r2l_r[7] =0.0123379;
    params.r2l_r[8] =0.999627;
    params.r2l_t[0] =-25.5325;
    params.r2l_t[1] =-0.184379;
    params.r2l_t[2] =-1.42236;

    params.l_k[0] = -0.0848228;
    params.l_k[1] = 0.257855;
    params.l_k[2] = -0.287954;
    params.l_k[3] = -0.00295626;
    params.l_k[4] = 0.00256612;
    params.r_k[0] = -0.0284233;
    params.r_k[1] = 0.0665382;
    params.r_k[2] = -0.0227067;
    params.r_k[3] = -0.000671229;
    params.r_k[4] = 0.00102594;

}

int VisionServoThread::colorDetection(Mat &imgin, Mat &imgout,Point &roughCenter, Rect &selectionout)
{
    //cout<<"color detecting....."<<endl;

    //---------------------hsv threshold
    int MyiLowH = 0;
    int MyiHighH = 54;
    int MyiLowS = 90;
    int MyiHighS =216;
    int MyiLowV = 155;
    int MyiHighV = 237;

    Mat imgThresholded;
    vector<Mat> hsvSplit;
    GaussianBlur(imgin,imgin,Size(3,3),0,0);
    cvtColor(imgin.clone(),hsv,COLOR_BGR2HSV);
    split(hsv,hsvSplit);
    equalizeHist(hsvSplit[2],hsvSplit[2]);
    merge(hsvSplit,hsv);

    inRange(imgin, Scalar(MyiLowH, MyiLowS, MyiLowV), Scalar(MyiHighH, MyiHighS, MyiHighV), imgThresholded); //Threshold the image
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    imgout = imgThresholded.clone();

    //------------------------------find contour
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    //Detect edges using canny
    int thresh = 100;
    Canny(imgThresholded, canny_output, thresh, thresh * 2, 3);
    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    //cout<<"contour number: "<<contours.size()<<endl;

    if(contours.size() ==0 ) //fail to detect
    {   cout<<"no target."<<endl;
        return -1;
    }

    int contoursArea[contours.size()];
    int max=0;
    for (int i = 0; i < contours.size(); i++){ //filter noise
        contoursArea[i]=contourArea(contours[i],true);
        if (contoursArea[i]>contoursArea[max]){
            max=i;
        }
    }

    //------------------------get rough center
    RotatedRect rect = fitEllipse(contours[max]);
    roughCenter=rect.center;
 //   Scalar color = Scalar(180);
 //   drawContours(imgout, contours, max, color, 2, 8, hierarchy, 0, Point());

    //----------------------output selection
    int xmax=0,xmin=1000,ymax=0,ymin=1000;
    for (int i=0;i<contours[max].size();i++){
        if(contours[max][i].x>xmax) xmax=contours[max][i].x;
        if(contours[max][i].x<xmin) xmin=contours[max][i].x;
        if(contours[max][i].y>ymax) ymax=contours[max][i].y;
        if(contours[max][i].y<ymin) ymin=contours[max][i].y;

    }
    selectionout.x=xmin;
    selectionout.y=ymin;
    selectionout.width=xmax-xmin;
    selectionout.height=ymax-ymin;

    cout<<"selection:x:"<<selectionout.x<<",y:"<<selectionout.y<<",width:"<<selectionout.width<<",height:"<<selectionout.height<<endl;

//    myAlgorithm.drawCross(imgout, Point2f(roughCenter.x,roughCenter.y),Scalar(220), 12,2);

    return 0;
}

int VisionServoThread::yellowCamshift(Mat &imgin, Mat &imgout, Rect &selectionin, Point &roughCenter)
{
    int vmin = 70;
    int vmax = 200;
    int smin = 186;
    imgout=imgin.clone();

    cvtColor(imgin,hsv,COLOR_BGR2HSV);
    hue.create(hsv.size(),hsv.depth());
    inRange(hsv,Scalar(0,smin,MIN(vmin,vmax)),Scalar(180,256,MAX(vmin,vmax)),mask);
    int ch[] = {0,0};
    mixChannels(&hsv,1,&hue,1,ch,1);

    //--------------------------get template hist once
    if(isGreendetectObject==-1 && iscaptureMarker==0){
    Mat roi(hue,selectionin), maskroi(mask,selectionin);
    calcHist(&roi,1,0,maskroi,hist,1,&hsize,&phranges);
    normalize(hist,hist,0,255,CV_MINMAX);
    trackWindow=selectionin;
//    cout<<"get hist"<<"finished"<<endl;
    }

    calcBackProject(&hue,1,0,hist,backproj,&phranges);
    backproj &=mask;
    RotatedRect trackBox = CamShift(backproj,trackWindow,TermCriteria(CV_TERMCRIT_EPS|CV_TERMCRIT_ITER,10,1));

    int trackArea = trackWindow.area();
    if((trackArea<=1) && (!GreenroughCenter.x) && (!GreenroughCenter.y)){ //lose a frame
        int cols = backproj.cols, rows=backproj.rows, r=(MIN(cols,rows)+5)/6;
        trackWindow = Rect(GreenroughCenter.x, GreenroughCenter.y, 20,20)&
                Rect(0,0,cols,rows);
    }
    else if(trackArea<=1){ //fail to detct, lose two frames or more
        isGreendetectObject = -1;
        iscaptureMarker=-1;
        cvtColor(imgout,imgout,CV_BGR2GRAY);
        return -1;
    }
//    cout<<"trackwindowArea:"<<area<<",x:"<<trackWindow.x<<",y:"<<trackWindow.y<<endl;

    //----------------------------get rough center
    Point2f vertices[4];
    trackBox.points(vertices);

    float x=0,y=0;
    for (int i=0;i<4;i++)
    {
        x+=vertices[i].x;
        y+=vertices[i].y;
    }
    roughCenter.x=int(x/4);
    roughCenter.y=int(y/4);
    cvtColor(imgout,imgout,CV_BGR2GRAY);

    return 0;
}

int VisionServoThread::GreencolorDetection(Mat &imgin, Mat &imgout, Point &roughCenter, Rect &selectionout)
{

    int MyiLowH = 103;
    int MyiHighH = 139;
    int MyiLowS = 46;
    int MyiHighS =90;
    int MyiLowV = 0;
    int MyiHighV = 219;

    Mat imgThresholded;
    vector<Mat> hsvSplit;

    GaussianBlur(imgin,imgin,Size(3,3),0,0);
    cvtColor(imgin.clone(),hsv,COLOR_BGR2HSV);
    split(hsv,hsvSplit);
    equalizeHist(hsvSplit[2],hsvSplit[2]);
    merge(hsvSplit,hsv);

    inRange(imgin, Scalar(MyiLowH, MyiLowS, MyiLowV), Scalar(MyiHighH, MyiHighS, MyiHighV), imgThresholded); //Threshold the image
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    imgout = imgThresholded.clone();

    //------------------------------find contour
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    int thresh = 100;
    Canny(imgThresholded, canny_output, thresh, thresh * 2, 3);
    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    //cout<<"contour number: "<<contours.size()<<endl;

    if(contours.size() ==0 ) //fail to detect
    {   cout<<"no marker."<<endl;
        return -1;
    }

    int contoursArea[contours.size()];
    int max=0;
    for (int i = 0; i < contours.size(); i++){ //filter noise
        contoursArea[i]=contourArea(contours[i],true);
        if (contoursArea[i]>contoursArea[max]){
            max=i;
        }
    }

   //----------------get rough center
    RotatedRect rect = fitEllipse(contours[max]);
    roughCenter=rect.center;
    Scalar color = Scalar(180);
    drawContours(imgout, contours, max, color, 2, 8, hierarchy, 0, Point());

    //-------------------------output selection
    int xmax=0,xmin=1000,ymax=0,ymin=1000;
    for (int i=0;i<contours[max].size();i++){
        if(contours[max][i].x>xmax) xmax=contours[max][i].x;
        if(contours[max][i].x<xmin) xmin=contours[max][i].x;
        if(contours[max][i].y>ymax) ymax=contours[max][i].y;
        if(contours[max][i].y<ymin) ymin=contours[max][i].y;

    }
    selectionout.x=xmin;
    selectionout.y=ymin;
    selectionout.width=xmax-xmin;
    selectionout.height=ymax-ymin;

    cout<<"selection:x:"<<selectionout.x<<",y:"<<selectionout.y<<",width:"<<selectionout.width<<",height:"<<selectionout.height<<endl;

    myAlgorithm.drawCross(imgout, Point2f(roughCenter.x,roughCenter.y),Scalar(220), 12,2);

    return 0;
}



void VisionServoThread::fillImage(Mat &frame, Point pt1, Point pt2)
{
    if (pt1.x > pt2.x) return;
    if (pt1.y > pt2.y) return;


    //segment upper
    for (int i = 0; i < pt1.y; i++){
        for (int j = 0; j < frame.cols; j++){

            frame.at<uchar>(i, j) = 0;
        }
    }

    //segment down
    for (int i = pt2.y; i < frame.rows; i++){
        for (int j = 0; j < frame.cols; j++){

            frame.at<uchar>(i, j) = 0;
        }
    }

    //segment left
    for (int i = 0; i < frame.rows; i++){
        for (int j = 0; j < pt1.x; j++){

            frame.at<uchar>(i, j) = 0;
        }
    }

    //segment right
    for (int i = 0; i < frame.rows; i++){
        for (int j = pt2.x; j < frame.cols; j++){

            frame.at<uchar>(i, j) = 0;
        }
    }



    return;
}

int VisionServoThread::detectMesh(Mat &imgin, Mat &imgout, Point &roughCenter)
{
    Mat gray;
    Mat corners;
    vector<pointsSet> objs;
    cvtColor(imgin.clone(),imgout,COLOR_GRAY2BGR);
    //cvtColor(imgin.clone(),gray,COLOR_BGR2GRAY);
    goodFeaturesToTrack(imgin,corners,800,0.1,5);

    cout<<"points:"<<imgin.rows<<","<<imgin.cols<<endl;
    for(int row=0;row<corners.rows;row++){
        int x = corners.at<Vec3b>(row,1)[0];
        int y = corners.at<Vec3b>(row,1)[1];
        //cout<<x<<","<<y<<endl;
        if (objs.size()==0){
            objs.push_back(pointsSet(Point(x,y)));
            continue;
        }
        vector<float> distances;
        for(int n=0;n<objs.size();n++)
        {
            Point cent = objs[n].center;
            distances.push_back(pow(cent.x-x,2)+pow(cent.y-y,2));
        }

        int min_index = 0;
        for(int n=0;n<distances.size();n++){
            if (distances[n]<distances[min_index]){
                min_index=n;
            }
        }
        if (distances[min_index] > 5000){
            objs.push_back(pointsSet(Point(x,y)));
            continue;
        }
        objs[min_index].addPoint(Point(x,y));
    }
    cout<<"obj_num:"<<objs.size()<<endl;
    for(int n=0;n<objs.size();n++){
        pointsSet obj=objs[n];
        if (obj.points.size() > 50){
            cout<<"points:"<<obj.points.size()<<endl;
//            for(int i=0;i<obj.points.size();i++){
//                Point pp = obj.points[i];
//                cout<<pp.x<<","<<pp.y<<endl;
//                circle(imgout,pp,10,255,-1);
//            }
            roughCenter.x=obj.center.x;
            roughCenter.y=obj.center.y;
            circle(imgout,obj.center,5,60,-1);
            //cout<<"roughcenter:"<<roughCenter.x<<","<<roughCenter.y<<endl;
        }
    }
    cout<<"hh"<<endl;
    return 0;
}

pointsSet::pointsSet(Point p)
{
    points.push_back(p);
}

void pointsSet::updateCenter()
{
    float xx=0,yy=0;
    for(int i=0;i<points.size();i++){
        xx+=points[i].x;
        yy+=points[i].y;

    }
    center.x=(int)xx/points.size();
    center.y=(int)yy/points.size();
}

void pointsSet::addPoint(Point p)
{
    points.push_back(p);
    updateCenter();
}
