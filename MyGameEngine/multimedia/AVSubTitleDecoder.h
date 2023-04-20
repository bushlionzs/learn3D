#pragma once

#include "AVDecoderBase.h"
#include "AVSubTitleRender.h"

class CAVSubTitleDecoder : public CAVDecoderBase
{
public:
    CAVSubTitleDecoder();

private:
    virtual CAVRenderBase* new_render(AVStream* pAVStream, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback);
    virtual int            decode(AVPacket* pkt);
    virtual void           cleanup();
};
