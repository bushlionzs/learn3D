

#ifndef _CEGUITitlebarProperties_h_
#define _CEGUITitlebarProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{



namespace TitlebarProperties
{

class DraggingEnabled : public Property
{
public:
	DraggingEnabled() : Property(
		"DraggingEnabled",
		"Property to get/set the state of the dragging enabled setting for the Titlebar.  Value is either \"True\" or \"False\".",
		"True")
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

} 

} 


#endif	
