

#ifndef _CEGUIVector_h_
#define _CEGUIVector_h_

#include "CEGUIBase.h"
#include "CEGUISize.h"



namespace CEGUI
{


class CEGUIEXPORT Vector2
{
public:
	Vector2(void) {}
	Vector2(float x, float y) : d_x(x), d_y(y) {}

	Vector2& operator*=(const Vector2& vec)
	{
		d_x *= vec.d_x;
		d_y *= vec.d_y;

		return *this;
	}

	Vector2& operator/=(const Vector2& vec)
	{
		d_x /= vec.d_x;
		d_y /= vec.d_y;

		return *this;
	}

	Vector2& operator+=(const Vector2& vec)
	{
		d_x += vec.d_x;
		d_y += vec.d_y;

		return *this;
	}

	Vector2& operator-=(const Vector2& vec)
	{
		d_x -= vec.d_x;
		d_y -= vec.d_y;

		return *this;
	}

	Vector2	operator+(const Vector2& vec) const
	{
		return Vector2(d_x + vec.d_x, d_y + vec.d_y);
	}

	Vector2	operator-(const Vector2& vec) const
	{
		return Vector2(d_x - vec.d_x, d_y - vec.d_y);
	}

	Vector2	operator*(const Vector2& vec) const
	{
		return Vector2(d_x * vec.d_x, d_y * vec.d_y);
	}

	bool	operator==(const Vector2& vec) const
	{
		return ((d_x == vec.d_x) && (d_y == vec.d_y));
	}

	bool	operator!=(const Vector2& vec) const
	{
		return !(operator==(vec));
	}

    Size asSize() const     { return Size(d_x, d_y); }

	float d_x, d_y;
};


typedef	Vector2		Point;



class CEGUIEXPORT Vector3
{
public:
	Vector3(void) {}
	Vector3(float x, float y, float z) : d_x(x), d_y(y), d_z(z) {}

	float	d_x, d_y, d_z;
};

} 


#endif	
