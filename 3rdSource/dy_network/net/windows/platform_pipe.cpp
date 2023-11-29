#include "platform_pipe.h"
#include "scoped_lock.h"
#include "platform_log.h"
#include "net_buffer.h"
#include "platform_io.h"
#include <windows.h>

PlatformPipe::PlatformPipe(INetSession* session, const std::string& name, bool client)
{
	_session = session;
	_name = name;
	_is_client = client;
	_pipe = NULL;
	
}

PlatformPipe::~PlatformPipe()
{
	if (_pipe != NULL)
	{
		CloseHandle(_pipe);
	}

	if (_send_buffer != nullptr)
	{
		delete _send_buffer;
	}
	
}

bool PlatformPipe::Recv(struct IOThredData* io_thread_data)
{
	DWORD dwRead = 0;

	net_buf_pos_t* net_pos = m_recvBuffer->get_recv_buf(io_thread_data);

	if (NULL == net_pos)
	{
		DestroySocket(16);
		return 0;
	}

	ref();

	memset(&m_olRecv.m_ol, 0, sizeof(m_olRecv.m_ol));
	m_olRecv.m_wsaBuffer.buf = net_pos->_buf;
	BOOL ret = ReadFile(
		_pipe,
		net_pos->_buf,
		net_pos->_size,
		&dwRead,
		(LPOVERLAPPED)&m_olRecv.m_ol);

	if (_is_client)
	{
		int kk = 0;
	}

	if (!ret)
	{
		DWORD err = GetLastError();

		if (err != ERROR_IO_PENDING)
		{
			unref();
			DestroySocket(101);
			return false;
		}
	}


	return true;
}

bool PlatformPipe::CreateResource()
{
	if (_is_client)
	{
		return CreatePipeClient();
	}
	else
	{
		return CreatePipeServer();
	}
	return true;
}

bool PlatformPipe::CreatePipeServer()
{

	_pipe = CreateNamedPipe(_name.c_str(), PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT
		, PIPE_UNLIMITED_INSTANCES, 1024, 1024, 0, NULL);

	if (_pipe == INVALID_HANDLE_VALUE)
	{
		DWORD err = GetLastError();
		
		return false;
	}

	return true;
}

bool PlatformPipe::CreatePipeClient()
{
	if (!WaitNamedPipe(_name.c_str(), NMPWAIT_NOWAIT))
	{
		return false;
	}

	_pipe = CreateFile(_name.c_str(), GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING,  FILE_FLAG_OVERLAPPED, NULL);

	if (_pipe == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	_connected = true;

	return true;
}


bool PlatformPipe::OnInit()
{
	m_olConnect.m_ioType = IOConnect;
	m_olSend.m_ioType = IOSend;
	m_olRecv.m_ioType = IORecv;


	ZeroMemory(&m_olConnect.m_ol, sizeof(OVERLAPPED));
	ZeroMemory(&m_olSend.m_ol, sizeof(OVERLAPPED));
	ZeroMemory(&m_olRecv.m_ol, sizeof(OVERLAPPED));

	m_recvBuffer = _session->create_recv_buffer(_sessionData);
	_send_buffer = new(std::nothrow) CBuffer(_session->get_send_buffer_size(_sessionData));

	m_recvBuffer->OnHandle(_handle, _sessionData);
	CreateResource();
	return true;
}

bool PlatformPipe::OnIOBinded()
{
	if (!_is_client)
	{
		BOOL ret = ConnectNamedPipe(_pipe, &m_olConnect.m_ol);

		if (ret)
		{
			return false;
		}

		DWORD err = GetLastError();

		if (err == ERROR_IO_PENDING)
		{
			return true;
		}

		if (err == ERROR_PIPE_CONNECTED)
		{
			_session->OnConnected(_handle, _sessionData);
			return Recv(nullptr);
		}

		return false;
	}
	else
	{
		return Recv(nullptr);
	}
	return true;
}

bool PlatformPipe::OnConnected(struct IOThredData* io_thread_data)
{
	_connected = true;
	_session->OnConnected(_handle, _sessionData);
	bool b = Recv(io_thread_data);

	if (!b)
		return false;

	return Send();
}

bool PlatformPipe::DestroySocket(int magic)
{
	if (_pipe != NULL)
	{
		ScopedLock<PlatformMutex> lock(_mutex);
		if (_pipe != NULL)
		{
			_session->OnClose(_handle, _sessionData);
			CloseHandle(_pipe);
			_pipe = NULL;

			NOTICE_LOG("nethandle:%llu, session:%p, DestroySocket, magic:%d, err:%d,this:%p\n",
				_handle, _session, magic, errno, this);
		}
	}
	return true;
}

int32_t PlatformPipe::Send(const uint8_t* data, uint32_t size, SndData* param)
{
	bool empty = false;
	
	ScopedLock<PlatformMutex> lock(_mutex);

	empty = _send_buffer->IsEmpty();
	bool add = _send_buffer->AddTcpBuffer(data, size);

	if (!add)
		return NetlibError_BufferError;

	if (!_connected)
		return NetlibError_None;

	if (empty)
	{
		Send();
	}
	
	return NetlibError_None;
}

int32_t PlatformPipe::Send()
{
	ScopedLock<PlatformMutex> lock(_mutex);

	const uint8_t* data = _send_buffer->GetTcpBuffer();
	uint32_t size = _send_buffer->GetTcpLength();

	if (size > 0)
	{
		DWORD dwWritten = 0;
		memset(&m_olSend.m_ol, 0, sizeof(m_olSend.m_ol));
		ref();
		BOOL ret = WriteFile(
			_pipe,
			data,
			size,
			&dwWritten,
			(LPOVERLAPPED)&m_olSend.m_ol);

		if (!ret)
		{
			DWORD err = GetLastError();

			if (err != ERROR_IO_PENDING)
			{
				unref();
				DestroySocket(102);
				return false;
			}
		}
	}

	return true;
}

void PlatformPipe::OnSend(uint32_t ioSize)
{
	ScopedLock<PlatformMutex> lock(_mutex);
	_send_buffer->ReleaseTcpBuffer(ioSize);
	Send();
}

bool PlatformPipe::RecvData(struct IOThredData* io_thread_data, OVERLAPPEDPLUS* olrecv, uint32_t size)
{
	const char* buf = olrecv->m_wsaBuffer.buf;
	
	m_recvBuffer->recv_data(buf, size, _sessionData);

	return Recv(io_thread_data);
}