#ifndef PALET_H
#define PALET_H

#include <GL/glu.h>
#include <opencv2/core.hpp>
#include <math.h>
#include "balle.h"

class Palet
{
public:
    Palet();
    void draw();
    void setX(float x){this->_x = x - _length/2;}
    float getX(){return (this->_x - _length/2);}
    cv::Point2f getDir(Balle ball);

private:
    // Taille du palet
    float _length = 16;
    float _radius = 0.6;

    // Position du palet
    float _x = _length/2;
    float _y = -20;
    float _z = 0;

    // Couleur 38, 196, 236
    float _r = 38.0/255;
    float _g = 196.0/255;
    float _b = 236.0/255;

    GLUquadric* _quadric = gluNewQuadric();
};

#endif // PALET_H
