#ifndef _BYTE_ORDER_H_INCLUDED
#define _BYTE_ORDER_H_INCLUDED

#include <stdint.h>
#include <type_traits>

#ifdef _WIN32
#include <stdlib.h>

#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN 4321

// defined by cmake TestBigEndian
#ifdef _OS_USE_BIG_ENDIAN
#define __BYTE_ORDER __BIG_ENDIAN
#else
#define __BYTE_ORDER __LITTLE_ENDIAN
#endif

#if __BYTE_ORDER == __LITTLE_ENDIAN

#define htobe16(x) _byteswap_ushort(x)
#define htole16(x) (x)
#define be16toh(x) _byteswap_ushort(x)
#define le16toh(x) (x)

#define htobe32(x) _byteswap_ulong(x)
#define htole32(x) (x)
#define be32toh(x) _byteswap_ulong(x)
#define le32toh(x) (x)

#define htobe64(x) _byteswap_uint64(x)
#define htole64(x) (x)
#define be64toh(x) _byteswap_uint64(x)
#define le64toh(x) (x)

#else

#define htobe16(x) (x)
#define htole16(x) _byteswap_ushort(x)
#define be16toh(x) (x)
#define le16toh(x) _byteswap_ushort(x)

#define htobe32(x) (x)
#define htole32(x) _byteswap_ulong(x)
#define be32toh(x) (x)
#define le32toh(x) _byteswap_ulong(x)

#define htobe64(x) (x)
#define htole64(x) _byteswap_uint64(x)
#define be64toh(x) (x)
#define le64toh(x) _byteswap_uint64(x)

#endif // __BYTE_ORDER == __LITTLE_ENDIAN

#else

#ifdef __APPLE__
#include <libkern/OSByteOrder.h>

#define htobe16(v) OSSwapHostToBigInt16(v)
#define htobe32(v) OSSwapHostToBigInt32(v)
#define htobe64(v) OSSwapHostToBigInt64(v)
#define be16toh(v) OSSwapBigToHostInt16(v)
#define be32toh(v) OSSwapBigToHostInt32(v)
#define be64toh(v) OSSwapBigToHostInt64(v)

#define htole16(v) OSSwapHostToLittleInt16(v)
#define htole32(v) OSSwapHostToLittleInt32(v)
#define htole64(v) OSSwapHostToLittleInt64(v)
#define le16toh(v) OSSwapLittleToHostInt16(v)
#define le32toh(v) OSSwapLittleToHostInt32(v)
#define le64toh(v) OSSwapLittleToHostInt64(v)
#else
#if defined(__ANDROID__)
#include <endian.h>

#define be16toh(x) htobe16(x)
#define be32toh(x) htobe32(x)
#define be64toh(x) htobe64(x)
#define le16toh(x) htole16(x)
#define le32toh(x) htole32(x)
#define le64toh(x) htole64(x)
#else 
#if __linux__
#include <endian.h>
#endif
#endif
#endif

#endif // _WIN32

template<typename T, size_t N = sizeof(T)>
union BytesNumber
{
    static_assert(std::is_integral<T>::value, "T muse be integral type");
    static_assert(N <= sizeof(T), "N <= sizeof(T)");

    T number;
    char bytes[N];

    constexpr BytesNumber(T n = 0) : number(n) {}
    constexpr operator T() const { return number; }
    BytesNumber& operator=(T n)
    {
        number = n;
        return *this;
    }
};

struct BigEndian
{
    static int16_t read_i16(const void *buf)
    {
        return be16toh(*static_cast<const int16_t *>(buf));
    }

    static uint16_t read_u16(const void *buf)
    {
        return be16toh(*static_cast<const uint16_t *>(buf));
    }

    static int32_t read_i24(const void *buf)
    {
        BytesNumber<int32_t, 3> dst;

        const char *src = static_cast<const char *>(buf);
#if __BYTE_ORDER == __LITTLE_ENDIAN
        dst.bytes[0] = src[2];
        dst.bytes[1] = src[1];
        dst.bytes[2] = src[0];
#else
        dst.bytes[0] = src[0];
        dst.bytes[1] = src[1];
        dst.bytes[2] = src[2];
#endif
        return dst.number;
    }

    static uint32_t read_u24(const void *buf)
    {
        BytesNumber<uint32_t, 3> dst;

        const char *src = static_cast<const char *>(buf);
#if __BYTE_ORDER == __LITTLE_ENDIAN
        dst.bytes[0] = src[2];
        dst.bytes[1] = src[1];
        dst.bytes[2] = src[0];
#else
        dst.bytes[0] = src[0];
        dst.bytes[1] = src[1];
        dst.bytes[2] = src[2];
#endif
        return dst.number;
    }

    static int32_t read_i32(const void *buf)
    {
        return be32toh(*static_cast<const int32_t *>(buf));
    }

    static uint32_t read_u32(const void *buf)
    {
        return be32toh(*static_cast<const uint32_t *>(buf));
    }

    static int64_t read_i64(const void *buf)
    {
        return be64toh(*static_cast<const int64_t *>(buf));
    }

    static uint64_t read_u64(const void *buf)
    {
        return be64toh(*static_cast<const uint64_t *>(buf));
    }

    static void write_i16(void *buf, int16_t value)
    {
        *static_cast<int16_t *>(buf) = htobe16(value);
    }

    static void write_u16(void *buf, uint16_t value)
    {
        *static_cast<uint16_t *>(buf) = htobe16(value);
    }

    static void write_i24(void *buf, int32_t value)
    {
        BytesNumber<int32_t, 3> src = value;

        char *dst = static_cast<char *>(buf);
#if __BYTE_ORDER == __LITTLE_ENDIAN
        dst[0] = src.bytes[2];
        dst[1] = src.bytes[1];
        dst[2] = src.bytes[0];
#else
        dst[0] = src.bytes[0];
        dst[1] = src.bytes[1];
        dst[2] = src.bytes[2];
#endif
    }

    static void write_u24(void *buf, uint32_t value)
    {
        BytesNumber<uint32_t, 3> src = value;

        char *dst = static_cast<char *>(buf);
#if __BYTE_ORDER == __LITTLE_ENDIAN
        dst[0] = src.bytes[2];
        dst[1] = src.bytes[1];
        dst[2] = src.bytes[0];
#else
        dst[0] = src.bytes[0];
        dst[1] = src.bytes[1];
        dst[2] = src.bytes[2];
#endif
    }

    static void write_i32(void *buf, int32_t value)
    {
        *static_cast<int32_t *>(buf) = htobe32(value);
    }

    static void write_u32(void *buf, uint32_t value)
    {
        *static_cast<uint32_t *>(buf) = htobe32(value);
    }

    static void write_i64(void *buf, int64_t value)
    {
        *static_cast<int64_t *>(buf) = htobe64(value);
    }

    static void write_u64(void *buf, uint64_t value)
    {
        *static_cast<uint64_t *>(buf) = htobe64(value);
    }
};

struct LittleEndian
{
    static int16_t read_i16(const void *buf)
    {
        return le16toh(*static_cast<const int16_t *>(buf));
    }

    static uint16_t read_u16(const void *buf)
    {
        return le16toh(*static_cast<const uint16_t *>(buf));
    }

    static int32_t read_i24(const void *buf)
    {
        BytesNumber<int32_t, 3> dst;

        const char *src = static_cast<const char *>(buf);
#if __BYTE_ORDER == __BIG_ENDIAN
        dst.bytes[0] = src[2];
        dst.bytes[1] = src[1];
        dst.bytes[2] = src[0];
#else
        dst.bytes[0] = src[0];
        dst.bytes[1] = src[1];
        dst.bytes[2] = src[2];
#endif
        return dst.number;
    }

    static uint32_t read_u24(const void *buf)
    {
        BytesNumber<uint32_t, 3> dst;

        const char *src = static_cast<const char *>(buf);
#if __BYTE_ORDER == __BIG_ENDIAN
        dst.bytes[0] = src[2];
        dst.bytes[1] = src[1];
        dst.bytes[2] = src[0];
#else
        dst.bytes[0] = src[0];
        dst.bytes[1] = src[1];
        dst.bytes[2] = src[2];
#endif
        return dst.number;
    }

    static int32_t read_i32(const void *buf)
    {
        return le32toh(*static_cast<const int32_t *>(buf));
    }

    static uint32_t read_u32(const void *buf)
    {
        return le32toh(*static_cast<const uint32_t *>(buf));
    }

    static int64_t read_i64(const void *buf)
    {
        return le64toh(*static_cast<const int64_t *>(buf));
    }

    static uint64_t read_u64(const void *buf)
    {
        return le64toh(*static_cast<const uint64_t *>(buf));
    }

    static void write_i16(void *buf, int16_t value)
    {
        *static_cast<int16_t *>(buf) = htole16(value);
    }

    static void write_u16(void *buf, uint16_t value)
    {
        *static_cast<uint16_t *>(buf) = htole16(value);
    }

    static void write_i24(void *buf, int32_t value)
    {
        BytesNumber<int32_t, 3> src = value;

        char *dst = static_cast<char *>(buf);
#if __BYTE_ORDER == __BIG_ENDIAN
        dst[0] = src.bytes[2];
        dst[1] = src.bytes[1];
        dst[2] = src.bytes[0];
#else
        dst[0] = src.bytes[0];
        dst[1] = src.bytes[1];
        dst[2] = src.bytes[2];
#endif
    }

    static void write_u24(void *buf, uint32_t value)
    {
        BytesNumber<uint32_t, 3> src = value;

        char *dst = static_cast<char *>(buf);
#if __BYTE_ORDER == __BIG_ENDIAN
        dst[0] = src.bytes[2];
        dst[1] = src.bytes[1];
        dst[2] = src.bytes[0];
#else
        dst[0] = src.bytes[0];
        dst[1] = src.bytes[1];
        dst[2] = src.bytes[2];
#endif
    }

    static void write_i32(void *buf, int32_t value)
    {
        *static_cast<int32_t *>(buf) = htole32(value);
    }

    static void write_u32(void *buf, uint32_t value)
    {
        *static_cast<uint32_t *>(buf) = htole32(value);
    }

    static void write_i64(void *buf, int64_t value)
    {
        *static_cast<int64_t *>(buf) = htole64(value);
    }

    static void write_u64(void *buf, uint64_t value)
    {
        *static_cast<uint64_t *>(buf) = htole64(value);
    }
};

using NetworkEndian = BigEndian;

#endif // !_BYTE_ORDER_H_INCLUDED
