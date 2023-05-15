QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp


OPENCV_HOME = /usr/local/
INCLUDEPATH += $${OPENCV_HOME}/include
DEPENDPATH += $${OPENCV_HOME}/include
LIBS += -L$${OPENCV_HOME}/lib -lopencv_world

#OPENCV_HOME = /usr/local/
#INCLUDEPATH += $${OPENCV_HOME}/include/opencv4/opencv2
#DEPENDPATH += $${OPENCV_HOME}/include/opencv4/opencv2
#LIBS += -L$${OPENCV_HOME}/lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -lopencv_calib3d
