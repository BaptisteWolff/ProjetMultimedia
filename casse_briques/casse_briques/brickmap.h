#ifndef BRICKMAP_H
#define BRICKMAP_H
#include "brick.h"
#include <QGLWidget>
#include <QKeyEvent>
#include <Qstring>
#include <QVector2D>
#include <opencv2/core.hpp>
#include <math.h>
#include <stdlib.h>     /* srand, rand */

/* Authors : Thomas Mion, Baptiste Wolff */
class BrickMap
{
private:
    int depth = 12;
    int column = 10;
    float dSizeBrick = 4;
    float cSizeBrick = 4;
    int c_brick = 0;
    int d_brick = 0;
    map<QString,Brick *> m_Bricks;
    float wallWidth = 2;
    int widthPlot = 100;
    int depthPlot = 28;
    int score_ = 0;
    int level_ = 1;
public:
    BrickMap();
    BrickMap(int nbx, int nby);
    void autoSizeBrick();
    void setWallWidth(float newWallWitdth){wallWidth = newWallWitdth;}
    void setSizeBrick(float dSizeBrick, float cSizeBrick){this->dSizeBrick = dSizeBrick;this->cSizeBrick = cSizeBrick;}
    void drawnBricks();
    void autoConstruct();
    float getMaxColumn() {return (widthPlot/(-2)+wallWidth+(column-1)*(cSizeBrick+1)+cSizeBrick/2);}
    float getMaxDepth() {return (depthPlot/(-2)+wallWidth+(depth-1)*(cSizeBrick+1)+cSizeBrick/2);}
    float getMinColumn() {return (widthPlot/(-2)+wallWidth+cSizeBrick/2);}
    float getMinDepth() {return (depthPlot/(-2)+wallWidth+cSizeBrick/2);}
    void destroyBrick(QString key);
    bool empty();
    Brick* brick(QString key);
    Ball changeDirection(Ball ball);
    cv::Point2f getDir(Ball ball);

    int getScore(){return score_;}
    void setLevel(int level){level_ = level;}
};

#endif // BRICKMAP_H
