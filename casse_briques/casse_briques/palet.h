#ifndef PALET_H
#define PALET_H

#include <GL/glu.h>

class Palet
{
public:
    Palet();
    Display();

private:
    // Taille du palet
    float length = 0.15;
    float radius = 0.01;

    // Position du palet
    float x = 0;
    float y = 0;

    // Couleur 38, 196, 236
    float r = 38;
    float g = 196;
    float b = 236;
};

#endif // PALET_H
