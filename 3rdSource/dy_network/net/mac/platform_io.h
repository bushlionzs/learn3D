#ifndef __PLATFORMIO_H__
#define __PLATFORMIO_H__
#include <set>
#include <vector>
#include <list>
#include <platform_mutex.h>
#include <platform_thread.h>
#include <stdint.h>
#include <net_handle.h>
#include <net_define.h>

class SockBase;

struct IOEvent
{
	uint32_t _event;
	SockBase* _self;
};

class PlatformIOThread
{
public:
    PlatformIOThread();
    ~PlatformIOThread();
    bool InitIO();
	bool BindSocket(SockBase* conn);
	bool UnBindSocket(SockBase* conn);
	void RunIO();
	void StopIO();
    void DelayDel(SockBase* conn);
    void DelaySend(NetHandle handle);
	void run_thread(const ThreadData& data);
	void PostEvent(IOEvent& ev);
    void join();
private:
    void RealDel();
    void RunEvent();
private:    
    int  _kqueue_fd;
    int _close_pipe_fds[2];
    bool m_bRun;
    struct IOThredData _io_thread_data;
    std::set<SockBase*> m_delay_set;
    std::vector<NetHandle> _pre_delay_handle_list;
    std::vector<NetHandle> _delay_handle_list;
	PlatformMutex m_mutex;
    PlatformMutex _delay_send_mutex;
    uint64_t _last_tick_count;
	std::shared_ptr<Thread> _tid;
	
	PlatformMutex _event_mutex;
	std::list<IOEvent> _event_list;
	std::list<IOEvent> _event_list_dummy;
};

class PlatformIO
{
	friend class DyNetworkContaintor;
public:
	static PlatformIO* GetInstance();
private:
	PlatformIO();
	~PlatformIO();
public:
	bool InitIO();
	bool BindSocket(SockBase* conn);
	bool UnBindSocket(SockBase* conn);
	void RunIO();
    void RunListen();
	void StopIO();
	void DelayDel(SockBase* conn);
    void DelaySend(NetHandle h);
    
    void RunThread(uint64_t index);
	void PostEvent(NetHandle h, IOEvent& ev);
private:
	void RealDel();
private:
    PlatformIOThread _listen_thread;
    PlatformIOThread* _logic_thread;
    uint64_t _logic_thread_size;
    
	std::set<SockBase*> m_delay_set;
	PlatformMutex m_mutex;
};
#endif //__PLATFORMIO_H__
