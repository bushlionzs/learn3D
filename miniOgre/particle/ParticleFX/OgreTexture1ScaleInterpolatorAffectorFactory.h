
#ifndef __Texture1ScaleInterpolatorAffectorFactory_H__
#define __Texture1ScaleInterpolatorAffectorFactory_H__

#include "OgreParticleAffectorFactory.h"
#include "OgreTexture1ScaleInterpolatorAffector.h"

namespace Ogre 
{

    class  Texture1ScaleInterpolatorAffectorFactory : public ParticleAffectorFactory
    {
        String getName() const { return "Texture1ScaleInterpolator"; }

        ParticleAffector* createAffector(ParticleSystem* psys)
        {
            ParticleAffector* p = OGRE_NEW Texture1ScaleInterpolatorAffector(psys);
            mAffectors.push_back(p);
            return p;
        }
    };
}

#endif

