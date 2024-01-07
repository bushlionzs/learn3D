

#ifndef _CEGUIListHeaderSegmentProperties_h_
#define _CEGUIListHeaderSegmentProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{



namespace ListHeaderSegmentProperties
{

class Sizable : public Property
{
public:
	Sizable() : Property(
		"Sizable",
		"Property to get/set the sizable setting of the header segment.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class Clickable : public Property
{
public:
	Clickable() : Property(
		"Clickable",
		"Property to get/set the click-able setting of the header segment.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class Dragable : public Property
{
public:
	Dragable() : Property(
		"Dragable",
		"Property to get/set the drag-able setting of the header segment.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class SortDirection : public Property
{
public:
	SortDirection() : Property(
		"SortDirection",
		"Property to get/set the sort direction setting of the header segment.  Value is the text of one of the SortDirection enumerated value names.",
		"None")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

} 

} 


#endif	
