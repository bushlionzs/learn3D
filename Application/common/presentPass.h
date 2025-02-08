#pragma once
#include "pass.h"

class PresentPass : public PassBase
{
public:
    PresentPass(
        Ogre::RenderTarget* sourceTarget, 
        Ogre::RenderWindow* renderWindow,
        const char* shaderName);
    ~PresentPass();

    virtual bool initialize()override;
    virtual void execute(RenderSystem* rs)override;
    virtual void update(float delta)override;
private:
    Ogre::RenderTarget* mSourceTarget;
    Ogre::RenderWindow* mRenderWindow;
    std::string mShaderName;
    Handle<HwPipeline> mPipelineHandle;

    Handle<HwDescriptorSet> mZeroSet;
};