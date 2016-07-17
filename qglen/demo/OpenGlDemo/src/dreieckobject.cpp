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
#include "dreieckobject.h"

#include <QOpenGLFunctions>
#include "colorpositionvertex.h"

#include <glm/glm.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective



// Front Verticies
#define VERTEX_FTR qglen::ColorPositionVertex( glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f, 0.0f, 0.0f ) )
#define VERTEX_FTL qglen::ColorPositionVertex( glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f, 1.0f, 0.0f ) )
#define VERTEX_FBL qglen::ColorPositionVertex( glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, 0.0f, 1.0f ) )
#define VERTEX_FBR qglen::ColorPositionVertex( glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, 0.0f, 0.0f ) )

// Back Verticies
#define VERTEX_BTR qglen::ColorPositionVertex( glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f, 1.0f, 0.0f ) )
#define VERTEX_BTL qglen::ColorPositionVertex( glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f, 1.0f, 1.0f ) )
#define VERTEX_BBL qglen::ColorPositionVertex( glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 1.0f, 0.0f, 1.0f ) )
#define VERTEX_BBR qglen::ColorPositionVertex( glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f, 1.0f, 1.0f ) )

// Create a colored cube
static const qglen::ColorPositionVertex sg_vertexes[] = {
    // Face 1 (Front)
        VERTEX_FTR, VERTEX_FTL, VERTEX_FBL,
        VERTEX_FBL, VERTEX_FBR, VERTEX_FTR,
      // Face 2 (Back)
        VERTEX_BBR, VERTEX_BTL, VERTEX_BTR,
        VERTEX_BTL, VERTEX_BBR, VERTEX_BBL,
      // Face 3 (Top)
        VERTEX_FTR, VERTEX_BTR, VERTEX_BTL,
        VERTEX_BTL, VERTEX_FTL, VERTEX_FTR,
      // Face 4 (Bottom)
        VERTEX_FBR, VERTEX_FBL, VERTEX_BBL,
        VERTEX_BBL, VERTEX_BBR, VERTEX_FBR,
      // Face 5 (Left)
        VERTEX_FBL, VERTEX_FTL, VERTEX_BTL,
        VERTEX_FBL, VERTEX_BTL, VERTEX_BBL,
      // Face 6 (Right)
        VERTEX_FTR, VERTEX_FBR, VERTEX_BBR,
        VERTEX_BBR, VERTEX_BTR, VERTEX_FTR

};

#undef VERTEX_BBR
#undef VERTEX_BBL
#undef VERTEX_BTL
#undef VERTEX_BTR

#undef VERTEX_FBR
#undef VERTEX_FBL
#undef VERTEX_FTL
#undef VERTEX_FTR


#include <shaderlist.h>


DreieckObject::DreieckObject(qglen::GameWindow* window) : qglen::IObject("DreieckObject", window)
{
    m_Position = glm::vec3(0, 0, -5);
}


bool DreieckObject::Initialize()
{
    // Application-specific initialization
     {
       // Create Shader (Do not release until VAO is created)
       m_program = qglen::ShaderList::instance()->GetByName("Basic");
       m_program->bind();

       // Create Buffer (Do not release until VAO is created)
       m_vertex.create();
       m_vertex.bind();
       m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
       m_vertex.allocate(sg_vertexes, sizeof(sg_vertexes));

       // Create Vertex Array Object
       m_object.create();
       m_object.bind();
       m_program->enableAttributeArray(0);
       m_program->enableAttributeArray(1);
       m_program->setAttributeBuffer(0, GL_FLOAT, qglen::ColorPositionVertex::positionOffset(), qglen::ColorPositionVertex::PositionTupleSize, qglen::ColorPositionVertex::stride());
       m_program->setAttributeBuffer(1, GL_FLOAT, qglen::ColorPositionVertex::colorOffset(), qglen::ColorPositionVertex::ColorTupleSize, qglen::ColorPositionVertex::stride());
       m_matrixUniform = m_program->uniformLocation("matCamera");

       // Release (unbind) all
       m_object.release();
       m_vertex.release();
       m_program->release();
     }
    GetGameWindow()->glEnable(GL_CULL_FACE);
    return true;
}

bool DreieckObject::Destroy()
{
    return true;
}

void DreieckObject::Move(qglen::GamePadState *pStates, int numDevices, double renderTime, double elapsedTime, bool lag)
{

    glm::vec3 pos_delta = glm::vec3();





            pos_delta.y -= 2.0f * (float)(pStates->axisRightY / GetGameWindow()->screen()->refreshRate());

            pos_delta.x -= 2.0f * (float)(pStates->axisLeftX / GetGameWindow()->screen()->refreshRate());
            pos_delta.z -= 2.0f * (float)(pStates->axisLeftY / GetGameWindow()->screen()->refreshRate());

        if(!lag)
        {
            m_Position += pos_delta;

            m_program->bind();
            {
                glm::mat4 matProjection =glm::perspective(45.0f, ((float)(GetGameWindow()->width() / GetGameWindow()->height())), 0.1f, 100.f);
                glm::mat4 matView = glm::translate(glm::mat4(1.0f), m_Position);
                //matView = glm::rotate(matView, rotate, glm::vec3(0.0f, 1.0f, 0.0f));
                glm::mat4 matModel = glm::scale(glm::mat4(1.0f), glm::vec3(0.8f));
                glm::mat4 matCamera = matProjection *matView * matModel;

                GetGameWindow()->glUniformMatrix4fv(m_matrixUniform, 1, GL_FALSE, glm::value_ptr(matCamera));

            }
            m_program->release();
                }
}

void DreieckObject::Render(double smoothStep)
{
    // Render using our shader
    m_program->bind();
    {

        m_object.bind();
        GetGameWindow()->glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
        m_object.release();
    }
    m_program->release();

}
