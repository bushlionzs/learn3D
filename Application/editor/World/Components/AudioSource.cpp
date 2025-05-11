/*
copyright(c) 2016-2025 panos karabelas

permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "software"), to deal
in the software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the software, and to permit persons to whom the software is furnished
to do so, subject to the following conditions :

the above copyright notice and this permission notice shall be included in
all copies or substantial portions of the software.

the software is provided "as is", without warranty of any kind, express or
implied, including but not limited to the warranties of merchantability, fitness
for a particular purpose and noninfringement. in no event shall the authors or
copyright holders be liable for any claim, damages or other liability, whether
in an action of contract, tort or otherwise, arising from, out of or in
connection with the software or the use or other dealings in the software.
*/

//= includes ========================
#include <OgreHeader.h>
#include "AudioSource.h"
#include <SDL3/SDL_audio.h>
#include "Renderer.h"
#include "Camera.h"
#include "../Entity.h"
//===================================

using namespace std;
using namespace spartan::math;

#define CHECK_SDL_ERROR(call)           \
if (!(call)) {                          \
    SP_LOG_ERROR("%s", SDL_GetError()); \
    return;                             \
}

namespace audio_device
{
    mutex device_mutex;
    SDL_AudioSpec spec;
    uint32_t id         = 0;
    uint32_t references = 0;

    // acquire the shared audio device, open it if it's not already open
    void acquire()
    {
        lock_guard<mutex> lock(device_mutex);
        if (references == 0)
        {
            id = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);
            if (id == 0)
            {
                assert_invariant(false);
            }
        }

        ++references;
    }

    // release the shared audio device, close it when no one is using it
    void release()
    {
        lock_guard<mutex> lock(device_mutex);
        --references;
        if (references == 0 && id != 0)
        {
            SDL_CloseAudioDevice(id);
            id = 0;
        }
    }
}

namespace spartan
{
    AudioSource::AudioSource(Entity* entity) : Component(entity)
    {
        audio_device::acquire();
    }

    AudioSource::~AudioSource()
    {
        Stop();

        if (m_stream)
        {
            SDL_DestroyAudioStream(m_stream);
            m_stream = nullptr;
        }

        if (m_buffer)
        {
            SDL_free(m_buffer);
            m_buffer = nullptr;
        }

        audio_device::release();
    }

    void AudioSource::OnInitialize()
    {
        Component::OnInitialize();
    }

    void AudioSource::OnStart()
    {
        if (m_play_on_start)
        { 
            Play();
        }
    }

    void AudioSource::OnStop()
    {
        Stop();
    }

    void AudioSource::OnRemove()
    {
        Stop();
    }

    void AudioSource::OnTick()
    {
       
    }

    void AudioSource::Serialize(FileStream* stream)
    {

    }

    void AudioSource::Deserialize(FileStream* stream)
    {
       
    }

    void AudioSource::SetAudioClip(const string& file_path)
    {
       
    }

    void AudioSource::Play()
    {
        
    }

    void AudioSource::Stop()
    {
        if (!m_is_playing)
            return;

        SDL_DestroyAudioStream(m_stream);
        m_stream = nullptr;

        m_is_playing = false;
    }

    float AudioSource::GetProgress() const
    {
        if (!m_is_playing)
            return 0.0f;

        return 1.0f; // todo: track bytes
    }

    void AudioSource::SetMute(bool mute)
    {
        if (m_mute == mute)
            return;

        m_mute = mute;
        SetVolume(m_volume);
    }

    void AudioSource::SetVolume(float volume)
    {
        
    }

    void AudioSource::SetPitch(const float pitch)
    {
        
    }
}
