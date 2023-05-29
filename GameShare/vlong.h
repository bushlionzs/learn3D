
#ifndef __VLONG_H__
#define __VLONG_H__

class vlong // very long integer - can be used like long
{
public:
  // Standard arithmetic operators
  friend vlong operator +( const vlong& x, const vlong& y );
  friend vlong operator -( const vlong& x, const vlong& y );
  friend vlong operator *( const vlong& x, const vlong& y );
  friend vlong operator /( const vlong& x, const vlong& y );
  friend vlong operator %( const vlong& x, const vlong& y );
  vlong& operator +=( const vlong& x );
  vlong& operator -=( const vlong& x );

  // Standard comparison operators
  friend inline int operator !=( const vlong& x, const vlong& y ){ return x.cf( y ) != 0; }
  friend inline int operator ==( const vlong& x, const vlong& y ){ return x.cf( y ) == 0; }
  friend inline int operator >=( const vlong& x, const vlong& y ){ return x.cf( y ) >= 0; }
  friend inline int operator <=( const vlong& x, const vlong& y ){ return x.cf( y ) <= 0; }
  friend inline int operator > ( const vlong& x, const vlong& y ){ return x.cf( y ) > 0; }
  friend inline int operator < ( const vlong& x, const vlong& y ){ return x.cf( y ) < 0; }

  // Construction and conversion operations
  vlong ( unsigned x=0 );
  vlong ( const vlong& x );
  ~vlong();
  operator unsigned ();
  vlong& operator =(const vlong& x);

 #if defined _70_WORLD
  char* tostring(char* output,int len);
  void  Binary2Str(char* input,char* output,int offset,int inPutLen);
#endif

  //public data funcs
  unsigned get( unsigned i ) const;
  unsigned get_z(void) const;

  unsigned int getShare();
  unsigned	getN() ;
  unsigned	getZ() ;
  unsigned	getArr(int id) ;

  void	setShare(unsigned int val);
  void	setN(unsigned val) ;
  void	setZ(unsigned val) ;
  void	setArr(int id,unsigned val) ;

public:
  class vlong_value * value;
  int negative;
  int cf( const vlong x ) const;
  void docopy();
  friend class monty;
};

vlong modexp( const vlong & x, const vlong & e, const vlong & m ); // m must be odd
vlong gcd( const vlong &X, const vlong &Y ); // greatest common denominator
vlong modinv( const vlong &a, const vlong &m ); // modular inverse

#endif


