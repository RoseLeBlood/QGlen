#include "jsonshader.h"

#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include "QJsonArray"

#include <QMetaEnum>
#include "QJsonDocument"

QGLEN_BEGIN

JSonShader::JSonShader()
{

}
void JSonShader::readFromConfig(const QJsonObject &json)
{
    m_fragShaderCode = json["FragmentCode"].toString();
    m_vertShaderCode = json["VertexCode"].toString();
    m_geoShaderCode = json["GeometryCode"].toString();
    m_strName = json["Name"].toString();
}
void JSonShader::writeToConfig(QJsonObject &json) const
{
    json["FragmentCode"] = m_fragShaderCode;
    json["VertexCode"] = m_vertShaderCode;
    json["GeometryCode"] = m_geoShaderCode;
    json["Name"] = m_strName;
}


void JSonShaderLoader::CreateInstance()
{

}
void JSonShaderLoader::DestroyInstance()
{

}

JSonShader* JSonShaderLoader::getShader(QString filePath)
{
    QDir dir = QDir(  QCoreApplication::applicationDirPath() );
    dir.cd(XmlShaderDir);
    QFile loadFile(dir.filePath(filePath));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        //qWarning("Couldn't open " + QString(filePath) + " file.");
        return 0;
    }
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    JSonShader* pConfig = new JSonShader();
    pConfig->readFromConfig(loadDoc.object());

    return pConfig;
}

bool JSonShaderLoader::setShader(JSonShader *cfg)
{
    QDir dir = QDir(  QCoreApplication::applicationDirPath() );
    dir.cd(XmlShaderDir);
    QFile saveFile(dir.filePath(cfg->getName() + ".sh"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        //qWarning() "Couldn't open " + QString(cfg->getName()) + " file.");
        return false;
    }

    QJsonObject gameObject;
    cfg->writeToConfig(gameObject);

    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());

     return true;
}

QGLEN_END
