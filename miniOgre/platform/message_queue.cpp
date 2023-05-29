#include "message_queue.h"

#include <string.h>
#include <stdlib.h>
#include <algorithm>

// static
MessageNode::Ptr MessageNode::alloc(uint32_t size)
{
    auto ptr = static_cast<MessageNode *>(malloc(sizeof(MessageNode) + size));
    if (ptr)
    {
        ptr->msg_size = size;
        ptr->on_release = &MessageNode::dealloc;
    }

    return MessageNode::Ptr(ptr);
}

// static
void MessageNode::dealloc(const MessageNode *node)
{
    free(const_cast<MessageNode *>(node));
}

MessageNode::Ptr MessageList::pop()
{
    if (!_head)
    {
        return nullptr;
    }

    MessageNode::Ptr node(_head);
    _head = _head->next;
    _size--;

    if (!_head)
    {
        _tail = &_head;
    }

    return node;
}

void MessageList::push(MessageNode::Ptr msg)
{
    // assert(msg);
    msg->next = nullptr;

    auto p = msg.release();

    *_tail = p;
    _tail = &p->next;
    _size++;
}

void MessageList::push(MessageList&& msgs)
{
    if (&msgs == this || msgs.empty())
    {
        return;
    }

    *_tail = msgs._head;
    _tail = msgs._tail;
    _size += msgs._size;

    msgs.init();
}

void MessageList::clear()
{
    while (_head)
    {
        auto node = _head;
        _head = _head->next;
        node->release();
    }

    _tail = &_head;
    _size = 0;
}

void MessageList::init()
{
    _head = nullptr;
    _tail = &_head;
    _size = 0;
}

bool MessageQueue::pop_msgs(MessageList& msgs)
{
    std::unique_lock<std::mutex> lock(_mutex);
    while (empty())
    {
        if (!_running)
        {
            return false;
        }

        _cond.wait(lock);
    }

    msgs.push(std::move(_hmsgq));
    msgs.push(std::move(_msgq));

    return true;
}

MessageNode::Ptr MessageQueue::pop_msg()
{
    std::unique_lock<std::mutex> lock(_mutex);
    while (empty())
    {
        if (!_running)
        {
            return nullptr;
        }

        _cond.wait(lock);
    }

    if (!_hmsgq.empty())
    {
        return _hmsgq.pop();
    }

    return _msgq.pop();
}

bool MessageQueue::push_msg(MessageNode::Ptr msg, bool high_priority)
{
    std::unique_lock<std::mutex> lock(_mutex);
    if (!_running)
    {
        return false;
    }

    auto&& msgq = high_priority ? _hmsgq : _msgq;
    msgq.push(std::move(msg));

    _cond.notify_one();
   
    return true;
}

void MessageQueue::wake_up()
{
    std::unique_lock<std::mutex> lock(_mutex);
    _running = false;
    _cond.notify_all();
}

void MessageQueue::clear()
{
    std::unique_lock<std::mutex> lock(_mutex);
    _hmsgq.clear();
    _msgq.clear();
}

uint32_t MessageQueue::size() const
{
    std::unique_lock<std::mutex> lock(_mutex);
    return _hmsgq.size() + _msgq.size(); 
}
