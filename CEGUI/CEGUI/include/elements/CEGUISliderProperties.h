

#ifndef _CEGUISliderProperties_h_
#define _CEGUISliderProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{



namespace SliderProperties
{

class CurrentValue : public Property
{
public:
	CurrentValue() : Property(
		"CurrentValue",
		"Property to get/set the current value of the slider.  Value is a float.",
		"0.000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class MaximumValue : public Property
{
public:
	MaximumValue() : Property(
		"MaximumValue",
		"Property to get/set the maximum value of the slider.  Value is a float.",
		"1.000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class ClickStepSize : public Property
{
public:
	ClickStepSize() : Property(
		"ClickStepSize",
		"Property to get/set the click-step size for the slider.  Value is a float.",
		"0.010000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

} 

} 


#endif	
