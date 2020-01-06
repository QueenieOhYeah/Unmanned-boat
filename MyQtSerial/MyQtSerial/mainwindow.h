#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "myroboticskinematics.h"
#include "VisionServoThread.h"

#include <QSerialPort>
#include <QMainWindow>
#include<QDebug>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "sys/wait.h"
#include <QTimer>
#include "opencv.hpp"
using namespace cv;
using namespace std;



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    double dev_y;

private:
    Ui::MainWindow *ui;
    QSerialPort serial;
    QTimer *timer;
    MyRoboticsKinematics RL;              //Robotics functions
    VisionServoThread *visionThread;      //Thread and image processing part

    //global variables
    vector <double>m_lasttime;
    vector <int> global_initialValue;
    vector<vector<double> > CurrentResultM;
    bool M1_leftMove_flag;
    int CurrentResultStepper;


    void rectifyMotorValue( vector<vector<double> > &MyCurrentResultM,vector<vector<double> > &CurrentResultM_Rectified);
    void DataRectifyConvert(double &data_in,double &data_converted);



private slots:


 //---SERIAL CONTROL PART---//
       //for serial receive
     void serialReceived();

     void on_Connect_serial_button_clicked();
     void on_disconnect_serial_button_clicked();
     void on_send_button_clicked();

//---JOINT CONTROL PART---//
     void on_send_CMD_button_clicked();
     void on_fk_calculation_button_clicked();

    //M1 control
    void M1_moveLeft_Timer();
    void M1_moveRight_Timer();
    void on_M1Left_button_pressed();
    void on_M1Left_button_released();
    void on_M1Right_button_pressed();
    void on_M1Right_button_released();

    //M2 control
    void M2_moveLeft_Timer();
    void M2_moveRight_Timer();
    void on_M2Left_button_pressed();
    void on_M2Left_button_released();
    void on_M2Right_button_pressed();
    void on_M2Right_button_released();

    //M3 control
    void M3_moveLeft_Timer();
    void M3_moveRight_Timer();
    void on_M3Left_button_pressed();
    void on_M3Left_button_released();
    void on_M3Right_button_pressed();
    void on_M3Right_button_released();

    //M4 control
    void M4_moveLeft_Timer();
    void M4_moveRight_Timer();
    void on_M4Left_button_pressed();
    void on_M4Left_button_released();
    void on_M4Right_button_pressed();
    void on_M4Right_button_released();

    //M5 control
    void M5_moveLeft_Timer();
    void M5_moveRight_Timer();
    void on_M5Left_button_pressed();
    void on_M5Left_button_released();
    void on_M5Right_button_pressed();
    void on_M5Right_button_released();

    void on_M6_ON_button_clicked();
    void on_M6_OFF_button_clicked();


//---END POINT CONTROL---//
    //void on_Test_clicked();
    void on_MyTestIK_button_clicked();
    void on_Run_button_clicked();

//---IMAGAE PROCESSING PART---//
    //motion control
    void moveMotor1(int Px,int Py,int Pz);
    void gripControl(int var); //0 open 1 close;
    void moveToP(int Px,int Py,int Pz);
    void stepperInitial();

    //image updating
    void updateFrame(Mat image);
    void updateCam2Frame(Mat image);

    void on_visionServo_open_button_clicked();
    void on_visionServo_close_button_clicked();
    void on_ResetRobot_button_clicked();

    void serialCommand(int n, int theta1, int theta2, int theta3, int theta4, int theta5, int theta6, int stepper);

};

#endif // MAINWINDOW_H
