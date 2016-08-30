#ifndef CAMERA_H
#define CAMERA_H

#include "glm/gtc/quaternion.hpp"
#include "glm/mat4x4.hpp"

#include "gamewindow.h"
#include "iobject.h"

#include <glm/glm.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

class Camera
{
public:
    Camera(qglen::GameWindow* window, glm::vec3 position = glm::vec3(0,0,-5));

    virtual void Update(qglen::GamePadState *pStates, int, double elapsedTime);

    void Yaw(float yaw);
    void Pitch(float pitch);
    void Roll(float roll);
    void Move(float x, float y);

    glm::mat4 getView() { return m_matView; }
    glm::mat4 getProjektion() { return m_matProj; }
    glm::vec3 getPosition() { return m_vecPositition; }
    glm::vec3 getDirection() { return m_vecDirection; }
private:
    glm::quat  m_caQuat;
    glm::mat4 m_matView;
    glm::mat4 m_matProj;
    glm::vec3 m_vecPositition;
    glm::vec3 m_vecVelocity;
    glm::vec3 m_vecDirection;

    float m_fYaw;
    float m_fPitch;
    float m_fRoll;
    float m_fSensetive;

    qglen::GameWindow* m_pWindow;
};

#endif // CAMERA_H
