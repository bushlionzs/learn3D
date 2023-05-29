#pragma once

#include <cstdint>
#include <cinttypes>
#include <mutex>

#include "FFmpegLib.h"

extern AVFrame gFlushFrm;
extern AVFrame gEofFrm;

bool IsFlushFrm(AVFrame* frame);
bool IsEofFrm(AVFrame* frame);
void UnrefFrm(AVFrame* frame);
void MoveFrmRef(AVFrame* dst, AVFrame* src);

class CAVFrameQueue
{
public:
    CAVFrameQueue(size_t numMaxFrames);
    ~CAVFrameQueue();

public:
    void    Freeze(bool frozen);
    int     PushBack(AVFrame& frame, bool block);
    int     PopFront(AVFrame& frame, bool block);
    void    Flush();

    size_t  NumFrames();

private:
    int     PushBackInternal(AVFrame& frame, bool block, std::unique_lock<std::mutex>& lock);

private:
    struct AVFrameList
    {
        AVFrame         frame;
        AVFrameList*    next;
    };

    AVFrameList*    m_pFirstFrame;
    AVFrameList*    m_pLastFrame;
    size_t          m_numFrames;
    size_t          m_numMaxFrames; //
    bool            m_bFrozen; // enable/disable PushBack/PopFront

    std::mutex      m_mutexQueue;
    std::condition_variable   m_cvQueue;
};
