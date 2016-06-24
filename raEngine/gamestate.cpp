#include "gamestate.h"
#include <QPainter>
#include <QString>
#include <map>
#include "gamewindow.h"

GameState::GameState(GameWindow* pWnd)
{
    m_Scene = new SceneManager(pWnd);
    m_pGameWindow = pWnd;
}
bool GameState::Initialize()
{
    return m_Scene->Initialize();
}
bool GameState::Destroy()
{
   return  m_Scene->Destroy();
}

bool GameState::Render(QPainter *painter, double smoothStep)
{
    return m_Scene->Render(painter, smoothStep);
}

bool GameState::Move(double renderTime, double elapsedTime)
{
    return m_Scene->Move(renderTime, elapsedTime);;
}
void GameState::AddObjectToScene(IObject* pObject)
{
    m_Scene->AddObjectToScene(pObject);
}
bool GameState::Input()
{
    return m_Scene->Input();;
}
