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

#include <QString>
#include <QFile>
#include <QTextStream>
#include "tsingleton.h"
#include "criticalsection.h"

class RAENGINESHARED_EXPORT DebugLog : public TSingleton<DebugLog>
{
    friend class TSingleton<DebugLog>;
protected:
    DebugLog() { m_pSection = new CriticalSection(); }
    ~DebugLog() { if(m_pSection != NULL) { delete[] m_pSection; m_pSection = NULL; } }

    virtual void CreateInstance() { }
    virtual void DestroyInstance() { }
public:
    bool InitLog(const QString file);
    bool ExitLog();

    bool WriteToLogDirect(const QString Format);
    bool WriteToLog(const QString Format);

    void ok(const QString x)            { WriteToLog("<b><font color=\"#008000\">OK:</font></b>" + x); }
    void info(const QString x)          { WriteToLog("<b><font color=\"#008000\">INFO:</font></b> " + x); }
    void warning(const QString x)       { WriteToLog("<b><font color=\"#FF0000\">WARNUNG:</font></b>" + x); }
    void error(const QString x)         { WriteToLog("<b><font color=\"#FF0000\">FEHLER:</font></b>" + x); }

    void nullpointer(const QString x)   { WriteToLog("<b><font color=\"#FF0000\">FEHLER:</font></b> <i>" + x + "</i> ist NULL!"); }
    void invalidvalue(const QString x)  { WriteToLog("<b><font color=\"#FF0000\">FEHLER:</font></b> <i>" + x + "</i> hat einen ungültigen Wert!"); }
    void outofmem()                     { WriteToLog("<b><font color=\"#FF0000\">FEHLER:</font></b> Nicht genug Speicher!"); }

    void file(const QString f)          { WriteToLog("<tr><td><font size=\"2\"><b><font color=\"#FF0000\">FEHLER:</font></b> Die Datei <i>" + f + "</i> konnte nicht geöffnet, gelesen, erstellt oder beschrieben werden!</font></td>"); }
private:
    QFile       flr_file;
    QTextStream flr_stream;
    CriticalSection *m_pSection;
};


#endif // DEBUGLOG_H
