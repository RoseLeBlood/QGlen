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
#include <QStringList>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include "QJsonArray"


#include <QMetaEnum>
#include "QJsonDocument"

QGLEN_BEGIN

Config::Config()
{
    m_stConfig.Grafik.Samples = 0;
    m_stConfig.Grafik.Depht = 8;
    m_stConfig.Grafik.FullScreen = false;
    m_stConfig.Grafik.Height = 800;
    m_stConfig.Grafik.Wight = 1280;
    m_stConfig.Grafik.Stencil = 0;

    m_stConfig.Audio.Frequenz = 44100;
    m_stConfig.Audio.Soundkarte = "";
}


void Config::readFromConfig(const QJsonObject &json)
{
    QJsonArray array = json["Grafik"].toArray();
    QJsonObject g = array[0].toObject();

    m_stConfig.Grafik.Samples = g["Samples"].toInt();
    m_stConfig.Grafik.Depht = g["Depth"].toInt();

    m_stConfig.Grafik.FullScreen = g["FullScreen"].toBool();
    m_stConfig.Grafik.Height = g["Height"].toInt();

    m_stConfig.Grafik.Wight = g["Wight"].toInt();
    m_stConfig.Grafik.Stencil = g["Stencil"].toInt();

    array = json["Sound"].toArray();
    QJsonObject s = array[0].toObject();

    m_stConfig.Audio.Frequenz = s["Frequenz"].toInt();
    m_stConfig.Audio.Soundkarte = s["Soundkarte"].toString();

}
void Config::writeToConfig(QJsonObject &json) const
{
    QJsonArray grafik, sound;
    QJsonObject g,s;

    g["Wight"] = m_stConfig.Grafik.Wight;
    g["Height"] = m_stConfig.Grafik.Height;
    g["FullScreen"] = m_stConfig.Grafik.FullScreen;
    g["Samples"] = m_stConfig.Grafik.Samples;
    g["Depth"] = m_stConfig.Grafik.Depht;
    g["Stencil"] = m_stConfig.Grafik.Stencil;

    grafik.append(g);

    s["Frequenz"] = m_stConfig.Audio.Frequenz;
    s["Soundkarte"] = m_stConfig.Audio.Soundkarte;

    sound.append(s);

    json["Grafik"] = grafik;
    json["Sound"] = sound;
}
Config* ConfigLoader::getConfig()
{

    QDir dir = QDir(  QCoreApplication::applicationDirPath() );
    dir.cd(XmlConfigDir);
    QFile loadFile(dir.filePath(XmlConfigFile));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open config file.");
        return 0;
    }
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    Config* pConfig = new Config();
    pConfig->readFromConfig(loadDoc.object());

    return pConfig;
}
bool ConfigLoader::setConfig(Config* cfg)
{
    QDir dir = QDir(  QCoreApplication::applicationDirPath() );
    dir.cd(XmlConfigDir);
    QFile saveFile(dir.filePath(XmlConfigFile));

   if (!saveFile.open(QIODevice::WriteOnly)) {
       qWarning("Couldn't open config file.");
       return false;
   }

   QJsonObject gameObject;
   cfg->writeToConfig(gameObject);

   QJsonDocument saveDoc(gameObject);
   saveFile.write(saveDoc.toJson());

    return true;
}

void ConfigLoader::CreateInstance()
{

}
void ConfigLoader::DestroyInstance()
{

}
QGLEN_END



























