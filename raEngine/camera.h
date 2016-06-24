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

#ifndef ICAMERA_H
#define ICAMERA_H

#include "iobject.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameWindow;

namespace CameraDirection
{
    enum CameraDirection_t
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        FORWARD,
        BACK,

        MouseLeft,
        MouseRight,
        MouseMiddle,
        MouseExtra1,
        MouseExtra2,
    };
}
namespace CameraType
{
    enum CameraType_t
    {
        Free,
        Ortho
    };
}
class RAENGINESHARED_EXPORT Camera : public IObject
{
public:
    Camera() { }
    Camera(QString strName, GameWindow* gameWnd);
    ~Camera();

    virtual bool CanUpdate() { return true; }
    virtual bool CanDraw() { return false; }
    virtual SceneManagerPrio::SceneManagerPrio_t
        Prio() { return SceneManagerPrio::Five; }

    virtual bool Initialize();
    virtual bool Destroy();

    virtual void Reset();
    virtual void Input(CameraDirection::CameraDirection_t dir, float value);
    virtual void Move(double renderTime, double elapsedTime);
    virtual void Render(QPainter *painter, double smoothStep);



    virtual void Input() { }


    //Change the pitch (up, down) for the free camera
   virtual  void ChangePitch(float degrees);
    //Change heading (left, right) for the free camera
    virtual void ChangeHeading(float degrees);

    //Change the heading and pitch of the camera based on the 2d movement of the mouse
    virtual void Move2D(int x, int y);

    //Setting Functions
    //Changes the camera mode, only three valid modes, Ortho, Free, and Spherical
    virtual void SetMode(CameraType::CameraType_t cam_mode);

    virtual void SetPosition(glm::vec3 pos) { camera_position = pos; }
    virtual void SetLookAt(glm::vec3 pos)   { camera_look_at = pos; }
    virtual void SetFOV(double fov)         { field_of_view = fov; }
    //Change the viewport location and size
    virtual void SetViewport(int loc_x, int loc_y, int width, int height);
    //Change the clipping distance for the camera
    virtual void SetClipping(double near_clip_distance, double far_clip_distance);

    //virtual void SetDistance(double cam_dist);
    virtual void SetPos(CameraDirection::CameraDirection_t mouseButton, bool down, int x, int y);

    virtual void GetViewport(int &loc_x, int &loc_y, int &width, int &height);
    virtual void GetMatricies(glm::mat4 &P, glm::mat4 &V, glm::mat4 &M);

  private:
    CameraType::CameraType_t m_cam_mode;

    int viewport_x;
    int viewport_y;

    int window_width;
    int window_height;

    double aspect;
    double field_of_view;
    double near_clip;
    double far_clip;

    float camera_scale;
    float camera_heading;
    float camera_pitch;

    float max_pitch_rate;
    float max_heading_rate;
    bool  move_camera;

    glm::vec3 camera_position;
    glm::vec3 camera_position_delta;
    glm::vec3 camera_look_at;
    glm::vec3 camera_direction;

    glm::vec3 camera_up;
    glm::quat rotation_quaternion;
    glm::vec3 mouse_position;

    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;
    glm::mat4 MVP;
};

#endif // ICAMERA_H
