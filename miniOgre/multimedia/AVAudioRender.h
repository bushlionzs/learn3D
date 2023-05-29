#pragma once

#include "AVRenderBase.h"
#include "AudioPlayer.h"


class CAVAudioRender : public CAVRenderBase
{
public:
    CAVAudioRender(size_t numMaxFrames, AVStream* pAVStream, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback);

public:
    double          GetVolume();
    void            SetVolume(double vol);

private:
    virtual bool    open();
    virtual bool    close();
    virtual int     render_frame(AVFrame& frame);

private:
    CAudioPlayer    m_oAudioPlayer;
};
