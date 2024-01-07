

#ifndef _CEGUIItemListBaseProperties_h_
#define _CEGUIItemListBaseProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{

namespace ItemListBaseProperties
{
    
    class AutoResizeEnabled : public Property
    {
    public:
	    AutoResizeEnabled() : Property(
		    "AutoResizeEnabled",
		    "Property to get/set the state of the auto resizing enabled setting for the ItemListBase.  Value is either \"True\" or \"False\".",
		    "False")
	    {}

	    String	get(const PropertyReceiver* receiver) const;
	    void	set(PropertyReceiver* receiver, const String& value);
    };

} 
} 

#endif	
