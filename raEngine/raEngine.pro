#-------------------------------------------------
#
# Project created by QtCreator 2016-04-25T16:44:27
#
#-------------------------------------------------

QT       += network opengl svg xml gui


TARGET = raEngine
TEMPLATE = lib

DEFINES += RAENGINE_LIBRARY
debug: DEFINES += RAEDEBUG

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
    shaderlist.cpp \
    xmlconfig.cpp \
    qglen.cpp \
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
    tsingleton.h \
    shaderlist.h \
    xmlconfig.h \
    qglen.h \
    camera.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    data/config/settings.xml \
    data/shader/ToonShader.rs \
    data/shader/ColorPosition.rs





