#ifndef INTERFACE_H
#define INTERFACE_H


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/dnn/layer.details.hpp>

#include <QFrame>


using namespace cv;
using namespace  std;

namespace Ui {
class Interface;
}

class Interface : public QFrame
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface();

    cv::Mat rotacion(cv::Mat &img, double grados);


private slots:
    void on_pBtnStart_clicked();

private:
    Ui::Interface *ui;
};

#endif // INTERFACE_H
