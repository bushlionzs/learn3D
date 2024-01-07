

#include "elements/CEGUITextItemProperties.h"
#include "elements/CEGUITextItem.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{

namespace TextItemProperties
{

String TextXOffset::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const TextItem*>(receiver)->getTextXOffset());
}

void TextXOffset::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<TextItem*>(receiver)->setTextXOffset(PropertyHelper::stringToFloat(value));
}


String TextColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const TextItem*>(receiver)->getTextColour());
}


void TextColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<TextItem*>(receiver)->setTextColour(PropertyHelper::stringToColour(value));
}


String TextFormatting::get(const PropertyReceiver* receiver) const
{
	switch(static_cast<const TextItem*>(receiver)->getTextFormatting())
	{
	case RightAligned:
		return String((utf8*)"RightAligned");
		break;

	case Centred:
		return String((utf8*)"HorzCentred");
		break;

	case Justified:
		return String((utf8*)"HorzJustified");
		break;

	case WordWrapLeftAligned:
		return String((utf8*)"WordWrapLeftAligned");
		break;

	case WordWrapRightAligned:
		return String((utf8*)"WordWrapRightAligned");
		break;

	case WordWrapCentred:
		return String((utf8*)"WordWrapCentred");
		break;

	case WordWrapJustified:
		return String((utf8*)"WordWrapJustified");
		break;

	default:
		return String((utf8*)"LeftAligned");
		break;
	}
}


void TextFormatting::set(PropertyReceiver* receiver, const String& value)
{
	CEGUI::TextFormatting fmt;

	if (value == (utf8*)"RightAligned")
	{
		fmt = RightAligned;
	}
	else if (value == (utf8*)"HorzCentred")
	{
		fmt = Centred;
	}
	else if (value == (utf8*)"HorzJustified")
	{
		fmt = Justified;
	}
	else if (value == (utf8*)"WordWrapLeftAligned")
	{
		fmt = WordWrapLeftAligned;
	}
	else if (value == (utf8*)"WordWrapRightAligned")
	{
		fmt = WordWrapRightAligned;
	}
	else if (value == (utf8*)"WordWrapCentred")
	{
		fmt = WordWrapCentred;
	}
	else if (value == (utf8*)"WordWrapJustified")
	{
		fmt = WordWrapJustified;
	}
	else
	{
		fmt = LeftAligned;
	}

	static_cast<TextItem*>(receiver)->setTextFormatting(fmt);
}

} 
} 
