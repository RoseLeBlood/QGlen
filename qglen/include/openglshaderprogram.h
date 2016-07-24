#ifndef OPENGLSHADERPROGRAM_H
#define OPENGLSHADERPROGRAM_H

#include <macros.h>
#include <QOpenGLShaderProgram>
QGLEN_BEGIN

// Register to check OpenGLShaderProgram
class RAENGINESHARED_EXPORT OpenGLShaderProgramChecked : public QOpenGLShaderProgram
{
public:
  explicit OpenGLShaderProgramChecked(QObject *parent = 0) : QOpenGLShaderProgram(parent) {}
  GL_CHECK(QOpenGLShaderProgram,addShader,QOpenGLShader*)
  GL_CHECK(QOpenGLShaderProgram,addShaderFromSourceCode,QOpenGLShader::ShaderType,const char*)
  GL_CHECK(QOpenGLShaderProgram,addShaderFromSourceCode,QOpenGLShader::ShaderType,const QByteArray&)
  GL_CHECK(QOpenGLShaderProgram,addShaderFromSourceCode,QOpenGLShader::ShaderType,const QString&)
  GL_CHECK(QOpenGLShaderProgram,addShaderFromSourceFile,QOpenGLShader::ShaderType,const QString&)
  GL_CHECK(QOpenGLShaderProgram,bind)
  GL_CHECK(QOpenGLShaderProgram,create)
  GL_CHECK(QOpenGLShaderProgram,link)
};

// Final class
class RAENGINESHARED_EXPORT OpenGLShaderProgram : public OpenGLShaderProgramChecked
{
public:
  explicit OpenGLShaderProgram(QObject *parent = 0) : OpenGLShaderProgramChecked(parent) {}
};


class RAENGINESHARED_EXPORT OpenGLShaderProgramBlock
{
public:
    OpenGLShaderProgramBlock(OpenGLShaderProgram* rc) :  m_rc(rc)
    {
        m_rc->bind();
    }
    ~OpenGLShaderProgramBlock(void)
    {
        m_rc->release();
    }
    operator bool()
    {
        return true;
    }
private:
    OpenGLShaderProgram*		m_rc;
};

#define BIND(x) if (qglen::OpenGLShaderProgramBlock __csc = x)

QGLEN_END
#endif // OPENGLSHADERPROGRAM_H
