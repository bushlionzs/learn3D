#include "AVSubTitleDecoder.h"
#include "AVCommon.h"

CAVSubTitleDecoder::CAVSubTitleDecoder()
: CAVDecoderBase()
{
}

CAVRenderBase* CAVSubTitleDecoder::new_render(AVStream* pAVStream, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback)
{
    return new CAVSubTitleRender(4, pAVStream, pAVSyncTuner, callback);
}

int CAVSubTitleDecoder::decode(AVPacket* pkt)
{
    return -1;
}

void CAVSubTitleDecoder::cleanup()
{

}
