

#ifndef _CEGUITextItemProperties_h_
#define _CEGUITextItemProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{

namespace TextItemProperties
{


class TextXOffset : public Property
{
public:
	TextXOffset() : Property(
		"TextXOffset",
		"Property to get/set the X offset of the text on the item.  Value is a float.",
		"0.000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class TextColour : public Property
{
public:
	TextColour() : Property(
		"TextColour",
		"Property to get/set the text colour of the item.  Value is a colour.",
		"00FFFFFF")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class TextFormatting : public Property
{
public:
	TextFormatting() : Property(
		"TextFormatting",
		"Property to get/set the horizontal formatting mode.  Value is one of the HorzFormatting strings.",
		"LeftAligned")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

} 
} 

#endif	
