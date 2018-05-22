#include "camwindow.h"
#include "ui_camwindow.h"

CamWindow::CamWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CamWindow)
{
    ui->setupUi(this);
}

CamWindow::~CamWindow()
{
    delete ui;
}
void CamWindow::webcamCapture(Mat image)
{
            // Invert Blue and Red color channels
            cvtColor(image,image,CV_BGR2RGB);
            // Convert to Qt image
            QImage img= QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);
            // Display on label
            ui->label_webcam->setPixmap(QPixmap::fromImage(img));
            // Resize the label to fit the image
            ui->label_webcam->resize(ui->label_webcam->pixmap()->size());
}
