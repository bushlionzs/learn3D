#include "utility/ip_stack_checker.h"

namespace dy_network
{
void IPStackChecker::set_ready(bool is_ip6_msg)
{
    if (is_ip6_msg)
    {
        this->ready.ip6 = true;
    }
    else
    {
        this->ready.ip4 = true;
    }
}

void IPStackChecker::on_response(int ip_stack_affinity, bool is_ip6_msg)
{
    set_ready(is_ip6_msg);

    int ip_stack_expect = this->ip_stack;
    if (AF_UNSPEC != ip_stack_expect)
    {
        return;
    }

    int ip_stack_msg = is_ip6_msg ? AF_INET6 : AF_INET;
    if (ip_stack_msg == ip_stack_affinity)
    {
        this->ip_stack.compare_exchange_strong(ip_stack_expect, ip_stack_msg);
    }
}

void IPStackChecker::on_timeout(int ip_stack_affinity, bool has_ip)
{
    if (!has_ip)
    {
        return;
    }

    int ip_stack_expect = this->ip_stack;
    if (AF_UNSPEC != ip_stack_expect)
    {
        return;
    }

    int ip_stack_msg = ip_stack_get_other(ip_stack_affinity);
    this->ip_stack.compare_exchange_strong(ip_stack_expect, ip_stack_msg);
}
}

