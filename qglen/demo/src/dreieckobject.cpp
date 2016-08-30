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
#include "basicshader.h"
#include "dreieckobject.h"

#include <QOpenGLFunctions>
#include "colorpositionvertex.h"

#include <glm/glm.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <colors.h>
#include "camera.h"

qglen::PointLight pointlight[] = {
    qglen::PointLight(qglen::Color(0.05f, 0.05f, 0.05f), qglen::Color(0.05f, 0.05f, 0.05f),
                      qglen::Colors::Black, glm::vec3( 4.7f,  3.2f,  2.0f)),

    qglen::PointLight(qglen::Color(0.05f, 0.05f, 0.05f), qglen::Color(0.05f, 0.05f, 0.05f),
                      qglen::Colors::Black, glm::vec3( 2.3f, -3.3f, -4.0f)),

    qglen::PointLight(qglen::Color(0.05f, 0.05f, 0.05f), qglen::Color(0.05f, 0.05f, 0.05f),
                      qglen::Colors::Black, glm::vec3(-6.0f,  2.0f, -2.0f)),

    qglen::PointLight(qglen::Color(0.05f, 0.05f, 0.05f), qglen::Color(0.05f, 0.05f, 0.05f),
                      qglen::Colors::Black, glm::vec3( 4.0f,  4.0f, -3.0f)),
};

GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };


#include <shaderlist.h>
#include "colors.h"

glm::mat4 matModel;

DreieckObject::DreieckObject(QString name,qglen::GameWindow* window, glm::vec3 pos, qglen::Material mat)
    : qglen::IObject(name, window, mat)
{
    m_Position = glm::vec3(0, 0, 0);
    m_Position = pos;
    matModel = glm::translate(glm::mat4(1.0f), m_Position);
}


bool DreieckObject::Initialize()
{
    // Create Buffer (Do not release until VAO is created)
    m_vertex.create();
    m_vertex.bind();
    m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertex.allocate(vertices, sizeof(vertices));

    // Create Vertex Array Object
    m_object.create();
    m_object.bind();

    GetGameWindow()->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    GetGameWindow()->glEnableVertexAttribArray(0);
    // Normal attribute
    GetGameWindow()->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    GetGameWindow()->glEnableVertexAttribArray(1);

    // Release (unbind) all
    m_object.release();
    m_vertex.release();

    GetGameWindow()->glEnable(GL_DEPTH_TEST);
    GetGameWindow()->glEnable(GL_FRAMEBUFFER_SRGB);
    //GetGameWindow()->glDisable(GL_CULL_FACE);
    GetGameWindow()->setClearColor(qglen::Colors::Black);

    return true;
}

bool DreieckObject::Destroy()
{
    return true;
}


glm::vec3 ExtractCameraPos(const glm::mat4 & a_modelView)
{
  glm::mat4 modelViewT = transpose(a_modelView);

  // Get plane normals
  glm::vec3 n1(modelViewT[0]);
  glm::vec3 n2(modelViewT[1]);
  glm::vec3 n3(modelViewT[2]);

  // Get plane distances
  float d1(modelViewT[0].w);
  float d2(modelViewT[1].w);
  float d3(modelViewT[2].w);

  // Get the intersection of these 3 planes
  // http://paulbourke.net/geometry/3planes/
  glm::vec3 n2n3 = glm::cross(n2, n3);
  glm::vec3 n3n1 = glm::cross(n3, n1);
  glm::vec3 n1n2 = glm::cross(n1, n2);

  glm::vec3 top = (n2n3 * d1) + (n3n1 * d2) + (n1n2 * d3);
  float denom = dot(n1, n2n3);

  return top / -denom;
}
void DreieckObject::Render(qglen::BasicEffect* effect, const glm::mat4& pView, const glm::mat4& pProj, double smoothStep)
{

    qglen::DirLight l(qglen::Color(1.0f, 1.0f, 1.0f), qglen::Color(1.0f, 1.0f, 1.0f) ,
               qglen::Color(1.0f, 1.0f, 1.0f));
    //l.setPosition(glm::vec3(1.2f, 1.0f, 2.0f));
    //l.setEnable(true);

    m_object.bind();
    effect->Setup(this->getMaterial(), l, pointlight,pView, pProj, glm::translate(glm::mat4(1.0f), m_Position));

    effect->setViewPosition(ExtractCameraPos(pView));

    GetGameWindow()->glDrawArrays(GL_TRIANGLES, 0, 36);

    m_object.release();

}
