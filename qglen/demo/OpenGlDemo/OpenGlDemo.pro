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
    src/dreieckgamestate.cpp

HEADERS  += \
    include/trianglewindow.h \
    include/dreieckobject.h \
    include/dreieckgamestate.h






win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../release/ -lQGlEn
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../debug/ -lQGlEn
else:unix: LIBS += -L$$PWD/../../ -lQGlEn

INCLUDEPATH += $$PWD/../../3dpart
INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../

