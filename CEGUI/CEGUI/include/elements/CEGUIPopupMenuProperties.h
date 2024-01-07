

#ifndef _CEGUIPopupMenuProperties_h_
#define _CEGUIPopupMenuProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{

namespace PopupMenuProperties
{


class FadeInTime : public Property
{
public:
	FadeInTime() : Property(
		"FadeInTime",
		"Property to get/set the fade in time in seconds of the menu bar.  Value is a float.",
		"0.000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class FadeOutTime : public Property
{
public:
	FadeOutTime() : Property(
		"FadeOutTime",
		"Property to get/set the fade out time in seconds of the menu bar.  Value is a float.",
		"0.000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

} 
} 

#endif	
