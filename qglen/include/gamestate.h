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

    virtual bool Render(double smoothStep); //
    virtual bool Move(GamePadState *pStates, int numDevices, double renderTime, double elapsedTime, bool lag); //

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
