#ifndef __PLATFORMIO_H__
#define __PLATFORMIO_H__
#include <set>
#include <vector>
#include <net_handle.h>
#include <net_define.h>
#include <scoped_lock.h>
#include <platform_mutex.h>
#include <platform_thread.h>
class SockBase;

class PlatformIOThread
{
public:
	PlatformIOThread();
	~PlatformIOThread();
	bool InitIO();
	bool BindSocket(SockBase* conn);
	bool UnBindSocket(SockBase* conn);
	void PostEvent(OVERLAPPED* dummy);

	void RunIO();
	void StopIO();
	void DelayDel(SockBase* conn);
	void DelaySend(NetHandle handle);

    void waitDel(SockBase* conn);
    void doWaitDel();

    void run_thread(const ThreadData& data);

    void join();
private:
	void RealDel();
	void DelaySend();
private:
	void*  _completion_port;
	bool _run;
	struct IOThredData _io_thread_data;
	PlatformMutex _mutex;
	uint64_t _last_tick_count;
    std::shared_ptr<Thread> _tid;
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

	void RunThread(uint64_t index);

	void PostEvent(NetHandle h, OVERLAPPED* dummy);

private:
	PlatformIOThread _listen_thread;
	PlatformIOThread* _logic_thread;
	uint64_t _logic_thread_size;

	PlatformMutex _mutex;
};

#endif //__PLATFORMIO_H__