#include "balle.h"
#include "QImage.h"
#include <QGLWidget>
#include <QFile>

// Constructeur :
balle::balle(float x, float y, float z, int speed, float xdirection, float ydirection)
{
    x_ = x;
    y_ = y;
    z_ = z;
    speed_ = speed;
    xdirection_ = xdirection;
    ydirection_ = ydirection;
}
balle::balle(float x, float y, int speed, float xdirection, float ydirection)
{
    x_ = x;
    y_ = y;
    z_ = z;
    speed_ = speed;
    xdirection_ = xdirection;
    ydirection_ = ydirection;
}
// Destructeur :
balle::~balle()
{
    // Destruction des quadriques
    gluDeleteQuadric(ball);
}

balle::drawnBall(){

}
balle::moveBall(){

}
