#ifndef OPENGLERROR_H
#define OPENGLERROR_H

#include <raengine_global.h>
#include <QEvent>
#include <QStack>
#include <QString>

namespace FunctionType
{
    enum FunctionType_t
    {
      bind,
      read,
      create,
      unmap,
      link,
      addShader,
      addShaderFromSourceCode,
      addShaderFromSourceFile
    };
}
namespace ObjectType
{
    enum ObjectType_t
    {
      QOpenGLBuffer,
      QOpenGLShaderProgram,
      QOpenGLVertexArrayObject
    };
}
class RAENGINESHARED_EXPORT OpenGLError : public QEvent
{
public:
    OpenGLError(QString callerName, QString fnName, ObjectType::ObjectType_t objType, FunctionType::FunctionType_t fnType);
    virtual ~OpenGLError();

    // Accessing Types
    QString functionName() const;
    QString callerName() const;
    ObjectType::ObjectType_t objectType() const;
    FunctionType::FunctionType_t functionType() const;

    // Static Access
    static QEvent::Type type();
    static bool sendEvent(OpenGLError *event);
    static void pushErrorHandler(QObject *obj);
    static void popErrorHandler();
private:
  QString m_functionName;
  QString m_callerName;
  ObjectType::ObjectType_t m_objectType;
  FunctionType::FunctionType_t m_functionType;
  static QStack<QObject*> m_errorHandler;

};

#endif // OPENGLERROR_H
