#include "include/basicshader.h"
#include "include/shaderlist.h"
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

QGLEN_BEGIN
BasicEffect::BasicEffect(GameWindow* wnd, QString shaderName)
{
    m_wnd = wnd;
    this->m_pShader = ShaderList::instance()->GetByName("Basic");
}

void BasicEffect::Setup(Material m, Light *lights, int num,
                        glm::mat4 view, glm::mat4 proj, glm::mat4 model)
{
    //BIND(m_pShader)
    {

       m_wnd->glUniformMatrix4fv(m_pShader->uniformLocation("view"),
                                                 1, GL_FALSE, glm::value_ptr(view));
       m_wnd->glUniformMatrix4fv(m_pShader->uniformLocation("projection"),
                                                 1, GL_FALSE, glm::value_ptr(proj));
        m_wnd->glUniformMatrix4fv(m_pShader->uniformLocation("model"),
                                                 1, GL_FALSE, glm::value_ptr(model));


        m_pShader->setUniformValue("material.ambient", m.getAmbient().r,
                                                       m.getAmbient().g,
                                                       m.getAmbient().b);
        m_pShader->setUniformValue("material.diffuse", m.getAmbient().r,
                                       m.getAmbient().g,
                                       m.getAmbient().b);
        m_pShader->setUniformValue("material.specular", m.getAmbient().r,
                                       m.getAmbient().g,
                                       m.getAmbient().b);
        m_pShader->setUniformValue("material.emission", m.getEmission().r,
                                       m.getEmission().g,
                                       m.getEmission().b);
        m_pShader->setUniformValue("material.shininess", m.getShininess());


        Light l = lights[0];
        m_pShader->setUniformValue("light.ambient", l.getAmbient().r,
                                                    l.getAmbient().g,
                                                    l.getAmbient().b);
        m_pShader->setUniformValue("light.diffuse", l.getDiffuse().r,
                                                    l.getDiffuse().g,
                                                    l.getDiffuse().b);
        m_pShader->setUniformValue("light.specular", l.getSpecular().r,
                                                    l.getSpecular().g,
                                                    l.getSpecular().b);

        m_pShader->setUniformValue("light.position", l.getPosition().x,
                                                     l.getPosition().y,
                                                     l.getPosition().z);
       // m_pShader->setUniformValue("light.enable", (l.IsEnable() ? 1 : 0));

    }
}
void BasicEffect::setViewPosition(glm::vec3 pos)
{
    m_pShader->setUniformValue("viewPos", pos.x, pos.y, pos.z);
}

QGLEN_END
