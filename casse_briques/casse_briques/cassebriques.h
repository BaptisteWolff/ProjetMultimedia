#ifndef CASSEBRIQUES_H
#define CASSEBRIQUES_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QColor>
#include <QVector2D>

#include "palet.h"
<<<<<<< HEAD
#include "balle.h"
#include "brick.h"
=======
#include "ball.h"
#include "QTimer"
#include "wall.h"

>>>>>>> 2c6fa350ddbc26ab253463a69a82cd6c1986679d

// Classe dediee a l'affichage d'une scene OpenGL
class CasseBriques : public QGLWidget
{
    Q_OBJECT

public:

    // Constructeur
    CasseBriques(QWidget * parent = nullptr);

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent * event);

private:
    float fps = 60;
    Palet palet;
<<<<<<< HEAD
    Balle balle = Balle(0,0,1,1,1);
    GLfloat xPalet = 0; // Position du palet
    Brick Brick1 = Brick(0,0,0);
    Brick Brick2 = Brick(6,6,0);
=======
    Ball ball1 = Ball(0,5,20/fps,0,-1);
    Ball ball2 = Ball(3,5,20/fps,0,-1);
    Ball ball3 = Ball(-3,5,20/fps,0,-1);
    Wall upperWall;
    Wall rightWall;
    Wall leftWall;
    Wall lowerWall;
    Ball updateBall(Ball ball);

private slots:
    void timeUpdate();
>>>>>>> 2c6fa350ddbc26ab253463a69a82cd6c1986679d
};

#endif // MYGLWIDGET_H
