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
