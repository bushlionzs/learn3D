#pragma once

#include <future>

#include "FFmpegLib.h"

#include "AVFrameQueue.h"
#include "AVClock.h"
#include "AVPlayCallback.h"

class CAVSyncTuner;

struct PTS_STATE
{
    uint32_t not_running    : 1;
    uint32_t stopped        : 1;
    uint32_t paused         : 1;
    uint32_t eof            : 1;
};

class CAVRenderBase : public CAVFrameQueue
{
public:
    CAVRenderBase(size_t numMaxFrames, AVStream* pAVStream, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback);
    virtual ~CAVRenderBase();

public:
    bool    Run();
    void    Stop(); // must called before the render object destroyed.
    void    Pause();
    void    Resume();

    void    OnCacheBegin();
    void    OnCacheEnd();

    void    AbortRender();

    bool    IsFinished();

public:
    double  GetRenderClock(PTS_STATE& state);
    double  GetPlayingTime(PTS_STATE& state);

private:
    using CAVFrameQueue::PopFront;

private:
    int     render_thread(std::promise<void>& barrier);

private:
    virtual bool    open() = 0;
    virtual bool    close() = 0;
    virtual int     render_frame(AVFrame& frame) = 0;

protected:
    IAVPlayCallback*                    m_pAVPlayCallback;
    CAVSyncTuner*                       m_pAVSyncTuner;
    AVStream*                           m_pAVStream;
    AVMediaType                         m_eAVType;

private:
    std::unique_ptr<std::thread>        m_thrdRender;
    volatile bool                       m_bStop;
    volatile bool                       m_bRunning;
    std::mutex                          m_mutexRender;
    std::condition_variable             m_cvRender;

protected:
    volatile bool                       m_bCacheing;
    volatile bool                       m_bPaused;
    volatile bool                       m_bEof;
    std::mutex                          m_mutexPause;
    std::condition_variable             m_cvPause;

// sync control
protected:
    double                              m_fPlaytime;

    double                              m_fCurPTS;
    CAVClock                            m_oCurPTSDrift; // Playing Time = m_fCurPTS + m_oPlayingClockDrift.Time()

    double                              m_fNextPTS; // predict next frame pts.

    int64_t                             m_nCurPTS;
    int64_t                             m_nNextPTS;

    int64_t                             m_nCurDuration;

    volatile bool                       m_bClockStopped;

    volatile bool                       m_bAbortRender;
};
