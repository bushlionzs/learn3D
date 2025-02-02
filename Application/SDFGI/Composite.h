#pragma once
#include "pass.h"
#include "SDFGIContext.h"

class CompositePass : public PassBase
{
public:
    CompositePass(
        RenderWindow* renderWindow,
        SDFGIContext& context);
    ~CompositePass();

    virtual bool initialize()override;
    virtual void execute(RenderSystem* rs)override;
    virtual void update(float delta)override;
private:
    RenderWindow* mRenderWindow;
    Handle<HwPipeline> mPipelineHandle;

    std::vector< Handle<HwDescriptorSet>> setlist;
    Handle<HwDescriptorSet> mCompositeZeroSet;
    Handle<HwDescriptorSet> mCompositeFirstSet;
    Handle<HwDescriptorSet> mCompositeSecondSet;
    Handle<HwDescriptorSet> mCompositeThirdSet;

    SDFGIContext& mContext;
};