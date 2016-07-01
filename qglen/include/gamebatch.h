#ifndef GAMEBATCH_H
#define GAMEBATCH_H

#include "raengine_global.h"
#include <glm/vec3.hpp>

class QPainter;
class GameWindow;

class RAENGINESHARED_EXPORT gameBatch
{
public:
    gameBatch(GameWindow *wnd) : m_pWnd(wnd) { }
    void drawText(QPainter *painter, const glm::vec3 &textPosWorld, QString text);

private:
    GameWindow *m_pWnd;
};



#endif // GAMEBATCH_H
