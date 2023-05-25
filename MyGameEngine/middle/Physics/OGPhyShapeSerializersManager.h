#ifndef OGPhyShapeSerializersManager_h__
#define OGPhyShapeSerializersManager_h__

#include "OgreSingleton.h"

namespace Orphigine
{
	class PhyShapeSerializersManager : public Ogre::Singleton<PhyShapeSerializersManager>
	{
	public:
		PhyShapeSerializersManager();
		virtual ~PhyShapeSerializersManager();
	protected:
	private:
	};
}
#endif // OGPhyShapeSerializersManager_h__
