#pragma once

#include <cstdint>

#include "FFmpegLib.h"

#include "AVDecoderBase.h"
#include "AVAudioRender.h"

class CAVAudioDecoder : public CAVDecoderBase
{
public:
    CAVAudioDecoder();

public:
    double                  GetVolume();
    void                    SetVolume(double vol);

private:
    virtual CAVRenderBase*  new_render(AVStream* pAVStream, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback);
    virtual int             decode(AVPacket* pkt);
    virtual void            cleanup();

private:
    bool                    convert_frame_copy(AVFrame* src_frame, AVFrame* dst_frame);

private:
    SwrContext*             m_pSwrContext;

#ifdef DEBUG_AUDIO_DECODE
    FILE*                   m_fOrgOutput;
    FILE*                   m_fCvtOutput;
#endif
};
