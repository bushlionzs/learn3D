#include "AudioPlayer.h"
#include "FFmpegLib.h"
#include "AVCommon.h"

#include <assert.h>
#include <algorithm>

inline static
void TuneVolume(audio_buffer_ptr audio_buffer, double volume)
{
    if ( (audio_buffer->size() % 2) != 0 )
        return;

    short* sample_buffer = (short*)audio_buffer->data();
    size_t    num_samples   = audio_buffer->size() / 2;
    for (size_t i = 0; i < num_samples; ++i)
    {
        int64_t tune_sample = sample_buffer[i] * volume;
        sample_buffer[i] = std::max<int64_t>(std::min<int64_t>(tune_sample, INT16_MAX), INT16_MIN);
    }
}

CAudioPlayer::CAudioPlayer(IAudioPlayerEventHandler* pEventHandler)
: m_pEventHandler(pEventHandler), m_maxDB(42)
{
    m_bStop = true;
    m_bRunning = false;
    m_numMaxPendingBuffers = 32;
    m_numPendingBuffers = 0;
    m_numPendingBytes = 0;
    m_volumeSet = 1;
    m_volumeMulti = 1;

#if defined(_WIN32)
    m_hWaveOut = NULL;
#endif

#if defined(ANDROID)
    m_engineObject = NULL;
    m_engineEngine = NULL;
    m_outputMixObject = NULL;
    m_bqPlayerObject = NULL;
    m_bqPlayerPlay = NULL;
    m_bqPlayerBufferQueue = NULL;
    m_bqPlayerEffectSend = NULL;
    m_bqPlayerVolume = NULL;
#endif

#ifdef S3AIRPLAY_DEBUG_AUDIOPLAYER2
    m_pAudioFile = NULL;
#endif
}

CAudioPlayer::~CAudioPlayer()
{
    this->Close();
}

bool CAudioPlayer::Open(uint32_t outputIdx, size_t maxPendingBuffers)
{
    std::unique_lock<std::mutex> lock(m_mutexRun);
    if ( m_bRunning )
        return true;

#if defined(_WIN32)

    HRESULT hr;

    WAVEFORMATEX    wfx;
    ZeroMemory(&wfx,sizeof(WAVEFORMATEX));

    wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.nChannels = 2;
    wfx.nSamplesPerSec = 44100L;
    wfx.wBitsPerSample = 16;
    wfx.cbSize = 0;
    wfx.nBlockAlign = wfx.wBitsPerSample * wfx.nChannels / 8;
    wfx.nAvgBytesPerSec =  wfx.nSamplesPerSec * wfx.nBlockAlign;

    if ( (hr = ::waveOutOpen(&m_hWaveOut, outputIdx, &wfx, (DWORD_PTR)&CAudioPlayer::WaveOutProc, (DWORD_PTR)this, CALLBACK_FUNCTION)) != MMSYSERR_NOERROR )
    {
        AV_LOG(ERROR, "waveOutOpen failed:" << hr);
        return false;
    }

    MMRESULT ok = waveOutSetVolume(m_hWaveOut, 0xFFFFFFFF);
    if (ok != MMSYSERR_NOERROR) {
        AV_LOG(ERROR, "waveOutSetVolume failed:" << ok);
    }

#endif

#if defined(ANDROID)
    if ( !openSLES() )
        return false;
#endif

    m_numMaxPendingBuffers = maxPendingBuffers;
    m_numPendingBuffers = 0;
    m_numPendingBytes = 0;
    m_volumeSet = 1;
    m_volumeMulti = 1;

    m_bStop = false;
    m_bRunning = true;

#ifdef S3AIRPLAY_DEBUG_AUDIOPLAYER2
#if     defined(_WIN32)
    m_pAudioFile = fopen("audio.pcm", "wb");
#elif   defined(ANDROID)
    m_pAudioFile = fopen("/data/data/com.s3graphics.airplay/audio.pcm", "wb");
#else
    m_pAudioFile = NULL;
#endif
#endif

    return m_bRunning;
}

void CAudioPlayer::Close()
{
    std::unique_lock<std::mutex> lock(m_mutexRun);
    if ( !m_bRunning )
        return;

    m_bStop = true;
    m_bRunning = false;

    m_cvBuffer.notify_all();

    // it's just a trick for wait pending PlayAudio to done.
    {
        std::unique_lock<std::mutex> lock(m_mutexPlayAudio);
    }

    // wait all pending audio buffer done.
    {
        std::unique_lock<std::mutex> lock(m_mutexBuffer);
        while ( m_numPendingBuffers > 0 )
            m_cvBuffer.wait(lock);
    }

    // clear done audio buffer.
    {
        std::unique_lock<std::mutex> lock(m_mutexBuffer);

#ifdef _WIN32
        while ( !m_doneWaveHDR.empty() ) {
            wavehdr_ptr pWaveHDR = m_doneWaveHDR.front();
            ::waveOutUnprepareHeader(m_hWaveOut, pWaveHDR.get(), sizeof(WAVEHDR));
            m_doneWaveHDR.pop_front();
        }
#endif

        while ( !m_doneBuffers.empty() )
            m_doneBuffers.pop_front();
    }

#if defined(_WIN32)
    ::waveOutReset(m_hWaveOut);
    ::waveOutClose(m_hWaveOut);
    m_hWaveOut = NULL;
#endif

#if defined(ANDROID)
    closeSLES();
#endif

    m_volumeSet = 1;
    m_volumeMulti = 1;

#ifdef S3AIRPLAY_DEBUG_AUDIOPLAYER2
    if ( m_pAudioFile ) {
        fflush(m_pAudioFile);
        fclose(m_pAudioFile);
        m_pAudioFile = NULL;
    }
#endif
}

double CAudioPlayer::PendingPlayTime()
{
    static const double kBytesPerSecond = 44100 * 2 * 2;
    std::unique_lock<std::mutex> lock(m_mutexBuffer);
    return m_numPendingBytes / kBytesPerSecond;
}

bool CAudioPlayer::PlayAudio(audio_buffer_ptr audio_buffer)
{
    if ( !m_bRunning )
        return false;

    std::unique_lock<std::mutex> lock(m_mutexPlayAudio);

    {
        std::unique_lock<std::mutex> lock(m_mutexBuffer);
        while ( !m_bStop && m_numPendingBuffers >= m_numMaxPendingBuffers )
        {
#if defined(_WIN32)
            while ( !m_doneWaveHDR.empty() ) {
                wavehdr_ptr pWaveHDR = m_doneWaveHDR.front();
                ::waveOutUnprepareHeader(m_hWaveOut, pWaveHDR.get(), sizeof(WAVEHDR));
                m_doneWaveHDR.pop_front();
            }
#endif

            while ( !m_doneBuffers.empty() )
                m_doneBuffers.pop_front();

            m_cvBuffer.wait(lock);
        }
    }

    if ( m_bStop )
        return false;

    TuneVolume(audio_buffer,  m_volumeMulti);
#if defined(_WIN32)

    HRESULT hr;
    std::shared_ptr<WAVEHDR> pWaveHDR(new WAVEHDR);

    memset(pWaveHDR.get(), 0, sizeof(WAVEHDR));
    pWaveHDR->lpData = (LPSTR)audio_buffer->data();
    pWaveHDR->dwBufferLength = audio_buffer->size();
    pWaveHDR->dwLoops = 1;

    if ( (hr = ::waveOutPrepareHeader(m_hWaveOut, pWaveHDR.get(), sizeof(WAVEHDR))) != MMSYSERR_NOERROR )
    {
        return false;
    }

    {
        std::unique_lock<std::mutex> lock(m_mutexBuffer);
        m_pendingBuffers.push_back(audio_buffer);
        m_pendingWaveHDR.push_back(pWaveHDR);
        ++m_numPendingBuffers;
        m_numPendingBytes += audio_buffer->size();
    }

    if ( (hr = ::waveOutWrite(m_hWaveOut, pWaveHDR.get(), sizeof(WAVEHDR)) != MMSYSERR_NOERROR) )
    {
        std::unique_lock<std::mutex> lock(m_mutexBuffer);
        m_pendingWaveHDR.pop_back();
        m_pendingBuffers.pop_back();
        --m_numPendingBuffers;
        m_numPendingBytes -= audio_buffer->size();
        return false;
    }

#elif defined(ANDROID)

    {
        std::unique_lock<std::mutex> lock(m_mutexBuffer);
        m_pendingBuffers.push_back(audio_buffer);
        ++m_numPendingBuffers;
        m_numPendingBytes += audio_buffer->size();
    }

    SLresult hr;
    if ( (hr=(*m_bqPlayerBufferQueue)->Enqueue(m_bqPlayerBufferQueue, audio_buffer->data(), audio_buffer->size())) != SL_RESULT_SUCCESS )
    {
        AV_LOG(ERROR, "(*m_bqPlayerBufferQueue)->Enqueue() failed. error: " << hr);
        std::unique_lock<std::mutex> lock(m_mutexBuffer);
        m_pendingBuffers.pop_back();
        --m_numPendingBuffers;
        m_numPendingBytes -= audio_buffer->size();
        return false;
    }

#else

    return false;

#endif

    {
        std::unique_lock<std::mutex> lock(m_mutexBuffer);

#if defined(_WIN32)
        while ( !m_doneWaveHDR.empty() ) {
            wavehdr_ptr pWaveHDR = m_doneWaveHDR.front();
            ::waveOutUnprepareHeader(m_hWaveOut, pWaveHDR.get(), sizeof(WAVEHDR));
            m_doneWaveHDR.pop_front();
        }
#endif

        while ( !m_doneBuffers.empty() )
            m_doneBuffers.pop_front();
    }

#ifdef S3AIRPLAY_DEBUG_AUDIOPLAYER2
    if ( m_pAudioFile ) {
        fwrite(audio_buffer->data(), 1, audio_buffer->size(), m_pAudioFile);
        fflush(m_pAudioFile);
    }
#endif

    return true;
}

void CAudioPlayer::SetVolume(double vol)
{
    std::unique_lock<std::mutex> lock(m_mutexRun);
    if (!m_bRunning)
        return;

    m_volumeSet = av_clipd(vol, 0.0, 1.0);
    if (m_volumeSet == 0) {
        m_volumeMulti = 0;
    }
    else {
        //double db = (m_volumeSet - 1.0) * m_maxDB;
        double db = (20.0f * log10(m_volumeSet));
        m_volumeMulti = pow(10.0, db / 20.0);
    }
    //vol = av_clipd(vol, 0.0, 1.0);
    //DWORD monoOutVolume = 0xFFFF * vol;
    //DWORD steroOutVolume = monoOutVolume | (monoOutVolume << 16);
    //MMRESULT ok = waveOutSetVolume(m_hWaveOut, steroOutVolume);
    //if (ok != MMSYSERR_NOERROR) {
    //    AV_LOG(ERROR, "waveOutSetVolume failed:" << ok);
    //}
}

double CAudioPlayer::GetVolume() const
{
    std::unique_lock<std::mutex> lock(m_mutexRun);
    if (!m_bRunning)
        return 0;

    return m_volumeSet;

    //DWORD steroOutVolume;
    //MMRESULT ok = waveOutGetVolume(m_hWaveOut, &steroOutVolume);
    //if (ok != MMSYSERR_NOERROR) {
    //    AV_LOG(ERROR, "waveOutGetVolume failed:" << ok);
    //    return 0;
    //}

    //return (steroOutVolume & 0xFFFF) / (double)0xFFFF;
}

#ifdef _WIN32

void CALLBACK CAudioPlayer::WaveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD_PTR  dwInstance, DWORD_PTR  dwParam1, DWORD_PTR  dwParam2)
{
    if(WOM_DONE == uMsg)
    {
        CAudioPlayer*  pThis       = (CAudioPlayer*)dwInstance;
        LPWAVEHDR       pWaveHDR    = (LPWAVEHDR)dwParam1;

        {
            std::unique_lock<std::mutex> lock(pThis->m_mutexBuffer);

            assert((LPSTR)pThis->m_pendingBuffers.front()->data() == pWaveHDR->lpData);
            assert(pThis->m_pendingBuffers.front()->size() == pWaveHDR->dwBufferLength);

            pThis->m_doneBuffers.push_back(pThis->m_pendingBuffers.front());
            pThis->m_doneWaveHDR.push_back(pThis->m_pendingWaveHDR.front());

            if ( pThis->m_doneBuffers.size() > pThis->m_numMaxPendingBuffers+1 ) {
            }

            pThis->m_pendingBuffers.pop_front();
            pThis->m_pendingWaveHDR.pop_front();

            --pThis->m_numPendingBuffers;
            pThis->m_numPendingBytes -= pThis->m_doneBuffers.back()->size();

            if ( pThis->m_numPendingBuffers <=2 && pThis->m_pEventHandler )
                pThis->m_pEventHandler->OnAudioPlayerWillExhaust(pThis);
        }

        pThis->m_cvBuffer.notify_all();
    }
}

#endif

#ifdef ANDROID

void CAudioPlayer::bqPlayCallBack(SLAndroidSimpleBufferQueueItf caller, void *pContext)
{
    CAudioPlayer* pThis = (CAudioPlayer*)pContext;

    {
        std::unique_lock<std::mutex> lock(pThis->m_mutexBuffer);

        pThis->m_doneBuffers.push_back(pThis->m_pendingBuffers.front());

        if ( pThis->m_doneBuffers.size() > pThis->m_numMaxPendingBuffers+1 ) {
            AV_LOG(ERROR, "AudioPlayer2 done buffer count: " << pThis->m_doneBuffers.size() << " large then max pending buffer count: " << pThis->m_numMaxPendingBuffers );
        }

        pThis->m_pendingBuffers.pop_front();

        --pThis->m_numPendingBuffers;
        pThis->m_numPendingBytes -= pThis->m_doneBuffers.back()->size();

        if ( pThis->m_numPendingBuffers <=2 && pThis->m_pEventHandler )
            pThis->m_pEventHandler->OnAudioPlayerWillExhaust(pThis);
    }

    pThis->m_cvBuffer.notify_all();
}

bool CAudioPlayer::openSLES()
{
    SLresult hr;
#define SLES_CALL(X) do { if( (hr = X) != SL_RESULT_SUCCESS ) { S3AVLog(ERROR, #X << " failed. error: " << hr ); return false; } } while(0)

    // create engine
    SLES_CALL( slCreateEngine(&m_engineObject, 0, NULL, 0, NULL, NULL) );

    SLES_CALL ( (*m_engineObject)->Realize(m_engineObject, SL_BOOLEAN_FALSE) );

    // get the engine interface, which is needed in order to create other objects
    SLES_CALL ( (*m_engineObject)->GetInterface(m_engineObject, SL_IID_ENGINE, &m_engineEngine) );

    // create output mix,
    SLES_CALL ( (*m_engineEngine)->CreateOutputMix(m_engineEngine, &m_outputMixObject, 0, NULL, NULL) );

    // realize the output mix
    SLES_CALL( (*m_outputMixObject)->Realize(m_outputMixObject, SL_BOOLEAN_FALSE) );

    // configure audio source
    SLDataLocator_AndroidSimpleBufferQueue loc_bufq = { SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, m_numMaxPendingBuffers };
    SLDataFormat_PCM format_pcm = { SL_DATAFORMAT_PCM, 2, SL_SAMPLINGRATE_44_1,
                                    SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
                                    SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT, SL_BYTEORDER_LITTLEENDIAN };

    SLDataSource audioSrc = { &loc_bufq, &format_pcm };

    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX, m_outputMixObject };
    SLDataSink audioSnk = { &loc_outmix, NULL };

    // create audio player
    const SLInterfaceID ids[3] = { SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND, SL_IID_VOLUME };
    const SLboolean req[3] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
    SLES_CALL ( (*m_engineEngine)->CreateAudioPlayer(m_engineEngine, &m_bqPlayerObject, &audioSrc, &audioSnk, 3, ids, req) );

    // realize the player
    SLES_CALL ( (*m_bqPlayerObject)->Realize(m_bqPlayerObject, SL_BOOLEAN_FALSE) );

    // get the play interface
    SLES_CALL ( (*m_bqPlayerObject)->GetInterface(m_bqPlayerObject, SL_IID_PLAY, &m_bqPlayerPlay) );

    // get the buffer queue interface
    SLES_CALL ( (*m_bqPlayerObject)->GetInterface(m_bqPlayerObject, SL_IID_BUFFERQUEUE, &m_bqPlayerBufferQueue) );

    // get the effect send interface
    SLES_CALL ( (*m_bqPlayerObject)->GetInterface(m_bqPlayerObject, SL_IID_EFFECTSEND, &m_bqPlayerEffectSend) );

    // get the volume interface
    SLES_CALL ( (*m_bqPlayerObject)->GetInterface(m_bqPlayerObject, SL_IID_VOLUME, &m_bqPlayerVolume) );

    // register callback on the buffer queue
    SLES_CALL ( (*m_bqPlayerBufferQueue)->RegisterCallback(m_bqPlayerBufferQueue, bqPlayCallBack, this) );

    SLES_CALL ( (*m_bqPlayerPlay)->SetPlayState(m_bqPlayerPlay, SL_PLAYSTATE_PLAYING) );

    AV_LOG(INFO, "Init SLES Success.");

    return true;

#undef SLES_CALL
}

void CAudioPlayer::closeSLES()
{
    SLAndroidSimpleBufferQueueState state;
    (*m_bqPlayerBufferQueue)->GetState(m_bqPlayerBufferQueue, &state);
    AV_ASSERT(state.count == 0);

    (*m_bqPlayerBufferQueue)->Clear(m_bqPlayerBufferQueue);

    if (m_bqPlayerObject != NULL)
    {
        (*m_bqPlayerObject)->Destroy(m_bqPlayerObject);
        m_bqPlayerObject = NULL;
        m_bqPlayerPlay = NULL;
        m_bqPlayerBufferQueue = NULL;
        m_bqPlayerEffectSend = NULL;
        m_bqPlayerVolume = NULL;
    }

    // destroy output mix object, and invalidate all associated interfaces
    if (m_outputMixObject != NULL)
    {
        (*m_outputMixObject)->Destroy(m_outputMixObject);
        m_outputMixObject = NULL;
    }

    // destroy engine object, and invalidate all associated interfaces
    if (m_engineObject != NULL)
    {
        (*m_engineObject)->Destroy(m_engineObject);
        m_engineObject = NULL;
        m_engineEngine = NULL;
    }
}

#endif
