#ifndef PALET_H
#define PALET_H

#include <GL/glu.h>
#include <opencv2/core.hpp>
#include <math.h>
#include "ball.h"

class Palet
{
public:
    Palet();
    void draw();
    void setX(float x){this->_x = x - _length/2;}
    float getX(){return (this->_x - _length/2);}
    cv::Point2f getDir(Ball ball);

private:
    // Taille du palet
    float _length = 16;
    float _radius = 0.6;

    // Position du palet
    float _x = _length/2;
    float _y = -20;
    float _z = 0;

    // Couleur rgb(255, 128, 0)
    float _r = 255.0/255;
    float _g = 128.0/255;
    float _b = 0.0/255;

    GLUquadric* _quadric = gluNewQuadric();
};

#endif // PALET_H
