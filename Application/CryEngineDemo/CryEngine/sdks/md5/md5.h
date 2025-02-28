#ifndef MD5_H
#define MD5_H

struct MD5Context
{
	unsigned int buf[4];
	unsigned int bits[2];
	unsigned char in[64];
};

#ifdef __cplusplus
extern "C"
{
#endif
extern void MD5Init( struct MD5Context *ctx );
extern void MD5Update( struct MD5Context *ctx,unsigned char *buf,unsigned len );
extern void MD5Final( unsigned char digest[16],struct MD5Context *ctx );
extern void MD5Transform( unsigned int buf[4],unsigned int in[16] );

#ifdef __cplusplus
};
#endif

/*
 * This is needed to make RSAREF happy on some MS-DOS compilers.
 */
typedef struct MD5Context MD5_CTX;

#endif /* !MD5_H */
