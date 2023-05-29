#include "AVClock.h"
#include "FFmpegLib.h"

double CAVClock::Time() const
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if ( m_bPaused )
        return m_nBase / kAVTimeBase;

    return (m_nBase + av_gettime_relative() - m_nStartTime) / kAVTimeBase;
}

void CAVClock::Reset()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_nBase = 0;
    m_nStartTime = av_gettime_relative();
    m_bPaused = false;
}

void CAVClock::Pause()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if ( !m_bPaused )
    {
        int64_t now_time = av_gettime_relative();
        m_nBase += (now_time - m_nStartTime);
        m_bPaused = true;
    }
}

void CAVClock::Resume()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if ( m_bPaused )
    {
        m_nStartTime = av_gettime_relative();
        m_bPaused = false;
    }
}
