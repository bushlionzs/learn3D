#ifndef __NETDEFINE_H__
#define __NETDEFINE_H__

#ifndef _WIN32
#include <sys/uio.h>
#endif

#include <stdlib.h>
#include <stdint.h>
#include <memory.h>
#include <string>
#include <memory>
#include <net_handle.h>
#include "net_helper.h"

#ifndef MAX_CONNECTION_COUNT
#define MAX_CONNECTION_COUNT 200000
#endif

enum NetProtocol
{
	NETPROTOCOL_INVALID = 0,
	NETPROTOCOL_UDP,
	NETPROTOCOL_TCP,
    NETPROTOCOL_QUIC,
};

class IChunkSlice;
class QuicEngineBase;
struct QuicConfig
{
    bool            _use_pkt_send = true;
    uint32_t        _max_pkt_list_size = 3000;
    uint32_t        _congestion_ctrl_algo = 0;
    uint32_t        _idle_conn_timeout = 30;
    uint32_t        _flow_control_window = 1*1024*1024;
    uint32_t        _max_flow_control_window = 0;
    uint32_t        _udp_send_buffer_size = 100 * 1024 * 1024;
    std::string     _log;
    std::string     _log_level = "notice";
    std::string     _sni;
    std::string     _crt_file;
    std::string     _key_file;
    std::shared_ptr<IChunkSlice> _chunk_slice;
    QuicEngineBase* _quic_engine = nullptr;
};

struct SessionData
{
	std::string  m_LocalIP;
	uint16_t     m_LocalPort = 0;
    uint16_t     m_family = AF_UNSPEC;  // AF_UNSPEC will auto check inet family
	std::string  m_PeerIP;   
	uint16_t     m_PeerPort = 0;
    std::string  m_BindInterface;
    uint16_t     m_is_client = 0;
    uint32_t     m_recv_buffer_size = 0;
    uint32_t     m_send_buffer_size = 0;
	void*		 m_param = nullptr;
    bool         m_reuse_port = false;
    bool         m_ipv6_only = false;
    bool         m_is_quic = false;
    std::shared_ptr<QuicConfig> m_quic_cfg;

    const char *get_local_ip() const;
    void check_inet_family();
};

struct SndData
{
	uint32_t _dst_address = 0; // network order, and v4 dst address never be 0
	uint16_t _dst_port = 0; // host order
    in6_addr _dst_address6;
    int64_t size_hint = -1;
    bool nodelay = false;

    bool is_ip4() const { return _dst_address != 0; }
    bool is_ip6() const { return _dst_address == 0; }
    bool from_string(const char *str);
};

#ifdef _WIN32
#pragma warning(disable:4200)
#endif

struct UdpData
{
	NetHandle _net_handle;
	uint32_t _send_ip;  // network order
	uint16_t _send_port; // host order
    in6_addr _send_ip6;
	uint32_t _size;
	char    _data[0];

    bool is_ip4() const { return _send_ip != 0; }
    bool is_ip6() const { return _send_ip == 0; }
    bool from_addr(const sockaddr* addr, int addrlen);
    bool to_addr(sockaddr* addr, int& addrlen) const;
    const char *ip_string(char *buf, size_t len) const;
};

// -1 unset
struct TcpKeepAliveOption
{
    int idle_sec = -1;
    int intvl_sec = -1;          // not support on MAC
    int probes = -1;             // not support on MAC or windows
};

struct NetLibParam
{
    uint32_t _max_number_of_epoll_event = 5000;
    uint32_t _max_queuing_connection_number = 2000;
    uint32_t _max_recv_buffer_size = 512 * 1024;
    uint32_t _io_thread_count = 2;
    uint32_t _async_io_thread_count = 1;
    uint32_t _delay_time_duration = 120; //ms
    uint32_t _timer_thread_count = 2;
    uint32_t _http_client_thread_count = 2;
    uint32_t _net_lib_buffer_block_size = 256 * 1024;
    uint32_t _max_connection_cnt = MAX_CONNECTION_COUNT;
    uint32_t _dns_client_port = 0;
    uint32_t _dns_cache_limit = 512;
    uint32_t _dns_timeout = 400;
    int      _ip_stack_affinity = AF_INET;
    std::string _ssl_crt_file_name;
    std::string _ssl_key_file_name;
    bool        _is_delay_send = false;
    bool        _is_async_send = false;
    bool        _ssl_cdn = false;
    bool        _dns_enable_ip6 = false;


};


struct IOThredData
{
    char* _recv_buffer;
    uint32_t _recv_buffer_size;
    void init(uint32_t size)
    {
        _recv_buffer_size = size;
        _recv_buffer = (char*)malloc(_recv_buffer_size);
    }
    IOThredData()
    {
        _recv_buffer_size = 0;
        _recv_buffer = NULL;
    }
    ~IOThredData()
    {
        if (_recv_buffer)
        {
            free(_recv_buffer);
        }
    }
};

#ifdef _WIN32
struct iovec
{
    void  *iov_base;
    size_t iov_len;
};
#endif

typedef struct{
    int64_t _recv_bytes;
    int64_t _send_bytes;
}net_lib_stat_t;

#endif //__NETDEFINE_H__

