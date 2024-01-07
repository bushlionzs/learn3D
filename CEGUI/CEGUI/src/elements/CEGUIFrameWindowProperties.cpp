

#include "elements/CEGUIFrameWindowProperties.h"
#include "elements/CEGUIFrameWindow.h"
#include "CEGUIPropertyHelper.h"
#include "CEGUIExceptions.h"
#include "CEGUIFont.h"



namespace CEGUI
{


namespace FrameWindowProperties
{
String	SizingEnabled::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const FrameWindow*>(receiver)->isSizingEnabled());
}


void	SizingEnabled::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<FrameWindow*>(receiver)->setSizingEnabled(PropertyHelper::stringToBool(value));
}


String	FrameEnabled::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const FrameWindow*>(receiver)->isFrameEnabled());
}


void	FrameEnabled::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<FrameWindow*>(receiver)->setFrameEnabled(PropertyHelper::stringToBool(value));
}


String	TitlebarEnabled::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const FrameWindow*>(receiver)->isTitleBarEnabled());
}


void	TitlebarEnabled::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<FrameWindow*>(receiver)->setTitleBarEnabled(PropertyHelper::stringToBool(value));
}


String	CloseButtonEnabled::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const FrameWindow*>(receiver)->isCloseButtonEnabled());
}


void	CloseButtonEnabled::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<FrameWindow*>(receiver)->setCloseButtonEnabled(PropertyHelper::stringToBool(value));
}


String	DragMovingEnabled::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const FrameWindow*>(receiver)->isDragMovingEnabled());
}


void	DragMovingEnabled::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<FrameWindow*>(receiver)->setDragMovingEnabled(PropertyHelper::stringToBool(value));
}


String	RollUpEnabled::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const FrameWindow*>(receiver)->isRollupEnabled());
}


void	RollUpEnabled::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<FrameWindow*>(receiver)->setRollupEnabled(PropertyHelper::stringToBool(value));
}


String	RollUpState::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const FrameWindow*>(receiver)->isRolledup());
}


void	RollUpState::set(PropertyReceiver* receiver, const String& value)
{
	bool reqState = PropertyHelper::stringToBool(value);

	if (reqState != static_cast<FrameWindow*>(receiver)->isRolledup())
	{
		static_cast<FrameWindow*>(receiver)->toggleRollup();
	}

}


String	SizingBorderThickness::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const FrameWindow*>(receiver)->getSizingBorderThickness());
}


void	SizingBorderThickness::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<FrameWindow*>(receiver)->setSizingBorderThickness(PropertyHelper::stringToFloat(value));
}


String	TitlebarFont::get(const PropertyReceiver* receiver) const
{
	return static_cast<const FrameWindow*>(receiver)->getTitlebarFont()->getName();	
}


void	TitlebarFont::set(PropertyReceiver* receiver, const String& value)
{
	if (value.empty())
	{
		static_cast<FrameWindow*>(receiver)->setTitlebarFont(System::getSingleton().getDefaultFont());
	}
	else
	{
		static_cast<FrameWindow*>(receiver)->setTitlebarFont(value);
	}
}

String CaptionColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const FrameWindow*>(receiver)->getCaptionColour());
}

void CaptionColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<FrameWindow*>(receiver)->setCaptionColour(PropertyHelper::stringToColour(value));
}

String NSSizingCursorImage::get(const PropertyReceiver* receiver) const
{
    const Image* img = static_cast<const FrameWindow*>(receiver)->getNSSizingCursorImage();
    return img ? PropertyHelper::imageToString(img) : String("");
}

void NSSizingCursorImage::set(PropertyReceiver* receiver, const String &value)
{
    static_cast<FrameWindow*>(receiver)->setNSSizingCursorImage(PropertyHelper::stringToImage(value));
}

String EWSizingCursorImage::get(const PropertyReceiver* receiver) const
{
    const Image* img = static_cast<const FrameWindow*>(receiver)->getEWSizingCursorImage();
    return img ? PropertyHelper::imageToString(img) : String("");
}

void EWSizingCursorImage::set(PropertyReceiver* receiver, const String &value)
{
    static_cast<FrameWindow*>(receiver)->setEWSizingCursorImage(PropertyHelper::stringToImage(value));
}

String NWSESizingCursorImage::get(const PropertyReceiver* receiver) const
{
    const Image* img = static_cast<const FrameWindow*>(receiver)->getNWSESizingCursorImage();
    return img ? PropertyHelper::imageToString(img) : String("");
}

void NWSESizingCursorImage::set(PropertyReceiver* receiver, const String &value)
{
    static_cast<FrameWindow*>(receiver)->setNWSESizingCursorImage(PropertyHelper::stringToImage(value));
}

String NESWSizingCursorImage::get(const PropertyReceiver* receiver) const
{
    const Image* img = static_cast<const FrameWindow*>(receiver)->getNESWSizingCursorImage();
    return img ? PropertyHelper::imageToString(img) : String("");
}

void NESWSizingCursorImage::set(PropertyReceiver* receiver, const String &value)
{
    static_cast<FrameWindow*>(receiver)->setNESWSizingCursorImage(PropertyHelper::stringToImage(value));
}


} 

} 
