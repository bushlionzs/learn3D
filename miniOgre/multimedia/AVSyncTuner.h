#pragma once

#include "AVClock.h"
#include "AVVideoRender.h"
#include "AVAudioRender.h"

#ifndef AV_SYNC_TYPE_DEFINED
enum AV_SYNC_TYPE
{
    AV_SYNC_AUDIO_MASTER,
    AV_SYNC_VIDEO_MASTER,
    AV_SYNC_EXTERNAL_CLOCK,
};
#define AV_SYNC_TYPE_DEFINED
#endif

enum AV_CLOCK_STRATEGY
{
    AV_CLOCK_PTS,
    AV_CLOCK_SYSTEM,
};

class CAVSyncTuner
{
public:
    CAVSyncTuner(AVFormatContext* pAVFormatContext, AV_SYNC_TYPE eType = AV_SYNC_AUDIO_MASTER);

public:
    void            SetSyncType();
    AV_SYNC_TYPE    GetSyncTpye();

    double          GetAudioClock(PTS_STATE& state);
    double          GetVideoClock(PTS_STATE& state);
    double          GetMasterClock(PTS_STATE& state);

    double          GetPlayingTime(PTS_STATE& state);

    void            OnSeek(double timeInSecond);
    void            OnClockRunning(AVMediaType type);


public:
    void            SetVideoRender(CAVVideoRender* video_render);
    void            SetAudioRender(CAVAudioRender* audio_render);

private:
    AV_SYNC_TYPE        m_eAVSyncType;

    AVFormatContext*    m_pAVFormatContext;
    CAVVideoRender*     m_pVideoRender;
    CAVAudioRender*     m_pAudioRender;

    volatile double     m_fStartTime;
    volatile bool       m_bAudioClockStopped;
    volatile bool       m_bVideoClockStopped;
    volatile bool       m_bIsHLS;
};
