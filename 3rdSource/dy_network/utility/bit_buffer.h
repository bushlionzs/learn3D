#pragma once

#include <cstdint>
#include <cstddef>
#include <type_traits>
#include <limits>

namespace dy_network
{

class BitBuffer 
{
public:
    BitBuffer(const uint8_t* bytes, size_t byte_count);

    size_t byte_offset() const { return _byte_offset; }
    size_t bit_offset() const { return _bit_offset; }
    size_t remaining_bit_count() const;

    template<typename T>
    bool read_uint(T &val)
    {
        static_assert(std::is_unsigned<T>::value, "T muse be unsigned");
        static_assert(sizeof(T) <= sizeof(uint32_t), "sizeof T must le uint32_t");

        uint32_t bit_val;
        if (!read_bits(bit_val, sizeof(T) * 8))
        {
            return false;
        }

        if (bit_val > std::numeric_limits<T>::max())
        {
            return  false;
        }

        val = static_cast<T>(bit_val);

        return true;
    }

    bool read_uint8(uint8_t& val);
    bool read_uint16(uint16_t& val);
    bool read_uint32(uint32_t& val);

    bool read_bits(uint32_t& val, size_t bit_count);
    bool peek_bits(uint32_t& val, size_t bit_count);

    bool read_exponential_golomb(uint32_t& val);
    bool read_signed_exponential_golomb(int32_t& val);

    bool consume_bytes(size_t byte_count);
    bool consume_bits(size_t bit_count);

    bool seek(size_t byte_offset, size_t bit_offset);
protected:
    const uint8_t* const _bytes = nullptr;
    size_t _byte_count = 0;
    size_t _byte_offset = 0;
    size_t _bit_offset = 0;
};

class BitBufferWriter
{
public:
    BitBufferWriter(uint32_t capacity = 512);
    ~BitBufferWriter();

    int write_bits(uint8_t val, size_t bit_count);
    size_t byte_count() const;
    bool copy(uint8_t* buf);
    bool padding();

private:
    bool grow_bits(size_t bit_count);
    size_t remaining_bit_count() const;

private:
    size_t _capacity = 0;
    size_t _bit_offset = 0;
    size_t _byte_offset = 0;
    uint8_t* _buf = nullptr;
};

}

