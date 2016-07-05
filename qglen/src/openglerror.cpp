#include "include/openglerror.h"
#include <QObject>
#include <QCoreApplication>
#include <QDebug>

QStack<QObject*> OpenGLError::m_errorHandler;

OpenGLError::OpenGLError(QString callerName, QString fnName, ObjectType::ObjectType_t objType, FunctionType::FunctionType_t fnType) :
    QEvent(type())
{
    m_functionName = fnName;
    m_callerName = callerName;
    m_objectType = objType;
    m_functionType = fnType;
}
OpenGLError::~OpenGLError()
{

}
QString OpenGLError::functionName() const
{
    return m_functionName;
}
QString OpenGLError::callerName() const
{
    return m_callerName;
}
ObjectType::ObjectType_t OpenGLError::objectType() const
{
    return m_objectType;
}
FunctionType::FunctionType_t OpenGLError::functionType() const
{
    return m_functionType;
}

QEvent::Type OpenGLError::type()
{
  static QEvent::Type customEventType =
    static_cast<QEvent::Type>(QEvent::registerEventType());
  return customEventType;
}

bool OpenGLError::sendEvent(OpenGLError *event)
{
  if (m_errorHandler.empty())
  {
    qWarning("Set OpenGLError::setErrorHandler() before calling any GL_DEBUG OpenGL functions!");
    return false;
  }
  return QCoreApplication::sendEvent(m_errorHandler.top(), event);
}

void OpenGLError::pushErrorHandler(QObject *obj)
{
#ifdef    GL_DEBUG
  qDebug() << "GL_DEBUG Error Handler (" << obj << ")";
#endif // GL_DEBUG
  m_errorHandler.push(obj);
}

void OpenGLError::popErrorHandler()
{
  m_errorHandler.pop();
}

