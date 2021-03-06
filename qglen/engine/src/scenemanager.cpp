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
#include "gamewindow.h"
#include "scenemanager.h"
#include "iobject.h"
#include "basicshader.h"
QGLEN_BEGIN

SceneManager::SceneManager(GameWindow* _pWnd)
{
    m_pWnd = _pWnd;
}
bool SceneManager::Initialize()
{
    for (std::list<IObject*>::iterator item = m_GameStates.begin();
         item != m_GameStates.end();
         item++)
    {
        IObject* object = ((IObject*)(*item));
        if(object != NULL)
        {
            object->Initialize();
        }
    }
    return true;
}
bool SceneManager::Destroy()
{
    for (std::list<IObject*>::iterator item = m_GameStates.begin();
         item != m_GameStates.end();
         item++)
    {
        IObject* object = ((IObject*)(*item));
        if(object != NULL)
        {
            object->Destroy();
        }
    }

    m_GameStates.clear();

    return true;
}

bool SceneManager::Render(BasicEffect* effect, const glm::mat4& pView, const glm::mat4& pProj, double smoothStep)
{
    for(int i= 0; i < SceneManagerPrio::MAX; i++)
    {
        for (std::list<IObject*>::iterator item = m_GameStates.begin();
             item != m_GameStates.end();
             item++)
        {
            IObject* object = ((IObject*)(*item));
            if(object != NULL)
            {
                if( object->Prio() == i)
                {
                    if(object->CanDraw())
                        object->Render(effect, pView, pProj, smoothStep);
                }
            }
        }
    }
    return true;
}

bool SceneManager::Move(GamePadState *pStates, int numDevices, double renderTime, double elapsedTime, bool lag)
{

    for (std::list<IObject*>::iterator item = m_GameStates.begin();
         item != m_GameStates.end();
         item++)
    {
        IObject* object = ((IObject*)(*item));
        if(object != NULL )
        {
            if(object->CanUpdate())
                object->Move(pStates, numDevices, renderTime, elapsedTime, lag);
        }
    }
    return true;
}
void SceneManager::AddObjectToScene(IObject* obj)
{
    m_GameStates.push_back(obj);
}
QGLEN_END
