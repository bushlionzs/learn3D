#include <stdio.h>

#include "net_header.h"
#include "server_logic.h"
#include "msg_process.h"
#include "server_def.h"
#include "platform_log.h"
#include "base_task.h"
#include "net_manager.h"


void serverlogic_init()
{
}

uint32_t serverlogic_entry(
    uint32_t moduleid, 
    uint32_t msg_id, 
    uint64_t sender, 
    uint64_t param, 
    void* msg, 
    uint32_t msg_size, 
    void* pNetThreadData)
{
	
    ServerLogic* server = (ServerLogic*)sender;

	switch (msg_id)
	{
    case NetMsg_HttpAgent:
    {
        NetHandle handle = (NetHandle)param;
        server->process_http_agent_message(handle, (char*)msg, msg_size, pNetThreadData);
    }
    break;
    case NetMsg_HttpHeader:
    {
        NetHandle handle = (NetHandle)param;
        server->process_http_header(handle, (char*)msg, msg_size, pNetThreadData);
    }
    break;
	case NetMsg_Data:
	{
		NetHandle handle = (NetHandle)param;
		server->process_message(handle, (char*)msg, msg_size, pNetThreadData);
	}
	break;

	case NetMsg_UdpData:
	{
		UdpData* udp_data = (UdpData*)param;
		server->process_udp_message(udp_data);
		free(udp_data);
	}
    break;
	case NetMsg_Custom:
    {
        server->process_custom_message((uint64_t)param, (char*)msg, msg_size, pNetThreadData);
    }
    break;
    case NetMsg_Timer:
    {
        platform_timer_t id = *(platform_timer_t*)msg;
        server->OnTimer(id, (void*)param);
    }
    break;
    case NetMsg_HttpData:
    {
		NetHandle handle = (NetHandle)param;
		server->process_http_message(handle, (char*)msg, msg_size, pNetThreadData);
    }
    break;
    case NetMsg_WebSocket_Data:
    case NetMsg_WebSocket_Fragment:
    case NetMsg_WebSocket_Fragment_Eof:
    {
		NetHandle handle = (NetHandle)param;
        server->process_websocket_message(handle, (char*)msg, msg_size, pNetThreadData);
    }
    break;
    case NetMsg_Accept:
    {
		NetHandle handle = (NetHandle)param;
        session_info_t sit;
        if (sizeof(sit) == msg_size)
        {
            memcpy(&sit, msg, msg_size);
        }
        server->OnAccept(handle, sit, pNetThreadData);

#ifndef WIN32
		if (!NetManager::GetInstance()->BindHandle(handle))
		{
			WARNING_LOG("[handle:%" PRIu64 "]BindHandle failed", handle);
		}
#endif
    }
    break;
    case NetMsg_Connected:
    {
		NetHandle handle = (NetHandle)param;
        session_info_t sit;
        if (sizeof(sit) == msg_size)
        {
            memcpy(&sit, msg, msg_size);
        }
        server->OnConnected(handle, sit, pNetThreadData);
    }
    break;
	case NetMsg_Close:
    {
		NetHandle handle = (NetHandle)param;
        session_info_t sit;
        if (sizeof(sit) == msg_size)
        {
            memcpy(&sit, msg, msg_size);
        }
        server->OnClose(handle, sit, pNetThreadData);
        NetFactory::GetInstance()->CloseNetHandle(handle);
    }
    break;
    case NetMsg_Session_Release:
    {
        NetHandle handle = (NetHandle)param;
        session_info_t sit;
        if (sizeof(sit) == msg_size)
        {
            memcpy(&sit, msg, msg_size);
        }
        server->on_session_release(handle, sit, pNetThreadData);
    }
    break;
    case NetMsg_Websokcet_HandShake:
    {
		NetHandle handle = (NetHandle)param;
        websocket_http_header_t* ws_http_header = *(websocket_http_header_t**)msg;
        server->process_websocket_handshake(handle, ws_http_header);
        delete ws_http_header;
    }
    break;
    case NetMsg_HttpException:
    case NetMsg_WebSocket_Exception:
	{
		NetHandle handle = (NetHandle)param;
		NetFactory::GetInstance()->CloseNetHandle(handle);
	}
	break;
	}
	
	return 0;
}

void msg_init()
{
}

uint32_t msg_entry(
    uint32_t moduleid, 
    uint32_t msg_id, 
    uint64_t sender, 
    uint64_t param, 
    void* msg , 
    uint32_t msg_size, 
    void* pNetThreadData)
{
	ServerLogic* server = (ServerLogic*)sender;
    IPlatformTask* task = (IPlatformTask*)param;

	task->run(server, moduleid, msg_id);
    delete task;
    return 0;
}
