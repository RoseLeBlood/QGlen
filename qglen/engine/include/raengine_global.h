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
#ifndef RAENGINE_GLOBAL_H
#define RAENGINE_GLOBAL_H

#include <QtCore/qglobal.h>


#if defined(RAENGINE_LIBRARY)
#  define RAENGINESHARED_EXPORT Q_DECL_EXPORT
#else
#  define RAENGINESHARED_EXPORT Q_DECL_IMPORT
#endif


#define XmlShaderVersion 0x01001 // version 1.00-1
#define XmlConfigVersion 0x01015 // version 1.01-5

#define XmlConfigDir "config"
#define XmlConfigFile "config.cfg"
#define XmlShaderDir "shader"

#define QGLEN_BEGIN namespace qglen {
#define QGLEN_END }


#endif // RAENGINE_GLOBAL_H
