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
    along with QGlEn.  If not, see <http://www.gnu.org/licenses/>.

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
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective


class RAENGINESHARED_EXPORT PhysikObject : public IRenderMovable
{
public:
    PhysikObject(IRenderMovable* rand,
                     const glm::vec3 Position = glm::vec3(0.0f,0,0),
                     const glm::vec3 Velocity = glm::vec3(0.0f,0,0),
                     const glm::vec3 Accelerator = glm::vec3(0.0f,0,0),
                     float mass = 1.0f) : IRenderMovable(rand->GetName() + QString("_PHYSIK")
                                                         , rand->GetGameWindow()),
        m_pObject(rand),
        m_Velocity(Velocity),
        m_Accelerate(Accelerator),
        m_AngularVelocity(glm::vec3(0.0f,0,0)),
        m_AngularAccelerate(glm::vec3(0.0f,0,0))
    {
        m_Translation = glm::translate(m_Translation, Position);
        m_Rotation = glm::mat4();

        m_Scaling  = glm::scale(m_Scaling, glm::vec3(0,0,0));
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

    void SetAccelerate(float x, float y, float z) { SetAccelerate(glm::vec3(x, y, z)); }
    void SetAccelerate(glm::vec3 accelerator) { m_Accelerate = accelerator; }

    void SetAngAccel(float x, float y, float z) { SetAngAccel(glm::vec3(x, y, z)); }
    void SetAngAccel(glm::vec3 Ang) { m_AngularAccelerate  = Ang; }

    void StopMotion()
    {
        m_Accelerate = glm::vec3(0,0,0);
        m_Velocity = glm::vec3(0,0,0);
        m_AngularVelocity = glm::vec3(0,0,0);
    }

    glm::vec3	GetVelocity() { return m_Velocity; }

    float		GetMass()     { return m_Mass; }
    float		GetBoundingSphereRadius() { return 1.0f; }

    void        SetVelocity(float x, float y, float z)
    {
        m_Velocity = glm::vec3(x,y,z);
    }

private:
    IRenderMovable  *m_pObject;
    glm::mat4		m_Translation;
    glm::vec3		m_Velocity;
    glm::vec3		m_Accelerate;

    glm::mat4		m_Rotation;
    glm::vec3		m_AngularVelocity;
    glm::vec3		m_AngularAccelerate;

    glm::mat4		m_Scaling;
    float			m_Mass;

};

#endif // PHYSIKOBJECT_H
