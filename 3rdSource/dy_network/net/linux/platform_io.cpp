#define THIS_MODULE MODULE_NETWORK
/* C standard header file */
#include <stdint.h>
#include <sys/time.h>
/* Linux system header file */
#include <unistd.h>
#include <sys/epoll.h>
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
    m_EpollFd = -1;
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

    m_EpollFd = epoll_create(1);

    if (-1 == this->m_EpollFd)
    {
        return false;
    }

    if (pipe(_close_pipe_fds) < 0)
    {
        return false;
    }

    struct epoll_event e;
    e.events = EPOLLIN;
    e.data.ptr = NULL;
    if (epoll_ctl(m_EpollFd, EPOLL_CTL_ADD, _close_pipe_fds[0], &e) < 0)
    {
        return false;
    }

    _io_thread_data.init(g_param._max_recv_buffer_size);
    m_bRun = true;

    return true;
}

bool PlatformIOThread::BindSocket(SockBase* conn)
{
    if (m_EpollFd >= 0)
    {
        epoll_event epollEventToAdd;
        

        int fdToAdd = conn->GetSockFd();
        
        if(fdToAdd >= 0)
        {
            epollEventToAdd.data.ptr = conn;

            if (conn->IsListenSocket())
            {
                epollEventToAdd.events  = EPOLLIN;
            }
            else
            {
                epollEventToAdd.events  = EPOLLIN | EPOLLOUT | EPOLLET;
            }

            if (0 == epoll_ctl(m_EpollFd, EPOLL_CTL_ADD, fdToAdd, &epollEventToAdd))
            {
                return true;
            } 
            else
            {
                FATAL_LOG("PlatformIOThread BindSocket err: %d", errno);
                return false;
            }
        }
        
        int fd_read = conn->GetReadSockFd();
        
        if(fd_read >= 0)
        {
            epollEventToAdd.data.ptr = conn;

            epollEventToAdd.events  = EPOLLIN | EPOLLET;

            if (0 == epoll_ctl(m_EpollFd, EPOLL_CTL_ADD, fd_read, &epollEventToAdd))
            {
                return true;
            } 
            else
            {
                FATAL_LOG("PlatformIOThread BindSocket Read err: %d", errno);
                return false;
            }
        }
		return true;
    }
    else
    {
        FATAL_LOG("epoll err");
        return false;
    }
}

bool PlatformIOThread::UnBindSocket(SockBase* conn)
{
    if (m_EpollFd >= 0)
    {
        epoll_event epollEventToAdd;

        int fdToAdd = (int)conn->GetSockFd();
        
        if(fdToAdd >= 0)
        {
            if (0 == epoll_ctl(m_EpollFd, EPOLL_CTL_DEL, fdToAdd, &epollEventToAdd))
            {
                return true;
            } 
            else
            {
                return false;
            }
        }
        
        
        int fd_read = conn->GetReadSockFd();
        
        if(fd_read >= 0)
        {
            if (0 == epoll_ctl(m_EpollFd, EPOLL_CTL_DEL, fd_read, &epollEventToAdd))
            {
                return true;
            } 
            else
            {
                return false;
            }
        }
        
        int fd_write = conn->GetReadSockFd();
        
        if(fd_write >= 0)
        {
            if (0 == epoll_ctl(m_EpollFd, EPOLL_CTL_DEL, fd_write, &epollEventToAdd))
            {
                return true;
            } 
            else
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

extern struct NetLibParam g_param;

void PlatformIOThread::RunIO()
{
    epoll_event* eventResults = new epoll_event[g_param._max_number_of_epoll_event];
    int32_t duration = 10;
    
    while (m_bRun)
    {
        int waitedEventNumber = epoll_wait(this->m_EpollFd, eventResults, g_param._max_number_of_epoll_event, duration);
        if (!m_bRun)
        {
            break;
        }

        if (waitedEventNumber > 0)
        {
            SockBase* socketToHandle = NULL;
            for (int eventIndex = 0 ;eventIndex < waitedEventNumber; ++eventIndex)
            {
                epoll_event& currentEvent = eventResults[eventIndex];
                socketToHandle = (SockBase*)currentEvent.data.ptr;
                if (!socketToHandle)
                {
                    continue;
                }

                if (currentEvent.events & EPOLLOUT)
                {
                    if (NetlibError_None != socketToHandle->Send())
                    {
                        continue;
                    }
                }
                
                if ( 
                     (currentEvent.events & EPOLLIN) ||
                     (currentEvent.events & EPOLLPRI)
                   )
                {
                    if (!socketToHandle->Recv(&_io_thread_data))
                    {
                        continue;
                    }
                }
            }
        }
		
		RunEvent();
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

    if (m_EpollFd >= 0)
    {
        close(m_EpollFd);
        m_EpollFd = -1;
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
