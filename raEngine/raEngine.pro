#-------------------------------------------------
#
# Project created by QtCreator 2016-04-25T16:44:27
#
#-------------------------------------------------

QT       += network opengl svg xml gui


TARGET = raEngine
TEMPLATE = lib

DEFINES += RAENGINE_LIBRARY

LIBS += -fopenmp
INCLUDEPATH    += $$PWD/include

win32: LIBS +=  -lopengl32 -lglu32 -lgdi32
win32: LIBS += -L$$PWD/include/sdl2/lib/ -lSDL2

SOURCES += \
    gamewindow.cpp \
    scenemanager.cpp \
    gamestate.cpp \
    gamestatemanager.cpp \
    physikobject.cpp \
    colorpositionvertex.cpp \
    debuglog.cpp \
    camera.cpp \
    qglen.cpp \
    xmlconfig.cpp \
<<<<<<< HEAD
    tsingleton.cpp \
    shaderlist.cpp
=======
    tsingleton.cpp
>>>>>>> 5d18df288e58703d7732b4aa62335b8240a15abb

HEADERS +=\
        raengine_global.h \
    gamewindow.h \
    scenemanager.h \
    gamestate.h \
    gamestatemanager.h \
    physikobject.h \
    iobject.h \
    irendermovable.h \
    colorpositionvertex.h \
    debuglog.h \
    camera.h \
    qglen.h \
    xmlconfig.h \
<<<<<<< HEAD
    tsingleton.h \
    shaderlist.h
=======
    tsingleton.h
>>>>>>> 5d18df288e58703d7732b4aa62335b8240a15abb

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    data/config/settings.xml \
    data/shader/ToonShader.rs \
    data/shader/ColorPosition.rs





