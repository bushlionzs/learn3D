#ifndef OgreMeshComponentRatationAffectorFactory_h__
#define OgreMeshComponentRatationAffectorFactory_h__


#include "OgreParticleAffectorFactory.h"
#include "OgreMeshComponentRotationAffector.h"

namespace Ogre 
{
	class MeshRotationAffectorFactory : public ParticleAffectorFactory
	{
		String getName() const 
		{ 
			return "MeshRotator"; 
		}

		ParticleAffector* createAffector(ParticleSystem* psys)
		{
			ParticleAffector* p = OGRE_NEW MeshComponentOrientationAffector(psys);
			mAffectors.push_back(p);
			return p;
		}
	};


}

#endif // OgreMeshComponentRatationAffectorFactory_h__