
#ifndef __Texture1RotateInterpolatorAffectorFactory_H__
#define __Texture1RotateInterpolatorAffectorFactory_H__

#include "OgreParticleAffectorFactory.h"
#include "OgreTexture1RotateInterpolatorAffector.h"

namespace Ogre 
{

    class  Texture1RotateInterpolatorAffectorFactory : public ParticleAffectorFactory
    {
        String getName() const { return "Texture1RotateInterpolator"; }

        ParticleAffector* createAffector(ParticleSystem* psys)
        {
            ParticleAffector* p = OGRE_NEW Texture1RotateInterpolatorAffector(psys);
            mAffectors.push_back(p);
            return p;
        }
    };
}

#endif

