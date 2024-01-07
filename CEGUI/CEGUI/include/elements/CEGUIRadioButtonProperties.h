

#ifndef _CEGUIRadioButtonProperties_h_
#define _CEGUIRadioButtonProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{



namespace RadioButtonProperties
{

class Selected : public Property
{
public:
	Selected() : Property(
		"Selected",
		"Property to get/set the selected state of the RadioButton.  Value is either \"True\" or \"False\".",
		"False")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class GroupID : public Property
{
public:
	GroupID() : Property(
		"GroupID",
		"Property to get/set the radio button group ID.  Value is an unsigned integer number.",
		"0")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


} 

} 


#endif	
