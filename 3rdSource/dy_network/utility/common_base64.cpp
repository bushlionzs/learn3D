#include "common_base64.h"
#include <string.h>
#include <assert.h>
#ifndef DY_NETWORK_DISNABLE_SSL
#include <openssl/md5.h>
#endif
#include <stdlib.h>
#include <cinttypes>

#ifdef DY_NETWORK_DISNABLE_SSL

/// copy from openssl's md5.h/md5.c

typedef struct md5_state_st MD5_CTX;

static inline void *OPENSSL_memset(void *dst, int c, size_t n) {
    if (n == 0) {
        return dst;
    }

    return memset(dst, c, n);
}

static inline void *OPENSSL_memcpy(void *dst, const void *src, size_t n) {
    if (n == 0) {
        return dst;
    }

    return memcpy(dst, src, n);
}

// MD5_CBLOCK is the block size of MD5.
#define MD5_CBLOCK 64

// MD5_DIGEST_LENGTH is the length of an MD5 digest.
#define MD5_DIGEST_LENGTH 16

// MD5_Init initialises |md5| and returns one.
int MD5_Init(MD5_CTX *md5);

// MD5_Update adds |len| bytes from |data| to |md5| and returns one.
int MD5_Update(MD5_CTX *md5, const void *data, size_t len);

// MD5_Final adds the final padding to |md5| and writes the resulting digest to
// |md|, which must have at least |MD5_DIGEST_LENGTH| bytes of space. It
// returns one.
int MD5_Final(uint8_t *md, MD5_CTX *md5);

// MD5 writes the digest of |len| bytes from |data| to |out| and returns |out|.
// There must be at least |MD5_DIGEST_LENGTH| bytes of space in |out|.
uint8_t *MD5(const uint8_t *data, size_t len, uint8_t *out);

// MD5_Transform is a low-level function that performs a single, MD5 block
// transformation using the state from |md5| and 64 bytes from |block|.
void MD5_Transform(MD5_CTX *md5, const uint8_t *block);

struct md5_state_st {
    uint32_t h[4];
    uint32_t Nl, Nh;
    uint8_t data[MD5_CBLOCK];
    unsigned num;
};

uint8_t *MD5(const uint8_t *data, size_t len, uint8_t *out) {
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, data, len);
    MD5_Final(out, &ctx);

    return out;
}

int MD5_Init(MD5_CTX *md5) {
    OPENSSL_memset(md5, 0, sizeof(MD5_CTX));
    md5->h[0] = 0x67452301UL;
    md5->h[1] = 0xefcdab89UL;
    md5->h[2] = 0x98badcfeUL;
    md5->h[3] = 0x10325476UL;
    return 1;
}

#if !defined(OPENSSL_NO_ASM) && \
    (defined(OPENSSL_X86_64) || defined(OPENSSL_X86))
#define MD5_ASM
#define md5_block_data_order md5_block_asm_data_order
extern void md5_block_data_order(uint32_t *state, const uint8_t *data,
    size_t num);
#else
static void md5_block_data_order(uint32_t *state, const uint8_t *data,
    size_t num);
#endif


#define DATA_ORDER_IS_LITTLE_ENDIAN

#define HASH_CTX MD5_CTX
#define HASH_CBLOCK 64
#define HASH_UPDATE MD5_Update
#define HASH_TRANSFORM MD5_Transform
#define HASH_FINAL MD5_Final
#define HASH_MAKE_STRING(c, s) \
  do {                         \
    uint32_t ll;               \
    ll = (c)->h[0];            \
    HOST_l2c(ll, (s));         \
    ll = (c)->h[1];            \
    HOST_l2c(ll, (s));         \
    ll = (c)->h[2];            \
    HOST_l2c(ll, (s));         \
    ll = (c)->h[3];            \
    HOST_l2c(ll, (s));         \
  } while (0)
#define HASH_BLOCK_DATA_ORDER md5_block_data_order

// This is a generic 32-bit "collector" for message digest algorithms. It
// collects input character stream into chunks of 32-bit values and invokes the
// block function that performs the actual hash calculations. To make use of
// this mechanism, the following macros must be defined before including
// md32_common.h.
//
// One of |DATA_ORDER_IS_BIG_ENDIAN| or |DATA_ORDER_IS_LITTLE_ENDIAN| must be
// defined to specify the byte order of the input stream.
//
// |HASH_CBLOCK| must be defined as the integer block size, in bytes.
//
// |HASH_CTX| must be defined as the name of the context structure, which must
// have at least the following members:
//
//     typedef struct <name>_state_st {
//       uint32_t h[<chaining length> / sizeof(uint32_t)];
//       uint32_t Nl, Nh;
//       uint8_t data[HASH_CBLOCK];
//       unsigned num;
//       ...
//     } <NAME>_CTX;
//
// <chaining length> is the output length of the hash in bytes, before
// any truncation (e.g. 64 for SHA-224 and SHA-256, 128 for SHA-384 and
// SHA-512).
//
// |HASH_UPDATE| must be defined as the name of the "Update" function to
// generate.
//
// |HASH_TRANSFORM| must be defined as the  the name of the "Transform"
// function to generate.
//
// |HASH_FINAL| must be defined as the name of "Final" function to generate.
//
// |HASH_BLOCK_DATA_ORDER| must be defined as the name of the "Block" function.
// That function must be implemented manually. It must be capable of operating
// on *unaligned* input data in its original (data) byte order. It must have
// this signature:
//
//     void HASH_BLOCK_DATA_ORDER(uint32_t *state, const uint8_t *data,
//                                size_t num);
//
// It must update the hash state |state| with |num| blocks of data from |data|,
// where each block is |HASH_CBLOCK| bytes; i.e. |data| points to a array of
// |HASH_CBLOCK * num| bytes. |state| points to the |h| member of a |HASH_CTX|,
// and so will have |<chaining length> / sizeof(uint32_t)| elements.
//
// |HASH_MAKE_STRING(c, s)| must be defined as a block statement that converts
// the hash state |c->h| into the output byte order, storing the result in |s|.

#if !defined(DATA_ORDER_IS_BIG_ENDIAN) && !defined(DATA_ORDER_IS_LITTLE_ENDIAN)
#error "DATA_ORDER must be defined!"
#endif

#ifndef HASH_CBLOCK
#error "HASH_CBLOCK must be defined!"
#endif
#ifndef HASH_CTX
#error "HASH_CTX must be defined!"
#endif

#ifndef HASH_UPDATE
#error "HASH_UPDATE must be defined!"
#endif
#ifndef HASH_TRANSFORM
#error "HASH_TRANSFORM must be defined!"
#endif
#ifndef HASH_FINAL
#error "HASH_FINAL must be defined!"
#endif

#ifndef HASH_BLOCK_DATA_ORDER
#error "HASH_BLOCK_DATA_ORDER must be defined!"
#endif

#ifndef HASH_MAKE_STRING
#error "HASH_MAKE_STRING must be defined!"
#endif

#if defined(DATA_ORDER_IS_BIG_ENDIAN)

#define HOST_c2l(c, l)                     \
  do {                                     \
    (l) = (((uint32_t)(*((c)++))) << 24);  \
    (l) |= (((uint32_t)(*((c)++))) << 16); \
    (l) |= (((uint32_t)(*((c)++))) << 8);  \
    (l) |= (((uint32_t)(*((c)++))));       \
  } while (0)

#define HOST_l2c(l, c)                        \
  do {                                        \
    *((c)++) = (uint8_t)(((l) >> 24) & 0xff); \
    *((c)++) = (uint8_t)(((l) >> 16) & 0xff); \
    *((c)++) = (uint8_t)(((l) >> 8) & 0xff);  \
    *((c)++) = (uint8_t)(((l)) & 0xff);       \
  } while (0)

#elif defined(DATA_ORDER_IS_LITTLE_ENDIAN)

#define HOST_c2l(c, l)                     \
  do {                                     \
    (l) = (((uint32_t)(*((c)++))));        \
    (l) |= (((uint32_t)(*((c)++))) << 8);  \
    (l) |= (((uint32_t)(*((c)++))) << 16); \
    (l) |= (((uint32_t)(*((c)++))) << 24); \
  } while (0)

#define HOST_l2c(l, c)                        \
  do {                                        \
    *((c)++) = (uint8_t)(((l)) & 0xff);       \
    *((c)++) = (uint8_t)(((l) >> 8) & 0xff);  \
    *((c)++) = (uint8_t)(((l) >> 16) & 0xff); \
    *((c)++) = (uint8_t)(((l) >> 24) & 0xff); \
  } while (0)

#endif  // DATA_ORDER

int HASH_UPDATE(HASH_CTX *c, const void *data_, size_t len) {
    const uint8_t *data = static_cast<const uint8_t*>(data_);

    if (len == 0) {
        return 1;
    }

    uint32_t l = c->Nl + (((uint32_t)len) << 3);
    if (l < c->Nl) {
        // Handle carries.
        c->Nh++;
    }
    c->Nh += (uint32_t)(len >> 29);
    c->Nl = l;

    size_t n = c->num;
    if (n != 0) {
        if (len >= HASH_CBLOCK || len + n >= HASH_CBLOCK) {
            OPENSSL_memcpy(c->data + n, data, HASH_CBLOCK - n);
            HASH_BLOCK_DATA_ORDER(c->h, c->data, 1);
            n = HASH_CBLOCK - n;
            data += n;
            len -= n;
            c->num = 0;
            // Keep |c->data| zeroed when unused.
            OPENSSL_memset(c->data, 0, HASH_CBLOCK);
        }
        else {
            OPENSSL_memcpy(c->data + n, data, len);
            c->num += (unsigned)len;
            return 1;
        }
    }

    n = len / HASH_CBLOCK;
    if (n > 0) {
        HASH_BLOCK_DATA_ORDER(c->h, data, n);
        n *= HASH_CBLOCK;
        data += n;
        len -= n;
    }

    if (len != 0) {
        c->num = (unsigned)len;
        OPENSSL_memcpy(c->data, data, len);
    }
    return 1;
}


void HASH_TRANSFORM(HASH_CTX *c, const uint8_t *data) {
    HASH_BLOCK_DATA_ORDER(c->h, data, 1);
}


int HASH_FINAL(uint8_t *md, HASH_CTX *c) {
    // |c->data| always has room for at least one byte. A full block would have
    // been consumed.
    size_t n = c->num;
    assert(n < HASH_CBLOCK);
    c->data[n] = 0x80;
    n++;

    // Fill the block with zeros if there isn't room for a 64-bit length.
    if (n > (HASH_CBLOCK - 8)) {
        OPENSSL_memset(c->data + n, 0, HASH_CBLOCK - n);
        n = 0;
        HASH_BLOCK_DATA_ORDER(c->h, c->data, 1);
    }
    OPENSSL_memset(c->data + n, 0, HASH_CBLOCK - 8 - n);

    // Append a 64-bit length to the block and process it.
    uint8_t *p = c->data + HASH_CBLOCK - 8;
#if defined(DATA_ORDER_IS_BIG_ENDIAN)
    HOST_l2c(c->Nh, p);
    HOST_l2c(c->Nl, p);
#elif defined(DATA_ORDER_IS_LITTLE_ENDIAN)
    HOST_l2c(c->Nl, p);
    HOST_l2c(c->Nh, p);
#endif
    assert(p == c->data + HASH_CBLOCK);
    HASH_BLOCK_DATA_ORDER(c->h, c->data, 1);
    c->num = 0;
    OPENSSL_memset(c->data, 0, HASH_CBLOCK);

    HASH_MAKE_STRING(c, md);
    return 1;
}

// As pointed out by Wei Dai <weidai@eskimo.com>, the above can be
// simplified to the code below.  Wei attributes these optimizations
// to Peter Gutmann's SHS code, and he attributes it to Rich Schroeppel.
#define F(b, c, d) ((((c) ^ (d)) & (b)) ^ (d))
#define G(b, c, d) ((((b) ^ (c)) & (d)) ^ (c))
#define H(b, c, d) ((b) ^ (c) ^ (d))
#define I(b, c, d) (((~(d)) | (b)) ^ (c))

#define ROTATE(a, n) (((a) << (n)) | ((a) >> (32 - (n))))

#define R0(a, b, c, d, k, s, t)            \
  do {                                     \
    (a) += ((k) + (t) + F((b), (c), (d))); \
    (a) = ROTATE(a, s);                    \
    (a) += (b);                            \
  } while (0)

#define R1(a, b, c, d, k, s, t)            \
  do {                                     \
    (a) += ((k) + (t) + G((b), (c), (d))); \
    (a) = ROTATE(a, s);                    \
    (a) += (b);                            \
  } while (0)

#define R2(a, b, c, d, k, s, t)            \
  do {                                     \
    (a) += ((k) + (t) + H((b), (c), (d))); \
    (a) = ROTATE(a, s);                    \
    (a) += (b);                            \
  } while (0)

#define R3(a, b, c, d, k, s, t)            \
  do {                                     \
    (a) += ((k) + (t) + I((b), (c), (d))); \
    (a) = ROTATE(a, s);                    \
    (a) += (b);                            \
  } while (0)

#ifndef MD5_ASM
#ifdef X
#undef X
#endif
static void md5_block_data_order(uint32_t *state, const uint8_t *data,
    size_t num) {
    uint32_t A, B, C, D, l;
    uint32_t XX0, XX1, XX2, XX3, XX4, XX5, XX6, XX7, XX8, XX9, XX10, XX11, XX12,
        XX13, XX14, XX15;
#define X(i) XX##i

    A = state[0];
    B = state[1];
    C = state[2];
    D = state[3];

    for (; num--;) {
        HOST_c2l(data, l);
        X(0) = l;
        HOST_c2l(data, l);
        X(1) = l;
        // Round 0
        R0(A, B, C, D, X(0), 7, 0xd76aa478L);
        HOST_c2l(data, l);
        X(2) = l;
        R0(D, A, B, C, X(1), 12, 0xe8c7b756L);
        HOST_c2l(data, l);
        X(3) = l;
        R0(C, D, A, B, X(2), 17, 0x242070dbL);
        HOST_c2l(data, l);
        X(4) = l;
        R0(B, C, D, A, X(3), 22, 0xc1bdceeeL);
        HOST_c2l(data, l);
        X(5) = l;
        R0(A, B, C, D, X(4), 7, 0xf57c0fafL);
        HOST_c2l(data, l);
        X(6) = l;
        R0(D, A, B, C, X(5), 12, 0x4787c62aL);
        HOST_c2l(data, l);
        X(7) = l;
        R0(C, D, A, B, X(6), 17, 0xa8304613L);
        HOST_c2l(data, l);
        X(8) = l;
        R0(B, C, D, A, X(7), 22, 0xfd469501L);
        HOST_c2l(data, l);
        X(9) = l;
        R0(A, B, C, D, X(8), 7, 0x698098d8L);
        HOST_c2l(data, l);
        X(10) = l;
        R0(D, A, B, C, X(9), 12, 0x8b44f7afL);
        HOST_c2l(data, l);
        X(11) = l;
        R0(C, D, A, B, X(10), 17, 0xffff5bb1L);
        HOST_c2l(data, l);
        X(12) = l;
        R0(B, C, D, A, X(11), 22, 0x895cd7beL);
        HOST_c2l(data, l);
        X(13) = l;
        R0(A, B, C, D, X(12), 7, 0x6b901122L);
        HOST_c2l(data, l);
        X(14) = l;
        R0(D, A, B, C, X(13), 12, 0xfd987193L);
        HOST_c2l(data, l);
        X(15) = l;
        R0(C, D, A, B, X(14), 17, 0xa679438eL);
        R0(B, C, D, A, X(15), 22, 0x49b40821L);
        // Round 1
        R1(A, B, C, D, X(1), 5, 0xf61e2562L);
        R1(D, A, B, C, X(6), 9, 0xc040b340L);
        R1(C, D, A, B, X(11), 14, 0x265e5a51L);
        R1(B, C, D, A, X(0), 20, 0xe9b6c7aaL);
        R1(A, B, C, D, X(5), 5, 0xd62f105dL);
        R1(D, A, B, C, X(10), 9, 0x02441453L);
        R1(C, D, A, B, X(15), 14, 0xd8a1e681L);
        R1(B, C, D, A, X(4), 20, 0xe7d3fbc8L);
        R1(A, B, C, D, X(9), 5, 0x21e1cde6L);
        R1(D, A, B, C, X(14), 9, 0xc33707d6L);
        R1(C, D, A, B, X(3), 14, 0xf4d50d87L);
        R1(B, C, D, A, X(8), 20, 0x455a14edL);
        R1(A, B, C, D, X(13), 5, 0xa9e3e905L);
        R1(D, A, B, C, X(2), 9, 0xfcefa3f8L);
        R1(C, D, A, B, X(7), 14, 0x676f02d9L);
        R1(B, C, D, A, X(12), 20, 0x8d2a4c8aL);
        // Round 2
        R2(A, B, C, D, X(5), 4, 0xfffa3942L);
        R2(D, A, B, C, X(8), 11, 0x8771f681L);
        R2(C, D, A, B, X(11), 16, 0x6d9d6122L);
        R2(B, C, D, A, X(14), 23, 0xfde5380cL);
        R2(A, B, C, D, X(1), 4, 0xa4beea44L);
        R2(D, A, B, C, X(4), 11, 0x4bdecfa9L);
        R2(C, D, A, B, X(7), 16, 0xf6bb4b60L);
        R2(B, C, D, A, X(10), 23, 0xbebfbc70L);
        R2(A, B, C, D, X(13), 4, 0x289b7ec6L);
        R2(D, A, B, C, X(0), 11, 0xeaa127faL);
        R2(C, D, A, B, X(3), 16, 0xd4ef3085L);
        R2(B, C, D, A, X(6), 23, 0x04881d05L);
        R2(A, B, C, D, X(9), 4, 0xd9d4d039L);
        R2(D, A, B, C, X(12), 11, 0xe6db99e5L);
        R2(C, D, A, B, X(15), 16, 0x1fa27cf8L);
        R2(B, C, D, A, X(2), 23, 0xc4ac5665L);
        // Round 3
        R3(A, B, C, D, X(0), 6, 0xf4292244L);
        R3(D, A, B, C, X(7), 10, 0x432aff97L);
        R3(C, D, A, B, X(14), 15, 0xab9423a7L);
        R3(B, C, D, A, X(5), 21, 0xfc93a039L);
        R3(A, B, C, D, X(12), 6, 0x655b59c3L);
        R3(D, A, B, C, X(3), 10, 0x8f0ccc92L);
        R3(C, D, A, B, X(10), 15, 0xffeff47dL);
        R3(B, C, D, A, X(1), 21, 0x85845dd1L);
        R3(A, B, C, D, X(8), 6, 0x6fa87e4fL);
        R3(D, A, B, C, X(15), 10, 0xfe2ce6e0L);
        R3(C, D, A, B, X(6), 15, 0xa3014314L);
        R3(B, C, D, A, X(13), 21, 0x4e0811a1L);
        R3(A, B, C, D, X(4), 6, 0xf7537e82L);
        R3(D, A, B, C, X(11), 10, 0xbd3af235L);
        R3(C, D, A, B, X(2), 15, 0x2ad7d2bbL);
        R3(B, C, D, A, X(9), 21, 0xeb86d391L);

        A = state[0] += A;
        B = state[1] += B;
        C = state[2] += C;
        D = state[3] += D;
    }
}
#undef X
#endif

#undef DATA_ORDER_IS_LITTLE_ENDIAN
#undef HASH_CTX
#undef HASH_CBLOCK
#undef HASH_UPDATE
#undef HASH_TRANSFORM
#undef HASH_FINAL
#undef HASH_MAKE_STRING
#undef HASH_BLOCK_DATA_ORDER
#undef F
#undef G
#undef H
#undef I
#undef ROTATE
#undef R0
#undef R1
#undef R2
#undef R3
#undef HOST_c2l
#undef HOST_l2c

#endif


static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(const unsigned char * data, unsigned int in_len) {
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--) {
        char_array_3[i++] = *(data++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';

    }

    return ret;

}

std::string base64_decode(const unsigned char* data, uint32_t size) {
    int in_len = size;
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (in_len-- && (data[in_] != '=') && is_base64(data[in_])) {
        char_array_4[i++] = data[in_]; in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = (unsigned char)base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (j = 0; j < 4; j++)
            char_array_4[j] = (unsigned  char )base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }

    return ret;
}

int md5_translate(uint64_t start_second, const std::string&sec_key, std::string& std_md5_hex, std::string& str_des_key)
{
    char md5_src[128];
    char md5_hex[128] = { 0 };
    unsigned char md5[16] = { 0 };
    char time_stamp_original[25] = { 0 };
    snprintf(time_stamp_original, 24, "%06" PRIu64, start_second);
    int time_stamp_length = static_cast<int>(strlen(time_stamp_original));
    int skip_length = time_stamp_length - 6;
    snprintf(md5_src, sizeof(md5_src) - 1, "%s%sxy", time_stamp_original + skip_length, sec_key.c_str());
    MD5_CTX c;
    MD5_Init(&c);
    MD5_Update(&c, (const unsigned char *)md5_src, strlen(md5_src));
    MD5_Final(md5, &c);

    for (int i = 0; i < 16; ++i) {
        snprintf(md5_hex + 2 * i, 33 - 2 * i, "%02x", md5[i]);
    }

    int des_key_offset = static_cast<int>(sec_key.size() - 5);
    int des_time_offset = static_cast<int>(strlen(time_stamp_original) - 3);
    char des_key[16] = { 0 };
    snprintf(des_key, sizeof(des_key), "%s%s", sec_key.c_str() + des_key_offset, time_stamp_original + des_time_offset);
    str_des_key = des_key;
    std_md5_hex = md5_hex;
    return 0;
}

std::string base64_encode_random(uint32_t size)
{
    unsigned char key[256];

    if (size > 256)
    {
        size = 256;
    }

    for (uint32_t i = 0; i < size; i++)
    {
        key[i] = rand() % 256 - 1;
    }
    return base64_encode(key, size);
}
