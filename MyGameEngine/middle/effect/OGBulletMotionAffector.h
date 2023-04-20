#ifndef OGBulletMotionAffector_h__
#define OGBulletMotionAffector_h__

#include "OgreStringInterface.h"

namespace Orphigine
{
	class BulletSystem;

	class BulletMotionAffector : public Ogre::StringInterface
	{
	public:
		BulletMotionAffector();
		virtual ~BulletMotionAffector();

		virtual void	affectBullet(BulletSystem* bulletSystem) = 0;

	protected:
	private:
	};
}
#endif // OGBulletMotionAffector_h__
