/*
    This file is part of QGlEn.

    QGlEn is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QGlEn is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

    Diese Datei ist Teil von QGlEn.

    QGlEn ist Freie Software: Sie können es unter den Bedingungen
    der GNU General Public License, wie von der Free Software Foundation,
    Version 3 der Lizenz oder (nach Ihrer Wahl) jeder späteren
    veröffentlichten Version, weiterverbreiten und/oder modifizieren.

    QGlEn wird in der Hoffnung, dass es nützlich sein wird, aber
    OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
    Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
    Siehe die GNU General Public License für weitere Details.

    Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
    Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*/
#ifndef XMLCONFIG_H
#define XMLCONFIG_H

#include <QSettings>
#include <QString>
#include "raengine_global.h"
#include "tsingleton.h"




class RAENGINESHARED_EXPORT XmlConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool FullScreen READ isFullScreen WRITE setFullScreen)
    Q_PROPERTY(int Samples READ getSamples WRITE setSamples)
    Q_PROPERTY(int Depth READ getDepth WRITE setDepth)
    Q_PROPERTY(int Wight READ getWight WRITE setWight)
    Q_PROPERTY(int Height READ getHeight WRITE setHeight)
public:



    XmlConfig() : XmlConfig(800,600,0,8,false) { }
    explicit XmlConfig(int wight, int height, int samples, int depth, bool fullscreen)
        : QObject(), m_iSamples(samples), m_iDepht(depth), m_bFullScreen(fullscreen), m_iH(height), m_iW(wight)
    {

    }
    XmlConfig(const XmlConfig& other) : QObject()
    {
        m_iSamples = other.m_iSamples;
        m_iDepht = other.m_iDepht;
        m_bFullScreen = other.m_bFullScreen;
        m_iH = other.m_iH;
        m_iW = other.m_iW;
    }

    int getSamples() { return m_iSamples; }
    int getDepth() { return m_iDepht; }
    bool isFullScreen() { return m_bFullScreen; }
    int getWight() { return m_iW; }
    int getHeight() { return m_iH; }

    void setSamples(int samples) {  m_iSamples = samples; }
    void setDepth(int depth) {  m_iDepht = depth; }
    void setFullScreen(bool fullscreen) {  m_bFullScreen = fullscreen; }
    void setWight(int w) {  m_iW = w; }
    void setHeight(int h) {  m_iH = h; }
private:
    int m_iSamples;
    int m_iDepht;
    bool m_bFullScreen;
    int m_iH;
    int m_iW;

};

class RAENGINESHARED_EXPORT XmlShader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString FragmentShaderCode READ getFragmentShaderCode WRITE setFragmentShaderCode)
    Q_PROPERTY(QString VertexShaderCode READ getVertexShaderCode WRITE setVertexShaderCode)
    Q_PROPERTY(QString GeometryShaderCode READ getGeometryShaderCode WRITE setGeometryShaderCode)
    Q_PROPERTY(QString Name READ getName WRITE setName)
public:
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

class RAENGINESHARED_EXPORT XmlConfigReader : public TSingleton<XmlConfigReader>
{
private:
    class XmlFormat
    {
    public:
        XmlFormat();


         static QSettings::Format getFormat() { return QSettings::registerFormat("xml", readXmlFile, writeXmlFile); }
    private:
         static bool readXmlFile(QIODevice &device, QSettings::SettingsMap &map);
         static bool writeXmlFile(QIODevice &device, const QSettings::SettingsMap &map);
    };
public:
    XmlConfigReader() { m_pConfig = 0; }
    XmlConfig *getConfig();
    XmlShader *getShader(QString filePath);

    bool saveConfig(XmlConfig* cfg);
    bool saveShader(XmlShader* shader);

    virtual void CreateInstance() { }
    virtual void DestroyInstance() { }
private:
    XmlConfig *m_pConfig;
};

#endif // XMLCONFIG_H
