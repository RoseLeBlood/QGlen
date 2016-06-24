#-------------------------------------------------
#
# Project created by QtCreator 2016-04-25T16:44:27
#
#-------------------------------------------------

QT       += network opengl svg multimedia gui


TARGET = raEngine
TEMPLATE = lib

DEFINES += RAENGINE_LIBRARY

LIBS += -fopenmp
INCLUDEPATH    += $$PWD/include

win32: LIBS +=  -lopengl32 -lglu32 -lgdi32

SOURCES += \
    gamewindow.cpp \
    scenemanager.cpp \
    gamestate.cpp \
    gamestatemanager.cpp \
    physikobject.cpp \
    colorpositionvertex.cpp \
    debuglog.cpp \
    camera.cpp

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
    camera.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


