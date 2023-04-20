#pragma once

#include <string>
#include <deque>
#include <mutex>

#ifdef _WIN32
#include <windows.h>
#include <mmeapi.h>
#endif

typedef std::basic_string<unsigned char>    audio_buffer_t;
typedef std::shared_ptr<audio_buffer_t>     audio_buffer_ptr;

#ifdef _WIN32
typedef std::shared_ptr<WAVEHDR>            wavehdr_ptr;
#endif

#ifdef ANDROID
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#endif

class CAudioPlayer;

struct IAudioPlayerEventHandler
{
    virtual int OnAudioPlayerWillExhaust(CAudioPlayer* pAudioPlayer) = 0;
};

class CAudioPlayer
{
public:
    CAudioPlayer(IAudioPlayerEventHandler* pEventHandler=NULL);
    ~CAudioPlayer();

public:
    bool    Open(uint32_t outputIdx, size_t maxPendingBuffers=8);
    void    Close();

public:
    bool    PlayAudio(audio_buffer_ptr audio_buffer);
    void    SetVolume(double vol); // [0, 1], 0 to mute
    double  GetVolume() const;
    double  PendingPlayTime();

private:

#if defined(_WIN32)
    static void CALLBACK                WaveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD_PTR  dwInstance, DWORD_PTR  dwParam1, DWORD_PTR  dwParam2);
    HWAVEOUT                            m_hWaveOut;
#endif

#if defined(ANDROID)
    bool                                openSLES();
    void                                closeSLES();

    static void                         bqPlayCallBack(SLAndroidSimpleBufferQueueItf caller, void *pContext);

    // engine interfaces
    SLObjectItf                         m_engineObject;
    SLEngineItf                         m_engineEngine;

    // output mix interfaces
    SLObjectItf                         m_outputMixObject;

    // buffer queue player interfaces
    SLObjectItf                         m_bqPlayerObject;
    SLPlayItf                           m_bqPlayerPlay;
    SLAndroidSimpleBufferQueueItf       m_bqPlayerBufferQueue;
    SLEffectSendItf                     m_bqPlayerEffectSend;
    SLVolumeItf                         m_bqPlayerVolume;

#endif

private:
    IAudioPlayerEventHandler*           m_pEventHandler;

    size_t                              m_numMaxPendingBuffers;
    size_t                              m_numPendingBuffers;
    size_t                              m_numPendingBytes;
    std::deque<audio_buffer_ptr>        m_pendingBuffers;
    std::deque<audio_buffer_ptr>        m_doneBuffers;
#ifdef _WIN32
    std::deque<wavehdr_ptr>             m_pendingWaveHDR;
    std::deque<wavehdr_ptr>             m_doneWaveHDR;
#endif
    const double                        m_maxDB;
    double                              m_volumeSet;
    double                              m_volumeMulti;
    std::mutex                          m_mutexBuffer;
    std::condition_variable             m_cvBuffer;

    std::mutex                          m_mutexPlayAudio;

private:
    volatile bool                       m_bStop;
    volatile bool                       m_bRunning;
    mutable std::mutex                  m_mutexRun;
    std::condition_variable             m_cvRun;

#ifdef S3AIRPLAY_DEBUG_AUDIOPLAYER2
private:
    FILE*                               m_pAudioFile;
#endif
};
