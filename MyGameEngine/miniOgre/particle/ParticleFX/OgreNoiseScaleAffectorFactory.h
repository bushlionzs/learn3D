#ifndef OgreNoiseScaleAffectorFactory_h__
#define OgreNoiseScaleAffectorFactory_h__


#include "OgreParticleAffectorFactory.h"
#include "OgreParticleAffector.h"
#include "OgreNoiseScaleAffector.h"

namespace Ogre
{
	class  NoiseScaleAffectorFactory : public ParticleAffectorFactory
	{
		virtual String getName() const
		{
			return "NoiseScale";
		}


		virtual ParticleAffector* createAffector(ParticleSystem* psys)
		{
			ParticleAffector* tmpParticleAffector = NULL;
			tmpParticleAffector = OGRE_NEW NoiseScaleAffector(psys);
			mAffectors.push_back(tmpParticleAffector);

			return tmpParticleAffector;
		}
	};
}
#endif // OgreNoiseScaleAffectorFactory_h__