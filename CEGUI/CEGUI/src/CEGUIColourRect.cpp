

#include "CEGUIColourRect.h"




namespace CEGUI
{

ColourRect::ColourRect(const colour& top_left, const colour& top_right, const colour& bottom_left, const colour& bottom_right) :
	d_top_left(top_left),
	d_top_right(top_right),
	d_bottom_left(bottom_left),
	d_bottom_right(bottom_right)
{
}


ColourRect::ColourRect(const colour& col) :
	d_top_left(col),
	d_top_right(col),
	d_bottom_left(col),
	d_bottom_right(col)
{
}



ColourRect::ColourRect(void) :
	d_top_left(),
	d_top_right(),
	d_bottom_left(),
	d_bottom_right()
{
}



void ColourRect::setAlpha(float alpha)
{
	d_top_left.setAlpha(alpha);
	d_top_right.setAlpha(alpha);
	d_bottom_left.setAlpha(alpha);
	d_bottom_right.setAlpha(alpha);
}



void ColourRect::setTopAlpha(float alpha)
{
	d_top_left.setAlpha(alpha);
	d_top_right.setAlpha(alpha);
}



void ColourRect::setBottomAlpha(float alpha)
{
	d_bottom_left.setAlpha(alpha);
	d_bottom_right.setAlpha(alpha);
}



void ColourRect::setLeftAlpha(float alpha)
{
	d_top_left.setAlpha(alpha);
	d_bottom_left.setAlpha(alpha);
}



void ColourRect::setRightAlpha(float alpha)
{
	d_top_right.setAlpha(alpha);
	d_bottom_right.setAlpha(alpha);
}


bool ColourRect::isMonochromatic() const
{
	return d_top_left == d_top_right &&
		   d_top_left == d_bottom_left &&
		   d_top_left == d_bottom_right;
}


colour ColourRect::getColourAtPoint( float x, float y ) const
{
    colour h1((d_top_right - d_top_left) * x + d_top_left);
	colour h2((d_bottom_right - d_bottom_left) * x + d_bottom_left);
	return colour((h2 - h1) * y + h1);
}


ColourRect ColourRect::getSubRectangle( float left, float right, float top, float bottom ) const
{
	return ColourRect(
		getColourAtPoint(left, top),
		getColourAtPoint(right, top),
		getColourAtPoint(left, bottom),
		getColourAtPoint(right, bottom)
	);
}



void ColourRect::setColours(const colour& col)
{
	d_top_left = d_top_right = d_bottom_left = d_bottom_right = col;
}



void ColourRect::modulateAlpha(float alpha)
{
	d_top_left.setAlpha(d_top_left.getAlpha()*alpha);
	d_top_right.setAlpha(d_top_right.getAlpha()*alpha);
	d_bottom_left.setAlpha(d_bottom_left.getAlpha()*alpha);
	d_bottom_right.setAlpha(d_bottom_right.getAlpha()*alpha);
}


ColourRect& ColourRect::operator *=(const ColourRect& other)
{
    d_top_left *= other.d_top_left;
    d_top_right *= other.d_top_right;
    d_bottom_left *= other.d_bottom_left;
    d_bottom_right *= other.d_bottom_right;

    return *this;
}


} 
