#include <string.h>
#include <vector>
#include <http_client.h>
#include <platform_util.h>
#include <platform_log.h>
#include <time_util.h>
#include <common_base64.h>
#include <encryt_util.h>
#include <url.h>
#include <scoped_lock.h>
#include <fstream>


#include "url_fetcher.h"


class FetcherHttpHandler : public HTTPClientHandler
{
public:
    FetcherHttpHandler(UrlFetcher* fetcher)
    {
        _fetcher = fetcher;
    }
    virtual int32_t on_http_event(IHttpClient*, const HTTPClientCtx& ctx, eHttpEvent event)
    {
        return _fetcher->process_http_event(ctx, event);
    }
    virtual int32_t on_http_data(IHttpClient*, const HTTPClientCtx& ctx, const char* data, uint32_t size)
    {
        return _fetcher->process_http_response(ctx, data, size);
    }

    virtual void on_http_release(IHttpClient*)
    {
        _fetcher->release();
    }
private:
    UrlFetcher* _fetcher;
};




UrlFetcher::UrlFetcher(fn_on_got_tracker_info cb)
{
    _cb = cb;
    _fetcher_state = url_fetcher_state::url_fetcher_init;
    
    HTTPClientConfig config;
    config.continue_data = false;
    _http_client = create_http_client(
        config, 
        new FetcherHttpHandler(this));
}

UrlFetcher::~UrlFetcher()
{
  
}


int32_t UrlFetcher::process_http_response(const HTTPClientCtx& ctx, const char* data, uint32_t size)
{
    int32_t ret = parse_get_url_response(data, size);

    SCOPE_LOCK_MACRO(_fetcher_mutex);
    if (_fetcher_state >= url_fetcher_state::url_fetch_http_client_close)
    {
        NOTICE_LOG("http client has stoped.");
        return 0;
    }

    _fetcher_state = url_fetcher_state::url_fetch_http_client_response;

    if (ret == 0)
    {
        _cb(RETCODE::ET_OK);
        close();
    }

    return ret;
}

int32_t UrlFetcher::parse_get_url_response(const char* data, uint32_t size)
{
    _url_result.append(data, size);
    return 0;
}


static RETCODE http_event_to_error_code(eHttpEvent event)
{
    switch (event)
    {
    case HTTP_EVENT_CONNECTED:
        return RETCODE::ET_OK;
    case HTTP_EVENT_CLOSE:
        return RETCODE::ET_URL_FETCHER_CONNECTION_CLOSE;

    case HTTP_EVENT_TIMEOUT:
        return RETCODE::ET_URL_FETCHER_RESPONSE_TIMEOUT;

    case HTTP_DNS_ERROR:
        return RETCODE::ET_URL_FETCHER_DNS_ERROR;

    case HTTP_302_ERROR:
        return RETCODE::ET_URL_FETCHER_302_ERROR;
    }

    return RETCODE::ET_OK;
}

int32_t UrlFetcher::process_http_event(const HTTPClientCtx& ctx, eHttpEvent event)
{
    switch (event)
    {
    case HTTP_EVENT_CLOSE:
    case HTTP_EVENT_TIMEOUT:
    case HTTP_DNS_ERROR:
        _cb(http_event_to_error_code(event));
        WARNING_LOG("[event:%d,url:%s]url fetcher failed", (int)event, _http_url.c_str());
        this->set_fetcher_state(url_fetcher_state::url_fetcher_init);
        break;
    }
   
    return 0;
}


const std::string& UrlFetcher::get_fetcher_result()
{
    return _url_result;
}

void UrlFetcher::close()
{
    _http_client->close();
}

void UrlFetcher::release()
{
    set_fetcher_state(url_fetcher_state::url_fetch_http_client_destory);
    delete this;
}

bool UrlFetcher::stop()
{
    set_fetcher_state(url_fetcher_state::url_fetch_http_client_close);
    auto p = _http_client;
    _http_client = NULL;
    release_http_client(p);

    return true;
}

int32_t UrlFetcher::get_url(const char* api_url, std::map<std::string, std::string>* http_header)
{
    if (!check_fetcher_state())
    {
        return (int32_t)RETCODE::ET_URL_FETCHER_IS_RUNNING;
    }

    set_fetcher_state(url_fetcher_state::url_fetch_http_client_request);

 
    _http_url = api_url;

    _url_result.clear();
    _http_client->http_get(_http_url, 3000, http_header);
    return 0;
}


int32_t UrlFetcher::post_url(const char* api_url,
    std::map<std::string, std::string>* http_header,
    const std::string* body)
{
    if (!check_fetcher_state())
    {
        return (int32_t)RETCODE::ET_URL_FETCHER_IS_RUNNING;
    }

    set_fetcher_state(url_fetcher_state::url_fetch_http_client_request);


    _http_url = api_url;
    _url_result.clear();
    _http_client->http_post(_http_url, body->data(), body->size(), 3000, http_header);
    return 0;
}

bool UrlFetcher::check_fetcher_state()
{
    SCOPE_LOCK_MACRO(_fetcher_mutex);
    return _fetcher_state == url_fetcher_state::url_fetcher_init || _fetcher_state == url_fetcher_state::url_fetch_http_client_destory;
}

void UrlFetcher::set_fetcher_state(url_fetcher_state state)
{
    SCOPE_LOCK_MACRO(_fetcher_mutex);
    _fetcher_state = state;
}
