#ifndef CASSEBRIQUES_H
#define CASSEBRIQUES_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QColor>
#include <QVector2D>

#include "palet.h"
#include "balle.h"
#include "QTimer"


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
    Balle balle = Balle(-2,3,10/fps,1,-1);



private slots:
    void timeUpdate();
};

#endif // MYGLWIDGET_H
