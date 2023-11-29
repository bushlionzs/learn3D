#ifndef _STRING_VIEW_H_INCLUDED
#define _STRING_VIEW_H_INCLUDED

#include <iterator>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <type_traits>

namespace dy_network
{

template<typename CharT, typename Traits>
class basic_string_view
{
public:
    static_assert(std::is_same<CharT, typename Traits::char_type>::value, "different char_type");

    typedef CharT value_type;
    typedef const CharT* pointer;
    typedef const CharT& reference;
    typedef const CharT& const_reference;
    typedef pointer const_iterator; // impl-defined
    typedef const_iterator iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef const_reverse_iterator reverse_iterator;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    static constexpr size_type npos = size_type(-1);

    constexpr basic_string_view() noexcept = default;
    constexpr basic_string_view(std::nullptr_t ptr) noexcept {}
    basic_string_view(const basic_string_view& rhs) noexcept = default;
    basic_string_view& operator=(const basic_string_view& rhs) noexcept = default;

    constexpr basic_string_view(const CharT *str, size_t len) noexcept : _ptr(str), _len(len) {}
    basic_string_view(const CharT *str) noexcept : basic_string_view(str, Traits::length(str)) {}

    template<typename Alloc>
    basic_string_view(const std::basic_string<CharT, Traits, Alloc>& str) noexcept
        : basic_string_view(str.data(), str.length()) {}

    std::basic_string<CharT, Traits> to_string() const
    {
        return { begin(), end() };
    }

    constexpr const_iterator begin() const noexcept { return _ptr; }
    constexpr const_iterator cbegin() const noexcept { return _ptr; }
    constexpr const_iterator end() const noexcept { return _ptr + _len; }
    constexpr const_iterator cend() const noexcept { return _ptr + _len; }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator (end()); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator (end()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator (begin()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator (begin()); }

    constexpr size_type size() const noexcept { return _len; }
    constexpr size_type length() const noexcept { return _len; }
    constexpr size_type max_size() const noexcept { return _len; }
    constexpr bool empty() const noexcept { return _len == 0; }

    constexpr const CharT& operator[](size_type pos) const noexcept { return _ptr[pos]; }

    const CharT& at(size_t pos) const
    {
        if (pos >= _len)
        {
            throw std::out_of_range ( "string_view::at" );
        }

        return _ptr[pos];
    }

    constexpr const CharT& front() const noexcept { return _ptr[0]; }
    constexpr const CharT& back() const noexcept { return _ptr[_len-1]; }
    constexpr const CharT* data() const noexcept { return _ptr; }

    void clear() noexcept { _len = 0; }
    void remove_prefix(size_type n) noexcept
    {
        if (n > _len)
        {
             n = _len;
        }

        _ptr += n;
        _len -= n;
    }

    void remove_suffix(size_type n) noexcept
    {
        if (n > _len)
        {
            n = _len;
        }

        _len -= n;
    }

    basic_string_view substr(size_type pos, size_type n = npos) const
    {
        if (pos > size())
        {
            throw std::out_of_range("basic_string_view::substr");
        }

        return { data() + pos, (std::min)(size() - pos, n) };
    }

    int compare(basic_string_view x) const 
    {
        const int cmp = Traits::compare(_ptr, x._ptr, (std::min)(_len, x._len));
        return cmp != 0 ? cmp : (_len == x._len ? 0 : _len < x._len ? -1 : 1 );
    }

    bool starts_with(CharT c) const { return !empty() && Traits::eq( c, front()); }
    bool starts_with(basic_string_view x) const
    {
        return _len >= x._len && Traits::compare(_ptr, x._ptr, x._len) == 0;
    }

    bool ends_with(CharT c) const { return !empty() && Traits::eq( c, back()); }
    bool ends_with(basic_string_view x) const
    {
        return _len >= x._len && Traits::compare(_ptr + _len - x._len, x._ptr, x._len) == 0;
    }

    size_type find(basic_string_view s) const 
    {
        const_iterator iter = std::search(this->cbegin (), this->cend (), s.cbegin (), s.cend (), Traits::eq);
        return iter == this->cend () ? npos : std::distance(this->cbegin(), iter);
    }

    size_type find(CharT c) const 
    {
        const_iterator iter = std::find_if(
            this->cbegin (),
            this->cend (),
            string_view_traits_eq(c));
        return iter == this->cend () ? npos : std::distance(this->cbegin (), iter);
    }

    size_type rfind(basic_string_view s) const 
    {
        const_reverse_iterator iter = std::search(
            this->crbegin (),
            this->crend (),
            s.crbegin (),
            s.crend (),
            Traits::eq);
        return iter == this->crend () ? npos : (std::distance(iter, this->crend()) - s.size());
    }

    size_type rfind(CharT c) const 
    {
        const_reverse_iterator iter = std::find_if(
            this->crbegin (), 
            this->crend (),
            string_view_traits_eq(c));
        return iter == this->crend () ? npos : (this->size() - 1 - std::distance(this->crbegin(), iter));
    }

    size_type find_first_of(CharT c) const { return find (c); }
    size_type find_last_of (CharT c) const { return rfind (c); }

    size_type find_first_of(basic_string_view s) const 
    {
        const_iterator iter = std::find_first_of(
            this->cbegin (),
            this->cend (),
            s.cbegin (),
            s.cend (),
            Traits::eq);
        return iter == this->cend () ? npos : std::distance (this->cbegin (), iter);
    }

    size_type find_last_of(basic_string_view s) const 
    {
        const_reverse_iterator iter = std::find_first_of(
            this->crbegin (),
            this->crend (),
            s.cbegin (), s.cend (),
            Traits::eq);
        return iter == this->crend () ? npos : (this->size() - 1 - std::distance(this->crbegin(), iter));
    }

    size_type find_first_not_of(basic_string_view s) const 
    {
        const_iterator iter = find_not_of (this->cbegin (), this->cend (), s);
        return iter == this->cend () ? npos : std::distance( this->cbegin (), iter);
    }

    size_type find_first_not_of(CharT c) const
    {
        for (const_iterator iter = this->cbegin (); iter != this->cend (); ++iter)
        {
            if (!Traits::eq(c, *iter))
            {
                return std::distance(this->cbegin (), iter);
            }
        }

        return npos;
    }

    size_type find_last_not_of(basic_string_view s) const
    {
        const_reverse_iterator iter = find_not_of (this->crbegin (), this->crend (), s);
        return iter == this->crend () ? npos : (this->size() - 1 - std::distance(this->crbegin(), iter));
    }

    size_type find_last_not_of(CharT c) const 
    {
        for (const_reverse_iterator iter = this->crbegin (); iter != this->crend (); ++iter)
        {
            if (!Traits::eq(c, *iter))
            {
                return this->size() - 1 - std::distance(this->crbegin(), iter);
            }
        }

        return npos;
    }

    void trim_left(basic_string_view s = " \r\n")
    {
        size_type pos = find_first_not_of(s);
        if (npos != pos)
        {
            remove_prefix(pos);
        }
    }

    void trim_right(basic_string_view s = " \r\n")
    {
        size_type pos = find_last_not_of(s);
        if (npos != pos)
        {
            remove_suffix(size() - pos - 1);
        }
    }

    void trim(basic_string_view s = " \r\n")
    {
        trim_left(s);
        trim_right(s);
    }

    template<typename Container>
    void split(CharT c, Container& result) const
    {
        size_type i = 0;
        size_type pos = 0;
        for (; i < size(); ++i)
        {
            if (c == at(i))
            {
                if (i > pos)
                {
                    result.emplace_back(substr(pos, i - pos));
                }

                pos = i + 1;
            }
        }

        if (i > pos)
        {
            result.emplace_back(substr(pos, i - pos));
        }
    }

    friend bool operator==(basic_string_view<CharT, Traits> x, basic_string_view<CharT, Traits> y)
    {
        if (x.size() != y.size()) return false;
        return x.compare(y) == 0;
    }

    template<typename Allocator>
    friend bool operator==(basic_string_view<CharT, Traits> x, const std::basic_string<CharT, Traits, Allocator> & y)
    {
        return x == basic_string_view<CharT, Traits>(y);
    }

    template<typename Allocator>
    friend bool operator==(const std::basic_string<CharT, Traits, Allocator> & x, basic_string_view<CharT, Traits> y)
    {
        return basic_string_view<CharT, Traits>(x) == y;
    }

    friend bool operator==(basic_string_view<CharT, Traits> x, const CharT * y)
    {
        return x == basic_string_view<CharT, Traits>(y);
    }

    friend bool operator==(const CharT * x, basic_string_view<CharT, Traits> y)
    {
        return basic_string_view<CharT, Traits>(x) == y;
    }

    friend bool operator!=(basic_string_view<CharT, Traits> x, basic_string_view<CharT, Traits> y)
    {
        if (x.size() != y.size()) return true;
        return x.compare(y) != 0;
    }

    template<typename Allocator>
    friend bool operator!=(basic_string_view<CharT, Traits> x, const std::basic_string<CharT, Traits, Allocator> & y)
    {
        return x != basic_string_view<CharT, Traits>(y);
    }

    template<typename Allocator>
    friend bool operator!=(const std::basic_string<CharT, Traits, Allocator> & x, basic_string_view<CharT, Traits> y)
    {
        return basic_string_view<CharT, Traits>(x) != y;
    }

    friend bool operator!=(basic_string_view<CharT, Traits> x, const CharT * y)
    {
        return x != basic_string_view<CharT, Traits>(y);
    }

    friend bool operator!=(const CharT * x, basic_string_view<CharT, Traits> y)
    {
        return basic_string_view<CharT, Traits>(x) != y;
    }

    friend bool operator<(basic_string_view<CharT, Traits> x, basic_string_view<CharT, Traits> y)
    {
        return x.compare(y) < 0;
    }

    template<typename Allocator>
    friend bool operator<(basic_string_view<CharT, Traits> x, const std::basic_string<CharT, Traits, Allocator> & y)
    {
        return x < basic_string_view<CharT, Traits>(y);
    }

    template<typename Allocator>
    friend bool operator<(const std::basic_string<CharT, Traits, Allocator> & x, basic_string_view<CharT, Traits> y)
    {
        return basic_string_view<CharT, Traits>(x) < y;
    }

    friend bool operator<(basic_string_view<CharT, Traits> x, const CharT * y)
    {
        return x < basic_string_view<CharT, Traits>(y);
    }

    friend bool operator<(const CharT * x, basic_string_view<CharT, Traits> y)
    {
        return basic_string_view<CharT, Traits>(x) < y;
    }

    friend bool operator>(basic_string_view<CharT, Traits> x, basic_string_view<CharT, Traits> y)
    {
        return x.compare(y) > 0;
    }

    template<typename Allocator>
    friend bool operator>(basic_string_view<CharT, Traits> x, const std::basic_string<CharT, Traits, Allocator> & y)
    {
        return x > basic_string_view<CharT, Traits>(y);
    }

    template<typename Allocator>
    friend bool operator>(const std::basic_string<CharT, Traits, Allocator> & x, basic_string_view<CharT, Traits> y)
    {
        return basic_string_view<CharT, Traits>(x) > y;
    }

    friend bool operator>(basic_string_view<CharT, Traits> x, const CharT * y)
    {
        return x > basic_string_view<CharT, Traits>(y);
    }

    friend bool operator>(const CharT * x, basic_string_view<CharT, Traits> y)
    {
        return basic_string_view<CharT, Traits>(x) > y;
    }

    friend bool operator<=(basic_string_view<CharT, Traits> x, basic_string_view<CharT, Traits> y)
    {
        return x.compare(y) <= 0;
    }

    template<typename Allocator>
    friend bool operator<=(basic_string_view<CharT, Traits> x, const std::basic_string<CharT, Traits, Allocator> & y)
    {
        return x <= basic_string_view<CharT, Traits>(y);
    }

    template<typename Allocator>
    friend bool operator<=(const std::basic_string<CharT, Traits, Allocator> & x, basic_string_view<CharT, Traits> y)
    {
        return basic_string_view<CharT, Traits>(x) <= y;
    }

    friend bool operator<=(basic_string_view<CharT, Traits> x, const CharT * y)
    {
        return x <= basic_string_view<CharT, Traits>(y);
    }

    friend bool operator<=(const CharT * x, basic_string_view<CharT, Traits> y)
    {
        return basic_string_view<CharT, Traits>(x) <= y;
    }

    friend bool operator>=(basic_string_view<CharT, Traits> x, basic_string_view<CharT, Traits> y)
    {
        return x.compare(y) >= 0;
    }

    template<typename Allocator>
    friend bool operator>=(basic_string_view<CharT, Traits> x, const std::basic_string<CharT, Traits, Allocator> & y)
    {
        return x >= basic_string_view<CharT, Traits>(y);
    }

    template<typename Allocator>
    friend bool operator>=(const std::basic_string<CharT, Traits, Allocator> & x, basic_string_view<CharT, Traits> y)
    {
        return basic_string_view<CharT, Traits>(x) >= y;
    }

    friend bool operator>=(basic_string_view<CharT, Traits> x, const CharT * y)
    {
        return x >= basic_string_view<CharT, Traits>(y);
    }

    friend bool operator>=(const CharT * x, basic_string_view<CharT, Traits> y)
    {
        return basic_string_view<CharT, Traits>(x) >= y;
    }

    friend std::basic_ostream<CharT, Traits>&operator<<(std::basic_ostream<CharT, Traits>& os,
        const basic_string_view<CharT, Traits>& str)
    {
        if (os.good())
        {
            os.write(str.data(), str.size());
        }

        return os;
    }
private:
    class string_view_traits_eq 
    {
    public:
        string_view_traits_eq(CharT ch) : ch_(ch) {}
        constexpr bool operator ()(CharT val) const { return Traits::eq(ch_, val); }
        CharT ch_;
    };

    template<typename Iterator>
    Iterator find_not_of(Iterator first, Iterator last, basic_string_view s) const 
    {
        for (; first != last ; ++first)
        {
            if (0 == Traits::find(s._ptr, s._len, *first))
            {
                return first;
            }
        }

        return last;
    }

    const CharT *_ptr = nullptr;
    std::size_t _len = 0;
};

using string_view = basic_string_view<char, std::char_traits<char>>;


inline int stoi(string_view str, size_t *idx = 0, int base = 0)
{
    return std::stoi(str.to_string(), idx, base);
}

inline long stol(string_view str, size_t *idx = 0, int base = 0)
{
    return std::stol(str.to_string(), idx, base);
}

inline unsigned long stoul(string_view str, size_t *idx = 0, int base = 0)
{
    return std::stoul(str.to_string(), idx, base);
}

inline long long stoll(string_view str, size_t *idx = 0, int base = 0)
{
    return std::stoll(str.to_string(), idx, base);
}

inline unsigned long long stoull(string_view str, size_t *idx = 0, int base = 0)
{
    return std::stoull(str.to_string(), idx, base);
}

}

using dy_network::string_view;
using dy_network::stoi;
using dy_network::stol;
using dy_network::stoul;
using dy_network::stoull;

#endif //_STRING_VIEW_H_INCLUDED
