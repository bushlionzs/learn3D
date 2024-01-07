

#ifndef _CEGUIFrameWindowProperties_h_
#define _CEGUIFrameWindowProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{



namespace FrameWindowProperties
{

class SizingEnabled : public Property
{
public:
	SizingEnabled() : Property(
		"SizingEnabled",
		"Property to get/set the state of the sizable setting for the FrameWindow.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class FrameEnabled : public Property
{
public:
	FrameEnabled() : Property(
		"FrameEnabled",
		"Property to get/set the setting for whether the window frame will be displayed.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class TitlebarEnabled : public Property
{
public:
	TitlebarEnabled() : Property(
		"TitlebarEnabled",
		"Property to get/set the setting for whether the window title-bar will be enabled (or displayed depending upon choice of final widget type).  Value is either \"True\" or \"False\".",
		"") 
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class CloseButtonEnabled : public Property
{
public:
	CloseButtonEnabled() : Property(
		"CloseButtonEnabled",
		"Property to get/set the setting for whether the window close button will be enabled (or displayed depending upon choice of final widget type).  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class RollUpEnabled : public Property
{
public:
	RollUpEnabled() : Property(
		"RollUpEnabled",
		"Property to get/set the setting for whether the user is able to roll-up / shade the window.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class RollUpState : public Property
{
public:
	RollUpState() : Property(
		"RollUpState",
		"Property to get/set the roll-up / shade state of the window.  Value is either \"True\" or \"False\".",
		"False")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class DragMovingEnabled : public Property
{
public:
	DragMovingEnabled() : Property(
		"DragMovingEnabled",
		"Property to get/set the setting for whether the user may drag the window around by its title bar.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class SizingBorderThickness : public Property
{
public:
	SizingBorderThickness() : Property(
		"SizingBorderThickness",
		"Property to get/set the setting for the sizing border thickness.  Value is a float specifying the border thickness in pixels.",
		"8.000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class TitlebarFont : public Property
{
public:
	TitlebarFont() : Property(
		"TitlebarFont",
		"Property to get/set the Font set for the windows title bar.  Value is the name of the font to use (must be loaded already).",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


class CaptionColour : public Property
{
public:
	CaptionColour() : Property(
		"CaptionColour",
		"Property to get/set the colour used for rendering the caption text.  Value is \"aarrggbb\" (hex).",
		"FF000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


class NSSizingCursorImage : public Property
{
public:
   NSSizingCursorImage() : Property(
	   "NSSizingCursorImage",
	   "Property to get/set the N-S (up-down) sizing cursor image for the FramwWindow.  Value should be \"set:[imageset name] image:[image name]\".",
	   "")
   {}

   String   get(const PropertyReceiver* receiver) const;
   void   set(PropertyReceiver* receiver, const String& value);
};


class EWSizingCursorImage : public Property
{
public:
   EWSizingCursorImage() : Property(
	   "EWSizingCursorImage",
	   "Property to get/set the E-W (left-right) sizing cursor image for the FramwWindow.  Value should be \"set:[imageset name] image:[image name]\".",
	   "")
   {}

   String   get(const PropertyReceiver* receiver) const;
   void   set(PropertyReceiver* receiver, const String& value);
};


class NWSESizingCursorImage : public Property
{
public:
   NWSESizingCursorImage() : Property(
	   "NWSESizingCursorImage",
	   "Property to get/set the NW-SE diagonal sizing cursor image for the FramwWindow.  Value should be \"set:[imageset name] image:[image name]\".",
	   "")
   {}

   String   get(const PropertyReceiver* receiver) const;
   void   set(PropertyReceiver* receiver, const String& value);
};


class NESWSizingCursorImage : public Property
{
public:
   NESWSizingCursorImage() : Property(
	   "NESWSizingCursorImage",
	   "Property to get/set the NE-SW diagonal sizing cursor image for the FramwWindow.  Value should be \"set:[imageset name] image:[image name]\".",
	   "")
   {}

   String   get(const PropertyReceiver* receiver) const;
   void   set(PropertyReceiver* receiver, const String& value);
};

} 

} 


#endif	
