

#ifndef _CEGUIPushButtonProperties_h_
#define _CEGUIPushButtonProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{



namespace PushButtonProperties
{


class NormalImage : public Property
{
public:
   NormalImage() : Property(
	   "NormalImage", 
	   "Property to get/set the normal image for the PushButton widget.  Value should be \"set:[imageset name] image:[image name]\".",
	   "")
   {}

   String   get(const PropertyReceiver* receiver) const;
   void   set(PropertyReceiver* receiver, const String& value);
};


class PushedImage : public Property
{
public:
   PushedImage() : Property(
	   "PushedImage",
	   "Property to get/set the pushed image for the PushButton widget.  Value should be \"set:[imageset name] image:[image name]\".",
	   "")
   {}

   String   get(const PropertyReceiver* receiver) const;
   void   set(PropertyReceiver* receiver, const String& value);
};


class HoverImage : public Property
{
public:
   HoverImage() : Property(
	   "HoverImage",
	   "Property to get/set the hover image for the PushButton widget.  Value should be \"set:[imageset name] image:[image name]\".",
	   "")
   {}

   String   get(const PropertyReceiver* receiver) const;
   void   set(PropertyReceiver* receiver, const String& value);
};


class DisabledImage : public Property
{
public:
   DisabledImage() : Property(
	   "DisabledImage",
	   "Property to get/set the disabled image for the PushButton widget.  Value should be \"set:[imageset name] image:[image name]\".",
	   "")
   {}

   String   get(const PropertyReceiver* receiver) const;
   void   set(PropertyReceiver* receiver, const String& value);
};


class UseStandardImagery : public Property
{
public:
   UseStandardImagery() : Property(
	   "UseStandardImagery",
	   "Property to get/set whether to use the standard imagery for the PushButton widget.  Value should be \"True\" or \"False\".",
	   "True")
   {}

   String   get(const PropertyReceiver* receiver) const;
   void   set(PropertyReceiver* receiver, const String& value);
};


class TextXOffset : public Property
{
public:
   TextXOffset() : Property(
	   "TextXOffset",
	   "Property to get/set a relative x offset for the button's text",
	   "0.000000")
   {}

   String get(const PropertyReceiver* receiver) const;
   void set(PropertyReceiver* receiver, const String& value);
};

}

}
#endif
