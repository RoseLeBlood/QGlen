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
#include "gamestate.h"
#include <QPainter>
#include <QString>
#include <map>
#include "gamewindow.h"

QGLEN_BEGIN

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

bool GameState::Render(double smoothStep)
{
    return m_Scene->Render(m_matView, m_matProjection, smoothStep);
}

bool GameState::Move(GamePadState *pStates, int numDevices, double renderTime, double elapsedTime, bool lag)
{
    return m_Scene->Move(pStates, numDevices, renderTime, elapsedTime, lag);;
}
void GameState::AddObjectToScene(IObject* pObject)
{
    m_Scene->AddObjectToScene(pObject);
}
QGLEN_END
