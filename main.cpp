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

int main()
{

    int nimgs=14;
    stringstream oldImgs, newImgs;

    Mat imgLeer, imgLeerMod, imgEscribir;
    namedWindow("image",WINDOW_AUTOSIZE);
    string direccion = "/home/glintec/Documents/repoProg/Qt/AdjustImage/AdjustImage/images/pieza_";

    for(int i=1; i <= nimgs; i++){

        oldImgs << direccion << i << ".jpg";
        newImgs << direccion << i << ".png";
//        qDebug()<<oldImgs.str().c_str()<<endl;
//        imgLeer=imread(Saveimgs.str().c_str(),IMREAD_COLOR);
        imgLeer=imread(oldImgs.str(),IMREAD_COLOR);
//        resize(imgLeer, imgLeerMod, Size(imgLeer.cols * 0.70,imgLeer.rows * 0.70), 0, 0, CV_INTER_LINEAR);
        resize(imgLeer, imgLeerMod, Size(640,480), 0, 0, CV_INTER_LINEAR);
        imgEscribir=imwrite(newImgs.str(),imgLeerMod);
        oldImgs = std::stringstream();
        newImgs = std::stringstream();
        if (imgLeer.empty()) {
           cout << "Image File Not Found" << endl;
           break;
         }
        imshow("image", imgLeerMod);
        qDebug()<<"!Imagen !"<<i<<endl;


        waitKey(70);
//        QThread::msleep(200);

    }
    return 0;
}
