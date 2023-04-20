#include "AVRenderBase.h"

#include <future>

#include "AVSyncTuner.h"
#include "AVCommon.h"


namespace
{
    const char* AV_TYPE_NAMES[] =
    {
        ("VIDEO"),
        ("AUDIO"),
        ("DATA"),
        ("SUBTITLE"),
        ("ATTACHMENT"),
    };
}

CAVRenderBase::CAVRenderBase(size_t numMaxFrames, AVStream* pAVStream, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback)
: CAVFrameQueue(numMaxFrames)
{
    m_pAVPlayCallback = callback;
    m_pAVSyncTuner = pAVSyncTuner;
    m_pAVStream = pAVStream;
    m_eAVType = pAVStream->codecpar->codec_type;

    m_bStop = true;
    m_bRunning = false;

    m_bCacheing = false;
    m_bPaused = false;
    m_bEof = false;

    m_fPlaytime = 0;

    m_fCurPTS = 0;
    m_oCurPTSDrift.Reset();

    m_fNextPTS = 0;

    m_nCurPTS = 0;
    m_nNextPTS = 0;

    m_nCurDuration = 0;

    m_bClockStopped = true;

    m_bAbortRender = false;
}

CAVRenderBase::~CAVRenderBase()
{
}

bool CAVRenderBase::Run()
{
    this->Stop();

    std::unique_lock<std::mutex> lock(m_mutexRender);

    m_bStop = false;
    this->Freeze(false);
    this->Flush();

    std::promise<void> barrier;
    m_thrdRender.reset(new std::thread(&CAVRenderBase::render_thread, this, std::ref(barrier)));
    barrier.get_future().wait();

    return m_bRunning;
}

void CAVRenderBase::Stop()
{
    std::unique_lock<std::mutex> lock(m_mutexRender);

    m_bStop = true;
    m_bAbortRender = true;
    this->Freeze(true);
    this->Flush();
    m_cvPause.notify_all();
    if ( m_thrdRender && m_thrdRender->joinable() )
        m_thrdRender->join();
}

void CAVRenderBase::Pause()
{
    std::unique_lock<std::mutex> lock(m_mutexPause);

    m_bPaused = true;
}

void CAVRenderBase::Resume()
{
    std::unique_lock<std::mutex> lock(m_mutexPause);

    m_bPaused = false;
    m_cvPause.notify_all();
}

void CAVRenderBase::OnCacheBegin()
{
    std::unique_lock<std::mutex> lock(m_mutexPause);

    m_bCacheing = true;
}

void CAVRenderBase::OnCacheEnd()
{
    std::unique_lock<std::mutex> lock(m_mutexPause);

    m_bCacheing = false;
    m_cvPause.notify_all();
}

void CAVRenderBase::AbortRender()
{
    m_bAbortRender = true;
    m_cvPause.notify_all();
}

bool CAVRenderBase::IsFinished()
{
    return this->NumFrames() == 0 && m_bEof;
}

double CAVRenderBase::GetRenderClock(PTS_STATE& state)
{
    state = { !m_bRunning, m_bClockStopped, m_bPaused, m_bEof };

    if (m_bRunning) {
        return m_fCurPTS + m_oCurPTSDrift.Time();
    }

    return 0.0;
}

double CAVRenderBase::GetPlayingTime(PTS_STATE& state)
{
    state = { !m_bRunning, m_bClockStopped, m_bPaused, m_bEof };

    return m_fPlaytime;
}

int CAVRenderBase::render_thread(std::promise<void>& barrier)
{
    if ( !this->open() )
    {
        barrier.set_value();
        return -1;
    }

    m_bCacheing = false;
    m_bPaused = false;
    m_bEof = false;
    m_bRunning = true;
    barrier.set_value();

    m_fPlaytime = 0;

    m_fCurPTS = 0;
    m_oCurPTSDrift.Reset();
    m_oCurPTSDrift.Pause();
    m_fNextPTS = 0;
    m_nCurPTS = 0;
    m_nNextPTS = 0;
    m_nCurDuration = 0;

    m_bClockStopped = true;
    m_bAbortRender = false;

    bool bNeedReset = true;
    AVFrame frame = { 0 };
    av_frame_unref(&frame);
    while ( !m_bStop )
    {
        {
            std::unique_lock<std::mutex> lock(m_mutexPause);
            while ( (m_bPaused||m_bCacheing) && !m_bStop )
            {
                m_oCurPTSDrift.Pause();
                m_cvPause.wait(lock);
                m_oCurPTSDrift.Resume();
            }
        }

        if ( this->PopFront(frame, true) <= 0 )
            continue;

        if ( IsFlushFrm(&frame) )
        {
            bNeedReset = true;

            m_bEof = false;
            m_bClockStopped = true;
            m_oCurPTSDrift.Pause();
            continue;
        }
        if ( IsEofFrm(&frame) )
        {
            m_bEof = true;
            m_oCurPTSDrift.Pause();
            continue;
        }

        m_bEof = false;
        m_bAbortRender = false;

        if (bNeedReset)
        {
            bNeedReset = false;

            m_fPlaytime = 0;

            /* received first frame, init the clock.*/
            int64_t frame_pts = frame.best_effort_timestamp;
            if ( frame_pts == AV_NOPTS_VALUE )
                frame_pts = 0;

            double frame_dpts = frame_pts * av_q2d(m_pAVStream->time_base);

            m_fCurPTS = frame_dpts;
            m_oCurPTSDrift.Reset();

            m_nCurPTS = frame_pts;

            m_nCurDuration = 0;

            frame.pts = *reinterpret_cast<int64_t*>(&frame_dpts);

            m_bClockStopped = false;
            m_bAbortRender = false;

            m_pAVSyncTuner->OnClockRunning(m_eAVType);

            AV_LOG(INFO, AV_TYPE_NAMES[m_eAVType] << " seek to pos " << m_fCurPTS );
        }
        else
        {
            int64_t frame_pts = frame.best_effort_timestamp;
            if (frame_pts == AV_NOPTS_VALUE)
            {
                frame.best_effort_timestamp = m_nNextPTS;
                frame.pts = *reinterpret_cast<int64_t*>(&m_fNextPTS);
            }
            else if (frame_pts < m_nCurPTS)
            {
                double frame_dpts = frame_pts * av_q2d(m_pAVStream->time_base);
                m_fCurPTS = frame_dpts;
                m_oCurPTSDrift.Reset();
                frame.pts = *reinterpret_cast<int64_t*>(&frame_dpts);
            }
            else
            {
                double frame_dpts = frame_pts * av_q2d(m_pAVStream->time_base);
                frame.pts = *reinterpret_cast<int64_t*>(&frame_dpts);
            }
        }

        this->render_frame(frame);

        UnrefFrm(&frame);
    }

    UnrefFrm(&frame);

    m_bRunning = false;
    this->close();

    return 0;
}
