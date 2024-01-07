

#include "elements/CEGUIStaticProperties.h"
#include "elements/CEGUIStatic.h"
#include "CEGUIPropertyHelper.h"



namespace CEGUI
{


namespace StaticProperties
{
String	FrameEnabled::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Static*>(receiver)->isFrameEnabled());
}


void	FrameEnabled::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Static*>(receiver)->setFrameEnabled(PropertyHelper::stringToBool(value));
}


String	BackgroundEnabled::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Static*>(receiver)->isBackgroundEnabled());
}


void	BackgroundEnabled::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Static*>(receiver)->setBackgroundEnabled(PropertyHelper::stringToBool(value));
}


String	FrameColours::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourRectToString(static_cast<const Static*>(receiver)->getFrameColours());
}


void	FrameColours::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Static*>(receiver)->setFrameColours(PropertyHelper::stringToColourRect(value));
}


String	BackgroundColours::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourRectToString(static_cast<const Static*>(receiver)->getBackgroundColours());
}


void	BackgroundColours::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Static*>(receiver)->setBackgroundColours(PropertyHelper::stringToColourRect(value));
}


String	BackgroundImage::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::imageToString(static_cast<const Static*>(receiver)->getBackgroundImage());
}


void	BackgroundImage::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Static*>(receiver)->setBackgroundImage(PropertyHelper::stringToImage(value));
}


String	TopLeftFrameImage::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::imageToString(static_cast<const Static*>(receiver)->getImageForFrameLocation(TopLeftCorner));
}


void	TopLeftFrameImage::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Static*>(receiver)->setImageForFrameLocation(TopLeftCorner, PropertyHelper::stringToImage(value));
}


String	TopRightFrameImage::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::imageToString(static_cast<const Static*>(receiver)->getImageForFrameLocation(TopRightCorner));
}


void	TopRightFrameImage::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Static*>(receiver)->setImageForFrameLocation(TopRightCorner, PropertyHelper::stringToImage(value));
}


String	BottomLeftFrameImage::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::imageToString(static_cast<const Static*>(receiver)->getImageForFrameLocation(BottomLeftCorner));
}


void	BottomLeftFrameImage::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Static*>(receiver)->setImageForFrameLocation(BottomLeftCorner, PropertyHelper::stringToImage(value));
}


String	BottomRightFrameImage::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::imageToString(static_cast<const Static*>(receiver)->getImageForFrameLocation(BottomRightCorner));
}


void	BottomRightFrameImage::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Static*>(receiver)->setImageForFrameLocation(BottomRightCorner, PropertyHelper::stringToImage(value));
}


String	LeftFrameImage::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::imageToString(static_cast<const Static*>(receiver)->getImageForFrameLocation(LeftEdge));
}


void	LeftFrameImage::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Static*>(receiver)->setImageForFrameLocation(LeftEdge, PropertyHelper::stringToImage(value));
}


String	RightFrameImage::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::imageToString(static_cast<const Static*>(receiver)->getImageForFrameLocation(RightEdge));
}


void	RightFrameImage::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Static*>(receiver)->setImageForFrameLocation(RightEdge, PropertyHelper::stringToImage(value));
}


String	TopFrameImage::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::imageToString(static_cast<const Static*>(receiver)->getImageForFrameLocation(TopEdge));
}


void	TopFrameImage::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Static*>(receiver)->setImageForFrameLocation(TopEdge, PropertyHelper::stringToImage(value));
}


String	BottomFrameImage::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::imageToString(static_cast<const Static*>(receiver)->getImageForFrameLocation(BottomEdge));
}


void	BottomFrameImage::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Static*>(receiver)->setImageForFrameLocation(BottomEdge, PropertyHelper::stringToImage(value));
}

String	RecalcFrame::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Static*>(receiver)->isRecalcFrameEnabled());
}


void	RecalcFrame::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Static*>(receiver)->setRecalcFrameEnabled(PropertyHelper::stringToBool(value));
}

} 

} 
