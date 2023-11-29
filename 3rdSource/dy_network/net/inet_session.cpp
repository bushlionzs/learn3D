#include "inet_session.h"
#include <net_define.h>
#include <server_def.h>
#include <server_interface.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

INetBuffer::INetBuffer(IServerInterface* server, uint32_t capacity, bool need_split)
{
	_start	    = 0;
	_end		= 0;
	_capacity   = capacity;
    _net_handle = INVALID_NET_HANDLE;
    _server = server;
    _need_split = need_split;
    
    if (_need_split)
    {
        _buf = new char[_capacity];
    }
    else
    {
#ifdef _WIN32
        _buf = new char[_capacity];
#else
        _buf = 0;
#endif
    }
}

INetBuffer::~INetBuffer()
{
    if (_buf)
	{
		delete [] _buf;
        _buf = nullptr;
	}
}


net_buf_pos_t* INetBuffer::get_recv_buf(struct IOThredData* io_thread_data)
{
    bool use_global_buffer = false;

    if (!_need_split)
    {
#ifndef _WIN32
        use_global_buffer = true;
#endif
    }

    if (use_global_buffer)
    {
        if (!io_thread_data)
        {
            return nullptr;
        }

        _net_buf_pos._buf = io_thread_data->_recv_buffer;
        _net_buf_pos._size = io_thread_data->_recv_buffer_size;
        return &_net_buf_pos;
    }
    else
    {
        uint32_t left = _capacity - _end;

        if (left < _start)
        {
            data_reset();
            memmove(_buf, _buf + _start, _end - _start);
            _end -= _start;
            _start = 0;
        }

        _net_buf_pos._buf = _buf + _end;
        _net_buf_pos._size = _capacity - _end;

        if (0 == _net_buf_pos._size)
        {
            return NULL;
        }
        return &_net_buf_pos;
    }
}

bool INetBuffer::recv_data(const char* data, uint32_t size, const SessionData& sd)
{
    if (!_need_split)
    {
        _server->post_network_message(NetMsg_Data, _net_handle, (const uint8_t*)data, size);
		return true;
    }
    else
    {
        _end += size;
        return process_data(sd);
    }
}

bool INetBuffer::OnHandle(NetHandle h, const SessionData&)
{
    _net_handle = h;
    return true;
}

void INetBuffer::printdata()
{
    //printf("start:%d, end:%d, start_value:%d, end_value:%d,this:%p, _buf:%p, threadid:%llu\n",
       // _start, _end, (int32_t)*(_buf + _start), (int32_t)*(_buf + _start + 1), this, _buf, dy::common::getpid());
}

/////////////////////////////////////////////////////////////////////
INetSession::~INetSession()
{
}

void INetSession::OnAccept(NetHandle, const SessionData&)
{
}

void INetSession::OnConnected(NetHandle, const SessionData&)
{
}

void INetSession::OnCloseServer( NetHandle )
{
}

void INetSession::on_release(NetHandle, const SessionData&)
{

}

uint32_t INetSession::get_send_buffer_size(const SessionData&)
{
    return _SND_BUF_SIZE;
}