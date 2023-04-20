#pragma once

#include "FFmpegLib.h"

extern AVPacket    gFlushPkt;
extern AVPacket    gEofPkt;

bool IsFlushPkt(AVPacket* pkt);
bool IsEofPkt(AVPacket* pkt);
void UnrefAVPacket(AVPacket* pkt);

class CAVPacketQueue
{
public:
    CAVPacketQueue();
    ~CAVPacketQueue();

public:
    int     PushBack(AVPacket& pkt);
    int     PopFront(AVPacket& pkt);
    void    Flush();

    size_t  NumPkts();
    size_t  TotalPktSize();

private:
    struct AVPacketList {
        AVPacket pkt;
        struct AVPacketList *next;
    };

    AVPacketList*   m_pFirstPkt;
    AVPacketList*   m_pLastPkt;
    size_t          m_numPkts;
    size_t          m_totalSize;    // sum of all pkt size.
};
