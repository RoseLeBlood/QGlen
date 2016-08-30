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
#include "dreieckgamestate.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

Camera *cam;
DreieckGameState::DreieckGameState(qglen::GameWindow *wnd)
    : qglen::GameState(wnd, "Basic")
{
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    qglen::Material mat[] = {
        qglen::Materials::Gold,
        qglen::Materials::Chrome,
        qglen::Materials::Brass,
        qglen::Materials::Obsidiant,
        qglen::Materials::BlackRubber,
        qglen::Materials::Silver,
        qglen::Materials::Bronze,
        qglen::Materials::Copper,
        qglen::Materials::Jade,
        qglen::Materials::Turquise
    };
    for(int i=0; i < 10; i++ )
    {
        AddObjectToScene(new DreieckObject("Quad_" + QString::number(i), wnd, cubePositions[i],
                                           mat[i]));
    }

      // AddObjectToScene(new Camera("camera", wnd));
    cam = new Camera(wnd);

}
bool DreieckGameState::Initialize()
{
     m_pStrem =new QtOpenalOggStream("teststrem", this->GetGameWindow()->getOpenAlContext());
     m_pStrem->LoadFile("test.ogg");
     m_pStrem->Play();
     m_pStrem->getSource()->setPosition(glm::vec3(0,0,0));

    return GameState::Initialize();
}
bool DreieckGameState::Move(qglen::GamePadState *pStates, int numDevices, double renderTime, double elapsedTime, bool lag)
{
    cam->Update(pStates, numDevices, elapsedTime);

    glm::vec3 pos = glm::vec3(cam->getPosition().x, 0, cam->getPosition().y);
    GetGameWindow()->getOpenAlContext()->setPosition(pos);

    GetGameWindow()->getOpenAlContext()->setOrientation(glm::vec3(std::cos(0)*100.0f, 100.0f,
                                                                sin(0)*100.0f));

    m_pStrem->Update();

    m_matView = cam->getView();
    m_matProjection = cam->getProjektion();


    return qglen::GameState::Move(pStates, numDevices, renderTime, elapsedTime, lag);
}
