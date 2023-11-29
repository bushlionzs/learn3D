#ifndef __NET_SSL_H__
#define __NET_SSL_H__

#include <stdint.h>
#include <stddef.h>

#ifndef DY_NETWORK_DISNABLE_SSL

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bn.h>
#include <openssl/conf.h>
#include <openssl/crypto.h>
#include <openssl/dh.h>
#ifndef OPENSSL_NO_ENGINE
#include <openssl/engine.h>
#endif
#include <openssl/evp.h>
#ifndef OPENSSL_NO_OCSP
#include <openssl/ocsp.h>
#endif
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

typedef struct 
{
    SSL                 *connection;
#ifdef _WIN32
    BIO* bio_in;
    BIO* bio_out;
    char* ssl_recv_buf;
    int32_t ssl_recv_buf_size;
#endif
    SSL_CTX             *session_ctx;
    int32_t             last;

    unsigned                    handshaked : 1;
    unsigned                    renegotiation : 1;
    unsigned                    buffer : 1;
    unsigned                    no_wait_shutdown : 1;
    unsigned                    no_send_shutdown : 1;
    unsigned                    handshake_buffer_set : 1;
}ssl_connection_t;

int32_t net_ssl_init(const char* crt, const char* key, bool is_cdn_ssl);

int32_t ngx_ssl_handshake(ssl_connection_t* sc);

ssl_connection_t* create_ssl_connection(int fd, bool is_client = false);
void destroy_ssl_connection(ssl_connection_t* sc);
void shutdown_ssl_connection(ssl_connection_t* sc);

#else

struct SSL;
struct BIO;
struct SSL_CTX;

// SSL_ERROR_WANT_WRITE indicates the operation failed attempting to write to
// the transport. The caller may retry the operation when the transport is ready
// for writing.
#define SSL_ERROR_WANT_WRITE 3

typedef struct
{
    SSL                 *connection;
#ifdef _WIN32
    BIO* bio_in;
    BIO* bio_out;
    char* ssl_recv_buf;
    uint32_t ssl_recv_buf_size;
#endif
    SSL_CTX             *session_ctx;
    int32_t             last;

    unsigned                    handshaked : 1;
    unsigned                    renegotiation : 1;
    unsigned                    buffer : 1;
    unsigned                    no_wait_shutdown : 1;
    unsigned                    no_send_shutdown : 1;
    unsigned                    handshake_buffer_set : 1;
} ssl_connection_t;

inline int32_t net_ssl_init(const char* crt, const char* key, bool is_cdn_ssl) { return 0; }
inline int32_t ngx_ssl_handshake(ssl_connection_t* sc) { return -1; }
inline ssl_connection_t* create_ssl_connection(int fd, bool is_client = false) { return nullptr; }
inline void destroy_ssl_connection(ssl_connection_t* sc) { }
inline void shutdown_ssl_connection(ssl_connection_t* sc) {}

inline int SSL_read(SSL *ssl, void *buf, int num) { return -1; }
inline int SSL_write(SSL *ssl, const void *buf, int num) { return -1; }
inline int SSL_get_error(const SSL *ssl, int ret_code) { return -1; }
inline int SSL_is_init_finished(const SSL *ssl) { return -1; }

inline int BIO_read(BIO *bio, void *data, int len) { return -1; }
inline int BIO_write(BIO *bio, const void *data, int len) { return -1; }
inline size_t BIO_pending(const BIO *bio) { return 0; }
#endif // DY_NETWORK_DISNABLE_SSL

#endif //__NET_SSL_H__