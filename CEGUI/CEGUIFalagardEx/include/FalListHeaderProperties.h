

#ifndef _FalListHeaderProperties_h_
#define _FalListHeaderProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{

namespace FalagardListHeaderProperties
{

class SegmentWidgetType : public Property
{
public:
   SegmentWidgetType() : Property(
	   "SegmentWidgetType",
	   "Property to get/set the widget type used when creating header segments.  Value should be \"[widgetTypeName]\".",
	   "")
   {}

   String   get(const PropertyReceiver* receiver) const;
   void   set(PropertyReceiver* receiver, const String& value);
};

}
} 


#endif  
