#include "platform_common.h"

#include <string.h>
#include <vector>
#include <atomic>
#include <algorithm>

#include "platform_thread.h"
#include "platform_util.h"
#include "time_util.h"

struct ModuleInformation
{
    uint32_t module_id = 0;
    module_init_func init = nullptr;
    module_entry_func entry = nullptr;
    void* user_data = nullptr;
    MessageQueue messageq;
    std::shared_ptr<Thread> thread;

    bool initialized() const { return !!this->thread; }

    void start(const char *module_name)
    {
        ThreadData data;
        data.threadfunc = ThreadPoolProc;
        data._param = this;
        data._module = this->module_id;
        strncpy(data._name, module_name, sizeof(data._name) - 1);
        this->thread = PlatformRunThread(data);
    }

    void stop()
    {
        this->messageq.wake_up();

        if (this->thread)
        {
            this->thread->join();
        }

        this->messageq.clear();
    }

    void execute(MessageNode& msg)
    {
        // assert(this->entry);
        this->entry(
            this->module_id,
            msg.msg_id,
            msg.sender,
            msg.param,
            0 == msg.msg_size ? nullptr : msg.data(),
            msg.msg_size,
            this->user_data
        );
    }

    static void ThreadPoolProc(void*  param)
    {
        auto pModule = static_cast<ModuleInformation*>(param);

        // assert(pModule);
        pModule->init();

        auto&& msgq = pModule->messageq;

        MessageList msgs;
        while (msgq.pop_msgs(msgs))
        {
            MessageNode::Ptr msg;
            while (!!(msg = msgs.pop()))
            {
                pModule->execute(*msg);
            }
        }
    }

};


class CModuleMgr : public IPlatformModule
{
public:
    enum { MAX_MODULE_NUM = 200 };

    CModuleMgr(uint32_t max_module, const char* module_name)
        : _modules(std::min(static_cast<uint32_t>(MAX_MODULE_NUM), max_module))
        , _module_name(module_name)
    {}

    bool attach_module(uint32_t moduleID , module_init_func init , module_entry_func entry, void* pModulePrivateData)
    {
        auto module = get_module(moduleID);
        if (!module)
        {
            return false;
        }

        if (module->initialized())
        {
            return false;
        }

        module->module_id = moduleID;
        module->init = init;
        module->entry  = entry;
        module->user_data = pModulePrivateData;

        return true;
    }

    bool run_module()
    {
        for (auto&& module : _modules)
        {
            module.start(_module_name.c_str());
        }

        return true;
    }

    void stop_module()
    {
        Stop();
    }

    bool post_module_message(uint32_t dstmodule, 
                             uint32_t messageid, 
                             uint64_t sender, 
                             uint64_t param, 
                             const void* message, 
                             uint32_t size, 
                             bool bIsOOB)
    {
        if (_stopped)
        {
            return false;
        }

        auto module = get_module(dstmodule);
        if (!module)
        {
            return false;
        }

        auto msg = MessageNode::alloc(size);
        if(!msg)
        {
            return false;
        }

        msg->msg_id = messageid;
        msg->sender = sender;
        msg->param = param;

        if(size > 0 && message)
        {
            char* data = (char*)msg->data();
            memmove(data, message, size);
        }

        return module->messageq.push_msg(std::move(msg), bIsOOB);
    }
    
    bool post_module_message(ServerLogic* server, IPlatformTask* task, uint32_t messageid, bool bIsOOB)
    {
        if (_stopped)
        {
            return false;
        }

        auto msg = MessageNode::alloc(0);
        if (!msg)
        {
            return false;
        }

        msg->msg_id = messageid;
        msg->sender = reinterpret_cast<uint64_t>(server);
        msg->param = reinterpret_cast<uint64_t>(task);

        uint32_t dstmodule = _module_index++ % _modules.size();
        return _modules[dstmodule].messageq.push_msg(std::move(msg), bIsOOB);
    }
    
    bool post_module_msg(uint32_t dstmodule, MessageNode::Ptr msg, bool priority)
    {
        if (_stopped)
        {
            return false;
        }

        auto module = get_module(dstmodule);
        if (!module)
        {
            return false;
        }

        return module->messageq.push_msg(std::move(msg), priority);
    }

    uint32_t get_thread_idx_of_smallest_task()
    {
        static std::atomic<uint32_t> idx{ 0 };
        return ++idx % _modules.size();
    }

    virtual uint32_t get_task_count(uint32_t dstmodule)
    {
        return _modules[dstmodule].messageq.size();
    }

    void Stop()
    {
        if (_stopped.exchange(true))
        {
            return;
        }

        for (auto&& module : _modules)
        {
            module.stop();
        }
    }
    
    void ClearMessage()
    {
        for (auto&& module : _modules)
        {
            module.messageq.clear();
        }
    }

private:
    ModuleInformation *get_module(uint32_t module_id)
    {
        if (module_id >= _modules.size())
        {
            return nullptr;
        }

        return &(_modules[module_id]);
    }

    std::vector<ModuleInformation> _modules;
    std::string _module_name;
    std::atomic<uint32_t> _module_index{ 0 };
    std::atomic_bool _stopped { false };
};

IPlatformModule* create_platform_module(uint32_t max_module, const char* module_name)
{
    return new CModuleMgr(max_module, module_name);
}

void destory_platform_module(IPlatformModule* module)
{
    module->stop_module();
    delete module;
}
