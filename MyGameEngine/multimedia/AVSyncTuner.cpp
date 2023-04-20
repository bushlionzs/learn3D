#include "AVSyncTuner.h"
#include "AVCommon.h"

#ifndef _WIN32
#define stricmp strcasecmp
#endif
extern "C" {
    typedef struct HLSContext {
        int n_variants;
        struct variant **variants;
        int n_playlists;
        struct playlist **playlists;
        int n_renditions;
        struct rendition **renditions;

        int cur_seq_no;
        int first_packet;
        int64_t base_starttime;
        int64_t first_timestamp;
        int64_t cur_timestamp;
        AVIOInterruptCB *interrupt_callback;
        char *user_agent;                    ///< holds HTTP user agent set as an AVOption to the HTTP protocol context
        char *cookies;                       ///< holds HTTP cookie values set in either the initial response or as an AVOption to the HTTP protocol context
        char *headers;                       ///< holds HTTP headers set as an AVOption to the HTTP protocol context
    } HLSContext;
}

CAVSyncTuner::CAVSyncTuner(AVFormatContext* pAVFormatContext, AV_SYNC_TYPE eType)
: m_pAVFormatContext(pAVFormatContext), m_eAVSyncType(eType)
{
    m_pVideoRender = NULL;
    m_pAudioRender = NULL;

    m_fStartTime = 0.0;
    m_bAudioClockStopped = true;
    m_bVideoClockStopped = true;
    m_bIsHLS = m_pAVFormatContext->iformat && m_pAVFormatContext->iformat->name && _stricmp(m_pAVFormatContext->iformat->name, "hls,applehttp") == 0;
}

void CAVSyncTuner::SetSyncType()
{

}

AV_SYNC_TYPE CAVSyncTuner::GetSyncTpye()
{
    return m_eAVSyncType;
}

double CAVSyncTuner::GetAudioClock(PTS_STATE& state)
{
    state = { 1, 0, 0, 0 };
    return m_pAudioRender ? m_pAudioRender->GetRenderClock(state) : 0;
}

double CAVSyncTuner::GetVideoClock(PTS_STATE& state)
{
    state = { 1, 0, 0, 0 };
    return m_pVideoRender ? m_pVideoRender->GetRenderClock(state) : 0;
}

double CAVSyncTuner::GetMasterClock(PTS_STATE& state)
{
    double clock = 0.0;
    state = { 1, 0, 0, 0 };
    switch ( m_eAVSyncType )
    {
    case AV_SYNC_AUDIO_MASTER:
        clock = m_pAudioRender ? m_pAudioRender->GetRenderClock(state) : m_pVideoRender->GetRenderClock(state);
        break;
    case AV_SYNC_VIDEO_MASTER:
        clock = m_pVideoRender ? m_pVideoRender->GetRenderClock(state) : m_pAudioRender->GetRenderClock(state);
        break;
    }
    return clock;
}

double CAVSyncTuner::GetPlayingTime(PTS_STATE& state)
{
    if (m_bIsHLS) {
        state = { 1, 0, 0, 0 };
        double playingtime = m_fStartTime;
        double timeoffset = 0;

        switch (m_eAVSyncType)
        {
        case AV_SYNC_AUDIO_MASTER:
            timeoffset = m_pAudioRender ? m_pAudioRender->GetPlayingTime(state) : m_pVideoRender->GetPlayingTime(state);
            state.stopped = state.stopped || (m_pAudioRender ? m_bAudioClockStopped : m_bVideoClockStopped);
            break;
        case AV_SYNC_VIDEO_MASTER:
            timeoffset = m_pVideoRender ? m_pVideoRender->GetPlayingTime(state) : m_pAudioRender->GetPlayingTime(state);
            state.stopped = state.stopped || (m_pVideoRender ? m_bVideoClockStopped : m_bAudioClockStopped);
            break;
        }

        if (!state.stopped && !state.not_running) {
            HLSContext* hls_ctx = (HLSContext*)m_pAVFormatContext->priv_data;
            playingtime = hls_ctx->base_starttime / (double)AV_TIME_BASE;
            playingtime += timeoffset;
        }

        return playingtime;
    }
    else {
        state = { 1, 0, 0, 0 };
        double playingtime = m_fStartTime;
        double render_clock = 0;

        switch (m_eAVSyncType)
        {
        case AV_SYNC_AUDIO_MASTER:
            render_clock = m_pAudioRender ? m_pAudioRender->GetRenderClock(state) : m_pVideoRender->GetRenderClock(state);
            state.stopped = state.stopped || (m_pAudioRender ? m_bAudioClockStopped : m_bVideoClockStopped);
            break;
        case AV_SYNC_VIDEO_MASTER:
            render_clock = m_pVideoRender ? m_pVideoRender->GetRenderClock(state) : m_pAudioRender->GetRenderClock(state);
            state.stopped = state.stopped || (m_pVideoRender ? m_bVideoClockStopped : m_bAudioClockStopped);
            break;
        }

        if (!state.stopped && !state.not_running) {
            playingtime = render_clock;
            if (m_pAVFormatContext->start_time != AV_NOPTS_VALUE) {
                playingtime -= m_pAVFormatContext->start_time/(double)AV_TIME_BASE;
            }
        }

        return playingtime;
    }
}

void CAVSyncTuner::SetVideoRender(CAVVideoRender* video_render)
{
    m_pVideoRender = video_render;
}

void CAVSyncTuner::SetAudioRender(CAVAudioRender* audio_render)
{
    m_pAudioRender = audio_render;
}

void CAVSyncTuner::OnSeek(double timeInSecond)
{
    m_fStartTime = timeInSecond;
    m_bAudioClockStopped = true;
    m_bVideoClockStopped = true;
}

void CAVSyncTuner::OnClockRunning(AVMediaType type)
{
    switch (type)
    {
    case AVMEDIA_TYPE_VIDEO:
        m_bVideoClockStopped = false;
        break;
    case AVMEDIA_TYPE_AUDIO:
        m_bAudioClockStopped = false;
        break;
    }
}
