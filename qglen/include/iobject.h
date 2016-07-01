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
    IObject(QString name, GameWindow *wnd) : m_strName(name), m_pWindow(wnd) { }

    virtual bool                                     CanUpdate() = 0;
    virtual bool                                     CanDraw() = 0;
    virtual SceneManagerPrio::SceneManagerPrio_t     Prio() = 0;
    virtual QString GetName()               { return m_strName; }


    virtual bool Initialize() = 0;
    virtual bool Destroy() = 0;

    virtual void Move(double renderTime, double elapsedTime) = 0;
    virtual void Input(GamePadState *pStates, int numDevices) = 0;
    virtual void Render(double smoothStep) = 0;

    GameWindow* GetGameWindow() { return m_pWindow; }
protected:
    virtual void    SetName(QString name)   { m_strName = name; }
    IObject() { }

    GameWindow  *m_pWindow;
private:
    QString     m_strName;
};

#endif // IOBJECT_H
