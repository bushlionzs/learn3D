

#include "CEGUISize.h"


namespace CEGUI
{

bool Size::operator==(const Size& other) const
{
	return d_width == other.d_width && d_height == other.d_height;
}


bool Size::operator!=(const Size& other) const
{
	return !operator==(other);
}


} 
