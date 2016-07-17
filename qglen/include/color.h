#ifndef COLOR_H
#define COLOR_H

#include "raengine_global.h"
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>

#define COLORCON (0.003921568627450980392156862745098f)

namespace qglen
{
    class RAENGINESHARED_EXPORT Color
    {
    public:
        union
        {
            struct
            {
                float r;
                float g;
                float b;
                float a;
            };
            struct
            {
                float red;
                float green;
                float blue;
                float alpa;
            };
            float c[4];
        };
        Color(void) 																																															{}
        Color(float _r, float _g, float _b, float _a)	: r(_r), g(_g), b(_b), a(_a)																															{}
        Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b), a(1.0f)																																	{}
        Color(float f) : r(f), g(f), b(f), a(f)																																								{}
        Color(float *com) : r(com[0]), g(com[1]), b(com[2]), a(com[3])																																	{}
        Color(const int _r, const int _g, const int _b) : r((float)(_r) * COLORCON), g((float)(_g) * COLORCON), b((float)(_b) * COLORCON), a(1.0f)														{}
        Color(const int _r, const int _g, const int _b, const int _a) : r((float)(_r) * COLORCON), g((float)(_g) * COLORCON), b((float)(_b) * COLORCON), a((float)(_a) * COLORCON)					{}
        Color(const int* pComponent) : r((float)(pComponent[0]) * COLORCON), g((float)(pComponent[1]) * COLORCON), b((float)(pComponent[2]) * COLORCON), a((float)(pComponent[3]) * COLORCON)		{}
        Color(const int c) : r(COLORCON * (float)(int)(c >> 16)), g(COLORCON * (float)(int)(c >> 8)), b(COLORCON * (float)(int)(c)), a(COLORCON * (float)(int)(c >> 24))							{}

        operator unsigned long () const
        {
            return ((a >= 1.0f ? 255 : a <= 0.0f ? 0 : (unsigned long)(a * 255.0f)) << 24) |
                   ((r >= 1.0f ? 255 : r <= 0.0f ? 0 : (unsigned long)(r * 255.0f)) << 16) |
                   ((g >= 1.0f ? 255 : g <= 0.0f ? 0 : (unsigned long)(g * 255.0f)) << 8)  |
                   (b >= 1.0f ? 255 : b <= 0.0f ? 0 : (unsigned long)(b * 255.0f));
        }
        operator float* ()			{return (float*)(c);}
        operator glm::vec3 ()       {return glm::vec3(r,g,b);}
        operator glm::vec4 ()       {return glm::vec4(r,g,b,a);}

        Color& operator = (const Color& c)	{a = c.a; b = c.b; g = c.g; r = c.r; return *this;}
        Color& operator += (const Color& c)	{r += c.r; g += c.g; b += c.b; a += c.a; return *this;}
        Color& operator -= (const Color& c)	{r -= c.r; g -= c.g; b -= c.b; a -= c.a; return *this;}
        Color& operator *= (const Color& c)	{r *= c.r; g *= c.g; b *= c.b; a *= c.a; return *this;}
        Color& operator *= (const float f)	{r *= f; g *= f; b *= f; a *= f; return *this;}
        Color& operator /= (const Color& c)	{r /= c.r; g /= c.g; b /= c.b; a /= c.a; return *this;}
        Color& operator /= (const float f)	{r /= f; g /= f; b /= f; a /= f; return *this;}

        static Color FromYUV(float y, float u, float v);
        static Color FromHSV(float h, float s, float v);
        static Color FromCMY(float c, float m, float y, float k = 0);
    };
    inline Color operator + (const Color& a, const Color& b)	{return Color(a.r + b.r, a.g + b.g, a.b + b.b, a.a + b.a);}
    inline Color operator - (const Color& a, const Color& b)	{return Color(a.r - b.r, a.g - b.g, a.b - b.b, a.a - b.a);}
    inline Color operator - (const Color& c)					{return Color(-c.r, -c.g, -c.b, c.a);}
    inline Color operator * (const Color& a, const Color& b)	{return Color(a.r * b.r, a.g * b.g, a.b * b.b, a.a * b.a);}
    inline Color operator * (const Color& c, const float f)		{return Color(c.r * f, c.g * f, c.b * f, c.a * f);}
    inline Color operator * (const float f, const Color& c)		{return Color(c.r * f, c.g * f, c.b * f, c.a * f);}
    inline Color operator / (const Color& a, const Color& b)	{return Color(a.r / b.r, a.g / b.g, a.b / b.b, a.a / b.a);}
    inline Color operator / (const Color& c, const float f)		{return Color(c.r / f, c.g / f, c.b / f, c.a / f);}

    // Vergleichsoperatoren
    inline bool operator == (const Color& a, const Color& b) {if(a.r != b.r) return false; if(a.g != b.g) return false; if(a.b != b.b) return false; return a.a == b.a;}
    inline bool operator != (const Color& a, const Color& b) {if(a.r != b.r) return true; if(a.g != b.g) return true; if(a.b != b.b) return true; return a.a != b.a;}

    // ******************************************************************
    // Funktionen deklarieren
    inline Color	ColorNegate(const Color& c)											{return Color(1.0f - c.r, 1.0f - c.g, 1.0f - c.b, 1.0f - c.a);}
    inline float	ColorBrightness(const Color& c)										{return c.r * 0.299f + c.g * 0.587f + c.b * 0.114f;}
    inline Color	ColorInterpolate(const Color& c1, const Color& c2, const float p)	{return c1 + p * (c2 - c1);}
    inline Color	ColorMin(const Color& c1, const Color& c2)
        {return Color(qMin(c1.r, c2.r), qMin(c1.g, c2.g), qMin(c1.b, c2.b), qMin(c1.a, c2.a));}
    inline Color	ColorMax(const Color& c1, const Color& c2)
        {return Color(qMax(c1.r, c2.r), qMax(c1.g, c2.g), qMax(c1.b, c2.b), qMax(c1.a, c2.a));}

}
#endif // COLOR_H
