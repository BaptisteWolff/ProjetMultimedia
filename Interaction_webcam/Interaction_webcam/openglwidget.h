#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QGLWidget>

namespace Ui {
class OpenGlWidget;
}

class OpenGlWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit OpenGlWidget(QWidget *parent = 0);
    ~OpenGlWidget();
    void translateSphere(float x, float y, float z);

private:
    Ui::OpenGlWidget *ui;
    float zoom = 0;
    bool zbuffer = true;
    float x_ = 0, y_ = 0, z_ = 0;

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();
};

#endif // OPENGLWIDGET_H
