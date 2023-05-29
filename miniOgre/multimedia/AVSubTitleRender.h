#pragma once

#include "AVRenderBase.h"

class CAVSubTitleRender : public CAVRenderBase
{
public:
    CAVSubTitleRender(size_t numMaxFrames, AVStream* pAVStream, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback);

private:
    virtual bool    open();
    virtual bool    close();
    virtual int     render_frame(AVFrame& frame);
};
