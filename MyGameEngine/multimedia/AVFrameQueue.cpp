#include "AVFrameQueue.h"
#include "AVCommon.h"

AVFrame gFlushFrm;
AVFrame gEofFrm;

bool IsFlushFrm(AVFrame* frame)
{
    AV_ASSERT(frame);
    return (frame==&gFlushFrm || frame->data[0]==gFlushFrm.data[0]);
}

bool IsEofFrm(AVFrame* frame)
{
    AV_ASSERT(frame);
    return (frame==&gEofFrm || frame->data[0]==gEofFrm.data[0]);
}

void UnrefFrm(AVFrame* frame)
{
    if (!IsFlushFrm(frame) && !IsEofFrm(frame))
    {
        av_frame_unref(frame);
    }
}


void MoveFrmRef(AVFrame* dst, AVFrame* src)
{
    if (IsFlushFrm(src) || IsEofFrm(src))
    {
        *dst = *src;
    }
    else
    {
        av_frame_move_ref(dst, src);
    }
}

CAVFrameQueue::CAVFrameQueue(size_t numMaxFrames)
{
    m_pFirstFrame = m_pLastFrame = NULL;
    m_numFrames = 0;
    m_numMaxFrames = numMaxFrames;
    m_bFrozen = false;
}

CAVFrameQueue::~CAVFrameQueue()
{
    this->Flush();
}

void CAVFrameQueue::Freeze(bool frozen)
{
    std::unique_lock<std::mutex> lock(m_mutexQueue);
    if ( frozen != m_bFrozen )
    {
        m_bFrozen = frozen;
        if ( m_bFrozen )
            m_cvQueue.notify_all();
    }
}

int CAVFrameQueue::PushBackInternal(AVFrame& frame, bool block, std::unique_lock<std::mutex>& lock)
{
    int ret;

    while (true)
    {
        if ( m_bFrozen )
        {
            ret = -1;
            break;
        }

        if ( m_numFrames >= m_numMaxFrames )
        {
            if ( !block )
            {
                ret = 0;
                break;
            }
            else
            {
                m_cvQueue.wait(lock);
                continue;
            }
        }

        AVFrameList* frameNode = (AVFrameList*)av_malloc(sizeof(AVFrameList));
        if ( !frameNode )
        {
            ret = -1;
            break;
        }

        MoveFrmRef(&frameNode->frame, &frame);
        frameNode->next = NULL;

        if ( m_pLastFrame )
            m_pLastFrame->next = frameNode;
        else
        {
            AV_ASSERT(m_numFrames==0);
            AV_ASSERT(!m_pFirstFrame);

            m_pFirstFrame = frameNode;
        }

        m_pLastFrame = frameNode;
        ++m_numFrames;

        if ( m_numFrames == 1 )
            m_cvQueue.notify_all();

        ret = 1;
        break;
    }

    return ret;
}

int CAVFrameQueue::PushBack(AVFrame& frame, bool block)
{
    int ret;

    {
        std::unique_lock<std::mutex> lock(m_mutexQueue);
        ret = PushBackInternal(frame, block, lock);
    }

    if (ret < 0)
        UnrefFrm(&frame);

    return ret;
}


int CAVFrameQueue::PopFront(AVFrame& frame, bool block)
{
    AVFrameList* frameNode;
    int ret;

    std::unique_lock<std::mutex> lock(m_mutexQueue);

    while ( true )
    {
        if ( m_bFrozen )
        {
            ret = -1;
            break;
        }

        frameNode = m_pFirstFrame;
        if ( frameNode )
        {
            m_pFirstFrame = frameNode->next;
            if ( !m_pFirstFrame )
                m_pLastFrame = NULL;
            --m_numFrames;

            if ( m_numFrames+1 == m_numMaxFrames )
                m_cvQueue.notify_all();

            av_frame_move_ref(&frame, &frameNode->frame);
            av_free(frameNode);
            frameNode = NULL;
            ret = 1;
            break;
        }
        else
        {
            if ( !block )
            {
                ret = 0;
                break;
            }
            else
            {
                m_cvQueue.wait(lock);
                continue;
            }
        }
    }

    return ret;
}

void CAVFrameQueue::Flush()
{
    std::unique_lock<std::mutex> lock(m_mutexQueue);

    size_t numFrames = m_numFrames;

    AVFrameList *frameNode, *frameNodeNext;
    for ( frameNode=m_pFirstFrame; frameNode!=NULL; frameNode=frameNodeNext )
    {
        frameNodeNext = frameNode->next;
        UnrefFrm(&frameNode->frame);
        av_free(frameNode);
    }
    m_pFirstFrame = m_pLastFrame = NULL;
    m_numFrames = 0;

    if ( numFrames >= m_numMaxFrames )
        m_cvQueue.notify_all();

    this->PushBackInternal(gFlushFrm, true, lock);
}

size_t CAVFrameQueue::NumFrames()
{
    std::unique_lock<std::mutex> lock(m_mutexQueue);
    return m_numFrames;
}
