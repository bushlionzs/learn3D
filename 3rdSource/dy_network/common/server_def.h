#ifndef __SERVER_DEF_H__
#define __SERVER_DEF_H__
#include <stdint.h>
#include <string>

#include "net_helper.h"

enum NetMsg
{
	NetMsg_Data                     = 0,
	NetMsg_UdpData					,
	NetMsg_Close                    ,
    NetMsg_Session_Release          ,
    NetMsg_HttpData                 ,
    NetMsg_HttpDataResponse         ,
    NetMsg_HttpAgent                ,
    NetMsg_HttpHeader               ,
    NetMsg_HttpException            ,
    NetMsg_Accept                   ,
    NetMsg_Timer                    ,
    NetMsg_Connected                ,
	NetMsg_Custom				    ,
    NetMsg_Websokcet_HandShake      ,
    NetMsg_WebSocket_Data           ,
    NetMsg_WebSocket_Fragment       ,
    NetMsg_WebSocket_Fragment_Eof   ,
    NetMsg_WebSocket_Exception      ,
    NetMsg_HttpReponse_StatusLine   ,
    NetMsg_HttpReponse_Headers      ,
    NetMsg_WebSocket_Ping,
    NetMsg_WebSocket_Pong,
    NetMsg_WebSocket_Close,
};

enum ServerError
{
    SERVER_SUCCESS                  = 0,
	CONFIG_FILE_NOT_EXIST 			= 1,
	CONFIG_FILE_NOT_JSON  			= 2,
	CONFIG_FILE_JSON_FORMAT_ERROR	= 3,
    LOAD_CONFIG_FILE_ERROR          = 4,
    CREATE_TCP_SERVER_FAILED        = 5,
    SERVER_ERROR_LOCAL_IP_FAILED    = 6,
    SERVER_ERROR_INVALID_MESSAGE    = 7,
    SERVER_ERROR_NOT_FIND_PEER      = 8,
    SERVER_ERROR_MEMORY             = 9,
	SERVER_ERROR_INIT_FAILED		= 10,
	CANNOT_FIND_APPID_BY_TYPE       = 11,
	PARSE_JSON_MSG_ERROR            = 12,
	SERVER_ERROR_SEND_MSG_FAILED    = 13,
	SERVER_ERROR_PARSE_MSG_FAILED   = 14,
	HTTP_ERROR                      = 15,
    SERVER_ERROR_MONITOR_DATA_EXPIRED = 16,
    PARSE_PROTO_MSG_ERROR = 17,
    SERVER_ERROR_CHECK_MD5_SECRET_FAILED = 18,
    SERVER_ERROR_CHECK_MACHINE_ID_FAILED = 19,
    CREATE_QUIC_SERVER_FAILED       = 20,
    SERVER_ERROR                      = 100,
};

enum ServerMsg
{
    SERVERMSG_MONITOR_DATA = 100,
};

// 监控系统相关的路由组APPID定义
enum RouteAppid
{
    ROUTE_APPID_MONITOR_WRITER          = 1,//MonitorWriterServer的路由组Appid
    ROUTE_APPID_MONITOR_AGGREGATOR      = 2,//MonitorAggregatorServer的路由组Appid
    ROUTE_APPID_MONITOR_FILTER          = 3,//MonitorFilterServer的路由组Appid
    ROUTE_APPID_MONITOR_NOTICE          = 4,//MonitorNoticeServer的路由组Appid
    ROUTE_APPID_MONITOR_SHEET           = 5,//MonitorSheetServer的路由组Appid
    ROUTE_APPID_MONITOR_PREDICTION      = 6,//MonitorPredictionServer的路由组Appid

    ROUTE_APPID_OUTER_MOBILE            = 101,// 外网移动接入点Appid
    ROUTE_APPID_OUTER_UNICOM            = 102,// 外网联调接入点Appid
    ROUTE_APPID_OUTER_TELECOM           = 103,// 外网电信接入点Appid
    ROUTE_APPID_OUTER_RAILCOM           = 104,// 外网铁通接入点Appid
    ROUTE_APPID_OUTER_EDUCATION         = 105,// 外网教育接入点Appid
    ROUTE_APPID_OUTER_ALICLOUD          = 106,// 外网阿里云接入点Appid
    ROUTE_APPID_OUTER_TENCLOUD          = 107,// 外网腾讯云接入点Appid
};

enum
{
    HttpState_Start             = 0,
    HttpState_Header            = 1,
    HttpState_Body              = 2,
    HttpState_ChunkSize         = 3,
    HttpState_ChunkBody         = 4,
    HttpState_ChunkFull         = 5,
    HttpState_Ignore            = 6,
    HttpState_Execption         = 7,
    
};

struct session_info_t
{
    char peer_ip[INET6_ADDRSTRLEN];
    uint16_t peer_port = 0;
    char local_ip[INET6_ADDRSTRLEN];
    uint16_t local_port = 0;
    bool is_client = false;
    bool is_logic_event = false;
	void* param;
    bool is_quic = false;
};

const char* get_error_msg(uint32_t error);

#endif //__SERVER_DEF_H__
