#pragma once

#include <sock_base.h>
#include "platform_mutex.h"
#include "inet_session.h"
class CBuffer;

class PlatformPipe : public SockBase
{
public:
	PlatformPipe(INetSession* session, const std::string& name, bool client);
	~PlatformPipe();

	virtual bool Recv(struct IOThredData* io_thread_data)override;

	virtual bool CreateResource() override;

	virtual void* GetResource() override
	{
		return _pipe;
	}
	virtual bool OnInit();
	virtual bool OnIOBinded() override;
	virtual bool OnConnected(struct IOThredData* io_thread_data);
	virtual bool DestroySocket(int magic) override;
	virtual int32_t Send(const uint8_t* data, uint32_t size, SndData* param);
	virtual int32_t Send();
	virtual void OnSend(uint32_t ioSize);
	virtual bool RecvData(struct IOThredData* io_thread_data, OVERLAPPEDPLUS* olrecv, uint32_t size);
private:
	bool CreatePipeServer();
	bool CreatePipeClient();
private:
	HANDLE _pipe = NULL;
	std::string _name;
	bool _is_client;

	OVERLAPPEDPLUS m_olConnect;
	OVERLAPPEDPLUS m_olSend;
	OVERLAPPEDPLUS m_olRecv;

	PlatformMutex _mutex;

	

	bool _connected = false;

	CBuffer* _send_buffer = nullptr;
	INetBuffer* m_recvBuffer = nullptr;
};