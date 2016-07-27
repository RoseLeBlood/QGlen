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
#include "xmlconfig.h"

#include <QFile>
#include <QXmlStreamReader>
#include <QStringList>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>


#include <QMetaEnum>


QGLEN_BEGIN

XmlConfigReader::XmlFormat::XmlFormat()
{

}
bool XmlConfigReader::XmlFormat::readXmlFile(QIODevice &device, QSettings::SettingsMap &map)
{
    QXmlStreamReader xmlReader(&device);
    QStringList elements;

    // Solange Ende nicht erreicht und kein Fehler aufgetreten ist
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        // N盲chsten Token lesen
        xmlReader.readNext();

        // Wenn Token ein Startelement
        if (xmlReader.isStartElement() && xmlReader.name() != "rae") {
            // Element zur Liste hinzuf眉gen
            elements.append(xmlReader.name().toString());
        // Wenn Token ein Endelement
        } else if (xmlReader.isEndElement()) {
            // Letztes Element l枚schen
            if(!elements.isEmpty()) elements.removeLast();
        // Wenn Token einen Wert enth盲lt
        } else if (xmlReader.isCharacters() && !xmlReader.isWhitespace()) {
            QString key;

            // Elemente zu String hinzuf眉gen
            for(int i = 0; i < elements.size(); i++) {
                if(i != 0) key += "/";
                key += elements.at(i);
            }

            // Wert in Map eintragen
            map[key] = xmlReader.text().toString();
        }
    }

    // Bei Fehler Warnung ausgeben
    if (xmlReader.hasError()) {
        qWarning() << xmlReader.errorString();
        return false;
    }

    return true;
}
bool XmlConfigReader::XmlFormat::writeXmlFile(QIODevice &device, const QSettings::SettingsMap &map) {
    QXmlStreamWriter xmlWriter(&device);

    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("rae");

    QStringList prev_elements;
    QSettings::SettingsMap::ConstIterator map_i;

    // Alle Elemente der Map durchlaufen
    for (map_i = map.begin(); map_i != map.end(); map_i++) {

        QStringList elements = map_i.key().split("/");

        int x = 0;
        // Zu schlie脽ende Elemente ermitteln
        while(x < prev_elements.size() && elements.at(x) == prev_elements.at(x)) {
            x++;
        }

        // Elemente schlie脽en
        for(int i = prev_elements.size() - 1; i >= x; i--) {
            xmlWriter.writeEndElement();
        }

        // Elemente 枚ffnen
        for (int i = x; i < elements.size(); i++) {
            xmlWriter.writeStartElement(elements.at(i));
        }

        // Wert eintragen
        xmlWriter.writeCharacters(map_i.value().toString());

        prev_elements = elements;
    }

    // Noch offene Elemente schlie脽en
    for(int i = 0; i < prev_elements.size(); i++) {
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    return true;
}

XmlConfig*  XmlConfigReader::getConfig()
{
    if(m_pConfig != 0)
        return m_pConfig;

    QDir dir = QDir(  QCoreApplication::applicationDirPath() );
    dir.cd(XmlConfigDir);

    QSettings *_xmlSetting = new QSettings(dir.absoluteFilePath(XmlConfigFile), XmlFormat::getFormat());
    if (_xmlSetting == 0)
    {
        qCritical() << "Config file not found, use std config";
        //qLog.error("Config file not found, use std config");
        m_pConfig = new XmlConfig();
        return m_pConfig;
    }
    if (_xmlSetting->value("Version").toInt() != XmlConfigVersion)
    {
        //QByteArray::number(myNumber).toHex()
        qCritical() << "Config file wrong version Number " << QByteArray::number(_xmlSetting->value("Version").toInt()).toHex() << " != " <<  QByteArray::number(XmlConfigVersion).toHex();
        //qLog.error("Config file wrong version Number");
        m_pConfig = new XmlConfig();
    }
    else
    {
        m_pConfig = new XmlConfig(_xmlSetting->value("Reselution", ScreenReselution::ScreenReselutionToString(ScreenReselution::HD_1280_720)).toString(),
                         _xmlSetting->value("samples", 2).toInt(),
                         _xmlSetting->value("depth", 1).toInt(),
                         _xmlSetting->value("stencil", 1).toInt(),
                         _xmlSetting->value("fullscreen", false).toBool());
    }
    delete _xmlSetting;

    return m_pConfig;

}
XmlShader*  XmlConfigReader::getShader(QString filePath)
{
    QDir dir = QDir(  QCoreApplication::applicationDirPath() );
    dir.cd(XmlShaderDir);
    QSettings *_xmlSetting = new QSettings(dir.absoluteFilePath(filePath), XmlFormat::getFormat());
    if (_xmlSetting == 0)
    {
         qCritical() << "Shader Config file not found";
        //qLog.error("Shader Config file not found");
        return 0;
    }
    if (_xmlSetting->value("Version").toInt() != XmlShaderVersion)
    {
        qCritical() << "Shader Config file have the wrong version Number";
        return 0;
    }
    XmlShader* shader = new XmlShader();
    shader->setVertexShaderCode(_xmlSetting->value("VertexCode", "").toString());
    shader->setFragmentShaderCode(_xmlSetting->value("FragmentCode", "").toString());
    shader->setGeometryShaderCode(_xmlSetting->value("GeometryCode", "").toString());
    shader->setName(_xmlSetting->value("Name", filePath).toString());

    delete _xmlSetting;
    return shader;
}
bool XmlConfigReader::saveConfig(XmlConfig* cfg)
{
    QDir dir = QDir(  QCoreApplication::applicationDirPath() );
    dir.cd(XmlConfigDir);
    QSettings *_xmlSetting = new QSettings(dir.absoluteFilePath(XmlConfigFile), XmlFormat::getFormat());
    if (_xmlSetting == 0)
    {
        return false;
    }

    _xmlSetting->setValue("Version", XmlConfigVersion);
    _xmlSetting->setValue("fullscreen", cfg->isFullScreen());
    _xmlSetting->setValue("Reselution", ScreenReselution::ScreenReselutionToString(cfg->getResulution()));
    _xmlSetting->setValue("stencil", cfg->getStencil());
    _xmlSetting->setValue("samples", cfg->getSamples());
    _xmlSetting->setValue("depth", cfg->getDepth());

    delete _xmlSetting;
    return true;
}
bool XmlConfigReader::saveShader(XmlShader* shader)
{

    QDir dir = QDir(  QCoreApplication::applicationDirPath() );
    dir.cd(XmlShaderDir);
    QSettings *_xmlSetting = new QSettings(dir.absoluteFilePath(shader->getName() + ".rs"), XmlFormat::getFormat());
    if (_xmlSetting == 0)
    {
        qCritical() << "Shader Config file not found";
        return false;
    }
    _xmlSetting->setValue("Version", XmlShaderVersion);
    _xmlSetting->setValue("VertexCode", shader->getVertexShaderCode());
    _xmlSetting->setValue("FragmentCode", shader->getFragmentShaderCode());
    _xmlSetting->setValue("GeometryCode", shader->getGeometryShaderCode());
    _xmlSetting->setValue("Name", shader->getName());
    delete _xmlSetting;

    return true;
}

QGLEN_END



























