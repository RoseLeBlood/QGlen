#-------------------------------------------------
#
# Project created by QtCreator 2016-04-22T17:29:31
#
#-------------------------------------------------

QT       += network opengl svg multimedia gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGlDemo
TEMPLATE = app
CONFIG += c++14

INCLUDEPATH += $$PWD/include

SOURCES += \
    src/trianglewindow.cpp \
    src/dreieckobject.cpp \
    src/dreieckgamestate.cpp \
    src/camera.cpp

HEADERS  += \
    include/trianglewindow.h \
    include/dreieckobject.h \
    include/dreieckgamestate.h \
    include/camera.h






win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../engine/release/ -lQGlEn
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../engine/debug/ -lQGlEn
else:unix: LIBS += -L$$OUT_PWD/../engine/ -lQGlEn

INCLUDEPATH += $$PWD/../engine/include
INCLUDEPATH += $$PWD/../engine/3dpart
DEPENDPATH += $$PWD/../engine
