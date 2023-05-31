#pragma once

struct NetLibParam
{
    uint32_t _max_number_of_epoll_event = 5000;
    uint32_t _max_queuing_connection_number = 2000;
    uint32_t _max_recv_buffer_size = 512 * 1024;
    uint32_t _io_thread_count = 1;
    uint32_t _async_io_thread_count = 1;
    uint32_t _delay_time_duration = 120; //ms
    uint32_t _timer_thread_count = 4;
    uint32_t _http_client_thread_count = 1;
    uint32_t _net_lib_buffer_block_size = 16 * 1024;
    uint32_t _max_connection_cnt = 100;
    uint32_t _dns_client_port = 0;
    uint32_t _dns_cache_limit = 512;
    int      _ip_stack_affinity = AF_INET;
    std::string _ssl_crt_file_name;
    std::string _ssl_key_file_name;
    bool        _is_delay_send = false;
    bool        _is_async_send = false;
    bool        _ssl_cdn = false;
    bool        _dns_enable_ip6 = false;
};