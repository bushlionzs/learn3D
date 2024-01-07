

#include "elements/CEGUIStaticTextProperties.h"
#include "elements/CEGUIStaticText.h"
#include "CEGUIPropertyHelper.h"



namespace CEGUI
{


namespace StaticTextProperties
{
String	TextColours::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourRectToString(static_cast<const StaticText*>(receiver)->getTextColours());
}


void	TextColours::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<StaticText*>(receiver)->setTextColours(PropertyHelper::stringToColourRect(value));
}


String	HorzFormatting::get(const PropertyReceiver* receiver) const
{
	switch(static_cast<const StaticText*>(receiver)->getHorizontalFormatting())
	{
	case StaticText::RightAligned:
		return String((utf8*)"RightAligned");
		break;

	case StaticText::HorzCentred:
		return String((utf8*)"HorzCentred");
		break;

	case StaticText::HorzJustified:
		return String((utf8*)"HorzJustified");
		break;

	case StaticText::WordWrapLeftAligned:
		return String((utf8*)"WordWrapLeftAligned");
		break;

	case StaticText::WordWrapRightAligned:
		return String((utf8*)"WordWrapRightAligned");
		break;

	case StaticText::WordWrapCentred:
		return String((utf8*)"WordWrapCentred");
		break;

	case StaticText::WordWrapJustified:
		return String((utf8*)"WordWrapJustified");
		break;

	default:
		return String((utf8*)"LeftAligned");
		break;
	}
}


void	HorzFormatting::set(PropertyReceiver* receiver, const String& value)
{
	StaticText::HorzFormatting fmt;

	if (value == (utf8*)"RightAligned")
	{
		fmt = StaticText::RightAligned;
	}
	else if (value == (utf8*)"HorzCentred")
	{
		fmt = StaticText::HorzCentred;
	}
	else if (value == (utf8*)"HorzJustified")
	{
		fmt = StaticText::HorzJustified;
	}
	else if (value == (utf8*)"WordWrapLeftAligned")
	{
		fmt = StaticText::WordWrapLeftAligned;
	}
	else if (value == (utf8*)"WordWrapRightAligned")
	{
		fmt = StaticText::WordWrapRightAligned;
	}
	else if (value == (utf8*)"WordWrapCentred")
	{
		fmt = StaticText::WordWrapCentred;
	}
	else if (value == (utf8*)"WordWrapJustified")
	{
		fmt = StaticText::WordWrapJustified;
	}
	else
	{
		fmt = StaticText::LeftAligned;
	}

	static_cast<StaticText*>(receiver)->setHorizontalFormatting(fmt);
}


String	VertFormatting::get(const PropertyReceiver* receiver) const
{
	switch(static_cast<const StaticText*>(receiver)->getVerticalFormatting())
	{
	case StaticText::BottomAligned:
		return String((utf8*)"BottomAligned");
		break;

	case StaticText::VertCentred:
		return String((utf8*)"VertCentred");
		break;

	default:
		return String((utf8*)"TopAligned");
		break;
	}
}


void	VertFormatting::set(PropertyReceiver* receiver, const String& value)
{
	StaticText::VertFormatting fmt;

	if (value == (utf8*)"BottomAligned")
	{
		fmt = StaticText::BottomAligned;
	}
	else if (value == (utf8*)"VertCentred")
	{
		fmt = StaticText::VertCentred;
	}
	else
	{
		fmt = StaticText::TopAligned;
	}

	static_cast<StaticText*>(receiver)->setVerticalFormatting(fmt);
}


String	VertScrollbar::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const StaticText*>(receiver)->isVerticalScrollbarEnabled());
}


void	VertScrollbar::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<StaticText*>(receiver)->setVerticalScrollbarEnabled(PropertyHelper::stringToBool(value));
}

String	HorzScrollbar::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const StaticText*>(receiver)->isHorizontalScrollbarEnabled());
}


void	HorzScrollbar::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<StaticText*>(receiver)->setHorizontalScrollbarEnabled(PropertyHelper::stringToBool(value));
}


String	TextScale::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::sizeToString(static_cast<const StaticText*>(receiver)->getTextScale());
}


void	TextScale::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<StaticText*>(receiver)->setTextScale(PropertyHelper::stringToSize(value));
}



} 

} 
