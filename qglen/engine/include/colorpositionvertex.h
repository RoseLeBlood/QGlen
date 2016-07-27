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
    along with QGlEn.  If not, see <http://www.gnu.org/licenses/>.

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
#ifndef COLORPOSITIONVERTEX_H
#define COLORPOSITIONVERTEX_H

#include "ivertex.h"
#include "color.h"

QGLEN_BEGIN
class RAENGINESHARED_EXPORT ColorPositionVertex : IVertex
{
public:
  // Constructors
    ColorPositionVertex();
    explicit ColorPositionVertex(const glm::vec3 &position);
    ColorPositionVertex(const glm::vec2 &position);
    ColorPositionVertex(const glm::vec3 &position, const Color &color);

  // Accessors / Mutators
   const glm::vec3& getPosition() const;
   const Color& getColor() const;
  void setPosition(const glm::vec3& position);
  void setColor(const Color& color);

  // OpenGL Helpers
  static const int PositionTupleSize = 3;
  static const int ColorTupleSize = 3;
  static Q_DECL_CONSTEXPR int positionOffset();
  static Q_DECL_CONSTEXPR int colorOffset();
  static Q_DECL_CONSTEXPR int stride();
protected:
  glm::vec3 m_position;
  Color m_color;
};



// Constructors
 inline ColorPositionVertex::ColorPositionVertex() {}
 inline ColorPositionVertex::ColorPositionVertex(const glm::vec3 &position) : m_position(position) {}
 inline ColorPositionVertex::ColorPositionVertex(const glm::vec2 &position) : m_position(glm::vec3(position,1.0f)) { }
 inline ColorPositionVertex::ColorPositionVertex(const glm::vec3 &position, const Color &color) : m_position(position), m_color(color) {}

// Accessors / Mutators
 inline const glm::vec3& ColorPositionVertex::getPosition() const { return m_position; }
 inline const Color &ColorPositionVertex::getColor() const { return m_color; }
void inline ColorPositionVertex::setPosition(const glm::vec3& position) { m_position = position; }
void inline ColorPositionVertex::setColor(const Color &color) { m_color = color; }

Q_DECL_CONSTEXPR inline int ColorPositionVertex::positionOffset() { return offsetof(ColorPositionVertex, m_position); }
Q_DECL_CONSTEXPR inline int ColorPositionVertex::colorOffset() { return offsetof(ColorPositionVertex, m_color); }
Q_DECL_CONSTEXPR inline int ColorPositionVertex::stride() { return sizeof(ColorPositionVertex); }

QGLEN_END

Q_DECLARE_TYPEINFO(qglen::ColorPositionVertex, Q_MOVABLE_TYPE);

#endif // COLORPOSITIONVERTEX_H
