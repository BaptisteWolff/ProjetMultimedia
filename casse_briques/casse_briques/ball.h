#ifndef BALLE_H
#define BALLE_H

#include <GL/glu.h>
#include <QColor>
#include <QtGui/qopengl.h>
#include <opencv2/core.hpp>

#include <cstdio>
#include <iostream>
#include <math.h>

using namespace std;

class Ball
{
public:
    /** Constructeur **/
    Ball(float x, float y, float z, float speed, float xdirection, float ydirection, float zdirection);
    Ball(float x, float y,float speed,float xdirection,float ydirection);
    /** Destructeur **/
    virtual ~Ball();
    /** Affichage **/
    // Permet d'afficher la balle
    void drawnBall();
    /** Déplacement **/
    // Permet de se faire déplacer la balle
    void moveBall();
    // Permet de changer la direction de la balle
    void changeDirection(float xDirection, float yDirection){xdirection_=xDirection;ydirection_ = yDirection;dirNorm();}
    void changeDirection(cv::Point2f dir);
    // Permet de changer la speed de la balle
    void changeSpeed(int newSpeed){speed_ = newSpeed;}
    // Permet de changer la taille de la balle
    void changeSpeed(float newsizeball){sizeball = newsizeball;}
    // Permet d'avoir l'emplacement actuel de la balle :
    float getX(){return x_;}
    float getY(){return y_;}
    float getZ(){return z_;}
    void setX(float x){this->x_ = x;}
    void setY(float y){this->y_ = y;}
    void setZ(float z){this->z_ = z;}
    void setXdir(float dir){this->xdirection_ = dir; dirNorm();}
    void removeLife(){this->life_--;}
    float getRadius(){return this->sizeball;}
    float getXDir(){return this->xdirection_;}
    float getYDir(){return this->ydirection_;}
    boolean isAlive(){return alive_;}
    void setAlive(boolean alive){this->alive_ = alive;}
    int getLife(){return life_;}
    void setLife(int life){this->life_ = life;}
private:
    /** Speed **/
    float speed_ = 0; // comprise entre 0 et 5
    /** Direction **/
    float xdirection_ = 0.0;
    float ydirection_ = 0.0;
    float zdirection_ = 0.0;
    /** Balle **/
        /** Coordonnée **/
    float x_ = 0.0;
    float y_ = 0.0;
    float z_ = 0.0;
        /** Quadric **/
    float sizeball = 1.0f;
    GLUquadric* ball;
        /** Couleur & Texture **/
    float r = 255.0/255;
    float g = 0/255;
    float b = 0;

    /** Normalisation de la direction **/
    void dirNorm();

    //
    int life_ = 2;
    bool alive_ = true;
};

#endif // BALLE_H
