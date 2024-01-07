

#ifndef _CEGUIStaticProperties_h_
#define _CEGUIStaticProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{



namespace StaticProperties
{

class FrameEnabled : public Property
{
public:
	FrameEnabled() : Property(
		"FrameEnabled",
		"Property to get/set the state of the frame enabled setting for the Static widget.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class BackgroundEnabled : public Property
{
public:
	BackgroundEnabled() : Property(
		"BackgroundEnabled",
		"Property to get/set the state of the frame background setting for the Static widget.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class FrameColours : public Property
{
public:
	FrameColours() : Property(
		"FrameColours",
		"Property to get/set the frame colours for the Static widget.  Value is \"tl:[aarrggbb] tr:[aarrggbb] bl:[aarrggbb] br:[aarrggbb]\".",
		"tl:FFFFFFFF tr:FFFFFFFF bl:FFFFFFFF br:FFFFFFFF")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class BackgroundColours : public Property
{
public:
	BackgroundColours() : Property(
		"BackgroundColours",
		"Property to get/set the background colours for the Static widget.  Value is \"tl:[aarrggbb] tr:[aarrggbb] bl:[aarrggbb] br:[aarrggbb]\".",
		"tl:FFFFFFFF tr:FFFFFFFF bl:FFFFFFFF br:FFFFFFFF")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class BackgroundImage : public Property
{
public:
	BackgroundImage() : Property(
		"BackgroundImage",
		"Property to get/set the background image for the Static widget.  Value should be \"set:[imageset name] image:[image name]\".",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class TopLeftFrameImage : public Property
{
public:
	TopLeftFrameImage() : Property(
		"TopLeftFrameImage",
		"Property to get/set the top-left image for the frame of the Static widget.  Value should be \"set:[imageset name] image:[image name]\".",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class TopRightFrameImage : public Property
{
public:
	TopRightFrameImage() : Property(
		"TopRightFrameImage",
		"Property to get/set the top-right image for the frame of the Static widget.  Value should be \"set:[imageset name] image:[image name]\".",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class BottomLeftFrameImage : public Property
{
public:
	BottomLeftFrameImage() : Property(
		"BottomLeftFrameImage",
		"Property to get/set the bottom-left image for the frame of the Static widget.  Value should be \"set:[imageset name] image:[image name]\".",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class BottomRightFrameImage : public Property
{
public:
	BottomRightFrameImage() : Property(
		"BottomRightFrameImage",
		"Property to get/set the bottom-right image for the frame of the Static widget.  Value should be \"set:[imageset name] image:[image name]\".",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class LeftFrameImage : public Property
{
public:
	LeftFrameImage() : Property(
		"LeftFrameImage",
		"Property to get/set the left edge image for the frame of the Static widget.  Value should be \"set:[imageset name] image:[image name]\".",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class RightFrameImage : public Property
{
public:
	RightFrameImage() : Property(
		"RightFrameImage",
		"Property to get/set the right edge image for the frame of the Static widget.  Value should be \"set:[imageset name] image:[image name]\".",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class TopFrameImage : public Property
{
public:
	TopFrameImage() : Property(
		"TopFrameImage",
		"Property to get/set the top edge image for the frame of the Static widget.  Value should be \"set:[imageset name] image:[image name]\".",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class BottomFrameImage : public Property
{
public:
	BottomFrameImage() : Property(
		"BottomFrameImage",
		"Property to get/set the bottom edge image for the frame of the Static widget.  Value should be \"set:[imageset name] image:[image name]\".",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


class RecalcFrame : public Property
{
public:
	RecalcFrame() : Property(
		"RecalcFrame",
		"Property to get/set the state of the frame enabled setting for the Static widget.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

} 

} 


#endif	
