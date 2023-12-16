#include "net_speed.h"
#include "platform_thread.h"
#include "platform_signal.h"
#include "net_factory.h"
#include "inet_session.h"
#include "http_client.h"
#include "platform_log.h"
#include "time_util.h"
#include "recv_buffer.h"
class NetSpeedSession;
static int32_t my_http_event_callback_func(IHttpClient* httpclient, const HTTPClientCtx& ctx, eHttpEvent event);
static int32_t my_http_data_callback_func(IHttpClient* httpclient, const HTTPClientCtx& ctx, const char* data, uint32_t size);
static void my_http_data_release_func(IHttpClient* httpclient);

class NetSpeedHandler : public HTTPClientHandler
{
public:
	NetSpeedHandler(NetSpeedSession* nss)
	{
		_nss = nss;
	}
	virtual int32_t on_http_event(IHttpClient* c, const HTTPClientCtx& ctx, eHttpEvent event);

	
	virtual int32_t on_http_data(IHttpClient* c, const HTTPClientCtx& ctx, const char* data, uint32_t size);

	virtual void on_http_release(IHttpClient*);
private:
	NetSpeedSession* _nss;
};

class NetSpeedSession : public INetSession
{
public:
	NetSpeedSession(NetSpeed& ns, void (*net_speed_callback)(NetSpeed*, void*), void* param) :_ns(ns)
	{
		_net_speed_callback = net_speed_callback;
		_param = param;
	}
	virtual void on_send_bytes(NetHandle h, const SessionData&, uint64_t total) override
	{
	}

	virtual uint32_t get_send_buffer_size(const SessionData&) override
	{
		return 1024 * 1024 * 5;
	}

	virtual INetBuffer* create_recv_buffer(const SessionData&) override
	{
		return (INetBuffer*)new RecvBuffer(nullptr, 1024 * 16, false);
	}

	virtual void OnClose(NetHandle, const SessionData&) override
	{
		_upload_connected = false;
	}

	virtual void OnConnected(NetHandle, const SessionData&) override
	{
		_upload_connected = true;
	}

	virtual void on_release(NetHandle, const SessionData&)
	{
		finish();
		delete  this;
	}

	void notify()
	{
		_cond.notify_one();
	}

	void wait(std::unique_lock<std::mutex>& lock)
	{
		_cond.wait(lock);
	}

	void download()
	{
		HTTPClientConfig httpconfig;
		httpconfig.continue_data = true;

		NetSpeedHandler* handler = new NetSpeedHandler(this);
		IHttpClient* hc = create_http_client(
			httpconfig,
			handler);

		std::unique_lock<std::mutex> lock(_mutex);
		hc->http_get(_ns._download_url, 3000, nullptr, nullptr);

		wait(lock);

		release_http_client(hc);
	}

	void download_begin()
	{
		_ns._download_time = get_tick_count();
		_ns._download_bandwidth = 0;
	}

	void download_data(uint32_t size)
	{
		_ns._download_bandwidth += size;
		if (size == 0)
		{
			_ns._download_time = get_tick_count() - _ns._download_time;
			if (_ns._download_time > 0)
			{
				_ns._download_bandwidth = _ns._download_bandwidth / (_ns._download_time / 1000.0f);
				_ns._download_success = true;
			}
			download_finish(true);
		}
	}
	void download_finish(bool sucess)
	{
		
	}
	void upload()
	{
		SessionData sd;
		sd.m_PeerIP = _ns._upload_ip;
		sd.m_PeerPort = _ns._upload_port;
		NetHandle h = NetFactory::GetInstance()->CreateTcpConnection(this, sd);

		uint64_t current = get_tick_count();
		uint64_t last = current + _ns._upload_time;

		std::string mem;
		mem.resize(1024 * 1024);
		while (current < last)
		{
			if (!_upload_connected)
			{
				cross_sleep(10);
				current = get_tick_count();
				continue;
			}

			
			int32_t ret = NetFactory::GetInstance()->SendData(h, (const uint8_t*)mem.c_str(), mem.size(), nullptr);

			if (ret == NetlibError_BufferError)
			{
				cross_sleep(10);
				current = get_tick_count();
			}
			else
			{
				_upload_bytes += mem.size();
			}

			if (!_upload_connected)
				break;
		}

		_ns._upload_bandwidth = _upload_bytes / (_ns._upload_time / 1000.0f);

		if (_upload_connected && _upload_bytes > 0)
		{
			_ns._upload_success = true;
		}

		NetFactory::GetInstance()->DisconnectHandle(h);
	}

	void finish()
	{
		_net_speed_callback(&_ns, _param);
	}
private:
	mutable std::mutex _mutex;
	std::condition_variable _cond;
	NetSpeed _ns;
	void (*_net_speed_callback)(NetSpeed*, void*);
	void* _param;
	bool _upload_connected = false;

	uint64_t _upload_bytes = 0;
};

static int32_t my_http_event_callback_func(IHttpClient* httpclient, const HTTPClientCtx& ctx, eHttpEvent event)
{
	if (event == HTTP_EVENT_CONNECTED)
	{
		NetSpeedSession* nss = (NetSpeedSession*)httpclient->get_user_data();
		nss->download_begin();
	}
	else if (event == HTTP_EVENT_TIMEOUT)
	{
		NetSpeedSession* nss = (NetSpeedSession*)httpclient->get_user_data();
		httpclient->close();
		nss->notify();
	}
	else if (event == HTTP_EVENT_CLOSE)
	{
		NetSpeedSession* nss = (NetSpeedSession*)httpclient->get_user_data();
		nss->notify();
	}
	else if (event == HTTP_DNS_ERROR)
	{
		NetSpeedSession* nss = (NetSpeedSession*)httpclient->get_user_data();
		nss->notify();
	}
	return 0;
}

static int32_t my_http_data_callback_func(IHttpClient* httpclient, const HTTPClientCtx& ctx, const char* data, uint32_t size)
{
	if (ctx.response_status_code != 200)
	{
		std::string content;
		content.assign(data, size);
		WARNING_LOG("clk log response error, code:%d, content:%s", ctx.response_status_code, content.c_str());
		httpclient->close();

		NetSpeedSession* nss = (NetSpeedSession*)httpclient->get_user_data();
		nss->download_finish(-1);
		return 0;
	}

	NetSpeedSession* nss = (NetSpeedSession*)httpclient->get_user_data();
	nss->download_data(size);

	if (size == 0)
	{
		httpclient->close();
	}
	
	return 0;
}

static void my_http_data_release_func(IHttpClient* httpclient)
{
	NOTICE_LOG("net_speed_download_release\n");
}

void net_speed_func(void* param)
{
	NetSpeedSession* nss = (NetSpeedSession*)param;
	nss->download();
	nss->upload();
}


bool net_speed_start(
	const std::string& download_url,
	const std::string& upload_ip,
	uint16_t upload_port,
	uint32_t upload_time,
	void (*net_speed_callback)(NetSpeed*, void*), void*param)
{
	ThreadData data;
	strcpy(data._name, "net_speed");
	NetSpeed ns;
	ns._download_url = download_url;
	ns._upload_ip = upload_ip;
	ns._upload_port = upload_port;
	ns._upload_time = upload_time;
	data.threadfunc = net_speed_func;
	data._param = new NetSpeedSession(ns, net_speed_callback, param);
	auto td =  PlatformRunThread(data);
	td->detach();
	return true;
}


int32_t NetSpeedHandler::on_http_event(IHttpClient* c, const HTTPClientCtx& ctx, eHttpEvent event)
{
	if (event == HTTP_EVENT_CONNECTED)
	{
		_nss->download_begin();
	}
	else if (event == HTTP_EVENT_TIMEOUT)
	{
		c->close();
		_nss->notify();
	}
	else if (event == HTTP_EVENT_CLOSE)
	{
		_nss->notify();
	}
	else if (event == HTTP_DNS_ERROR)
	{
		_nss->notify();
	}
	return 0;
}


int32_t NetSpeedHandler::on_http_data(IHttpClient* c, const HTTPClientCtx& ctx, const char* data, uint32_t size)
{
	if (ctx.response_status_code != 200)
	{
		std::string content;
		content.assign(data, size);
		WARNING_LOG("clk log response error, code:%d, content:%s", ctx.response_status_code, content.c_str());
		c->close();

		_nss->download_finish(-1);
		return 0;
	}

	_nss->download_data(size);

	if (size == 0)
	{
		c->close();
	}

	return 0;
}

void NetSpeedHandler::on_http_release(IHttpClient*)
{
}