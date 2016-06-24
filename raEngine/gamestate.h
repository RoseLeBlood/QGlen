#ifndef GAMESTATE_H
#define GAMESTATE_H


#include "scenemanager.h"

class QPainter;
class QString;

class GameWindow;

class RAENGINESHARED_EXPORT GameState
{
public:
    GameState(GameWindow* pWnd);

    virtual bool Initialize();
    virtual bool Destroy();
    virtual bool Switch(bool next, GameState* pOld)  = 0;

    virtual bool Render(QPainter *painter, double smoothStep); //
    virtual bool Move(double renderTime, double elapsedTime); //
    virtual bool Input();
    GameWindow* GetGameWindow()
        { return m_pGameWindow; }

    void SetSceneManager(SceneManager* pScene) { m_Scene = pScene; }
    void AddObjectToScene(IObject* pObject);

protected:
    SceneManager* GetSceneManager() { return m_Scene; }
protected:
    SceneManager                 *m_Scene;
    GameWindow                   *m_pGameWindow;
};

#endif // GAMESTATE_H
