#ifndef __SERVER_INTERFACE_H__
#define __SERVER_INTERFACE_H__
#include <map>

#include "inet_session.h"
#include <net_define.h>
class MediaMessage;
struct SessionData;
struct websocket_http_header_t;
struct session_info_t;

class IServerInterface
{
public:
    virtual ~IServerInterface(){}
    virtual uint32_t  get_worker_thread_count(){return 1;}
    virtual uint32_t get_network_thread_count(){return 1;}
    virtual uint32_t get_network_io_thread_count(){return 1;}
    virtual bool is_ssl() {return false;}
    virtual bool is_http_ssl() { return is_ssl(); }
    virtual bool is_http_continue_data() { return false; }
    virtual bool is_http_multi_req() { return true; }
    virtual bool is_http_length_ignore(){ return false;  }
    virtual bool is_websocket() {return false;}
    virtual bool is_need_split() {return true;}
    virtual std::string get_server_ip() {return std::string();}
    virtual uint16_t get_server_port() {return 0;}
    virtual std::string get_server_http_ip() {return std::string();}
	virtual uint16_t get_server_http_port() {return 0;}
    virtual uint32_t get_delay_time_duration() {return 120;}
	virtual uint32_t get_http_recv_buffer_size() {return 1024 * 256;}
	virtual uint32_t get_rtmp_recv_buffer_size() {return 1024 * 256;}    
    virtual uint32_t get_recv_buffer_size() {return 1024 * 16;}            
    virtual uint32_t get_client_recv_buffer_size() {return 1024 * 128;}     
    virtual uint32_t get_send_buffer_size() {return 1024 * 512;}            
    virtual uint32_t get_client_send_buffer_size() {return 1024 * 512;}     
    virtual uint32_t get_relay_establish_timeout() {return 10 * 1000;}
    virtual uint32_t get_relay_conn_timeout() {return 10 * 1000;}
    virtual bool use_multi_send() {return false;}

    virtual INetBuffer* create_quic_recv_buf(SessionData& sd){ return nullptr; }
    
	virtual bool  is_delay_send() {return false;}
    virtual bool  is_async_send() {return false;}
    
    virtual bool is_agent()
    {
        return false;
    }
    virtual int post_redirect_message(void *param, const std::string& loc) { return 0; }
    virtual int post_network_message(uint32_t msg_id, uint64_t param, const SessionData& data) { return -1; }
    virtual int post_network_message(uint32_t msg_id, uint64_t param, const uint8_t* data, uint32_t size) = 0;

    virtual int post_network_message(uint32_t msg_id, uint64_t param, const uint8_t* data, uint32_t size, const SessionData& sd) 
    {
        return post_network_message(msg_id, param, data, size);
    }
    
//    virtual int post_network_message(uint32_t msg_id, uint64_t param, const SessionData& data) { return -1; }
    virtual int post_network_message(uint32_t net_idx, uint32_t msg_id, uint64_t param, const uint8_t* data, uint32_t size) { return -1; }
    virtual int post_network_message(uint32_t net_idx, uint32_t msg_id, uint64_t param, const uint8_t* data, uint32_t size, IServerInterface* owner) { return -1; }
    virtual bool post_custom_message(uint32_t uiModuleIndex, uint64_t param, const uint8_t* data, uint32_t size, IServerInterface* owner, bool bIsOOB = false) { return true; }
    virtual int process_udp_message(UdpData* upd_data) {return -1;}
    virtual void stop() {};

    virtual int process_http_agent_message(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData) { return 0; }
    virtual int process_message(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData) { return 0; }
    virtual int process_custom_message(uint64_t param, const char* msg, uint32_t msg_size, void* pNetThreadData) { return 0; }
    virtual void OnAccept(NetHandle h, const session_info_t& data, void* pNetThreadData) {}
    virtual void OnConnected(NetHandle h, const session_info_t& data, void* pNetThreadData) {}
    virtual void OnClose(NetHandle h, const session_info_t& data, void* pNetThreadData) {}
    virtual void on_session_release(NetHandle h, const session_info_t& data, void* pNetThreadData) {}
    virtual int process_websocket_message(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData) { return 0; }
    virtual int process_websocket_handshake(NetHandle handle, websocket_http_header_t* header) { return 0; }
    virtual int process_http_message(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData) { return 0; }
    virtual int process_http_header(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData) { return 0; }
};
#endif //__SERVER_INTERFACE_H__