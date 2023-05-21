#include "interface.h"
#include "ui_interface.h"

#include <QApplication>
#include <QCoreApplication>
#include <QtDebug>


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/dnn/layer.details.hpp>

#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <stdio.h>

using namespace cv;
using namespace std;

Interface::Interface(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);

    QStringList vs = {"png", "jpg", "jpeg", "bmp"};
    std::vector<std::string> v = {"png", "jpg", "jpeg", "bmp"};
//    for (int i=0; i<vs.size(); i++)
//    {
        ui->lWidgetIn->addItems(vs);
        ui->lWidgetOut->addItems(vs);

//    }
}

Interface::~Interface()
{
    delete ui;
}


Mat Interface::rotacion(cv::Mat &img, double grados)
{
    double offsetX, offsetY;
    double angle = -45;
    double width = img.size().width;
    double height = img.size().height;
    Point2d center = Point2d (width / 2, height / 2);
    Rect bounds = RotatedRect (center, img.size(), angle).boundingRect();
    Mat resized = Mat::zeros (bounds.size(), img.type());
    offsetX = (bounds.width - width) / 2;
    offsetY = (bounds.height - height) / 2;
    Rect roi = Rect (offsetX, offsetY, width, height);
    img.copyTo (resized (roi));
    center += Point2d (offsetX, offsetY);

    //    Point2f src_center((img.cols-1)/2.0F, (img.rows-1)/2.0F);
    //    Mat rot_matrix = getRotationMatrix2D(src_center, grados, 1.0);
    Mat rot_matrix = getRotationMatrix2D(center, grados, 1.0);
    //    Mat rotated_img(Size(img.size().height, img.size().width), img.type());
    Mat rotated_img;
    //    warpAffine(img, rotated_img, rot_matrix, img.size());
    warpAffine(img, rotated_img, rot_matrix, resized.size());
    //    imwrite("rotated.jpg", rotated_img);
    return rotated_img;
}

void Interface::on_pBtnStart_clicked()
{

    //    int nimgs=461;
    int nimgs=ui->lEdTotalImgs->text().toInt();
    int counterImages=1; //contador de imagenes
    stringstream oldImgs, newImgs, rotatedImgs;

    Mat imgLeer, imgLeerMod, imgEscribir;
    namedWindow("image",WINDOW_AUTOSIZE);
    //    string direccion = "/home/glintec/Documents/programs/QtQML/ajustImage/images/piezaPrint";
    //    string direccionMod = "/home/glintec/Documents/programs/QtQML/ajustImage/images/piezaPrint_";
    string direccion = "/home/glintec/Documents/programs/QtQML/ajustImage/images/pi_";
    //        string direccionMod = "/home/glintec/Documents/programs/QtQML/ajustImage/images/piezaImpresa_";
    //    string direccionMod = "/media/glintec/o_0/IMAGENES/pi_";
    string direccionMod = "/home/glintec/Videos/obj/pi_";

    string direccionGiro = "/home/glintec/Videos/obj/piGiro_";

    for(int i=1; i <= nimgs; i++)
    {
        counterImages++;
        oldImgs << direccion << i << ".jpg";
        newImgs << direccionMod << counterImages << ".png";

        //        qDebug()<<oldImgs.str().c_str()<<endl;
        //        imgLeer=imread(Saveimgs.str().c_str(),IMREAD_COLOR);
        imgLeer=imread(oldImgs.str(),IMREAD_COLOR);
        //        resize(imgLeer, imgLeerMod, Size(imgLeer.cols * 1.0,imgLeer.rows * 1.0), 0, 0, CV_INTER_LINEAR);
        cv::resize(imgLeer, imgLeerMod, Size(640,480), 0, 0, CV_INTER_LINEAR);
        imgEscribir=imwrite(newImgs.str(),imgLeerMod);
        oldImgs = std::stringstream();
        newImgs = std::stringstream();
        if (imgLeer.empty()) {
            cout << "Image File Not Found" << endl;
            break;
        }

        //Decide to rotate image
        if(false){
            for(int i=0; i<=270; i+=10)
            {
                counterImages++;
                Mat imgRotada;
                rotatedImgs << direccionGiro<< counterImages << ".png";
                imgRotada=rotacion(imgLeerMod, (double)i);
                //            resize(imgRotada, imgRotada, Size(imgRotada.cols * 0.7,imgRotada.rows * 0.7), 0, 0, CV_INTER_LINEAR);
                imgEscribir=imwrite(rotatedImgs.str(), imgRotada);
                rotatedImgs = std::stringstream();
                cout << i<< endl;
            }

        }

        //Define the % for the processing images
        float porcentaje = (float)((i*100)/nimgs);
        cout << "% --> " << porcentaje << endl;

        ui->progressBar->setValue(porcentaje);


//        QImage imLabel((uchar*)imgLeerMod.data, imgLeerMod.cols,
//                    imgLeerMod.rows, QImage::Format_RGB888);

        QImage imLabel = QImage((const unsigned char*)(imgLeerMod.data),imgLeerMod.cols,
                                imgLeerMod.rows,QImage::Format_RGB888);

        ui->lImagen->setPixmap(QPixmap::fromImage(imLabel));
        ui->lImagen->resize(ui->lImagen->pixmap()->size());

//        imshow("image", imgLeerMod);
        qDebug()<<"!Imagen !"<<i<<endl;


        waitKey(10);
        //        QThread::msleep(200);

    }
}
