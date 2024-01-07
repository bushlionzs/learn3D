#ifndef _FalIMEEditBoxProperties_h_
#define _FalIMEEditBoxProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{
	
	namespace KLIMEEditBoxProperties
	{

		
		class DefaultEditBox : public Property
		{
		public:
			DefaultEditBox() : Property(
				"DefaultEditBox",
				"Property to get/set the default editbox property.",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};

	}
}

#endif