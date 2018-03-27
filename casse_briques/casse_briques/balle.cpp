#include "balle.h"
#include "QImage.h"
#include <QGLWidget>
#include <QFile>

// Constructeur :

Balle::Balle(float x, float y, float z, int speed, float xdirection, float ydirection, float zdirection)
{
    x_ = x;
    y_ = y;
    z_ = z;
    speed_ = speed;
    xdirection_ = xdirection;
    ydirection_ = ydirection;
    zdirection_ = zdirection;
}
Balle::Balle(float x, float y, int speed, float xdirection, float ydirection)
{
    x_ = x;
    y_ = y;
    speed_ = speed;
    xdirection_ = xdirection;
    ydirection_ = ydirection;
}
// Destructeur :
Balle::~Balle()
{
    // Destruction des quadriques
    gluDeleteQuadric(ball);
}

Balle::drawnBall(){
    // Affichage de la quadrique
    ball = gluNewQuadric();
    glTranslatef(x_, y_, z_); // On lui applique une translation
    glColor3f(0.0, 0.0, 1.0); // On définit la couleur courante comme étant bleue
    gluSphere(ball, sizeball, 32, 32); // On dessine une sphère
}
Balle::moveBall(){
    x_ += xdirection_*speed_;
    y_ += ydirection_*speed_;
    z_ += zdirection_*speed_;
}
