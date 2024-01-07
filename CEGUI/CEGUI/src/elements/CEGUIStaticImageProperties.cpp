

#include "elements/CEGUIStaticImageProperties.h"
#include "elements/CEGUIStaticImage.h"
#include "CEGUIPropertyHelper.h"



namespace CEGUI
{


namespace StaticImageProperties
{
String	Image::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::imageToString(static_cast<const StaticImage*>(receiver)->getImage());
}


void	Image::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<StaticImage*>(receiver)->setImage(PropertyHelper::stringToImage(value));
}


String	ImageColours::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourRectToString(static_cast<const StaticImage*>(receiver)->getImageColours());
}


void	ImageColours::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<StaticImage*>(receiver)->setImageColours(PropertyHelper::stringToColourRect(value));
}


String	VertFormatting::get(const PropertyReceiver* receiver) const
{
	switch(static_cast<const StaticImage*>(receiver)->getVerticalFormatting())
	{
	case StaticImage::TopAligned:
		return String((utf8*)"TopAligned");
		break;

	case StaticImage::BottomAligned:
		return String((utf8*)"BottomAligned");
		break;

	case StaticImage::VertTiled:
		return String((utf8*)"VertTiled");
		break;

	case StaticImage::VertCentred:
		return String((utf8*)"VertCentred");
		break;

	default:
		return String((utf8*)"VertStretched");
		break;
	}

}


void	VertFormatting::set(PropertyReceiver* receiver, const String& value)
{
	StaticImage::VertFormatting fmt;

	if (value == (utf8*)"TopAligned")
	{
		fmt = StaticImage::TopAligned;
	}
	else if (value == (utf8*)"BottomAligned")
	{
		fmt = StaticImage::BottomAligned;
	}
	else if (value == (utf8*)"VertTiled")
	{
		fmt = StaticImage::VertTiled;
	}
	else if (value == (utf8*)"VertCentred")
	{
		fmt = StaticImage::VertCentred;
	}
	else
	{
		fmt = StaticImage::VertStretched;
	}

	static_cast<StaticImage*>(receiver)->setVerticalFormatting(fmt);
}


String	HorzFormatting::get(const PropertyReceiver* receiver) const
{
	switch(static_cast<const StaticImage*>(receiver)->getHorizontalFormatting())
	{
	case StaticImage::LeftAligned:
		return String((utf8*)"LeftAligned");
		break;

	case StaticImage::RightAligned:
		return String((utf8*)"RightAligned");
		break;

	case StaticImage::HorzTiled:
		return String((utf8*)"HorzTiled");
		break;

	case StaticImage::HorzCentred:
		return String((utf8*)"HorzCentred");
		break;

	default:
		return String((utf8*)"HorzStretched");
		break;
	}

}


void	HorzFormatting::set(PropertyReceiver* receiver, const String& value)
{
	StaticImage::HorzFormatting fmt;

	if (value == (utf8*)"LeftAligned")
	{
		fmt = StaticImage::LeftAligned;
	}
	else if (value == (utf8*)"RightAligned")
	{
		fmt = StaticImage::RightAligned;
	}
	else if (value == (utf8*)"HorzTiled")
	{
		fmt = StaticImage::HorzTiled;
	}
	else if (value == (utf8*)"HorzCentred")
	{
		fmt = StaticImage::HorzCentred;
	}
	else
	{
		fmt = StaticImage::HorzStretched;
	}

	static_cast<StaticImage*>(receiver)->setHorizontalFormatting(fmt);
}

String	RightAnchor::get(const PropertyReceiver* receiver) const
{
	return static_cast<const StaticImage*>(receiver)->getRightAnchor();
}


void	RightAnchor::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<StaticImage*>(receiver)->setRightAnchor(value);
}

String	BottomAnchor::get(const PropertyReceiver* receiver) const
{
	return static_cast<const StaticImage*>(receiver)->getBottomAnchor();
}


void	BottomAnchor::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<StaticImage*>(receiver)->setBottomAnchor(value);
}

} 

} 
