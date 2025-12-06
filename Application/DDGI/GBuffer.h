#pragma once
#include <DriverBase.h>
#include "ddgiTypes.h"
#include "GIContext.h"

class GBuffer: public PassBase
{
public:
    GBuffer(SDFGIContext& context);
    virtual bool initialize();
    virtual void update(float delta);
    virtual void execute(RenderContext& context);
private:
    bool loadAndCompileShaders();

    void updateDescriptorSet();
private:
    Handle<HwRaytracingProgram> mProgramHandle;

    std::vector<Handle<HwDescriptorSet>> mGBufferZeroSets;

    SDFGIContext& mContext;
};