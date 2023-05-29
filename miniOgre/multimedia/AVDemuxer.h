#pragma once

#include <cstdint>
#include <cinttypes>
#include <mutex>

#include "AVPacketQueue.h"
#include "SampleCounter.h"
#include "AVPlayCallback.h"

class CAVVideoDecoder;
class CAVAudioDecoder;

class CAVDemuxer
{
public:
    CAVDemuxer();
    ~CAVDemuxer();

public:
    bool        Open(AVFormatContext* pAVFormatContext, IAVCacheCallBack* pAVCacheCallBack);
    bool        Close();

    void        CloseVideo();
    void        CloseAudio();

public:
    void        Freeze(bool frozen);    // default unfreeze.
    void        EnableMinGuard(bool b);  //default enable
    void        EnableMaxGuard(bool b);  //default enable

    int         PushPkt(AVPacket& pkt, bool block);
    int         PopPkt(AVPacket& pkt, AVMediaType type, bool block);

    void        Flush();
    void        SetEof(bool eof);

    size_t      NumTotalPkts();
    size_t      NumVideoPkts();
    size_t      NumAudioPkts();

    size_t      TotalSize();
    size_t      VideoSize();
    size_t      AudioSize();

    AVStream*   GetVideoStream();
    AVStream*   GetAudioStream();

    double      GetBPSIn();     // unit: kb/s
    double      GetBPSOut();    // unit: kb/s

    bool        IsHLS();

private:
    std::unique_ptr<CAVPacketQueue>     m_pVideoPktQueue;
    std::unique_ptr<CAVPacketQueue>     m_pAudioPktQueue;

    size_t                              m_nTotalPkts;
    size_t                              m_nTotalPktSize;

    size_t                              m_nMinOrgTotalPktSize;
    size_t                              m_nMaxOrgTotalPktSize;
    size_t                              m_nMinTotalPktSize;
    size_t                              m_nMaxTotalPktSize;

    bool                                m_bFirstPop;
    bool                                m_bMinGuard;
    bool                                m_bMaxGuard;
    bool                                m_bEof;

    // enable/disable Push/Pop, default false.
    bool                                m_bFrozen;

    bool                                m_bPushBlocking;

    // if min guard enabled, the queue must cache packets until queue size retched minNumPkts before it can pop. become true when pkt_queue comes to empty.
    bool                                m_bCaching;

    std::mutex                          m_mutex;
    std::condition_variable             m_cv;

    IAVCacheCallBack*                   m_pAVCacheCallBack;

    AVFormatContext*                    m_pAVFormatContext;
    bool                                m_bIsHLS;

    int                                 m_nVideoIdx;
    int                                 m_nAudioIdx;
    int                                 m_nSubTitleIdx;

    AVStream*                           m_pVideoStream;
    AVStream*                           m_pAudioStream;
    AVStream*                           m_pSubtitleStream;

    CAVBitrateCounter                   m_oAVBitrateCounterIn;
    CAVBitrateCounter                   m_oAVBitrateCounterOut;
};
