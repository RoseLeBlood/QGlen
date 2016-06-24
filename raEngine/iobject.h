#ifndef IOBJECT_H
#define IOBJECT_H

#include "raengine_global.h"
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

class RAENGINESHARED_EXPORT IObject
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
    virtual void Input() = 0;
    virtual void Render(QPainter *painter, double smoothStep) = 0;

    GameWindow* GetGameWindow() { return m_pWindow; }
protected:
    virtual void    SetName(QString name)   { m_strName = name; }
    IObject() { }

    GameWindow  *m_pWindow;
private:
    QString     m_strName;
};

#endif // IOBJECT_H
