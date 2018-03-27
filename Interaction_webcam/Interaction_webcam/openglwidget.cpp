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
}


void OpenGlWidget::paintGL()
{
    // Activation du zbuffer
    if (zbuffer){
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
    // Reinitialisation des tampons
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    // Definition de la matrice modelview
    glLoadIdentity( );
    //glFrustum(-1.6, 1.6, -0.9, 0.9, 1, 1000); // Définir les paramètres pour notre projection perspective
    gluPerspective(90, (float)width()/(float)height(), 0.1, 1000);
    gluLookAt(10.0 + zoom,  10.0 + zoom,  10.0 + zoom, zoom, zoom, zoom, 0, 1.0, 0);

    // ----------------------------------------------------------------
    // Affichage de la quadrique
    GLUquadric* quadrique = gluNewQuadric();
    glColor3f(0.0, 0.0, 1.0); // On définit la couleur courante comme étant bleue
    glTranslatef(x_, y_, z_); // On lui applique une translation
    glColor3f(0.0, 0.0, 1.0); // On définit la couleur courante comme étant bleue
    gluSphere(quadrique, 1.1, 200, 200); // On dessine une sphère
    // ----------------------------------------------------------------


}

void OpenGlWidget::translateSphere(float x, float y, float z)
{
    x_ += x;
    y_ += y;
    z_ += z;
    updateGL();
}
