/*$T Common/EncryptAriths/Mars.h GC 1.140 10/10/07 10:06:29 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __MARS_H__
#define __MARS_H__

#include "CryptDef.h"

class MARS :
	public BlockTransformation
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { KEYLENGTH = 16, BLOCKSIZE = 16 };

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 BlockSize() const
	{
		return BLOCKSIZE;
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	void			SetUserKey(const byte *userKey);

	static const uint32	Sbox[512];

	SecBlock<uint32, 40>	EK;
};

class MARSEncryption :
	public MARS
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	void	SetUserKey(const byte *userKey);

	void	ProcessBlock(const byte *inBlock, byte *outBlock) const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void ProcessBlock(byte *inoutBlock) const
	{
		MARSEncryption::ProcessBlock(inoutBlock, inoutBlock);
	}
};

class MARSDecryption :
	public MARS
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	void	SetUserKey(const byte *userKey);

	void	ProcessBlock(const byte *inBlock, byte *outBlock) const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void ProcessBlock(byte *inoutBlock) const
	{
		MARSDecryption::ProcessBlock(inoutBlock, inoutBlock);
	}
};
#endif