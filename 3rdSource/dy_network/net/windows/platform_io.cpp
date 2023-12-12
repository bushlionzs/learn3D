#include <stdint.h>
#include <assert.h>
#include <windows/platform_io.h>
#include <windows/platform_socket.h>
#include <iclient_connection.h>
#include <platform_log.h>
#include <platform.h>
#include <platform_util.h>
#include <platform_thread.h>
#include <net_manager.h>
#include <time_util.h>
#include <dy_network_containter.h>
extern DyNetworkContaintor *g_dy_network_containtor;

#ifdef _WIN32
#pragma warning(disable:4127)
#endif

extern struct NetLibParam g_param;

PlatformIOThread::PlatformIOThread()
{
	_completion_port = NULL;
	_run = false;
}

PlatformIOThread::~PlatformIOThread()
{
	if (_completion_port != NULL )
	{
		CloseHandle((HANDLE)_completion_port);
	}
}

bool PlatformIOThread::InitIO()
{
	if (_run)
	{
		return false;
	}

	_run = true;

	if(_completion_port == NULL )
	{
		_completion_port = (void*)CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL , 0, 0);
		_io_thread_data.init(g_param._max_recv_buffer_size);
	}
	return true;
}

bool PlatformIOThread::BindSocket(SockBase* conn)
{
	if (!conn->is_bind_io())
	{
		if (NULL != _completion_port)
		{
			void* s = (void*)conn->GetResource();
			if (_completion_port != (void*)CreateIoCompletionPort(s, _completion_port, (ULONG_PTR)conn, 0))
			{
				return false;
			}
			conn->set_bind_io(true);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

bool PlatformIOThread::UnBindSocket(SockBase* conn)
{
	conn->DestroySocket(20);
	return true;
}

void PlatformIOThread::PostEvent(OVERLAPPED* dummy)
{
	bool b = PostQueuedCompletionStatus(_completion_port, 0, 0, dummy);
}

void PlatformIOThread::RunIO()
{
	OVERLAPPED* pOverlapped;
	DWORD dwIoSize = 0;

	SockBase* sock = nullptr;
    _last_tick_count = get_tick_count();
	try
	{
		while (_run)
		{
			pOverlapped = nullptr;
            dwIoSize = 0;
			sock = nullptr;
			BOOL bIoRet = GetQueuedCompletionStatus(
				_completion_port,
				&dwIoSize,
				(PULONG_PTR)&sock,
				&pOverlapped, INFINITE);


            
			OverlappedPlus* ovPlus = (OverlappedPlus*)pOverlapped;

			if (nullptr == ovPlus)
			{
				continue;
			}

			if (nullptr == sock)
			{
				if (ovPlus->m_ioType == IOEvent)
				{
					EventOverPlus* pOverPlus = (EventOverPlus*)ovPlus;
					PlatformSocket* curr = pOverPlus->m_Owner;
					curr->OnEvent(&_io_thread_data, pOverPlus->m_event, pOverPlus->m_param);
					curr->unref();
					continue;
				}
				else
				{
					WARNING_LOG("platformSocket is nullptr");
					break;
				}
				
			}

			if (ovPlus->m_ioType == IOSend)
			{
				sock->OnSend(dwIoSize);
				sock->unref();
			}
			else if (ovPlus->m_ioType == IORecv)
			{
                OVERLAPPEDPLUS* olrecv = (OVERLAPPEDPLUS*)pOverlapped;
                if (0 == dwIoSize)
                {
					sock->DestroySocket(101);
                    NetManager::GetInstance()->ReleaseHandle(sock);
                }
                else
                {
                    if (!sock->RecvData(&_io_thread_data, olrecv, dwIoSize))
                    {
                        NetManager::GetInstance()->ReleaseHandle(sock);
                    }
                }

				sock->unref();
			}
			
			else if (ovPlus->m_ioType == IOConnect)
			{
                if (!bIoRet || !sock->OnConnected(&_io_thread_data))
                {
                    NetManager::GetInstance()->ReleaseHandle(sock);
                }

				sock->unref();
			}
			else if (ovPlus->m_ioType == IOAccept)
			{
				AcceptOverPlus* pOverPlus = (AcceptOverPlus*)ovPlus;

				PlatformSocket* curr = pOverPlus->m_Owner;

                if (curr->is_socket_valid())
                {
                    curr->update_socket_addrs(pOverPlus->m_netBuffer);

                    curr->OnAccept();
                    BindSocket(curr);
                    curr->Recv(&_io_thread_data);
					sock->Recv(nullptr);
                }
			}
            else
            {
                WARNING_LOG("[sockbase:%p]recv invalid iocp event", sock);
            }
		}
	}
	catch (...)
	{

	}
}


void PlatformIOThread::StopIO()
{
	_run = false;
    ::PostQueuedCompletionStatus(_completion_port, 0, NULL, NULL);
    join();
}

void PlatformIOThread::run_thread(const ThreadData& data)
{
    _tid = PlatformRunThread(data);
}

void PlatformIOThread::join()
{
    _tid->join();
}

PlatformIO* PlatformIO::GetInstance()
{
    return g_dy_network_containtor->get_platform_io();
}

PlatformIO::PlatformIO()
{
	_logic_thread_size = g_param._io_thread_count;
	_logic_thread = new PlatformIOThread[_logic_thread_size];
}

PlatformIO::~PlatformIO()
{
	delete[] _logic_thread;
}

bool PlatformIO::InitIO()
{
	if (false == _listen_thread.InitIO())
	{
		return false;
	}

	for (uint32_t i = 0; i < _logic_thread_size; i++)
	{
		if (false == _logic_thread[i].InitIO())
		{
			return false;
		}
	}

	return true;;
}

bool PlatformIO::BindSocket(SockBase* conn)
{
	if (conn->IsListenSocket())
	{
		return _listen_thread.BindSocket(conn);
	}
	else
	{
		NetHandle h = conn->GetNetHandle();
		uint32_t index = static_cast<uint32_t>(h % _logic_thread_size);
		return _logic_thread[index].BindSocket(conn);
	}
}

bool PlatformIO::UnBindSocket(SockBase* conn)
{
	if (conn->IsListenSocket())
	{
		return _listen_thread.UnBindSocket(conn);
	}
	else
	{
		NetHandle h = conn->GetNetHandle();
		uint32_t index = static_cast<uint32_t>(h % _logic_thread_size);

		return _logic_thread[index].UnBindSocket(conn);
	}
}

static void listen_entry(void* param)
{
	PlatformIO::GetInstance()->RunListen();
}

static void network_entry(void* param)
{
	uint64_t index = (uint64_t)param;
	PlatformIO::GetInstance()->RunThread(index);
}

void PlatformIO::RunThread(uint64_t index)
{
	if (index < g_param._io_thread_count)
	{
		_logic_thread[index].RunIO();
	}
}

void PlatformIO::PostEvent(NetHandle h, OVERLAPPED* dummy)
{
	uint32_t index = static_cast<uint32_t>(h % _logic_thread_size);
	_logic_thread[index].PostEvent(dummy);
}


void PlatformIO::RunListen()
{
	_listen_thread.RunIO();
}

void PlatformIO::RunIO()
{
	ThreadData data;
	data.threadfunc = listen_entry;
	data._param = 0;
	data._module = 0;
	strcpy(data._name, "net_listen");
    _listen_thread.run_thread(data);
	for (uint64_t i = 0; i < _logic_thread_size; i++)
	{
		data._param = (void*)i;
		data.threadfunc = network_entry;
		strcpy(data._name, "net_io");
        _logic_thread[i].run_thread(data);
	}
}

void PlatformIO::StopIO()
{
    _listen_thread.StopIO();
    for (uint64_t i = 0; i < _logic_thread_size; i++)
    {
        _logic_thread[i].StopIO();
    }
}

