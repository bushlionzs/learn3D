#include <string.h>

#include "utility/bit_buffer.h"

namespace
{
inline uint8_t lowest_bits(uint8_t byte, size_t bit_count)
{
    return byte & ((1 << bit_count) - 1);
}

inline uint8_t highest_bits(uint8_t byte, size_t bit_count)
{
    uint8_t shift = 8 - static_cast<uint8_t>(bit_count);
    uint8_t mask = 0xFF << shift;
    return (byte & mask) >> shift;
}
}

namespace dy_network
{
BitBuffer::BitBuffer(const uint8_t* bytes, size_t byte_count)
    : _bytes(bytes)
    , _byte_count(byte_count) 
{
}

size_t BitBuffer::remaining_bit_count() const
{
    return (_byte_count - _byte_offset) * 8 - _bit_offset;
}

bool BitBuffer::read_uint8(uint8_t& val)
{
    return read_uint(val);
}

bool BitBuffer::read_uint16(uint16_t& val)
{
    return read_uint(val);
}

bool BitBuffer::read_uint32(uint32_t& val)
{
    return read_bits(val, sizeof(uint32_t) * 8);
}

bool BitBuffer::peek_bits(uint32_t& val, size_t bit_count)
{
    if (bit_count > remaining_bit_count() || bit_count > 32)
    {
        return false;
    }

    const uint8_t* bytes = _bytes + _byte_offset;
    size_t remaining_bits_in_current_byte = 8 - _bit_offset;
    uint32_t bits = lowest_bits(*bytes++, remaining_bits_in_current_byte);
    if (bit_count < remaining_bits_in_current_byte)
    {
        val = highest_bits(bits, _bit_offset + bit_count);
        return true;
    }

    bit_count -= remaining_bits_in_current_byte;
    while (bit_count >= 8)
    {
        bits = (bits << 8) | *bytes++;
        bit_count -= 8;
    }

    if (bit_count > 0)
    {
        bits <<= bit_count;
        bits |= highest_bits(*bytes, bit_count);
    }

    val = bits;
    return true;
}

bool BitBuffer::read_bits(uint32_t& val, size_t bit_count)
{
    return peek_bits(val, bit_count) && consume_bits(bit_count);
}

bool BitBuffer::consume_bytes(size_t byte_count)
{
    return consume_bits(byte_count * 8);
}

bool BitBuffer::consume_bits(size_t bit_count)
{
    if (bit_count > remaining_bit_count())
    {
        return false;
    }

    _byte_offset += (_bit_offset + bit_count) / 8;
    _bit_offset = (_bit_offset + bit_count) % 8;

    return true;
}

bool BitBuffer::read_exponential_golomb(uint32_t& val)
{
    size_t original_byte_offset = _byte_offset;
    size_t original_bit_offset = _bit_offset;

    size_t zero_bit_count = 0;
    uint32_t peeked_bit;
    while (peek_bits(peeked_bit, 1) && peeked_bit == 0)
    {
        zero_bit_count++;
        consume_bits(1);
    }

    size_t value_bit_count = zero_bit_count + 1;
    if (value_bit_count > 32 || !read_bits(val, value_bit_count))
    {
        seek(original_byte_offset, original_bit_offset);
        return false;
    }

    val -= 1;
    return true;
}

bool BitBuffer::read_signed_exponential_golomb(int32_t& val)
{
    uint32_t unsigned_val;
    if (!read_exponential_golomb(unsigned_val))
    {
        return false;
    }

    if ((unsigned_val & 1) == 0)
    {
        val = -static_cast<int32_t>(unsigned_val / 2);
    }
    else
    {
        val = (unsigned_val + 1) / 2;
    }

    return true;
}

bool BitBuffer::seek(size_t byte_offset, size_t bit_offset)
{
    if (byte_offset > _byte_count || bit_offset > 7
        ||(byte_offset == _byte_count && bit_offset > 0))
    {
        return false;
    }

    _byte_offset = byte_offset;
    _bit_offset = bit_offset;

    return true;
}

BitBufferWriter::BitBufferWriter(uint32_t capacity/* = 512*/)
    : _capacity(capacity)
{
    _buf = new uint8_t[_capacity];
    memset(_buf, 0, _capacity);
}

BitBufferWriter::~BitBufferWriter()
{
    if (_buf)
    {
        delete [] _buf;
    }
}

int BitBufferWriter::write_bits(uint8_t val, size_t bit_count)
{
    if (bit_count > 8 || bit_count == 0 || val >= (1UL << bit_count))
    {
        return -1;
    }

    if (bit_count > remaining_bit_count())
    {
        return -2;
    }

    uint8_t* buf = _buf + _byte_offset;
    size_t remaining_bits_in_current_byte = 8 - _bit_offset;
    if (bit_count <= remaining_bits_in_current_byte)
    {
        *buf |= (val << (remaining_bits_in_current_byte - bit_count));
        grow_bits(bit_count);
        return 0;
    }

    *buf |= (val >> (bit_count - remaining_bits_in_current_byte));
    bit_count -= remaining_bits_in_current_byte;
    grow_bits(remaining_bits_in_current_byte);

    buf++;
    *buf = (val << (8 - bit_count));
    grow_bits(bit_count);

    return 0;
}

size_t BitBufferWriter::byte_count() const
{
    if (_bit_offset == 0 && _byte_offset == 0)
    {
        return 0;
    }

    return _byte_offset + (_bit_offset % 8 ? 1 : 0);
}

bool BitBufferWriter::copy(uint8_t* buf)
{
    if (!_buf)
    {
        return false;
    }

    if (_bit_offset % 8 != 0)
    {
        padding();
    }

    memcpy(buf, _buf, byte_count());
    return true;
}

bool BitBufferWriter::grow_bits(size_t bit_count)
{
    _byte_offset += (_bit_offset + bit_count) / 8;
    _bit_offset = (_bit_offset + bit_count) % 8;

    return true;
}

size_t BitBufferWriter::remaining_bit_count() const
{
    return (_capacity - _byte_offset) * 8 - _bit_offset;
}

bool BitBufferWriter::padding()
{
    if (0 != write_bits(0, 8 - _bit_offset))
    {
        return false;
    }

    return true;
}

}
