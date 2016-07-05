#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H

#include <macros.h>
#include <QOpenGLBuffer>

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


#endif // OPENGLBUFFER_H
