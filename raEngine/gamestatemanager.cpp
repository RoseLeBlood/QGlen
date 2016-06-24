#include <QPainter>
#include "gamewindow.h"
#include "gamestatemanager.h"

GameStateManager::GameStateManager(GameWindow *pGame)
    : m_pGameWindow(pGame),
      m_pCurrent(0)
{
    m_GameStates = std::map<QString, GameState*>();
}
GameStateManager::~GameStateManager()
{
    m_pGameWindow = 0;
}
bool GameStateManager::Add(QString name, GameState *pGameState)
{
    if(GetGameStateByName(name) == 0)
    {
        m_GameStates.insert(std::make_pair(name, pGameState));

        if(m_pCurrent == 0)
            m_pCurrent = pGameState;

        return true;
    }
    return false;
}
bool GameStateManager::Initialize()
{
    if(m_pCurrent != 0)
    {
        m_pCurrent->Initialize();
    }
}
bool GameStateManager::Destroy()
{
    if(m_pCurrent != 0)
    {
        m_pCurrent->Destroy();
    }
}

void GameStateManager::Remove(QString name)
{
    GameState* state = GetGameStateByName(name);
    if(state != 0)
    {
        if(m_pCurrent == state)
            return;

        state->Destroy();

        m_GameStates.erase(name);
    }
}
void GameStateManager::Reset()
{
    m_pCurrent = 0;
    m_GameStates.clear();
}

void GameStateManager::Switch(QString name)
{
    Switch(GetGameStateByName(name));
}
GameState* GameStateManager::GetGameStateByName(QString name)
{
    return m_GameStates[name];
}


void GameStateManager::Switch(GameState *pState)
{
    GameState* pOld = m_pCurrent;

    if(pState == 0) return;

    if(m_pCurrent != 0)
    {
        m_pCurrent->Switch(false, 0);
        m_pCurrent->Destroy();
    }
    m_pCurrent = pState;

    m_pCurrent->Switch(true, pOld);
    Initialize();
}
bool GameStateManager::Render(QPainter *painter, double smoothStep)
{
    if(m_pCurrent != 0)
    {
       return m_pCurrent->Render(painter, smoothStep);
    }
    return false;
}
void GameStateManager::Input()
{
    if(m_pCurrent != 0)
    {
       m_pCurrent->Input();
    }
}

bool GameStateManager::Move(double renderTime, double elapsedTime)
{
    if(m_pCurrent != 0)
    {
       return m_pCurrent->Move(renderTime, elapsedTime );
    }
    return false;
}
