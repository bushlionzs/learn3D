#include "net_ssl.h"
#include <platform_log.h>
#include <platform_mutex.h>
#include <scoped_lock.h>
#include <pid.h>

#ifndef DY_NETWORK_DISNABLE_SSL

#ifdef _WIN32
//#include <WinSock2.h>
#endif
typedef struct {
    SSL_CTX                    *ctx;
}net_ssl_t;



static net_ssl_t _g_net_ssl;

static void ngx_ssl_info_callback(const SSL *ssl_conn, int where, int ret)
{
   // BIO               *rbio, *wbio;
   // ngx_connection_t  *c;

   // if (where & SSL_CB_HANDSHAKE_START) {
   //     c = ngx_ssl_get_connection((ngx_ssl_conn_t *) ssl_conn);

   //     if (c->ssl->handshaked) {
   //         c->ssl->renegotiation = 1;
   //         ngx_log_debug0(NGX_LOG_DEBUG_EVENT, c->log, 0, "SSL renegotiation");
   //     }
   // }

   // if ((where & SSL_CB_ACCEPT_LOOP) == SSL_CB_ACCEPT_LOOP) {
   //     c = ngx_ssl_get_connection((ngx_ssl_conn_t *) ssl_conn);

    //    if (!c->ssl->handshake_buffer_set) {
            /*
             * By default OpenSSL uses 4k buffer during a handshake,
             * which is too low for long certificate chains and might
             * result in extra round-trips.
             *
             * To adjust a buffer size we detect that buffering was added
             * to write side of the connection by comparing rbio and wbio.
             * If they are different, we assume that it's due to buffering
             * added to wbio, and set buffer size.
             */

      //      rbio = SSL_get_rbio((ngx_ssl_conn_t *) ssl_conn);
      //      wbio = SSL_get_wbio((ngx_ssl_conn_t *) ssl_conn);

      //      if (rbio != wbio) {
      //          (void) BIO_set_write_buffer_size(wbio, NGX_SSL_BUFSIZE);
      //          c->ssl->handshake_buffer_set = 1;
      //      }
      //  }
   // }
}

int  ngx_ssl_certificate_index;
int  ngx_ssl_next_certificate_index;

int32_t ngx_ssl_certificate(net_ssl_t *ssl, const char *cert, const char* key);
static PlatformMutex *_lock_cs = NULL;
static dy::common::pid_t pthreads_thread_id(void)
{
    return dy::common::gettid();
}

static void pthreads_locking_callback(int mode, int type, const char *file, int line)
{
    if (mode & CRYPTO_LOCK)
    {
       _lock_cs[type].lock();
    }
    else
    {
		_lock_cs[type].unlock();
    }
}

void net_ssl_thread_init()
{
	_lock_cs = new PlatformMutex[CRYPTO_num_locks()];
   
   CRYPTO_set_id_callback((unsigned long (*)())pthreads_thread_id);
   CRYPTO_set_locking_callback(pthreads_locking_callback);
}

int32_t net_ssl_init(const char* crt, const char* key, bool is_cdn_ssl)
{
	OPENSSL_config(NULL);

	SSL_library_init();
	SSL_load_error_strings();

	OpenSSL_add_all_algorithms();

    
    net_ssl_thread_init();
    
    net_ssl_t *ssl = &_g_net_ssl;
    
    ssl->ctx = SSL_CTX_new(SSLv23_method());
	//SSL_CTX_set_verify(ssl->ctx, SSL_VERIFY_NONE, NULL);
    
	
    SSL_CTX_set_options(ssl->ctx, SSL_OP_SSLREF2_REUSE_CERT_TYPE_BUG);
    SSL_CTX_set_options(ssl->ctx, SSL_OP_MICROSOFT_BIG_SSLV3_BUFFER);
    SSL_CTX_set_options(ssl->ctx, SSL_OP_MSIE_SSLV2_RSA_PADDING);
    SSL_CTX_set_options(ssl->ctx, SSL_OP_SSLEAY_080_CLIENT_DH_BUG);
    SSL_CTX_set_options(ssl->ctx, SSL_OP_TLS_D5_BUG);
    SSL_CTX_set_options(ssl->ctx, SSL_OP_TLS_BLOCK_PADDING_BUG);
    SSL_CTX_set_options(ssl->ctx, SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS);
    SSL_CTX_set_options(ssl->ctx, SSL_OP_SINGLE_DH_USE);
    SSL_CTX_clear_options(ssl->ctx, SSL_OP_NO_SSLv2|SSL_OP_NO_SSLv3|SSL_OP_NO_TLSv1);
    SSL_CTX_set_options(ssl->ctx, SSL_OP_NO_COMPRESSION);
    SSL_CTX_set_mode(ssl->ctx, SSL_MODE_NO_AUTO_CHAIN);
    SSL_CTX_set_read_ahead(ssl->ctx, 1);
    SSL_CTX_set_info_callback(ssl->ctx, ngx_ssl_info_callback);

    if(is_cdn_ssl){
        const char* ssl_ciphers = "HIGH:!aNULL:!eNULL:!EXPORT:!DES:!MD5:!PSK:!RC4";
        int result = SSL_CTX_set_cipher_list(ssl->ctx, (char *)ssl_ciphers);
        if(result != 1)
        {
            printf("SSL_CTX_set_cipher_list '%s' failed,ret %d\n", ssl_ciphers, result);
            return -1;
        }
        SSL_CTX_set_options(ssl->ctx, SSL_OP_CIPHER_SERVER_PREFERENCE);
        SSL_CTX_set_options(ssl->ctx, SSL_OP_NO_SSLv3);
        SSL_CTX_set_options(ssl->ctx, SSL_OP_NO_SSLv2);
    }

    ngx_ssl_certificate_index = SSL_CTX_get_ex_new_index(0, NULL, NULL, NULL, NULL);
    if (ngx_ssl_certificate_index == -1) {
        return -1;
    }

    ngx_ssl_next_certificate_index = X509_get_ex_new_index(0, NULL, NULL, NULL, NULL);
    if (ngx_ssl_next_certificate_index == -1) {
        return -1;
    }
    
    if (SSL_CTX_set_ex_data(ssl->ctx, ngx_ssl_certificate_index, NULL) == 0) {
        return -1;
    }
    
    if (crt[0] != 0 && key[0] != 0)
    {
        if (0 != ngx_ssl_certificate(ssl, crt, key))
        {
            printf("ngx_ssl_certificate failed\n");
        }
    }
	
    printf("ssl init successfully,crt:%s,key:%s\n", crt, key);
    return 0;
}
static PlatformMutex _ssl_mutex;
ssl_connection_t* create_ssl_connection(int fd, bool is_client)
{
    ssl_connection_t* sc = (ssl_connection_t*)malloc(sizeof(ssl_connection_t));
    memset(sc, 0, sizeof(ssl_connection_t));
    sc->session_ctx = _g_net_ssl.ctx;
    sc->connection = SSL_new(_g_net_ssl.ctx);
    if (NULL == sc->connection)
    {
        return NULL;
    }
#ifndef _WIN32
    if (SSL_set_fd(sc->connection, fd) == 0) {
        return NULL;
    }
#endif    
#ifdef _WIN32
	sc->bio_in = BIO_new(BIO_s_mem());
	sc->bio_out = BIO_new(BIO_s_mem());
	SSL_set_bio(sc->connection, sc->bio_in, sc->bio_out);
	sc->ssl_recv_buf_size = 1024 * 128;
	sc->ssl_recv_buf = (char*)malloc(sc->ssl_recv_buf_size);
#endif 
    if (!is_client)
    {
        SSL_set_accept_state(sc->connection);
    }
    else
    {
        SSL_set_connect_state(sc->connection);
    }
    return sc;
}

void destroy_ssl_connection(ssl_connection_t* sc)
{
    //SSL_shutdown(sc->connection);
    SSL_free(sc->connection);
    sc->connection = 0;
    free(sc);
}

void shutdown_ssl_connection(ssl_connection_t* sc)
{
    if (!sc || !sc->connection || SSL_in_init(sc->connection))
    {
        return ;
    }

    int n = SSL_shutdown(sc->connection);
    if (n != 1 && ERR_peek_error())
    {
        int sslerr = SSL_get_error(sc->connection, n);
        WARNING_LOG("[err:%d,n:%d, sys err:%d]SSL_shutdown error", sslerr, n, errno);
    }
}

void ngx_ssl_clear_error()
{
    ERR_clear_error();
}

int32_t ngx_ssl_handshake(ssl_connection_t* sc)
{
    int        n, sslerr;
    
    ngx_ssl_clear_error();
    
    n = SSL_do_handshake(sc->connection);
    
    if (1 == n)
    {
        sc->handshaked = 1;
#if OPENSSL_VERSION_NUMBER < 0x10100000L
#ifdef SSL3_FLAGS_NO_RENEGOTIATE_CIPHERS
        if (sc->connection->s3)
        {
            sc->connection->s3->flags |= SSL3_FLAGS_NO_RENEGOTIATE_CIPHERS;
        }
#endif
#endif
    }
    else
    {
        sslerr = SSL_get_error(sc->connection, n);
        if (sslerr == SSL_ERROR_WANT_READ || sslerr == SSL_ERROR_WANT_WRITE)
        {
            return EAGAIN;
        }
        WARNING_LOG("[err:%d,n:%d, sys err:%d]ngx_ssl_handshake error", sslerr, n, errno);
        return -1;
    }
    return 0;
}

int32_t ngx_ssl_certificate(net_ssl_t *ssl, const char *cert, const char* key)
{
    BIO         *bio;
    X509        *x509;
    char        *pwd;
    u_long       n;
    uint32_t    tries;

    bio = BIO_new_file((char *)cert, "r");
    if (bio == NULL) {
        return -1;
    }

    x509 = PEM_read_bio_X509_AUX(bio, NULL, NULL, NULL);
    if (x509 == NULL) {
        BIO_free(bio);
        return -1;
    }

    if (SSL_CTX_use_certificate(ssl->ctx, x509) == 0) {
        X509_free(x509);
        BIO_free(bio);
        return -1;
    }

    if (X509_set_ex_data(x509, ngx_ssl_next_certificate_index,
                      SSL_CTX_get_ex_data(ssl->ctx, ngx_ssl_certificate_index))
        == 0)
    {
        X509_free(x509);
        BIO_free(bio);
        return -1;
    }

    if (SSL_CTX_set_ex_data(ssl->ctx, ngx_ssl_certificate_index, x509)
        == 0)
    {
        X509_free(x509);
        BIO_free(bio);
        return -1;
    }

    /* read rest of the chain */

    for ( ;; ) {

        x509 = PEM_read_bio_X509(bio, NULL, NULL, NULL);
        if (x509 == NULL) {
            n = ERR_peek_last_error();

            if (ERR_GET_LIB(n) == ERR_LIB_PEM
                && ERR_GET_REASON(n) == PEM_R_NO_START_LINE)
            {
                /* end of file */
                ERR_clear_error();
                break;
            }

            /* some real error */

            BIO_free(bio);
            return -1;
        }

#ifdef SSL_CTRL_CHAIN_CERT
        if (SSL_CTX_add0_chain_cert(ssl->ctx, x509) == 0) {
            X509_free(x509);
            BIO_free(bio);
            return -1;
        }
#else
        if (SSL_CTX_add_extra_chain_cert(ssl->ctx, x509) == 0) {
            X509_free(x509);
            BIO_free(bio);
            return -1;
        }
#endif
    }

    BIO_free(bio);

    if (strncmp(key, "engine:", sizeof("engine:") - 1) == 0) {
        return -1;
    }
    tries = 1;
    pwd = NULL;

    for ( ;; ) {

        if (SSL_CTX_use_PrivateKey_file(ssl->ctx, (char *)key, SSL_FILETYPE_PEM)
            != 0)
        {
            break;
        }

        if (--tries) {
            ERR_clear_error();
            SSL_CTX_set_default_passwd_cb_userdata(ssl->ctx, ++pwd);
            continue;
        }

        return -1;
    }

    SSL_CTX_set_default_passwd_cb(ssl->ctx, NULL);

    return 0;
}

#endif
