#ifndef VISIONSERVOTHREAD_H
#define VISIONSERVOTHREAD_H
#include <iostream>
#include <math.h>
using namespace std;
#include <QThread>
#include <QObject>
#include "mystereocam.h"


#include "opencv2/opencv.hpp"
using namespace cv;


// OpenNI2
#include "OpenNI.h"
#include <iostream>
#include <math.h>
using namespace openni;

// OpenCV
#include "opencv2/opencv.hpp"
#include "RGBDCamera.h"
using namespace std;
using namespace cv;

#include "Draw.h"
#include "SoftwareRegistrator.h"
#include "MyTinyAlgorithm.h"


class VisionServoThread : public QThread
{
    Q_OBJECT
public:
    VisionServoThread();
    bool stop;
    void run();


    vector<Point> pointSet;
    vector<Point> pointSetPredict;
    vector<Point> pointSetDetect;
    bool tissuebagDetectflag;

private:
    MyStereoCam *myCam;
    void loadParams(OBCameraParams &params);
    void camshiftDetection(Mat &imgin, Mat &imgout, Point &roughCenter);
    void loadTemplateImage();
    int colorDetection(Mat &imgin, Mat &imgout, Point &roughCenter, Rect &selectionout); //for targert
    int yellowCamshift(Mat &imgin, Mat &imgout, Rect &selectionin, Point &roughCenter);
    int GreencolorDetection(Mat &imgin,Mat &imgout,Point &roughCenter, Rect &selectionout);// for green point
    int detectMesh(Mat &imgin, Mat &imgout, Point &roughCenter);
    MyTinyAlgorithm myAlgorithm;

    bool movePflag ;
    bool feedbackflag;
    int iternum;
    float computedGreenX,computedGreenY,computedGreenZ;
    float GlobalPX,GlobalPY,GlobalPZ; //control vars
    void fillImage(Mat &frame, Point pt1, Point pt2);

    Mat roi;
    Mat hue;
    Mat hsv;
    Mat hist;
    Mat backproj;
    Mat image_roi;
    Rect trackWindow;
    int _vmin = 0;
    int vmax = 0;



signals:
    void updateFrame(Mat);
    void updateCam2Frame(Mat);
    void moveToP(int,int,int);
    void gripControl(int);
    void moveMotor1(int,int,int);

};

class pointsSet
{
public:
    pointsSet(Point p);
    void updateCenter();
    void addPoint(Point p);
    Point center;
    vector<Point> points;
};

#endif // VISIONSERVOTHREAD_H
