#include "AVDecoderBase.h"

#include <thread>
#include <chrono>

CAVDecoderBase::CAVDecoderBase()
{
    m_pAVPlayCallback = NULL;
    m_pAVStream = NULL;
    m_pAVDemuxer = NULL;
    m_pDecodedFrame = NULL;

    m_eAVType = AVMEDIA_TYPE_UNKNOWN;

    m_bStop = true;
    m_bRunning = false;
    m_bEof = true;
    m_bPaused = false;
}

CAVDecoderBase::~CAVDecoderBase()
{
}

bool CAVDecoderBase::Run(AVStream* pAVStream, CAVDemuxer* pAVDemuxer, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback, bool hwaccel)
{
    this->Stop();

    std::unique_lock<std::mutex> lock(m_mutexDecoder);

    m_bStop = false;

    std::promise<void> barrier;
    m_thrdDecode.reset(new std::thread(&CAVDecoderBase::decode_thread, this, pAVStream, pAVDemuxer, pAVSyncTuner, callback, hwaccel, std::ref(barrier)));
    barrier.get_future().wait();

    return m_bRunning;
}

void CAVDecoderBase::Stop()
{
    std::unique_lock<std::mutex> lock(m_mutexDecoder);

    if ( m_pAVRender )
        m_pAVRender->Stop();

    m_bStop = true;
    m_cvPause.notify_all();
    if ( m_thrdDecode && m_thrdDecode->joinable() )
        m_thrdDecode->join();
}

void CAVDecoderBase::Pause()
{
    std::unique_lock<std::mutex> lock(m_mutexPause);

    m_bPaused = true;
    if ( m_pAVRender )
        m_pAVRender->Pause();
}

void CAVDecoderBase::Resume()
{
    std::unique_lock<std::mutex> lock(m_mutexPause);

    m_bPaused = false;
    if ( m_pAVRender )
        m_pAVRender->Resume();

    m_cvPause.notify_all();
}

void CAVDecoderBase::OnSeek()
{
    m_bEof = false;
    m_pAVRender->Freeze(true);      // decoder_thread will unblock at FrameQueue::PushBack
}

void CAVDecoderBase::OnCacheBegin()
{
    m_pAVRender->OnCacheBegin();
}

void CAVDecoderBase::OnCacheEnd()
{
    m_pAVRender->OnCacheEnd();
}

bool CAVDecoderBase::IsFinished()
{
    return m_bEof && (!m_pAVRender || (m_pAVRender->IsFinished()));
}

int CAVDecoderBase::decode_thread(AVStream* pAVStream, CAVDemuxer* pAVDemuxer, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback, bool hwaccel, std::promise<void>& barrier)
{
    int ret = 0;

    if (!this->open(pAVStream, pAVDemuxer, pAVSyncTuner, callback, hwaccel))
    {
        barrier.set_value();
        return -1;
    }

    m_bRunning = true;
    m_bEof = false;
    barrier.set_value();

    AVPacket pkt = { 0 };
    while (!m_bStop)
    {
        {
            std::unique_lock<std::mutex> lock(m_mutexPause);
            while (m_bPaused && !m_bStop) m_cvPause.wait(lock);
        }

        if (m_pAVDemuxer->PopPkt(pkt, m_eAVType, true) <= 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        if ( IsFlushPkt(&pkt) )
        {
            avcodec_flush_buffers(m_pCodecContext);
            m_pAVRender->Flush();
            m_pAVRender->Freeze(false);
            m_pAVRender->Flush();
            m_pAVRender->AbortRender();
            continue;
        }

        this->decode(&pkt);

        UnrefAVPacket(&pkt);
    }
    m_bRunning = false;
    m_bStop = true;
    this->close();
    this->cleanup();

    return ret;
}

bool CAVDecoderBase::open(AVStream* pAVStream, CAVDemuxer* pAVDemuxer, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback, bool hwaccel)
{
    m_pAVPlayCallback = callback;

    m_pCodecContext = avcodec_alloc_context3(NULL);
    if (avcodec_parameters_to_context(m_pCodecContext, pAVStream->codecpar) < 0)
        return false;

    const AVCodec* codec = avcodec_find_decoder(m_pCodecContext->codec_id);
    if (!codec) {
        avcodec_free_context(&m_pCodecContext);
        return false;
    }

    m_pCodecContext->pkt_timebase = pAVStream->time_base;
    m_pCodecContext->codec_id = codec->id;
    m_pCodecContext->workaround_bugs = FF_BUG_AUTODETECT;
    m_pCodecContext->lowres = 0;
    m_pCodecContext->idct_algo = FF_IDCT_AUTO;
    m_pCodecContext->skip_frame = AVDISCARD_DEFAULT;
    m_pCodecContext->skip_idct = AVDISCARD_DEFAULT;
    m_pCodecContext->skip_loop_filter = AVDISCARD_DEFAULT;
    m_pCodecContext->error_concealment = 3;

    AVDictionary *opts = NULL;
    av_dict_set(&opts, "threads", "auto", 0);
    av_dict_set(&opts, "refcounted_frames", "1", 0);
    if (avcodec_open2(m_pCodecContext, codec, &opts) < 0)
    {
        av_dict_free(&opts);
        avcodec_free_context(&m_pCodecContext);
        return false;
    }
    av_dict_free(&opts);

    m_eAVType = m_pCodecContext->codec_type;

    pAVStream->discard = AVDISCARD_DEFAULT;
    m_pAVStream = pAVStream;
    m_pAVDemuxer = pAVDemuxer;
    m_pDecodedFrame = av_frame_alloc();

    m_pAVRender.reset(new_render(pAVStream, pAVSyncTuner, callback));
    if ( !m_pAVRender->Run() )
    {
        this->close();
        return false;
    }

    return true;
}

bool CAVDecoderBase::close()
{
    m_pAVRender->Stop();
    m_pAVRender.reset();

    avcodec_flush_buffers(m_pCodecContext);

    av_frame_free(&m_pDecodedFrame);
    m_pDecodedFrame = NULL;

    m_pAVDemuxer = NULL;

    m_pAVStream->discard = AVDISCARD_ALL;
    avcodec_close(m_pCodecContext);
    avcodec_free_context(&m_pCodecContext);
    m_pAVStream = NULL;
    m_pAVPlayCallback = NULL;

    return true;
}

