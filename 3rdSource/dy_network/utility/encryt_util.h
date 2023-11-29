#ifndef __ENCRY_UTIL_H__
#define __ENCRY_UTIL_H__

unsigned char *p2p_des_cbc_encrypt(const unsigned char *clear_text, int *text_len,
	const unsigned char *key, int key_len,
	const unsigned char *iv, int iv_len);
unsigned char *p2p_des_cbc_decrypt(const unsigned char *cipher_text, int *text_len,
	const unsigned char *key, int key_len,
	const unsigned char *iv, int iv_len);
	
#endif //__ENCRY_UTIL_H__