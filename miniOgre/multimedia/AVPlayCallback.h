#pragma once

#include "FFmpegLib.h"

struct IAVCacheCallBack
{
    virtual ~IAVCacheCallBack() = default;
    virtual void    OnCacheBegin()  = 0;
    virtual void    OnCacheEnd()    = 0;
};

struct IAVPlayCallback : public IAVCacheCallBack
{
    virtual void    OnPlayerStateChanged(int state) = 0;
    virtual void    OnVideoFrame(AVFrame& frame) = 0;
};
