#ifndef IRENDERMOVABLE_H
#define IRENDERMOVABLE_H

#include "iobject.h"

class RAENGINESHARED_EXPORT IRenderMovable : public IObject
{
public:
    IRenderMovable(QString name, GameWindow* pWnd) : IObject(name, pWnd) { }

    virtual bool    CanUpdate() { return true; }
    virtual bool    CanDraw() { return true; }
protected:
    IRenderMovable() { }
};

#endif // IRENDERMOVABLE_H
