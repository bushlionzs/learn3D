

#include "elements/CEGUIListHeaderSegmentProperties.h"
#include "elements/CEGUIListHeaderSegment.h"
#include "CEGUIPropertyHelper.h"



namespace CEGUI
{


namespace ListHeaderSegmentProperties
{
String	Sizable::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const ListHeaderSegment*>(receiver)->isSizingEnabled());
}


void	Sizable::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<ListHeaderSegment*>(receiver)->setSizingEnabled(PropertyHelper::stringToBool(value));
}


String	Clickable::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const ListHeaderSegment*>(receiver)->isClickable());
}


void	Clickable::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<ListHeaderSegment*>(receiver)->setClickable(PropertyHelper::stringToBool(value));
}


String	Dragable::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const ListHeaderSegment*>(receiver)->isDragMovingEnabled());
}


void	Dragable::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<ListHeaderSegment*>(receiver)->setDragMovingEnabled(PropertyHelper::stringToBool(value));
}


String	SortDirection::get(const PropertyReceiver* receiver) const
{
	switch(static_cast<const ListHeaderSegment*>(receiver)->getSortDirection())
	{
	case ListHeaderSegment::Ascending:
		return String((utf8*)"Ascending");
		break;

	case ListHeaderSegment::Descending:
		return String((utf8*)"Descending");
		break;

	default:
		return String((utf8*)"None");
		break;
	}

}


void	SortDirection::set(PropertyReceiver* receiver, const String& value)
{
	ListHeaderSegment::SortDirection dir;

	if (value == (utf8*)"Ascending")
	{
		dir = ListHeaderSegment::Ascending;
	}
	else if (value == (utf8*)"Descending")
	{
		dir = ListHeaderSegment::Descending;
	}
	else
	{
		dir = ListHeaderSegment::None;
	}

	static_cast<ListHeaderSegment*>(receiver)->setSortDirection(dir);
}


} 

} 
