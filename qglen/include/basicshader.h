#ifndef BASICSHADER_H
#define BASICSHADER_H

#include <raengine_global.h>
#include <openglshaderprogram.h>

#include <QString>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <colorpositionsnormalvertex.h>
#include <color.h>
#include "iobject.h"
#include "light.h"
#include "material.h"
#include "gamewindow.h"

QGLEN_BEGIN

class RAENGINESHARED_EXPORT BasicEffect
{
public:
    BasicEffect(GameWindow* wnd, QString shaderName);
    BasicEffect(GameWindow *wnd, OpenGLShaderProgram* prg)
        : m_pShader(prg), m_wnd(wnd) {}

    void setViewPosition(glm::vec3 pos);
    void setGamma(float gamma) { m_pShader->setUniformValue("gamma", gamma); }
    virtual void Setup(Material mat, Light *lights, int num,
                       glm::mat4 view, glm::mat4 proj, glm::mat4 model);

    OpenGLShaderProgram* getProgram() { return m_pShader; }

    operator OpenGLShaderProgram*() { return m_pShader; }
private:
    OpenGLShaderProgram *m_pShader;
    GameWindow         *m_wnd;
};

QGLEN_END

#endif // BASICSHADER_H
