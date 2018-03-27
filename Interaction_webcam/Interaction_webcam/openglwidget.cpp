#include "openglwidget.h"
#include "ui_openglwidget.h"

#define _USE_MATH_DEFINES

#include <GL/glu.h>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

// Declarations des constantes
const unsigned int WIN_WIDTH  = 640;
const unsigned int WIN_HEIGHT = 480;
const float MAX_DIMENSION     = 50.0f;
OpenGlWidget::OpenGlWidget(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::OpenGlWidget)
{
    ui->setupUi(this);
    // Reglage de la taille/position
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    //updateGL();
}

OpenGlWidget::~OpenGlWidget()
{
    delete ui;
}

// Fonction d'initialisation
void OpenGlWidget::initializeGL()
{
    // Reglage de la couleur de fond
    glClearColor(0.5, 0.5, 0.5, 1.0);
}

// Fonction de redimensionnement
void OpenGlWidget::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0,0,width,height);
    // Definition de la matrice de projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    if(width != 0)
        glOrtho(-MAX_DIMENSION, MAX_DIMENSION, -MAX_DIMENSION * height / static_cast<float>(width), MAX_DIMENSION * height / static_cast<float>(width), -MAX_DIMENSION * 2.0f, MAX_DIMENSION * 2.0f);

}


void OpenGlWidget::paintGL()
{
    glEnable(GL_DEPTH_TEST);
    // Reinitialisation des tampons
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Definition de la matrice Projection :
    glLoadIdentity( );
    gluPerspective(90, (float)width()/(float)height(), 0.1, 1000);
    //glFrustum(-1.6, 1.6, -0.9, 0.9, 1, 1000); // Définir les paramètres pour notre projection perspective
    // Definition et réinitialisation de la matrice de modelisation / visualisation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, -3.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);//gluLookAt(10.0 + zoom,  10.0 + zoom,  10.0 + zoom, zoom, zoom, zoom, 0, 1.0, 0);
    // ----------------------------------------------------------------
    // Affichage de la quadrique
    GLUquadric* quadrique = gluNewQuadric();
    glTranslatef(x_, y_, z_); // On lui applique une translation
    glColor3f(0.0, 0.0, 1.0); // On définit la couleur courante comme étant bleue
    gluSphere(quadrique, 2.0f, 32, 32); // On dessine une sphère
    // ----------------------------------------------------------------


}

void OpenGlWidget::translateSphere(float x, float y, float z) // Il faut faire attention le x/y est beaucoup trop grand par rapport à l'échelle prix.
{
    x_ += x/30; //
    y_ += y/30; //yc
    updateGL();
}
