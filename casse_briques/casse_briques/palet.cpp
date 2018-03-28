#include "palet.h"

Palet::Palet()
{

}

void Palet::draw()
{

    glPushMatrix();

    glColor3f(r, g, b);
    glTranslatef(x, y, z);
    glRotatef(90, 0, 1, 0);
    gluCylinder(quadric, radius, radius, length, 100, 1);
    glPopMatrix();

}
