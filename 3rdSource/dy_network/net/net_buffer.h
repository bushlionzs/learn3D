#ifndef __NETBUFFER_H__
#define __NETBUFFER_H__

#include <net_define.h>

struct BufferZone
{
    BufferZone(uint32_t capacity);
    ~BufferZone();
    void init();
    uint32_t add_buffer(const uint8_t* buf, uint32_t size);
    int32_t  release_buffer(uint32_t size);
    const uint8_t* get_buffer()
    {
        return _buf + _start;
    }
    uint32_t get_size()
    {
        return _size;
    }
    int32_t get_left()
    {
        return _capacity - _size;
    }
    
    void clear()
    {
        _start = _end = _size = 0;
    }
    
    bool empty()
    {
        return 0 == _size;
    }
    struct BufferZone* _next;
private:
    
    uint32_t _size;
    uint32_t _capacity;
    uint32_t _start;
    uint32_t _end;
    uint8_t* _buf;  
};


class CBuffer
{
public:
    CBuffer(uint32_t size);
	
    ~CBuffer();
    bool AddTcpBuffer(const uint8_t* buf, uint32_t size);
    void ReleaseTcpBuffer(uint32_t size);
    const uint8_t* GetTcpBuffer();
	uint32_t GetTcpLength() const
	{ 
		return _current->get_size();
	}

	bool IsEmpty() const
	{
        return _current->empty();
	}
    
    uint32_t GetLeftData();
    uint32_t GetLeftCapacity();
private:
    struct BufferZone* alloc_zone();
    void release_zone(struct BufferZone* zone);
    void release_all_zone();
private:
    struct BufferZone* _current = NULL;
    struct BufferZone* _tail = NULL;
    
    int32_t _flag_count;
    int32_t _max_flag_count;
};

#pragma pack(push, 1)

struct UdpChunkHeader
{
    uint32_t capacity;
    uint16_t port;
    uint16_t family;

    bool get_send_param(dy_network::SockaddrStorage& dst, const uint8_t *&data, uint32_t& len) const;
};

template<typename T>
struct UdpChunk : UdpChunkHeader
{
    T ip;

    uint8_t *data() { return reinterpret_cast<uint8_t *>(this + 1); }
    const uint8_t *data() const { return reinterpret_cast<const uint8_t *>(this + 1); }
    uint32_t size() const { return this->capacity - sizeof(UdpChunkHeader) - sizeof(T); }
};

using UdpChunkIP4 = UdpChunk<uint32_t>;
using UdpChunkIP6 = UdpChunk<in6_addr>;

#pragma pack(pop)

class CUdpSendBuffer
{
public:
	CUdpSendBuffer(uint32_t size);

	~CUdpSendBuffer();

	void clear()
	{
		m_nLength = 0;
		m_nStart = 0;
		m_nEnd = 0;
	}

	uint32_t get_left_data() const
	{
		return m_nLength;
	}

    bool add_udp_buffer(const SndData& sd, const uint8_t *buf, uint32_t size);

    template<typename T>
    bool add_udp_buffer(uint16_t family, T ip, uint16_t port, const uint8_t *buf, uint32_t size)
    {
        auto h = add_udp_buffer(sizeof(UdpChunk<T>) + size, port, family);
        if (!h)
        {
            return false;
        }

        auto chunk = static_cast<UdpChunk<T> *>(h);
        chunk->ip = ip;
        memcpy(chunk->data(), buf, size);

        return true;
    }

    const UdpChunkHeader *get_udp_buffer() const;
    void release_udp_buffer();
	void release_udp_buffer(const UdpChunkHeader *h);

	bool empty() const
	{
		return m_nLength == 0;
	}
    
    bool check(uint32_t size);

private:
    UdpChunkHeader *add_udp_buffer(uint32_t capacity, uint16_t port, uint16_t family);
    void release_udp_buffer(uint32_t capacity);

	uint32_t m_nLength;
	uint32_t m_nCapacity;
	uint32_t m_nStart;
	uint32_t m_nEnd;
	uint8_t* m_pBuf;
};

#endif
