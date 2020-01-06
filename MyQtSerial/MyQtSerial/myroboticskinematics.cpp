#include "myroboticskinematics.h"

MyRoboticsKinematics::MyRoboticsKinematics()
{




}



int MyRoboticsKinematics::MyinverseKinematics(vector<double> &dstPos, vector<vector<double> > &resultM)
{

        double pi=3.14159265;
        double xxx =dstPos[0];
        double yyy = dstPos[1];
        double zzz = dstPos[2];
        //cout<<"xxx-zzz:"<<xxx<<","<<yyy<<","<<zzz<<endl;

        double theta0 =atan2(-1*xxx,yyy);
        //cout<<"theta0: "<<theta0/pi*180<<endl;

        double zz = zzz;
        double yy = sqrt(xxx*xxx+yyy*yyy);

    //system parameters
        double l1=124.0;
        double l2=124.0;
        double l3=60.0+135.0;
        double l4 =72.0;

        zz=zz-l4;

    //outputs
    vector <double> q0;   //(-pi/2,pi/2)
    vector <double> q1;   //(-pi/2,pi/2)
    vector <double> q2;   //(-pi/2,pi/2)
    vector <double> q3;   //(-pi/2,pi/2)
    vector <double> q4;   //(-pi/2,pi/2)

    //initial calculation
    int interval = 5;// calculate every 5 intervals

    for (int i=-90;i<90;i=i+interval) {

    double phiphi =  i/180.0 *pi;

    double x= yy-l3*cos(phiphi);
    double y = zz - l3*sin(phiphi);
    double phi = phiphi;

    double c2 = (x*x+y*y-l1*l1-l2*l2)/(2*l1*l2);

    if(c2>0 && c2<1) { // to make sure  -90<theta2<90

        //condition1
        double s2 = sqrt(1-c2*c2);
        double theta2 = atan2(s2,c2);
        double k1=l1+l2*c2;
        double k2=l2*s2;
        double theta1 = (atan2(y,x)-atan2(k2,k1));
        double theta3 = phi - theta1- theta2;

        if((theta1<(165.0/180.0*pi)) && (theta1>(15.0/180.0*pi))) {//  to make sure  15<theta1<165
                if(theta3>-1*pi/2 && theta3<pi/2){ // to make sure <-90theta3<90
                      q0.push_back(theta0);
                      q1.push_back(theta1);
                      q2.push_back(theta2);
                      q3.push_back(theta3);
                      q4.push_back(phiphi);
                }
        }

        //condition2
        s2 = -1*sqrt(1-c2*c2);
        theta2 = atan2(s2,c2);
        k1=l1+l2*c2;
        k2=l2*s2;
        theta1 = (atan2(y,x)-atan2(k2,k1));
        theta3 = phi - theta1- theta2;
        if((theta1<(165.0/180.0*pi)) && (theta1>(15.0/180.0*pi))) {//  to make sure  15<theta1<165
                if(theta3>-1*pi/2 && theta3<pi/2){ // to make sure <-90theta3<90
                      q0.push_back(theta0);
                      q1.push_back(theta1);
                      q2.push_back(theta2);
                      q3.push_back(theta3);
                      q4.push_back(phiphi);
                }
        }

    }

    }


if(q1.size()==0) {
    cout<<"No result."<<endl;
    return -1;
}

for (int i=0;i<q1.size();i++){
       double t_theta1 = q1[i];
       double t_theta2 = q2[i];
       double t_theta3 = q3[i];


       double tx = l1*cos(t_theta1)+l2*cos(t_theta1+t_theta2)+l3*cos(t_theta1+t_theta2+t_theta3);
       double ty = l1*sin(t_theta1)+l2*sin(t_theta1+t_theta2)+l3*sin(t_theta1+t_theta2+t_theta3);

       double valRadtToDegree = 180/pi;


      vector <double>tmp;
      tmp.push_back(q0[i]*valRadtToDegree);
      tmp.push_back(q1[i]*valRadtToDegree-90);
      tmp.push_back(q2[i]*valRadtToDegree);
      tmp.push_back(q3[i]*valRadtToDegree);
      tmp.push_back(q4[i]*valRadtToDegree);

      resultM.push_back(tmp);
       //cout<<i<<" q0-3:"<<q1[i]*valRadtToDegree<<","<<q1[i]*valRadtToDegree-90<<","<<q2[i]*valRadtToDegree<<","<<q3[i]*valRadtToDegree<<","<<q4[i]*valRadtToDegree<<","
       //   <<q4[i]*valRadtToDegree<<"x:"<<tx<<",y:"<<ty+l4<<endl;
    }


   // cout<<"End ik!"<<endl;
return 0;
}

int MyRoboticsKinematics::MyforwardKinematics(vector<double> &m, vector<double> &result)
{
    cout<<"hello"<<endl;
    double l1=72.0;
    double l2=124.0;
    double l3 = 124;
    double l4=60.0+135.0;
    double mPI = 3.1415926;

    double A= mPI/2 + m[1];
    double B= mPI/2 + m[1]+m[2];
    double C= mPI/2 + m[1]+m[2]+m[3];
    double xx = l2*cos(A)+l3*cos(B)+l4*cos(C);
    double yy = l2*sin(A)+l3*sin(B)+l4*sin(C);
    double x = -1*xx*sin(m[0]);
    double y = xx*cos(m[0]);
    double z = yy+l1;
   result.push_back(x);
   result.push_back(y);
   result.push_back(z);

    cout<<x<<","<<y<<","<<z<<endl;
    return 0;

}















