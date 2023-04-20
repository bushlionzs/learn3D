#ifndef OgreFollowTargetAffectorFactory_h__
#define OgreFollowTargetAffectorFactory_h__

#include "OgreParticleAffectorFactory.h"
#include "OgreFollowTargetAffector.h"
#include "OgreParticleAffector.h"

namespace Ogre
{
	class   FollowTargetAffectorFactory : public ParticleAffectorFactory
	{
		virtual String getName() const
		{
			return "FollowTarget";
		}


		virtual ParticleAffector* createAffector(ParticleSystem* psys)
		{
			ParticleAffector* tmpParticleAffector = NULL;
			tmpParticleAffector = OGRE_NEW FollowTargetAffector(psys);
			mAffectors.push_back(tmpParticleAffector);

			return tmpParticleAffector;
		}
	};
}

#endif // OgreFollowTargetAffectorFactory_h__