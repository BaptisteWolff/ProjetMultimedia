#include "brick.h"

Brick::Brick(){}
Brick::Brick(float x, float y){
    x_=x;
    y_=y;
}
Brick::Brick(float x, float y, float z){
    x_=x;
    y_=y;
    z_=z;
}
void Brick::setXY(float x, float y){
    x_=x;
    y_=y;
}
void Brick::setTexture(string m_Name){
    tex = QGLWidget::convertToGLFormat(QImage(QString(":/bricks/%1").arg(QString::fromStdString(m_Name))));
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexImage2D( GL_TEXTURE_2D, 0, 4, tex.width(),tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Répétition de la texture pour la dimension horizontale
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Répétition de la texture pour la dimension verticale
    texture = true;
}

void Brick::drawnBrick()
{
    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix(); // On stocke le repère d’origine
    // Affichage du cube (face selon un repère orthonormé (x,y,z)
    float sizeCenterX_ = sizeX_/2;
    float sizeCenterY_ = sizeY_/2;
    float sizeCenterZ_ = sizeZ_/2;
    glColor3f(r,g,b); // Définiton de la couleur (RVB) du polygone  (ici en vert)|
    if (texture==true){
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, m_TextureID);
            glColor3f(1,1,1);
    };

    glRotatef(0, 1, 0, 0);
    glBegin(GL_QUADS);
    /** Devant = glRotatef(0, 1, 0, 0); **/
    glTexCoord2f(0, 0);glVertex3f(x_-sizeCenterX_, y_-sizeCenterY_, z_+sizeCenterZ_);
    glTexCoord2f(1, 0);glVertex3f(x_+sizeCenterX_, y_-sizeCenterY_, z_+sizeCenterZ_);
    glTexCoord2f(1, 1);glVertex3f(x_+sizeCenterX_, y_+sizeCenterY_, z_+sizeCenterZ_);
    glTexCoord2f(0, 1);glVertex3f(x_-sizeCenterX_, y_+sizeCenterY_, z_+sizeCenterZ_);
    /** Derrière = glRotatef(180, 1, 0, 0); **/
    glTexCoord2f(0, 0);glVertex3f(x_-sizeCenterX_, y_-sizeCenterY_, z_-sizeCenterZ_);
    glTexCoord2f(1, 0);glVertex3f(x_-sizeCenterX_, y_+sizeCenterY_, z_-sizeCenterZ_);
    glTexCoord2f(1, 1);glVertex3f(x_+sizeCenterX_, y_+sizeCenterY_, z_-sizeCenterZ_);
    glTexCoord2f(0, 1);glVertex3f(x_+sizeCenterX_, y_-sizeCenterY_, z_-sizeCenterZ_);
    /** haut = glRotatef(90, 1, 0, 0)**/
    glTexCoord2f(0, 0);glVertex3f(x_-sizeCenterX_, y_+sizeCenterY_, z_-sizeCenterZ_);
    glTexCoord2f(1, 0);glVertex3f(x_-sizeCenterX_, y_+sizeCenterY_, z_+sizeCenterZ_);
    glTexCoord2f(1, 1);glVertex3f(x_+sizeCenterX_, y_+sizeCenterY_, z_+sizeCenterZ_);
    glTexCoord2f(0, 1);glVertex3f(x_+sizeCenterX_, y_+sizeCenterY_, z_-sizeCenterZ_);
    /** Bas = glRotatef(-90, 1, 0, 0) **/
    glTexCoord2f(0, 0);glVertex3f(x_-sizeCenterX_, y_-sizeCenterY_, z_-sizeCenterZ_);
    glTexCoord2f(1, 0);glVertex3f(x_+sizeCenterX_, y_-sizeCenterY_, z_-sizeCenterZ_);
    glTexCoord2f(1, 1);glVertex3f(x_+sizeCenterX_, y_-sizeCenterY_, z_+sizeCenterZ_);
    glTexCoord2f(0, 1);glVertex3f(x_-sizeCenterX_, y_-sizeCenterY_, z_+sizeCenterZ_);
    /** coté droit = glRotatef(-90, 0, 1, 0) **/
    glTexCoord2f(0, 0);glVertex3f(x_+sizeCenterX_, y_-sizeCenterY_, z_-sizeCenterZ_);
    glTexCoord2f(1, 0);glVertex3f(x_+sizeCenterX_, y_+sizeCenterY_, z_-sizeCenterZ_);
    glTexCoord2f(1, 1);glVertex3f(x_+sizeCenterX_, y_+sizeCenterY_, z_+sizeCenterZ_);
    glTexCoord2f(0, 1);glVertex3f(x_+sizeCenterX_, y_-sizeCenterY_, z_+sizeCenterZ_);
    /** coté gauche = glRotatef(90, 0, 1, 0)**/
    glTexCoord2f(0, 0);glVertex3f(x_-sizeCenterX_, y_-sizeCenterY_, z_-sizeCenterZ_);
    glTexCoord2f(1, 0);glVertex3f(x_-sizeCenterX_, y_-sizeCenterY_, z_+sizeCenterZ_);
    glTexCoord2f(1, 1);glVertex3f(x_-sizeCenterX_, y_+sizeCenterY_, z_+sizeCenterZ_);
    glTexCoord2f(0, 1);glVertex3f(x_-sizeCenterX_, y_+sizeCenterY_, z_-sizeCenterZ_);
    glEnd();
    // ----------------------------------------------------------------
    glPopMatrix(); // On redonne le repère d’origine
    glDisable(GL_TEXTURE_2D);
}

void Brick::setSize(float sizeX,float sizeY,float sizeZ){
    sizeX_ = sizeX;
    sizeY_ = sizeY;
    sizeZ_ = sizeZ;
}
