/*
    This file is part of QGlEn.

    QGlEn is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QGlEn is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

    Diese Datei ist Teil von QGlEn.

    QGlEn ist Freie Software: Sie können es unter den Bedingungen
    der GNU General Public License, wie von der Free Software Foundation,
    Version 3 der Lizenz oder (nach Ihrer Wahl) jeder späteren
    veröffentlichten Version, weiterverbreiten und/oder modifizieren.

    QGlEn wird in der Hoffnung, dass es nützlich sein wird, aber
    OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
    Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
    Siehe die GNU General Public License für weitere Details.

    Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
    Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*/
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
