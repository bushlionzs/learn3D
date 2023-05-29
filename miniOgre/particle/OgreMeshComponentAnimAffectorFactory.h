#ifndef OgreMeshComponentAnimAffectorFactory_h__
#define OgreMeshComponentAnimAffectorFactory_h__


#include "OgreParticleAffectorFactory.h"
#include "OgreMeshComponentAnimAffector.h"

namespace Ogre 
{
	class MeshComponentAnimAffectorFactory : public ParticleAffectorFactory
	{
		ParticleAffector* createAffector(ParticleSystem* psys)
		{
			ParticleAffector* p = OGRE_NEW MeshComponentAnimAffector(psys);
			mAffectors.push_back(p);
			return p;
		}

		String getName() const { return "MeshAnimationAffector"; }
	};


}

#endif // OgreMeshComponentAnimAffectorFactory_h__