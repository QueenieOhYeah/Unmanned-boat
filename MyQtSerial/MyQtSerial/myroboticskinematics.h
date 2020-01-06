#ifndef MYROBOTICSKINEMATICS_H
#define MYROBOTICSKINEMATICS_H


#include <iostream>
#include <vector>
#include <QDebug>
#include <math.h>
using namespace std;


class MyRoboticsKinematics
{
public:
    MyRoboticsKinematics();
   int MyinverseKinematics(vector<double> &dstPos, vector<vector<double> > &resultM);
   int MyforwardKinematics(vector<double>&m, vector<double> &result);

};

#endif // MYROBOTICSKINEMATICS_H
