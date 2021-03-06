#include "include/color.h"

namespace qglen
{
Color Color::FromYUV(float y, float u, float v)
{
    float r = 1.164f * (y - 16) + 1.596f*(v - 128);
    float g = 1.164f * (y - 16) - 0.813f*(v - 128) - 0.391f*(u - 128);
    float b = 1.164f * (y - 16) + 2.018f*(u - 128);

    return Color(r, g, b);
}

Color Color::FromHSV(float h, float s, float v)
{
    float i;
        float f, p, q, t;
        if( s == 0 )
        {
            // achromatic (grey)
            return Color(v,v,v);
        }
        h /= 60;			// sector 0 to 5
        i = floor( h );
        f = h - i;			// factorial part of h
        p = v * ( 1 - s );
        q = v * ( 1 - s * f );
        t = v * ( 1 - s * ( 1 - f ) );

        if(i == 0)
            return Color(v, t, p);
        if( i == 1.0f)
            return Color(q, v, p);
        if(i == 2.0f)
            return Color(p, v, t);
        if(i == 3.0f)
            return Color(p, q, v);
        if(i == 4.0f)
            return Color(t, p, v);

        return Color(v, p, q);

}

Color Color::FromCMY(float c, float m, float y, float k)
{
    return Color( 1.0f - c * (1.0f - k), 1.0f - m * (1.0f - k), 1.0f - y * (1.0f - k));
}


Color Color::FromSRGB(float r, float g, float b, float a)
{
    float _r = ((r <= 0.04045f) ? (r / 12.92f) : ((float)pow((r + 0.055f) / 1.055f, 2.4f))),
          _g = ((g <= 0.04045f) ? (g / 12.92f) : ((float)pow((g + 0.055f) / 1.055f, 2.4f))),
          _b = ((b <= 0.04045f) ? (b / 12.92f) : ((float)pow((b + 0.055f) / 1.055f, 2.4f)));
   return Color(_r, _g, _b, a);
}
Color Color::ToSRGB(float r, float g, float b, float a)
{
    float _r = ((r <= 0.0031308) ? (r * 12.92f) : ((float)pow(r, 1.0f / 2.4f) - 0.055f )),
          _g = ((g <= 0.0031308) ? (g * 12.92f) : ((float)pow(g, 1.0f / 2.4f) - 0.055f )),
          _b = ((b <= 0.0031308) ? (b * 12.92f) : ((float)pow(b, 1.0f / 2.4f) - 0.055f ));
    return Color(_r, _g, _b, a);
}
}
