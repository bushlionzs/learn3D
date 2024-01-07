

#ifndef _CEGUIMultiColumnListProperties_h_
#define _CEGUIMultiColumnListProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{



namespace MultiColumnListProperties
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
		"Property to get/set the sort direction setting of the list.  Value is the text of one of the SortDirection enumerated value names.",
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
		"0", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class NominatedSelectionColumnID : public Property
{
public:
	NominatedSelectionColumnID() : Property(
		"NominatedSelectionColumnID",
		"Property to get/set the nominated selection column (via ID).  Value is an unsigned integer number.",
		"0")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class NominatedSelectionRow : public Property
{
public:
	NominatedSelectionRow() : Property(
		"NominatedSelectionRow",
		"Property to get/set the nominated selection row.  Value is an unsigned integer number.",
		"0")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class ForceVertScrollbar : public Property
{
public:
	ForceVertScrollbar() : Property(
		"ForceVertScrollbar",
		"Property to get/set the 'always show' setting for the vertical scroll bar of the list box.  Value is either \"True\" or \"False\".",
		"False")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class ForceHorzScrollbar : public Property
{
public:
	ForceHorzScrollbar() : Property(
		"ForceHorzScrollbar",
		"Property to get/set the 'always show' setting for the horizontal scroll bar of the list box.  Value is either \"True\" or \"False\".",
		"False")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class SelectionMode : public Property
{
public:
	SelectionMode() : Property(
		"SelectionMode",
		"Property to get/set the selection mode setting of the list.  Value is the text of one of the SelectionMode enumerated value names.",
		"RowSingle")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class ColumnHeader : public Property
{
public:
	ColumnHeader() : Property(
		"ColumnHeader",
		"Property to set up a column (there is no getter for this property)",
		"", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


class RowCount : public Property
{
public:
	RowCount() : Property(
		"RowCount",
		"Property to access the number of rows in the list (read only)",
		"", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


class NoHeader : public Property
{
public:
	NoHeader() : Property(
		"NoHeader",
		"Property to get/set the 'show' setting for the header of the list box.  Value is either \"True\" or \"False\".",
		"False", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

} 

} 


#endif	
