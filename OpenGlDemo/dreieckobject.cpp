#include "dreieckobject.h"

#include <QOpenGLFunctions>
#include "colorpositionvertex.h"

#include <glm/glm.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective



// Front Verticies
#define VERTEX_FTR ColorPositionVertex( glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f, 0.0f, 0.0f ) )
#define VERTEX_FTL ColorPositionVertex( glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f, 1.0f, 0.0f ) )
#define VERTEX_FBL ColorPositionVertex( glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, 0.0f, 1.0f ) )
#define VERTEX_FBR ColorPositionVertex( glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, 0.0f, 0.0f ) )

// Back Verticies
#define VERTEX_BTR ColorPositionVertex( glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f, 1.0f, 0.0f ) )
#define VERTEX_BTL ColorPositionVertex( glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f, 1.0f, 1.0f ) )
#define VERTEX_BBL ColorPositionVertex( glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 1.0f, 0.0f, 1.0f ) )
#define VERTEX_BBR ColorPositionVertex( glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f, 1.0f, 1.0f ) )

// Create a colored cube
static const ColorPositionVertex sg_vertexes[] = {
    ColorPositionVertex( glm::vec3( 0.00f,  0.75f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f) ),
     ColorPositionVertex( glm::vec3(-0.75f, -0.75f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) ),
     ColorPositionVertex( glm::vec3( 0.75f, -0.75f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) )
};

#undef VERTEX_BBR
#undef VERTEX_BBL
#undef VERTEX_BTL
#undef VERTEX_BTR

#undef VERTEX_FBR
#undef VERTEX_FBL
#undef VERTEX_FTL
#undef VERTEX_FTR




static const char *vertexShaderSource =
    "layout(location = 0) in vec3 position;\n"
    "layout(location = 1) in vec3 color;\n"
    "out vec4 vColor;\n"
    "uniform highp mat4 matCamera;\n"
    "void main() {\n"
    "   gl_Position = matCamera * vec4(position, 1.0);\n"
    "   vColor = vec4(color, 1.0f);\n"
    "}\n";

static const char *fragmentShaderSource =
    "in highp vec4 vColor;\n"
    "out highp vec4 fColor;\n"
    "void main() {\n"
    "   fColor = vColor;\n"
    "}\n";

DreieckObject::DreieckObject(GameWindow* window) : IObject("DreieckObject", window)
{
    m_Position = QVector3D(0, 0, -5);
}


bool DreieckObject::Initialize()
{
    // Application-specific initialization
     {
       // Create Shader (Do not release until VAO is created)
       m_program = new QOpenGLShaderProgram();
       m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
       m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
       m_program->link();
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
       m_program->setAttributeBuffer(0, GL_FLOAT, ColorPositionVertex::positionOffset(), ColorPositionVertex::PositionTupleSize, ColorPositionVertex::stride());
       m_program->setAttributeBuffer(1, GL_FLOAT, ColorPositionVertex::colorOffset(), ColorPositionVertex::ColorTupleSize, ColorPositionVertex::stride());
       m_matrixUniform = m_program->uniformLocation("matCamera");

       // Release (unbind) all
       m_object.release();
       m_vertex.release();
       m_program->release();
     }
    return true;
}

bool DreieckObject::Destroy()
{
    return true;
}

void DreieckObject::Move(double renderTime, double elapsedTime)
{
    const qreal retinaScale = GetGameWindow()->devicePixelRatio();
    GetGameWindow()->glViewport(0, 0, GetGameWindow()->width() * retinaScale, GetGameWindow()->height() * retinaScale);

    m_program->bind();
    {
        glm::mat4 matProjection =glm::perspective(45.0f, ((float)(GetGameWindow()->width() / GetGameWindow()->height())), 0.1f, 100.f);
        glm::mat4 matView = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position.x(), m_Position.y(), m_Position.z()));
        matView = glm::rotate(matView, (float)(2.0f * (renderTime / 100.0f)  / GetGameWindow()->screen()->refreshRate()), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 matModel = glm::scale(glm::mat4(1.0f), glm::vec3(0.8f));
        glm::mat4 matCamera = matProjection *matView * matModel;

        GetGameWindow()->glUniformMatrix4fv(m_matrixUniform, 1, GL_FALSE, glm::value_ptr(matCamera));

    }
    m_program->release();
}
void DreieckObject::Input()
{

}
void DreieckObject::Render(QPainter *painter, double smoothStep)
{
    GetGameWindow()->glEnable(GL_MULTISAMPLE);
    // Render using our shader
    m_program->bind();
    {

        m_object.bind();
        GetGameWindow()->glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
        m_object.release();
    }
    m_program->release();

}
