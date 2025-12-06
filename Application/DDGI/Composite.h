#pragma once
#include "pass.h"
#include "GIContext.h"

class CompositePass : public PassBase
{
public:
    CompositePass(
        RenderWindow* renderWindow,
        SDFGIContext& context);
    ~CompositePass();

    virtual bool initialize()override;
    virtual void execute(RenderContext& context)override;
    virtual void update(float delta)override;
private:
    RenderWindow* mRenderWindow;
    Handle<HwPipeline> mPipelineHandle;
    Handle<HwProgram> mPresentHandle;
    std::vector<Handle<HwDescriptorSet>> mCompositeZeroSets;


    SDFGIContext& mContext;
};