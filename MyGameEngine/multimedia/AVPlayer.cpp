#include "AVPlayer.h"
#include "AVCommon.h"
#include <stdint.h>
#include <limits>
#include <thread>
#include <chrono>

int CAVPlayer::av_io_interrupt_cb(void* ctx)
{
    CAVPlayer* player = (CAVPlayer*)ctx;
    return player->m_bStop;
};

namespace
{

void print_error(int err)
{
    char errbuf[256];
    const char *errbuf_ptr = errbuf;

    if (av_strerror(err, errbuf, sizeof(errbuf)) < 0)
        errbuf_ptr = strerror(AVUNERROR(err));
    AV_LOG(ERROR, errbuf_ptr);
}

}


std::shared_ptr<CAVPlayer> CAVPlayer::Create()
{
    return std::shared_ptr<CAVPlayer>(new CAVPlayer(), [](CAVPlayer* p) { delete p; });
}

CAVPlayer::CAVPlayer()
{
    m_pAVPlayCallback = NULL;

    m_bStop = true;

    m_eSyncType = AV_SYNC_AUDIO_MASTER;
    m_bAutoExit = true;
    m_bPlaying = false;
    m_bSeeking = false;
    m_bEof = false;

    m_pFormatContext = NULL;

    m_fStartTimeInSecond = 0;

    m_ePlayerState = AVPlayerState_Stopped;
}

CAVPlayer::~CAVPlayer()
{
    this->Stop();
}

bool CAVPlayer::Play(const char* filename, IAVPlayCallback* callback, const Config& config, bool block)
{
    this->Stop(block);

    std::unique_lock<std::mutex> lock(m_mutexRun);

    m_bStop = false;
    m_pAVPlayCallback = callback;
    m_strFileName = filename;

    std::promise<void> barrier;
    m_thrdInputReader.reset(new std::thread(&CAVPlayer::read_thread, shared_from_this(), m_strFileName.c_str(), config, block ? &barrier : nullptr));
    if (block) {
        barrier.get_future().wait();
        return m_bPlaying;
    }
    return true;
}

bool CAVPlayer::Stop(bool block)
{
    std::unique_lock<std::mutex> lock(m_mutexRun);

    m_bStop = true;
    if (m_thrdInputReader)
        block && m_thrdInputReader->joinable() ? m_thrdInputReader->join() : m_thrdInputReader->detach();

    m_thrdInputReader.reset();

    return true;
}

bool CAVPlayer::Pause()
{
    if (!m_bPlaying)
        return false;

    AVPlayerEvent event_pause = { AVPlayerEvent_Pause, 0.0 };
    m_pEventQueue->PushEvent(event_pause);
    return true;
}

bool CAVPlayer::Resume()
{
    if (!m_bPlaying)
        return false;

    AVPlayerEvent event_resume = { AVPlayerEvent_Resume, 0.0 };
    m_pEventQueue->PushEvent(event_resume);
    return true;
}

bool CAVPlayer::Seek(double timeOffsetInSecond, int origin)
{
    if (!m_bPlaying)
        return false;

    double pos;
    PTS_STATE state;
    switch (origin)
    {
    case SEEK_CUR:
        pos = this->CurPlayTime(state) + timeOffsetInSecond;
        break;
    case SEEK_SET:
        pos = timeOffsetInSecond;
        break;
    case SEEK_END:
        pos = this->Duration() + timeOffsetInSecond;
        break;
    }

    if (fabs(this->CurPlayTime(state) - pos) < 0.1) {
        AV_LOG(INFO, "ignore duplicate seek request: " << pos);
        return true;
    }

    AVPlayerEvent event_seek = { AVPlayerEvent_Seek, pos };
    m_pEventQueue->PushEvent(event_seek);
    return true;
}

double CAVPlayer::GetVolume()
{
    if (!m_bPlaying)
        return 0;

    if (!m_pAudioDecoder)
        return 0;

    return m_pAudioDecoder->GetVolume();
}

void CAVPlayer::SetVolume(double volume)
{
    if (!m_bPlaying)
        return;

    AVPlayerEvent event_volume = { AVPlayerEvent_Volume, volume };
    m_pEventQueue->PushEvent(event_volume);
}

double CAVPlayer::Duration()
{
    if (!m_bPlaying)
        return 0;

    return (double)m_pFormatContext->duration / AV_TIME_BASE;
}

double CAVPlayer::CurPlayTime(PTS_STATE& state)
{
    state = { 1, 0, 0, 0 };
    if (!m_bPlaying || !m_pAVSyncTuner)
        return m_fStartTimeInSecond;

    return m_pAVSyncTuner->GetPlayingTime(state);
}

double CAVPlayer::StartPlayTime()
{
    return m_fStartTimeInSecond;
}

double CAVPlayer::DownloadRate()
{
    if (!m_bPlaying)
        return 0;

    if (!m_pAVBitRateCounter)
        return 0;

    return m_pAVBitRateCounter->SampleRate() / 1024;
}

int CAVPlayer::VideoWidth()
{
    if (!m_bPlaying || !m_pAVDemuxer->GetVideoStream())
        return 0;

    return m_pAVDemuxer->GetVideoStream()->codecpar->width;
}

int CAVPlayer::VideoHeight()
{
    if (!m_bPlaying || !m_pAVDemuxer->GetVideoStream())
        return 0;

    return m_pAVDemuxer->GetVideoStream()->codecpar->height;
}

AV_PLAYER_STATE CAVPlayer::CurPlayerState()
{
    return m_ePlayerState;
}

bool CAVPlayer::IsReady()
{
    return m_bPlaying;
}

void CAVPlayer::OnCacheBegin()
{
    AV_LOG(INFO, "OnCacheBegin");

    if (m_pAVPlayCallback)  m_pAVPlayCallback->OnCacheBegin();
    if (m_pVideoDecoder)    m_pVideoDecoder->OnCacheBegin();
    if (m_pAudioDecoder)    m_pAudioDecoder->OnCacheBegin();
}

void CAVPlayer::OnCacheEnd()
{
    AV_LOG(INFO, "OnCacheEnd");

    if (m_pAVPlayCallback)  m_pAVPlayCallback->OnCacheEnd();
    if (m_pVideoDecoder)    m_pVideoDecoder->OnCacheEnd();
    if (m_pAudioDecoder)    m_pAudioDecoder->OnCacheEnd();
}

//////////////////////////////////////////////////////////////////////////
///

bool CAVPlayer::open(const char* filename, bool hwaccel)
{
    AVDictionary *opts = NULL;

    m_pFormatContext = avformat_alloc_context();
    m_pFormatContext->flags = AVFMT_FLAG_GENPTS;
    m_pFormatContext->interrupt_callback.callback = av_io_interrupt_cb;
    m_pFormatContext->interrupt_callback.opaque = this;

    int openErr = avformat_open_input(&m_pFormatContext, filename, NULL, &opts);
    if (openErr < 0)
    {
        av_dict_free(&opts);
        print_error(openErr);
        avformat_free_context(m_pFormatContext);
        m_pFormatContext = NULL;
        return false;
    }
    av_dict_free(&opts);

    if (m_pFormatContext->pb)
        m_pFormatContext->pb->eof_reached = 0;

    av_format_inject_global_side_data(m_pFormatContext);

    m_pAVDemuxer.reset(new CAVDemuxer);
    if (!m_pAVDemuxer->Open(m_pFormatContext, this))
    {
        m_pAVDemuxer.reset();

        avformat_close_input(&m_pFormatContext);
        avformat_free_context(m_pFormatContext);
        m_pFormatContext = NULL;

        return false;
    }

    m_pAVSyncTuner.reset(new CAVSyncTuner(m_pFormatContext, AV_SYNC_AUDIO_MASTER));

    bool openDecoderOk = false;
    if (m_pAVDemuxer->GetVideoStream())
    {
        m_pVideoDecoder.reset(new CAVVideoDecoder());
    }
    if (m_pAVDemuxer->GetAudioStream())
    {
        m_pAudioDecoder.reset(new CAVAudioDecoder());
    }
    if (m_pVideoDecoder)
    {
        m_pVideoDecoder->Pause();
        if (m_pVideoDecoder->Run(m_pAVDemuxer->GetVideoStream(), m_pAVDemuxer.get(), m_pAVSyncTuner.get(), m_pAVPlayCallback, hwaccel)) {
            openDecoderOk = true;
        }
        else {
            m_pVideoDecoder->Stop();
            m_pVideoDecoder.reset();
            m_pAVDemuxer->CloseVideo();
        }
    }
    if (m_pAudioDecoder)
    {
        m_pAudioDecoder->Pause();
        if (m_pAudioDecoder->Run(m_pAVDemuxer->GetAudioStream(), m_pAVDemuxer.get(), m_pAVSyncTuner.get(), m_pAVPlayCallback, hwaccel)) {
            openDecoderOk = true;
        }
        else {
            m_pAudioDecoder->Stop();
            m_pAudioDecoder.reset();
            m_pAVDemuxer->CloseAudio();
        }
    }
    if (m_pVideoDecoder)
        m_pVideoDecoder->Resume();
    if (m_pAudioDecoder)
        m_pAudioDecoder->Resume();

    if (!openDecoderOk)
    {
        if (m_pSubTitleDecoder)
        {
            m_pSubTitleDecoder->Stop();
            m_pSubTitleDecoder.reset();
        }

        m_pAVDemuxer.reset();
        m_pAVSyncTuner.reset();

        avformat_close_input(&m_pFormatContext);
        avformat_free_context(m_pFormatContext);
        m_pFormatContext = NULL;
        return false;
    }

    m_pEventQueue.reset(new CAVPlayerEventQueue);

    m_pAVBitRateCounter.reset(new CAVBitrateCounter);

    return true;
}

bool CAVPlayer::close()
{
    m_pAVDemuxer->Freeze(true);
    m_pAVDemuxer->Flush();

    if (m_pEventQueue)
    {
        m_pEventQueue.reset();
    }
    if (m_pAVBitRateCounter)
    {
        m_pAVBitRateCounter.reset();
    }
    if (m_pSubTitleDecoder)
    {
        m_pSubTitleDecoder->Stop();
        m_pSubTitleDecoder.reset();
    }
    if (m_pAudioDecoder)
    {
        m_pAudioDecoder->Stop();
        m_pAudioDecoder.reset();
    }
    if (m_pVideoDecoder)
    {
        m_pVideoDecoder->Stop();
        m_pVideoDecoder.reset();
    }
    if (m_pAVSyncTuner)
    {
        m_pAVSyncTuner.reset();
    }
    if (m_pAVDemuxer)
    {
        m_pAVDemuxer->Close();
        m_pAVDemuxer.reset();
    }
    if (m_pFormatContext)
    {
        avformat_close_input(&m_pFormatContext);
        avformat_free_context(m_pFormatContext);
        m_pFormatContext = NULL;
    }

    return true;
}


int CAVPlayer::read_thread(const char* filename, const Config& config, std::promise<void>* barrier)
{
    m_bPlaying = false;
    m_bSeeking = false;

    if (!this->open(filename, config.hwaccel))
    {
        if(barrier) barrier->set_value();
        return -1;
    }
    if (m_pVideoDecoder) {
        m_pVideoDecoder->SetRenderSize(config.render_width, config.render_height);
    }
    if (m_pAudioDecoder) {
        m_pAudioDecoder->SetVolume(config.volume);
    }

    m_fStartTimeInSecond = config.startTimeInPersent * m_pFormatContext->duration / AV_TIME_BASE;
    m_eSyncType = config.syncType;
    m_bEof = false;
    m_bAutoExit = config.autoExit;

    if (m_fStartTimeInSecond != 0.0)
        this->seek_imp(m_fStartTimeInSecond);

    m_bPlaying = true;
    if(barrier) barrier->set_value();

#ifdef DEBUG_AV_PLAYER
    m_thrdAVStateReporter.reset(new std::thread(&CAVPlayer::av_state_reporter_thread, this));
#endif

    this->set_player_state(AVPlayerState_Playing);

    int ret = 0;
    int pushOk = 1;
    AVPacket pkt = { 0 };
    while (!m_bStop)
    {
        if (!this->handle_playerevent())
        {
            ret = 0;
            break;
        }

        if (pushOk != 0)
        {
            int readErr = av_read_frame(m_pFormatContext, &pkt);
            if (m_bSeeking) {
                m_bSeeking = false;
                AV_LOG(INFO, "seek done. read continued.");
            }
            if (readErr < 0)
            {
                if (this->handle_read_err(readErr))
                    continue;
                else
                {
                    ret = readErr;
                    break;
                }
            }
            if (m_bEof)
            {
                m_bEof = false;
                m_pAVDemuxer->SetEof(m_bEof);
            }
            m_pAVBitRateCounter->AddSamples(pkt.size);
        }

        pushOk = m_pAVDemuxer->PushPkt(pkt, false);

        if (pushOk == 0) // decode queue full, if -1 the pkt discarded.
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }
    }

    m_fStartTimeInSecond = 0;
    m_bStop = true;
    m_bPlaying = false;
    m_bSeeking = false;
    this->close();

    this->set_player_state(AVPlayerState_Stopped);

#ifdef DEBUG_AV_PLAYER
    m_thrdAVStateReporter->join();
    m_thrdAVStateReporter.reset();
#endif

    return 0;
}

int CAVPlayer::handle_playerevent()
{
    AVPlayerEvent event;

    while (m_pEventQueue->PopEvent(event))
    {
        switch (event.eventType)
        {
        case AVPlayerEvent_Volume:
            if (m_pAudioDecoder)  m_pAudioDecoder->SetVolume(event.value);
            break;

        case AVPlayerEvent_Pause:
            if (m_pVideoDecoder)      m_pVideoDecoder->Pause();
            if (m_pAudioDecoder)      m_pAudioDecoder->Pause();
            if (m_pSubTitleDecoder)   m_pSubTitleDecoder->Pause();

            this->set_player_state(AVPlayerState_Paused);
            break;

        case AVPlayerEvent_Resume:
            if (m_pVideoDecoder)      m_pVideoDecoder->Resume();
            if (m_pAudioDecoder)      m_pAudioDecoder->Resume();
            if (m_pSubTitleDecoder)   m_pSubTitleDecoder->Resume();

            this->set_player_state(AVPlayerState_Playing);
            break;

        case AVPlayerEvent_Seek:
            this->seek_imp(event.value);
            break;

        case AVPlayerEvent_Stop:
            return 0;
            break;
        }
    }
    return 1;
}

int CAVPlayer::handle_read_err(int err)
{
    if (m_pFormatContext->pb && m_pFormatContext->pb->error)
        return 0;

    if (err == AVERROR_EOF || avio_feof(m_pFormatContext->pb))
    {
        bool all_finished = true;
        if (m_pAVDemuxer) { all_finished &= (m_pAVDemuxer->NumTotalPkts() == 0); }
        if (m_pVideoDecoder) { all_finished &= m_pVideoDecoder->IsFinished(); }
        if (m_pAudioDecoder) { all_finished &= m_pAudioDecoder->IsFinished(); }
        if (m_pSubTitleDecoder) { all_finished &= m_pSubTitleDecoder->IsFinished(); }

        if (all_finished)
        {
            this->set_player_state(AVPlayerState_Completed);

            if (m_bAutoExit)
                return 0;
        }

        if (!m_bEof)
        {
            AV_LOG(INFO, "EOF reached");
            m_bEof = true;
            m_pAVDemuxer->SetEof(m_bEof);
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return 1;
}

bool CAVPlayer::seek_imp(double timeInSecond)
{
    int64_t seek_pos = (int64_t)(timeInSecond*AV_TIME_BASE);
    if (m_pFormatContext->start_time != AV_NOPTS_VALUE)
        seek_pos += m_pFormatContext->start_time;

    int seekErr = avformat_seek_file(m_pFormatContext, -1, INT64_MIN, seek_pos, INT64_MAX, 0);
    if (seekErr >= 0)
    {
        AV_LOG(INFO, "seek to pos: " << timeInSecond);
        m_bEof = false;
        m_bSeeking = true;

        m_pAVSyncTuner->OnSeek(timeInSecond);

        m_pAVDemuxer->Flush();

        if (m_pVideoDecoder) { m_pVideoDecoder->OnSeek(); }
        if (m_pAudioDecoder) { m_pAudioDecoder->OnSeek(); }
        if (m_pSubTitleDecoder) { m_pSubTitleDecoder->OnSeek(); }

        if (m_ePlayerState != AVPlayerState_Paused)
            this->set_player_state(AVPlayerState_Playing);

        return true;
    }
    else
    {
        AV_LOG(ERROR, m_strFileName.c_str() << " could not seek to position " << timeInSecond << " second!");
        return false;
    }
}

void CAVPlayer::set_player_state(AV_PLAYER_STATE state)
{
    if (m_ePlayerState != state)
    {
        m_ePlayerState = state;
        if (m_pAVPlayCallback)
            m_pAVPlayCallback->OnPlayerStateChanged(state);

        switch (m_ePlayerState)
        {
        case AVPlayerState_Playing:
            AV_LOG(INFO, "AVPlayerState_Playing");
            break;
        case AVPlayerState_Paused:
            AV_LOG(INFO, "AVPlayerState_Paused");
            break;
        case AVPlayerState_Completed:
            AV_LOG(INFO, "AVPlayerState_Completed");
            break;
        case AVPlayerState_Stopped:
            AV_LOG(INFO, "AVPlayerState_Stopped");
            break;
        }
    }
}

#ifdef DEBUG_AV_PLAYER
inline
int hours(int64_t sec)
{
    return static_cast<int>(sec / 3600);
}

inline
int minutes(int64_t sec)
{
    return static_cast<int>((sec % 3600) / 60);
}

inline
int seconds(int64_t sec)
{
    return static_cast<int>(sec % 60);
}

int CAVPlayer::av_state_reporter_thread()
{
    while (m_pAVSyncTuner && m_pAVDemuxer && !m_bStop && m_bPlaying)
    {
        double aClock = 0, vClock = 0, vSize = 0, aSize = 0, bps = 0, bps_in = 0, bps_out = 0;
        PTS_STATE m_state, a_state, v_state;

        int64_t duration = (int64_t)this->Duration();
        int64_t play_time = (int64_t)this->CurPlayTime(m_state);

        aClock = m_pAVSyncTuner->GetAudioClock(a_state);
        vClock = m_pAVSyncTuner->GetVideoClock(v_state);
        vSize = m_pAVDemuxer->VideoSize() / 1024.;
        aSize = m_pAVDemuxer->AudioSize() / 1024.;
        bps = this->DownloadRate();
        bps_in = m_pAVDemuxer->GetBPSIn();
        bps_out = m_pAVDemuxer->GetBPSOut();

        printf("\rEOF:%d M/D: %02d:%02d:%02d / %02d:%02d:%02d vq:%8.2fkb aq:%8.2fkb A: %8.3f V: %8.3f  A-V: %+8.3f dBPS:%7.2fkb/s iBPS:%7.2fkb/s oBPS:%7.2fkb/s  ",
            m_bEof ? 1 : 0,
            hours(play_time), minutes(play_time), seconds(play_time), hours(duration), minutes(duration), seconds(duration),
            vSize, aSize, aClock, vClock, aClock - vClock, bps, bps_in, bps_out);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 0;
}
#endif
