
#ifndef __Texture2PosInterpolatorAffectorFactory_H__
#define __Texture2PosInterpolatorAffectorFactory_H__

#include "OgreParticleAffectorFactory.h"
#include "OgreTexture2PosInterpolatorAffector.h"

namespace Ogre 
{

    class  Texture2PosInterpolatorAffectorFactory : public ParticleAffectorFactory
    {
        String getName() const { return "Texture2PosInterpolator"; }

        ParticleAffector* createAffector(ParticleSystem* psys)
        {
            ParticleAffector* p = OGRE_NEW Texture2PosInterpolatorAffector(psys);
            mAffectors.push_back(p);
            return p;
        }
    };
}

#endif

