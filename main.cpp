#include "interface.h"
#include <QApplication>

#include <QCoreApplication>
#include <QtDebug>
#include <QThread>

#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/dnn/layer.details.hpp>


using namespace cv;
using namespace  std;



int main(int argc, char *argv[])
{

     QApplication a(argc, argv);
     Interface w;


//    return 0;


    w.show();

    return a.exec();

}
