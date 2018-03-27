#include "cassebriques.h"
#include <QApplication>
#include <QDesktopWidget>
#include <math.h>

// Declarations des constantes
const unsigned int WIN_WIDTH  = 1600;
const unsigned int WIN_HEIGHT = 900;
const float ASPECT_RATIO      = static_cast<float>(WIN_WIDTH) / WIN_HEIGHT;
const float ORTHO_DIM         = 50.0f;

bool triangle = true;
bool primitive = true;
float r1 = 0.6;
float g1 = 0;
float b1 = 0.8;

float r2 = 0.1;
float g2 = 0.15;
float b2 = 0.2;

float r3 = 0.1;
float g3 = 0.9;
float b3 = 0.2;

float r4 = 0.1;
float g4 = 0.1;
float b4 = 0.2;

GLfloat X = 0;
GLfloat Y = 0;
GLfloat Z = 0;

GLfloat angle = 0;


// Constructeur
CasseBriques::CasseBriques(QWidget * parent) : QGLWidget(parent)
{
    // Reglage de la taille/position
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
}


// Fonction d'initialisation
void CasseBriques::initializeGL()
{
    // Reglage de la couleur de fond
    glClearColor(0.5, 0.5, 0.5, 1.0);
}


// Fonction de redimensionnement
void CasseBriques::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)

    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ORTHO_DIM * ASPECT_RATIO, ORTHO_DIM * ASPECT_RATIO, -ORTHO_DIM, ORTHO_DIM, -2.0f * ORTHO_DIM, 2.0f * ORTHO_DIM);

    // Definition de la matrice de modele
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// Fonction d'affichage
void CasseBriques::paintGL()
{
    // Reinitialisation du tampon de couleur
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0,0,width(),height());
    // Reinitialisation de la matrice courante
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.6, 0.0, 0.9, -1.0, 1.0);

    // Reglage de la couleur
    glColor3ub(r1, g1, b1);

    glTranslatef(X+0.8, Y+0.45, Z);

    glRotatef(angle, 0, 0, 1);

    // Debut de l'affichage
    if(primitive)
    {
        glEnableClientState(GL_VERTEX_ARRAY); // Active le tableau permettant de définir les vertices
        glEnableClientState(GL_COLOR_ARRAY);
        GLfloat vertices[] = { 0.3*cos(2*M_PI/3), 0.3*sin(2*M_PI/3), // triangle
                               0.3*cos(4*M_PI/3), 0.3*sin(4*M_PI/3),
                               0.3*cos(6*M_PI/3), 0.3*sin(6*M_PI/3),
                               -0.25, -0.25, // rectangle
                               -0.25, 0.25,
                               0.25, 0.25,
                               0.25, -0.25
                             };
        GLfloat colors[] = {r1, g1, b1,
                            r2, g2, b2,
                            r3, g3 ,b3,
                            r1, g1, b1,
                            r2, g2, b2,
                            r3, g3 ,b3,
                            r4, g4, b4};


        glColorPointer(3, GL_FLOAT, 0, colors);
        glVertexPointer(2, GL_FLOAT, 0, vertices); // 2 coordonnées pour chaque vertex

        if (triangle)
        {
            glDrawArrays(GL_TRIANGLES, 0, 3); // Dessine 1 triangle ayant 3 vertices

            /*glBegin(GL_TRIANGLES); // Primitive à afficher et début de la déclaration des vertices de cette primitive
            glVertex2f(0.3*cos(2*M_PI/3), 0.3*sin(2*M_PI/3));
            glColor3ub(r2, g2, b2);
            glVertex2f(0.3*cos(4*M_PI/3), 0.3*sin(4*M_PI/3));
            glColor3ub(r3, g3, b3);
            glVertex2f(0.3*cos(6*M_PI/3), 0.3*sin(6*M_PI/3));
            glEnd(); // Fin de la déclaration*/
        }
        else
        {
            glDrawArrays(GL_QUADS, 3, 4);

            /*glBegin(GL_QUADS);
            glVertex2f(-0.25,-0.25);
            glColor3ub(r2, g2, b2);
            glVertex2f(-0.25,0.25);
            glColor3ub(r3, g3, b3);
            glVertex2f(0.25,0.25);
            glColor3ub(r4, g4, b4);
            glVertex2f(0.25,-0.25);
            glEnd();*/
        }

        glDisableClientState(GL_VERTEX_ARRAY); // Désactive le tableau
    }
}


// Fonction de gestion d'interactions clavier
void CasseBriques::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
        // Changement de couleur du fond
        case Qt::Key_B:
        {
            float R = rand() / (float)RAND_MAX;
            float G = rand() / (float)RAND_MAX;
            float B = rand() / (float)RAND_MAX;
            glClearColor(R, G, B, 1.0);
            break;
        }

        // Changement de couleur de l'objet
        case Qt::Key_C:
        {
            r1 = rand() / (float)RAND_MAX;
            g1 = rand() / (float)RAND_MAX;
            b1 = rand() / (float)RAND_MAX;

            r2 = rand() / (float)RAND_MAX;
            g2 = rand() / (float)RAND_MAX;
            b2 = rand() / (float)RAND_MAX;

            r3 = rand() / (float)RAND_MAX;
            g3 = rand() / (float)RAND_MAX;
            b3 = rand() / (float)RAND_MAX;

            r4 = rand() / (float)RAND_MAX;
            g4 = rand() / (float)RAND_MAX;
            b4 = rand() / (float)RAND_MAX;
            break;
        }

        // Affichage/Masquage de l'objet
        case Qt::Key_H:
        {
            primitive = !primitive;
            break;
        }

        // Changement de l'objet a afficher
        case Qt::Key_Space:
        {
            triangle = !triangle;
            break;
        }

        // Sortie de l'application
        case Qt::Key_Escape:
        {
            break;
        }

        case Qt::Key_Up:
        {
            Y+=0.01;
            break;
        }

        case Qt::Key_Down:
        {
            Y-=0.01;
            break;
        }

        case Qt::Key_Left:
        {
            X-=0.01;
            break;
        }

        case Qt::Key_Right:
        {
            X+=0.01;
            break;
        }

        case Qt::Key_R:
        {
            angle += 5;
            break;
        }

        // Cas par defaut
        default:
        {
            // Ignorer l'evenement
            event->ignore();
            return;
        }
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    updateGL();
}
