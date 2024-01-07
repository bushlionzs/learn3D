

#include "elements/CEGUISliderProperties.h"
#include "elements/CEGUISlider.h"
#include "CEGUIPropertyHelper.h"



namespace CEGUI
{


namespace SliderProperties
{
String	CurrentValue::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Slider*>(receiver)->getCurrentValue());
}


void	CurrentValue::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Slider*>(receiver)->setCurrentValue(PropertyHelper::stringToFloat(value));
}


String	MaximumValue::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Slider*>(receiver)->getMaxValue());
}


void	MaximumValue::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Slider*>(receiver)->setMaxValue(PropertyHelper::stringToFloat(value));
}


String	ClickStepSize::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Slider*>(receiver)->getClickStep());
}


void	ClickStepSize::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Slider*>(receiver)->setClickStep(PropertyHelper::stringToFloat(value));
}

} 

} 
