#ifndef MATERIAL_H
#define MATERIAL_H

#include <colors.h>

QGLEN_BEGIN

class RAENGINESHARED_EXPORT Material
{
public:
    Material() : Material(Colors::Orange, Colors::Gray, Colors::White, 0.2f) { }
    Material(Color ambient, Color diffuse, Color specular, float shininess = 32.0f, Color emission = Colors::Black);

    void setAmbient(Color am) { m_colAmbient = am; }
    void setDiffuse(Color df) { m_colDiffuse = df; }
    void setSpecular(Color sp){ m_colSpecular = sp; }
    void setShininess(float f) { m_fShininess = f; }
    void setEmission(Color ef) { m_colEmission = ef; }

    Color getAmbient() { return m_colAmbient; }
    Color getDiffuse() { return m_colDiffuse; }
    Color getSpecular() { return m_colSpecular; }
    float getShininess() { return m_fShininess; }
    Color getEmission() { return m_colEmission; }

private:
    Color m_colAmbient;
    Color m_colDiffuse;
    Color m_colSpecular;
    Color m_colEmission;
    float m_fShininess;
};

QGLEN_END

#endif // MATERIAL_H
