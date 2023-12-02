#include "net_context.h"
#include "client_message.pb.h"
#include "net_message_manager.h"
#include "net_factory.h"

NetContext::NetContext()
{

}

NetContext::~NetContext()
{

}

void NetContext::OnConnected(NetHandle h, const session_info_t& data, void* pNetThreadData)
{
	login();
}

void NetContext::OnClose(NetHandle h, const session_info_t& data, void* pNetThreadData)
{

}


int NetContext::process_message(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData)
{
	NetMessageManager::GetSingleton().dispatchMessage(handle, msg, msg_size);
	return 0;
}


void NetContext::OnAfterInit()
{
	SessionData data;
	data.m_PeerIP = "127.0.0.1";
	data.m_PeerPort = 8888;
	_client_handle = NetFactory::GetInstance()->CreateTcpConnection((INetSession*)_net_session, data);
}

void NetContext::login()
{
	clientmessage::MsgLogin dummy;
	dummy.set_username("");
	dummy.set_passwd("");

	NetMessageManager::GetSingletonPtr()->sendNetMessage(_client_handle, clientmessage::CS_LOGIN, &dummy);
}