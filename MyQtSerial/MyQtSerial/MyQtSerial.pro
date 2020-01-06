#-------------------------------------------------
#
# Project created by QtCreator 2017-06-16T19:07:49
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyQtSerial
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myroboticskinematics.cpp \
    VisionServoThread.cpp \
    mystereocam.cpp \
    ../../MyAstraViewer/MyAstraviewer/src/AstraIO.cpp \
    ../../MyAstraViewer/MyAstraviewer/src/Draw.cpp \
    ../../MyAstraViewer/MyAstraviewer/src/Key.cpp \
    ../../MyAstraViewer/MyAstraviewer/src/MyTinyAlgorithm.cpp \
    ../../MyAstraViewer/MyAstraviewer/src/PointCloud.cpp \
    ../../MyAstraViewer/MyAstraviewer/src/RGBDCamera.cpp \
    ../../MyAstraViewer/MyAstraviewer/src/SoftwareRegistrator.cpp \
    getframe.cpp

HEADERS  += mainwindow.h \
    myroboticskinematics.h \
    VisionServoThread.h \
    mystereocam.h \
    ../../MyAstraViewer/MyAstraviewer/include/AstraIO.h \
    ../../MyAstraViewer/MyAstraviewer/include/Config.h \
    ../../MyAstraViewer/MyAstraviewer/include/Draw.h \
    ../../MyAstraViewer/MyAstraviewer/include/File.h \
    ../../MyAstraViewer/MyAstraviewer/include/Key.h \
    ../../MyAstraViewer/MyAstraviewer/include/PointCloud.h \
    ../../MyAstraViewer/MyAstraviewer/include/RGBDCamera.h \
    ../../MyAstraViewer/MyAstraviewer/src/MyTinyAlgorithm.h \
    ../../MyAstraViewer/MyAstraviewer/src/SoftwareRegistrator.h \
    define.h \
    getframe.h

FORMS    += mainwindow.ui




INCLUDEPATH += /usr/include/opencv2 \
            /usr/include/openni2\
             /home/jack/OpenNI-Linux-x64-2.3/Include/ \
        /usr/include/eigen3 \
        /user/include/GL \
        /home/joule/Desktop/MyAstraViewer/MyAstraviewer/include \
        /home/joule/Desktop/MyAstraViewer/MyAstraviewer/src



    #/usr/include/openni2/ \



LIBS += /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so \
/usr/lib/x86_64-linux-gnu/libopencv_contrib.so \
/usr/lib/x86_64-linux-gnu/libopencv_core.so \
/usr/lib/x86_64-linux-gnu/libopencv_features2d.so \
/usr/lib/x86_64-linux-gnu/libopencv_flann.so \
/usr/lib/x86_64-linux-gnu/libopencv_gpu.so \
/usr/lib/x86_64-linux-gnu/libopencv_highgui.so \
/usr/lib/x86_64-linux-gnu/libopencv_imgproc.so \
/usr/lib/x86_64-linux-gnu/libopencv_legacy.so \
/usr/lib/x86_64-linux-gnu/libopencv_ml.so \
/usr/lib/x86_64-linux-gnu/libopencv_objdetect.so \
/usr/lib/x86_64-linux-gnu/libopencv_ocl.so \
/usr/lib/x86_64-linux-gnu/libopencv_photo.so \
/usr/lib/x86_64-linux-gnu/libopencv_stitching.so \
/usr/lib/x86_64-linux-gnu/libopencv_superres.so \
/usr/lib/x86_64-linux-gnu/libopencv_ts.so \
/usr/lib/x86_64-linux-gnu/libopencv_video.so \
/usr/lib/x86_64-linux-gnu/libopencv_videostab.so


#lib files
LIBS += /home/joule/OpenNI-Linux-x64-2.3/Redist/libOpenNI2.so \
         /usr/lib/x86_64-linux-gnu/libglut.so.3 \
         /usr/lib/x86_64-linux-gnu/mesa/libGL.so.1 \

