#ifndef BRICK_H
#define BRICK_H
#include <GL/glu.h>
#include <QColor>
#include <QImage>
#include <QGLWidget>
#include <QtGui/qopengl.h>
#include <QCoreApplication>
#include <cstdio>
#include <iostream>
#include <opencv2/core.hpp>
#include <math.h>

#include "ball.h"

using namespace std;

class Brick
{
public:
    /** Constructeur **/
    Brick();
    Brick(float x, float y, float z);
    Brick(float x, float y);
    /** Affichage **/
    // Permet d'afficher la brick :
    void drawnBrick();
    // Permet d'avoir l'emplacement actuel de la brick :
    float getX(){return x_;}
    float getY(){return y_;}
    float getZ(){return z_;}
    // Permet de set la taille:
    void setSize(float sizeX,float sizeY,float sizeZ);
    // Permet de savoir la taille :
    float getSizeX(){return sizeX_;}
    float getSizeY(){return sizeY_;}
    float getSizeZ(){return sizeZ_;}
    // Permet de set la texure :
    void setTexture(string m_Name);
    void setXY(float x, float y);
    void setScore(int score){score_ = score;}
    int getScore(){return score_;}
    // Permet de tester si la balle touche la brique et donne la direction x,y de la balle
    cv::Point2f getDir(Ball ball);
    ~Brick();
private:
    /** Brick **/
        /** Coordonnée **/
    float x_ = 0.0;
    float y_ = 0.0;
    float z_ = 0.0;
        /** Bords **/
    float xMin_;
    float xMax_;
    float yMin_;
    float yMax_;
        /** Taille **/
    float sizeX_ = 4.0;
    float sizeY_ = 4.0;
    float sizeZ_ = 4.0;
        /** Couleur & Texture **/
    float r = 0;
    float g = 255;
    float b = 0;
    bool texture = false;
    // Identifiant de texture
    GLuint m_TextureID = 0;
    QImage tex;

    /** score **/
    int score_ = 1;

    void setEdges();
};

#endif // BRICKS_H
