#include "palet.h"

Palet::Palet()
{

}

void Palet::draw()
{

    glPushMatrix();

    glColor3f(r, g, b);
    glRotatef(90, 0, 1, 0);
    glTranslatef(x, y, z);
    gluCylinder(quadric, radius, radius, length, 100, 1);

    glPopMatrix();
}
