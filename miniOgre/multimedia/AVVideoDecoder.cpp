#include "AVVideoDecoder.h"
#include "AVCommon.h"

CAVVideoDecoder::CAVVideoDecoder()
    : CAVDecoderBase()
{
    m_pSwsContext = NULL;
    m_nVideoRotation = 0;
}


void CAVVideoDecoder::SetRenderSize(int w, int h)
{
    m_nRenderWidth = w;
    m_nRenderHeight = h;
}

CAVRenderBase* CAVVideoDecoder::new_render(AVStream* pAVStream, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback)
{
    AV_ASSERT(pAVStream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO);
    AV_ASSERT(m_eAVType == AVMEDIA_TYPE_VIDEO);

    m_nVideoRotation = 0;
    AVDictionaryEntry *de = av_dict_get(pAVStream->metadata, "rotate", NULL, AV_DICT_IGNORE_SUFFIX);
    if (de)
        m_nVideoRotation = std::atoi(de->value) % 360;

    return new CAVVideoRender(4, pAVStream, pAVSyncTuner, callback);
}

int CAVVideoDecoder::decode(AVPacket* pkt)
{
    AV_ASSERT(m_pDecodedFrame);

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

        AVFrame dst_frame = { 0 };
        av_frame_unref(&dst_frame);
        if (convert_frame_copy(m_pDecodedFrame, &dst_frame))
        {
            dst_frame.opaque = (void*)(size_t)m_nVideoRotation;
            m_pAVRender->PushBack(dst_frame, true);
        }
    }
    return numFrames;
}

void CAVVideoDecoder::cleanup()
{
    if (m_pSwsContext)
    {
        sws_freeContext(m_pSwsContext);
        m_pSwsContext = NULL;
    }
}

bool CAVVideoDecoder::convert_frame_copy(AVFrame* src_frame, AVFrame* dst_frame)
{
    int src_width = src_frame->width;
    int src_height = src_frame->height;
    int dst_width = m_nRenderWidth;
    int dst_height = m_nRenderHeight;
    if (dst_width == 0 || dst_height == 0) {
        dst_width = src_width;
        dst_height = src_height;
    }

    if (src_frame->format == AV_PIX_FMT_BGRA && src_width == dst_width && src_height == dst_height)
    {
        av_frame_ref(dst_frame, src_frame);
        return true;
    }

    av_frame_copy_props(dst_frame, src_frame);

    dst_frame->format = AV_PIX_FMT_BGRA;
    dst_frame->width = dst_width;
    dst_frame->height = dst_height;
    if (av_frame_get_buffer(dst_frame, 0) != 0) {
        return false;
    }

    int dstX, dstY, dstW, dstH;
    if (src_width * dst_height >= dst_width * src_height)
    {
        dstW = dst_width;
        dstH = src_height * dstW / src_width;
        dstX = 0;
        dstY = (dst_height - dstH) / 2;
        if (dstY == 0) dstH = dst_height;
    }
    else
    {
        dstH = dst_height;
        dstW = src_width * dstH / src_height;
        dstY = 0;
        dstX = (dst_width - dstW) / 2;
        if (dstX == 0) dstW = dst_width;
    }

    uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };
    int linesize[AV_NUM_DATA_POINTERS] = { 0 };
    data[0] = dst_frame->data[0] + dst_frame->linesize[0] * dstY + dstX * 4;
    linesize[0] = dst_frame->linesize[0];

    m_pSwsContext = sws_getCachedContext(
        m_pSwsContext,
        src_width, src_height, (AVPixelFormat)src_frame->format,
        dstW, dstH, AV_PIX_FMT_BGRA,
        SWS_BICUBIC, NULL, NULL, NULL);
    if (!m_pSwsContext) {
        return false;
    }

    static const uint32_t kBlackLine[1024 * 8] = { 0xff000000 };
    if (dstX > 0 || dstY > 0) {
        for (int i = 0; i < dst_frame->height; ++i) {
            memcpy(dst_frame->data[0] + i * dst_frame->linesize[0], kBlackLine, dst_frame->linesize[0]);
        }
    }

    sws_scale(
        m_pSwsContext,
        src_frame->data, src_frame->linesize, 0, src_height,
        data, linesize);

    if(dstX > 0)
    {
        for (int y = 0; y < dst_frame->height; ++y) {
            uint8_t* line_start = dst_frame->data[0] + y * dst_frame->linesize[0];
            uint8_t* line_end = line_start + dst_frame->linesize[0];
            uint8_t* line_pixel_end = line_start + (dstX + dstW) * 4;
            memcpy(line_start, kBlackLine, 4 * dstX);
            memcpy(line_pixel_end, kBlackLine, line_end - line_pixel_end);
        }
    }

    return true;
}
