

#ifndef _CEGUIMenuItemProperties_h_
#define _CEGUIMenuItemProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{

namespace MenuItemProperties
{


class HoverColour : public Property
{
public:
	HoverColour() : Property(
		"HoverColour",
		"Property to get/set the hover colour of the item.  Value is a colour.",
		"00FFFFFF")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class PushedColour : public Property
{
public:
	PushedColour() : Property(
		"PushedColour",
		"Property to get/set the pushed colour of the item.  Value is a colour.",
		"00FFFFFF")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class OpenedColour : public Property
{
public:
	OpenedColour() : Property(
		"OpenedColour",
		"Property to get/set the opened colour of the item.  Value is a colour.",
		"00EFEFEF")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class NormalTextColour : public Property
{
public:
	NormalTextColour() : Property(
		"NormalTextColour",
		"Property to get/set the normal text colour of the item.  Value is a colour.",
		"00FFFFFF")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class DisabledTextColour : public Property
{
public:
	DisabledTextColour() : Property(
		"DisabledTextColour",
		"Property to get/set the disabled text colour of the item.  Value is a colour.",
		"007F7F7F")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


} 
} 

#endif	
