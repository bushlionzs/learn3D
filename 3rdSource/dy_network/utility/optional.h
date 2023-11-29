#ifndef _DY_OPTIONAL_H_INCLUDED
#define _DY_OPTIONAL_H_INCLUDED

#include <exception>
#include <memory>
#include <type_traits>

struct nullopt_t {};

constexpr nullopt_t nullopt{};

class bad_optional_access : public std::exception
{
public:
    explicit bad_optional_access(const char *const what) : _what(what) {}
    const char* what() const noexcept override { return _what; }
private:
    const char *const _what = nullptr;
};

template<typename T>
class optional
{
public:
    static_assert(!std::is_reference<T>::value, "T must be not a reference type");

    using value_type = T;

    constexpr optional() noexcept : _dummy(0) {}
    constexpr optional(nullopt_t) noexcept : optional() {}
    optional(const optional& other)
    {
        if (other)
        {
            construct(other.value());
        }
    }
    optional(optional&& other)
    {
        if (other)
        {
            construct(std::move(other.value()));
        }
    }

    template<typename U>
    optional(U&& value)
    {
        construct(std::forward<U>(value));
    }

    ~optional()
    {
        destruct();
    }

    optional& operator=(nullopt_t) noexcept
    {
        reset();
        return *this;
    }
    optional& operator=(const optional& other)
    {
        if (this != &other)
        {
            reset();

            if (other)
            {
                construct(other.value());
            }
        }

        return *this;
    }

    optional& operator=(optional&& other)
    {
        if (this != &other)
        {
            reset();

            if (other)
            {
                construct(std::move(other.value()));
            }
        }

        return *this;
    }

    constexpr const T* operator->() const noexcept { return std::addressof(_value); }
    T* operator->() noexcept { return std::addressof(_value); }
    T& operator*() noexcept { return _value; }
    constexpr const T& operator*() const noexcept { return _value; }

    constexpr explicit operator bool() const noexcept { return _has_value; }
    constexpr bool has_value() const noexcept { return _has_value; }

    T& value() &
    {
        if (!_has_value)
        {
            throw bad_optional_access("optional::value");
        }

        return _value;
    }
    const T & value() const &
    {
        if (!_has_value)
        {
            throw bad_optional_access("optional::value");
        }

        return _value;
    }
    T&& value() &&
    {
        if (!_has_value)
        {
            throw bad_optional_access("optional::value");
        }

        return std::move(_value);
    }
    const T&& value() const &&
    {
        if (!_has_value)
        {
            throw bad_optional_access("optional::value");
        }

        return std::move(_value);
    }

    const T *get_if() const noexcept
    {
        return _has_value ? &_value : nullptr;
    }

    T *get_if() noexcept
    {
        return _has_value ? &_value : nullptr;
    }

    template< class U >
    T value_or(U&& default_value) const&
    {
        if (!_has_value)
        {
            return std::forward<U>(default_value);
        }

        return _value;
    }

    template< class U >
    T value_or(U&& default_value) const&&
    {
        if (!_has_value)
        {
            return std::forward<U>(default_value);
        }

        return std::move(_value);
    }

    void swap(optional& other) noexcept
    {
        if (this != &other)
        {
            std::swap(_value, other._value);
            std::swap(_has_value, other._has_value);
        }
    }

    void reset()
    {
        destruct();
    }

    template< class... Args >
    T& emplace(Args&&... args)
    {
        reset();

        construct(std::forward<Args>(args)...);
        return _value;
    }
private:
    template<typename ... Args>
    void construct(Args&& ... args)
    {
        new (&_value) T(std::forward<Args>(args)...);
        _has_value = true;
    }

    void destruct()
    {
        if (_has_value)
        {
            _value.~T();
            _has_value = false;
        }
    }

    union
    {
        char _dummy;
        T _value;
    };

    bool _has_value = false;
};

#endif // !_DY_OPTIONAL_H_INCLUDED
