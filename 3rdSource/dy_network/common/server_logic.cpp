#ifndef DY_NETWORK_DISNABLE_SSL
#include <openssl/sha.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#endif
#include <platform_log.h>
#include <platform_common.h>
#include <platform_util.h>
#include <platform.h>
#include <packet.h>
#include <msg_process.h>
#include <net_session.h>
#include <http_session.h>
#include <udp_session.h>
#include <net_header.h>
#include <http_defines.h>
#include <server_logic.h>
#include <net_manager.h>
#include <time_util.h>
#include <common_base64.h>



ServerLogic::ServerLogic()
{
	_net_session = NULL;
    _udp_session = NULL;
	_http_session = NULL;
    _websocket_session = NULL;
	_task_module = NULL;
	_network_module = NULL;

	_client_map.clear();

    _init_done = false;
    
    _network_thread_count = 1;
}

ServerLogic::~ServerLogic()
{
    if (_net_session != NULL)
    {
        delete _net_session;
        _net_session = NULL;
    }

    if (_http_session != NULL)
    {
        delete _http_session;
        _http_session = NULL;
    }

	if (_udp_session != NULL)
	{
		delete _udp_session;
		_udp_session = NULL;
	}

    if (_task_module != NULL)
    {
        destory_platform_module(_task_module);
        _task_module = NULL;
    }

    if (_network_module != NULL)
    {
        destory_platform_module(_network_module);
        _network_module = NULL;
    }
}


int ServerLogic::process_message(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData)
{
	return SERVER_SUCCESS;;
}

int ServerLogic::process_custom_message(uint64_t param, const char* msg, uint32_t msg_size, void* pNetThreadData)
{
    return SERVER_SUCCESS;
}

void ServerLogic::OnAccept(NetHandle h, const session_info_t& data, void* pNetThreadData)
{
	FLOW_LOG("[handle:%" PRIu64 "]client(%s:%d) connected to self server(%s:%d)",
		h,
		data.peer_ip,
		(int)data.peer_port,
		data.local_ip,
		(int)data.local_port);
    if (!check_visitor(data))
    {
        WARNING_LOG("client is forbidden, client ip:%s, client port: %d, server port: %d",
            data.peer_ip, data.peer_port, data.local_port);
        NetFactory::GetInstance()->CloseNetHandle(h);
    }
}

void ServerLogic::OnConnected(NetHandle h, const session_info_t& data, void* pNetThreadData)
{
    FLOW_LOG("[handle:%" PRIu64 "]client(%s:%d) connected to self server(%s:%d)",
        h,
        data.peer_ip, 
        (int)data.peer_port, 
        data.local_ip, 
        (int)data.local_port);
}

void ServerLogic::OnClose(NetHandle h, const session_info_t& data, void* pNetThreadData)
{
    FLOW_LOG("[handle:%" PRIu64 "]is_client:%d|client(%s:%d) net handle close(%s:%d)",
        h,
        (int)data.is_client,
        data.peer_ip, 
        (int)data.peer_port, 
        data.local_ip, 
        (int)data.local_port);
}

void ServerLogic::on_session_release(NetHandle h, const session_info_t& data, void* pNetThreadData)
{

}

bool ServerLogic::check_visitor(const session_info_t& data)
{
    return true;
}

int ServerLogic::load_config()
{
    return SERVER_SUCCESS;
}

int ServerLogic::process_http_message(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData)
{
	HttpContent* content =*(HttpContent**)msg;
	
    OnHttpCommand(handle, content->location, content, pNetThreadData);

    delete content;
    return SERVER_SUCCESS;
}

int ServerLogic::process_http_header(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData)
{
    HttpContent* content = *(HttpContent**)msg;

    OnHttpHeader(handle, content->location, content, pNetThreadData);

    delete content;
    return SERVER_SUCCESS;
}

int ServerLogic::process_http_agent_message(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData)
{
    OnHttpAgentData(handle, msg, msg_size, pNetThreadData);
    return SERVER_SUCCESS;
}

int ServerLogic::process_websocket_handshake(NetHandle handle, websocket_http_header_t* ws_header)
{
    if (SERVER_SUCCESS != websocket_handshake(handle, ws_header))
    {
        NetFactory::GetInstance()->CloseNetHandle(handle);
        return SERVER_SUCCESS;
    } 

    if (!NetFactory::is_client_handle(handle))
    {
        static const char* mask = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
        static const char* replyFormat = "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: %s\r\nSec-WebSocket-Version: 13\r\n\r\n";
        char header[512] = { 0 };

        std::string makeSha1String = ws_header->_sec_websocket_key + mask;

        std::string base64 = dy_network::SHA1HashString(makeSha1String.c_str());
        base64 = base64_encode((const unsigned char*)base64.c_str(), base64.size());


        int n = snprintf(header, sizeof(header), replyFormat, base64.c_str());

        NetFactory::GetInstance()->SendData(handle, (const uint8_t*)header, n);
    }

    return SERVER_SUCCESS;
}

int32_t ServerLogic::send_data(NetHandle handle, const uint8_t* data, uint32_t size, SndData* param /* = NULL */)
{
    return NetFactory::GetInstance()->SendData(handle, data, size, param);
}

int ServerLogic::init()
{
    OnPreInit();
    platform_log_init(create_log(), nullptr, is_flow_log_single_file());
	if (SERVER_SUCCESS != load_config())
    {
		INIT_LOG("init load_config failed\n");
        return LOAD_CONFIG_FILE_ERROR;
    }
	
	platform_init();
    
    struct NetLibParam nlp;
    
    nlp._ssl_crt_file_name = get_ssl_crt_file_name();
    nlp._ssl_key_file_name = get_ssl_key_file_name();
    nlp._io_thread_count   = get_network_io_thread_count();
    nlp._is_delay_send     = is_delay_send();
    nlp._is_async_send     = is_async_send();
    nlp._async_io_thread_count = get_async_io_thread_count();
    nlp._delay_time_duration = get_delay_time_duration();
    nlp._http_client_thread_count = get_http_client_thread_count();
    nlp._timer_thread_count = get_timer_thread_count();
    nlp._dns_client_port = get_dns_client_port();
    if (!netlib_init(&nlp))
    {
        INIT_LOG("netlib_init err");
        return SERVER_ERROR;
    }

    _network_thread_count = get_network_thread_count();
    
    if (0 == _network_thread_count || _network_thread_count > 64)
    {
        _network_thread_count = 1;
    }
	_network_module = create_platform_module(_network_thread_count, "net_msg");
    for (uint32_t i = 0; i < _network_thread_count; i++)
    {
        void* pThreadData = create_net_thread_data(i);
        _network_module->attach_module(i, serverlogic_init, serverlogic_entry, pThreadData);
    }
	
	_net_session = new NetSession(this, is_need_split());
	_udp_session = new UdpSession(this);
	std::string server_ip = get_server_ip();
    uint16_t port = get_server_port();
    if (!server_ip.empty() && port != 0)
    {
        if (is_websocket())
        {
            _websocket_session = new HttpSession(this, is_ssl(), true);
            NetHandle h = NetFactory::GetInstance()->CreateTcpServer(_websocket_session, server_ip, port);
            if (h == INVALID_NET_HANDLE)
            {
                INIT_LOG("[ip:%s,port:%d]fail to create websocket server", server_ip.c_str(), port);
                return CREATE_TCP_SERVER_FAILED;
            }
            
            INIT_LOG("[ip:%s,port:%d,ssl:%d]success to create websocket server", server_ip.c_str(), port, is_ssl());
        }
        else
        {
            NetHandle h = NetFactory::GetInstance()->CreateTcpServer(_net_session, server_ip, port);
            if (h == INVALID_NET_HANDLE)
            {
                 INIT_LOG("[ip:%s,port:%d]fail to create tcp server", server_ip.c_str(), port);
                return CREATE_TCP_SERVER_FAILED;
            }
            INIT_LOG("[ip:%s,port:%d]success to create tcp server", server_ip.c_str(), port);
        }
    }
	else
	{
		INIT_LOG("[ip:%s,port:%d]tcp ip is empty", server_ip.c_str(), port);
	}
    
    std::string http_ip = get_server_http_ip();
    uint16_t http_port = get_server_http_port();
    if (!http_ip.empty())
    {
        _http_session = new HttpSession(this, is_http_ssl(), false);
        NetHandle h2 = NetFactory::GetInstance()->CreateTcpServer(_http_session, http_ip, http_port);
        if (h2 == INVALID_NET_HANDLE)
        {
            INIT_LOG("[ip:%s,port:%d]fail to create http server", http_ip.c_str(), http_port);
            return CREATE_TCP_SERVER_FAILED;
        }
        _http_server_hander = h2;
        SessionData sessionData;
        NetManager::GetInstance()->GetClientConnectionInfo(h2, sessionData);
        http_port = sessionData.m_LocalPort;
        this->set_server_http_port(http_port);
        INIT_LOG("[ip:%s,port:%d]success to create http server", http_ip.c_str(), http_port);
    }
    else
    {
		INIT_LOG("[ip:%s,port:%d]http ip is emtpy", server_ip.c_str(), port);
    }
	
	uint32_t module_count = get_worker_thread_count();
    if (module_count > 0)
    {
        _task_module = create_platform_module(module_count, "task");
        for (uint32_t i = 0; i < module_count; i++)
        {
            _task_module->attach_module(i, msg_init, msg_entry, NULL);	// NOTE: task module donot need thread data
        }
    }
	

    _init_done = true;
   

    OnAfterInit();
	return SERVER_SUCCESS;
}

void ServerLogic::start(bool block)
{
    if (_task_module)
    {
        _task_module->run_module();
    }
	_network_module->run_module();
	if (block)
	{
        std::unique_lock<std::mutex> lock(_mutex);
		_cond.wait(lock);
	}
}

void ServerLogic::stop()
{
    std::unique_lock<std::mutex> lock(_mutex);
	_cond.signal();
}

void ServerLogic::destroy()
{
	platform_destroy();
	
	cross_sleep(1);
	if (_net_session)
	{
		delete _net_session;
		_net_session = NULL;
	}
}

void ServerLogic::stop_thread()
{
    //断开连接
    netlib_destroy();

    //关闭IO线程
    if (NULL != _network_module)
    {
        destory_platform_module(_network_module);
        _network_module = NULL;
    }
}

int ServerLogic::post_network_message(uint32_t msg_id, uint64_t param, const uint8_t* data, uint32_t size)
{
    int net_idx = param % _network_thread_count;
    do_post_network_message(net_idx, msg_id, param, data, size);
    return net_idx;
}

int ServerLogic::post_network_message(uint32_t msg_id, uint64_t param, const uint8_t* data, uint32_t size, const SessionData& sd)
{
    int net_idx = param % _network_thread_count;
    do_post_network_message(net_idx, msg_id, param, data, size);
    return net_idx;
}

int ServerLogic::post_network_message(uint32_t net_idx, uint32_t msg_id, uint64_t param, const uint8_t* data, uint32_t size, IServerInterface* owner)
{
    _network_module->post_module_message(net_idx, msg_id, (uint64_t)(owner ? owner : this), param, data, size);
    return net_idx;
}

bool ServerLogic::post_custom_message(uint32_t uiModuleIndex, uint64_t param, const uint8_t* data, uint32_t size, IServerInterface* owner, bool bIsOOB /*= false*/)
{
    return _network_module->post_module_message(uiModuleIndex, NetMsg_Custom, (uint64_t)(owner?owner:this), param, data, size, bIsOOB);
}

void ServerLogic::do_post_network_message(uint32_t uiModuleIndex, uint32_t msg_id, uint64_t param, const uint8_t* data, uint32_t size)
{
    _network_module->post_module_message(uiModuleIndex, msg_id, (uint64_t)this, (uint64_t)param, data, size);
}


int ServerLogic::connect_server(const std::string& ip, uint16_t port, void* param)
{
    char buffer[256];
    SessionData data;
    data.m_PeerIP = ip;
    data.m_PeerPort = port;
    
   ScopedLock<PlatformMutex> _lock(m_oClientMapMutex);
    NetHandle h = NetFactory::GetInstance()->CreateTcpConnection(_net_session, data);
    if (h != INVALID_NET_HANDLE)
    {
        snprintf(buffer, sizeof(buffer), "%s:%d", ip.c_str(), port);
        std::string ip_port(buffer);
        std::map<std::string, NetHandle>::iterator client_it = _client_map.find(ip_port);
        if ((client_it != _client_map.end()) && (client_it->second != INVALID_NET_HANDLE))
        {
            NetFactory::GetInstance()->CloseNetHandle(client_it->second);
        }
        _client_map[ip_port] = h;
    }

    FLOW_LOG("connect_server,ip:%s,port:%d", ip.c_str(), port);

    return SERVER_SUCCESS;
}

int ServerLogic::disconnect_server(const std::string& ip, uint16_t port)
{
    char buffer[256] = {0};
    snprintf(buffer, sizeof(buffer), "%s:%d", ip.c_str(), port);
    
    ScopedLock<PlatformMutex> _lock(m_oClientMapMutex);
    std::map<std::string, NetHandle>::iterator client_iter = _client_map.find(buffer);
    if (client_iter != _client_map.end())
    {
        // 关闭连接
        NetFactory::GetInstance()->CloseNetHandle(client_iter->second);
        // 删除连接句柄
        _client_map.erase(client_iter);
    }
    
    FLOW_LOG("disconnect_server,ip:%s,port:%d", ip.c_str(), port);

    return SERVER_SUCCESS;
}

int ServerLogic::disconnect_server(const std::string& ip_port)
{
    ScopedLock<PlatformMutex> _lock(m_oClientMapMutex);
    std::map<std::string, NetHandle>::iterator client_iter = _client_map.find(ip_port);
    if (client_iter != _client_map.end())
    {
        // 关闭连接
        NetFactory::GetInstance()->CloseNetHandle(client_iter->second);
        // 删除连接句柄
        _client_map.erase(client_iter);
    }
    
    FLOW_LOG("disconnect_server,ip_port: %s", ip_port.c_str());

    return SERVER_SUCCESS;
}

bool ServerLogic::is_connection_alive(const std::string& ip_port)
{
    ScopedLock<PlatformMutex> _lock(m_oClientMapMutex);
    return (_client_map.find(ip_port) != _client_map.end());
}

NetHandle ServerLogic::get_peer_connection(const std::string& ip_port)
{
    NetHandle ret = INVALID_NET_HANDLE;

    ScopedLock<PlatformMutex> _lock(m_oClientMapMutex);
    ClientMapIterator itor = _client_map.find(ip_port);
    if (itor != _client_map.end())
    {
        ret = itor->second;
    }

    if (ret == INVALID_NET_HANDLE)
    {
        WARNING_LOG("[%s]fail to find info in client_map", ip_port.c_str());
    }
    
    return ret;
}


static int32_t serverlogic_platfom_timer_callback(platform_timer_t id, void* timer_self, void* timer_param)
{
    ServerLogic* server = (ServerLogic*)timer_self;
    server->post_network_message(NetMsg_Timer, (uint64_t)timer_param,  (const uint8_t*)&id, sizeof(platform_timer_t));
    return -1;
}

int32_t serverlogic_platfom_timer_callback_loop(platform_timer_t id, void* timer_self, void* timer_param)
{
    ServerLogic* server = (ServerLogic*)timer_self;
    server->OnTimerPre(id);
    server->post_network_message(NetMsg_Timer, (uint64_t)timer_param, (const uint8_t*)&id, sizeof(platform_timer_t));
    return 0;
}

platform_timer_t ServerLogic::create_timer(uint32_t duration, void* param, bool loop)
{
    if (loop)
    {
        return platform_create_timer(duration, serverlogic_platfom_timer_callback_loop, this, param);
    }
    else
    {
        return platform_create_timer(duration, serverlogic_platfom_timer_callback, this, param);
    }
   
}

bool ServerLogic::delete_timer(platform_timer_t id)
{
    return platform_delete_timer(id);
}



