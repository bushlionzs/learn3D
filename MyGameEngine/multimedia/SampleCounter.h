#pragma once

#include "FFmpegLib.h"

template<size_t MAX_SAMPLES=5, int64_t SAMPLE_DURATION_US=AV_TIME_BASE>
class CSampleCounter
{
public:
    CSampleCounter();

public:
    void    AddSamples(size_t numBytes);
    double  SampleRate(); // how many samples per second.

private:
    void    reset();
    double  calcSampleRate();

private:
    bool    m_bActivity;
    int64_t m_nLastActivityTime;

    size_t  m_SampleContainers[MAX_SAMPLES];
    int64_t m_SampleStartTime[MAX_SAMPLES];
    int64_t m_SampleEndTime[MAX_SAMPLES];
    size_t  m_nCurSampleIdx;
    double  m_fSampleRate;
};

//////////////////////////////////////////////////////////////////////////
///


template<size_t MAX_SAMPLES, int64_t SAMPLE_DURATION_US>
CSampleCounter<MAX_SAMPLES, SAMPLE_DURATION_US>::CSampleCounter()
{
    this->reset();
}

template<size_t MAX_SAMPLES, int64_t SAMPLE_DURATION_US>
void CSampleCounter<MAX_SAMPLES, SAMPLE_DURATION_US>::reset()
{
    m_bActivity = false;
    m_nLastActivityTime = 0;

    m_fSampleRate = 0.0;

    m_nCurSampleIdx = 0;
    for (size_t idx=0; idx< MAX_SAMPLES; ++idx)
    {
        m_SampleContainers[idx] = 0;
        m_SampleStartTime[idx] = m_SampleEndTime[idx] = 0;
    }
}

template<size_t MAX_SAMPLES, int64_t SAMPLE_DURATION_US>
void CSampleCounter<MAX_SAMPLES, SAMPLE_DURATION_US>::AddSamples(size_t numBytes)
{
    int64_t now_time = av_gettime_relative();

    m_bActivity = true;
    m_nLastActivityTime = now_time;

    if ( m_SampleStartTime[m_nCurSampleIdx] == 0 )
    {
        m_SampleStartTime[m_nCurSampleIdx] = now_time;
        m_SampleEndTime[m_nCurSampleIdx] = now_time;
    }

    m_SampleContainers[m_nCurSampleIdx] += numBytes;

    if ( (now_time - m_SampleStartTime[m_nCurSampleIdx]) >= SAMPLE_DURATION_US)
    {
        m_SampleEndTime[m_nCurSampleIdx] = now_time;

        m_fSampleRate = this->calcSampleRate();

        m_nCurSampleIdx = (++m_nCurSampleIdx) % MAX_SAMPLES;

        m_SampleContainers[m_nCurSampleIdx] = 0;
        m_SampleStartTime[m_nCurSampleIdx] = now_time;
        m_SampleEndTime[m_nCurSampleIdx] = now_time;
    }
}

template<size_t MAX_SAMPLES, int64_t SAMPLE_DURATION_US>
double CSampleCounter<MAX_SAMPLES, SAMPLE_DURATION_US>::SampleRate()
{
    if ( m_bActivity )
    {
        int64_t now_time = av_gettime_relative();
        if ( now_time - m_nLastActivityTime > SAMPLE_DURATION_US)
        {
            m_bActivity = false;
            this->reset();
        }
    }
    return m_fSampleRate;
}

template<size_t MAX_SAMPLES, int64_t SAMPLE_DURATION_US>
double CSampleCounter<MAX_SAMPLES, SAMPLE_DURATION_US>::calcSampleRate()
{
    int64_t sum_samples = 0;
    int64_t sum_time = 0;

    for ( size_t idx=0; idx<MAX_SAMPLES; ++idx )
    {
        sum_samples += m_SampleContainers[idx];
        sum_time += ( m_SampleEndTime[idx] - m_SampleStartTime[idx] );
    }

    if ( sum_time <= 0 )
        return 0;

    return sum_samples * SAMPLE_DURATION_US / (double)sum_time;
}

//////////////////////////////////////////////////////////////////////////
///

typedef CSampleCounter<1>  CAVBitrateCounter;
typedef CSampleCounter<1>  CAVFPSCounter;
