

#include "CEGUIRect.h"


namespace CEGUI
{

Rect::Rect(float left, float top, float right, float bottom) :
	d_top(top),
	d_bottom(bottom),
	d_left(left),
	d_right(right)
{
}

Rect::Rect(Point pos, Size sz) :
    d_top(pos.d_y),
    d_bottom(pos.d_y + sz.d_height),
    d_left(pos.d_x),
    d_right(pos.d_x + sz.d_width)
{
}



Rect Rect::getIntersection(const Rect& rect) const
{
	
	if ((d_right > rect.d_left) &&
		(d_left < rect.d_right) &&
		(d_bottom > rect.d_top) &&
		(d_top < rect.d_bottom))
	{
		Rect temp;

		
		temp.d_left = (d_left > rect.d_left) ? d_left : rect.d_left;
		temp.d_right = (d_right < rect.d_right) ? d_right : rect.d_right;
		temp.d_top = (d_top > rect.d_top) ? d_top : rect.d_top;
		temp.d_bottom = (d_bottom < rect.d_bottom) ? d_bottom : rect.d_bottom;

		return temp;
	}
	else
	{
		return Rect(0.0f, 0.0f, 0.0f, 0.0f);
	}

}


Rect& Rect::offset(const Point& pt)
{
	d_left		+= pt.d_x;
	d_right		+= pt.d_x;
	d_top		+= pt.d_y;
	d_bottom	+= pt.d_y;
	return *this;
}



bool Rect::isPointInRect(const Point& pt) const
{
	if ((d_left > pt.d_x) ||
		(d_right <= pt.d_x) ||
		(d_top > pt.d_y) ||
		(d_bottom <= pt.d_y))
	{
		return false;
	}

	return true;
}


void Rect::setPosition(const Point& pt)
{
	Size sz(getSize());

	d_left = pt.d_x;
	d_top  = pt.d_y;
	setSize(sz);
}



Rect& Rect::constrainSizeMax(const Size& sz)
{
	if (getWidth() > sz.d_width)
	{
		setWidth(sz.d_width);
	}

	if (getHeight() > sz.d_height)
	{
		setHeight(sz.d_height);
	}

	return *this;
}



Rect& Rect::constrainSizeMin(const Size& sz)
{
	if (getWidth() < sz.d_width)
	{
		setWidth(sz.d_width);
	}

	if (getHeight() < sz.d_height)
	{
		setHeight(sz.d_height);
	}

	return *this;
}



Rect& Rect::constrainSize(const Size& max_sz, const Size& min_sz)
{
	Size curr_sz(getSize());

	if (curr_sz.d_width > max_sz.d_width)
	{
		setWidth(max_sz.d_width);
	}
	else if (curr_sz.d_width < min_sz.d_width)
	{
		setWidth(min_sz.d_width);
	}

	if (curr_sz.d_height > max_sz.d_height)
	{
		setHeight(max_sz.d_height);
	}
	else if (curr_sz.d_height < min_sz.d_height)
	{
		setHeight(min_sz.d_height);
	}

	return *this;
}

Rect& Rect::operator=(const Rect& rhs)
{
	d_left = rhs.d_left;
	d_top = rhs.d_top;
	d_right = rhs.d_right;
	d_bottom = rhs.d_bottom;

	return *this;
}

} 
