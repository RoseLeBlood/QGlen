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
DreieckGameState::DreieckGameState(qglen::GameWindow *wnd) : qglen::GameState(wnd)
{
      AddObjectToScene(new DreieckObject(wnd));
     // AddObjectToScene(new Camera("camera", wnd));
    cam = new Camera(wnd);



}
bool DreieckGameState::Initialize()
{


    return GameState::Initialize();
}

glm::vec3 g_Position = glm::vec3(0,0,-5);

glm::quat    camera_quat;

glm::vec2 rotate(float x, float y)
{
    float yaw = 0, pitch = 0;

    const float mouse_Sensitivity = 0.125f;

    yaw += mouse_Sensitivity *x;
    pitch += mouse_Sensitivity * y;
    return glm::vec2(yaw, pitch);
}
glm::vec3 move(float x, float y, glm::mat4 view)
{
    glm::vec3 forward(view[0][2], view[1][2], view[2][2]);
    glm::vec3 strafe( view[0][0], view[1][0], view[2][0]);
    return glm::vec3(y * forward + x * strafe) * 0.25f;
}


bool DreieckGameState::Move(qglen::GamePadState *pStates, int numDevices, double renderTime, double elapsedTime, bool lag)
{
    cam->Update(pStates, numDevices, elapsedTime);

    m_matView = cam->getView();
    m_matProjection = cam->getProjektion();

    /*
   g_Position += move( (float)(pStates->axisRightX / elapsedTime),
                       -(float)(pStates->axisRightY / elapsedTime), m_matView);

    glm::vec2 yp = rotate((float)(pStates->axisLeftY / elapsedTime),
                        (float)(pStates->axisLeftX / elapsedTime));

    if(pStates->buttonA)
    {
        g_Position = glm::vec3(0,0,-5);
        yp = glm::vec2(0,0);
    }
    glm::quat key_quat = glm::quat(glm::vec3(yp.x, yp.y, 0));
    camera_quat = key_quat * camera_quat;
    camera_quat = glm::normalize(camera_quat);
    glm::mat4 rotate = glm::mat4_cast(camera_quat);

    glm::mat4 translate = glm::mat4(1.0f);
    translate = glm::translate(translate, g_Position);

    m_matView = rotate * translate;
    m_matProjection = glm::perspective(45.0f, ((float)(GetGameWindow()->width() / GetGameWindow()->height())), 0.1f, 100.f);
*/

    return qglen::GameState::Move(pStates, numDevices, renderTime, elapsedTime, lag);
}
