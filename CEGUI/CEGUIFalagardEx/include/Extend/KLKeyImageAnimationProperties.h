#ifndef _FalAnimateProperties_h_
#define _FalAnimateProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{

	namespace KLKeyImageAnimationProperties
	{
	
		class FalKeyImageAnimation : public Property
		{
		public:
			FalKeyImageAnimation() : Property(
				"Animate",
				"Property to get/set Animate name status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
	}
}

#endif  
