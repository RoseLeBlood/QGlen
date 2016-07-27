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
#include <QPainter>
#include "gamewindow.h"
#include "gamestatemanager.h"
#include <QDebug>
QGLEN_BEGIN
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
        qInfo() << "Add GameState " << name << "to GameStateManager";
        return true;
    }
    qInfo() << "GameState " << name << "allready in GameStateManager";

    return false;
}
bool GameStateManager::Initialize()
{
    if(m_pCurrent != 0)
    {
        return m_pCurrent->Initialize();
    }
    return true;
}
bool GameStateManager::Destroy()
{
    if(m_pCurrent != 0)
    {
       return m_pCurrent->Destroy();
    }
    return true;
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
bool GameStateManager::Render(double smoothStep)
{
    if(m_pCurrent != 0)
    {
       return m_pCurrent->Render(smoothStep);
    }
    return false;
}

bool GameStateManager::Move(GamePadState *pStates, int numDevices,double renderTime, double elapsedTime, bool lag)
{
    if(m_pCurrent != 0)
    {
       return m_pCurrent->Move(pStates, numDevices, renderTime, elapsedTime, lag );
    }
    return false;
}
QGLEN_END
