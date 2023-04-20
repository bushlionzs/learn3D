#include "AVSubTitleRender.h"
#include "AVSyncTuner.h"
#include "AVCommon.h"

CAVSubTitleRender::CAVSubTitleRender(size_t numMaxFrames, AVStream* pAVStream, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback)
: CAVRenderBase(numMaxFrames, pAVStream, pAVSyncTuner, callback)
{
}

bool CAVSubTitleRender::open()
{
    return true;
}

bool CAVSubTitleRender::close()
{
    return true;
}

int CAVSubTitleRender::render_frame(AVFrame& frame)
{
    return 1;
}
