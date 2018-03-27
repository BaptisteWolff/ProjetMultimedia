#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "opencv2/opencv.hpp"
#include <iostream>
#include <QTimer>

#include"detectmotion.h"

using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    VideoCapture * webCam_;
    QTimer *timerWebcam;
    DetectMotion detectMotion;
    bool isFirstFrame = true;

private slots:
    void webcamCapture();
};

#endif // MAINWINDOW_H
