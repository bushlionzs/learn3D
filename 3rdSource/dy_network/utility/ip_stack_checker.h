#pragma once

#include <atomic>

#include "net_helper.h"

namespace dy_network
{

template<typename T>
struct IPStackPair
{
    T ip4;
    T ip6;

    T *get(int family) noexcept
    {
        if (AF_INET == family)
        {
            return &this->ip4;
        }

        if (AF_INET6 == family)
        {
            return &this->ip6;
        }

        return nullptr;
    }

    const T *get(int family) const noexcept
    {
        return const_cast<IPStackPair<T> *>(this)->get(family);
    }
};

struct IPStackChecker
{
    IPStackPair<bool> ready = { false, false };
    std::atomic<int> ip_stack{ AF_UNSPEC };

    void set_ready(bool is_ip6_msg);
    void on_response(int ip_stack_affinity, bool is_ip6_msg);
    void on_timeout(int ip_stack_affinity, bool has_ip);
};

constexpr int ip_stack_get_other(int ip_stack)
{
    return (AF_INET == ip_stack) ? AF_INET6 : ((AF_INET6 == ip_stack) ? AF_INET : ip_stack);
}

}


