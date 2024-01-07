

#include "elements/CEGUIThumbProperties.h"
#include "elements/CEGUIThumb.h"
#include "CEGUIPropertyHelper.h"
#include <stdio.h>


namespace CEGUI
{


namespace ThumbProperties
{
String	HotTracked::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Thumb*>(receiver)->isHotTracked());
}


void	HotTracked::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Thumb*>(receiver)->setHotTracked(PropertyHelper::stringToBool(value));
}


String	VertFree::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Thumb*>(receiver)->isVertFree());
}


void	VertFree::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Thumb*>(receiver)->setVertFree(PropertyHelper::stringToBool(value));
}


String	HorzFree::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Thumb*>(receiver)->isHorzFree());
}


void	HorzFree::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Thumb*>(receiver)->setHorzFree(PropertyHelper::stringToBool(value));
}


String	VertRange::get(const PropertyReceiver* receiver) const
{
	using namespace std;
	char buff[64];

	pair<float, float> range = static_cast<const Thumb*>(receiver)->getVertRange();
	sprintf(buff, "min:%f max:%f", range.first, range.second);

	return String((utf8*)buff);
}


void	VertRange::set(PropertyReceiver* receiver, const String& value)
{
	using namespace std;

	float rangeMin = 0, rangeMax = 0;
	sscanf(value.c_str(), " min:%f max:%f", &rangeMin, &rangeMax);

	static_cast<Thumb*>(receiver)->setVertRange(rangeMin, rangeMax);
}


String	HorzRange::get(const PropertyReceiver* receiver) const
{
	using namespace std;

	char buff[64];
	pair<float, float> range = static_cast<const Thumb*>(receiver)->getHorzRange();
	sprintf(buff, "min:%f max:%f", range.first, range.second);

	return String((utf8*)buff);
}


void	HorzRange::set(PropertyReceiver* receiver, const String& value)
{
	using namespace std;

	float rangeMin = 0, rangeMax = 0;
	sscanf(value.c_str(), " min:%f max:%f", &rangeMin, &rangeMax);

	static_cast<Thumb*>(receiver)->setHorzRange(rangeMin, rangeMax);
}


} 

} 
