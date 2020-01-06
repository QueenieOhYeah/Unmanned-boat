
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>

#define QDEBUG
int ideal_y=250;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    cout<<"Hello!"<<endl;

    ui->setupUi(this);

    visionThread = new VisionServoThread();
    qRegisterMetaType<Mat>("Mat");
     qRegisterMetaType<int>("int");
    connect(visionThread,SIGNAL(updateFrame(Mat)),this,SLOT(updateFrame(Mat)));
    connect(visionThread,SIGNAL(moveToP(int,int,int)),this,SLOT(moveToP(int,int,int)));
    connect(visionThread,SIGNAL(gripControl(int)),this,SLOT(gripControl(int)));
    connect(visionThread,SIGNAL(moveMotor1(int,int,int)),this,SLOT(moveMotor1(int,int,int)));
//    connect(visionThread,SIGNAL(moveMotor1(int,int,int)),this,SLOT(stepperInitial(int)));
    connect(visionThread,SIGNAL(updateCam2Frame(Mat)),this,SLOT(updateCam2Frame(Mat)));

    timer=new QTimer();

    M1_leftMove_flag = true;
    m_lasttime.push_back(0.00);
    m_lasttime.push_back(0.00);
    m_lasttime.push_back(0.00);
    m_lasttime.push_back(0.00);
    m_lasttime.push_back(0.00);


    connect(&serial,SIGNAL(readyRead()),this,SLOT(serialReceived()));


    ui->M6_ON_button->setEnabled(false);
    ui->disconnect_serial_button->setEnabled(false);
    ui->send_button->setEnabled(false);

    //cout<<"hello world";

    serial.setBaudRate(QSerialPort::Baud115200);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::rectifyMotorValue(vector<vector<double> > &MyCurrentResultM, vector<vector<double> > &CurrentResultM_Rectified)
{
    CurrentResultM_Rectified = MyCurrentResultM;
   // cout<<"before rectified value: "<<MyCurrentResultM[0][0]<<endl;

    for(int i=0;i<MyCurrentResultM.size();i++)
    {
        DataRectifyConvert(MyCurrentResultM[i][0],CurrentResultM_Rectified[i][0]);
    }


    for(int i=0;i<MyCurrentResultM.size();i++){
    CurrentResultM_Rectified[i][1] = MyCurrentResultM[i][1]+24;
    //cout<<"original: "<<MyCurrentResultM[i][1]<<"; after: "<<CurrentResultM_Rectified[i][1]<<endl;
    }



}

void MainWindow::DataRectifyConvert(double &data_in, double &data_converted)
{
//    theory          practical        practical2
//    -90             -90               -90
//    -80             -80               -83
//    -70             -72               -74
//    -60             -62               -66
//    -50             -55               -57
//    -40             -45               -49
//    -30             -35               -39
//    -20             -25               -29
//    -10             -14               -17
//      0              -4               -10
//     10              10                 3
//     20              20                15
//     30              30                26
//     40              40                36
//     50              50                46
//     60              60                56
//     70              70                64
//     80              80                74
//     90              90                84

    int d_m90 = -90;
    int d_m80 = -80;
    int d_m70 = -72;
    int d_m60 = -62;
    int d_m50 = -55;
    int d_m40 = -45;
    int d_m30 = -35;
    int d_m20 = -25;
    int d_m10 = -14;
    int d_0 = -4;
    int d_10 = 10;
    int d_20 = 20;
    int d_30 = 30;
    int d_40 = 40;
    int d_50 = 50;
    int d_60 = 60;
    int d_70 = 70;
    int d_80 = 80;
    int d_90 = 90;

  //  cout<<"data_in: "<<data_in<<endl;
    int data = int(data_in);

    if(data<-80&& data>=-90){

        data_converted  = d_m80 + (d_m80 -d_m90)/10.0 * (data+80);
      // cout<<"data_out: "<<data_converted<<endl;
     //  cout<<"m80"<<endl;
       return ;
    }

    if(data<-70&& data>=-80){

        data_converted  = d_m70 + (d_m70 -d_m80)/10.0 * (data+70);
       //cout<<"data_out: "<<data_converted<<endl;
    //   cout<<"m70"<<endl;
       return ;
    }

    if(data<-60&& data>=-70){

        data_converted  = d_m60 + (d_m60 -d_m70)/10.0 * (data+60);
      // cout<<"data_out: "<<data_converted<<endl;
    //   cout<<"m60"<<endl;
        return ;
    }

    if(data<-50&& data>=-60){

        data_converted  = d_m50 + (d_m50 -d_m60)/10.0 * (data+50);
     //  cout<<"data_out: "<<data_converted<<endl;
    //   cout<<"m50"<<endl;
        return ;
    }

    if(data<-40&& data>=-50){

        data_converted  = d_m40 + (d_m40 -d_m50)/10.0 * (data+40);
   //    cout<<"data_covted,"<<data_converted<<"="<< d_m40<<"+("<<d_m40<<"-"<<d_m50<<")/10.0*("<<data<<"+40)"<<endl;
        //cout<<"data_out: "<<data_converted<<endl;
    //    cout<<"m40"<<endl;

        return ;
    }

    if(data<-30&& data>=-40){

        data_converted  = d_m30 + (d_m30 -d_m40)/10.0 * (data+30);
    //   cout<<"data_out: "<<data_converted<<endl;
   //    cout<<"m30"<<endl;
   //    cout<<"data: "<<data<<endl;
   //     cout<<"d_m30: "<<d_m30<<",d_m40: "<<d_m40<<endl;
       return ;
    }

    if(data<-20&& data>=-30){

        data_converted  = d_m20 + (d_m20 -d_m30)/10.0 * (data+20);
      // cout<<"data_out: "<<data_converted<<endl;
   //    cout<<"m20"<<endl;
        return ;
    }

    if(data<-10&& data>=-20){

        data_converted  = d_m10 + (d_m10 -d_m20)/10.0 * (data+10);
   //      cout<<"data_covted,"<<data_converted<<"="<< d_m10<<"+("<<d_m10<<"-"<<d_m20<<")/10.0*("<<data<<"+10)"<<endl;
       //cout<<"data_out: "<<data_converted<<endl;
     //  cout<<"m10"<<endl;
        return ;
    }

    if(data<0&& data>=-10){

        data_converted  = d_0 + (d_0 -d_m10)/10.0 * data;
       //cout<<"data_out: "<<data_converted<<endl;
        return ;
    }


    if(data<10&& data>=0){

        data_converted  = d_10 + (d_10 -d_0)/10.0 * (data-10);
       //cout<<"data_out: "<<data_converted<<endl;
        return ;
    }

    if(data<20&& data>=10){

        data_converted  = d_20 + (d_20 -d_10)/10.0 * (data-20);
      // cout<<"data_out: "<<data_converted<<endl;
        return ;
    }


    if(data<30&& data>=20){

        data_converted  = d_30 + (d_30 -d_20)/10.0 * (data-30);
      // cout<<"data_out: "<<data_converted<<endl;
        return ;
    }

    if(data<40&& data>=30){

        data_converted  = d_40 + (d_40 -d_30)/10.0 * (data-40);
     //  cout<<"data_out: "<<data_converted<<endl;
        return ;
    }

    if(data<50&& data>=40){

        data_converted  = d_50 + (d_50 -d_40)/10.0 * (data-50);
       //cout<<"data_out: "<<data_converted<<endl;
        return ;
    }

    if(data<60&& data>=50){

        data_converted  = d_60 + (d_60 -d_50)/10.0 * (data-60);
     //  cout<<"data_out: "<<data_converted<<endl;
        return ;
    }

    if(data<70&& data>=60){

        data_converted  = d_70 + (d_70 -d_60)/10.0 * (data-70);
      // cout<<"data_out: "<<data_converted<<endl;
        return ;
    }

    if(data<80&& data>=70){

        data_converted  = d_80 + (d_80 -d_70)/10.0 * (data-80);
       //cout<<"data_out: "<<data_converted<<endl;
        return ;
    }

    if(data<90&& data>=80){

        data_converted  = d_90 + (d_90 -d_80)/10.0 * (data-90);
     //  cout<<"data_out: "<<data_converted<<endl;
        return ;
    }

    cout<<"none!"<<endl;

}

void MainWindow::moveMotor1(int Px, int Py, int Pz)
{
    cout<<"get: moved to px py pz: "<<Px<<","<<Py<<","<<Pz<<endl;
    //go there

    double motor1Angle = -1.0*atan2(Px,Py)/3.14159*180+30;
    cout<<"motor1Angle: "<<motor1Angle<<endl;

    double motor1Angle_rectified;
    DataRectifyConvert(motor1Angle,motor1Angle_rectified);


//   QString cmdstr_rectified = (QString::number((int)motor1Angle_rectified, 10) +","
//                     +ui->lineEdit_m2->text()+","
//                     +ui->lineEdit_m3->text()+","
//                     +ui->lineEdit_m4->text()+","
//                     +QString::number((int)motor1Angle_rectified, 10)+","
//                     +ui->lineEdit_m6->text()
//                     );


//    serial.write((cmdstr_rectified+"\n").toLatin1());
    serialCommand(35,
                  (int)motor1Angle_rectified,
                  ui->lineEdit_m2->text().toInt(),
                  ui->lineEdit_m3->text().toInt(),
                  ui->lineEdit_m4->text().toInt(),
                  (int)motor1Angle_rectified,
                  ui->lineEdit_m6->text().toInt(),
                  ui->lineEdit_stepper->text().toInt());
   serial.waitForBytesWritten(100);


    //update gui
    ui->lineEdit_m1->setText(QString::number((int)motor1Angle_rectified, 10));
    cout<<"done!"<<endl;
}

void MainWindow::gripControl(int var)
{
    //cout<<"get gripper Control value: "<<var<<endl;
    double m1_angle;
    double m1_tmp=ui->lineEdit_m1->text().toDouble();
//    DataRectifyConvert(m1_tmp,m1_angle);

//     QString cmdstr = ( QString::number((int)m1_tmp, 10) +","
//                      +ui->lineEdit_m2->text()+","
//                      +ui->lineEdit_m3->text()+","
//                      +ui->lineEdit_m4->text()+","
//                      +ui->lineEdit_m5->text()+","
//                      +QString::number(var, 10)
//                      );
//    serial.write((cmdstr+"\n").toLatin1());

//     ui->textEdit->append("sent: "+cmdstr);
    serialCommand(35,
                  (int)m1_tmp,
                  ui->lineEdit_m2->text().toInt(),
                  ui->lineEdit_m3->text().toInt(),
                  ui->lineEdit_m4->text().toInt(),
                  ui->lineEdit_m5->text().toInt(),
                  var,
                  ui->lineEdit_stepper->text().toInt());


    ui->lineEdit_m6->setText(QString::number(var, 10));
    serial.waitForBytesWritten(100);


}

void MainWindow::stepperInitial()
{
    serialCommand(37,0,38,-90,-90,0,1,0);
    ui->lineEdit_m1->setText("0");
    ui->lineEdit_m2->setText("38");
    ui->lineEdit_m3->setText("-90");
    ui->lineEdit_m4->setText("-90");
    ui->lineEdit_m5->setText("0");
    ui->lineEdit_m6->setText("1");
}

void MainWindow::moveToP(int Px, int Py, int Pz)
{
    //cout<<"get: moved to px py pz: "<<Px<<","<<Py<<","<<Pz<<endl;
    //go there
    double dev_y;
    dev_y=Py-ideal_y;
    if (dev_y>40) dev_y=40;
    if (dev_y<-10) dev_y=-10;

    vector<double> dst_pos;
    dst_pos.push_back((double)Px);
    dst_pos.push_back((double)Py-dev_y);
    dst_pos.push_back((double)Pz);

    vector<vector<double> > resultM;
    int errorcode = RL.MyinverseKinematics(dst_pos, resultM);
   // cout<<"verifing..."<<endl;
  //  cout<<"m1:"<<resultM[0][0]<<",m2:"<<resultM[0][1]<<endl;

    if(errorcode ==-1){
        ui->textEdit_endPointcontrol->append("No result!");
        CurrentResultM.clear();
        return ;
    }


    for (int i=0;i<resultM.size();i++){
        //cout<<i<<" q0-4:"<<resultM[i][0] <<","<<resultM[i][1]<<","<<resultM[i][2]<<","<<resultM[i][3]<<","<<resultM[i][4]<<endl;

        QString cmdstr = QString::number(i,10)+" q0-4: "
                +QString::number((int)resultM[i][0], 10) +","
                +QString::number((int)resultM[i][1], 10) +","
                +QString::number((int)resultM[i][2], 10) +","
                +QString::number((int)resultM[i][3], 10) +","
                +QString::number((int)resultM[i][4], 10);

        ui->textEdit_endPointcontrol->append(cmdstr);

    }

    CurrentResultM.clear();
    CurrentResultM = resultM;
    CurrentResultStepper=dev_y;


    int ID =0;
//    QString cmdstr =  QString::number((int)CurrentResultM[ID][0], 10) +","
//                      +QString::number((int)CurrentResultM[ID][1], 10) +","
//                      +QString::number((int)CurrentResultM[ID][2], 10) +","
//                      +QString::number((int)CurrentResultM[ID][3], 10) +","
//                      +"0"+","
//                      +"1";


   // cout<<"proccess 2: go therehere2"<<endl;
    vector<vector<double> > CurrentResultM_Rectified;
    rectifyMotorValue(CurrentResultM,CurrentResultM_Rectified);

//    QString cmdstr_rectified =  QString::number((int)CurrentResultM_Rectified[ID][0], 10) +","
//                      +QString::number((int)CurrentResultM_Rectified[ID][1], 10) +","
//                      +QString::number((int)CurrentResultM_Rectified[ID][2], 10) +","
//                      +QString::number((int)CurrentResultM_Rectified[ID][3], 10) +","
//                      +QString::number((int)CurrentResultM_Rectified[ID][0], 10)+","
//                      +ui->lineEdit_m6->text();
//    serial.write((cmdstr_rectified+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
    serialCommand(35,
            (int)CurrentResultM_Rectified[ID][0],
            (int)CurrentResultM_Rectified[ID][1],
            (int)CurrentResultM_Rectified[ID][2],
            (int)CurrentResultM_Rectified[ID][3],
            (int)CurrentResultM_Rectified[ID][0],
            0,
            (int)CurrentResultStepper);

   serial.waitForBytesWritten(100);


    //update gui
    ui->lineEdit_m1->setText(QString::number((int)CurrentResultM_Rectified[ID][0]));
    ui->lineEdit_m2->setText(QString::number((int)CurrentResultM_Rectified[ID][1]));
    ui->lineEdit_m3->setText(QString::number((int)CurrentResultM_Rectified[ID][2]));
    ui->lineEdit_m4->setText(QString::number((int)CurrentResultM_Rectified[ID][3]));
    ui->lineEdit_m5->setText(QString::number((int)CurrentResultM_Rectified[ID][0]));
    ui->lineEdit_m6->setText(ui->lineEdit_m6->text());
    ui->lineEdit_stepper->setText(QString::number((int)CurrentResultStepper));
   // sleep(1);
    //cout<<"done!"<<endl;

}

void MainWindow::updateFrame(Mat image)
{
    Mat image1_updated;
    cvtColor(image,image1_updated,CV_BGR2RGB);
    QImage qimage((uchar*)image1_updated.data,image1_updated.cols,image1_updated.rows,image1_updated.step,QImage::Format_RGB888);
    ui->image_Label->setPixmap(QPixmap::fromImage(qimage).scaled(QSize(ui->image_Label->width(),ui->image_Label->height())));

}


void MainWindow::updateCam2Frame(Mat image)
{
    Mat image2_updated;
    cvtColor(image,image2_updated,CV_BGR2RGB);
    QImage qimage((uchar*)image2_updated.data,image2_updated.cols,image2_updated.rows,image2_updated.step,QImage::Format_RGB888);
    ui->cam2_Label->setPixmap(QPixmap::fromImage(qimage).scaled(QSize(ui->cam2_Label->width(),ui->cam2_Label->height())));
}

void MainWindow::serialReceived()
{
    ui->textEdit->append("received: "+serial.readAll());

}



void MainWindow::on_Connect_serial_button_clicked()
{
    //cout<<"opening the port...";
    serial.setPortName(ui->lineEdit_2->text());
    if(serial.open(QIODevice::ReadWrite))
    {
           ui->textEdit->append(ui->lineEdit_2->text()+" is connected successfully!");
           ui->Connect_serial_button->setEnabled(false);
           ui->disconnect_serial_button->setEnabled(true);
           ui->send_button->setEnabled(true);

    }
    else{

        ui->textEdit->append("failed to connect to "+ui->lineEdit_2->text());
    }

}

void MainWindow::on_disconnect_serial_button_clicked()
{
    serial.close();
    if(!serial.isOpen())
    {
        ui->textEdit->append(ui->lineEdit_2->text()+" is closed successfully!");
        ui->disconnect_serial_button->setEnabled(false);
        ui->Connect_serial_button->setEnabled(true);
        ui->send_button->setEnabled(false);

    }
    else
    {

        ui->textEdit->append("failed to close "+ui->lineEdit_2->text());
        QString result = QString(system("echo 'joule' | sudo -S chmod 777 /dev/ttyACM*"));
        ui->textEdit->append("enable and reconnect the serail!");
        if (result != NULL){
             serial.setPortName(ui->lineEdit_2->text());
             if(serial.open(QIODevice::ReadWrite))
             {
                   ui->textEdit->append(ui->lineEdit_2->text()+" is connected successfully!");
                   ui->Connect_serial_button->setEnabled(false);
                   ui->disconnect_serial_button->setEnabled(true);
                   ui->send_button->setEnabled(true);

              }
              else{
                   ui->textEdit->append("fail to reconnect to !"+ui->lineEdit_2->text());
                }
              }
    }
}

void MainWindow::on_send_button_clicked()
{
    ui->textEdit->append("sent: "+ui->lineEdit->text());
    serial.write((ui->lineEdit->text()+"\n").toLatin1());

}

void MainWindow::on_send_CMD_button_clicked()
{

//    QString cmdstr = (ui->lineEdit_m1->text()+","
//                      +ui->lineEdit_m2->text()+","
//                      +ui->lineEdit_m3->text()+","
//                      +ui->lineEdit_m4->text()+","
//                      +ui->lineEdit_m5->text()+","
//                      +ui->lineEdit_m6->text()
//                      );

//    serial.write((cmdstr+"\n").toLatin1());
//     ui->textEdit->append("sent: "+cmdstr);
    serialCommand(35,
                  ui->lineEdit_m1->text().toInt(),
                  ui->lineEdit_m2->text().toInt(),
                  ui->lineEdit_m3->text().toInt(),
                  ui->lineEdit_m4->text().toInt(),
                  ui->lineEdit_m5->text().toInt(),
                  ui->lineEdit_m6->text().toInt(),
                  ui->lineEdit_stepper->text().toInt());
}







void MainWindow::on_fk_calculation_button_clicked()
{


    cout<<" ";
    cout<<"==============================";
    cout<<" ";
    cout<<"FK calculation...";

    //##############TEST FK
       vector<double>m;
       double valDegreetoRad = 1.0/180*3.1415926;
       m.push_back(ui->lineEdit_m1->text().toDouble()*valDegreetoRad);
       m.push_back(ui->lineEdit_m2->text().toDouble()*valDegreetoRad);
       m.push_back(ui->lineEdit_m3->text().toDouble()*valDegreetoRad);
       m.push_back(ui->lineEdit_m4->text().toDouble()*valDegreetoRad);
       m.push_back(ui->lineEdit_m5->text().toDouble()*valDegreetoRad);


       cout<<"msize:"<<m.size();
       for (int i=0;i<m.size();i++){
           cout<<"input value:"<<m[i];
       }




                vector<double>result;
           int      error = RL.MyforwardKinematics(m,result);
                  if(error ==-1){
                      cout<<"fk failed! "<<endl;
                      return;
                  }


       ui->textEdit_endPointcontrol->append("fk succeded!");
       QString cmdstr = "fk_pos:"
               + QString("%1").arg(result[0])+","
              + QString("%1").arg(result[1])+","
               + QString("%1").arg(result[2]);
       ui->textEdit_endPointcontrol->append(cmdstr);


}



void MainWindow::on_MyTestIK_button_clicked()
{
    vector<double> dst_pos;
    double dev_y;
    dev_y=ui->lineEdit_y->text().toDouble()-ideal_y;
    if (dev_y>40) dev_y=40;
    if (dev_y<-10) dev_y=-10;

    dst_pos.push_back(ui->lineEdit_x->text().toDouble());
    dst_pos.push_back(ui->lineEdit_y->text().toDouble()-dev_y);
    dst_pos.push_back(ui->lineEdit_z->text().toDouble());

    vector<vector<double> > resultM;
    int errorcode = RL.MyinverseKinematics(dst_pos, resultM);
    cout<<"verifing..."<<endl;

    if(errorcode ==-1){
        ui->textEdit_endPointcontrol->append("No result!");
        CurrentResultM.clear();
    }

    for (int i=0;i<resultM.size();i++){
        cout<<i<<" q0-4:"<<resultM[i][0] <<","<<resultM[i][1]<<","<<resultM[i][2]<<","<<resultM[i][3]<<","<<resultM[i][4]<<endl;

        QString cmdstr = QString::number(i,10)+" q0-4: "
                +QString::number((int)resultM[i][0], 10) +","
                +QString::number((int)resultM[i][1], 10) +","
                +QString::number((int)resultM[i][2], 10) +","
                +QString::number((int)resultM[i][3], 10) +","
                +QString::number((int)resultM[i][4], 10);

        ui->textEdit_endPointcontrol->append(cmdstr);
    }

    CurrentResultM.clear();
    CurrentResultM = resultM;
    CurrentResultStepper = dev_y;
}


void MainWindow::on_Run_button_clicked()
{
     int ID = ui->lineEdit_ID->text().toInt();
//     QString cmdstr =  QString::number((int)CurrentResultM[ID][0], 10) +","
//                       +QString::number((int)CurrentResultM[ID][1], 10) +","
//                       +QString::number((int)CurrentResultM[ID][2], 10) +","
//                       +QString::number((int)CurrentResultM[ID][3], 10) +","
//                       +"0"+","
//                       +"1";




     cout<<"run "<<ID<<": "<< CurrentResultM[ID][0]
                           <<","<< CurrentResultM[ID][1]
                           <<","<< CurrentResultM[ID][2]
                           <<","<< CurrentResultM[ID][3]
                           <<","<< CurrentResultM[ID][4]
                           <<",stepper:"<< CurrentResultStepper<<endl;
#ifndef QDEBUG

     //open the gripper
     cout<<"proccess 1: open the gripper"<<endl;
     double m1_angle;
     double m1_tmp=ui->lineEdit_m1->text().toDouble();
     DataRectifyConvert(m1_tmp,m1_angle);

//      cmdstr = ( QString::number((int)m1_angle, 10) +","
//                       +ui->lineEdit_m2->text()+","
//                       +ui->lineEdit_m3->text()+","
//                       +ui->lineEdit_m4->text()+","
//                       +ui->lineEdit_m5->text()+","
//                       +"0"
//                       );
//     serial.write((cmdstr+"\n").toLatin1());
//      ui->textEdit->append("sent: "+cmdstr);
     serialCommand(35,
                   (int)m1_angle,
                   ui->lineEdit_m2->text().toInt(),
                   ui->lineEdit_m3->text().toInt(),
                   ui->lineEdit_m4->text().toInt(),
                   ui->lineEdit_m5->text().toInt(),
                   0,
                   ui->lineEdit_stepper->text().toInt);
     ui->lineEdit_m6->setText("0");
     serial.waitForBytesWritten(100);

      sleep(1);
#endif


     //go there
      cout<<"proccess 2: go therehere2"<<endl;
     vector<vector<double> > CurrentResultM_Rectified;
     rectifyMotorValue(CurrentResultM,CurrentResultM_Rectified);

//     QString cmdstr_rectified =  QString::number((int)CurrentResultM_Rectified[ID][0], 10) +","
//                       +QString::number((int)CurrentResultM_Rectified[ID][1], 10) +","
//                       +QString::number((int)CurrentResultM_Rectified[ID][2], 10) +","
//                       +QString::number((int)CurrentResultM_Rectified[ID][3], 10) +","
//                       +QString::number((int)CurrentResultM_Rectified[ID][0], 10)+","
//                       +ui->lineEdit_m6->text();
//     serial.write((cmdstr_rectified+"\n").toLatin1());
//     ui->textEdit->append("sent: "+cmdstr);
     serialCommand(35,
                   (int)CurrentResultM_Rectified[ID][0],
                   (int)CurrentResultM_Rectified[ID][1],
                   (int)CurrentResultM_Rectified[ID][2],
                   (int)CurrentResultM_Rectified[ID][3],
                   (int)CurrentResultM_Rectified[ID][0],
                   ui->lineEdit_m6->text().toInt(),
                   CurrentResultStepper);
    serial.waitForBytesWritten(100);


     //update gui
     ui->lineEdit_m1->setText(QString::number((int)CurrentResultM_Rectified[ID][0]));
     ui->lineEdit_m2->setText(QString::number((int)CurrentResultM_Rectified[ID][1]));
     ui->lineEdit_m3->setText(QString::number((int)CurrentResultM_Rectified[ID][2]));
     ui->lineEdit_m4->setText(QString::number((int)CurrentResultM_Rectified[ID][3]));
     ui->lineEdit_m5->setText(QString::number((int)CurrentResultM_Rectified[ID][0]));
     ui->lineEdit_m6->setText(ui->lineEdit_m6->text());
     ui->lineEdit_stepper->setText(QString::number((int)CurrentResultStepper));
     sleep(2);




#ifndef QDEBUG

    // close gripper
     cout<<"proccess 3: close gripper"<<endl;
//    cmdstr = (QString::number((int)CurrentResultM_Rectified[ID][0], 10)+","
//                     +ui->lineEdit_m2->text()+","
//                     +ui->lineEdit_m3->text()+","
//                     +ui->lineEdit_m4->text()+","
//                     +ui->lineEdit_m5->text()+","
//                     +"1"
//                     );
//   serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
     serialCommand(35,
                   (int)CurrentResultM_Rectified[ID][0],
                   ui->lineEdit_m2->text().toInt(),
                   ui->lineEdit_m3->text().toInt(),
                   ui->lineEdit_m4->text().toInt(),
                   ui->lineEdit_m5->text().toInt(),
                   1,
                   ui->lineEdit_stepper->text().toInt());
    ui->lineEdit_m6->setText("1");
    serial.waitForBytesWritten(100);

     sleep(2);
    // pull up
     cout<<"proccess 4: pull up"<<endl;
//    cmdstr = (QString::number((int)CurrentResultM_Rectified[ID][0], 10)+","
//                     +"20"+","
//                     +ui->lineEdit_m3->text()+","
//                     +ui->lineEdit_m4->text()+","
//                     +ui->lineEdit_m5->text()+","
//                     +ui->lineEdit_m6->text()
//                     );
//   serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
     serialCommand(35,
                   (int)CurrentResultM_Rectified[ID][0],
                   20,
                   ui->lineEdit_m3->text().toInt(),
                   ui->lineEdit_m4->text().toInt(),
                   ui->lineEdit_m5->text().toInt(),
                   ui->lineEdit_m6->text().toInt(),
                   ui->lineEdit_stepper->text().toInt());
    ui->lineEdit_m2->setText("20");
    serial.waitForBytesWritten(100);

     sleep(1);
    // goes back
     cout<<"proccess 5: go back"<<endl;
//    cmdstr = (QString("-90")+","
//                     +ui->lineEdit_m2->text()+","
//                     +ui->lineEdit_m3->text()+","
//                     +ui->lineEdit_m4->text()+","
//                     +ui->lineEdit_m5->text()+","
//                     +ui->lineEdit_m6->text()
//                     );
//   serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
     serialCommand(35,
                   -90,
                   ui->lineEdit_m2->text().toInt(),
                   ui->lineEdit_m3->text().toInt(),
                   ui->lineEdit_m4->text().toInt(),
                   ui->lineEdit_m5->text().toInt(),
                   ui->lineEdit_m6->text().toInt(),
                   ui->lineEdit_stepper->text().toInt());
    ui->lineEdit_m1->setText("-90");
    serial.waitForBytesWritten(100);

     sleep(1);

     //goes down
     cout<<"proccess 6: drop it"<<endl;
//    cmdstr = (        ui->lineEdit_m1->text()+","
//                     +"-8"+","
//                     +ui->lineEdit_m3->text()+","
//                     +ui->lineEdit_m4->text()+","
//                     +ui->lineEdit_m5->text()+","
//                     +ui->lineEdit_m6->text()
//                     );
//   serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
     serialCommand(35,
                   ui->lineEdit_m1->text().toInt(),
                   -8,
                   ui->lineEdit_m3->text().toInt(),
                   ui->lineEdit_m4->text().toInt(),
                   ui->lineEdit_m5->text().toInt(),
                   ui->lineEdit_m6->text().toInt(),
                   ui->lineEdit_stepper->text().toInt());
    ui->lineEdit_m2->setText("-8");
    serial.waitForBytesWritten(100);
    sleep(1);


    // drop it
     cout<<"proccess 7: drop it"<<endl;
//    cmdstr = (        ui->lineEdit_m1->text()+","
//                     +ui->lineEdit_m2->text()+","
//                     +ui->lineEdit_m3->text()+","
//                     +ui->lineEdit_m4->text()+","
//                     +ui->lineEdit_m5->text()+","
//                     +"0"
//                     );
//   serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
     serialCommand(35,
                   ui->lineEdit_m1->text().toInt(),
                   ui->lineEdit_m2->text().toInt(),
                   ui->lineEdit_m3->text().toInt(),
                   ui->lineEdit_m4->text().toInt(),
                   ui->lineEdit_m5->text().toInt(),
                   0,
                   ui->lineEdit_stepper->text().toInt());
    ui->lineEdit_m6->setText("0");
    serial.waitForBytesWritten(100);
     cmdstr = "run "+QString::number(ID,10)+": "+
             QString::number((int)CurrentResultM[ID][0], 10) +","
             +QString::number((int)CurrentResultM[ID][1], 10) +","
             +QString::number((int)CurrentResultM[ID][2], 10) +","
             +QString::number((int)CurrentResultM[ID][3], 10) +","
             +QString::number((int)CurrentResultM[ID][4], 10);


     ui->textEdit_endPointcontrol->append(cmdstr);


      sleep(1);


    //return to idle position
     cout<<"proccess 8: home position"<<endl;
//     cmdstr = QString( "0,46,-63,-80,0,1");
//    serial.write((cmdstr+"\n").toLatin1());
     serialCommand(35,0,46,-63,-80,0,1,0);
     ui->textEdit->append("sent: "+cmdstr);
     ui->lineEdit_m1->setText("0");
     ui->lineEdit_m2->setText("46");
     ui->lineEdit_m3->setText("-63");
     ui->lineEdit_m4->setText("-80");
     ui->lineEdit_m5->setText("0");
     ui->lineEdit_m6->setText("1");
     serial.waitForBytesWritten(100);
#endif



     cout<<"done!"<<endl;


}







void MainWindow::M1_moveLeft_Timer()
{
    int Value = ui->lineEdit_m1->text().toInt();
    Value = Value+2;


    if(Value>90) {
        cout<<"reached left limit!"<<endl;
        return;

    }

    ui->lineEdit_m1->setText(QString::number( Value, 10));
//    QString cmdstr = (QString::number( Value, 10)+","
//                      +ui->lineEdit_m2->text()+","
//                      +ui->lineEdit_m3->text()+","
//                      +ui->lineEdit_m4->text()+","
//                      +ui->lineEdit_m5->text()+","
//                      +ui->lineEdit_m6->text()
//                      );

//    serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
    serialCommand(35,
                  Value,
                  ui->lineEdit_m2->text().toInt(),
                  ui->lineEdit_m3->text().toInt(),
                  ui->lineEdit_m4->text().toInt(),
                  ui->lineEdit_m5->text().toInt(),
                  ui->lineEdit_m6->text().toInt(),
                  ui->lineEdit_stepper->text().toInt());

    cout<<"M1_left_moving...: "<<Value<<endl;
}

void MainWindow::M1_moveRight_Timer()
{
    int Value = ui->lineEdit_m1->text().toInt();
    Value = Value-2;


    if(Value<-90) {
        cout<<"reached right limit!"<<endl;
        return;

    }

    ui->lineEdit_m1->setText(QString::number( Value, 10));
//    QString cmdstr = (QString::number( Value, 10)+","
//                      +ui->lineEdit_m2->text()+","
//                      +ui->lineEdit_m3->text()+","
//                      +ui->lineEdit_m4->text()+","
//                      +ui->lineEdit_m5->text()+","
//                      +ui->lineEdit_m6->text()
//                      );

//    serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
    serialCommand(35,
                  Value,
                  ui->lineEdit_m2->text().toInt(),
                  ui->lineEdit_m3->text().toInt(),
                  ui->lineEdit_m4->text().toInt(),
                  ui->lineEdit_m5->text().toInt(),
                  ui->lineEdit_m6->text().toInt(),
                  ui->lineEdit_stepper->text().toInt());

    cout<<"M1_right_moving...: "<<Value<<endl;

}

void MainWindow::on_M1Left_button_pressed()
{
    connect(timer,SIGNAL(timeout()),this,SLOT(M1_moveLeft_Timer()));
    timer->start(25);

}

void MainWindow::on_M1Left_button_released()
{

  timer->stop();
  disconnect(timer,SIGNAL(timeout()),this,SLOT(M1_moveLeft_Timer()));
  cout<<"moving left stop"<<endl;
}

void MainWindow::on_M1Right_button_pressed()
{
    connect(timer,SIGNAL(timeout()),this,SLOT(M1_moveRight_Timer()));
    timer->start(25);
}

void MainWindow::on_M1Right_button_released()
{
    timer->stop();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(M1_moveRight_Timer()));
    cout<<"moving right stop"<<endl;
}


void MainWindow::M2_moveLeft_Timer()
{
    int Value = ui->lineEdit_m2->text().toInt();
    Value = Value+2;


    if(Value>90) {
        cout<<"reached left limit!"<<endl;
        return;

    }

    ui->lineEdit_m2->setText(QString::number( Value, 10));
//    QString cmdstr = (ui->lineEdit_m1->text()+","
//                      +QString::number( Value, 10)+","
//                      +ui->lineEdit_m3->text()+","
//                      +ui->lineEdit_m4->text()+","
//                      +ui->lineEdit_m5->text()+","
//                      +ui->lineEdit_m6->text()
//                      );

//    serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
    serialCommand(35,
                  ui->lineEdit_m1->text().toInt(),
                  Value,
                  ui->lineEdit_m3->text().toInt(),
                  ui->lineEdit_m4->text().toInt(),
                  ui->lineEdit_m5->text().toInt(),
                  ui->lineEdit_m6->text().toInt(),
                  ui->lineEdit_stepper->text().toInt());

    cout<<"M2_left_moving...: "<<Value<<endl;
}

void MainWindow::M2_moveRight_Timer()
{
    int Value = ui->lineEdit_m2->text().toInt();
    Value = Value-2;


    if(Value<-90) {
        cout<<"reached right limit!"<<endl;
        return;

    }

    ui->lineEdit_m2->setText(QString::number( Value, 10));
//    QString cmdstr = (ui->lineEdit_m1->text()+","
//                      +QString::number( Value, 10)+","
//                      +ui->lineEdit_m3->text()+","
//                      +ui->lineEdit_m4->text()+","
//                      +ui->lineEdit_m5->text()+","
//                      +ui->lineEdit_m6->text()
//                      );

//    serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
    serialCommand(35,
                  ui->lineEdit_m1->text().toInt(),
                  Value,
                  ui->lineEdit_m3->text().toInt(),
                  ui->lineEdit_m4->text().toInt(),
                  ui->lineEdit_m5->text().toInt(),
                  ui->lineEdit_m6->text().toInt(),
                  ui->lineEdit_stepper->text().toInt());

    cout<<"M2_right_moving...: "<<Value<<endl;

}

void MainWindow::on_M2Left_button_pressed()
{
    connect(timer,SIGNAL(timeout()),this,SLOT(M2_moveLeft_Timer()));
    timer->start(100);

}

void MainWindow::on_M2Left_button_released()
{

  timer->stop();
  disconnect(timer,SIGNAL(timeout()),this,SLOT(M2_moveLeft_Timer()));
  cout<<"moving left stop"<<endl;
}

void MainWindow::on_M2Right_button_pressed()
{
    connect(timer,SIGNAL(timeout()),this,SLOT(M2_moveRight_Timer()));
    timer->start(100);
}

void MainWindow::on_M2Right_button_released()
{
    timer->stop();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(M2_moveRight_Timer()));
    cout<<"moving right stop"<<endl;
}


void MainWindow::M3_moveLeft_Timer()
{
    int Value = ui->lineEdit_m3->text().toInt();
    Value = Value+2;


    if(Value>90) {
        cout<<"reached left limit!"<<endl;
        return;

    }

    ui->lineEdit_m3->setText(QString::number( Value, 10));
//    QString cmdstr = ( ui->lineEdit_m1->text()+","
//                      +ui->lineEdit_m2->text()+","
//                      +QString::number( Value, 10)+","
//                      +ui->lineEdit_m4->text()+","
//                      +ui->lineEdit_m5->text()+","
//                      +ui->lineEdit_m6->text()
//                      );

//    serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
    serialCommand(35,
                  ui->lineEdit_m1->text().toInt(),
                  ui->lineEdit_m2->text().toInt(),
                  Value,
                  ui->lineEdit_m4->text().toInt(),
                  ui->lineEdit_m5->text().toInt(),
                  ui->lineEdit_m6->text().toInt(),
                  ui->lineEdit_stepper->text().toInt());

    cout<<"M3_left_moving...: "<<Value<<endl;
}

void MainWindow::M3_moveRight_Timer()
{
    int Value = ui->lineEdit_m3->text().toInt();
    Value = Value-2;


    if(Value<-90) {
        cout<<"reached right limit!"<<endl;
        return;

    }

    ui->lineEdit_m3->setText(QString::number( Value, 10));
//    QString cmdstr = ( ui->lineEdit_m1->text()+","
//                      +ui->lineEdit_m2->text()+","
//                      +QString::number( Value, 10)+","
//                      +ui->lineEdit_m4->text()+","
//                      +ui->lineEdit_m5->text()+","
//                      +ui->lineEdit_m6->text()
//                      );

//    serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
    serialCommand(35,
                  ui->lineEdit_m1->text().toInt(),
                  ui->lineEdit_m2->text().toInt(),
                  Value,
                  ui->lineEdit_m4->text().toInt(),
                  ui->lineEdit_m5->text().toInt(),
                  ui->lineEdit_m6->text().toInt(),
                  ui->lineEdit_stepper->text().toInt());

    cout<<"M3_right_moving...: "<<Value<<endl;

}

void MainWindow::on_M3Left_button_pressed()
{
    connect(timer,SIGNAL(timeout()),this,SLOT(M3_moveLeft_Timer()));
    timer->start(25);
}

void MainWindow::on_M3Left_button_released()
{

  timer->stop();
  disconnect(timer,SIGNAL(timeout()),this,SLOT(M3_moveLeft_Timer()));
  cout<<"moving left stop"<<endl;
}

void MainWindow::on_M3Right_button_pressed()
{
    connect(timer,SIGNAL(timeout()),this,SLOT(M3_moveRight_Timer()));
    timer->start(25);
}

void MainWindow::on_M3Right_button_released()
{
    timer->stop();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(M3_moveRight_Timer()));
    cout<<"moving right stop"<<endl;
}


void MainWindow::M4_moveLeft_Timer()
{
    int Value = ui->lineEdit_m4->text().toInt();
    Value = Value+2;


    if(Value>90) {
        cout<<"reached left limit!"<<endl;
        return;

    }

    ui->lineEdit_m4->setText(QString::number( Value, 10));
//    QString cmdstr = ( ui->lineEdit_m1->text()+","
//                      +ui->lineEdit_m2->text()+","
//                      +ui->lineEdit_m3->text()+","
//                      +QString::number( Value, 10)+","
//                      +ui->lineEdit_m5->text()+","
//                      +ui->lineEdit_m6->text()
//                      );

//    serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
    serialCommand(35,
                  ui->lineEdit_m1->text().toInt(),
                  ui->lineEdit_m2->text().toInt(),
                  ui->lineEdit_m3->text().toInt(),
                  Value,
                  ui->lineEdit_m5->text().toInt(),
                  ui->lineEdit_m6->text().toInt(),
                  ui->lineEdit_stepper->text().toInt());

    cout<<"M4_left_moving...: "<<Value<<endl;
}

void MainWindow::M4_moveRight_Timer()
{
    int Value = ui->lineEdit_m4->text().toInt();
    Value = Value-2;


    if(Value<-90) {
        cout<<"reached right limit!"<<endl;
        return;

    }

    ui->lineEdit_m4->setText(QString::number( Value, 10));
//    QString cmdstr = ( ui->lineEdit_m1->text()+","
//                      +ui->lineEdit_m2->text()+","
//                      +ui->lineEdit_m3->text()+","
//                      +QString::number( Value, 10)+","
//                      +ui->lineEdit_m5->text()+","
//                      +ui->lineEdit_m6->text()
//                      );


//    serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
    serialCommand(35,
                  ui->lineEdit_m1->text().toInt(),
                  ui->lineEdit_m2->text().toInt(),
                  ui->lineEdit_m3->text().toInt(),
                  Value,
                  ui->lineEdit_m5->text().toInt(),
                  ui->lineEdit_m6->text().toInt(),
                  ui->lineEdit_stepper->text().toInt());

    cout<<"M4_right_moving...: "<<Value<<endl;

}

void MainWindow::on_M4Left_button_pressed()
{
    connect(timer,SIGNAL(timeout()),this,SLOT(M4_moveLeft_Timer()));
    timer->start(25);

}

void MainWindow::on_M4Left_button_released()
{

  timer->stop();
  disconnect(timer,SIGNAL(timeout()),this,SLOT(M4_moveLeft_Timer()));
  cout<<"moving left stop"<<endl;
}

void MainWindow::on_M4Right_button_pressed()
{
    connect(timer,SIGNAL(timeout()),this,SLOT(M4_moveRight_Timer()));
    timer->start(25);
}

void MainWindow::on_M4Right_button_released()
{
    timer->stop();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(M4_moveRight_Timer()));
    cout<<"moving right stop"<<endl;
}


void MainWindow::M5_moveLeft_Timer()
{
    int Value = ui->lineEdit_m5->text().toInt();
    Value = Value+2;


    if(Value>90) {
        cout<<"reached left limit!"<<endl;
        return;

    }

    ui->lineEdit_m5->setText(QString::number( Value, 10));
//    QString cmdstr = ( ui->lineEdit_m1->text()+","
//                      +ui->lineEdit_m2->text()+","
//                      +ui->lineEdit_m3->text()+","
//                      +ui->lineEdit_m4->text()+","
//                      +QString::number( Value, 10)+","
//                      +ui->lineEdit_m6->text()
//                      );

//    serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
    serialCommand(35,
                  ui->lineEdit_m1->text().toInt(),
                  ui->lineEdit_m2->text().toInt(),
                  ui->lineEdit_m3->text().toInt(),
                  ui->lineEdit_m4->text().toInt(),
                  Value,
                  ui->lineEdit_m6->text().toInt(),
                  ui->lineEdit_stepper->text().toInt());

    cout<<"M5_left_moving...: "<<Value<<endl;
}

void MainWindow::M5_moveRight_Timer()
{
    int Value = ui->lineEdit_m5->text().toInt();
    Value = Value-2;


    if(Value<-90) {
        cout<<"reached right limit!"<<endl;
        return;

    }

    ui->lineEdit_m5->setText(QString::number( Value, 10));
//    QString cmdstr = ( ui->lineEdit_m1->text()+","
//                      +ui->lineEdit_m2->text()+","
//                      +ui->lineEdit_m3->text()+","
//                      +ui->lineEdit_m4->text()+","
//                      +QString::number( Value, 10)+","
//                      +ui->lineEdit_m6->text()
//                      );

//    serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
    serialCommand(35,
                  ui->lineEdit_m1->text().toInt(),
                  ui->lineEdit_m2->text().toInt(),
                  ui->lineEdit_m3->text().toInt(),
                  ui->lineEdit_m4->text().toInt(),
                  Value,
                  ui->lineEdit_m6->text().toInt(),
                  ui->lineEdit_stepper->text().toInt());

    cout<<"M5_right_moving...: "<<Value<<endl;

}

void MainWindow::on_M5Left_button_pressed()
{
    connect(timer,SIGNAL(timeout()),this,SLOT(M5_moveLeft_Timer()));
    timer->start(25);

}

void MainWindow::on_M5Left_button_released()
{

  timer->stop();
  disconnect(timer,SIGNAL(timeout()),this,SLOT(M5_moveLeft_Timer()));
  cout<<"moving left stop"<<endl;
}

void MainWindow::on_M5Right_button_pressed()
{
    connect(timer,SIGNAL(timeout()),this,SLOT(M5_moveRight_Timer()));
    timer->start(25);
}

void MainWindow::on_M5Right_button_released()
{
    timer->stop();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(M5_moveRight_Timer()));
    cout<<"moving right stop"<<endl;
}



void MainWindow::on_M6_ON_button_clicked()
{



//    QString cmdstr = (ui->lineEdit_m1->text()+","
//                      +ui->lineEdit_m2->text()+","
//                      +ui->lineEdit_m3->text()+","
//                      +ui->lineEdit_m4->text()+","
//                      +ui->lineEdit_m5->text()+","
//                      +"1"
//                      );

//    serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
    serialCommand(35,
                  ui->lineEdit_m1->text().toInt(),
                  ui->lineEdit_m2->text().toInt(),
                  ui->lineEdit_m3->text().toInt(),
                  ui->lineEdit_m4->text().toInt(),
                  ui->lineEdit_m5->text().toInt(),
                  1,
                  ui->lineEdit_stepper->text().toInt());


    ui->lineEdit_m6->setText("1");
    ui->M6_ON_button->setEnabled(false);
    ui->M6_OFF_button->setEnabled(true);

}

void MainWindow::on_M6_OFF_button_clicked()
{

//    QString cmdstr = (ui->lineEdit_m1->text()+","
//                      +ui->lineEdit_m2->text()+","
//                      +ui->lineEdit_m3->text()+","
//                      +ui->lineEdit_m4->text()+","
//                      +ui->lineEdit_m5->text()+","
//                      +"0"
//                      );

//    serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
    serialCommand(35,
                  ui->lineEdit_m1->text().toInt(),
                  ui->lineEdit_m2->text().toInt(),
                  ui->lineEdit_m3->text().toInt(),
                  ui->lineEdit_m4->text().toInt(),
                  ui->lineEdit_m5->text().toInt(),
                  0,
                  ui->lineEdit_stepper->text().toInt());

    ui->lineEdit_m6->setText("0");
    ui->M6_OFF_button->setEnabled(false);
    ui->M6_ON_button->setEnabled(true);
}

void MainWindow::on_visionServo_open_button_clicked()
{
    cout<<"vision start!"<<endl;
    visionThread->stop= false;
     visionThread->tissuebagDetectflag = true;
    visionThread->start();


}

void MainWindow::on_visionServo_close_button_clicked()
{

    cout<<"vision stop!"<<endl;
    visionThread->stop=true;
    visionThread->pointSet.clear();
    visionThread->pointSetPredict.clear();

}

void MainWindow::on_ResetRobot_button_clicked()
{

//    QString cmdstr = "reset";
//    serial.write((cmdstr+"\n").toLatin1());
//    ui->textEdit->append("sent: "+cmdstr);
    serialCommand(37,0,38,-90,-90,0,1,0);
    ui->lineEdit_m1->setText("0");
    ui->lineEdit_m2->setText("38");
    ui->lineEdit_m3->setText("-90");
    ui->lineEdit_m4->setText("-90");
    ui->lineEdit_m5->setText("0");
    ui->lineEdit_m6->setText("1");


}

void MainWindow::serialCommand(int n, int theta1, int theta2, int theta3, int theta4, int theta5, int theta6, int stepper)
{
//    QString controlValue1=tr("%1").arg(theta1), controlValue2=tr("%1").arg(theta2), controlValue3=tr("%1").arg(theta3),
//            controlValue4=tr("%1").arg(theta4), controlValue5=tr("%1").arg(theta5), controlValue6=tr("%1").arg(theta6),
//            controlStepper=tr("%1").arg(stepper);
//    QString cmd = ( controlValue1+ "," +
//                    controlValue2+ "," +
//                    controlValue3+ "," +
//                    controlValue4+ "," +
//                    controlValue5+ "," +
//                    controlValue6+ "," +
//                    controlStepper+"\n");
//    serial.write(cmd.toLatin1());
    unsigned char controlValue1 = (unsigned char) (theta1+100);
    unsigned char controlValue2 = (unsigned char) (theta2+100);
    unsigned char controlValue3 = (unsigned char) (theta3+100);
    unsigned char controlValue4 = (unsigned char) (theta4+100);
    unsigned char controlValue5 = (unsigned char) (theta5+100);
    unsigned char controlValue6 = (unsigned char) (theta6+100);
    unsigned char controlStepper = (unsigned char) (stepper+100);
    QString cmd = QString((unsigned char)126) +QString((unsigned char)n) + QString(controlValue1) + QString(controlValue2) + QString(controlValue3) +
            QString(controlValue4) + QString(controlValue5) + QString(controlValue6) + QString(controlStepper) + QString((unsigned char)125);
    serial.write(cmd.toLatin1());



}



