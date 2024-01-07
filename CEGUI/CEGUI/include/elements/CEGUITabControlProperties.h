

#ifndef _CEGUITabControlProperties_h_
#define _CEGUITabControlProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{



namespace TabControlProperties
{

class TabHeight : public Property
{
public:
	TabHeight() : Property(
		"TabHeight",
		"Property to get/set the height of the tabs.",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);

	
	bool	isDefault(const PropertyReceiver* receiver) const;
	String	getDefault(const PropertyReceiver* receiver) const;
};


class AbsoluteTabHeight : public Property
{
public:
    AbsoluteTabHeight() : Property(
		"AbsoluteTabHeight",
		"Property to get/set the absolute height of the tabs.",
		"", false)
	{}

    String	get(const PropertyReceiver* receiver) const;
    void	set(PropertyReceiver* receiver, const String& value);

	
	bool	isDefault(const PropertyReceiver* receiver) const;
	String	getDefault(const PropertyReceiver* receiver) const;
};


class RelativeTabHeight : public Property
{
public:
    RelativeTabHeight() : Property(
		"RelativeTabHeight",
		"Property to get/set the relative height of the tabs.",
		"0.050000", false)
	{}

    String	get(const PropertyReceiver* receiver) const;
    void	set(PropertyReceiver* receiver, const String& value);
};


class TabTextPadding : public Property
{
public:
    TabTextPadding() : Property(
		"TabTextPadding", 
		"Property to get/set the padding either side of the tab buttons.",
		"")
	{}

    String	get(const PropertyReceiver* receiver) const;
    void	set(PropertyReceiver* receiver, const String& value);

	
	bool	isDefault(const PropertyReceiver* receiver) const;
	String	getDefault(const PropertyReceiver* receiver) const;
};


class AbsoluteTabTextPadding : public Property
{
public:
    AbsoluteTabTextPadding() : Property(
		"AbsoluteTabTextPadding",
		"Property to get/set the absolute padding either side of the tab buttons.",
		"5", false)
	{}

    String	get(const PropertyReceiver* receiver) const;
    void	set(PropertyReceiver* receiver, const String& value);
};


class RelativeTabTextPadding : public Property
{
public:
    RelativeTabTextPadding() : Property(
		"RelativeTabTextPadding",
		"Property to get/set the relative padding either side of the tab buttons.",
		"", false)
	{}

    String	get(const PropertyReceiver* receiver) const;
    void	set(PropertyReceiver* receiver, const String& value);

	
	bool	isDefault(const PropertyReceiver* receiver) const;
	String	getDefault(const PropertyReceiver* receiver) const;
};





} 

} 


#endif	
