#include "AVPlayerEventQueue.h"

namespace
{

inline
bool is_same_event(AVPlayerEvent e1, AVPlayerEvent e2)
{
    return (e1.eventType/10 == e2.eventType/10);
}

}

void CAVPlayerEventQueue::PushEvent(AVPlayerEvent& event)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_eventQueue.push_back(event);
}

bool CAVPlayerEventQueue::PopEvent(AVPlayerEvent& event)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    if ( m_eventQueue.empty() )
        return false;

    AVPlayerEvent fe1 = m_eventQueue.front();
    m_eventQueue.pop_front();
    while ( !m_eventQueue.empty() )
    {
        AVPlayerEvent fe2 = m_eventQueue.front();
        if ( !is_same_event(fe1, fe2) )
            break;
        else
        {
            fe1 = fe2;
            m_eventQueue.pop_front();
        }
    }

    event = fe1;
    return true;
}
