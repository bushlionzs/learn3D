
#ifndef __Texture2RotateInterpolatorAffectorFactory_H__
#define __Texture2RotateInterpolatorAffectorFactory_H__

#include "OgreParticleAffectorFactory.h"
#include "OgreTexture2RotateInterpolatorAffector.h"

namespace Ogre 
{

    class  Texture2RotateInterpolatorAffectorFactory : public ParticleAffectorFactory
    {
        String getName() const { return "Texture2RotateInterpolator"; }

        ParticleAffector* createAffector(ParticleSystem* psys)
        {
            ParticleAffector* p = OGRE_NEW Texture2RotateInterpolatorAffector(psys);
            mAffectors.push_back(p);
            return p;
        }
    };
}

#endif

