#include "brick.h"

Brick::Brick(float x, float y){
    x_=x;
    y_=y;
}

Brick::Brick(float x, float y, float z){
    x_=x;
    y_=y;
    z_=z;
}

void Brick::drawnBrick()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix(); // On stocke le repère d’origine
    glClear(GL_COLOR_BUFFER_BIT); // On vide la couleur
    // Affichage du cube (face selon un repère orthonormé (x,y,z)
    float sizeCenterX_ = sizeX_/2;
    float sizeCenterY_ = sizeY_/2;
    float sizeCenterZ_ = sizeZ_/2;
    glBegin(GL_QUADS);

    glColor3ub(r,g,b); // Définiton de la couleur (RVB) du polygone  (ici en vert)|
    /** Devant **/
    glVertex3f(x_-sizeCenterX_, y_-sizeCenterY_, z_+sizeCenterZ_);
    glVertex3f(x_+sizeCenterX_, y_-sizeCenterY_, z_+sizeCenterZ_);
    glVertex3f(x_+sizeCenterX_, y_+sizeCenterY_, z_+sizeCenterZ_);
    glVertex3f(x_-sizeCenterX_, y_+sizeCenterY_, z_+sizeCenterZ_);
    /** Derrière **/
    glVertex3f(x_-sizeCenterX_, y_-sizeCenterY_, z_-sizeCenterZ_);
    glVertex3f(x_-sizeCenterX_, y_+sizeCenterY_, z_-sizeCenterZ_);
    glVertex3f(x_+sizeCenterX_, y_+sizeCenterY_, z_-sizeCenterZ_);
    glVertex3f(x_+sizeCenterX_, y_-sizeCenterY_, z_-sizeCenterZ_);
    /** Haut **/
    glVertex3f(x_-sizeCenterX_, y_+sizeCenterY_, z_-sizeCenterZ_);
    glVertex3f(x_-sizeCenterX_, y_+sizeCenterY_, z_+sizeCenterZ_);
    glVertex3f(x_+sizeCenterX_, y_+sizeCenterY_, z_+sizeCenterZ_);
    glVertex3f(x_+sizeCenterX_, y_+sizeCenterY_, z_-sizeCenterZ_);
    /** Bas **/
    glVertex3f(x_-sizeCenterX_, y_-sizeCenterY_, z_-sizeCenterZ_);
    glVertex3f(x_+sizeCenterX_, y_-sizeCenterY_, z_-sizeCenterZ_);
    glVertex3f(x_+sizeCenterX_, y_-sizeCenterY_, z_+sizeCenterZ_);
    glVertex3f(x_-sizeCenterX_, y_-sizeCenterY_, z_+sizeCenterZ_);
    /** coté droit **/
    glVertex3f(x_+sizeCenterX_, y_-sizeCenterY_, z_-sizeCenterZ_);
    glVertex3f(x_+sizeCenterX_, y_+sizeCenterY_, z_-sizeCenterZ_);
    glVertex3f(x_+sizeCenterX_, y_+sizeCenterY_, z_+sizeCenterZ_);
    glVertex3f(x_+sizeCenterX_, y_-sizeCenterY_, z_+sizeCenterZ_);
    /** coté gauche **/
    glVertex3f(x_-sizeCenterX_, y_-sizeCenterY_, z_-sizeCenterZ_);
    glVertex3f(x_-sizeCenterX_, y_-sizeCenterY_, z_+sizeCenterZ_);
    glVertex3f(x_-sizeCenterX_, y_+sizeCenterY_, z_+sizeCenterZ_);
    glVertex3f(x_-sizeCenterX_, y_+sizeCenterY_, z_-sizeCenterZ_);
    glEnd();
    // ----------------------------------------------------------------
    glPopMatrix(); // On redonne le repère d’origine
}

void Brick::setSize(float sizeX,float sizeY,float sizeZ){
    sizeX_ = sizeX/2;
    sizeY_ = sizeY/2;
    sizeZ_ = sizeZ/2;
}
