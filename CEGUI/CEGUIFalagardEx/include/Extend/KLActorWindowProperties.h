#ifndef _FalActorWindowProperties_h_
#define _FalActorWindowProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{
	namespace KLActorWindowProperties
	{
		
		class FakeObject: public Property
		{
		public:
			FakeObject() : Property(
				"FakeObject",
				"Property to get/set FakeObject name.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		
		class ShowControl: public Property
		{
		public:
			ShowControl() : Property(
				"ShowControl",
				"Property to get/set window name that control show or hide.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
	}

}

#endif