#include <stdint.h>
#include <sys/time.h>
#include <sys/event.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <net_handle.h>
#include <net_tools.h>

#include <platform_socket.h>
#include <platform_thread.h>
#include <platform_io.h>


#include <net_manager.h>
#include <platform.h>
#include <platform_mutex.h>
#include <scoped_lock.h>
#include <platform_util.h>
#include <platform_log.h>
#include <time_util.h>
#include <dy_network_containter.h>
extern DyNetworkContaintor *g_dy_network_containtor;

#define MAX_NUMBER_OF_PROCESSED_EPOLL_EVENT (5000)

extern struct NetLibParam g_param;

PlatformIOThread::PlatformIOThread()
{
    _kqueue_fd = -1;
    _close_pipe_fds[0] = -1;
    _close_pipe_fds[1] = -1;
	m_bRun = false;
}

PlatformIOThread::~PlatformIOThread()
{
    StopIO();
}

bool PlatformIOThread::InitIO()
{
    if (m_bRun)
    {
        return false;
    }

    _kqueue_fd = kqueue();

	if (-1 == _kqueue_fd)
	{
		return false;
	}

    if (pipe(_close_pipe_fds) < 0)
    {
        return false;
    }

    //struct epoll_event e;
    //e.events = EPOLLIN;
    //e.data.ptr = NULL;
	
	struct kevent ke;
	EV_SET(&ke, _close_pipe_fds[0], EVFILT_READ, EV_ADD, 0, 0, NULL);
    if (kevent(_kqueue_fd, &ke, 1, NULL, 0, NULL) == -1)
	{
		return false;
	}

    _io_thread_data.init(g_param._max_recv_buffer_size);
    m_bRun = true;

	return true;
}

#define AE_READABLE 1
#define AE_WRITABLE  2
bool PlatformIOThread::BindSocket(SockBase* conn)
{
    if (_kqueue_fd >= 0)
	{
		int fd = (int)conn->GetSockFd();
		
		if (fd >= 0)
		{
			int event = AE_READABLE | AE_WRITABLE;
			if (conn->IsListenSocket())
			{
				event  = AE_READABLE;
			}
			
			if (event & AE_READABLE)
			{
				struct kevent ke;
				EV_SET(&ke, fd, EVFILT_READ, EV_ADD | EV_CLEAR, 0, 0, (void*)conn);
				
				if (kevent(_kqueue_fd, &ke, 1, NULL, 0, NULL) == -1)
				{
					FATAL_LOG("PlatformIOThread BindSocket err: %d", errno);
					return false;
				}
			}
			
			if (event & AE_WRITABLE)
			{
				struct kevent ke;
				EV_SET(&ke, fd, EVFILT_WRITE, EV_ADD | EV_CLEAR, 0, 0, (void*)conn);
				
				if (kevent(_kqueue_fd, &ke, 1, NULL, 0, NULL) == -1)
				{
					FATAL_LOG("PlatformIOThread BindSocket err: %d", errno);
					return false;
				}
			}
		}
		
		int fd_read = conn->GetReadSockFd();
        
        if(fd_read >= 0)
        {
            struct kevent ke;
			EV_SET(&ke, fd_read, EVFILT_READ, EV_ADD | EV_CLEAR, 0, 0, (void*)conn);
			
			if (kevent(_kqueue_fd, &ke, 1, NULL, 0, NULL) == -1)
			{
				FATAL_LOG("[fd:%d, err:%d]PlatformIOThread BindSocket err: %d", fd_read, errno);
				return false;
			}
        }
		
	}
	else
	{
        FATAL_LOG("PlatformIOThread BindSocket err");
		return false;
	}

    return true;
}

bool PlatformIOThread::UnBindSocket(SockBase* conn)
{
    if (_kqueue_fd >= 0)
	{
		//epoll_event epollEventToAdd;

		int fd = (int)conn->GetSockFd();
		
		struct kevent ke;
		EV_SET(&ke, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
		EV_SET(&ke, fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
		kevent(_kqueue_fd, &ke, 1, NULL, 0, NULL);
        
	}
	else
	{
		return false;
	}

    return true;
}

extern struct NetLibParam g_param;

void PlatformIOThread::RunIO()
{
    struct kevent*  eventResults = new struct kevent[g_param._max_number_of_epoll_event];
    _last_tick_count = get_tick_count();
    struct timespec timeout;
	struct timespec* tp = NULL;
 
	timeout.tv_sec = 0;
	timeout.tv_nsec = 10 * 1000000;
	tp = &timeout;

	
	while (m_bRun)
	{
		int waitedEventNumber = kevent(_kqueue_fd, NULL, 0, eventResults, g_param._max_number_of_epoll_event, tp);
        if (!m_bRun)
        {
            break;
        }

        RunEvent();

        if (waitedEventNumber > 0)
        {
            SockBase* socketToHandle = NULL;
            for (int eventIndex = 0 ;eventIndex < waitedEventNumber; ++eventIndex)
            {
                struct kevent & currentEvent = eventResults[eventIndex];
                socketToHandle = (SockBase*)currentEvent.udata;
                if (!socketToHandle)
                {
                    continue;
                }

                if (currentEvent.filter == EVFILT_WRITE)
                {
                    if (NetlibError_None != socketToHandle->Send())
                    {
                        continue;
                    }
                }
                else if ( currentEvent.filter == EVFILT_READ)
                {
                    if (!socketToHandle->Recv(&_io_thread_data))
                    {
                        continue;
                    }
                    
                }
            }
        }
		
        RealDel();
	}
    
    delete [] eventResults;
}

void PlatformIOThread::StopIO()
{
    m_bRun = false;

    if (_close_pipe_fds[1] >= 0)
    {
        char c = 0;
        write(_close_pipe_fds[1], &c, 1);
    }

    if (_kqueue_fd >= 0)
    {
        close(_kqueue_fd);
        _kqueue_fd = -1;
    }

    join();

    if (_close_pipe_fds[0] >= 0)
    {
        close(_close_pipe_fds[0]);
        _close_pipe_fds[0] = -1;
    }

    if (_close_pipe_fds[1] >= 0)
    {
        close(_close_pipe_fds[1]);
        _close_pipe_fds[1] = -1;
    }
}

void PlatformIOThread::DelayDel(SockBase* conn)
{
    ScopedLock<PlatformMutex> lock(m_mutex);
	m_delay_set.insert(conn);
}

void PlatformIOThread::DelaySend(NetHandle h)
{
    ScopedLock<PlatformMutex> lock(_delay_send_mutex);
	_pre_delay_handle_list.push_back(h);
}

void PlatformIOThread::run_thread(const ThreadData& data)
{
	_tid = PlatformRunThread(data);
}

void PlatformIOThread::PostEvent(IOEvent& ev)
{
	ScopedLock<PlatformMutex> lock(_event_mutex);
	_event_list.push_back(ev);
}

void PlatformIOThread::join()
{
    if (_tid)
    {
        _tid->join();
        _tid.reset();
    }
}


void PlatformIOThread::RunEvent()
{
	{
		ScopedLock<PlatformMutex> lock(_event_mutex);
		_event_list_dummy.swap(_event_list);
	}
	
	for(auto& itor:_event_list_dummy)
	{
		itor._self->OnEvent(&_io_thread_data, itor._event, nullptr);
		itor._self->unref();
	}
	
	_event_list_dummy.clear();
}

void PlatformIOThread::RealDel()
{
    if (!m_delay_set.empty())
    {
        ScopedLock<PlatformMutex> lock(m_mutex);
        std::set<SockBase*>::iterator itor = m_delay_set.begin();
        for(; itor != m_delay_set.end(); itor++)
        {
            SockBase* conn = *itor;
            conn->DestroySocket();
            delete conn;
        }
        m_delay_set.clear();
    }
}

/////////////////////////////////////////////////////////
static PlatformMutex m_ioMutex;



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
	delete [] _logic_thread;
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
        uint32_t index = h % _logic_thread_size;
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
        uint32_t index = h % _logic_thread_size;
        
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

void PlatformIO::PostEvent(NetHandle h, IOEvent& ev)
{
	uint32_t index = static_cast<uint32_t>(h % _logic_thread_size);
	_logic_thread[index].PostEvent(ev);
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
    for (uint32_t i = 0; i < _logic_thread_size; i++)
    {
        _logic_thread[i].StopIO();
    }
}

void PlatformIO::DelayDel(SockBase* conn)
{
    if (!conn->IsListenSocket())
    {
        NetHandle h = conn->GetNetHandle();
        uint32_t index = h % _logic_thread_size;
        _logic_thread[index].DelayDel(conn);
    }
    else
    {
        _listen_thread.DelayDel(conn);
    }
}

void PlatformIO::DelaySend(NetHandle h)
{
    uint32_t index = h % _logic_thread_size;
    _logic_thread[index].DelaySend(h);
}

void PlatformIO::RealDel()
{
	
}
