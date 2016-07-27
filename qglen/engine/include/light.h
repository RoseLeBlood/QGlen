#ifndef LIGHT_H
#define LIGHT_H

#include <raengine_global.h>
#include <colors.h>

QGLEN_BEGIN

class RAENGINESHARED_EXPORT Light
{
public:
    Light() : m_colAmbient(Colors::Black), m_colDiffuse(Colors::Blue), m_colSpecular(Colors::Blue) { }
    Light(const Color Ambient, const Color Diffuse, const Color Specular)
        : m_colAmbient(Ambient), m_colDiffuse(Diffuse), m_colSpecular(Specular) { }
    Light(const Light& o) : m_colAmbient(o.m_colAmbient), m_colDiffuse(o.m_colDiffuse),
        m_colSpecular(o.m_colSpecular), m_bEnable(o.m_bEnable) { }

    void setAmbient(Color ambient) { m_colAmbient = ambient; }
    void setDiffuse(Color diffuse) { m_colDiffuse = diffuse; }
    void setSpecular(Color specular) { m_colSpecular = specular; }
    void setEnable(bool enable)     { m_bEnable = enable; }
    void setPosition(glm::vec3 position)  { m_vecPosition = position; }

    Color getAmbient() { return m_colAmbient; }
    Color getDiffuse() { return m_colDiffuse; }
    Color getSpecular() { return m_colSpecular; }
    glm::vec3   getPosition()           { return m_vecPosition; }


    bool  IsEnable()   { return m_bEnable; }
protected:
    glm::vec3 m_vecPosition;
    Color   m_colAmbient;
    Color   m_colDiffuse;
    Color   m_colSpecular;
    bool    m_bEnable;
};
class RAENGINESHARED_EXPORT DirLight : public Light
{
public:
    DirLight(glm::vec3 direction = glm::vec3(-0.2f, -0.2f, -0.2f))
        : m_vecDirection(direction) { }
    DirLight(Color Ambient, Color Diffuse, Color Specular,
             glm::vec3 direction = glm::vec3(-0.2f, -0.2f, -0.2f))
        : Light(Ambient, Diffuse, Specular), m_vecDirection(direction) { }
    DirLight(const DirLight& o) : Light(o), m_vecDirection(o.m_vecDirection) { }

    void setDirection(glm::vec3 direction)  { m_vecDirection = direction; }
    glm::vec3 getDirection()                { return m_vecDirection; }
protected:
    glm::vec3 m_vecDirection;
};

class RAENGINESHARED_EXPORT PointLight : public DirLight
{
public:
    PointLight() : PointLight(glm::vec3(1.0f, 1.0f, 1.0f)) { }

    PointLight(glm::vec3 position, float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f)
        : DirLight(), m_fConstant(constant), m_fLinear(linear), m_fQuadratic(quadratic) { m_vecPosition = (position); }

    PointLight(const Color Ambient, const Color Diffuse, const Color Specular,
               glm::vec3 position, float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f)
        : DirLight(Ambient, Diffuse, Specular ),
          m_fConstant(constant), m_fLinear(linear), m_fQuadratic(quadratic) { m_vecPosition = (position); }
    PointLight(const PointLight& o) : DirLight(o), m_fConstant(o.m_fConstant),
        m_fLinear(o.m_fLinear), m_fQuadratic(o.m_fQuadratic)    { m_vecPosition = o.m_vecPosition; }


    void setConstant(float constant)      { m_fConstant = constant; }
    void setLinear(float linear)          { m_fLinear = linear; }
    void setQuadratic(float quadratic)    { m_fQuadratic = quadratic; }


    float       getConstant()           { return m_fConstant; }
    float       getLinear()             { return m_fLinear; }
    float       getQuadratic()          { return m_fQuadratic; }
protected:
    float m_fConstant;
    float m_fLinear;
    float m_fQuadratic;
};

class RAENGINESHARED_EXPORT SpotLight : public PointLight
{
public:
    SpotLight(glm::vec3 position,
              glm::vec3 direction = glm::vec3(-0.2f, -0.2f, -0.2f),
              float cutoff = 7.0f, float outercutoff = 10.0f,
              float constant = 1.0f, float linear = 0.07f, float quadratic = 0.07f)
        :  PointLight(position, constant, linear, quadratic),
           m_fCutOff(cutoff), m_fOuterCutOff(outercutoff) { m_vecDirection = direction; }

    SpotLight(Color Ambient, Color Diffuse, Color Specular,
            glm::vec3 position,
            glm::vec3 direction = glm::vec3(-0.2f, -0.2f, -0.2f),
            float cutoff = 7.0f, float outercutoff = 10.0f,
            float constant = 1.0f, float linear = 0.07f, float quadratic = 0.07f)
        : PointLight(Ambient, Diffuse,Specular, position,
                     constant, linear, quadratic),
          m_fCutOff(cutoff), m_fOuterCutOff(outercutoff) { m_vecDirection = direction; }

    SpotLight(const SpotLight& o)
        : PointLight(o), m_fCutOff(o.m_fCutOff), m_fOuterCutOff(o.m_fOuterCutOff) { m_vecDirection = o.m_vecDirection; }

    float getCufOff()       { return m_fCutOff; }
    float getOuterCutOff()  { return m_fOuterCutOff; }

    void setCutOff(float cutoff) { m_fCutOff = cutoff; }
    void setOuterCutOff(float ocutoff) { m_fOuterCutOff = ocutoff; }
protected:
    float m_fCutOff;
    float m_fOuterCutOff;
};

QGLEN_END

#endif // LIGHT_H
