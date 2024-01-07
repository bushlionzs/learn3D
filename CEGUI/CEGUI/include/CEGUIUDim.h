

#ifndef _CEGUIUDim_h_
#define _CEGUIUDim_h_

#include "CEGUIRect.h"
#include "CEGUIVector.h"


#define cegui_absdim(x)     UDim(0,(x))
#define cegui_reldim(x)     UDim((x),0)



namespace CEGUI
{
    
    class CEGUIEXPORT UDim
    {
    public:
        UDim() {}
        UDim(float scale, float offset) : d_scale(scale), d_offset(offset) {}
        ~UDim() {}

        float asAbsolute(float base) const    { return PixelAligned(base * d_scale) + d_offset; }
        float asRelative(float base) const    { return (base != 0.0f) ? d_offset / base + d_scale : 0.0f; }

        UDim operator+(const UDim& other) const     { return UDim(d_scale + other.d_scale, d_offset + other.d_offset); }
        UDim operator-(const UDim& other) const     { return UDim(d_scale - other.d_scale, d_offset - other.d_offset); }
        UDim operator/(const UDim& other) const     { return UDim(d_scale / other.d_scale, d_offset / other.d_offset); }
        UDim operator*(const UDim& other) const     { return UDim(d_scale * other.d_scale, d_offset * other.d_offset); }

        const UDim& operator+=(const UDim& other)   { d_scale += other.d_scale; d_offset += other.d_offset; return *this; }
        const UDim& operator-=(const UDim& other)   { d_scale -= other.d_scale; d_offset -= other.d_offset; return *this; }
        const UDim& operator/=(const UDim& other)   { d_scale /= other.d_scale; d_offset /= other.d_offset; return *this; }
        const UDim& operator*=(const UDim& other)   { d_scale *= other.d_scale; d_offset *= other.d_offset; return *this; }

        bool operator==(const UDim& other) const    { return d_scale == other.d_scale && d_offset == other.d_offset; }
        bool operator!=(const UDim& other) const    { return !operator==(other); }

        float d_scale, d_offset;
    };

    
    class CEGUIEXPORT UVector2
    {
    public:
        UVector2() {}
        UVector2(const UDim& x, const UDim& y) : d_x(x), d_y(y) {}
        ~UVector2() {}

        Vector2 asAbsolute(const Size& base) const    { return Vector2(d_x.asAbsolute(base.d_width), d_y.asAbsolute(base.d_height)); }
        Vector2 asRelative(const Size& base) const    { return Vector2(d_x.asRelative(base.d_width), d_y.asRelative(base.d_height)); }

        UVector2 operator+(const UVector2& other) const     { return UVector2(d_x + other.d_x, d_y + other.d_y); }
        UVector2 operator-(const UVector2& other) const     { return UVector2(d_x - other.d_x, d_y - other.d_y); }
        UVector2 operator/(const UVector2& other) const     { return UVector2(d_x / other.d_x, d_y / other.d_y); }
        UVector2 operator*(const UVector2& other) const     { return UVector2(d_x * other.d_x, d_y * other.d_y); }

        const UVector2& operator+=(const UVector2& other)   { d_x += other.d_x; d_y += other.d_y; return *this; }
        const UVector2& operator-=(const UVector2& other)   { d_x -= other.d_x; d_y -= other.d_y; return *this; }
        const UVector2& operator/=(const UVector2& other)   { d_x /= other.d_x; d_y /= other.d_y; return *this; }
        const UVector2& operator*=(const UVector2& other)   { d_x *= other.d_x; d_y *= other.d_y; return *this; }
        
        bool operator==(const UVector2& other) const    { return d_x == other.d_x && d_y == other.d_y; }
        bool operator!=(const UVector2& other) const    { return !operator==(other); }

        UDim d_x, d_y;
    };

    
    class CEGUIEXPORT URect
    {
    public:
        URect() {}
        
        URect(const UVector2& min, const UVector2& max) : d_min(min), d_max(max) {}
        
        URect(const UDim& left, const UDim& top, const UDim& right, const UDim& bottom)
        {
            d_min.d_x = left;
            d_min.d_y = top;
            d_max.d_x = right;
            d_max.d_y = bottom;
        }
        
        ~URect() {}
    
        Rect asAbsolute(const Size& base) const
        {
            return Rect(
                    d_min.d_x.asAbsolute(base.d_width),
                    d_min.d_y.asAbsolute(base.d_height),
                    d_max.d_x.asAbsolute(base.d_width),
                    d_max.d_y.asAbsolute(base.d_height)
                );
        }

        Rect asRelative(const Size& base) const
        {
            return Rect(
                    d_min.d_x.asRelative(base.d_width),
                    d_min.d_y.asRelative(base.d_height),
                    d_max.d_x.asRelative(base.d_width),
                    d_max.d_y.asRelative(base.d_height)
                );
        }

        const UVector2& getPosition() const     { return d_min; }
        UVector2 getSize() const                { return d_max - d_min; }
        UDim getWidth() const                   { return d_max.d_x - d_min.d_x; }
        UDim getHeight() const                  { return d_max.d_y - d_min.d_y; }

        void setPosition(const UVector2& pos)
        {
            UVector2 sz(d_max - d_min);
            d_min = pos;
            d_max = d_min + sz;
        }

        void setSize(const UVector2& sz)
        {
            d_max = d_min + sz;
        }

        void setWidth(const UDim& w)        { d_max.d_x = d_min.d_x + w; }
        void setHeight(const UDim& h)       { d_max.d_y = d_min.d_y + h; }

        void offset(const UVector2& sz)
        {
            d_min += sz;
            d_max += sz;
        }
        
        UVector2 d_min, d_max;
    };

} 


#endif  
