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

void BasicEffect::Setup(Material m, DirLight l, PointLight points[],
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
                                                       m.getAmbient().b
                                                       );
       m_pShader->setUniformValue("material.diffuse", m.getDiffuse().r,
                                       m.getDiffuse().g,
                                       m.getDiffuse().b);
        m_pShader->setUniformValue("material.specular", m.getSpecular().r,
                                       m.getSpecular().g,
                                       m.getSpecular().b);

        m_pShader->setUniformValue("material.emission", m.getEmission().r,
                                       m.getEmission().g,
                                       m.getEmission().b);
        m_pShader->setUniformValue("material.shininess", m.getShininess());


        m_pShader->setUniformValue("dirLight.ambient", l.getAmbient().r,
                                                    l.getAmbient().g,
                                                    l.getAmbient().b);
        m_pShader->setUniformValue("dirLight.diffuse", l.getDiffuse().r,
                                                    l.getDiffuse().g,
                                                    l.getDiffuse().b);

        m_pShader->setUniformValue("dirLight.specular", l.getSpecular().r,
                                                    l.getSpecular().g,
                                                    l.getSpecular().b);

        m_pShader->setUniformValue("dirLight.direction", l.getDirection().x,
                                                     l.getDirection().y,
                                                     l.getDirection().z);

        for(int i=0; i < 4; i++)
        {
            points[i].setEnable(true);

            std::string number = QString::number(i).toStdString();

            m_pShader->setUniformValue(("pointLights[" + number + "].position").c_str(),
                                                                          points[i].getPosition().x,
                                                                          points[i].getPosition().y,
                                                                          points[i].getPosition().z);
            m_pShader->setUniformValue(("pointLights[" + number + "].ambient").c_str(),
                                                                          points[i].getAmbient().r,
                                                                          points[i].getAmbient().g,
                                                                          points[i].getAmbient().b);
            m_pShader->setUniformValue(("pointLights[" + number + "].diffuse").c_str(),
                                                                          points[i].getDiffuse().r,
                                                                          points[i].getDiffuse().g,
                                                                          points[i].getDiffuse().b);
            m_pShader->setUniformValue(("pointLights[" + number + "].specular").c_str(),
                                                                          points[i].getSpecular().r,
                                                                          points[i].getSpecular().g,
                                                                          points[i].getSpecular().b);

            m_pShader->setUniformValue(("pointLights[" + number + "].constant").c_str(),
                                       points[i].getConstant());
            m_pShader->setUniformValue(("pointLights[" + number + "].linear").c_str(),
                                       points[i].getLinear());
            m_pShader->setUniformValue(("pointLights[" + number + "].quadratic").c_str(),
                                       points[i].getQuadratic());

            m_pShader->setUniformValue(("pointLights[" + number + "].enable").c_str(),
                                       points[i].IsEnable());

        }

    }
}
void BasicEffect::setViewPosition(glm::vec3 pos)
{
    m_pShader->setUniformValue("viewPos", pos.x, pos.y, pos.z);
}

QGLEN_END
