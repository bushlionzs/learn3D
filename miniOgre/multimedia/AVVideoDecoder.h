#pragma once

#include "AVDecoderBase.h"
#include "AVVideoRender.h"

class CAVVideoDecoder : public CAVDecoderBase
{
public:
    CAVVideoDecoder();

    void SetRenderSize(int w, int h);

private:
    virtual CAVRenderBase*  new_render(AVStream* pAVStream, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback);
    virtual int             decode(AVPacket* pkt);
    virtual void            cleanup();

private:
    bool                    convert_frame_copy(AVFrame* src_frame, AVFrame* dst_frame);

private:
    SwsContext*             m_pSwsContext;
    int                     m_nVideoRotation;
    int                     m_nRenderWidth = 0;
    int                     m_nRenderHeight = 0;
};
