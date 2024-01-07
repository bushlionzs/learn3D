

#ifndef _CEGUIButtonBaseProperties_h_
#define _CEGUIButtonBaseProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{


namespace ButtonBaseProperties
{

class NormalTextColour : public Property
{
public:
	NormalTextColour() : Property(
		"NormalTextColour",
		"Property to get/set the colour to use when rendering label text for normal state.  Value is \"aarrggbb\" (hex).",
		"FFFFFFFF")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class HoverTextColour : public Property
{
public:
	HoverTextColour() : Property(
		"HoverTextColour",
		"Property to get/set the colour to use when rendering label text for hover/highlight state.  Value is \"aarrggbb\" (hex).",
		"FFFFFFFF")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class PushedTextColour : public Property
{
public:
	PushedTextColour() : Property(
		"PushedTextColour", 
		"Property to get/set the colour to use when rendering label text for pushed state.  Value is \"aarrggbb\" (hex).",
		"FFFFFFFF")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class DisabledTextColour : public Property
{
public:
	DisabledTextColour() : Property(
		"DisabledTextColour",
		"Property to get/set the colour to use when rendering label text for disabled state.  Value is \"aarrggbb\" (hex).",
		"FF7F7F7F")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


} 


} 


#endif	
