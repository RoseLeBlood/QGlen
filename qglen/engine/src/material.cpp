#include "include/material.h"

QGLEN_BEGIN

Material::Material(Color ambient, Color diffuse, Color specular, float shininess, Color emission)
    : m_colAmbient(ambient), m_colDiffuse(diffuse), m_colSpecular(specular), m_fShininess(shininess),
      m_colEmission(emission)
{

}

QGLEN_END
