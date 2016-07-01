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
#include "camera.h"

Camera::Camera(QString strName, GameWindow *gameWnd) : IObject(strName, gameWnd),
      m_cam_mode(CameraType::Free),
      camera_up(glm::vec3(0, 1, 0)),
      field_of_view(45),
      rotation_quaternion(glm::quat(1, 0, 0, 0)),
      camera_position_delta(glm::vec3(0, 0, 0)),
      camera_scale(.5f),
      max_pitch_rate(5),
      max_heading_rate(5),
      move_camera(false)
{

}
void Camera::Reset()
{
    camera_up = glm::vec3(0, 1, 0);
}
bool Camera::Destroy()
{
    return true;
}
bool Camera::Initialize()
{
    return true;
}
void Camera::Render(double )
{

}

void Camera::SetViewport(int loc_x, int loc_y, int width, int height)
{
    viewport_x = loc_x;
    viewport_y = loc_y;
    window_width = width;
    window_height = height;
    //need to use doubles division here, it will not work otherwise and it is possible to get a zero aspect ratio with integer rounding
    aspect = double(width) / double(height);
}
void Camera::SetClipping(double near_clip_distance, double far_clip_distance)
{
    near_clip = near_clip_distance;
    far_clip = far_clip_distance;
}
void Camera::GetViewport(int &loc_x, int &loc_y, int &width, int &height)
{
    loc_x = viewport_x;
    loc_y = viewport_y;
    width = window_width;
    height = window_height;
}

void Camera::GetMatricies(glm::mat4 &P, glm::mat4 &V, glm::mat4 &M)
{
    P = projection;
    V = view;
    M = model;
}
void Camera::Move(double renderTime, double elapsedTime)
{
    return ;

    camera_direction = glm::normalize(camera_look_at - camera_position);
    //need to set the matrix state. this is only important because lighting doesn't work if this isn't done
    //glMatrixMode(GL_PROJECTION);
   // glLoadIdentity();
    //glViewport(viewport_x, viewport_y, window_width, window_height);

    if (m_cam_mode == CameraType::Ortho) {
        //our projection matrix will be an orthogonal one in this case
        //if the values are not floating point, this command does not work properly
        //need to multiply by aspect!!! (otherise will not scale properly)
        projection = glm::ortho(-1.5f * float(aspect), 1.5f * float(aspect), -1.5f, 1.5f, -10.0f, 10.f);
    } else if (m_cam_mode == CameraType::Free) {
        projection = glm::perspective(field_of_view, aspect, near_clip, far_clip);
        //detmine axis for pitch rotation
        glm::vec3 axis = glm::cross(camera_direction, camera_up);
        //compute quaternion for pitch based on the camera pitch angle
        glm::quat pitch_quat = glm::angleAxis(camera_pitch, axis);
        //determine heading quaternion from the camera up vector and the heading angle
        glm::quat heading_quat = glm::angleAxis(camera_heading, camera_up);
        //add the two quaternions
        glm::quat temp = glm::cross(pitch_quat, heading_quat);
        temp = glm::normalize(temp);
        //update the direction from the quaternion
        camera_direction = glm::rotate(temp, camera_direction);
        //add the camera delta
        camera_position += camera_position_delta;
        //set the look at to be infront of the camera
        camera_look_at = camera_position + camera_direction * 1.0f;
        //damping for smooth camera
        camera_heading *= .5;
        camera_pitch *= .5;
        camera_position_delta = camera_position_delta * .8f;
    }
    //compute the MVP
    view = glm::lookAt(camera_position, camera_look_at, camera_up);
    model = glm::mat4(1.0f);
    MVP = projection * view * model;
    glLoadMatrixf(glm::value_ptr(MVP));
}
void Camera::SetMode(CameraType::CameraType_t cam_mode) {
    m_cam_mode = cam_mode;
    camera_up = glm::vec3(0, 1, 0);
    rotation_quaternion = glm::quat(1, 0, 0, 0);
}
void Camera::Input(CameraDirection::CameraDirection_t dir, float value)
{
    if (m_cam_mode == CameraType::Free) {
        switch (dir) {
            case CameraDirection::UP:
                camera_position_delta += camera_up * value;
                break;
            case CameraDirection::DOWN:
                camera_position_delta -= camera_up * value;
                break;
            case CameraDirection::LEFT:
                camera_position_delta -= glm::cross(camera_direction, camera_up) * value;
                break;
            case CameraDirection::RIGHT:
                camera_position_delta += glm::cross(camera_direction, camera_up) * value;
                break;
            case CameraDirection::FORWARD:
                camera_position_delta += camera_direction * value;
                break;
            case CameraDirection::BACK:
                camera_position_delta -= camera_direction * value;
                break;
        }
    }
}
void Camera::ChangePitch(float degrees)
{
    //Check bounds with the max pitch rate so that we aren't moving too fast
    if (degrees < -max_pitch_rate)
    {
        degrees = -max_pitch_rate;
    } else if (degrees > max_pitch_rate)
    {
        degrees = max_pitch_rate;
    }
    camera_pitch += degrees;

    //Check bounds for the camera pitch
    if (camera_pitch > 360.0f)
    {
        camera_pitch -= 360.0f;
    } else if (camera_pitch < -360.0f)
    {
        camera_pitch += 360.0f;
    }
}
void Camera::ChangeHeading(float degrees)
{
    //Check bounds with the max heading rate so that we aren't moving too fast
    if (degrees < -max_heading_rate)
    {
        degrees = -max_heading_rate;
    }
    else if (degrees > max_heading_rate)
    {
        degrees = max_heading_rate;
    }
    //This controls how the heading is changed if the camera is pointed straight up or down
    //The heading delta direction changes
    if (camera_pitch > 90 && camera_pitch < 270 || (camera_pitch < -90 && camera_pitch > -270))
    {
        camera_heading -= degrees;
    }
    else
    {
        camera_heading += degrees;
    }
    //Check bounds for the camera heading
    if (camera_heading > 360.0f)
    {
        camera_heading -= 360.0f;
    }
    else if (camera_heading < -360.0f)
    {
        camera_heading += 360.0f;
    }
}
void Camera::Move2D(int x, int y)
{
    glm::vec3 mouse_delta = mouse_position - glm::vec3(x, y, 0);

    if(move_camera)
    {
        ChangeHeading(.08f * mouse_delta.x);
        ChangePitch(.08f * mouse_delta.y);
    }
    mouse_position = glm::vec3(x, y, 0);
}
void Camera::SetPos(CameraDirection::CameraDirection_t mouseButton, bool down, int x, int y)
{
    if (mouseButton == CameraDirection::MouseExtra1 && down)
    {
        camera_position_delta += camera_up * .05f;
    }
    else if (mouseButton == CameraDirection::MouseExtra2 && down)
    {
        camera_position_delta -= camera_up * .05f;
    }
    else if (mouseButton == CameraDirection::MouseLeft && down)
    {
        move_camera = true;
    }
    else if (mouseButton == CameraDirection::MouseLeft && !down)
    {
        move_camera = false;
    }
    mouse_position = glm::vec3(x, y, 0);
}
