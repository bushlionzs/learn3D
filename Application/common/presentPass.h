#pragma once
#include "pass.h"

class PresentPass : public PassBase
{
public:
    PresentPass(
        Ogre::OgreTexture* source, 
        Ogre::RenderWindow* renderWindow,
        bool useSRGB = false);
    ~PresentPass();

    virtual bool initialize()override;
    virtual void execute(RenderContext& context)override;
    virtual void update(RenderContext& context)override;
private:
    Ogre::OgreTexture* mSourceTexture;
    Ogre::RenderWindow* mRenderWindow;
    std::string mShaderName;
    bool mUseSRGB;
    filament::backend::Handle<filament::backend::HwPipeline> mPipelineHandle;
    filament::backend::Handle<filament::backend::HwProgram> mPresentHandle;
    filament::backend::Handle<filament::backend::HwDescriptorSet> mZeroSet;
};