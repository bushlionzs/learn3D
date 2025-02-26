#pragma once
#include "pass.h"

class PresentPass : public PassBase
{
public:
    PresentPass(
        Ogre::OgreTexture* source, 
        Ogre::RenderWindow* renderWindow,
        const char* shaderName = nullptr);
    ~PresentPass();

    virtual bool initialize()override;
    virtual void execute(RenderSystem* rs)override;
    virtual void update(float delta)override;
private:
    Ogre::OgreTexture* mSourceTexture;
    Ogre::RenderWindow* mRenderWindow;
    std::string mShaderName;
    filament::backend::Handle<filament::backend::HwPipeline> mPipelineHandle;

    filament::backend::Handle<filament::backend::HwDescriptorSet> mZeroSet;
};