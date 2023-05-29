#ifndef OGPhyTimeController_h__
#define OGPhyTimeController_h__

#include "OgreFrameListener.h"

namespace Orphigine
{
	class PhyWorld;

	class PhyDefaultTimeController : Ogre::FrameListener
	{
	public:
		PhyDefaultTimeController(PhyWorld* world);
		~PhyDefaultTimeController();

		virtual bool frameStarted(const Ogre::FrameEvent& evt);
		
	protected:
		PhyWorld*		m_world;
	private:
	};
}
#endif // OGPhyTimeController_h__
