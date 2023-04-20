#include "AVAudioDecoder.h"
#include "AVCommon.h"

CAVAudioDecoder::CAVAudioDecoder()
    : CAVDecoderBase()
{
    m_pSwrContext = NULL;

#ifdef DEBUG_AUDIO_DECODE
    m_fCvtOutput = fopen("audio_cvt.bin", "wb");
    m_fOrgOutput = fopen("audio_org.bin", "wb");
#endif
}

double CAVAudioDecoder::GetVolume()
{
    if (!m_bRunning)
        return 0;

    return ((CAVAudioRender*)m_pAVRender.get())->GetVolume();
}

void CAVAudioDecoder::SetVolume(double vol)
{
    if (m_bRunning)
        ((CAVAudioRender*)m_pAVRender.get())->SetVolume(vol);
}

CAVRenderBase* CAVAudioDecoder::new_render(AVStream* pAVStream, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback)
{
    return new CAVAudioRender(4, pAVStream, pAVSyncTuner, callback);
}

int CAVAudioDecoder::decode(AVPacket* pkt)
{
    assert(m_pDecodedFrame);

    AVPacket decodingPkt = *pkt;
    int numFrames = 0;

    int send_err = avcodec_send_packet(m_pCodecContext, &decodingPkt);
    AV_ASSERT(send_err != AVERROR(EAGAIN));

    while (!m_bStop)
    {
        int recv_err = avcodec_receive_frame(m_pCodecContext, m_pDecodedFrame);
        if (recv_err < 0)
        {
            m_bEof = (recv_err == AVERROR_EOF);
            if (m_bEof) {
                m_pAVRender->PushBack(gEofFrm, true);
            }
            return numFrames;
        }
        ++numFrames;

#ifdef DEBUG_AUDIO_DECODE
        fwrite(m_pDecodedFrame->data[0], m_pDecodedFrame->linesize[0], 1, m_fOrgOutput);
        fflush(m_fOrgOutput);
#endif

        AVFrame dst_frame = { 0 };
        av_frame_unref(&dst_frame);
        if (convert_frame_copy(m_pDecodedFrame, &dst_frame))
        {
#ifdef DEBUG_AUDIO_DECODE
            fwrite(dst_frame.data[0], dst_frame.linesize[0], 1, m_fCvtOutput);
            fflush(m_fCvtOutput);
#endif
            m_pAVRender->PushBack(dst_frame, true);
        }
    }
    return numFrames;
}

void CAVAudioDecoder::cleanup()
{
    if (m_pSwrContext)
    {
        swr_free(&m_pSwrContext);
        m_pSwrContext = NULL;
    }
#ifdef DEBUG_AUDIO_DECODE
    fclose(m_fCvtOutput); m_fCvtOutput = NULL;
    fclose(m_fOrgOutput); m_fOrgOutput = NULL;
#endif
}

bool CAVAudioDecoder::convert_frame_copy(AVFrame* src_frame, AVFrame* dst_frame)
{
    int dec_channel_layout =
        (src_frame->channel_layout && src_frame->channels == av_get_channel_layout_nb_channels(src_frame->channel_layout)) ?
        src_frame->channel_layout : av_get_default_channel_layout(src_frame->channels);

    AVSampleFormat  src_format = (AVSampleFormat)src_frame->format;
    int             src_channels = (int)src_frame->channels;
    int             src_channel_layout = dec_channel_layout;
    int             src_sample_rate = src_frame->sample_rate;
    int             src_nb_samples = src_frame->nb_samples;
    int             src_bps = av_get_bytes_per_sample(src_format);

    AVSampleFormat  dst_format = AV_SAMPLE_FMT_S16;
    int             dst_channels = 2;
    int             dst_channel_layout = (int)av_get_default_channel_layout(dst_channels);
    int             dst_sample_rate = 44100;
    int             dst_nb_samples = src_nb_samples*dst_sample_rate/src_sample_rate;
    int             dst_bps = av_get_bytes_per_sample(dst_format);

    if (src_format == dst_format
        && src_channel_layout == dst_channel_layout
        && src_sample_rate == dst_sample_rate)
    {
        av_frame_copy(dst_frame, src_frame);
        return true;
    }

    av_frame_copy_props(dst_frame, src_frame);

    dst_frame->format = dst_format;
    dst_frame->sample_rate = dst_sample_rate;
    dst_frame->channels = dst_channels;
    dst_frame->channel_layout = dst_channel_layout;
    dst_frame->nb_samples = dst_nb_samples+256;
    if (av_frame_get_buffer(dst_frame, 0) != 0) {
        return false;
    }

    if (!m_pSwrContext)
    {
        m_pSwrContext = swr_alloc_set_opts(NULL,
            dst_channel_layout, dst_format, dst_sample_rate,
            src_channel_layout, src_format, src_sample_rate,
            0, NULL);

        if (!m_pSwrContext)
        {
            return false;
        }

        if (swr_init(m_pSwrContext) < 0)
        {
            return false;
        }
    }


    //if (dst_nb_samples != src_nb_samples)
    //{
    //    if (swr_set_compensation(m_pSwrContext,
    //        (dst_nb_samples - src_nb_samples) * dst_sample_rate / src_sample_rate,
    //        dst_nb_samples * dst_sample_rate / src_sample_rate) < 0)
    //    {
    //        return false;
    //    }
    //}

    int nb_samples_converted;
    if ((nb_samples_converted = swr_convert(m_pSwrContext, dst_frame->data, dst_frame->nb_samples, (const uint8_t**)src_frame->extended_data, src_nb_samples)) < 0)
    {
        return false;
    }
    dst_frame->nb_samples = nb_samples_converted;
    dst_frame->linesize[0] = nb_samples_converted * dst_channels * dst_bps;

    return true;

}
