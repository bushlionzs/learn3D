
#ifndef __Texture2ScaleInterpolatorAffectorFactory_H__
#define __Texture2ScaleInterpolatorAffectorFactory_H__

#include "OgreParticleAffectorFactory.h"
#include "OgreTexture2ScaleInterpolatorAffector.h"

namespace Ogre 
{

    class  Texture2ScaleInterpolatorAffectorFactory : public ParticleAffectorFactory
    {
        String getName() const { return "Texture2ScaleInterpolator"; }

        ParticleAffector* createAffector(ParticleSystem* psys)
        {
            ParticleAffector* p = OGRE_NEW Texture2ScaleInterpolatorAffector(psys);
            mAffectors.push_back(p);
            return p;
        }
    };
}

#endif

