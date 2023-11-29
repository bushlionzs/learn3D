#pragma once

namespace dy_network
{
template<size_t N>
constexpr const char *ct_basename(const char *filepath)
{
    return filepath + N;
}

constexpr size_t ct_basename_pos(const char *filepath, size_t len)
{
    return (0 == len)
        ? 0
        : ('/' == filepath[len - 1] || '\\' == filepath[len - 1])
            ? len
            : ct_basename_pos(filepath, len - 1);
}
}

#define __DY_NETWORK_BASENAME__                                         \
    dy_network::ct_basename<                                            \
        dy_network::ct_basename_pos(__FILE__, sizeof(__FILE__) - 1)     \
    >(__FILE__)
