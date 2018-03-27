#ifndef PALET_H
#define PALET_H

#include <GL/glu.h>

class Palet
{
public:
    Palet();
    void draw();

private:
    // Taille du palet
    float length = 16;
    float radius = 0.6;

    // Position du palet
    float x = -length / 2;
    float y = -20;
    float z = 0;

    // Couleur 38, 196, 236
    float r = 38.0/255;
    float g = 196.0/255;
    float b = 236.0/255;

     GLUquadric* quadric = gluNewQuadric();
};

#endif // PALET_H
