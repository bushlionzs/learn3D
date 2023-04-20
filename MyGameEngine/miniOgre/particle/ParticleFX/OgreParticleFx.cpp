#include "OgreHeader.h"
#include "OgreParticleFx.h"
#include "OgreRoot.h"
#include "OgreParticleSystemManager.h"
#include "OgrePointEmitterFactory.h"
#include "OgreBoxEmitterFactory.h"
#include "OgreEllipsoidEmitterFactory.h"
#include "OgreHollowEllipsoidEmitterFactory.h"
#include "OgreRingEmitterFactory.h"
#include "OgreCylinderEmitterFactory.h"
#include "OgreLinearForceAffectorFactory.h"
#include "OgreColourFaderAffectorFactory.h"
#include "OgreColourFaderAffectorFactory2.h"
#include "OgreColourImageAffectorFactory.h"
#include "OgreColourInterpolatorAffectorFactory.h"
#include "OgreScaleAffectorFactory.h"
#include "OgreRotationAffectorFactory.h"
#include "OgreDirectionRandomiserAffectorFactory.h"
#include "OgreDeflectorPlaneAffectorFactory.h"
#include "OgreTextureAnimatorAffector.h"
#include "OgreParticleAffectorFactory.h"
#include "OgreParticleEmitterFactory.h"

#include "OgreColourFadingAffectorFactory.h"
#include "OgreMovementAffectorFactory.h"
#include "OgreScaleInterpolatorAffectorFactory.h"
#include "OgrePolarEmitterFactory.h"
#include "OgreTexture1PosInterpolatorAffectorFactory.h"
#include "OgreTexture2PosInterpolatorAffectorFactory.h"
#include "OgreTexture1ScaleInterpolatorAffectorFactory.h"
#include "OgreTexture2ScaleInterpolatorAffectorFactory.h"
#include "OgreTexture1RotateInterpolatorAffectorFactory.h"
#include "OgreTexture2RotateInterpolatorAffectorFactory.h"

#include "OgreFollowTargetAffectorFactory.h"
#include "OgreNoiseColorAffectorFactory.h"
#include "OgreNoiseScaleAffectorFactory.h"
#include "OgreRevolutionAffectorFactory.h"

#include "OgreTexcoordBillboardParticleRenderer.h"
#include "OgreMeshComponentParticleRenderer.h"
#include "OgreMeshComponentRotationAffectorFactory.h"
#include "OgreMeshComponentAnimAffectorFactory.h"
#include "OgreRibandParticleRenderer.h"
#include "OgreHeightFieldAffectorFactory.h"

using namespace Ogre;

static std::vector<ParticleEmitterFactory*> mEmitterFactories;
static std::vector<ParticleAffectorFactory*> mAffectorFactories;

void OgreParticleFx_init()
{
    ParticleEmitterFactory* pEmitFact;

    // PointEmitter
    pEmitFact = OGRE_NEW PointEmitterFactory();
    ParticleSystemManager::getSingleton().addEmitterFactory(pEmitFact);
    mEmitterFactories.push_back(pEmitFact);

    // BoxEmitter
    pEmitFact = OGRE_NEW BoxEmitterFactory();
    ParticleSystemManager::getSingleton().addEmitterFactory(pEmitFact);
    mEmitterFactories.push_back(pEmitFact);

    // EllipsoidEmitter
    pEmitFact = OGRE_NEW EllipsoidEmitterFactory();
    ParticleSystemManager::getSingleton().addEmitterFactory(pEmitFact);
    mEmitterFactories.push_back(pEmitFact);

    // CylinderEmitter
    pEmitFact = OGRE_NEW CylinderEmitterFactory();
    ParticleSystemManager::getSingleton().addEmitterFactory(pEmitFact);
    mEmitterFactories.push_back(pEmitFact);

    // RingEmitter
    pEmitFact = OGRE_NEW RingEmitterFactory();
    ParticleSystemManager::getSingleton().addEmitterFactory(pEmitFact);
    mEmitterFactories.push_back(pEmitFact);

    // HollowEllipsoidEmitter
    pEmitFact = OGRE_NEW HollowEllipsoidEmitterFactory();
    ParticleSystemManager::getSingleton().addEmitterFactory(pEmitFact);
    mEmitterFactories.push_back(pEmitFact);

    // PolarEmitter
    pEmitFact = new PolarEmitterFactory();
    ParticleSystemManager::getSingleton().addEmitterFactory(pEmitFact);
    mEmitterFactories.push_back(pEmitFact);

    // -- Create all new particle affector factories --
    ParticleAffectorFactory* pAffFact;

    // LinearForceAffector
    pAffFact = OGRE_NEW LinearForceAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    // ColourFaderAffector
    pAffFact = OGRE_NEW ColourFaderAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    // ColourFaderAffector2
    pAffFact = OGRE_NEW ColourFaderAffectorFactory2();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    // ColourImageAffector
    pAffFact = OGRE_NEW ColourImageAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    // ColourInterpolatorAffector
    pAffFact = OGRE_NEW ColourInterpolatorAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    // ScaleAffector
    pAffFact = OGRE_NEW ScaleAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    // RotationAffector
    pAffFact = OGRE_NEW RotationAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);


    // DirectionRandomiserAffector
    pAffFact = OGRE_NEW DirectionRandomiserAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    // DeflectorPlaneAffector
    pAffFact = OGRE_NEW DeflectorPlaneAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    // TextureAnimatorAffector
    pAffFact = OGRE_NEW TextureAnimatorAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    ////// new affector
        // ColourFadingAffector
    pAffFact = new ColourFadingAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    // ColourFadingAffector
    pAffFact = new ColourFadingAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    // MoveAffector
    pAffFact = new MovementAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    pAffFact = new RevolutionAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    // ScaleInterpolatorAffector
    pAffFact = new ScaleInterpolatorAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    pAffFact = new NoiseScaleAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    pAffFact = new Texture1PosInterpolatorAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    pAffFact = new Texture2PosInterpolatorAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    pAffFact = new Texture1ScaleInterpolatorAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    pAffFact = new Texture2ScaleInterpolatorAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    pAffFact = new Texture1RotateInterpolatorAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);

    pAffFact = new Texture2RotateInterpolatorAffectorFactory();
    ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);
    mAffectorFactories.push_back(pAffFact);


    //add renderer
    auto pTexCoordBillboardParticleRendererFactory = new Ogre::TexCoordBillboardParticleRendererFactory();
    Ogre::ParticleSystemManager::getSingleton().addRendererFactory(pTexCoordBillboardParticleRendererFactory);//给粒子系统增加纹理坐标Billboard渲染器


    auto mMeshParticleRendererFactory = new Ogre::MeshComponentParticleRendererFactory();
    Ogre::ParticleSystemManager::getSingleton().addRendererFactory(mMeshParticleRendererFactory);//给粒子系统增加mesh渲染器

    auto mMeshRotationAffectorFactory = new Ogre::MeshRotationAffectorFactory();
    Ogre::ParticleSystemManager::getSingleton().addAffectorFactory(mMeshRotationAffectorFactory);//给粒子系统增加mesh旋转影响器

    auto mMeshAnimationAffectorFactory = new Ogre::MeshComponentAnimAffectorFactory();
    Ogre::ParticleSystemManager::getSingleton().addAffectorFactory(mMeshAnimationAffectorFactory);//给粒子系统增加mesh动画影响器

    auto mRibbonRendererFactory = new Ogre::RibbonRendererFactory;
    Ogre::ParticleSystemManager::getSingleton().addRendererFactory(mRibbonRendererFactory);//给粒子系统增加Ribbon渲染器

    auto mHeightFieldAffectorFactory = new Ogre::HeightFieldAffectorFactory;
    Ogre::ParticleSystemManager::getSingleton().addAffectorFactory(mHeightFieldAffectorFactory);//给粒子系统增加HeightField影响器
}