#ifndef __PLATFORM_COMMON_H__
#define __PLATFORM_COMMON_H__

#include <stdint.h>
#include "message_queue.h"

class ServerLogic;
class IPlatformTask;
typedef void (*module_init_func) (); 
typedef uint32_t (*module_entry_func)(uint32_t moduleid, 
                                    uint32_t msg_id, 
                                    uint64_t sender, 
                                    uint64_t param, 
                                    void* msg, 
                                    uint32_t msg_size, 
                                    void* pModulePrivateData);


class IPlatformModule
{
public:
    virtual ~IPlatformModule() {}
	virtual bool attach_module(uint32_t moduleid, 
                        	module_init_func init, 
                        	module_entry_func entry, 
                        	void* pModulePrivateData) = 0;
	virtual bool run_module() = 0;

	virtual bool post_module_message(uint32_t dstmodule, uint32_t messageid, 
        uint64_t sender, uint64_t param, const void* message, uint32_t size, bool bIsOOB = false) = 0;
    virtual bool post_module_message(ServerLogic* server, IPlatformTask* task, 
        uint32_t messageid, bool bIsOOB = false) = 0;

	virtual bool post_module_msg(uint32_t dstmodule, MessageNode::Ptr msg, bool priority = false) = 0;
	virtual uint32_t get_thread_idx_of_smallest_task() = 0;
    virtual uint32_t get_task_count(uint32_t dstmodule){return 0;}
    virtual void stop_module() = 0;
};

IPlatformModule* create_platform_module(uint32_t max_module, const char* module_name = "");

void destory_platform_module(IPlatformModule* module);


#endif //__PLATFORM_COMMON_H__
