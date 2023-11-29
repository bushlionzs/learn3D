#pragma once

#include <unordered_map>
#include <list>

namespace dy_network
{

template<typename T>
struct PtrEq
{
    constexpr size_t operator()(const T * const lhs, const T * const rhs) const
    {
        return *lhs == *rhs;
    }
};

template<typename T>
struct PtrHash
{
    constexpr size_t operator()(const T * const ptr) const
    {
        return std::hash<T>{}(*ptr);
    }
};

template<typename Key, typename Value>
class LRUCache
{
public:
    using Entry = std::pair<Key, Value>;
    using Entries = std::list<Entry>;
    using Map = std::unordered_map<const Key *, typename Entries::iterator, PtrHash<Key>, PtrEq<Key>>;

    enum { NO_LIMIT = 0 };

    explicit LRUCache(size_t capacity = NO_LIMIT) : _capacity(capacity) {}

    constexpr size_t capacity() const noexcept { return _capacity; }
    bool empty() const noexcept { return _cache.empty(); }
    size_t size() const noexcept { return _cache.size(); }

    void clear() noexcept
    {
        _cache.clear();
        _entries.clear();
    }

    bool put(const Key& key, Value value, bool force_update)
    {
        return put(key, std::move(value), [force_update](const Value&) { return force_update; });
    }

    template<typename Pred>
    bool put(const Key& key, Value value, Pred pred)
    {
        auto p = get(key);
        if (p)
        {
            if (pred(*p))
            {
                *p = std::move(value);
            }

            return false;
        }

        _entries.push_front({ key, std::move(value) });
        auto it = _entries.begin();
        _cache.insert({ &(it->first), it });

        prune();

        return true;
    }

    const Value *get(const Key& key) const
    {
        return const_cast<LRUCache *>(this)->get(key);
    }

    bool remove(const Key& key)
    {
        auto it = _cache.find(&key);
        if (_cache.end() == it)
        {
            return false;
        }

        _entries.erase(it->second);
        _cache.erase(it);

        return true;
    }

    bool contains(const Key& key) const noexcept
    {
        return _cache.find(key) != _cache.end();
    }

    template<typename F>
    void visit(F&& f) const
    {
        for (auto&& entry : _entries)
        {
            f(entry);
        }
    }
private:
    Value *get(const Key& key)
    {
        auto it = _cache.find(&key);
        if (_cache.end() == it)
        {
            return nullptr;
        }

        _entries.splice(_entries.begin(), _entries, it->second);
        return &(it->second->second);
    }

    size_t prune()
    {
        if (NO_LIMIT == _capacity)
        {
            return 0;
        }

        size_t count = 0;
        while (_cache.size() > _capacity)
        {
            _cache.erase(&(_entries.back().first));
            _entries.pop_back();
            ++count;
        }

        return count;
    }

    const size_t _capacity = NO_LIMIT;

    Map _cache;
    mutable Entries _entries;
};

}
