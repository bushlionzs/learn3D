#include "AVAudioRender.h"
#include "AVSyncTuner.h"
#include "AVCommon.h"

CAVAudioRender::CAVAudioRender(size_t numMaxFrames, AVStream* pAVStream, CAVSyncTuner* pAVSyncTuner, IAVPlayCallback* callback)
: CAVRenderBase(numMaxFrames, pAVStream, pAVSyncTuner, callback)
{

}

double CAVAudioRender::GetVolume()
{
    return m_oAudioPlayer.GetVolume();
}

void CAVAudioRender::SetVolume(double vol)
{
    m_oAudioPlayer.SetVolume(vol);
}

bool CAVAudioRender::open()
{
    if (m_oAudioPlayer.Open(WAVE_MAPPER)) {
        m_pAVSyncTuner->SetAudioRender(this);
        return true;
    }
    return false;
}

bool CAVAudioRender::close()
{
    m_pAVSyncTuner->SetAudioRender(NULL);
    m_oAudioPlayer.Close();
    return true;
}

int CAVAudioRender::render_frame(AVFrame& frame)
{
    static const double  render_threshold_second = 0.001;
    static const int64_t sleep_threshold_millisecond = 1;
    static const double  av_nosync_threshold_second = 10.0;

    double pts = *reinterpret_cast<double*>(&frame.pts);
    double frame_duration = av_q2d(m_pAVStream->time_base) * frame.pkt_duration;
    double cur_duration = av_q2d(m_pAVStream->time_base) * m_nCurDuration;
    double master_clock = 0;
    double self_clock = 0;
    double clock_diff = 0;
    double render_diff = 0;
    bool   sync_to_self_clock = false;
    PTS_STATE master_state, self_state;

    while ( !m_bAbortRender )
    {
        /* waiting master clock tick in advance */
        while ((master_clock = m_pAVSyncTuner->GetMasterClock(master_state), master_state.not_running || master_state.stopped) && !m_bAbortRender && !m_bPaused && !m_bCacheing)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep_threshold_millisecond));
        }

        if ( m_bAbortRender )
            return -1;

        /* paused&chcheing state maybe setted in 'render_frame' call, so check again*/
        {
            std::unique_lock<std::mutex> lock(m_mutexPause);
            while ( (m_bPaused||m_bCacheing) && !m_bAbortRender )
            {
                m_oCurPTSDrift.Pause();
                m_cvPause.wait(lock);
                m_oCurPTSDrift.Resume();
            }
        }

        if ( m_bAbortRender )
            return -1;

        if (m_pAVSyncTuner->GetSyncTpye() == AV_SYNC_AUDIO_MASTER)
            break;

        /* check a-v nosync */
        self_clock = this->GetRenderClock(self_state);
        clock_diff = self_clock - master_clock;
        sync_to_self_clock = master_state.eof || (fabs(clock_diff) > av_nosync_threshold_second);

        if (sync_to_self_clock) {
            /* sync pts to self clock */
            render_diff = pts - self_clock;
            if ((render_diff > render_threshold_second) && (m_oCurPTSDrift.Time() < cur_duration))
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(sleep_threshold_millisecond));
                continue;
            }
            else
            {
                break;
            }
        }
        else {
            /* sync pts to master clock */
            render_diff = pts - master_clock;
            if (render_diff > render_threshold_second)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(sleep_threshold_millisecond));
                continue;
            }
            else
            {
                break;
            }
        }
    }

    if ( m_bAbortRender )
        return -1;

    /* update clock */
    m_fCurPTS = pts - m_oAudioPlayer.PendingPlayTime();
    m_oCurPTSDrift.Reset();
    m_fNextPTS = pts + frame_duration;

    m_nCurPTS = frame.best_effort_timestamp;
    m_nNextPTS = m_nCurPTS + frame.pkt_duration;

    m_nCurDuration = frame.pkt_duration;

    m_fPlaytime += frame.nb_samples / (double)frame.sample_rate;

    m_oAudioPlayer.PlayAudio(audio_buffer_ptr(new audio_buffer_t(frame.data[0], frame.linesize[0])));

    return 1;
}
