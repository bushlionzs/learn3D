#pragma once
#include "server_logic.h"

class NetContext : public ServerLogic
{
public:
	NetContext();
	~NetContext();

	virtual void OnConnected(NetHandle h, const session_info_t& data, void* pNetThreadData)override;
	virtual void OnClose(NetHandle h, const session_info_t& data, void* pNetThreadData)override;
	virtual int process_message(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData) override;

	virtual void OnAfterInit() override;
private:
	void login();
private:
	NetHandle _client_handle = INVALID_NET_HANDLE;
};