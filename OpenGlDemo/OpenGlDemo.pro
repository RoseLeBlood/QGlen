#-------------------------------------------------
#
# Project created by QtCreator 2016-04-22T17:29:31
#
#-------------------------------------------------

QT       += network opengl svg multimedia gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGlDemo
TEMPLATE = app

INCLUDEPATH += $$PWD/include

SOURCES += \
    src/trianglewindow.cpp \
    src/dreieckobject.cpp \
    src/dreieckgamestate.cpp

HEADERS  += \
    include/trianglewindow.h \
    include/dreieckobject.h \
    include/dreieckgamestate.h






win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../raEngine/release/ -lQGlEn
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../raEngine/debug/ -lQGlEn
else:unix: LIBS += -L$$PWD/../raEngine/ -lQGlEn

INCLUDEPATH += $$PWD/../raEngine/3dpart
INCLUDEPATH += $$PWD/../raEngine/include
DEPENDPATH += $$PWD/../raEngine/
