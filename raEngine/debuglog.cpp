#include "debuglog.h"

#define MAX_PATH 260
DebugLog::DebugLog()
{

}
bool DebugLog::InitLog(QString File)
{
    m_File = fopen(File.toStdString().c_str(), "wt");
    /*m_File = new QFile(File);
    if (!m_File->open(QIODevice::WriteOnly | QIODevice::Text))
            return false;
    m_out = QTextStream(File, QIODevice::WriteOnly | QIODevice::Text);
    m_out << "<!DOCTYPE html>\n<title>raEngine OPENGL Log</title>\n";*/
    if(!m_File) return false;

        return true;
}
bool DebugLog::ExitLog()
{
    // Datei schlie?en
        if(m_File)
        {
            fflush(m_File);
            fclose(m_File);
            m_File = NULL;
        }

        return true;
}

bool DebugLog::Write(const glm::vec2& v)
{
    char temp[MAX_PATH];
        sprintf(temp, "<tr><td><font size=\"2\"><b><font color=\"#000080\">2D-Vektor:</font></b> x = <i>%.3f</i>, y = <i>%.3f</i></td></tr>",
                                  v.x, v.y);
    return WriteToLogDirect(QString(temp));
}
bool DebugLog::Write(const glm::vec3& v)
{
    // 3D-Vektor in die Logbuchdatei schreiben
        char temp[MAX_PATH];
        sprintf(temp, "<tr><td><font size=\"2\"><b><font color=\"#000080\">3D-Vektor:</font></b> x = <i>%.3f</i>, y = <i>%.3f</i>, z = <i>%.3f</i></td></tr>",
                                  v.x, v.y, v.z);
        return WriteToLogDirect(QString(temp));
}
bool DebugLog::Write(const glm::mat4& m)
{
   /* m_out << "<tr><td><font size=\"2\"><b><font color=\"#000080\">Matrix:</font></b><table>";
    for(int iRow = 0; iRow < 4; iRow++)
    {
        m_out << "<tr>";

        for(int iColumn = 0; iColumn < 4; iColumn++)
        {
            m_out << "<td><font size=\"1\">";
            m_out << "<i>" + m[iRow*iColumn] + "</i></td>";
        }

        m_out << "</tr>";
    }
    m_out << "</table>";*/
    return true;
}
bool RemoveHTMLTags( std::string pcIn,  std::string pcOut, size_t dwOutLength)
{
    /*size_t dwInLength = strlen(pcIn.c_str());

    DWORD dwOut = 0;

    ZeroMemory((void*)pcOut.c_str(), dwOutLength);
    for(DWORD dwIn = 0; dwIn < dwInLength; dwIn++)
    {
        if(pcIn[dwIn] != '<') {pcOut[dwOut] = pcIn[dwIn]; dwOut++;}
        else
        {
            while(pcIn[dwIn] != '>') dwIn++;
        }
    }
*/
    return true;
}
bool DebugLog::WriteToLogDirect(const QString& Format)
{
    if(m_File)
        {
            fprintf(m_File, "%s<br>", Format.toStdString().c_str());
    #ifdef _DEBUG
            fflush(m_File);
    #endif
        }

        return true;
}
#include <qdebug.h>

void OutputDebugString(QString pcStr)
{
    //qDebug << pcStr;
}

bool DebugLog::Write(const QString& Format)
{
    if(m_File)
        {
            fprintf(m_File, "<tr><td><font size=\"2\" color=\"#000080\">%s</font></td></tr><br>", Format.toStdString().c_str());
    #ifdef _DEBUG
            fflush(m_File);
    #endif
        }
        OutputDebugString(Format);

        return true;
}
