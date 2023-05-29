
#ifndef __Texture1PosInterpolatorAffectorFactory_H__
#define __Texture1PosInterpolatorAffectorFactory_H__

#include "OgreParticleAffectorFactory.h"
#include "OgreTexture1PosInterpolatorAffector.h"

namespace Ogre 
{

    class  Texture1PosInterpolatorAffectorFactory : public ParticleAffectorFactory
    {
        String getName() const { return "Texture1PosInterpolator"; }

        ParticleAffector* createAffector(ParticleSystem* psys)
        {
            ParticleAffector* p = OGRE_NEW Texture1PosInterpolatorAffector(psys);
            mAffectors.push_back(p);
            return p;
        }
    };
}

#endif

