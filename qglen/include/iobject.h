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
#ifndef IOBJECT_H
#define IOBJECT_H

#include "criticalsection.h"
#include <QString>

#include <QPainter>
#include "gamewindow.h"
#include <glm/mat4x4.hpp>

QGLEN_BEGIN

namespace SceneManagerPrio {
    enum SceneManagerPrio_t
    {
        First = 0,
        Second,
        Third,
        Four,
        Five = 4,

        MAX
    };
}

class RAENGINESHARED_EXPORT IObject : public CriticalSection
{
public:
    IObject(QString name, GameWindow *wnd, glm::mat4 *mWorld = 0)
        :  m_pWindow(wnd), m_bVisual(true), m_bSelected(false), m_strName(name)
    {
        if(mWorld != 0)
            m_matWorld = *mWorld;
        else
            m_matWorld = glm::mat4(1);
    }

    virtual bool                                     CanUpdate() = 0;
    virtual bool                                     CanDraw() = 0;
    virtual SceneManagerPrio::SceneManagerPrio_t     Prio() = 0;
    virtual QString GetName()               { return m_strName; }


    virtual bool Initialize() = 0;
    virtual bool Destroy() = 0;

    virtual void Move(GamePadState *pStates, int numDevices, double renderTime, double elapsedTime, bool lag) = 0;
    virtual void Render(const glm::mat4& pView, const glm::mat4& pProj, double smoothStep) = 0;

    GameWindow* GetGameWindow() { return m_pWindow; }

    virtual void  setWorldMatrix(const glm::mat4& value) { m_matWorld = value; }
    virtual glm::mat4& getWorldMatrix(void) { return m_matWorld; }

    virtual void setSelected(bool sel) { m_bSelected = sel; }
    virtual bool isSelected() { return m_bSelected; }

    virtual void setVisual(bool vis) { m_bVisual = vis; }
    virtual bool IsVisual() { return m_bVisual; }

    virtual const float getBoundingsphereRadius()		{ return 1.0f; }
    virtual bool		Intersects(const glm::vec3* pRayPos,
                                   const glm::vec3* pRayDir,
                                   float* pDist)
    {
        Q_UNUSED(pRayPos)
        Q_UNUSED(pRayDir)
        Q_UNUSED(pDist)
        return false;
    };

protected:
    virtual void    SetName(QString name)   { m_strName = name; }
    IObject() { }

    GameWindow  *m_pWindow;

    glm::mat4       m_matWorld;
    bool            m_bVisual;
    bool            m_bSelected;
private:
    QString     m_strName;
};

QGLEN_END

#endif // IOBJECT_H
