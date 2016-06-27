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
#include "qglen.h"
#include <QCoreApplication>
#include <QDir>
#include "xmlconfig.h"

XmlConfig* startQGlEn(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

     QDir( QCoreApplication::applicationDirPath() ).mkdir(XmlConfigDir);
     QDir( QCoreApplication::applicationDirPath() ).mkdir(XmlShaderDir);

#if  RAEDEBUG
     XmlShader* shader = new XmlShader();
     shader->setVertexShaderCode("in vec3 position;\n"
                                 "in vec3 color;\n"
                                 "out vec4 vColor;\n"
                                 "uniform highp mat4 matCamera;\n"
                                 "void main() {\n"
                                 "   gl_Position = matCamera * vec4(position, 1.0);\n"
                                 "   vColor = vec4(color, 1.0);\n"
                                 "}\n");
     shader->setFragmentShaderCode("in highp vec4 vColor;\n"
                                   "out highp vec4 fColor;\n"
                                   "void main() {\n"
                                   "   fColor = vColor;\n"
                                   "}\n");
     shader->setGeometryShaderCode("");
     shader->setName("ColorPosition");

     XmlConfigReader::instance()->saveShader(shader);
     delete shader;

     XmlConfigReader::instance()->saveConfig(XmlConfigReader::instance()->getConfig());
#endif

    return XmlConfigReader::instance()->getConfig();

}

void endQGlEn()
{

}
