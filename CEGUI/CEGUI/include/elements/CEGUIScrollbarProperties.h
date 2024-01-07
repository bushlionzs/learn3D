

#ifndef _CEGUIScrollbarProperties_h_
#define _CEGUIScrollbarProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{



namespace ScrollbarProperties
{

class DocumentSize : public Property
{
public:
	DocumentSize() : Property(
		"DocumentSize",
		"Property to get/set the document size for the Scrollbar.  Value is a float.",
		"1.000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class PageSize : public Property
{
public:
	PageSize() : Property(
		"PageSize",
		"Property to get/set the page size for the Scrollbar.  Value is a float.",
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
		"Property to get/set the step size for the Scrollbar.  Value is a float.",
		"1.000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class OverlapSize : public Property
{
public:
	OverlapSize() : Property(
		"OverlapSize",
		"Property to get/set the overlap size for the Scrollbar.  Value is a float.",
		"0.000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


class ScrollPosition : public Property
{
public:
	ScrollPosition() : Property(
		"ScrollPosition",
		"Property to get/set the scroll position of the Scrollbar.  Value is a float.",
		"0.000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

} 

} 


#endif	
