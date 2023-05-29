/*$T Common/EncryptAriths/rc6.cpp GC 1.140 10/10/07 10:06:30 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "rc6.h"

#define ROTL(x, y)	(rotl((x), (uint32) (y) % (sizeof(RC6_WORD) * 8)))
#define ROTR(x, y)	(rotr((x), (uint32) (y) % (sizeof(RC6_WORD) * 8)))

/*
 =======================================================================================================================
 =======================================================================================================================
 */

RC6Base::RC6Base(uint32 rounds) :
	r(rounds)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void RC6Base::SetUserKey(const byte *k)
{
	m_BlockLen = KEYLENGTH;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	static const RC6_WORD	MAGIC_P = 0xb7e15163L;
	static const RC6_WORD	MAGIC_Q = 0x9e3779b9L;
	static const int	U = sizeof(RC6_WORD);
	const uint32		c = (KEYLENGTH - 1) / U + 1;
	SecBlock<RC6_WORD, c>	l;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	l[(KEYLENGTH - 1) / U] = 0;
	for(int i = (KEYLENGTH - 1); i >= 0; i--) l[i / U] = (l[i / U] << 8) + k[i];

	sTable[0] = MAGIC_P;
	for(unsigned j = 1; j < sTable.m_size; j++) sTable[j] = sTable[j - 1] + MAGIC_Q;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	RC6_WORD	a = 0, b = 0;
	const unsigned	n = 3 * max(sTable.m_size, c);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(unsigned h = 0; h < n; h++)
	{
		a = sTable[h % sTable.m_size] = ROTL((sTable[h % sTable.m_size] + a + b), 3);
		b = l[h % c] = ROTL((l[h % c] + a + b), (a + b));
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
static inline void GETBLOCK(const byte *block, uint32 &a, uint32 &b, uint32 &c, uint32 &d)
{
#ifdef IS_LITTLE_ENDIAN
	a = *(uint32 *) block;
	b = *(uint32 *) (block + 4);
	c = *(uint32 *) (block + 8);
	d = *(uint32 *) (block + 12);
#else
	a = byteReverse(*(uint32 *) block);
	b = byteReverse(*(uint32 *) (block + 4));
	c = byteReverse(*(uint32 *) (block + 8));
	d = byteReverse(*(uint32 *) (block + 12));
#endif
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
static inline void PUTBLOCK(byte *block, uint32 a, uint32 b, uint32 c, uint32 d)
{
#ifdef IS_LITTLE_ENDIAN
	* (uint32 *) block = a;
	*(uint32 *) (block + 4) = b;
	*(uint32 *) (block + 8) = c;
	*(uint32 *) (block + 12) = d;
#else
	* (uint32 *) block = byteReverse(a);
	*(uint32 *) (block + 4) = byteReverse(b);
	*(uint32 *) (block + 8) = byteReverse(c);
	*(uint32 *) (block + 12) = byteReverse(d);
#endif
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void RC6Encryption::SetUserKey(const byte *key)
{
	RC6Base::SetUserKey(key);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void RC6Encryption::ProcessBlock(const byte *in, byte *out) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const RC6_WORD	*sptr = sTable;
	RC6_WORD	a, b, c, d, t, u;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GETBLOCK(in, a, b, c, d);
	b += sptr[0];
	d += sptr[1];
	sptr += 2;

	for(unsigned i = 0; i < r; i++)
	{
		t = ROTL(b * (2 * b + 1), 5);
		u = ROTL(d * (2 * d + 1), 5);
		a = ROTL(a ^ t, u) + sptr[0];
		c = ROTL(c ^ u, t) + sptr[1];
		t = a;
		a = b;
		b = c;
		c = d;
		d = t;
		sptr += 2;
	}

	a += sptr[0];
	c += sptr[1];

	PUTBLOCK(out, a, b, c, d);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void RC6Decryption::SetUserKey(const byte *key)
{
	RC6Base::SetUserKey(key);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void RC6Decryption::ProcessBlock(const byte *in, byte *out) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const RC6_WORD	*sptr = sTable + sTable.m_size;
	RC6_WORD	a, b, c, d, t, u;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GETBLOCK(in, a, b, c, d);

	sptr -= 2;
	c -= sptr[1];
	a -= sptr[0];

	for(unsigned i = 0; i < r; i++)
	{
		sptr -= 2;
		t = a;
		a = d;
		d = c;
		c = b;
		b = t;
		u = ROTL(d * (2 * d + 1), 5);
		t = ROTL(b * (2 * b + 1), 5);
		c = ROTR(c - sptr[1], t) ^ u;
		a = ROTR(a - sptr[0], u) ^ t;
	}

	sptr -= 2;
	d -= sTable[1];
	b -= sTable[0];

	PUTBLOCK(out, a, b, c, d);
}
