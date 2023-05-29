#pragma once

#include <string>
#include <cassert>
#include <sstream>

#include "FFmpegLib.h"

#define AV_ASSERT(x) assert(x)
#define AV_UNUSED(x) ((void)x);
#define AV_LOG(level, log) { std::stringstream ss; ss << log; printf("%s\n", ss.str().c_str()); }

void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame);
void SaveFrameYUV420(AVFrame *pFrame, int width, int height, int iFrame);
