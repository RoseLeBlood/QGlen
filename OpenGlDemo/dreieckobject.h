#ifndef DREIECKOBJECT_H
#define DREIECKOBJECT_H


#include <iobject.h>
#include <gamewindow.h>

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

class DreieckObject : public IObject
{
public:
    DreieckObject(GameWindow* window);


    virtual bool CanUpdate() { return true; }
    virtual bool CanDraw() { return true; }
    virtual SceneManagerPrio::SceneManagerPrio_t
        Prio() { return SceneManagerPrio::First; }

    virtual bool Initialize();
    virtual bool Destroy();

    virtual void Move(double renderTime, double elapsedTime);
    virtual void Input();
    virtual void Render(QPainter *painter, double smoothStep);


    void SetPosition(QVector3D vector) { m_Position = vector; }
private:
     int m_posAttr;
     int m_colAttr;
     int m_matrixUniform;

     QVector3D  m_Position;
     QOpenGLBuffer m_vertex;
     QOpenGLVertexArrayObject m_object;
     QOpenGLShaderProgram *m_program;
};

#endif // DREIECKOBJECT_H
