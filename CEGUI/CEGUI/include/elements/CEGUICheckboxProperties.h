

#ifndef _CEGUICheckboxProperties_h_
#define _CEGUICheckboxProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{



namespace CheckboxProperties
{

class Selected : public Property
{
public:
	Selected() : Property(
		"Selected",
		"Property to get/set the selected state of the Checkbox.  Value is either \"True\" or \"False\".",
		"False")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

} 

} 


#endif	
