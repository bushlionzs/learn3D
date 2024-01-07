

#ifndef _CEGUIListHeaderProperties_h_
#define _CEGUIListHeaderProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{



namespace ListHeaderProperties
{

class ColumnsSizable : public Property
{
public:
	ColumnsSizable() : Property(
		"ColumnsSizable",
		"Property to get/set the setting for user sizing of the column headers.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class ColumnsMovable : public Property
{
public:
	ColumnsMovable() : Property(
		"ColumnsMovable",
		"Property to get/set the setting for user moving of the column headers.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class SortSettingEnabled : public Property
{
public:
	SortSettingEnabled() : Property(
		"SortSettingEnabled",
		"Property to get/set the setting for for user modification of the sort column & direction.  Value is either \"True\" or \"False\".",
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
		"Property to get/set the sort direction setting of the header.  Value is the text of one of the SortDirection enumerated value names.",
		"None")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class SortColumnID : public Property
{
public:
	SortColumnID() : Property(
		"SortColumnID",
		"Property to get/set the current sort column (via ID code).  Value is an unsigned integer number.",
		"0")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

} 

} 


#endif	
