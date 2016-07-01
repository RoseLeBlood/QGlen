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
#include "debuglog.h"
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <qdebug.h>
#include <qdir.h>

bool DebugLog::InitLog(const QString file)
{
        flr_file.setFileName(file);
        flr_file.open(QIODevice::WriteOnly);
        flr_stream.setDevice(&flr_file);

        WriteToLogDirect("<!DOCTYPE HTML>\n<html>");
        WriteToLogDirect("<head>\n\t<meta charset=\"utf-8\">\n\t"
                         "<title>QGlen Log Datei</title>\n\t"
                         "<meta name=\"robots\" content=\"noindex,nofollow\">"
                         "<meta charset=\"UTF-8\">\n"
                         "\n</head>\n<body>");
    return true;
}
bool DebugLog::ExitLog()
{
        // Datei schlie�en
        if(flr_file.isOpen())
        {
            WriteToLogDirect("</body>");
            WriteToLogDirect("</html>");

            flr_stream.flush();
            flr_stream.setDevice(NULL);
            flr_file.close();
        }
    return true;
}

bool DebugLog::WriteToLogDirect(const QString pcFormat)
{
    LOCK(m_pSection)
    {
        // String ins Logbuch schreiben
        if(flr_file.isOpen())
        {
            flr_stream << pcFormat << "\n";
            flr_stream.flush();

        }
    }
    return true;
}
bool DebugLog::WriteToLog(const QString pcFormat)
{
    LOCK(m_pSection)
    {
        if(flr_file.isOpen())
        {
            flr_stream  << "<tr><td><font size=\"2\" color=\"#000080\">" << pcFormat <<  "</font></td></tr><br>" << "\n";
            flr_stream.flush();
        }
    }
    return true;
}
