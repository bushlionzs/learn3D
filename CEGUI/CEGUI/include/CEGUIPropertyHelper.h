

#ifndef _CEGUIPropertyHelper_h_
#define _CEGUIPropertyHelper_h_

#include "CEGUIWindow.h"



namespace CEGUI
{

class CEGUIEXPORT PropertyHelper
{
public:
	static	float	stringToFloat(const String& str);
	static	uint	stringToUint(const String& str);
	static	int		stringToInt(const String& str);
	static	bool	stringToBool(const String& str);
	static	Size	stringToSize(const String& str);
	static	Point	stringToPoint(const String& str);
	static	Rect	stringToRect(const String& str);
	static	MetricsMode	stringToMetricsMode(const String& str);
	static const Image*	stringToImage(const String& str);
	static const Image*	stringToImage(const String& imageset, const String& imagename);
	static	colour	stringToColour(const String& str);
	static	ColourRect	stringToColourRect(const String& str);
	static	UDim	stringToUDim(const String& str);
	static	UVector2	stringToUVector2(const String& str);
	static	URect	stringToURect(const String& str);
	static  HookMode stringToHookMode( const String& str );


	static String	floatToString(float val);
	static String	uintToString(uint val);
	static String	intToString(int val);
	static String	boolToString(bool val);
	static String	sizeToString(const Size& val);
	static String	pointToString(const Point& val);
	static String	rectToString(const Rect& val);
	static String	metricsModeToString(MetricsMode val);
	static String	imageToString(const Image* const val);
	static String	stringToImageString(const String& imageset, const String& image);
	static String	colourToString(const colour& val);
	static String	colourRectToString(const ColourRect& val);
	static String	udimToString(const UDim& val);
	static String	uvector2ToString(const UVector2& val);
	static String	urectToString(const URect& val);
	static String   hookModeToString( const HookMode& val );
};

} 


#endif	
