#pragma once

#include "AVRenderBase.h"

class CAVVideoRender : public CAVRenderBase
{
public:
    CAVVideoRender(size_t numMaxFrames, AVStream* pAVStream, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback);

private:
    virtual bool    open();
    virtual bool    close();
    virtual int     render_frame(AVFrame& frame);
};
