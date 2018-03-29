#include "Balle.h"
#include "QImage.h"
#include <QGLWidget>
#include <QFile>

// Constructeur :

Balle::Balle(float x, float y, float z, float speed, float xdirection, float ydirection, float zdirection)
{
    x_ = x;
    y_ = y;
    z_ = z;
    speed_ = speed;
    xdirection_ = xdirection;
    ydirection_ = ydirection;
    zdirection_ = zdirection;
    dirNorm();
}
Balle::Balle(float x, float y, float speed, float xdirection, float ydirection)
{
    x_ = x;
    y_ = y;
    speed_ = speed;
    xdirection_ = xdirection;
    ydirection_ = ydirection;
    dirNorm();
}
// Destructeur :
Balle::~Balle()
{
    // Destruction des quadriques
    gluDeleteQuadric(ball);
}
void Balle::drawnBall(){
    // Affichage de la quadrique
    glPushMatrix();
    ball = gluNewQuadric();
    glTranslatef(x_, y_, z_); // On lui applique une translation
    glColor3f(r, g, b); // On définit la couleur courante comme étant bleue
    gluSphere(ball, sizeball, 32, 32); // On dessine une sphère
    glPopMatrix();
}
void Balle::moveBall(){
    x_ += xdirection_*speed_;
    y_ += ydirection_*speed_;
    z_ += zdirection_*speed_;
}
void Balle::dirNorm()
{
    float tot = xdirection_*xdirection_ + ydirection_*ydirection_ + zdirection_*zdirection_;
    xdirection_ = xdirection_ / sqrtf(tot);
    ydirection_ = ydirection_ / sqrtf(tot);
    zdirection_ = zdirection_ / sqrtf(tot);
}
void Balle::changeDirection(cv::Point2f dir)
{
    xdirection_ = dir.x;
    ydirection_ = dir.y;
    dirNorm();
}
