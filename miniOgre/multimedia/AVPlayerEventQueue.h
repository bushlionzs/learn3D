#pragma once

#include <deque>
#include <mutex>

enum
{
    AVPlayerEvent_Volume = 0,
    AVPlayerEvent_Pause = 10,
    AVPlayerEvent_Resume = 11,
    AVPlayerEvent_Seek = 20,
    AVPlayerEvent_Stop = 30,
};

struct AVPlayerEvent
{
    int     eventType;
    double  value;
};

class CAVPlayerEventQueue
{
public:
    void    PushEvent(AVPlayerEvent& event);
    bool    PopEvent(AVPlayerEvent& event);

private:
    std::deque<AVPlayerEvent>   m_eventQueue;
    std::mutex                  m_mutex;
};
