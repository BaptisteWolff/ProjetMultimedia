#ifndef BALLE_H
#define BALLE_H

#include <GL/glu.h>
#include <QColor>
#include <QtGui/qopengl.h>

#include <cstdio>
#include <iostream>

using namespace std;

class balle
{
public:
    // Constructeur
    balle(float x, float y, float z,int speed,float xdirection,float ydirection);
    balle(float x, float y,int speed,float xdirection,float ydirection);
    // Destructeur
    virtual ~balle();
    // Permet d'afficher la balle
    void drawnBall();
    // Permet de se faire déplacer la balle
    void moveBall();
    // Permet de changer la direction de la balle
    void changeDirection(float xDirection, float yDirection){xdirection_=xDirection;ydirection_ = yDirection;}
    // Permet de changer la speed de la balle
    void changeSpeed(int newSpeed){speed_ = newSpeed;}
private:
    int speed_ = 0; // comprise entre 0 et 5
    float xdirection_ = 0.0;
    float ydirection_ = 0.0;
    float x_ = 0.0;
    float y_ = 0.0;
    float z_ = 0.0;
    bool display = true;
    float sizeball;
    GLUquadric ball;
};

#endif // BALLE_H
