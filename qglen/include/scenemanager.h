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
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H


#include "list"

#include <glm/mat4x4.hpp>
#include "light.h"
#include "gamewindow.h"

class QPainter;
QGLEN_BEGIN

class IObject;
class BasicEffect;

class RAENGINESHARED_EXPORT SceneManager
{
public:
    SceneManager(GameWindow* pWnd);

    virtual bool Initialize();
    virtual bool Destroy();

    virtual bool Render(BasicEffect* effect, const glm::mat4& pView, const glm::mat4& pProj,
                        double smoothStep);

    virtual bool Move(GamePadState *pStates, int numDevices, double renderTime, double elapsedTime, bool lag);
    void AddObjectToScene(IObject* obj);
    GameWindow* GetGameWindow() { return m_pWnd; }
protected:
     GameWindow* m_pWnd;
private:
     std::list<IObject*>  m_GameStates;
     DirLight             m_pDirLights[4];

};
QGLEN_END

#endif // SCENEMANAGER_H
