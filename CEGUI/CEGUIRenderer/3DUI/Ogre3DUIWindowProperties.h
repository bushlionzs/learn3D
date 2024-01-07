


#ifndef  _OGRE3DUIWINDOWProperties_H
#define  _OGRE3DUIWINDOWProperties_H

#include "CEGUIProperty.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif

namespace CEGUI
{
	namespace Ogre3DUIWindowProperties
	{
		class Ogre3DUIGeometryType : public Property
		{
		public:
			Ogre3DUIGeometryType() : Property("UIGeometryType","Property to get/set UIPlace status.","")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		class Ogre3DUIType : public Property
		{
		public:
			Ogre3DUIType() : Property("UIType","Property to get/set UIType status.","")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		
		
		
		
		

		
		
		

		class Ogre3DSecondTextureName : public Property
		{
		public:
			Ogre3DSecondTextureName() : Property("Second Texture","Property to get/set second texture name.","")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		class OgreSceneObjectName : public Property
		{
		public:
			OgreSceneObjectName() : Property("Object Name","Property to get/set Object Name.","")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};


		class OgreMovableType: public Property
		{
		public:
			OgreMovableType() : Property("Movable Type","Property to get/set Movable Type.","")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};


		class OgreMovableResource: public Property
		{
		public:
			OgreMovableResource() : Property("Movable Resource","Property to get/set Movable Resource.","")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

	}
} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif