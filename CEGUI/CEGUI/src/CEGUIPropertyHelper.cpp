

#include "CEGUIPropertyHelper.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIImageset.h"
#include "CEGUIExceptions.h"

#include <cstdio>


namespace CEGUI
{
float PropertyHelper::stringToFloat(const String& str)
{
	using namespace std;

	float val = 0;
	sscanf(str.c_str(), " %f", &val);

	return val;
}


uint PropertyHelper::stringToUint(const String& str)
{
	using namespace std;

	uint val = 0;
	sscanf(str.c_str(), " %u", &val);

	return val;
}


int PropertyHelper::stringToInt(const String& str)
{
	using namespace std;

	uint val = 0;
	sscanf(str.c_str(), " %d", &val);

	return val;
}


bool PropertyHelper::stringToBool(const String& str)
{
	if ((str == (utf8*)"True") || (str == (utf8*)"true"))
	{
		return true;
	}
	else
	{
		return false;
	}

}


Size PropertyHelper::stringToSize(const String& str)
{
	using namespace std;

	Size val(0,0);
	sscanf(str.c_str(), " w:%f h:%f", &val.d_width, &val.d_height);

	return val;
}


Point PropertyHelper::stringToPoint(const String& str)
{
	using namespace std;

	Point val(0,0) ;
	sscanf(str.c_str(), " x:%f y:%f", &val.d_x, &val.d_y);

	return val;
}


Rect PropertyHelper::stringToRect(const String& str)
{
	using namespace std;

	Rect val(0, 0, 0, 0);
	sscanf(str.c_str(), " l:%f t:%f r:%f b:%f", &val.d_left, &val.d_top, &val.d_right, &val.d_bottom);

	return val;
}


MetricsMode PropertyHelper::stringToMetricsMode(const String& str)
{
	if (str == (utf8*)"Relative")
	{
		return Relative;
	}
	else if (str == (utf8*)"Absolute")
	{
		return Absolute;
	}
	else
	{
		return Inherited;
	}

}


const Image* PropertyHelper::stringToImage(const String& imageset, const String& imagename)
{
	const Image* image;

	try
	{
		if( !ImagesetManager::getSingleton().isImagesetPresent(imageset) )
			return 0;

		image = ImagesetManager::getSingleton().getImageset(imageset)->getImage(imagename);
	}
	catch (UnknownObjectException)
	{
		image = NULL;
	}

	return image;
}


const Image* PropertyHelper::stringToImage(const String& str)
{
	using namespace std;

	char imageSet[128] = {0};
	char imageName[128] = {0};

	sscanf(str.c_str(), " set:%127s image:%127s", imageSet, imageName);

	const Image* image;

	try
	{
		if(!(ImagesetManager::getSingleton().isImagesetPresent((utf8*)imageSet))) return 0;
		image = ImagesetManager::getSingleton().getImageset((utf8*)imageSet)->getImage((utf8*)imageName);
	}
	catch (UnknownObjectException)
	{
		image = NULL;
	}

	return image;
}


UDim PropertyHelper::stringToUDim(const String& str)
{
	using namespace std;

	UDim ud;
	sscanf(str.c_str()," {%f,%f}", &ud.d_scale, &ud.d_offset);

	return ud;
}


UVector2 PropertyHelper::stringToUVector2(const String& str)
{
	using namespace std;

	UVector2 uv;
	sscanf(str.c_str(), " {{%f,%f},{%f,%f}}", &uv.d_x.d_scale,&uv.d_x.d_offset, &uv.d_y.d_scale,&uv.d_y.d_offset);

	return uv;
}


URect PropertyHelper::stringToURect(const String& str)
{
	using namespace std;

	URect ur;
	sscanf(
		str.c_str(),
		" {{%f,%f},{%f,%f},{%f,%f},{%f,%f}}",
		&ur.d_min.d_x.d_scale, &ur.d_min.d_x.d_offset,
		&ur.d_min.d_y.d_scale, &ur.d_min.d_y.d_offset,
		&ur.d_max.d_x.d_scale, &ur.d_max.d_x.d_offset,
		&ur.d_max.d_y.d_scale, &ur.d_max.d_y.d_offset
	);

	return ur;
}


String PropertyHelper::floatToString(float val)
{
	using namespace std;

	char buff[64];
	sprintf(buff, "%f", val);

	return String((utf8*)buff);
}


String PropertyHelper::uintToString(uint val)
{
	using namespace std;

	char buff[64];
	sprintf(buff, "%u", val);

	return String((utf8*)buff);
}


String PropertyHelper::intToString(int val)
{
	using namespace std;

	char buff[64];
	sprintf(buff, "%d", val);

	return String((utf8*)buff);
}


String PropertyHelper::boolToString(bool val)
{
	if (val)
	{
		return String((utf8*)"True");
	}
	else
	{
		return String ((utf8*)"False");
	}

}


String PropertyHelper::sizeToString(const Size& val)
{
	using namespace std;

	char buff[128];
	sprintf(buff, "w:%f h:%f", val.d_width, val.d_height);

	return String((utf8*)buff);
}


String PropertyHelper::pointToString(const Point& val)
{
	using namespace std;

	char buff[128];
	sprintf(buff, "x:%f y:%f", val.d_x, val.d_y);

	return String((utf8*)buff);
}


String PropertyHelper::rectToString(const Rect& val)
{
	using namespace std;

	char buff[256];
	sprintf(buff, "l:%f t:%f r:%f b:%f", val.d_left, val.d_top, val.d_right, val.d_bottom);

	return String((utf8*)buff);
}


String PropertyHelper::metricsModeToString(MetricsMode val)
{
	if (val == Relative)
	{
		return String((utf8*)"Relative");
	}
	else if (val == Absolute)
	{
		return String((utf8*)"Absolute");
	}
	else
	{
		return String((utf8*)"Inherited");
	}

}


String PropertyHelper::imageToString(const Image* const val)
{
	if (val != NULL)
	{
		return String((utf8*)"set:" + val->getImagesetName() + (utf8*)" image:" + val->getName());
	}

	return String((utf8*)"");
}


String PropertyHelper::stringToImageString(const String& imageset, const String& image)
{
	if ( !imageset.empty() && !image.empty() )
	{
		return String((utf8*)"set:" + imageset + (utf8*)" image:" + image);
	}

	return String((utf8*)"");
}


String PropertyHelper::udimToString(const UDim& val)
{
	using namespace std;

	char buff[128];
	sprintf(buff, "{%f,%f}", val.d_scale, val.d_offset);

	return String((utf8*)buff);
}


String PropertyHelper::uvector2ToString(const UVector2& val)
{
	using namespace std;

	char buff[256];
	sprintf(buff, "{{%f,%f},{%f,%f}}", val.d_x.d_scale, val.d_x.d_offset, val.d_y.d_scale, val.d_y.d_offset);

	return String((utf8*)buff);
}


String PropertyHelper::urectToString(const URect& val)
{
	using namespace std;

	char buff[512];
	sprintf(
		buff,
		"{{%f,%f},{%f,%f},{%f,%f},{%f,%f}}",
		val.d_min.d_x.d_scale,val.d_min.d_x.d_offset,
		val.d_min.d_y.d_scale,val.d_min.d_y.d_offset,
		val.d_max.d_x.d_scale,val.d_max.d_x.d_offset,
		val.d_max.d_y.d_scale,val.d_max.d_y.d_offset
	);

	return String((utf8*)buff);
}


String PropertyHelper::colourToString(const colour& val)
{
	using namespace std;

	char buff[16];
	sprintf(buff, "%.8X", val.getARGB());

	return String((utf8*)buff);
}


colour PropertyHelper::stringToColour(const String& str)
{
	using namespace std;

	
	
	

	argb_t val = 0x0;
	char* sp = (char*)str.c_str();
	sscanf(sp, " %X", &val);
	val += 0xFF000000;

	return colour(val);

}


String PropertyHelper::colourRectToString(const ColourRect& val)
{
	using namespace std;

	char buff[64];
	sprintf(buff, "tl:%.8X tr:%.8X bl:%.8X br:%.8X", val.d_top_left.getARGB(), val.d_top_right.getARGB(), val.d_bottom_left.getARGB(), val.d_bottom_right.getARGB());

	return String((utf8*)buff);
}


ColourRect PropertyHelper::stringToColourRect(const String& str)
{
	using namespace std;

	argb_t topLeft = 0xFF000000, topRight = 0xFF000000, bottomLeft = 0xFF000000, bottomRight = 0xFF000000;
	sscanf(str.c_str(), "tl:%8X tr:%8X bl:%8X br:%8X", &topLeft, &topRight, &bottomLeft, &bottomRight);

	return ColourRect(topLeft, topRight, bottomLeft, bottomRight);
}

String PropertyHelper::hookModeToString( const HookMode& val)
{
	if (val == Hook_Left)
	{
		return String((utf8*)"Left");
	}
	else if (val == Hook_Right)
	{
		return String((utf8*)"Right");
	}
	else if (val == Hook_Top)
	{
		return String((utf8*)"Top");
	}
	else if (val == Hook_Bottom)
	{
		return String((utf8*)"Bottom");
	}
	else if (val == Hook_LeftTop)
	{
		return String((utf8*)"LeftTop");
	}
	else if (val == Hook_LeftBottom)
	{
		return String((utf8*)"LeftBottom");
	}
	else if (val == Hook_RightTop)
	{
		return String((utf8*)"RightTop");
	}
	else if (val == Hook_RightBottom)
	{
		return String((utf8*)"RightBottom");
	}
	else if (val == Hook_Center)
	{
		return String((utf8*)"Center");
	}
	else
	{
		return String((utf8*)"None");
	}

}

HookMode PropertyHelper::stringToHookMode(const String& str)
{
	if (str == String((utf8*)"Left"))
	{
		return Hook_Left;
	}
	else if (str == String((utf8*)"Right") )
	{
		return Hook_Right;
	}
	else if (str == String((utf8*)"Top"))
	{
		return Hook_Top;
	}
	else if (str == String((utf8*)"Bottom") )
	{
		return Hook_Bottom;
	}
	else if (str == String((utf8*)"LeftTop") )
	{
		return Hook_LeftTop;
	}
	else if (str == String((utf8*)"LeftBottom"))
	{
		return Hook_LeftBottom ;
	}
	else if (str == String((utf8*)"RightTop"))
	{
		return Hook_RightTop ;
	}
	else if (str == String((utf8*)"RightBottom"))
	{
		return Hook_RightBottom ;
	}
	else if (str == String((utf8*)"Center"))
	{
		return Hook_Center ;
	}
	else
	{
		return Hook_None;
	}

}

} 
