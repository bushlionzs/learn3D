

#ifndef _CEGUIStaticImageProperties_h_
#define _CEGUIStaticImageProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{



namespace StaticImageProperties
{

class Image : public Property
{
public:
	Image() : Property(
		"Image",
		"Property to get/set the image for the StaticImage widget.  Value should be \"set:[imageset name] image:[image name]\".",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class ImageColours : public Property
{
public:
	ImageColours() : Property(
		"ImageColours",
		"Property to get/set the text colours for the StaticImage widget.  Value is \"tl:[aarrggbb] tr:[aarrggbb] bl:[aarrggbb] br:[aarrggbb]\".",
		"tl:FFFFFFFF tr:FFFFFFFF bl:FFFFFFFF br:FFFFFFFF")
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
		"HorzStretched")
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
		"VertStretched")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


class RightAnchor : public Property
{
public:
	RightAnchor() : Property(
		"RightAnchor",
		"",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


class BottomAnchor : public Property
{
public:
	BottomAnchor() : Property(
		"BottomAnchor",
		"",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

} 

} 


#endif	
