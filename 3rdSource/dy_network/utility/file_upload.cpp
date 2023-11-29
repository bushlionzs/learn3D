#include "file_upload.h"
#include "server_interface.h"
#include "server_def.h"
#include "net_factory.h"
#include "http_session.h"
#include "platform_common.h"
#include "platform_log.h"
#include "platform_util.h"
#include "rc_object.h"
#include "string_util.h"
#include "http_defines.h"
#include "dy_dns.h"
#include "url.h"
#include <stdio.h>
#include <mutex>

static IPlatformModule* _upload_module = nullptr;
static std::mutex _upload_mutex;

static void upload_init()
{
}


static uint32_t upload_entry(uint32_t moduleid, uint32_t msg_id, uint64_t sender, uint64_t param, void* msg, uint32_t msg_size, void* pNetThreadData);

static void create_upload_module()
{
    if (_upload_module == nullptr)
    {
        std::unique_lock<std::mutex> lock(_upload_mutex);
        if (_upload_module == nullptr)
        {
            _upload_module = create_platform_module(1, "upload");
            _upload_module->attach_module(0, upload_init, upload_entry, nullptr);
            _upload_module->run_module();
        }
    }
}

class FileUpload : public IServerInterface, public ReferenceObject
{
private:
    std::string _url;
    std::string _filename;
    std::string _host;
    uint16_t _url_port;
    void (*_upload_callback)(int32_t code, const std::string& name, uint64_t size, void* param);
    mutable std::mutex _mutex;
    std::condition_variable _cond;
    INetSession* _http_session;
    INetSession* _http_ssl_session;
    NetHandle _upload_handle = INVALID_NET_HANDLE;
    platform_timer_t _upload_timer = INVALID_TIMER_ID;
    FILE* _upload_file = nullptr;
    uint32_t _file_size = 0;
    std::string _formtail;
    std::string _cache;
    uint32_t _cache_capacity = 1024 * 5;
    int32_t _cache_size = 0;
    bool _block = false;
    int32_t _upload_code = -1;
    bool _ssl = false;
    void* _usr_data = nullptr;
public:
FileUpload(
    const std::string& url, 
    const std::string& filename,
    void (*upload_callback)(int32_t code, const std::string& name, uint64_t size, void* param), void* usr_data)
{
    _url = url;
    _filename = filename;
    _upload_callback = upload_callback;
    _usr_data = usr_data;
    _http_session = new HttpSession(this, false, false, true);
    _http_ssl_session = new HttpSession(this, true, false, true);

    create_upload_module();
}


~FileUpload()
{
    delete _http_session;
    delete _http_ssl_session;

    if (_upload_file != nullptr)
    {
        fclose(_upload_file);
    }
}

void run(bool block)
{
    _block = block;
    std::unique_lock<std::mutex> lock(_mutex);
    _upload_module->post_module_message(0, NetMsg_Custom, (uint64_t)this, 0, nullptr, 0);
    
    if (_block)
    {
        _cond.wait(lock);
    }
}


void on_release()
{
    if (_block)
    {
        _cond.notify_one();
    }
    else
    {
        if (_upload_callback)
        {
            _upload_callback(_upload_code, _filename, _file_size, _usr_data);
        }
        unref();
    }
}

void on_close()
{
    terminate();
}

static int32_t upload_timer_callback(platform_timer_t, void* timer_self, void* timer_param)
{
    _upload_module->post_module_message(0, NetMsg_Timer, (uint64_t)timer_self, (uint64_t)timer_param, nullptr, 0);
    return 0;
}



void on_connected()
{
    _file_size = 0;
    if (_upload_file == nullptr)
    {
        _upload_file = fopen(_filename.c_str(), "rb");

        if (_upload_file == nullptr)
        {
            NetFactory::GetInstance()->CloseNetHandle(_upload_handle);
            return;
        }

        fseek(_upload_file, 0, SEEK_END);
        _file_size = ftell(_upload_file);
        fseek(_upload_file, 0, SEEK_SET);
    }

    std::string formheader = "--------------------------5dfedf0d8e488a44\r\n";
    formheader += "Content-Disposition: form-data; name=\"filename\"; filename=\"";
    formheader += dy::get_short_name(_filename);
    formheader += "\"\r\n";
    formheader += "Content-Type: application/octet-stream\r\n\r\n";

    _formtail = "\r\n--------------------------5dfedf0d8e488a44--\r\n";

    std::string httpheader = "POST /upload HTTP/1.1\r\n";
    httpheader += dy::str_format("Host: %s:%d\r\n", _host.c_str(), _url_port);
    httpheader += "User-Agent: curl/8.0.1\r\n";
    httpheader += "Accept: */*\r\n";
    httpheader += dy::str_format("Content-Length: %d\r\n", formheader.size() + _formtail.size() + _file_size);
    httpheader += "Content-Type: multipart/form-data; boundary=------------------------5dfedf0d8e488a44\r\n\r\n";

    httpheader += formheader;

    _cache.resize(_cache_capacity);

    memcpy((void*)_cache.data(), httpheader.c_str(), httpheader.size());
    _cache_size = httpheader.size();

    _upload_timer = platform_create_timer(10, upload_timer_callback, this, nullptr);

    ref();
}

void upload_file()
{
    if (_cache_size)
    {
        int32_t ret = NetFactory::GetInstance()->SendData(_upload_handle, (const uint8_t*)_cache.data(), _cache_size);
        if (ret == 0)
        {
            _cache_size = 0;
        }
        else
        {
            if (ret != NetlibError_BufferError)
            {
                WARNING_LOG("upload error, ret:%d", ret);
                terminate();
            }
            return;
        }
    }

    if (_upload_file)
    {
        _cache_size = fread((void*)_cache.data(), 1, _cache_capacity, _upload_file);

        if (_cache_size < 0)
        {
            fclose(_upload_file);
            _upload_file = nullptr;
            terminate();
            return;
        }

        if (_cache_size == 0)
        {
            fclose(_upload_file);
            _upload_file = nullptr;
            memcpy((void*)_cache.data(), _formtail.c_str(), _formtail.size());
            _cache_size = _formtail.size();
        }
    }

    
}

void terminate()
{
    if (_upload_timer != INVALID_TIMER_ID)
    {
        if (platform_delete_timer(_upload_timer))
        {
            unref();
        }

        _upload_timer = INVALID_TIMER_ID;
    }
    
    if (_upload_handle != INVALID_NET_HANDLE)
    {
        NetFactory::GetInstance()->CloseNetHandle(_upload_handle);
        _upload_handle = INVALID_NET_HANDLE;
    }
}

int process_network_message(uint32_t msg_id, const uint8_t* data, uint32_t size)
{
    switch (msg_id)
    {
    case NetMsg_HttpReponse_StatusLine:
    {
        HTTPStatusLine* status_line_copy = *((HTTPStatusLine**)data);
        if (status_line_copy->status_code == 200)
        {
            _upload_code = 0;
        }
        delete status_line_copy;
    }
    break;
    case NetMsg_HttpReponse_Headers:
    {
        HTTPHeaders* headers_copy = *((HTTPHeaders**)data);
        delete headers_copy;
    }
    break;
    case NetMsg_HttpDataResponse:
        terminate();
        break;
    case NetMsg_Timer:
        upload_file();
        break;
    case NetMsg_Close:
        on_close();
        break;
    case NetMsg_Session_Release:
        on_release();
        break;
    case NetMsg_Connected:
    {
        on_connected();
    }
    break;
    case NetMsg_Custom:
        pre_connect();
        break;
    break;
    default:
        break;
    }

    return 0;
}

void dns_result(const std::string& ip)
{
    tcp_connect(ip, _url_port, _ssl);
}

private:
    static void upload_dns_callback(dy_dns_t* dummy)
    {
        FileUpload* fl = (FileUpload*)dummy->_user_data;
        
        if (dummy->_ip_list.empty())
        {
            fl->on_release();
        }
        else
        {
            fl->dns_result(dummy->_ip_list.front());
        }

        fl->unref();
    }
    void pre_connect()
    {
        string_view schema, hostport, uri;
        string_view host;
        if (!util::parse_url(_url, &schema, &hostport, &uri))
        {
            goto error;
        }


        if (!util::split_host_port(hostport, &host, &_url_port))
        {
            goto error;
        }

        if (schema == "https")
        {
            _ssl = true;
        }

        _host = host.to_string();

        if (!util::is_ipv4(host))
        {
            ref();
            dns_resolve(host.to_string(), upload_dns_callback, this);
        }

        tcp_connect(host.to_string(), _url_port, _ssl);
        return;
    error:
        on_release();
    }



void tcp_connect(const std::string& ip, uint16_t port, bool ssl)
{
    SessionData sessionData;
    sessionData.m_PeerIP = ip;
    sessionData.m_PeerPort = port;
    INetSession* net_session = nullptr;

    if (ssl)
    {
        net_session = _http_ssl_session;
    }
    else
    {
        net_session = _http_session;
    }

    _upload_handle = NetFactory::GetInstance()->CreateTcpConnection(net_session, sessionData);

    if (_upload_handle == INVALID_NET_HANDLE)
    {
        on_release();
    }
}


virtual int post_network_message(uint32_t msg_id, uint64_t param, const uint8_t* data, uint32_t size) override
{
    _upload_module->post_module_message(0, msg_id, (uint64_t)this, param, data, size);
    return 0;
}
};


static uint32_t upload_entry(uint32_t moduleid, uint32_t msg_id, uint64_t sender, uint64_t param, void* msg, uint32_t msg_size, void* pNetThreadData)
{
    FileUpload* upload = (FileUpload*)sender;
    upload->process_network_message(msg_id, (const uint8_t*)msg, msg_size);
    return 0;
}

void syncUploadFile(const std::string& url, const std::string& filename)
{
    FileUpload* upload = new FileUpload(url, filename, nullptr, nullptr);
    upload->run(true);
    upload->unref();
}


void asyncUploadFile(
	const std::string& url,
	const std::string& filename,
    void (*upload_callback)(int32_t code, const std::string& name, uint64_t size, void* param), void* usr_data)
{
    FileUpload* upload = new FileUpload(url, filename, upload_callback, usr_data);
    upload->run(false);
}