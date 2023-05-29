/*$T Common/EncryptAriths/BitOper.cpp GC 1.140 10/10/07 10:06:29 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "BitOper.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

void BitOperBase::SetUserKey(const uchar *key)
{
	m_BlockLen = BUFSIZE;
	memset(m_szUserKey, 0, KEYLENGTH);
	memcpy(m_szUserKey, key, KEYLENGTH);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BitOperEncryption1::SetUserKey(const uchar *key)
{
	BitOperBase::SetUserKey(key);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BitOperEncryption1::ProcessBlock(const uchar *in, uchar *out) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	userKey = (uint32) atoi(m_szUserKey);
	uint32	startPos = userKey % BUFSIZE;
	uint32	endPos = BUFSIZE - startPos;
	char	tmpBuf[BUFSIZE] = { 0 };
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memcpy(tmpBuf, out, BUFSIZE);
	memcpy(out, tmpBuf + startPos, endPos);
	memcpy(out + endPos, tmpBuf, startPos);

	for(int32 num = 0; num < BUFSIZE; ++num)
	{
		out[num] = out[num] ^ userKey;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BitOperDecryption1::SetUserKey(const uchar *key)
{
	BitOperBase::SetUserKey(key);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BitOperDecryption1::ProcessBlock(const uchar *in, uchar *out) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	userKey = (uint32) atoi(m_szUserKey);
	uint32	startPos = userKey % BUFSIZE;
	uint32	endPos = BUFSIZE - startPos;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 num = 0; num < BUFSIZE; ++num)
	{
		out[num] = out[num] ^ userKey;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char	tmpBuf[BUFSIZE] = { 0 };
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memcpy(tmpBuf, out, BUFSIZE);
	memcpy(out, tmpBuf + endPos, startPos);
	memcpy(out + startPos, tmpBuf, endPos);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BitOperEncryption2::SetUserKey(const uchar *key)
{
	BitOperBase::SetUserKey(key);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BitOperEncryption2::ProcessBlock(const uchar *in, uchar *out) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	userKey = (uint32) atoi(m_szUserKey);
	uint32	startPos = userKey % BUFSIZE;
	uint32	endPos = BUFSIZE - startPos;
	char	tmpBuf[BUFSIZE] = { 0 };
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memcpy(tmpBuf, out, BUFSIZE);
	memcpy(out, tmpBuf + startPos, endPos);
	memcpy(out + endPos, tmpBuf, startPos);

	for(int32 num = 0; num < BUFSIZE; ++num)
	{
		out[num] = ~out[num];
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BitOperDecryption2::SetUserKey(const uchar *key)
{
	BitOperBase::SetUserKey(key);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BitOperDecryption2::ProcessBlock(const uchar *in, uchar *out) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	userKey = (uint32) atoi(m_szUserKey);
	uint32	startPos = userKey % BUFSIZE;
	uint32	endPos = BUFSIZE - startPos;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 num = 0; num < BUFSIZE; ++num)
	{
		out[num] = ~out[num];
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char	tmpBuf[BUFSIZE] = { 0 };
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memcpy(tmpBuf, out, BUFSIZE);
	memcpy(out, tmpBuf + endPos, startPos);
	memcpy(out + startPos, tmpBuf, endPos);
}
