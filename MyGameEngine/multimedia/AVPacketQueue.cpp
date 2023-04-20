#include "AVPacketQueue.h"
#include "AVCommon.h"

// avoid decode operation in cross thread
AVPacket    gFlushPkt;
AVPacket    gEofPkt;

bool IsFlushPkt(AVPacket* pkt)
{
    AV_ASSERT(pkt);
    return pkt == &gFlushPkt || pkt->data==gFlushPkt.data;
}

bool IsEofPkt(AVPacket* pkt)
{
    AV_ASSERT(pkt);
    return pkt == &gEofPkt || pkt->data==gEofPkt.data;
}

void UnrefAVPacket(AVPacket* pkt)
{
    AV_ASSERT(pkt);
    if ( !IsFlushPkt(pkt) && !IsEofPkt(pkt) )
    {
        av_packet_unref(pkt);
    }
}

CAVPacketQueue::CAVPacketQueue()
{
    m_pFirstPkt = m_pLastPkt = NULL;
    m_numPkts = m_totalSize = 0;
}

CAVPacketQueue::~CAVPacketQueue()
{
    this->Flush();
}

int CAVPacketQueue::PushBack(AVPacket& pkt)
{
    AVPacketList* pktNode = (AVPacketList*)av_malloc(sizeof(AVPacketList));
    if ( !pktNode )
    {
        UnrefAVPacket(&pkt);
        return -1;
    }

    pktNode->pkt = pkt;
    pktNode->next = NULL;

    if ( m_pLastPkt )
        m_pLastPkt->next = pktNode;
    else
    {
        AV_ASSERT(m_numPkts==0);
        AV_ASSERT(!m_pFirstPkt);

        m_pFirstPkt = pktNode;
    }

    m_pLastPkt = pktNode;
    ++m_numPkts;
    m_totalSize += pkt.size;

    return 1;
}


int CAVPacketQueue::PopFront( AVPacket& pkt )
{
    if ( !m_pFirstPkt )
        return -1;

    AVPacketList* pktNode = m_pFirstPkt;

    m_pFirstPkt = pktNode->next;
    if ( !m_pFirstPkt )
        m_pLastPkt = NULL;

    pkt = pktNode->pkt;

    --m_numPkts;
    m_totalSize -= pkt.size;

    av_free(pktNode);

    return 1;
}

void CAVPacketQueue::Flush()
{
    AVPacketList *pktNode, *pktNodeNext;
    for ( pktNode=m_pFirstPkt; pktNode!=NULL; pktNode=pktNodeNext )
    {
        pktNodeNext = pktNode->next;
        UnrefAVPacket(&pktNode->pkt);
        av_free(pktNode);
    }
    m_pFirstPkt = m_pLastPkt = NULL;
    m_numPkts = 0;
    m_totalSize = 0;

    this->PushBack(gFlushPkt);
}

size_t CAVPacketQueue::NumPkts()
{
    return m_numPkts;
}

size_t CAVPacketQueue::TotalPktSize()
{
    return m_totalSize;
}
