#include "include/camera.h"

Camera::Camera(qglen::GameWindow* wnd, glm::vec3 position) : m_pWindow(wnd)
{
    m_fSensetive = 0.125f;
    m_fYaw = 0.0f;
    m_fPitch = 0.0f;
    m_fRoll = 0.0f;
    m_vecPositition = position;
}
void Camera::Update(qglen::GamePadState *pStates, int, double elapsedTime)
{
    glm::vec3 temp = m_vecPositition;
     Move( (float)(pStates->axisRightX / elapsedTime),
                        -(float)(pStates->axisRightY / elapsedTime));
     Yaw((float)(pStates->axisLeftY / elapsedTime));
     Pitch((float)(pStates->axisLeftX / elapsedTime));
     Roll( (float)(pStates->buttonL2 / 300.0f / elapsedTime));
     Roll( (float)(-pStates->buttonR2 / 300.0f / elapsedTime));

     glm::quat key_quat = glm::quat(glm::vec3(m_fYaw, m_fPitch, m_fRoll));
     m_caQuat = key_quat * m_caQuat;
     m_caQuat = glm::normalize(m_caQuat);
     glm::mat4 rotate = glm::mat4_cast(m_caQuat);

     glm::mat4 translate = glm::mat4(1.0f);
     translate = glm::translate(translate, m_vecPositition);

     m_matView = rotate * translate;
     m_matProj = glm::perspective(45.0f, ((float)(m_pWindow->width() / m_pWindow->height())), 0.1f, 100.f);

     m_vecVelocity = m_vecPositition - temp;

     glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
     m_vecDirection = glm::normalize(m_vecPositition - cameraTarget);

}
void Camera::Yaw(float yaw)
{
   m_fYaw = m_fSensetive * yaw;
}
void Camera::Pitch(float pitch)
{
    m_fPitch = m_fSensetive * pitch;


}
void Camera::Roll(float roll)
{
    m_fRoll +=  m_fSensetive * roll;  //m_fSensetive *  (left ? roll : roll);
}
void Camera::Move(float x, float y)
{
    glm::vec3 forward(m_matView[0][2], m_matView[1][2], m_matView[2][2]);
    glm::vec3 strafe( m_matView[0][0], m_matView[1][0], m_matView[2][0]);
    m_vecPositition +=  glm::vec3(y * forward + x * strafe) * 0.25f;
}
