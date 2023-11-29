#pragma once

#include <sock_base.h>
#include "platform_mutex.h"

class CBuffer;

class PlatformPipe : public SockBase
{
public:
    PlatformPipe(INetSession* session, const std::string& name, bool client);
    ~PlatformPipe();

    virtual bool Recv(struct IOThredData* io_thread_data)override;

    virtual bool CreateResource() override;

    virtual int GetReadSockFd() override
    {
        return _pipe_read;
    }
    virtual bool OnInit();
    virtual bool DestroySocket(int magic) override;
    virtual int32_t Send(const uint8_t* data, uint32_t size, SndData* param);
private:
    int _fifo_read = -1;
    int _fifo_write = -1;
    int _pipe_read = -1;
    int _pipe_write = -1;
    std::string _name;
    bool _is_client;

    PlatformMutex _mutex;

    CBuffer* _send_buffer = nullptr;
    INetBuffer* _recv_buffer = nullptr;
};
