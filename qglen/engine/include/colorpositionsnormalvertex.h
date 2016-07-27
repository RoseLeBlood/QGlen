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
#ifndef COLORPOSITIONSNORMALVERTEX_H
#define COLORPOSITIONSNORMALVERTEX_H

#include "ivertex.h"

QGLEN_BEGIN

class RAENGINESHARED_EXPORT PositionsNormalVertex : IVertex
{
public:
  // Constructors
    PositionsNormalVertex();
    explicit PositionsNormalVertex(const glm::vec3 &position, const glm::vec3 &normal);

  // Accessors / Mutators
   const glm::vec3& getPosition() const;
   const glm::vec3& getNormal() const;
  void setPosition(const glm::vec3& position);
  void setNormal(const glm::vec3& normal);

  // OpenGL Helpers
  static const int PositionTupleSize = 3;
  static const int NormalTupleSize = 3;
  static Q_DECL_CONSTEXPR int positionOffset();
  static Q_DECL_CONSTEXPR int normalOffset();
  static Q_DECL_CONSTEXPR int stride();
protected:
  glm::vec3 m_position;
  glm::vec3 m_normal;

};



// Constructors
 inline PositionsNormalVertex::PositionsNormalVertex() {}
 inline PositionsNormalVertex::PositionsNormalVertex(const glm::vec3 &position, const glm::vec3 &normal) : m_position(position), m_normal(normal) {}

// Accessors / Mutators
 inline const glm::vec3& PositionsNormalVertex::getPosition() const { return m_position; }
 inline const glm::vec3& PositionsNormalVertex::getNormal() const { return m_normal; }
void inline PositionsNormalVertex::setPosition(const glm::vec3& position) { m_position = position; }
void inline PositionsNormalVertex::setNormal(const glm::vec3 &normal) { m_normal = normal; }

Q_DECL_CONSTEXPR inline int PositionsNormalVertex::positionOffset() { return offsetof(PositionsNormalVertex, m_position); }
Q_DECL_CONSTEXPR inline int PositionsNormalVertex::normalOffset() { return offsetof(PositionsNormalVertex, m_normal); }
Q_DECL_CONSTEXPR inline int PositionsNormalVertex::stride() { return sizeof(PositionsNormalVertex); }


QGLEN_END

Q_DECLARE_TYPEINFO(qglen::PositionsNormalVertex, Q_MOVABLE_TYPE);

#endif // COLORPOSITIONSNORMALVERTEX_H
