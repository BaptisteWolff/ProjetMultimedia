#include "palet.h"

Palet::Palet()
{

}

void Palet::draw()
{
    glPushMatrix();
    glColor3f(_r, _g, _b);
    glTranslatef(_x, _y, _z);
    glRotatef(90, 0, 1, 0);
    gluCylinder(_quadric, _radius, _radius, _length, 100, 1);
    glPopMatrix();
}

cv::Point2f Palet::getDir(Ball ball)
{
    float radius = ball.getRadius();
    float y = ball.getY();

    if ((y <= _y + _radius) && (y >= _y - radius))
    {

        float xMin = ball.getX() - radius;
        float xMax = ball.getX() + radius;

        if ((_x <= xMax) && ((_x + _length) >= xMin))
        {
            float xDir = 2 * (ball.getX() - _x - _length/2) / _length;
            if (xDir > 0.9){
                xDir = 0.9;
            }
            else if (xDir < -0.9)
            {
                xDir = -0.9;
            }
            float yDir =  sqrtf(1 - xDir * xDir);
            return cv::Point2f(xDir, yDir);
        }
    }

    return cv::Point2f(ball.getXDir(), ball.getYDir());
}


void Palet::setX(float x)
{
    x -= this->_length/2;
    if (x + this->_length <= _xMax && x >= _xMin)
    {
        this->_x = x;
    }
}
