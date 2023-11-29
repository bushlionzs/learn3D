#ifndef __BASE_TASK_H__
#define __BASE_TASK_H__
#include <stdint.h>
class ServerLogic;
class IPlatformTask
{
public:
    IPlatformTask(){}
    virtual ~IPlatformTask(){}
public:
    virtual bool run(ServerLogic* server, uint32_t moduleid, uint32_t msgid) = 0;
};

#endif //__BASE_TASK_H__