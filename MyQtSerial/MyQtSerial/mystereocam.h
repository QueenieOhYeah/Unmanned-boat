#ifndef MYSTEREOCAM_H
#define MYSTEREOCAM_H


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



class MyStereoCam
{
public:
    MyStereoCam();
    void grab_image_and_depth(Mat &image,Mat &depth); //just grab the image and calibrated depth
    void get_point3(); // from color to pnt3


};

#endif // MYSTEREOCAM_H
