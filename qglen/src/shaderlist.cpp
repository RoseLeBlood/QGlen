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
#include "shaderlist.h"
#include <QDir>
#include <QCoreApplication>
#include <xmlconfig.h>

void ShaderList::Add(QString strName, QOpenGLShaderProgram *mPrg)
{
    if(mPrg == 0)
    {
        qWarning() << "Shader Program: " << strName << "error";
    }
    else if(m_pListShader.contains(strName))
    {
        qInfo() << "Shader Program: " << strName << "allready in list";
        return;
    }
    else
    {
        qDebug() << "Add Shader Program: " << strName << "to List";
           m_pListShader.insert(strName, mPrg);
    }
}
void ShaderList::AddFromSource(QString strName, QString verteSource, QString fagmentSource,
                   QString geometrySource  )
{
    if(m_pListShader.contains(strName))
    {
        return;
    }

    QOpenGLShaderProgram *prg = new QOpenGLShaderProgram();
    prg->addShaderFromSourceCode(QOpenGLShader::Vertex, verteSource);
    prg->addShaderFromSourceCode(QOpenGLShader::Fragment, fagmentSource);
    if(geometrySource != "")
        prg->addShaderFromSourceCode(QOpenGLShader::Geometry, geometrySource);
    prg->link();
    prg->bind();

    Add(strName.remove(".rs"), prg);
}
void ShaderList::AddFromFile(QString strName, QString vertexFileName, QString fagmentFileName,
                 QString geometryFileName )
{
    if(m_pListShader.contains(strName))
    {
        return;
    }

    QOpenGLShaderProgram prg;
    prg.addShaderFromSourceFile(QOpenGLShader::Vertex, "Shader/" + vertexFileName);
    prg.addShaderFromSourceCode(QOpenGLShader::Fragment, "Shader/" + fagmentFileName);
    if(geometryFileName != "")
        prg.addShaderFromSourceCode(QOpenGLShader::Geometry, "Shader/" + geometryFileName);
    prg.link();
    prg.bind();

    Add(strName, &prg);
}

QOpenGLShaderProgram* ShaderList::GetByName(QString strName)
{
    if(m_pListShader.contains(strName))
    {
        return m_pListShader.value(strName);
    }
    return 0;
}
void ShaderList::loadShaders(GameWindow* wnd)
{
    m_wnd = wnd;
    QDir dir = QDir(  QCoreApplication::applicationDirPath() );
    dir.cd(XmlShaderDir);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    dir.setNameFilters(QStringList()<<"*.rs");

    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);

       XmlShader* shader = XmlConfigReader::instance()->getShader(fileInfo.fileName());
       AddFromSource(shader->getName(), shader->getVertexShaderCode(), shader->getFragmentShaderCode(), shader->getGeometryShaderCode());
     }
}


void ShaderList::CreateInstance()
{


}
void ShaderList::DestroyInstance()
{
    foreach(QOpenGLShaderProgram *str, m_pListShader)
    {
        //code
        str->release();
        str->removeAllShaders();
    }
    m_pListShader.clear();
}

