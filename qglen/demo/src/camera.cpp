#include "include/camera.h"

Camera::Camera(qglen::GameWindow* wnd, glm::vec3 position) : m_pWindow(wnd)
{
    m_fSensetive = 0.125f;
    m_vecPositition = position;
}
