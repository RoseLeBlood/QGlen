#-------------------------------------------------
#
# Project created by QtCreator 2016-04-25T16:44:27
#
#-------------------------------------------------

QT       += network opengl svg xml gui gamepad


TARGET = QGlEn
TEMPLATE = lib

DEFINES += RAENGINE_LIBRARY

CONFIG(debug,debug|release) {
      DEFINES += RAEDEBUG
}


LIBS += -fopenmp
INCLUDEPATH    += $$PWD/3dpart
INCLUDEPATH    += $$PWD/include

CONFIG += c++14

win32: LIBS +=  -lopengl32 -lglu32 -lgdi32

SOURCES += \
    src/gamewindow.cpp \
    src/scenemanager.cpp \
    src/gamestate.cpp \
    src/gamestatemanager.cpp \
    src/physikobject.cpp \
    src/colorpositionvertex.cpp \
    src/debuglog.cpp \
    src/shaderlist.cpp \
    src/xmlconfig.cpp \
    src/camera.cpp \
    src/CriticalSection.cpp \
    src/colorpositionsnormalvertex.cpp \
    src/gamebatch.cpp \
    src/openglerror.cpp \
    src/color.cpp \
    src/qglenenapplication.cpp \
    src/openglvertexarrayobject.cpp

HEADERS +=\
        include/raengine_global.h \
    include/gamewindow.h \
    include/scenemanager.h \
    include/gamestate.h \
    include/gamestatemanager.h \
    include/physikobject.h \
    include/iobject.h \
    include/irendermovable.h \
    include/colorpositionvertex.h \
    include/debuglog.h \
    include/tsingleton.h \
    include/shaderlist.h \
    include/xmlconfig.h \
    include/qglen.h \
    include/camera.h \
    include/criticalsection.h \
    include/colorpositionsnormalvertex.h \
    include/ivertex.h \
    include/gamebatch.h \
    include/openglerror.h \
    include/macros.h \
    include/openglbuffer.h \
    include/openglshaderprogram.h \
    include/openglvertexarrayobject.h \
    include/color.h \
    include/qglenenapplication.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    data/config/settings.xml \
    data/shader/ToonShader.rs





