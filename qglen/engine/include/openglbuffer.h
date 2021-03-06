#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H

#include <macros.h>
#include <QOpenGLBuffer>

QGLEN_BEGIN

// Register to check OpenGLBuffer
class RAENGINESHARED_EXPORT OpenGLBufferChecked : public QOpenGLBuffer
{
public:
  GL_CHECK(QOpenGLBuffer,bind)
  GL_CHECK(QOpenGLBuffer,create)
  GL_CHECK(QOpenGLBuffer,unmap)
  GL_CHECK(QOpenGLBuffer,read,int,void*,int)
};

// Final class
class RAENGINESHARED_EXPORT OpenGLBuffer : public OpenGLBufferChecked
{
  // Intentionally Empty
};
QGLEN_END

#endif // OPENGLBUFFER_H
