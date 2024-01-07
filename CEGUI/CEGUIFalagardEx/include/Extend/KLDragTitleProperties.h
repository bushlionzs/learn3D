#ifndef _FalDragTitleProperties_h_
#define _FalDragTitleProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{
	
	namespace KLDragTitleProperties
	{
		
		class DragTarget : public Property
		{
		public:
			DragTarget() : Property(
				"DragTarget",
				"Property to get/set the drag target Window.",
				"[String]", false)
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};
	}
}

#endif