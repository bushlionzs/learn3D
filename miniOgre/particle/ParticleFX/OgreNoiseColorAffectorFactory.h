#ifndef OgreNoiseColorAffectorFactory_h__
#define OgreNoiseColorAffectorFactory_h__


#include "OgreParticleAffectorFactory.h"
#include "OgreParticleAffector.h"
#include "OgreNoiseColorAffector.h"

namespace Ogre
{
	class   NoiseColorAffectorFactory : public ParticleAffectorFactory
	{
		virtual String getName() const
		{
			return "NoiseColor";
		}


		virtual ParticleAffector* createAffector(ParticleSystem* psys)
		{
			ParticleAffector* tmpParticleAffector = NULL;
			tmpParticleAffector = OGRE_NEW NoiseColorAffector(psys);
			mAffectors.push_back(tmpParticleAffector);

			return tmpParticleAffector;
		}
	};
}
#endif // OgreNoiseColorAffectorFactory_h__