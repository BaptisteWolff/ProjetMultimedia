#include "wall.h"

Wall::Wall(cv::Point2f center, float sizeX, float sizeY)
{
    this->x_ = center.x;
    this->y_ = center.y;

    this->sizeX_ = sizeX;
    this->sizeY_ = sizeY;

    this->xMin_ = x_ - sizeX/2;
    this->xMax_ = x_ + sizeX/2;

    this->yMin_ = y_ - sizeY/2;
    this->yMax_ = y_ + sizeY/2;
}

Wall::Wall()
{

}

void Wall::draw()
{
    glPushMatrix(); // On stocke le repère d’origine
    // Affichage du cube (face selon un repère orthonormé (x,y,z)
    float sizeCenterX = sizeX_/2;
    float sizeCenterY = sizeY_/2;
    float sizeCenterZ = sizeZ_/2;
    glBegin(GL_QUADS);

    glColor3f(r_,g_,b_); // Définiton de la couleur (RVB) du polygone  (ici en vert)|
    /** Devant **/
    glVertex3f(x_-sizeCenterX, y_-sizeCenterY, z_+sizeCenterZ);
    glVertex3f(x_+sizeCenterX, y_-sizeCenterY, z_+sizeCenterZ);
    glVertex3f(x_+sizeCenterX, y_+sizeCenterY, z_+sizeCenterZ);
    glVertex3f(x_-sizeCenterX, y_+sizeCenterY, z_+sizeCenterZ);
    /** Derrière **/
    glVertex3f(x_-sizeCenterX, y_-sizeCenterY, z_-sizeCenterZ);
    glVertex3f(x_-sizeCenterX, y_+sizeCenterY, z_-sizeCenterZ);
    glVertex3f(x_+sizeCenterX, y_+sizeCenterY, z_-sizeCenterZ);
    glVertex3f(x_+sizeCenterX, y_-sizeCenterY, z_-sizeCenterZ);
    /** Haut **/
    glVertex3f(x_-sizeCenterX, y_+sizeCenterY, z_-sizeCenterZ);
    glVertex3f(x_-sizeCenterX, y_+sizeCenterY, z_+sizeCenterZ);
    glVertex3f(x_+sizeCenterX, y_+sizeCenterY, z_+sizeCenterZ);
    glVertex3f(x_+sizeCenterX, y_+sizeCenterY, z_-sizeCenterZ);
    /** Bas **/
    glVertex3f(x_-sizeCenterX, y_-sizeCenterY, z_-sizeCenterZ);
    glVertex3f(x_+sizeCenterX, y_-sizeCenterY, z_-sizeCenterZ);
    glVertex3f(x_+sizeCenterX, y_-sizeCenterY, z_+sizeCenterZ);
    glVertex3f(x_-sizeCenterX, y_-sizeCenterY, z_+sizeCenterZ);
    /** coté droit **/
    glVertex3f(x_+sizeCenterX, y_-sizeCenterY, z_-sizeCenterZ);
    glVertex3f(x_+sizeCenterX, y_+sizeCenterY, z_-sizeCenterZ);
    glVertex3f(x_+sizeCenterX, y_+sizeCenterY, z_+sizeCenterZ);
    glVertex3f(x_+sizeCenterX, y_-sizeCenterY, z_+sizeCenterZ);
    /** coté gauche **/
    glVertex3f(x_-sizeCenterX, y_-sizeCenterY, z_-sizeCenterZ);
    glVertex3f(x_-sizeCenterX, y_-sizeCenterY, z_+sizeCenterZ);
    glVertex3f(x_-sizeCenterX, y_+sizeCenterY, z_+sizeCenterZ);
    glVertex3f(x_-sizeCenterX, y_+sizeCenterY, z_-sizeCenterZ);
    glEnd();
    // ----------------------------------------------------------------
    glPopMatrix(); // On redonne le repère d’origine
}

cv::Point2f Wall::getDir(Ball ball)
{
    float xDir = ball.getXDir();
    float yDir = ball.getYDir();

    float radius = ball.getRadius();
    int xMin = ball.getX() - radius;
    int xMax = ball.getX() + radius;
    int yMin = ball.getY() - radius;
    int yMax = ball.getY() + radius;

    if (xMax == this->xMin_ || xMin == this->xMax_)
    {
        xDir = - xDir;
    }
    if (yMax == this->yMin_ || yMin == this->yMax_)
    {
        yDir = - yDir;
    }

    return cv::Point2f(xDir, yDir);
}

bool Wall::isTouching(Ball ball)
{
    float radius = ball.getRadius();
    int xMin = ball.getX() - radius;
    int xMax = ball.getX() + radius;
    int yMin = ball.getY() - radius;
    int yMax = ball.getY() + radius;

    if (xMax == this->xMin_ || xMin == this->xMax_)
    {
        return true;
    }
    if (yMax == this->yMin_ || yMin == this->yMax_)
    {
        return true;
    }
    return false;
}
