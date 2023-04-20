#include "FFmpegInitializer.h"
#include "AVPlayer.h"
#include "AVCommon.h"

#include "FFmpegLib.h"

#define LINE_SZ 1024
static int av_log_level = AV_LOG_WARNING;

static int get_category(void *ptr){
    AVClass *avc = *(AVClass **) ptr;
    if(    !avc
        || (avc->version&0xFF)<100
        ||  avc->version < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) return AV_CLASS_CATEGORY_NA + 16;

    if(avc->get_category)
        return avc->get_category(ptr) + 16;

    return avc->category + 16;
}

static void format_line(void *ptr, int level, const char *fmt, va_list vl,
    char part[3][LINE_SZ], int part_size, int *print_prefix, int type[2])
{
    AVClass* avc = ptr ? *(AVClass **) ptr : NULL;
    part[0][0] = part[1][0] = part[2][0] = 0;
    if(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    if (*print_prefix && avc) {
        if (avc->parent_log_context_offset) {
            AVClass** parent = *(AVClass ***) (((uint8_t *) ptr) +
                avc->parent_log_context_offset);
            if (parent && *parent) {
                _snprintf(part[0], part_size, "[%s @ %p] ",
                    (*parent)->item_name(parent), parent);
                if(type) type[0] = get_category(((uint8_t *) ptr) + avc->parent_log_context_offset);
            }
        }
        _snprintf(part[1], part_size, "[%s @ %p] ",
            avc->item_name(ptr), ptr);
        if(type) type[1] = get_category(ptr);
    }

    vsnprintf(part[2], part_size, fmt, vl);

    *print_prefix = strlen(part[2]) && part[2][strlen(part[2]) - 1] == '\n';
}

static void log_callback(void* ptr, int level, const char* fmt, va_list vl)
{
    static int print_prefix = 1;
    static int count;
    static char prev[LINE_SZ];
    char part[3][LINE_SZ];
    char line[LINE_SZ];
    static int is_atty;
    int type[2];

    format_line(ptr, level, fmt, vl, part, sizeof(part[0]), &print_prefix, type);
    _snprintf(line, sizeof(line), "%s%s%s", part[0], part[1], part[2]);

    if (level >= AV_LOG_DEBUG)
    {
        AV_LOG(DEBUG, line);
    }
    else if (level < AV_LOG_DEBUG && level >= AV_LOG_INFO)
    {
        AV_LOG(INFO, line);
    }
    else if (level < AV_LOG_INFO && level >= AV_LOG_WARNING)
    {
        AV_LOG(WARN, line);
    }
    else if (level < AV_LOG_WARNING && level >= AV_LOG_ERROR)
    {
        AV_LOG(ERROR, line);
    }
    else
    {
        AV_LOG(FATAL, line);
    }
}

bool CFFmpegInitializer::InitFFmpeg()
{
    //av_log_set_flags(AV_LOG_SKIP_REPEATED);
    //av_log_set_level(AV_LOG_INFO);
    //av_log_set_callback(log_callback);

    avdevice_register_all();
    avformat_network_init();

    av_init_packet(&gFlushPkt);
    av_init_packet(&gEofPkt);
    av_frame_unref(&gFlushFrm);
    av_frame_unref(&gEofFrm);
    gFlushPkt.data = (uint8_t*)"FLUSH_PKT";
    gFlushPkt.size = strlen("FLUSH_PKT");

    gEofPkt.data = NULL;
    gEofPkt.size = strlen("EOF_PKT");

    gFlushFrm.data[0] = (uint8_t*)"FLUSH_FRAME";
    gFlushFrm.linesize[0] = strlen("FLUSH_FRAME");

    gEofFrm.data[0] = NULL;
    gEofFrm.linesize[0] = strlen("EOF_FRAME");

    return true;
}

void CFFmpegInitializer::ShutdownFFmpeg()
{
    avformat_network_deinit();
}
