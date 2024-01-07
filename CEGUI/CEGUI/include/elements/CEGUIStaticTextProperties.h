

#ifndef _CEGUIStaticTextProperties_h_
#define _CEGUIStaticTextProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{



namespace StaticTextProperties
{

class TextColours : public Property
{
public:
	TextColours() : Property(
		"TextColours",
		"Property to get/set the text colours for the StaticText widget.  Value is \"tl:[aarrggbb] tr:[aarrggbb] bl:[aarrggbb] br:[aarrggbb]\".",
		"tl:FFFFFFFF tr:FFFFFFFF bl:FFFFFFFF br:FFFFFFFF")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

class TextScale: public Property
{
public:
	TextScale() : Property(
		"TextScale",
		"Property to get/set the text colours for the StaticText widget.  Value is \"tl:[aarrggbb] tr:[aarrggbb] bl:[aarrggbb] br:[aarrggbb]\".",
		"x:1 y:1")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


class HorzFormatting : public Property
{
public:
	HorzFormatting() : Property(
		"HorzFormatting",
		"Property to get/set the horizontal formatting mode.  Value is one of the HorzFormatting strings.",
		"LeftAligned")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class VertFormatting : public Property
{
public:
	VertFormatting() : Property(
		"VertFormatting",
		"Property to get/set the vertical formatting mode.  Value is one of the VertFormatting strings.",
		"VertCentred")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class VertScrollbar : public Property
{
public:
	VertScrollbar() : Property(
		"VertScrollbar",
		"Property to get/set the setting for the vertical scroll bar.  Value is either \"True\" or \"False\".",
		"False")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class HorzScrollbar : public Property
{
public:
	HorzScrollbar() : Property(
		"HorzScrollbar",
		"Property to get/set the setting for the horizontal scroll bar.  Value is either \"True\" or \"False\".",
		"False")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

} 

} 


#endif	
