#include "cassebriques.h"
#include <QApplication>
#include <QDesktopWidget>
#include <math.h>

// Declarations des constantes
const unsigned int WIN_WIDTH  = 1600;
const unsigned int WIN_HEIGHT = 900;
const float MAX_DIMENSION     = 50.0f;




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


    // Webcam setup
    webCam_=new VideoCapture(0);
    int width=webCam_->get(CV_CAP_PROP_FRAME_WIDTH);
    int height=webCam_->get(CV_CAP_PROP_FRAME_HEIGHT);
    // Timer webcam
    float fps = 30;
    timerWebcam = new QTimer(this);
    timerWebcam->setInterval((int)(1000/fps));
    connect(timerWebcam, SIGNAL(timeout()) , this, SLOT(webcamCapture()));
    timerWebcam->start();
    // Detect motion
    detectMotion = DetectMotion(width, height);
    ball = Ball(0,-5,20/fps,0,-1);
    setInitBall();

    font = QFont("Times", 30, QFont::Bold);
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

    if (isPlaying)
    {
        // Debut de l'affichage
        mBricks->drawnBricks();
        palet.draw();
        ball.drawnBall();
        upperWall.draw();
        lowerWall.draw();
        rightWall.draw();
        leftWall.draw();

        // Affichage du texte
        glColor3f(1.0, 1.0, 1.0);
        // vies
        renderText(10, 40, "Vies : " + QString::number(ball.getLife()), font);
        // score
        renderText(1300, 40, "Score : " + QString::number(mBricks->getScore()), font);
        // Fin de partie
        if (mBricks->empty())
        {
            renderText(700, 400, "Victoire !", font);
        }
        else if(ball.getLife() == 0 && !ball.isAlive())
        {
            renderText(640, 400, "Partie terminée", font);
        }
    }
    else
    {
        // Affichage du texte
        glColor3f(1.0, 1.0, 1.0);
        renderText(550, 200, "Reprendre partie", font);
        renderText(550, 300, "Nouvelle partie", font);
        renderText(550, 400, "Scores", font);
        renderText(550, 500, "Choisir niveau", font);

         glColor3f(1.0, 1.0, 0);
        switch (optionSelected) {
        case 0:
            renderText(550, 200, "Reprendre partie", font);
            break;
        case 1:
            renderText(550, 300, "Nouvelle partie", font);
            break;
        case 2:
            renderText(550, 400, "Scores", font);
            break;
        case 3:
            renderText(550, 500, "Choisir niveau", font);
            break;
        default:
            break;
        }
    }
}


// Fonction de gestion d'interactions clavier
void CasseBriques::keyPressEvent(QKeyEvent * event)
{
    if(isPlaying)
    {
        switch(event->key())
        {
        case Qt::Key_Escape:
        {
            isPlaying = false;
            timer->stop();
            break;
        }

        case Qt::Key_Space:
        {
            if(timer->isActive())
            {
                //timer->stop();
            }
            else
            {
                timer->start();
            }
            break;
        }

        case Qt::Key_Up:
        {
            /*if(!timer->isActive())
            {
                timeUpdate();
            }*/
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

        case Qt::Key_C:
        {
            cam =!cam;
            if (cam){
                webCam_=new VideoCapture(0);
                camwindow.show();
            }else{
                webCam_->release();
                camwindow.hide();
            }
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

        updateInit();
    }
    else
    {
        switch(event->key())
        {
        case Qt::Key_Escape:
        {
           isPlaying = true;
           if (!initBall)
           {
               timer->start();
           }
           break;
        }


        case Qt::Key_Down:
        {
            optionSelected++;
            if(optionSelected > 3)
            {
                optionSelected = 0;
            }
            break;
        }

        case Qt::Key_Up:
        {
            optionSelected--;
            if(optionSelected < 0)
            {
                optionSelected = 3;
            }
            break;
        }

        case Qt::Key_Return:
        {
            switch(optionSelected){
            case 0:
                isPlaying = true;
                if (!initBall)
                {
                    timer->start();
                }
                break;
            case 1:
                newGame();
                break;
            case 2:

                break;
            case 3:

                break;
            }
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
    }

    // Acceptation de l'evenement
    event->accept();
    updateGL();

}

void CasseBriques::timeUpdate()
{    
    updateBall();
    updateGL();
}

void CasseBriques::updateBall()
{
    if (ball.isAlive() && !initBall){
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
        ball.removeLife();
        setInitBall();
        ball.setAlive(true);

        initBall = true;
    }
}

void CasseBriques::updateInit()
{
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

void CasseBriques::setInitBall()
{
    ball.setX(palet.getX());
    ball.setY(palet.getY() + palet.getRadius() + ball.getRadius());
    ball.setXdir(0);
}

void CasseBriques::webcamCapture()
{
    if (webCam_->isOpened()) {
        Mat image;
        if (webCam_->read(image))
        {   // Capture a frame

            if (isFirstFrame)
            {
                detectMotion.setFirstFrame(image);
                isFirstFrame = false;
            }
            // Detect motion
            detectMotion.detect(image);
            // Sphere translation
            Point vect = detectMotion.getVect();
            if (vect.x >5 || vect.x<-5)
            {
                float x = palet.getX();
                x += vect.x/3;
                palet.setX(x);

                updateInit();
            }
            camwindow.webcamCapture(image);
        }
        else
        {}
    }
}

void CasseBriques::newGame()
{
    mBricks = new BrickMap();
    mBricks->autoConstruct();
    initBall = true;
    isPlaying = true;
    setInitBall();
    updateInit();
}
