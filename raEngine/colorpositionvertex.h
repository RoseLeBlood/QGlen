#ifndef COLORPOSITIONVERTEX_H
#define COLORPOSITIONVERTEX_H

#include "raengine_global.h"

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

class RAENGINESHARED_EXPORT IVertex
{

};


class RAENGINESHARED_EXPORT ColorPositionVertex : IVertex
{
public:
  // Constructors
    ColorPositionVertex();
    explicit ColorPositionVertex(const glm::vec3 &position);
    ColorPositionVertex(const glm::vec2 &position);
    ColorPositionVertex(const glm::vec3 &position, const glm::vec3 &color);

  // Accessors / Mutators
   const glm::vec3& getPosition() const;
   const glm::vec3& getColor() const;
  void setPosition(const glm::vec3& position);
  void setColor(const glm::vec3& color);

  // OpenGL Helpers
  static const int PositionTupleSize = 3;
  static const int ColorTupleSize = 3;
  static Q_DECL_CONSTEXPR int positionOffset();
  static Q_DECL_CONSTEXPR int colorOffset();
  static Q_DECL_CONSTEXPR int stride();
protected:
  glm::vec3 m_position;
  glm::vec3 m_color;
};

Q_DECLARE_TYPEINFO(ColorPositionVertex, Q_MOVABLE_TYPE);

// Constructors
 inline ColorPositionVertex::ColorPositionVertex() {}
 inline ColorPositionVertex::ColorPositionVertex(const glm::vec3 &position) : m_position(position) {}
 inline ColorPositionVertex::ColorPositionVertex(const glm::vec2 &position) : m_position(glm::vec3(position,1.0f)) { }
 inline ColorPositionVertex::ColorPositionVertex(const glm::vec3 &position, const glm::vec3 &color) : m_position(position), m_color(color) {}

// Accessors / Mutators
 inline const glm::vec3& ColorPositionVertex::getPosition() const { return m_position; }
 inline const glm::vec3& ColorPositionVertex::getColor() const { return m_color; }
void inline ColorPositionVertex::setPosition(const glm::vec3& position) { m_position = position; }
void inline ColorPositionVertex::setColor(const glm::vec3 &color) { m_color = color; }

Q_DECL_CONSTEXPR inline int ColorPositionVertex::positionOffset() { return offsetof(ColorPositionVertex, m_position); }
Q_DECL_CONSTEXPR inline int ColorPositionVertex::colorOffset() { return offsetof(ColorPositionVertex, m_color); }
Q_DECL_CONSTEXPR inline int ColorPositionVertex::stride() { return sizeof(ColorPositionVertex); }



#endif // COLORPOSITIONVERTEX_H
