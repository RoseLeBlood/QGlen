#ifndef QCLCONTEXTGL_H
#define QCLCONTEXTGL_H

#include "qclglobal.h"
#include "qclcontext.h"
#include <QtOpenGL/qgl.h>
#include <QtOpenGL/qglbuffer.h>


QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(CL)

class QCLContextGLPrivate;

// Note: this class probably should be in the QtOpenGL library.
class Q_CL_EXPORT QCLContextGL : public QCLContext
{
public:
    QCLContextGL();
    ~QCLContextGL();

    bool create(const QCLPlatform &platform = QCLPlatform());
    void release();

    bool supportsObjectSharing() const;

    QCLBuffer createGLBuffer(GLuint bufobj, QCLMemoryObject::Access access);

    QCLBuffer createGLBuffer(QGLBuffer *bufobj, QCLMemoryObject::Access access);

    QCLImage2D createTexture2D
        (GLenum type, GLuint texture, GLint mipmapLevel, QCLMemoryObject::Access access);
    QCLImage2D createTexture2D(GLuint texture, QCLMemoryObject::Access access);

    QCLImage3D createTexture3D
        (GLenum type, GLuint texture, GLint mipmapLevel, QCLMemoryObject::Access access);
    QCLImage3D createTexture3D(GLuint texture, QCLMemoryObject::Access access);

    QCLImage2D createRenderbuffer(GLuint renderbuffer, QCLMemoryObject::Access access);

#ifdef Q_MAC_COMPAT_GL_FUNCTIONS
    QCLBuffer createGLBuffer(QMacCompatGLuint bufobj, QCLMemoryObject::Access access);

    QCLImage2D createTexture2D
        (QMacCompatGLenum type, QMacCompatGLuint texture,
         QMacCompatGLint mipmapLevel, QCLMemoryObject::Access access);
    QCLImage2D createTexture2D(QMacCompatGLuint texture, QCLMemoryObject::Access access);

    QCLImage3D createTexture3D
        (QMacCompatGLenum type, QMacCompatGLuint texture,
         QMacCompatGLint mipmapLevel, QCLMemoryObject::Access access);
    QCLImage3D createTexture3D(QMacCompatGLuint texture, QCLMemoryObject::Access access);

    QCLImage2D createRenderbuffer
        (QMacCompatGLuint renderbuffer, QCLMemoryObject::Access access);
#endif

    static bool isGLBuffer(const QCLBuffer &buffer);
    static bool isTexture2D(const QCLImage2D &image);
    static bool isTexture3D(const QCLImage3D &image);
    static bool isRenderbuffer(const QCLImage2D &image);

    QCLEvent acquire(const QCLMemoryObject &mem);
    QCLEvent acquire
        (const QCLMemoryObject &mem, const QCLEventList &after);

    QCLEvent release(const QCLMemoryObject &mem);
    QCLEvent release
        (const QCLMemoryObject &mem, const QCLEventList &after);

private:
    QScopedPointer<QCLContextGLPrivate> d_ptr;

    Q_DISABLE_COPY(QCLContextGL)
    Q_DECLARE_PRIVATE(QCLContextGL)

    void reportError(const char *name, cl_int error);
};



QT_END_NAMESPACE

QT_END_HEADER


#endif // QCLCONTEXTGL_H
