#ifndef GETFRAME
#define GETFRAME
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


class getframe: public QThread
{
    Q_OBJECT
public:
};
#endif // GETFRAME

