

#ifndef _FalTabControlProperties_h_
#define _FalTabControlProperties_h_
#include "CEGUIProperty.h"


namespace CEGUI
{

namespace FalagardTabControlProperties
{

class TabButtonType : public Property
{
public:
   TabButtonType() : Property(
	   "TabButtonType",
	   "Property to get/set the widget type used when creating tab buttons.  Value should be \"[widgetTypeName]\".",
	   "")
   {}

   String   get(const PropertyReceiver* receiver) const;
   void   set(PropertyReceiver* receiver, const String& value);
};

}
} 

#endif  
