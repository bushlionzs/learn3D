

#include "elements/CEGUIScrollbarProperties.h"
#include "elements/CEGUIScrollbar.h"
#include "CEGUIPropertyHelper.h"



namespace CEGUI
{


namespace ScrollbarProperties
{
String	DocumentSize::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Scrollbar*>(receiver)->getDocumentSize());
}


void	DocumentSize::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Scrollbar*>(receiver)->setDocumentSize(PropertyHelper::stringToFloat(value));
}


String	PageSize::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Scrollbar*>(receiver)->getPageSize());
}


void	PageSize::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Scrollbar*>(receiver)->setPageSize(PropertyHelper::stringToFloat(value));
}


String	StepSize::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Scrollbar*>(receiver)->getStepSize());
}


void	StepSize::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Scrollbar*>(receiver)->setStepSize(PropertyHelper::stringToFloat(value));
}


String	OverlapSize::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Scrollbar*>(receiver)->getOverlapSize());
}


void	OverlapSize::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Scrollbar*>(receiver)->setOverlapSize(PropertyHelper::stringToFloat(value));
}


String	ScrollPosition::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Scrollbar*>(receiver)->getScrollPosition());
}


void	ScrollPosition::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Scrollbar*>(receiver)->setScrollPosition(PropertyHelper::stringToFloat(value));
}

} 

} 
