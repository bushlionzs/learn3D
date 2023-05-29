#ifndef OGPhysicsManager_h__
#define OGPhysicsManager_h__

#include "OgreSingleton.h"

namespace Orphigine
{
	class PhyWorld;

	class _OrphigineExport PhysicsManager : public Ogre::Singleton<PhysicsManager>
	{
	public:
		PhysicsManager();
		~PhysicsManager();

		PhyWorld*				getWorld() const;

	protected:
		PhyWorld*				m_world;

	private:
	};
}
#endif // OGPhysicsManager_h__
