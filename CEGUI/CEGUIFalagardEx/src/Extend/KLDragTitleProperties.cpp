
#include "KLDragTitleProperties.h"
#include "KLDragTitle.h"
#include "CEGUIPropertyHelper.h"



namespace CEGUI
{

	
	namespace KLDragTitleProperties
	{
		
		

		String DragTarget::get(const PropertyReceiver* receiver) const
		{
			return static_cast<const KLDragTitle*>(receiver)->getDragTarget();
		}

		void DragTarget::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLDragTitle*>(receiver)->setDragTarget(value);
		}

	}
}