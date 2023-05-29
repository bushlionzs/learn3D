#pragma once

#include "AVDemuxer.h"
#include "AVVideoDecoder.h"
#include "AVAudioDecoder.h"
#include "AVSubTitleDecoder.h"
#include "AVSyncTuner.h"
#include "AVPlayerEventQueue.h"
#include "AVPlayCallback.h"
#include "SampleCounter.h"

enum AV_PLAYER_STATE
{
    AVPlayerState_Playing,
    AVPlayerState_Paused,
    AVPlayerState_Completed,
    AVPlayerState_Stopped,
};

class CAVPlayer : public IAVCacheCallBack
                , public std::enable_shared_from_this<CAVPlayer>
{
public:

    struct Config
    {
        bool hwaccel = false;
        bool autoExit = true;
        double startTimeInPersent = 0;
        int render_width = 0;
        int render_height = 0;
        double volume = 0;
        AV_SYNC_TYPE syncType = AV_SYNC_AUDIO_MASTER;
    };

    static std::shared_ptr<CAVPlayer> Create();

private:
    CAVPlayer();
    ~CAVPlayer();

public:
    bool            Play(const char* filename, IAVPlayCallback* callback, const Config& config, bool block=false);
    bool            Stop(bool block = true);

    bool            Pause();
    bool            Resume();

    bool            Seek(double timeOffsetInSecond, int origin=SEEK_SET);

    double          GetVolume();
    void            SetVolume(double volume); // [0, 1], 0 for muted

    double          Duration();     // unit: second
    double          CurPlayTime(PTS_STATE& state);  // unit: second
    double          StartPlayTime();// unit: second

    double          DownloadRate(); // unit: KB/S

    int             VideoWidth();
    int             VideoHeight();

    AV_PLAYER_STATE CurPlayerState();
    bool            IsReady();

public:
    virtual void    OnCacheBegin();
    virtual void    OnCacheEnd();

private:
    static int  av_io_interrupt_cb(void* ctx);
    int         read_thread(const char* filename, const Config& config, std::promise<void>* barrier);
    int         handle_playerevent();   // return 0 when receive stop event.
    int         handle_read_err(int err);      // return 0 to end the read loop, 1 to goto the next poll.

private:
    bool        open(const char* filename, bool hwaccel);
    bool        close();
    bool        seek_imp(double timeInSecond);
    void        set_player_state(AV_PLAYER_STATE state);

private:
    std::unique_ptr<std::thread>            m_thrdInputReader;
    volatile bool                           m_bStop;
    std::mutex                              m_mutexRun;
    std::string                             m_strFileName;

    IAVPlayCallback*                        m_pAVPlayCallback;

    AV_SYNC_TYPE                            m_eSyncType;
    bool                                    m_bAutoExit;
    volatile AV_PLAYER_STATE                m_ePlayerState;
    volatile bool                           m_bPlaying;
    volatile bool                           m_bSeeking;
    volatile bool                           m_bEof;

    double                                  m_fStartTimeInSecond;
    AVFormatContext*                        m_pFormatContext;

    std::unique_ptr<CAVDemuxer>             m_pAVDemuxer;

    std::unique_ptr<CAVVideoDecoder>        m_pVideoDecoder;
    std::unique_ptr<CAVAudioDecoder>        m_pAudioDecoder;
    std::unique_ptr<CAVSubTitleDecoder>     m_pSubTitleDecoder;

    std::unique_ptr<CAVPlayerEventQueue>    m_pEventQueue;

    std::unique_ptr<CAVSyncTuner>           m_pAVSyncTuner;

    std::unique_ptr<CAVBitrateCounter>      m_pAVBitRateCounter;

#ifdef DEBUG_AV_PLAYER
    std::unique_ptr<std::thread>            m_thrdAVStateReporter;
    int av_state_reporter_thread();
#endif
};

