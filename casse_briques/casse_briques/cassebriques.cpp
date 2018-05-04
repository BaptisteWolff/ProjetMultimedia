#include "cassebriques.h"
#include <QApplication>
#include <QDesktopWidget>
#include <math.h>

// Declarations des constantes
const unsigned int WIN_WIDTH  = 1600;
const unsigned int WIN_HEIGHT = 900;
const float MAX_DIMENSION     = 50.0f;

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

    float wallWidth = 2;
    cv::Point2f p1(0, 28);
    cv::Point2f p2(50, 0);
    cv::Point2f p3(0, -28);
    cv::Point2f p4(-50, 0);
    mBricks->autoConstruct();
    upperWall = Wall(p1, 100, wallWidth);
    rightWall = Wall(p2, wallWidth, 56);
    lowerWall = Wall(p3, 100, wallWidth);
    leftWall = Wall(p4, wallWidth, 56);
    lowerWall.setRGB(0, 255, 0);

    QScreen *screen = QApplication::screens().at(0);
    fps = screen->refreshRate();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    timer->setInterval(1000/fps);
    //timer->start();

    ball = Ball(0,-5,20/fps,0,-1);
    setInitBall();
    /*ball2 = Ball(3,-5,20/fps,0,-1);
    ball3 = Ball(-3,-5,20/fps,0,-1);*/
}


// Fonction d'initialisation
void CasseBriques::initializeGL()
{
    // Reglage de la couleur de fond
    glClearColor(0.5, 0.5, 0.5, 1.0);

    // Activation du zbuffer
   glEnable(GL_DEPTH_TEST);

   // Active les textures 2D
   //glEnable(GL_TEXTURE_2D);
}


// Fonction de redimensionnement
void CasseBriques::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);

    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(width != 0)
        glOrtho(-MAX_DIMENSION, MAX_DIMENSION, -MAX_DIMENSION * height / static_cast<float>(width), MAX_DIMENSION * height / static_cast<float>(width), -MAX_DIMENSION * 2.0f, MAX_DIMENSION * 2.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// Fonction d'affichage
void CasseBriques::paintGL()
{
    // Reinitialisation des tampons
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Definition de la position de la camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Debut de l'affichage
    mBricks->drawnBricks();
    palet.draw();
    ball.drawnBall();
    /*ball2.drawnBall();
    ball3.drawnBall();*/
    upperWall.draw();
    lowerWall.draw();
    rightWall.draw();
    leftWall.draw();
}


// Fonction de gestion d'interactions clavier
void CasseBriques::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
        // Changement de couleur du fond
        case Qt::Key_B:
        {
            ball.moveBall();
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
            if(timer->isActive())
            {
                timer->stop();
            }
            else
            {
                timer->start();
            }
            break;
        }

        // Sortie de l'application
        case Qt::Key_Escape:
        {
            break;
        }

        case Qt::Key_Up:
        {
            if(!timer->isActive())
            {
                timeUpdate();
            }
            break;
        }

        case Qt::Key_Down:
        {
            break;
        }

        case Qt::Key_Left:
        {
            float x = palet.getX();
            x -= 1;
            palet.setX(x);
            break;
        }

        case Qt::Key_Right:
        {
            float x = palet.getX();
            x += 1;
            palet.setX(x);
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

    // Acceptation de l'evenement
    event->accept();
    if (!timer->isActive())
    {
        if(initBall)
        {
            setInitBall();
        }
        updateGL();
    }
    else
    {
        initBall = false;
    }
}

void CasseBriques::timeUpdate()
{    
    updateBall();
    //ball2 = updateBall(ball2);
    //ball3 = updateBall(ball3);
    updateGL();
}

void CasseBriques::updateBall()
{
    if (ball.isAlive()){
        ball.moveBall();
        ball.changeDirection(palet.getDir(ball));
        ball.changeDirection(upperWall.getDir(ball));
        ball.changeDirection(rightWall.getDir(ball));
        ball.changeDirection(leftWall.getDir(ball));
        //ball = mBricks->changeDirection(ball);
        ball.changeDirection(mBricks->getDir(ball));
        ball.setAlive(!lowerWall.isTouching(ball));
    }

    if(!ball.isAlive() && ball.getLife() > 0)
    {
        timer->stop();
        setInitBall();
        ball.removeLife();
        ball.setAlive(true);

        initBall = true;
    }
}

void CasseBriques::setInitBall()
{
    ball.setX(palet.getX());
    ball.setY(palet.getY() + palet.getRadius() + ball.getRadius());
    ball.setXdir(0);
}
