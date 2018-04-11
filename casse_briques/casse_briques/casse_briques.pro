# configuration Qt
QT       += core gui opengl widgets
TEMPLATE  = app

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core2413 \
    -lopencv_highgui2413 \
    -lopencv_imgproc2413 \
    -lopencv_features2d2413 \
    -lopencv_calib3d2413

# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
else {
	LIBS     += -lGL -lGLU
}

# nom de l'exe genere
TARGET 	  = CasseBriques

# fichiers sources/headers
SOURCES	+= main.cpp \
    cassebriques.cpp \
    palet.cpp \
<<<<<<< HEAD
    balle.cpp \
    brick.cpp \

HEADERS += \
    cassebriques.h \
    palet.h \
    balle.h \
    brick.h \

=======
    brick.cpp \
    wall.cpp \
    ball.cpp
HEADERS += \
    cassebriques.h \
    palet.h \
    brick.h \
    wall.h \
    ball.h
>>>>>>> 2c6fa350ddbc26ab253463a69a82cd6c1986679d
