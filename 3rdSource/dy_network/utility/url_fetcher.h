#pragma once
#include <stdint.h>
#include <string>
#include <dy_dns.h>
#include <platform_mutex.h>
#include <platform_signal.h>
#include <http_client.h>
#include <functional>
#include "url_error_code.h"


enum class url_fetcher_state : uint32_t
{
    url_fetcher_init = 0,
    url_fetch_http_client_request,
    url_fetch_http_client_response,
    url_fetch_http_client_close,
    url_fetch_http_client_destory,
};

enum
{
    kParseUrlOk = 0,
    kParseUrlNoMustField = -1,
    kParseUrlDecryptError = -2,
    kParseUrlBadJson = -3,
    kParseUrlNoTracker = -4,
    kParseUrlResolveingTrackerHost = 1,
};

using fn_on_got_tracker_info = std::function<void(RETCODE)>;

class UrlFetcher
{
public:
    UrlFetcher(fn_on_got_tracker_info cb);
    ~UrlFetcher();
    int32_t get_url(const char* api_url, std::map<std::string, std::string>* http_header = nullptr);
    int32_t post_url(const char* api_url,
        std::map<std::string, std::string>* http_header = nullptr,
        const std::string* body = nullptr);
    int32_t process_http_response(const HTTPClientCtx& ctx, const char* data, uint32_t size);
    int32_t process_http_event(const HTTPClientCtx& ctx, eHttpEvent event);
    const std::string& get_fetcher_result();
    void close();
    void release();
    bool stop();
private:
    int32_t parse_get_url_response(const char* data, uint32_t size);
    bool check_fetcher_state();
    void set_fetcher_state(url_fetcher_state state);
private:
    fn_on_got_tracker_info _cb;
    std::string _http_url;
    std::string _url_result;

    url_fetcher_state _fetcher_state;
    PlatformMutex _fetcher_mutex;
    PlatformCond _fetcher_signal;
    IHttpClient* _http_client;
};

#define URL_ERROR_NEED_RETRY(err)                           \
        ((err) >= RETCODE::ET_URL_FETCHER_IS_RUNNING        \
        && (err) <= RETCODE::ET_URL_FETCHER_302_ERROR       \
        && (err) != RETCODE::ET_URL_FETCHER_STATUS_ERROR)
