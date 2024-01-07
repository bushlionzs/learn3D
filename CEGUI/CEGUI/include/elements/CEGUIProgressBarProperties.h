

#ifndef _CEGUIProgressBarProperties_h_
#define _CEGUIProgressBarProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{



namespace ProgressBarProperties
{

class CurrentProgress : public Property
{
public:
	CurrentProgress() : Property(
		"CurrentProgress",
		"Property to get/set the current progress of the progress bar.  Value is a float  value between 0.0 and 1.0 specifying the progress.",
		"0.000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class StepSize : public Property
{
public:
	StepSize() : Property(
		"StepSize",
		"Property to get/set the step size setting for the progress bar.  Value is a float value.",
		"0.010000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


} 

} 


#endif	
