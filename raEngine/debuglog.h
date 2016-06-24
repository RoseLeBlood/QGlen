#ifndef DEBUGLOG_H
#define DEBUGLOG_H

#include <raengine_global.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <QString>

#include <stdio.h>

class RAENGINESHARED_EXPORT DebugLog
{
public:
    DebugLog();

    virtual bool InitLog(QString File);
    virtual bool ExitLog();

    virtual bool Write(const glm::vec2& v);
    virtual bool Write(const glm::vec3& v);
    virtual bool Write(const glm::mat4& m);
    virtual bool Write(const QString& Format);

    virtual void OK(const QString& x) { WriteToLogDirect("<b><font color=\"#008000\">OK:</font></b>" + x); }
    virtual void Error(const QString& x) { WriteToLogDirect("<b><font color=\"#800000\">Error:</font></b>" + x); }
    virtual void Warning(const QString& x){ WriteToLogDirect("<b><font color=\"#000080\">Warning:</font></b>" + x); }
protected:
    virtual bool WriteToLogDirect(const QString& Format);

protected:
    FILE *m_File;
};

#endif // DEBUGLOG_H
