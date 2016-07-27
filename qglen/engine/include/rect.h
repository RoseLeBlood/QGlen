#ifndef RECT_H
#define RECT_H

#include <raengine_global.h>
#include <glm/vec2.hpp>

QGLEN_BEGIN

class RAENGINESHARED_EXPORT rect
{
public:
    union
    {
        struct
        {
            long left;
            long top;
            long right;
            long bottom;
        };
        struct
        {
            long x1, x2;
            long y1, y2;
        };
        long	r[4];
    };

    rect(void) 																										{}
    rect(const rect& _r)	: left(_r.left), top(_r.top), right(_r.right), bottom(_r.bottom)						{}
    rect(const long& _r)	: left(_r), top(_r), right(_r), bottom(_r)													{}
    rect(const long& _l, const long& _t, const long& _r, const long& _b) : left(_l), top(_t), right(_r), bottom(_b)	{}
    rect(const long* _lpl) : left(_lpl[0]), top(_lpl[1]), right(_lpl[2]), bottom(_lpl[3])							{}
    rect(glm::vec2 p, float w, float h) : left(p.x), top(p.y), right(p.x + w), bottom(p.y + h) {}

    operator long* ()							{ return (long*)(r); }
    operator void* ()							{ return (void*)(r); }

    float getWidth() { return right - left; }
    float getHeight() { return bottom - top; }

    void setWidth(float w) { right = left + w; }
    void setHeight(float h) { bottom = top + h; }

    glm::vec2 getPosition() { return glm::vec2(left, top); }
    void setPosition(glm::vec2 p) { left = p.x; top = p.y; }

    rect operator =  (const rect& r)		{ left = r.left; top = r.top; right = r.right; bottom = r.bottom; return *this; }
    rect operator += (const rect& r)		{ left += r.left; top += r.top; right += r.right; bottom += r.bottom; return *this; }
    rect operator -= (const rect& r)		{ left -= r.left; top -= r.top; right -= r.right; bottom -= r.bottom; return *this; }
    rect operator *= (const rect& r)		{ left *= r.left; top *= r.top; right *= r.right; bottom *= r.bottom; return *this; }
    rect operator /= (const rect& r)		{ left /= r.left; top /= r.top; right /= r.right; bottom /= r.bottom; return *this; }

    rect operator =  (const long l)			{ left = l; top = l; right = l; bottom = l; return *this; }
    rect operator += (const long l)			{ left += l; top += l; right += l; bottom += l; return *this; }
    rect operator -= (const long l)			{ left -= l; top -= l; right -= l; bottom -= l; return *this; }
    rect operator *= (const long l)			{ left *= l; top *= l; right *= l; bottom *= l; return *this; }
    rect operator /= (const long l)			{ left /= l; top /= l; right /= l; bottom /= l; return *this; }
};

QGLEN_END

#endif // RECT_H
