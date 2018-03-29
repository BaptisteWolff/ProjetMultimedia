#ifndef WALL_H
#define WALL_H

#include <opencv2/core.hpp>
#include "balle.h"

class Wall
{
public:
    Wall(cv::Point2f center, float sizeX, float sizeY);
    Wall();
    cv::Point2f getDir(Balle ball);
    void draw();
    void setRGB(float r, float g, float b){r_ = r/255; g_ = g/255; b_ = b/255;}

private:
    cv::Point2f _p1, _p2;

    // color rgb(0, 191, 255)
    float r_ = 0.0/255.0;
    float g_ = 191.0/255.0;
    float b_ = 255.0/255.0;

    //center
    float x_ = 0;
    float y_ = 0;
    float z_ = 0;

    float sizeX_ = 0;
    float sizeY_ = 0;
    float sizeZ_ = 2;

    int xMin_;
    int xMax_;
    int yMin_;
    int yMax_;
};

#endif // WALL_H
