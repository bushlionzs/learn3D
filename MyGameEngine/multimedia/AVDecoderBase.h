#pragma once

#include "AVDemuxer.h"
#include "AVRenderBase.h"


class CAVDecoderBase
{
public:
    CAVDecoderBase();
    virtual ~CAVDecoderBase();

public:
    bool    Run(AVStream* pAVStream, CAVDemuxer* pAVDemuxer, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback, bool hwaccel);
    void    Stop();     // must called before the decoder object destroyed.
    void    Pause();
    void    Resume();

    void    OnSeek();
    void    OnCacheBegin();
    void    OnCacheEnd();

    bool    IsFinished();


private:
    int     decode_thread(AVStream* pAVStream, CAVDemuxer* pAVDemuxer, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback, bool hwaccel, std::promise<void>& barrier); // decode thread executor
    bool    open(AVStream* pAVStream, CAVDemuxer* pAVDemuxer, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback, bool hwaccel);
    bool    close();

private:
    virtual CAVRenderBase*  new_render(AVStream* pAVStream, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback) = 0;
    virtual int             decode(AVPacket* pkt) = 0;
    virtual void            cleanup() = 0;

protected:
    IAVPlayCallback*                    m_pAVPlayCallback;
    AVStream*                           m_pAVStream;
    AVCodecContext*                     m_pCodecContext;
    CAVDemuxer*                         m_pAVDemuxer;
    AVFrame*                            m_pDecodedFrame;
    AVMediaType                         m_eAVType;

    std::unique_ptr<CAVRenderBase>      m_pAVRender;

    volatile bool                       m_bStop;
    volatile bool                       m_bRunning;
    volatile bool                       m_bEof;

private:
    std::unique_ptr<std::thread>        m_thrdDecode;

    volatile bool                       m_bPaused;

    std::mutex                          m_mutexDecoder;
    std::condition_variable             m_cvDecoder;

    std::mutex                          m_mutexPause;
    std::condition_variable             m_cvPause;
};
