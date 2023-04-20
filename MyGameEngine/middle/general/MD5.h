namespace ku
{

	#define ENABLE_GETMD5STRING
	#define ENABLE_GETMD5FILE

	char* PrintMD5( unsigned char md5Digest[16] );
	#if defined(ENABLE_GETMD5STRING) || defined (ENABLE_GETMD5RANDOM)
		char* MD5String(const char* szString);
	#endif

	#if defined(ENABLE_GETMD5FILE)
		char* MD5File(const char* szFilename);
	#endif


	class md5
	{
	// Methods
	public:

		md5() { Init(); }
		void	Init();
		void	Update(unsigned char* chInput, unsigned int nInputLen);
		void	Finalize();
		unsigned char*	Digest() { return m_Digest; }

	private:

		void	Transform(unsigned char* block);
		void	Encode(unsigned char* dest, unsigned int* src, unsigned int nLength);
		void	Decode(unsigned int* dest, unsigned char* src, unsigned int nLength);


		inline	unsigned int	rotate_left(unsigned int x, unsigned int n)
						{ return ((x << n) | (x >> (32-n))); }

		inline	unsigned int	F(unsigned int x, unsigned int y, unsigned int z)
						{ return ((x & y) | (~x & z)); }

		inline  unsigned int	G(unsigned int x, unsigned int y, unsigned int z)
						{ return ((x & z) | (y & ~z)); }

		inline  unsigned int	H(unsigned int x, unsigned int y, unsigned int z)
						{ return (x ^ y ^ z); }

		inline  unsigned int	I(unsigned int x, unsigned int y, unsigned int z)
						{ return (y ^ (x | ~z)); }

		inline	void	FF(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac)
						{ a += F(b, c, d) + x + ac; a = rotate_left(a, s); a += b; }

		inline	void	GG(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac)
						{ a += G(b, c, d) + x + ac; a = rotate_left(a, s); a += b; }

		inline	void	HH(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac)
						{ a += H(b, c, d) + x + ac; a = rotate_left(a, s); a += b; }

		inline	void	II(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac)
						{ a += I(b, c, d) + x + ac; a = rotate_left(a, s); a += b; }

	// Data
	private:

		unsigned int		m_State[4];
		unsigned int		m_Count[2];
		unsigned char		m_Buffer[64];
		unsigned char		m_Digest[16];
		unsigned char		m_Finalized;

	};	// class md5

};	// namespace 
