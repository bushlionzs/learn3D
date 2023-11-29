#ifndef __SERVER_LOGIC_H__
#define __SERVER_LOGIC_H__
#include <map>
#include <set>
#include <vector>
#include <net_lib.h>
#include <platform_mutex.h>
#include <platform_signal.h>
#include <platform_util.h>
#include <scoped_lock.h>
#include <server_def.h>
#include <websocket_buffer.h>
#include <server_interface.h>

class NetSession;
class HttpSession;
class IPlatformModule;
class ILog;

class ServerLogic: public IServerInterface
{
public:
	ServerLogic();
	virtual ~ServerLogic();
public:
    int init();
	void destroy();

    void stop_thread();

	virtual int process_message(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData);
    virtual int process_custom_message(uint64_t param, const char* msg, uint32_t msg_size, void* pNetThreadData);
    virtual void OnAccept(NetHandle h, const session_info_t& data, void* pNetThreadData);
    virtual void OnConnected(NetHandle h, const session_info_t& data, void* pNetThreadData);
    virtual void OnClose(NetHandle h, const session_info_t& data, void* pNetThreadData);
    virtual void on_session_release(NetHandle h, const session_info_t& data, void* pNetThreadData);
    virtual void* create_net_thread_data(uint32_t uiThreadIndex) { return NULL; }
    virtual ILog* create_log() { return NULL; }
    virtual bool is_flow_log_single_file() { return false; }

    virtual bool check_visitor(const session_info_t& data);
    virtual int load_config();
    virtual uint32_t  get_worker_thread_count(){return 0;}
    virtual uint32_t get_network_thread_count(){return 1;}
    virtual uint32_t get_network_io_thread_count(){return 1;}
    virtual uint32_t get_http_client_thread_count() { return 1; }
    virtual uint32_t get_timer_thread_count() { return 4; }
	virtual uint16_t get_dns_client_port() {return 0;}
    virtual bool is_ssl() {return false;}
    virtual bool is_websocket() {return false;}
    virtual bool is_need_split() {return true;}
    virtual std::string get_server_ip() {return std::string();}
    virtual uint16_t get_server_port() {return 0;}
    virtual std::string get_server_http_ip() {return std::string();}
	virtual uint16_t get_server_http_port() {return 0;}
    virtual void set_server_http_port(uint16_t port) {}
    virtual uint32_t get_delay_time_duration() {return 120;}
	
	virtual bool  is_delay_send() {return false;}
    virtual bool  is_async_send() {return false;}
    virtual uint32_t get_async_io_thread_count(){return 1;}

    virtual std::string get_ssl_crt_file_name(){return std::string();}
    virtual std::string get_ssl_key_file_name(){return std::string();}
    virtual int websocket_handshake(NetHandle, websocket_http_header_t*){return 0;}
    
    virtual void OnCommand(const char* cmd, 
        const std::vector<std::string>& params,
        std::string& result, void* pNetThreadData){}
    
    virtual int process_websocket_message(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData){return 0;}

    

	virtual int process_websocket_handshake(NetHandle handle, websocket_http_header_t* header);

    
	virtual int process_http_message(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData) final;
    virtual int process_http_header(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData) final;
    virtual int process_http_agent_message(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData) final;

    int32_t send_data(NetHandle handle, const uint8_t* data, uint32_t size, SndData* param = nullptr);
	
    void start(bool block);
    void stop();
	
	virtual int post_network_message(uint32_t msg_id, uint64_t param, const uint8_t* data, uint32_t size) override;
    virtual int post_network_message(uint32_t msg_id, uint64_t param, const uint8_t* data, uint32_t size, const SessionData& sd) override;
    virtual int post_network_message(uint32_t net_idx, uint32_t msg_id, uint64_t param, const uint8_t* data, uint32_t size, IServerInterface* owner) override;
    virtual bool post_custom_message(uint32_t uiModuleIndex, uint64_t param, const uint8_t* data, uint32_t size, IServerInterface* owner, bool bIsOOB = false) override;
    void do_post_network_message(uint32_t uiModuleIndex, uint32_t msg_id, uint64_t param, const uint8_t* data, uint32_t size);

    

    int connect_server(const std::string& ip, uint16_t port, void* param = 0);
    int disconnect_server(const std::string& ip, uint16_t port);
    int disconnect_server(const std::string& ip_port);
    bool is_connection_alive(const std::string& ip_port);
    NetHandle get_peer_connection(const std::string& ip_port);

    //
    virtual void OnHttpCommand(NetHandle handle, const std::string& location, struct HttpContent* content, void* pNetThreadData) { }
    virtual void OnHttpHeader(NetHandle handle, const std::string& location, struct HttpContent* content, void* pNetThreadData) { }
    virtual void OnHttpAgentData(NetHandle handle, const char* data, uint32_t size, void* pNetThreadData) {}

    virtual void OnPreInit() {}
    virtual void OnAfterInit() {}
    virtual void OnTimer(platform_timer_t, void* param) {}
    virtual void OnTimerPre(platform_timer_t) {}
    platform_timer_t create_timer(uint32_t duration, void* param, bool loop);
    bool delete_timer(platform_timer_t);
protected:
	std::mutex _mutex;
	PlatformCond _cond;
	NetSession* _net_session;
	UdpSession *_udp_session;
	HttpSession* _http_session;
    HttpSession* _websocket_session;
    NetHandle   _http_server_hander = INVALID_NET_HANDLE;
    
    IPlatformModule* _task_module;
	IPlatformModule* _network_module;
    
    typedef std::map<std::string, NetHandle>::iterator ClientMapIterator;
    PlatformMutex m_oClientMapMutex;
    std::map<std::string, NetHandle> _client_map;

    bool _init_done;
    
    uint32_t _network_thread_count;
};

#endif //__SERVER_LOGIC_H__

