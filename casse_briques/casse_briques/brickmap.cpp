#include "brickmap.h"

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
    dSizeBrick=(100-2*wallWidth)/11;
    cSizeBrick=(56-2*wallWidth)/24;
}
void BrickMap::autoConstruct(){
    autoSizeBrick();
    while (c_brick<depth){
        if (d_brick==column){
            d_brick=0;
            c_brick++;
        }
        if (c_brick == depth){

        }else{
        QString key = QString::number(d_brick)+","+QString::number(c_brick);
        m_Bricks.insert(std::pair<QString,Brick*>(key,new Brick(widthPlot/(-2)+wallWidth+d_brick*(dSizeBrick+1)+dSizeBrick/2,depthPlot-wallWidth-c_brick*(cSizeBrick+1)-cSizeBrick/2)));
        m_Bricks.at(key)->setSize(dSizeBrick,cSizeBrick,4);
        d_brick++;
        }
    }
}
void BrickMap::drawnBricks(){
    c_brick = 0;
    d_brick = 0;
    while (c_brick<depth){
        if (d_brick==column){
            d_brick=0;
            c_brick++;
        }
        if (c_brick == depth){

        }else{
        QString key = QString::number(d_brick)+","+QString::number(c_brick);
        m_Bricks.at(key)->drawnBrick();
        d_brick++;
        }
    };
}
void BrickMap::destroyBrick(QString key){
    m_Bricks.erase(key);
}
Brick* BrickMap::Brick(QString key){
    return m_Bricks[key];
}
bool BrickMap::empty(){
    return m_Bricks.empty();
}
