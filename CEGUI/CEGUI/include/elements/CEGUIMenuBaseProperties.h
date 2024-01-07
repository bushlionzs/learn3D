

#ifndef _CEGUIMenuBaseProperties_h_
#define _CEGUIMenuBaseProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{

namespace MenuBaseProperties
{


class ItemSpacing : public Property
{
public:
	ItemSpacing() : Property(
		"ItemSpacing",
		"Property to get/set the item spacing of the menu.  Value is a float.",
		"10.000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class HorzPadding : public Property
{
public:
	HorzPadding() : Property(
		"HorzPadding",
		"Property to get/set the horizontal padding of the menu.  Value is a float.",
		"3.000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class VertPadding : public Property
{
public:
	VertPadding() : Property(
		"VertPadding",
		"Property to get/set the vertical padding of the menu.  Value is a float.",
		"3.000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class BorderWidth : public Property
{
public:
	BorderWidth() : Property(
		"BorderWidth",
		"Property to get/set the border width of the menu.  Value is a float.",
		"5.000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class BackgroundColours : public Property
{
public:
	BackgroundColours() : Property(
		"BackgroundColours",
		"Property to get/set the background colours of the menu.  Value is a ColourRect.",
		"tl:FFFFFFFF tr:FFFFFFFF bl:FFFFFFFF br:FFFFFFFF")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class AllowMultiplePopups : public Property
{
public:
    AllowMultiplePopups() : Property(
	    "AllowMultiplePopups",
	    "Property to get/set the state of the allow multiple popups setting for the menu.  Value is either \"True\" or \"False\".",
	    "False")
    {}

    String	get(const PropertyReceiver* receiver) const;
    void	set(PropertyReceiver* receiver, const String& value);
};

} 
} 

#endif	
