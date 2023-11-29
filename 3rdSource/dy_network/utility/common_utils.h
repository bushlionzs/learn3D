#pragma once

#include <memory>
#include <type_traits>

namespace dy_network
{

template<
    typename T, 
    typename ... Args,
    typename std::enable_if<!std::is_array<T>::value, int>::type = 0
>
inline std::unique_ptr<T> wrap_unique(Args&&... args)
{
    return (std::unique_ptr<T>(new T(std::forward<Args>(args)...)));
}

template<
    typename T,
    typename std::enable_if<std::is_array<T>::value && std::extent<T>::value == 0, int>::type = 0
>
inline std::unique_ptr<T> wrap_unique(size_t size)
{
    using Elem = typename std::remove_extent<T>::type;
    return std::unique_ptr<T>(new Elem[size]);
}

template<
    typename T,
    typename ... Args,
    typename std::enable_if<std::extent<T>::value != 0, int>::type = 0
>
void make_unique(Args &&...) = delete;

template<typename C, typename K>
bool c_exist(const C& container, K&& key)
{
    return container.find(std::forward<K>(key)) != container.end();
}

template<typename C, typename K>
const typename C::mapped_type *c_find(const C& container, K&& key)
{
    auto it = container.find(std::forward<K>(key));
    return it != container.end() ? &(it->second) : nullptr;
}

template<typename C, typename K>
typename C::mapped_type *c_find(C& container, K&& key)
{
    auto it = container.find(std::forward<K>(key));
    return it != container.end() ? &(it->second) : nullptr;
}

template<typename T>
struct ZeroPod : T
{
    static_assert(std::is_pod<T>::value, "T must be pod");

    ZeroPod() noexcept
    {
        memset(this, 0, sizeof(T));
    }
};

template <typename T, size_t N>
uint8_t (&dy_array_size_helper(T(&array)[N]))[N];

#define DY_ARRAY_SIZE(__a) (sizeof(dy_array_size_helper(__a)))

}
