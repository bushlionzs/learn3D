#pragma once

#include <initializer_list>
#include <stdexcept>

namespace dy_network
{

template<typename T>
class ArrayView
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using const_pointer = const T*;
    using reference = T &;
    using const_reference = const T &;
    using iterator = T * ;
    using const_iterator = const T *;

    constexpr ArrayView() = default;
    constexpr ArrayView(const ArrayView&) = default;
    ArrayView& operator=(const ArrayView&) = default;

    constexpr ArrayView(pointer data, size_type size) noexcept : _data(data), _size(size) {}

    template<size_t N>
    constexpr ArrayView(T(&a)[N]) noexcept : ArrayView(a, N) {}

    constexpr ArrayView(std::initializer_list<T> il) noexcept : ArrayView(il.begin(), il.size()) {}

    template<typename U,
        typename = decltype(static_cast<T *>(std::declval<U>().data())),
        typename = decltype(std::declval<U>().size())>
    constexpr ArrayView(U&& v) noexcept : ArrayView(v.data(), v.size()) {}

    constexpr bool empty() const noexcept { return 0 == _size; }
    constexpr size_type size() const noexcept { return _size; }

    constexpr pointer data() const noexcept { return _data; }
    constexpr reference at(size_type pos) const noexcept { return _data[pos]; }
    constexpr reference operator[](size_type pos) const noexcept { return _data[pos]; }
    constexpr reference front() const noexcept { return _data[0]; }
    constexpr reference back() const noexcept { return _data[_size - 1]; }

    constexpr iterator begin() const noexcept { return _data; }
    constexpr iterator end() const noexcept { return _data + _size; }
    constexpr const_iterator cbegin() const noexcept { return _data; }
    constexpr const_iterator cend() const noexcept { return _data + _size; }

    void remove_prefix(size_type n) noexcept
    {
        _data += n;
        _size -= n;
    }

    void remove_suffix(size_type n) noexcept
    {
        _size -= n;
    }

    ArrayView<T> sub_array(size_type pos, size_type count) const
    {
        if (pos + count > _size)
        {
            throw std::out_of_range("ArrayView<T>::sub_array out of range");
        }

        return { _data + pos, count };
    }

private:
    pointer _data = nullptr;
    size_type _size = 0;
};

}
