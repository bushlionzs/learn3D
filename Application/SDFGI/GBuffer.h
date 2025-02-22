#pragma once
#include <DriverBase.h>
#include "ddgiTypes.h"
#include "SDFGIContext.h"

class GBuffer: public PassBase
{
public:
    GBuffer(SDFGIContext& context);
    virtual bool initialize();
    virtual void update(float delta);
    virtual void execute(RenderSystem* rs);
private:
    bool loadAndCompileShaders();

    void updateDescriptorSet();
private:
    Handle<HwRaytracingProgram> mProgramHandle;

    Handle<HwDescriptorSet> mGBufferZeroSet;

    SDFGIContext& mContext;
};