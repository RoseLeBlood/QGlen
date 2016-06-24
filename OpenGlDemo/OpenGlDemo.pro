#-------------------------------------------------
#
# Project created by QtCreator 2016-04-22T17:29:31
#
#-------------------------------------------------

QT       += network opengl svg multimedia gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGlDemo
TEMPLATE = app

SOURCES += \
    trianglewindow.cpp \
    dreieckobject.cpp \
    dreieckgamestate.cpp

HEADERS  += \
    trianglewindow.h \
    dreieckobject.h \
    dreieckgamestate.h






win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../raEngine/release/ -lraEngine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../raEngine/debug/ -lraEngine
else:unix: LIBS += -L$$PWD/../raEngine/ -lraEngine

INCLUDEPATH += $$PWD/../raEngine/
INCLUDEPATH += $$PWD/../raEngine/include
DEPENDPATH += $$PWD/../raEngine/
