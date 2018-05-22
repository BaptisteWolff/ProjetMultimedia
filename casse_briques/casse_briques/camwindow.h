#ifndef CAMWINDOW_H
#define CAMWINDOW_H

#include <QMainWindow>
#include "opencv2/opencv.hpp"
using namespace cv;
namespace Ui {
class CamWindow;
}

class CamWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CamWindow(QWidget *parent = 0);
    ~CamWindow();
    void webcamCapture(Mat image);
private:
    Ui::CamWindow *ui;
};

#endif // CAMWINDOW_H
