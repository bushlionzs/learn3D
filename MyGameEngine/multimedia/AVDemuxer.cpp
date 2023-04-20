#include "AVDemuxer.h"
#include "AVVideoDecoder.h"
#include "AVAudioDecoder.h"
#include "AVCommon.h"

#ifndef _WIN32
#define stricmp strcasecmp
#endif

constexpr size_t kMinCacheSize = 1024 * 512;
constexpr size_t kMaxCacheSize = 1024 * 1024 * 20;

CAVDemuxer::CAVDemuxer()
{
    m_nTotalPkts = m_nTotalPktSize = 0;

    m_nMinOrgTotalPktSize = m_nMinTotalPktSize = kMinCacheSize;
    m_nMaxOrgTotalPktSize = m_nMaxTotalPktSize = kMaxCacheSize;

    m_bFirstPop = true;
    m_bMinGuard = m_bMaxGuard = true;
    m_bEof = false;

    m_bFrozen = false;
    m_bCaching = false;
    m_bPushBlocking = false;

    m_pAVCacheCallBack = NULL;

    m_pAVFormatContext = NULL;
    m_bIsHLS = false;

    m_nVideoIdx = m_nAudioIdx = m_nSubTitleIdx = AVERROR_STREAM_NOT_FOUND;

    m_pVideoStream = m_pAudioStream = m_pSubtitleStream = NULL;
}

CAVDemuxer::~CAVDemuxer()
{
}

bool CAVDemuxer::Open(AVFormatContext* pAVFormatContext, IAVCacheCallBack* pAVCacheCallBack)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    int findErr = avformat_find_stream_info(pAVFormatContext, NULL);
    if ( findErr < 0 )
        return false;

    for (unsigned int i = 0; i < pAVFormatContext->nb_streams; ++i)
        pAVFormatContext->streams[i]->discard = AVDISCARD_ALL;

    m_nVideoIdx = av_find_best_stream(pAVFormatContext, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0 );
    m_nAudioIdx = av_find_best_stream(pAVFormatContext, AVMEDIA_TYPE_AUDIO, -1, m_nVideoIdx, NULL, 0);
    m_nSubTitleIdx = av_find_best_stream(pAVFormatContext, AVMEDIA_TYPE_SUBTITLE, -1, m_nAudioIdx>=0?m_nAudioIdx:m_nVideoIdx, NULL, 0);

    if ( m_nVideoIdx<0 && m_nAudioIdx<0 )
        return false;

    if ( m_nVideoIdx>=0 )   m_pVideoStream = pAVFormatContext->streams[m_nVideoIdx];
    if ( m_nAudioIdx>=0 )   m_pAudioStream = pAVFormatContext->streams[m_nAudioIdx];
    if ( m_nSubTitleIdx>=0 )m_pSubtitleStream = pAVFormatContext->streams[m_nSubTitleIdx];

    m_bIsHLS = false;
    m_pAVFormatContext = pAVFormatContext;
    m_pAVCacheCallBack = pAVCacheCallBack;
    if ( m_pAVFormatContext->iformat && m_pAVFormatContext->iformat->name && _stricmp(m_pAVFormatContext->iformat->name, "hls,applehttp")==0 )
        m_bIsHLS = true;

    if ( m_pVideoStream )
    {
        m_pVideoPktQueue.reset(new CAVPacketQueue);
    }

    if ( m_pAudioStream )
    {
        m_pAudioPktQueue.reset(new CAVPacketQueue);
    }

    size_t min_cache_size = std::max<size_t>(m_pAVFormatContext->bit_rate, kMinCacheSize);

    m_bMinGuard = m_bMaxGuard = true;
    m_bEof = false;
    m_bFrozen = false;
    m_bCaching = false;
    m_bPushBlocking = false;

    m_nTotalPkts = m_nTotalPktSize = 0;

    m_nMinOrgTotalPktSize = m_nMinTotalPktSize = min_cache_size;
    m_nMaxOrgTotalPktSize = m_nMaxTotalPktSize = (std::max)(m_nMinTotalPktSize*2, kMaxCacheSize);

    return true;
}

bool CAVDemuxer::Close()
{
    this->Freeze(true);
    this->Flush();

    std::unique_lock<std::mutex> lock(m_mutex);

    m_pVideoPktQueue.reset();
    m_pAudioPktQueue.reset();

    m_nVideoIdx = m_nAudioIdx = m_nSubTitleIdx = AVERROR_STREAM_NOT_FOUND;

    m_pVideoStream = m_pAudioStream = m_pSubtitleStream = NULL;

    m_nTotalPkts = m_nTotalPktSize = 0;

    m_nMinOrgTotalPktSize = m_nMinTotalPktSize = kMinCacheSize;
    m_nMaxOrgTotalPktSize = m_nMaxTotalPktSize = kMaxCacheSize;

    m_pAVFormatContext = NULL;
    m_bIsHLS = false;

    m_bMinGuard = m_bMaxGuard = false;
    if (m_bCaching)
    {
        m_bCaching = false;
        if (m_pAVCacheCallBack)
        {
            m_pAVCacheCallBack->OnCacheEnd();
        }
    }

    m_cv.notify_all();

    m_pAVCacheCallBack = NULL;

    return true;
}


void CAVDemuxer::CloseVideo()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_nVideoIdx = AVERROR_STREAM_NOT_FOUND;
    m_pVideoStream = nullptr;
    m_pVideoPktQueue.reset();
}


void CAVDemuxer::CloseAudio()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_nAudioIdx = AVERROR_STREAM_NOT_FOUND;
    m_pAudioStream = nullptr;
    m_pAudioPktQueue.reset();
}

void CAVDemuxer::Freeze(bool frozen)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    if ( frozen != m_bFrozen )
    {
        m_bFrozen = frozen;
        m_cv.notify_all();
    }
}

void CAVDemuxer::EnableMinGuard(bool b)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    if ( b != m_bMinGuard )
    {
        m_bMinGuard = b;
        if ( !m_bMinGuard && m_bCaching )
        {
            m_bCaching = false;
            if ( m_pAVCacheCallBack )
                m_pAVCacheCallBack->OnCacheEnd();
        }
        m_cv.notify_all();
    }
}

void CAVDemuxer::EnableMaxGuard(bool b)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    if ( b != m_bMaxGuard )
    {
        m_bMaxGuard = b;
        m_cv.notify_all();
    }
}

int CAVDemuxer::PushPkt(AVPacket& pkt, bool block)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    CAVPacketQueue* target_queue = NULL;

    if ( pkt.stream_index == m_nVideoIdx )
        target_queue = m_pVideoPktQueue.get();
    else if (pkt.stream_index == m_nAudioIdx)
        target_queue = m_pAudioPktQueue.get();

    if ( !target_queue )
    {
        UnrefAVPacket(&pkt);
        return -1;
    }

    while ( true )
    {
        if ( m_bFrozen )
        {
            UnrefAVPacket(&pkt);
            return -1;
        }

        if ( m_bMaxGuard && m_nTotalPktSize+pkt.size > m_nMaxTotalPktSize && !m_bCaching )
        {
            if ( !block )
                return 0;

            m_bPushBlocking = true;
            m_cv.wait(lock);
            continue;
        }

        m_bPushBlocking = false;
        int ret = target_queue->PushBack(pkt);
        AV_ASSERT( ret > 0 );

        m_oAVBitrateCounterIn.AddSamples(pkt.size);

        ++m_nTotalPkts;
        m_nTotalPktSize += pkt.size;
        if ( m_nTotalPktSize > (m_bCaching ? m_nMinTotalPktSize : 0)
          && (!m_pVideoPktQueue||m_pVideoPktQueue->NumPkts()>0)
          && (!m_pAudioPktQueue||m_pAudioPktQueue->NumPkts()>0) )
        {
            if (m_bCaching)
            {
                AV_ASSERT(m_bMinGuard);
                m_bCaching = false;
                if ( m_pAVCacheCallBack )
                    m_pAVCacheCallBack->OnCacheEnd();
            }

            m_cv.notify_all();
        }

        return ret;
    }
}

int CAVDemuxer::PopPkt(AVPacket& pkt, AVMediaType type, bool block)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    CAVPacketQueue* target_queue = NULL;

    switch ( type )
    {
    case AVMEDIA_TYPE_VIDEO:
        target_queue = m_pVideoPktQueue.get();
        break;
    case AVMEDIA_TYPE_AUDIO:
        target_queue = m_pAudioPktQueue.get();
        break;
    }

    if ( !target_queue )
        return -1;

    while ( true )
    {
        if ( m_bFrozen )
            return -1;

        if ( (m_nTotalPktSize<=0 || target_queue->NumPkts()<1) && !m_bCaching && m_bMinGuard && !m_bEof && !m_bFirstPop)
        {
            m_nMinTotalPktSize = (std::max)((size_t)m_oAVBitrateCounterOut.SampleRate(), m_nMinOrgTotalPktSize);
            m_nMaxTotalPktSize = (std::max)(m_nMinTotalPktSize*2, m_nMaxOrgTotalPktSize);

            m_bCaching = true;
            if ( m_pAVCacheCallBack )
                m_pAVCacheCallBack->OnCacheBegin();
        }

        size_t min_reserve_size = m_bMinGuard&&m_bCaching&&!m_bFirstPop ? m_nMinTotalPktSize : 0;

        if ( m_nTotalPktSize <= min_reserve_size
          || target_queue->NumPkts() < 1
          || m_bCaching )
        {
            if ( !block )
                return 0;

            m_cv.wait(lock);
            continue;
        }

        m_bFirstPop = false;
        int ret = target_queue->PopFront(pkt);
        AV_ASSERT( ret > 0 );

        m_oAVBitrateCounterOut.AddSamples(pkt.size);

        --m_nTotalPkts;
        m_nTotalPktSize -= pkt.size;

        if (m_bPushBlocking && m_nTotalPktSize < m_nMaxTotalPktSize)
            m_cv.notify_all();

        return ret;
    }
}

void CAVDemuxer::Flush()
{
    std::unique_lock<std::mutex> lock(m_mutex);

    m_bEof = false;
    m_nTotalPkts = m_nTotalPktSize = 0;

    if ( m_pVideoPktQueue )
    {
        m_pVideoPktQueue->Flush();
        m_nTotalPkts += m_pVideoPktQueue->NumPkts();
        m_nTotalPktSize += m_pVideoPktQueue->TotalPktSize();
    }

    if ( m_pAudioPktQueue )
    {
        m_pAudioPktQueue->Flush();
        m_nTotalPkts += m_pAudioPktQueue->NumPkts();
        m_nTotalPktSize += m_pAudioPktQueue->TotalPktSize();
    }
    m_cv.notify_all();
}

void CAVDemuxer::SetEof(bool eof)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_bEof == eof)
        return;

    m_bEof = eof;
    if (m_bEof)
    {
        if ( m_pVideoPktQueue )
        {
            ++m_nTotalPkts;
            m_nTotalPktSize += gEofPkt.size;
            m_pVideoPktQueue->PushBack(gEofPkt);
        }
        if ( m_pAudioPktQueue )
        {
            ++m_nTotalPkts;
            m_nTotalPktSize += gEofPkt.size;
            m_pAudioPktQueue->PushBack(gEofPkt);
        }

        if ( m_bCaching )
        {
            m_bCaching = false;
            if ( m_pAVCacheCallBack )
                m_pAVCacheCallBack->OnCacheEnd();

            m_cv.notify_all();
        }
    }
}

size_t CAVDemuxer::NumTotalPkts()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_nTotalPkts;
}

size_t CAVDemuxer::NumVideoPkts()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_pVideoPktQueue ? m_pVideoPktQueue->NumPkts() : 0;
}

size_t CAVDemuxer::NumAudioPkts()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_pAudioPktQueue ? m_pAudioPktQueue->NumPkts() : 0;
}

size_t CAVDemuxer::TotalSize()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_nTotalPktSize;
}

size_t CAVDemuxer::VideoSize()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_pVideoPktQueue ? m_pVideoPktQueue->TotalPktSize() : 0;
}

size_t CAVDemuxer::AudioSize()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_pAudioPktQueue ? m_pAudioPktQueue->TotalPktSize() : 0;
}

AVStream* CAVDemuxer::GetVideoStream()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_pVideoStream;
}

AVStream* CAVDemuxer::GetAudioStream()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_pAudioStream;
}

double CAVDemuxer::GetBPSIn()
{
    return m_oAVBitrateCounterIn.SampleRate()/1024.0;
}

double CAVDemuxer::GetBPSOut()
{
    return m_oAVBitrateCounterOut.SampleRate()/1024.0;
}

bool CAVDemuxer::IsHLS()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_bIsHLS;
}
