#ifndef DREIECKGAMESTATE_H
#define DREIECKGAMESTATE_H

#include "gamestate.h"
#include "dreieckobject.h"

class DreieckGameState : public GameState
{
public:
    DreieckGameState(GameWindow *wnd);

    virtual bool Switch(bool , GameState* ) { return true; }

    virtual bool Render(QPainter *painter, double smoothStep)
    {
        GetGameWindow()->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        return GameState::Render(painter, smoothStep);
    }

    virtual bool Move(double renderTime, double elapsedTime)
    {
        const qreal retinaScale = GetGameWindow()->devicePixelRatio();
        GetGameWindow()->glViewport(0, 0, GetGameWindow()->width() * retinaScale, GetGameWindow()->height() * retinaScale);

        return GameState::Move(renderTime, elapsedTime);
    }
    bool Initialize();
};

#endif // DREIECKGAMESTATE_H
