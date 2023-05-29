// RSA public key encryption

#ifndef __RSA__H__
#define __RSA__H__

#include "vlong.h"

static vlong from_str( const char * s,const int offset = 0  )
{
	vlong x = 0;
	while (*s)
	{
		x = x * vlong(256) + vlong( ((unsigned char)*s)-offset );
		s += 1;
	}
	return x;
}

static void vlong_to_str( const vlong& plain,const char * pOut )
{
	//
}

class public_key
{
  public:
  vlong m,e;
  vlong encrypt( const vlong& plain ); // Requires 0 <= plain < m

  int RSA_Encode(char * s,vlong& out);
};

class private_key : public public_key
{
  public:
  vlong p,q;
  vlong decrypt( const vlong& cipher );

  void create( const char * r1, const char * r2 );
  // r1 and r2 should be null terminated random strings
  // each of length around 35 characters (for a 500 bit modulus)

  int RSA_Decode(char * s,vlong& out,vlong& output);
};

#endif
