#pragma once

#include <cstdint>
#include <cinttypes>
#include <cstdlib>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <libavdevice/avdevice.h>
#include <libavcodec/avcodec.h>
#include <libavcodec/avfft.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include <libavutil/avutil.h>
#include <libavutil/avstring.h>
#include <libavutil/mathematics.h>
#include <libavutil/pixdesc.h>
#include <libavutil/imgutils.h>
#include <libavutil/dict.h>
#include <libavutil/parseutils.h>
#include <libavutil/samplefmt.h>
#include <libavutil/avassert.h>
#include <libavutil/time.h>
#include <libavutil/opt.h>
#include <libavutil/intreadwrite.h>

#ifdef __cplusplus
}
#endif // __cplusplus

constexpr double kAVTimeBase = AV_TIME_BASE;
