#pragma once

#include <cstdint>
#include <cinttypes>
#include <mutex>

class CAVClock
{
public:
    double  Time() const; // unit: second

    void    Reset();
    void    Pause();
    void    Resume();

private:
    int64_t             m_nBase;
    int64_t             m_nStartTime;
    bool                m_bPaused;
    mutable std::mutex  m_mutex;
};
