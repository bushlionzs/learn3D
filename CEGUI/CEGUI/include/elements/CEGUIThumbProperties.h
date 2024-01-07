

#ifndef _CEGUIThumbProperties_h_
#define _CEGUIThumbProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{



namespace ThumbProperties
{

class HotTracked : public Property
{
public:
	HotTracked() : Property(
		"HotTracked",
		"Property to get/set the state of the state of the 'hot-tracked' setting for the thumb.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class VertFree : public Property
{
public:
	VertFree() : Property(
		"VertFree",
		"Property to get/set the state the setting to free the thumb vertically.  Value is either \"True\" or \"False\".",
		"False")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class HorzFree : public Property
{
public:
	HorzFree() : Property(
		"HorzFree", 
		"Property to get/set the state the setting to free the thumb horizontally.  Value is either \"True\" or \"False\".",
		"False")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class VertRange : public Property
{
public:
	VertRange() : Property(
		"VertRange",
		"Property to get/set the vertical movement range for the thumb.  Value is \"min:[float] max:[float]\".",
		"min:0.000000 max:1.000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class HorzRange : public Property
{
public:
	HorzRange() : Property(
		"HorzRange",
		"Property to get/set the horizontal movement range for the thumb.  Value is \"min:[float] max:[float]\".",
		"min:0.000000 max:1.000000")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


} 

} 


#endif	
