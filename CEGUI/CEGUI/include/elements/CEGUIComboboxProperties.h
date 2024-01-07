

#ifndef _CEGUIComboboxProperties_h_
#define _CEGUIComboboxProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{



namespace ComboboxProperties
{

class ReadOnly : public Property
{
public:
	ReadOnly() : Property(
		"ReadOnly",
		"Property to get/set the read-only setting for the Editbox.  Value is either \"True\" or \"False\".",
		"False")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class ValidationString : public Property
{
public:
	ValidationString() : Property(
		"ValidationString",
		"Property to get/set the validation string Editbox.  Value is a text string.",
		".*")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class CaratIndex : public Property
{
public:
	CaratIndex() : Property(
		"CaratIndex",
		"Property to get/set the current carat index.  Value is \"[uint]\".",
		"0")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class EditSelectionStart : public Property
{
public:
	EditSelectionStart() : Property(
		"EditSelectionStart",
		"Property to get/set the zero based index of the selection start position within the text.  Value is \"[uint]\".",
		"0")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class EditSelectionLength : public Property
{
public:
	EditSelectionLength() : Property(
		"EditSelectionLength",
		"Property to get/set the length of the selection (as a count of the number of code points selected).  Value is \"[uint]\".",
		"0")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class MaxEditTextLength : public Property
{
public:
	MaxEditTextLength() : Property(
		"MaxEditTextLength",
		"Property to get/set the the maximum allowed text length (as a count of code points).  Value is \"[uint]\".",
		"1073741824")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class NormalEditTextColour : public Property
{
public:
	NormalEditTextColour() : Property(
		"NormalEditTextColour",
		"Property to get/set the normal, unselected, text colour used for rendering text.  Value is \"aarrggbb\" (hex).",
		"00FFFFFF")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class SelectedEditTextColour : public Property
{
public:
	SelectedEditTextColour() : Property(
		"SelectedEditTextColour",
		"Property to get/set the colour used for rendering text within the selection area.  Value is \"aarrggbb\" (hex).",
		"00000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class ActiveEditSelectionColour : public Property
{
public:
	ActiveEditSelectionColour() : Property(
		"ActiveEditSelectionColour",
		"Property to get/set the colour used for rendering the selection highlight when the edit box is active.  Value is \"aarrggbb\" (hex).",
		"006060FF")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class InactiveEditSelectionColour : public Property
{
public:
	InactiveEditSelectionColour() : Property(
		"InactiveEditSelectionColour",
		"Property to get/set the colour used for rendering the selection highlight when the edit box is inactive.  Value is \"aarrggbb\" (hex).",
		"00808080")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class SortList : public Property
{
public:
	SortList() : Property(
		"SortList",
		"Property to get/set the sort setting of the list box.  Value is either \"True\" or \"False\".",
		"False")
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

class DropButtonAndVertScrollbarMaxWidth : public Property
{
public:
	DropButtonAndVertScrollbarMaxWidth() : Property(
		"BtnVertScbMaxWidth",
		"Property to get/set the DropButton and VertScrollbar max width.",
		"1000")
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



class SingleClickMode : public Property
{
public:
	SingleClickMode() : Property(
		"SingleClickMode",
		"Property to get/set the 'single click mode' setting for the combo box.  Value is either \"True\" or \"False\".",
		"False")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


} 

} 


#endif	
