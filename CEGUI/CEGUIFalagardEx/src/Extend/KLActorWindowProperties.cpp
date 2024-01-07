
#include "KLActorWindowProperties.h"
#include "KLActorWindow.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{

	
	namespace KLActorWindowProperties 
	{
		

		String FakeObject::get(const PropertyReceiver* receiver) const
		{
			return static_cast<const KLActorWindow*>(receiver)->getFakeObject();
		}

		void FakeObject::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLActorWindow*>(receiver)->setFakeObject(value);
		}

		

		String ShowControl::get(const PropertyReceiver* receiver) const
		{
			return static_cast<const KLActorWindow*>(receiver)->getShowControl();
		}

		void ShowControl::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLActorWindow*>(receiver)->setShowControl(value);
		}
	}

}