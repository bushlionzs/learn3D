

#ifndef _FalListHeaderSegmentProperties_h_
#define _FalListHeaderSegmentProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{

namespace FalagardListHeaderSegmentProperties
{

class SizingCursorImage : public Property
{
public:
   SizingCursorImage() : Property(
	   "SizingCursorImage",
	   "Property to get/set the sizing cursor image for the List Header Segment.  Value should be \"set:[imageset name] image:[image name]\".",
	   "")
   {}

   String   get(const PropertyReceiver* receiver) const;
   void   set(PropertyReceiver* receiver, const String& value);
};


class MovingCursorImage : public Property
{
public:
   MovingCursorImage() : Property(
	   "MovingCursorImage",
	   "Property to get/set the moving cursor image for the List Header Segment.  Value should be \"set:[imageset name] image:[image name]\".",
	   "")
   {}

   String   get(const PropertyReceiver* receiver) const;
   void   set(PropertyReceiver* receiver, const String& value);
};

}

} 


#endif  
