#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "raengine_global.h"
#include <qstring.h>
#include <map>
#include "gamestate.h"

class GameWindow;

class GameStateManager
{
public:
    explicit GameStateManager(GameWindow* pGame);
    ~GameStateManager();

    bool Initialize();
    bool Destroy();

    bool Add(QString name, GameState *pGameState);
    void Remove(QString name);
    void Reset();

    bool Render(QPainter *painter, double smoothStep);
    bool Move(double renderTime, double elapsedTime);
    void Switch(QString name);
    void Input();

    GameState* GetGameStateByName(QString name);
private:
    void Switch(GameState *pState);
private:
    std::map<QString, GameState*>  m_GameStates;
    GameState                      *m_pCurrent;
    GameWindow                     *m_pGameWindow;
};

#endif // GAMESTATEMANAGER_H
