#pragma once

enum class RETCODE : int
{
    ET_OK,
    ET_FFMPEG_INIT_ERROR,
    ET_FFMPEG_DEMUX_ERROR,
    ET_FFMPEG_DEMUX_DTS_INCORRECT,
    ET_CHUNK_DUPLICATED,
    ET_CHUNK_CRC_HEADER_NOT_FOUND,
    ET_CHUNK_KEY_HEADER_NOT_FOUND,
    ET_CHUNK_SYSTEM_ERROR,
    ET_CHUNK_CRC_ERROR,
    ET_TASK_ABORT,
    ET_FFMPEG_DEMUX_NEW_STREAM_ERROR,
    ET_FFMPEG_DEMUX_STREAM_TYPE_ERROR,
    ET_FFMPEG_DEMUX_STREAM_DATA_ERROR,
    ET_FFMPEG_DEMUX_SAVE_DATA_ERROR,
    ET_CHUNK_KIWI_POS_ERROR,
    ET_STATIS_SYSTEM_ERROR,
    ET_CHUNK_INFO_NOT_FOUND,
    ET_LOAD_CONFIG_FILE_ERROR,
    ET_URL_FETCHER_IS_RUNNING,
    ET_URL_FETCHER_STATUS_ERROR,
    ET_URL_FETCHER_PARSE_ERROR,
    ET_URL_FETCHER_CONNECTION_CLOSE,
    ET_URL_FETCHER_RESPONSE_TIMEOUT,
    ET_URL_FETCHER_DNS_ERROR,
    ET_URL_FETCHER_302_ERROR,
    ET_CHUNK_DATA_NOT_READY,
    ET_CHUNK_DATA_ERROR_NOT_READY,
    ET_WEBRTC_SEND_DATA_FAILED,
    ET_WEBRTC_SYSTEM_ERROR,
    ET_WEBRTC_SYSTEM_STOPPED,
    ET_REACCEPT_SYSTEM_ERROR,
    ET_P2P_WANTED_CHUNK_FAILED,
    ET_DNS_RESOLVE_FAILED,
    ET_SWITCH_NO_AVAILABLE_SOURCE,
    ET_SYMMETRIC_NET,
    ET_CDN_DOWNLOADER_ERROR,
    ET_TRACKER_DISCONNECTED,
    ET_SWITCH_SEQ_CHANGED,
    ET_NOT_ALLOWED_P2P,
    ET_NO_AVIABLE_TRACKER,
    ET_PLAY_TIME_EXPIRED,
    ET_PCDN_GOP_DOWNLOAD_ERROR,
    ET_CATON_TOO_LONG,
    ET_PLAY_LAUNCHED_FAILED,
    ET_STREAM_RE_PUSHED,
    ET_PCDN_GOP_TABLE_CHNSTOP,
};

inline const char* error_string(RETCODE ec)
{
    switch (ec)
    {
    case RETCODE::ET_OK:
        return "ok";

    case RETCODE::ET_FFMPEG_INIT_ERROR:
        return "ffmpeg_init_error";

    case RETCODE::ET_FFMPEG_DEMUX_ERROR:
        return "ffmpeg_demux_error";

    case RETCODE::ET_FFMPEG_DEMUX_DTS_INCORRECT:
        return "ffmpeg_demux_dts_incorrect";

    case RETCODE::ET_CHUNK_DUPLICATED:
        return "chunk_duplicated";

    case RETCODE::ET_CHUNK_CRC_HEADER_NOT_FOUND:
        return "chunk_crc_header_not_found";

    case RETCODE::ET_CHUNK_KEY_HEADER_NOT_FOUND:
        return "chunk_key_header_not_found";

    case RETCODE::ET_CHUNK_SYSTEM_ERROR:
        return "chunk_system_error";

    case RETCODE::ET_CHUNK_CRC_ERROR:
        return "chunk_crc_error";

    case RETCODE::ET_TASK_ABORT:
        return "task_abort";

    case RETCODE::ET_FFMPEG_DEMUX_NEW_STREAM_ERROR:
        return "ffmpeg_demux_new_stream_error";

    case RETCODE::ET_FFMPEG_DEMUX_STREAM_TYPE_ERROR:
        return "ffmpeg_demux_stream_type_error";

    case RETCODE::ET_FFMPEG_DEMUX_STREAM_DATA_ERROR:
        return "ffmpeg_demux_stream_data_error";

    case RETCODE::ET_FFMPEG_DEMUX_SAVE_DATA_ERROR:
        return "ffmpeg_demux_save_data_error";

    case RETCODE::ET_CHUNK_KIWI_POS_ERROR:
        return "chunk_kiwi_pos_error";

    case RETCODE::ET_STATIS_SYSTEM_ERROR:
        return "statis_system_error";

    case RETCODE::ET_CHUNK_INFO_NOT_FOUND:
        return "chunk_info_not_found";

    case RETCODE::ET_LOAD_CONFIG_FILE_ERROR:
        return "load_config_file_error";

    case RETCODE::ET_URL_FETCHER_IS_RUNNING:
        return "url_fetcher_is_running";

    case RETCODE::ET_URL_FETCHER_STATUS_ERROR:
        return "url_fetcher_status_error";

    case RETCODE::ET_URL_FETCHER_PARSE_ERROR:
        return "url_fetcher_parse_error";

    case RETCODE::ET_URL_FETCHER_CONNECTION_CLOSE:
        return "url_fetcher_connection_close";

    case RETCODE::ET_URL_FETCHER_RESPONSE_TIMEOUT:
        return "url_fetcher_response_timeout";

    case RETCODE::ET_URL_FETCHER_DNS_ERROR:
        return "url_fetcher_dns_error";

    case RETCODE::ET_URL_FETCHER_302_ERROR:
        return "url_fetcher_302_error";

    case RETCODE::ET_CHUNK_DATA_NOT_READY:
        return "chunk_data_not_ready";

    case RETCODE::ET_CHUNK_DATA_ERROR_NOT_READY:
        return "chunk_data_error_not_ready";

    case RETCODE::ET_WEBRTC_SEND_DATA_FAILED:
        return "webrtc_send_data_failed";

    case RETCODE::ET_WEBRTC_SYSTEM_ERROR:
        return "webrtc_system_error";

    case RETCODE::ET_WEBRTC_SYSTEM_STOPPED:
        return "webrtc_system_stopped";

    case RETCODE::ET_REACCEPT_SYSTEM_ERROR:
        return "reaccept_system_error";

    case RETCODE::ET_P2P_WANTED_CHUNK_FAILED:
        return "p2p_wanted_chunk_failed";

    case RETCODE::ET_DNS_RESOLVE_FAILED:
        return "dns_resolve_failed";

    case RETCODE::ET_SWITCH_NO_AVAILABLE_SOURCE:
        return "switch_no_available_source";

    case RETCODE::ET_SYMMETRIC_NET:
        return "symmetric_net";

    case RETCODE::ET_CDN_DOWNLOADER_ERROR:
        return "cdn_downloader_error";

    case RETCODE::ET_TRACKER_DISCONNECTED:
        return "tracker_disconnected";

    case RETCODE::ET_SWITCH_SEQ_CHANGED:
        return "sequence_changed";

    case RETCODE::ET_NOT_ALLOWED_P2P:
        return "not_allowed_p2p";

    case  RETCODE::ET_NO_AVIABLE_TRACKER:
        return "no_aviable_tracker";

    case RETCODE::ET_PLAY_TIME_EXPIRED:
        return "play_time_expired";

    case  RETCODE::ET_PCDN_GOP_DOWNLOAD_ERROR:
        return "pcdn_gop_download_error";

    case RETCODE::ET_CATON_TOO_LONG:
        return "caton_too_long";

    case RETCODE::ET_PLAY_LAUNCHED_FAILED:
        return "play_launched_failed";

    case RETCODE::ET_STREAM_RE_PUSHED:
        return "stream_re_pushed";

    case  RETCODE::ET_PCDN_GOP_TABLE_CHNSTOP:
        return "pcdn_gop_table_chnstop";
    }
    return "";
}
