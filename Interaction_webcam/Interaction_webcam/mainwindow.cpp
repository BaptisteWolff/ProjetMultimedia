#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Webcam setup
    webCam_=new VideoCapture(0);
    int width=webCam_->get(CV_CAP_PROP_FRAME_WIDTH);
    int height=webCam_->get(CV_CAP_PROP_FRAME_HEIGHT);

    if(!webCam_->isOpened())  // check if we succeeded
    {
        ui->label_infoWebcam->setText("Error openning the default camera !");
    }
    else
    {
        ui->label_infoWebcam->setText(QString("Video ok, image size is %1x%2 pixels").arg(width).arg(height));
    }

    // Timer webcam
    float fps = 30;
    timerWebcam = new QTimer(this);
    timerWebcam->setInterval((int)(1000/fps));
    connect(timerWebcam, SIGNAL(timeout()) , this, SLOT(webcamCapture()));
    timerWebcam->start();

    // Detect motion
    detectMotion = DetectMotion(width, height);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete webCam_;
}

void MainWindow::webcamCapture()
{
    if (webCam_->isOpened()) {
        Mat image;
        if (webCam_->read(image))
        {   // Capture a frame

            if (isFirstFrame)
            {
                detectMotion.setFirstFrame(image);
                isFirstFrame = false;
            }
            // Detect motion
            detectMotion.detect(image);
            //image = detectMotion.getFrame();

            /*// Flip to get a mirror effect
            flip(image,image,1);*/
            // Invert Blue and Red color channels
            cvtColor(image,image,CV_BGR2RGB);

            // Convert to Qt image
            QImage img= QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);
            // Display on label
            ui->label_webcam->setPixmap(QPixmap::fromImage(img));
            // Resize the label to fit the image
            ui->label_webcam->resize(ui->label_webcam->pixmap()->size());
            // Sphere translation
            Point vect = detectMotion.getVect();
            if (vect.x > 5 || vect.y > 5 || vect.y<-5 || vect.x<-5)
            {
                ui->openGl->translateSphere(vect.x, vect.y, 0);
            }
        }
        else
        {
            ui->label_infoWebcam->setText("Error capturing the frame");
        }

    }
}

