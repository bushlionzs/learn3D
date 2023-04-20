#pragma once

#include <cstdint>
#include <mutex>
#include <condition_variable>
#include <memory>

struct MessageNode
{
    MessageNode* next = nullptr;
    uint64_t sender = 0;
    uint64_t param = 0;
    uint32_t msg_id = 0;
    uint32_t msg_size = 0;
    void(*on_release)(const MessageNode *)  = nullptr;

    void* data() { return this + 1; }
    const void* data() const { return this + 1; }

    void release() const
    {
        if (on_release)
        {
            on_release(this);
        }
    }

    struct Deleter
    {
        void operator()(const MessageNode* node)
        {
            node->release();
        }
    };

    using Ptr = std::unique_ptr<MessageNode, Deleter>;

    static Ptr alloc(uint32_t size);
    static void dealloc(const MessageNode *node);

    template<typename T, typename ... Args>
    static Ptr create(Args&& ... args)
    {
        auto ptr = alloc(sizeof(T));
        if (ptr)
        {
            new (ptr->data()) T(std::forward<Args>(args)...);
            ptr->on_release = &MessageNode::destory<T>;
        }

        return ptr;
    }

    template<typename T>
    static void destory(const MessageNode *node)
    {
        if (node)
        {
            auto p = static_cast<const T *>(node->data());
            p->~T();
            dealloc(node);
        }
    }
};

class MessageList
{
public:
    MessageList() = default;
    ~MessageList() { clear(); }

    MessageNode::Ptr pop();
    void push(MessageNode::Ptr msg);
    void push(MessageList&& msgs);
    void clear();
    uint32_t size() const { return _size; }
    bool empty() const { return 0 == _size; }
private:
    void init();

    // copy disallowed
    MessageList(const MessageList&) = delete;
    void operator=(const MessageList&) = delete;

    MessageNode* _head = nullptr;
    MessageNode** _tail = &_head;
    uint32_t _size = 0;
};

class MessageQueue
{
public:
    bool pop_msgs(MessageList& msgs);
    MessageNode::Ptr pop_msg();
    bool push_msg(MessageNode::Ptr msg, bool high_priority = false);
    void wake_up();
    void clear();
    uint32_t size() const;
private:
    bool empty() const { return _hmsgq.empty() && _msgq.empty(); }

    MessageList _hmsgq;
    MessageList _msgq;

    mutable std::mutex _mutex;
    std::condition_variable _cond;
    bool _running = true;
};
