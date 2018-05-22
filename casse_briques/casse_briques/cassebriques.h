#ifndef CASSEBRIQUES_H
#define CASSEBRIQUES_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QColor>
#include <QVector2D>
#include <QScreen>
#include <QDebug>
#include "palet.h"
#include "brick.h"
#include "brickmap.h"
#include "ball.h"
#include "QTimer"
#include "wall.h"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <QTimer>
#include<QFont>

#include"detectmotion.h"

using namespace cv;
using namespace std;
// Classe dediee a l'affichage d'une scene OpenGL
class CasseBriques : public QGLWidget
{
    Q_OBJECT

public:

    // Constructeur
    CasseBriques(QWidget * parent = nullptr);

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent * event);

private:
    float fps = 60;
    Palet palet;
    GLfloat xPalet = 0; // Position du palet
    Ball ball = Ball(0,1,20/fps,0,-1);

    Wall upperWall;
    Wall rightWall;
    Wall leftWall;
    Wall lowerWall;

    void updateBall();
    BrickMap* mBricks = new BrickMap();
    QTimer *timer;
    VideoCapture * webCam_;
    QTimer *timerWebcam;
    DetectMotion detectMotion;
    bool isFirstFrame = true;
    bool cam = false;

    bool initBall = true;
    void setInitBall();
    void updateInit();

    bool isPlaying = false;

    /* 0 : reprendre partie
     * 1 : nouvelle partie
     * 2 : afficher scores
     * 3 : choisir niveau
     * */
    int optionSelected = 0;

    QFont font;
private slots:
    void webcamCapture();
    void timeUpdate();
};


#endif // MYGLWIDGET_H
