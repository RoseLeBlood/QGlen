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

#include "iconfigure.h"

#include <QJsonObject>

QGLEN_BEGIN


class QApplication;


class RAENGINESHARED_EXPORT Config : public IConfigure
{
public:
    struct GameConfig
    {
        struct
        {
            int Samples;
            int Depht;
            bool FullScreen;
            int Height;
            int Wight;
            int Stencil;
        }Grafik;
        struct
        {
            QString Soundkarte;
            int     Frequenz;
        }Audio;
        QString GameName;
    };

    Config();

    virtual void readFromConfig(const QJsonObject &json);
    virtual void writeToConfig(QJsonObject &json) const;

    GameConfig getGameConfig() { return m_stConfig; }
    void setGameConfig(GameConfig c) { m_stConfig = c; }

    QString getGameName() { return m_stConfig.GameName; }
    void setGameName(QString name) { m_stConfig.GameName = name; }
protected:
    GameConfig m_stConfig;
};

class RAENGINESHARED_EXPORT ConfigLoader : public TSingleton<ConfigLoader>
{
public:
    Config* getConfig();
    bool setConfig(Config *cfg);

    virtual void CreateInstance();
    virtual void DestroyInstance();
};


QGLEN_END

#endif // XMLCONFIG_H
