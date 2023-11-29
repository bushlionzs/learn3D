#include "platform_pipe.h"
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include "net_buffer.h"
#include "platform_log.h"
#include "scoped_lock.h"
#include "string_util.h"
#include "platform_file_system.h"

PlatformPipe::PlatformPipe(INetSession* session, const std::string& name, bool client)
{
    _session = session;
	_name = CPlatformFileSystem::GetInstance()->GetProcessDirectory();
	_name += "/";
    _name += name;
    _is_client = client;    
}

PlatformPipe::~PlatformPipe()
{
    if (_pipe_read >= 0)
    {
        close(_pipe_read);
    }
    
    if(_pipe_write >= 0)
    {
        close(_pipe_write);
    }

    if (_send_buffer)
    {
        delete _send_buffer;
    }
    
    if(_recv_buffer)
    {
        delete _recv_buffer;
    }
}

bool PlatformPipe::Recv(struct IOThredData* io_thread_data)
{
    ScopedLock<PlatformMutex> lock(_mutex);
    while (true)
    {
        net_buf_pos_t* net_pos = _recv_buffer->get_recv_buf(io_thread_data);
        
        if (NULL == net_pos)
        {
            DestroySocket(19);
            return false;
        }
        
        int recvResult = read(_pipe_read, net_pos->_buf, net_pos->_size);
        
        switch (recvResult)
        {
        case -1:
        {
            if (errno != EAGAIN)
            {
				NOTICE_LOG("[pipe_read:%d,isclient:%d,size:%d,err:%d]pipe recv error", _pipe_read, _is_client,net_pos->_size, errno);
                //DestroySocket(20);
                return true;
            }
            else
            {
                return true;
            }
        }
        break;
        case 0:
            {
                DestroySocket(21);
                return 0;
            }
            break;
        default:
            {
                if (false == _recv_buffer->recv_data(net_pos->_buf, recvResult, _sessionData))
                {
                    DestroySocket(22);
                }
            }
        }
    }
    
    return true;
}

bool PlatformPipe::CreateResource()
{   
    std::string servername = _name + "_server";
    std::string clientname = _name + "_client";
    
    mkfifo(servername.c_str(),0666);
    
    mkfifo(clientname.c_str(),0666);
    
    if(_is_client)
    {
        _pipe_read = open(clientname.c_str(), O_RDONLY | O_NONBLOCK);
    
        if(_pipe_read < 0)
        {
            return false;
        }
    }
    else
    {
        _pipe_read = open(servername.c_str(), O_RDONLY | O_NONBLOCK);
    
        if(_pipe_read < 0)
        {
            return false;
        }
    }
    
	NOTICE_LOG("[pipe_read:%d,isclient:%d]create pipe sucessfully", _pipe_read, _is_client);
    return true;
}

bool PlatformPipe::OnInit()
{
    _recv_buffer = _session->create_recv_buffer(_sessionData);
    _send_buffer = new(std::nothrow) CBuffer(_session->get_send_buffer_size(_sessionData));
	
	_recv_buffer->OnHandle(_handle, _sessionData);
    CreateResource();
    return true;
}


bool PlatformPipe::DestroySocket(int magic)
{
    if (_pipe_read >= 0)
    {
        ScopedLock<PlatformMutex> lock(_mutex);
        if (_pipe_read >= 0)
        {
            _session->OnClose(_handle, _sessionData);
            close(_pipe_read);
			if(_pipe_write >= 0)
                close(_pipe_write);
            _pipe_read = -1;
            _pipe_write = -1;
            NOTICE_LOG("nethandle:%llu, session:%p, DestroySocket, magic:%d, err:%d,this:%p",
                _handle, _session, magic, errno, this);
        }
    }
    return true;

}

int32_t PlatformPipe::Send(const uint8_t* data, uint32_t size, SndData* param)
{
    std::string servername = _name + "_server";
    std::string clientname = _name + "_client";
    ScopedLock<PlatformMutex> lock(_mutex);
    if(_is_client)
    {
        if(_pipe_write < 0)
        {
            _pipe_write = open(servername.c_str(), O_WRONLY | O_NONBLOCK);
        
            if(_pipe_write < 0)
            {
                return NetlibError_OpenPipeError;
            }
        }
    }
    else
    {
        if(_pipe_write < 0)
        {
            _pipe_write = open(clientname.c_str(), O_WRONLY | O_NONBLOCK);
        
            if(_pipe_write < 0)
            {
                return NetlibError_OpenPipeError;
            }
        }
    }
    
    int32_t ret = write(_pipe_write, data, size);
    
    if(ret != size)
    {
        WARNING_LOG("[ret:%d,size:%d,err:%d, fd:%d, isclient:%d]write pipe failed", ret, size, errno, _pipe_write, _is_client);
		close(_pipe_write);
		_pipe_write = -1;
        return NetlibError_PipeSendError;
    }
    
    return NetlibError_None;
}




