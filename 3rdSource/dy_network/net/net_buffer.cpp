#include <net_buffer.h>
#include <assert.h>
#include <stdio.h>
#include <net_stat.h>
#include <platform_mutex.h>
#include <scoped_lock.h>
#include <platform_log.h>

//#define BUFFER_ZONE_SIZE (16 * 1024)
extern struct NetLibParam g_param;
static struct BufferZone g_zone_header(512);
//static uint32_t g_zone_count = 0;
static PlatformMutex _zone_mutex;
#define MAX_ZONE_POOL_COUNT 10000

static struct BufferZone* alloc_zone_by_pool()
{
    struct BufferZone* zone = new BufferZone(g_param._net_lib_buffer_block_size);
    return zone;
    /*
    ScopedLock<PlatformMutex> lock(_zone_mutex);
    if (g_zone_header._next == NULL)
    {
        struct BufferZone* zone = new BufferZone(BUFFER_ZONE_SIZE);
        incr_recv_block(1);
        return zone;
    }
    else
    {
        struct BufferZone* zone = g_zone_header._next;
        g_zone_header._next = zone->_next;
        g_zone_count--;
        zone->init();
        return zone;
    }
    */
}

static void release_zone_by_pool(struct BufferZone* zone)
{
    delete zone;
    /*
    ScopedLock<PlatformMutex> lock(_zone_mutex);
    if (g_zone_count < MAX_ZONE_POOL_COUNT)
    {
        g_zone_count++;
        zone->_next = g_zone_header._next;
        g_zone_header._next = zone;
    }
    else
    {
        incr_recv_block(-1);
        delete zone;
    }
    */
}

BufferZone::BufferZone(uint32_t capacity)
{
    _capacity = capacity;
    
    _buf = (uint8_t*)malloc(capacity);
    init();
}

void BufferZone::init()
{
    _next = 0;
    _size = 0;
    _start = 0;
    _end   = 0;
}

BufferZone::~BufferZone()
{
    if (NULL != _buf)
    {
        free(_buf);
    }
}


uint32_t BufferZone::add_buffer(const uint8_t* buf, uint32_t size)
{
    assert(_capacity >= _end);
    uint32_t left = _capacity - _end;
	if (left < size)
    {
		if (_start > 0)
        {
            memmove(_buf , _buf + _start , _size);
            _start = 0;
            _end = _start + _size;

            left = _capacity - _end;
        }
    }
    
    uint32_t min = left > size?size:left;
    memmove(_buf + _end, buf, min);
    _size += min;
    _end  += min;
    return min;
}

int32_t  BufferZone::release_buffer(uint32_t size)
{
    if (size > _size)
    {
        //assert(false);
        FATAL_LOG("release_buffer logic error, assert(false)");
        _start = 0;
        _end = 0;
        _size = 0;
        return -1;
    }
    
    _start += size;
    
    _size -= size;
    
    if (0 == _size)
    {
        _start = 0;
        _end = 0;
    }
    return 0;
}

CBuffer::CBuffer(uint32_t size)
{
    _max_flag_count = size / g_param._net_lib_buffer_block_size;
    
    
    if (size % g_param._net_lib_buffer_block_size)
    {
        _max_flag_count++;
    }
    
    _flag_count = 0;
    _current = alloc_zone();
}

CBuffer::~CBuffer()
{
	release_all_zone();
}

const uint8_t* CBuffer::GetTcpBuffer()
{
    return _current->get_buffer();
}

bool CBuffer::AddTcpBuffer(const uint8_t* buf, uint32_t size)
{
    //struct BufferZone* nzone = _current;
    //struct BufferZone* zone = _tail;
    
    if (_tail == NULL)
    {
        _tail = _current;
        while (_tail->_next) 
        {
            _tail = _tail->_next;   
        }
    }
    
    uint32_t left = _tail->get_left() + (_max_flag_count - _flag_count) * g_param._net_lib_buffer_block_size;
    if (left < size)
    {
//         DY_ERROR_LOG(0, 0, __FUNCTION__, "", 
//         		"[left:%d,max_flag_count:%d,flag_count:%d,size:%d]add tcp buffer failed",
//             		left, _max_flag_count, _flag_count, size);
        return false;
    }
    const uint8_t* start = buf;
    left = size;
    uint32_t loop = _max_flag_count;
    while (loop)
    {
        uint32_t ret = _tail->add_buffer(start, left);
        if (ret < left)
        {
            if (_flag_count < _max_flag_count)
            {
                struct BufferZone* newzone = alloc_zone();
                
                start += ret;
                left -= ret;
                _tail->_next = newzone;
                _tail = newzone; 
            }
            else
            {
//                 DY_ERROR_LOG(0, 0, __FUNCTION__, "", 
//                 		"[left:%d,max_flag_count:%d,flag_count:%d,size:%d]add tcp buffer failed",
//                     		left, _max_flag_count, _flag_count, size);
                return false;
            }
        }
        else
        {
            break;
        }
        loop--;
    }
    
    return true;
}

void CBuffer::ReleaseTcpBuffer(uint32_t size)
{
    _current->release_buffer(size);
    
    if (_current->empty())
    {
        struct BufferZone* next = _current->_next;
        if (next != NULL)
        {
            release_zone(_current);
            _current = next;
        }
    }
}

uint32_t CBuffer::GetLeftData()
{
    uint32_t total = 0;
    struct BufferZone* next = _current;
    while (next)
    {
        total += next->get_size();
        next = next->_next;
    }
    return  total;
}

uint32_t CBuffer::GetLeftCapacity()
{
    if (_tail == NULL)
    {
        _tail = _current;
        while (_tail->_next)
        {
            _tail = _tail->_next;
        }
    }
    return _tail->get_left() + (_max_flag_count - _flag_count) * g_param._net_lib_buffer_block_size;
}

struct BufferZone* CBuffer::alloc_zone()
{
    if (_flag_count < _max_flag_count)
    {
        _flag_count++;
        struct BufferZone* zone = alloc_zone_by_pool();
        return zone;
    }
    else
    {
        return NULL;
    }
}

void CBuffer::release_zone(struct BufferZone* zone)
{
    _flag_count--;
    release_zone_by_pool(zone);
}

void CBuffer::release_all_zone()
{
    struct BufferZone* zone = 0;
    while (_current)
    {
        zone = _current->_next;
        release_zone(_current);
        _current = zone;
    }
    _current = 0;
    _tail = 0;
}

bool UdpChunkHeader::get_send_param(dy_network::SockaddrStorage& dst, const uint8_t *&data, uint32_t& len) const
{
    if( AF_INET == this->family)
    {
        auto v4 = reinterpret_cast<const UdpChunkIP4 *>(this);
        auto addr4 = dst.addr4();
        addr4->sin_family = AF_INET;
        addr4->sin_addr.s_addr = v4->ip;
        addr4->set_port(v4->port);

        data = v4->data();
        len = v4->size();

        return true;
    }

    if (AF_INET6 == this->family)
    {
        auto v6 = reinterpret_cast<const UdpChunkIP6 *>(this);
        auto addr6 = dst.addr6();
        addr6->sin6_family = AF_INET6;
        addr6->sin6_addr = v6->ip;
        addr6->set_port(v6->port);
        addr6->zero_unused();

        data = v6->data();
        len = v6->size();

        return true;
    }

    return false;
}


CUdpSendBuffer::CUdpSendBuffer(uint32_t size)
{
	m_nLength = 0;
	m_nStart = 0;
	m_nEnd = 0;
	m_nCapacity = size;
	m_pBuf = new uint8_t[m_nCapacity];
}

CUdpSendBuffer::~CUdpSendBuffer()
{
	if (m_pBuf)
	{
		delete[] m_pBuf;
		m_pBuf = NULL;
	}
}

bool CUdpSendBuffer::add_udp_buffer(const SndData& sd, const uint8_t *buf, uint32_t size)
{
    if (sd.is_ip4())
    {
        return add_udp_buffer(AF_INET, sd._dst_address, sd._dst_port, buf, size);
    }

    return add_udp_buffer(AF_INET6, sd._dst_address6, sd._dst_port, buf, size);
}

const UdpChunkHeader *CUdpSendBuffer::get_udp_buffer() const
{
    return (0 == m_nLength)
        ? nullptr
        : reinterpret_cast<const UdpChunkHeader *>(m_pBuf + m_nStart);
}

bool CUdpSendBuffer::check(uint32_t size)
{
	uint32_t left = m_nCapacity - m_nEnd;
	if (left >= size)
		return true;
	if (m_nLength + size > m_nCapacity)
		return false;
	if (left < size)
	{
		memmove(m_pBuf, m_pBuf + m_nStart, m_nLength);
		m_nStart = 0;
		m_nEnd = m_nLength;
	}
	return true;
}

UdpChunkHeader *CUdpSendBuffer::add_udp_buffer(uint32_t capacity, uint16_t port, uint16_t family)
{
    if (!check(capacity))
    {
        return nullptr;
    }

    auto h = reinterpret_cast<UdpChunkHeader *>(m_pBuf + m_nEnd);
    h->capacity = capacity;
    h->port = port;
    h->family = family;

    m_nLength += capacity;
    m_nEnd += capacity;

	return h;
}

void CUdpSendBuffer::release_udp_buffer()
{
    auto h = get_udp_buffer();
    if (h)
    {
        release_udp_buffer(h);
    }
}

void CUdpSendBuffer::release_udp_buffer(const UdpChunkHeader *h)
{
    release_udp_buffer(h->capacity);
}

void CUdpSendBuffer::release_udp_buffer(uint32_t capacity)
{
    if (capacity > m_nLength)
    {
        assert(false);
        m_nLength = 0;
        m_nStart = 0;
        m_nEnd = 0;
    }
    else
    {
        m_nLength -= capacity;
        m_nStart += capacity;
    }
}
