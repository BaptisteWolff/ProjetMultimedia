#include "brickmap.h"
#include "brick.h"

// ratio des briques : 1/3 !!!!

BrickMap::BrickMap()
{
    m_Bricks.clear();
}
BrickMap::BrickMap(int nbx, int nby)
{
    depth = nbx;
    column = nby;
    m_Bricks.clear();
}
void BrickMap::autoSizeBrick(){
    /*
    dSizeBrick=(widthPlot-2*wallWidth)/11;
    cSizeBrick=(depthPlot-2*wallWidth)/16; //24
    */
    dSizeBrick=(widthPlot-2*wallWidth)/14;
    cSizeBrick=dSizeBrick/3; //24
}
void BrickMap::autoConstruct(){
    autoSizeBrick();
    d_brick = 0;
    c_brick = 0;
    while (c_brick<depth){
        if (d_brick==column){
            d_brick=0;
            c_brick++;
        }
        if (c_brick != depth)
        {
            QString key = QString::number(d_brick)+","+QString::number(c_brick);
            Brick* brick1 = new Brick(widthPlot/(-2)+wallWidth+d_brick*(dSizeBrick*1.4)+dSizeBrick/1.4,depthPlot-wallWidth-c_brick*(cSizeBrick+1)-cSizeBrick/2);
            m_Bricks.insert(std::pair<QString,Brick*>(key,brick1));
            m_Bricks.at(key)->setSize(dSizeBrick,cSizeBrick,4);
            d_brick++;
        }
    }
}
void BrickMap::drawnBricks(){
    c_brick = 0;
    d_brick = 0;
    while (c_brick<depth){
        if (d_brick==column)
        {
            d_brick=0;
            c_brick++;
        }
        if (c_brick != depth)
        {
            QString key = QString::number(d_brick)+","+QString::number(c_brick);
            if (m_Bricks.count(key) == 1)
            {
                m_Bricks.at(key)->drawnBrick();
            }
            d_brick++;
        }
    };
}
void BrickMap::destroyBrick(QString key){
    m_Bricks.erase(key);
}
Brick* BrickMap::brick(QString key){
    return m_Bricks[key];
}
bool BrickMap::empty(){
    return m_Bricks.empty();
}

Ball BrickMap::changeDirection(Ball ball)
{
    float dirX = ball.getXDir();
    float dirY = ball.getYDir();

    bool alreadyChanged = false;

    c_brick = 0;
    d_brick = 0;

    while (c_brick<depth)
    {
        if (d_brick==column)
        {
            d_brick=0;
            c_brick++;
        }
        if (c_brick != depth)
        {
            QString key = QString::number(d_brick)+","+QString::number(c_brick);
            if (m_Bricks.count(key) == 1)
            {
                Brick *brick = m_Bricks.at(key);
                ball.changeDirection(brick->getDir(ball));
                if (dirX != ball.getXDir() || dirY != ball.getYDir())
                {
                    score_ += brick->getScore();
                    m_Bricks.erase(key);
                    break;
                }
            }
            d_brick++;
        }
    }

    return ball;
}

cv::Point2f BrickMap::getDir(Ball ball)
{
    float x = ball.getX();
    float y = ball.getY();

    cv::Point2f dir(ball.getXDir(), ball.getYDir());

    float c = -1;
    float d = -1;

    float dist = 10000;

    c_brick = 0;
    d_brick = 0;

    while (c_brick<depth)
    {
        if (d_brick==column)
        {
            d_brick=0;
            c_brick++;
        }
        if (c_brick != depth)
        {
            QString key = QString::number(d_brick)+","+QString::number(c_brick);
            if (m_Bricks.count(key) == 1)
            {
                float xBrick1 = widthPlot/(-2)+wallWidth+d_brick*(dSizeBrick+1)+dSizeBrick/2;
                float yBrick1 = depthPlot-wallWidth-c_brick*(cSizeBrick+1)-cSizeBrick/2;

                float dist1 = sqrt((x - xBrick1) * (x - xBrick1) + (y - yBrick1) * (y - yBrick1));
                if (dist1 < dist)
                {
                    dist = dist1;
                    c = c_brick;
                    d = d_brick;
                }
            }

            d_brick++;
        }
    }

    QString key = QString::number(d)+","+QString::number(c);
    if (m_Bricks.count(key) == 1)
    {
        Brick *brick = m_Bricks.at(key);

        dir = brick->getDir(ball);

        if (dir.x != ball.getXDir() || dir.y != ball.getYDir())
        {
            score_ += brick->getScore();
            m_Bricks.erase(key);
        }
    }
    return dir;
}
