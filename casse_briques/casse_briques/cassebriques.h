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
    Ball ball1 = Ball(0,1,20/fps,0,-1);
    Ball ball2 = Ball(3,1,20/fps,0,-1);
    Ball ball3 = Ball(-3,1,20/fps,0,-1);
    Wall upperWall;
    Wall rightWall;
    Wall leftWall;
    Wall lowerWall;
    Ball updateBall(Ball ball);
    BrickMap* mBricks = new BrickMap();
    QTimer *timer;
private slots:
    void timeUpdate();
};

#endif // MYGLWIDGET_H
