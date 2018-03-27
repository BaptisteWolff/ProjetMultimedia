#ifndef BALLE_H
#define BALLE_H

#include <GL/glu.h>
#include <QColor>
#include <QtGui/qopengl.h>

#include <cstdio>
#include <iostream>

using namespace std;

class Balle
{
public:
    /** Constructeur **/
    Balle(float x, float y, float z, int speed, float xdirection, float ydirection, float zdirection);
    Balle(float x, float y,int speed,float xdirection,float ydirection);
    /** Destructeur **/
    virtual ~Balle();
    /** Affichage **/
    // Permet d'afficher la balle
    void drawnBall();
    /** Déplacement **/
    // Permet de se faire déplacer la balle
    void moveBall();
    // Permet de changer la direction de la balle
    void changeDirection(float xDirection, float yDirection){xdirection_=xDirection;ydirection_ = yDirection;}
    // Permet de changer la speed de la balle
    void changeSpeed(int newSpeed){speed_ = newSpeed;}
private:
    /** Speed **/
    int speed_ = 0; // comprise entre 0 et 5
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
    float sizeball = 5.0f;
    GLUquadric* ball;
        /** Couleur & Texture **/
    float r = 38;
    float g = 196;
    float b = 236;

};

#endif // BALLE_H
