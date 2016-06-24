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
#ifndef __PHYSIKOBJECT_H
#define __PHYSIKOBJECT_H

#include "irendermovable.h"
#include <QVector3D>
#include <QString>
#include <QMatrix4x4>

class RAENGINESHARED_EXPORT PhysikObject : public IRenderMovable
{
public:
    PhysikObject(IRenderMovable* rand,
                     const QVector3D Position = QVector3D(0.0f,0,0),
                     const QVector3D Velocity = QVector3D(0.0f,0,0),
                     const QVector3D Accelerator = QVector3D(0.0f,0,0),
                     float mass = 1.0f) : IRenderMovable(rand->GetName() + QString("_PHYSIK")
                                                         , rand->GetGameWindow()),
        m_pObject(rand),
        m_Velocity(Velocity),
        m_Accelerate(Accelerator),
        m_AngularVelocity(QVector3D(0.0f,0,0)),
        m_AngularAccelerate(QVector3D(0.0f,0,0))
    {
        m_Translation.translate(Position);
        m_Rotation = QMatrix4x4();

                /*m_Scaling = raMatrixScaling(raVector3(m_pRender->GetWorldMatrix()->m11,
                                                      m_pRender->GetWorldMatrix()->m22,
                                                      m_pRender->GetWorldMatrix()->m33));*/

        m_Mass = mass;
    }

    virtual void Move(double renderTime, double elapsedTime)
    {
            // TODO
    }

    void Accelerate(float x, float y, float z) ;
    void AngAccel(float x, float y, float z);

    void SetAccelerate(float x, float y, float z) { SetAccelerate(QVector3D(x, y, z)); }
    void SetAccelerate(QVector3D accelerator) { m_Accelerate = accelerator; }

    void SetAngAccel(float x, float y, float z) { SetAngAccel(QVector3D(x, y, z)); }
    void SetAngAccel(QVector3D Ang) { m_AngularAccelerate  = Ang; }

    void StopMotion()
    {
        m_Accelerate = QVector3D(0,0,0);
        m_Velocity = QVector3D(0,0,0);
        m_AngularVelocity = QVector3D(0,0,0);
    }

    QVector3D	GetVelocity() { return m_Velocity; }

    float		GetMass()     { return m_Mass; }
    float		GetBoundingSphereRadius() { return 1.0f; }

    void        SetVelocity(float x, float y, float z)
    {
        m_Velocity = QVector3D(x,y,z);
    }

private:
    IRenderMovable  *m_pObject;
    QMatrix4x4		m_Translation;
    QVector3D		m_Velocity;
    QVector3D		m_Accelerate;

    QMatrix4x4		m_Rotation;
    QVector3D		m_AngularVelocity;
    QVector3D		m_AngularAccelerate;

    QMatrix4x4		m_Scaling;
    float			m_Mass;

};

#endif // PHYSIKOBJECT_H
