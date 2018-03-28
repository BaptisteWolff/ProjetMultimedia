#ifndef CASSEBRIQUES_H
#define CASSEBRIQUES_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QColor>
#include <QVector2D>

#include "palet.h"


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

    Palet palet;
    GLfloat xPalet = 0; // Position du palet
};

#endif // MYGLWIDGET_H
