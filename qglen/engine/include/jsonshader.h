#ifndef JSONSHADER_H
#define JSONSHADER_H

#include <QString>
#include "raengine_global.h"
#include "tsingleton.h"

#include "QJsonDocument"
#include <QJsonObject>

#include "iconfigure.h"

QGLEN_BEGIN

class RAENGINESHARED_EXPORT JSonShader : public IConfigure
{
public:
    JSonShader();

    virtual void readFromConfig(const QJsonObject &json);
    virtual void writeToConfig(QJsonObject &json) const;

    QString getFragmentShaderCode() { return m_fragShaderCode; }
    QString getVertexShaderCode() { return m_vertShaderCode; }
    QString getGeometryShaderCode() { return m_geoShaderCode; }
    QString getName() { return m_strName; }

    void setFragmentShaderCode(QString code) { m_fragShaderCode = code; }
    void setVertexShaderCode(QString code) { m_vertShaderCode = code; }
    void setGeometryShaderCode(QString code) { m_geoShaderCode = code; }
    void setName(QString name) { m_strName = name; }
private:
    QString m_fragShaderCode;
    QString m_vertShaderCode;
    QString m_geoShaderCode;
    QString m_strName;
};


class RAENGINESHARED_EXPORT JSonShaderLoader : public TSingleton<JSonShaderLoader>
{
public:
    JSonShader* getShader(QString filePath);
    bool setShader(JSonShader *cfg);

    virtual void CreateInstance();
    virtual void DestroyInstance();
};

QGLEN_END

#endif // JSONSHADER_H
