#include "Ogre3DUIWindow.h"
#include "Ogre3DUIWindowProperties.h"


namespace CEGUI
{
	namespace Ogre3DUIWindowProperties
	{
		void Ogre3DUIGeometryType::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<Ogre3DUIWindow*>(receiver)->set3DUIGeometryType(value);
		}

		String	Ogre3DUIGeometryType::get(const PropertyReceiver* receiver) const
		{
			return static_cast<const Ogre3DUIWindow*>(receiver)->get3DUIGeometryType();
		}

		void	Ogre3DUIType::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<Ogre3DUIWindow*>(receiver)->set3DUIType(value);
		}

		String	Ogre3DUIType::get(const PropertyReceiver* receiver) const
		{
			return static_cast<const Ogre3DUIWindow*>(receiver)->get3DUIType();
		}

		
		
		
		

		
		
		
		

		void	Ogre3DSecondTextureName::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<Ogre3DUIWindow*>(receiver)->setSecondTextureName(value);
		}

		String	Ogre3DSecondTextureName::get(const PropertyReceiver* receiver) const
		{
			return static_cast<const Ogre3DUIWindow*>(receiver)->getSecondTextureName();
		}

		void	OgreSceneObjectName::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<Ogre3DUIWindow*>(receiver)->setSceneObjectName(value);
		}

		String	OgreSceneObjectName::get(const PropertyReceiver* receiver) const
		{
			return static_cast<const Ogre3DUIWindow*>(receiver)->getSceneObjectName();
		}

		void	OgreMovableType::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<Ogre3DUIWindow*>(receiver)->setMovableType(value);
		}

		String	OgreMovableType::get(const PropertyReceiver* receiver) const
		{
			return static_cast<const Ogre3DUIWindow*>(receiver)->getMovableType();
		}		
		
		void	OgreMovableResource::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<Ogre3DUIWindow*>(receiver)->setMovableResourceName(value);
		}

		String	OgreMovableResource::get(const PropertyReceiver* receiver) const
		{
			return static_cast<const Ogre3DUIWindow*>(receiver)->getMovableResourceName();
		}
	}
}