

#include "elements/CEGUICheckboxProperties.h"
#include "elements/CEGUICheckbox.h"
#include "CEGUIPropertyHelper.h"
#include "CEGUIExceptions.h"
#include <cstdlib>
#include <cstdio>



namespace CEGUI
{


namespace CheckboxProperties
{
	String Selected::get(const PropertyReceiver* receiver) const
	{
		return PropertyHelper::boolToString(static_cast<const Checkbox*>(receiver)->isSelected());
	}


	void Selected::set(PropertyReceiver* receiver, const String& value)
	{
		static_cast<Checkbox*>(receiver)->setSelected(PropertyHelper::stringToBool(value));
	}

} 

} 
