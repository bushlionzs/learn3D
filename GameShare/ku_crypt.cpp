
#include "OgreHeader.h"
#include "ku.h"
#include "MD5.h"


//------------------
// "khan0707"
// "khan0203"
// "khan"
//------------------

//------------------ TW
// "khan_tw0707"
// "khan_tw0203"
// "khan_tw"
//------------------

//------------------ HK
// "khan_hk0707"
// "khan_hk0203"
// "khan_hk"
//------------------

const char g_szKey1[] = "khan0707";	// FileConversion  -- 表
const char g_szKey2[] = "khan0203";	// FileConversion
const char g_szKey3[] = "khan";		// LuaFileConversion		-- lua


//----------------------------------------------------------------------------
// 加密1
// 
// -- nOffset	指定数组大概一半的尺寸，所以其值为 源串长度
// -- nAppend	附加尺寸
//				如：64可以指定30，余下的附加存储其它的信息
// -- 方法：前部保存随机值，后部保存计算结果，存储位存放随机的偏移值
int ku::CKU::GetEncryptCode( int nOffset, int nAppend, const char* szSource, char* szResult )	//  = 30;	// 登陆
{
	if( NULL == szSource ||
		NULL == szResult )
	{
//			::MessageBox( NULL, "20001", "成吉思汗 提示", NULL );	// 源值为空
		return 1;
	}

	// 生成的长度
	int nSourceLen = (int)strlen( szSource );
//	if( nSourceLen != nOffset )
//	{
//		::MessageBox( NULL, "20002", "成吉思汗 提示", NULL );	// 偏移长度错误
//		return ;
//	}

	// 总长
	int nCodeLen = nOffset * 2 + nAppend;

//	char cName[ nCodeLen ] = { 0 };
//	char cCommun[MAX_VERIFY_CODE] = { 0 };
	char* szName = new char[ nCodeLen ];

	for( INT num = 0; num < nCodeLen; ++num )
	{
		szName[ num ]	= rand() % 99;
		szResult[ num ]	= szName[ num ];
	}

	for( INT len = 0; len < nSourceLen; ++len )
		szName[ len + nOffset ] = (CHAR)( szSource[ len ] ) - szName[ len ];
//		cName[ len + nOffset ] = (CHAR)( strUserName.at( len ) );

	INT nRandIndex = rand() % nOffset - 1;	// 偏移索引
	if( nRandIndex < 0 || nRandIndex > nOffset )
		nRandIndex = 0;
	INT nIndex = nRandIndex;

	for( INT num = 0; num < nSourceLen; ++num )
	{
		if( nIndex >= nOffset )
			nIndex = 0;

		szResult[ nIndex ]			 = szName[ num ];
		szResult[ nIndex + nOffset ] = szName[ num + nOffset ];

		++nIndex;
	}
	szResult[ nCodeLen - 1 ] = nRandIndex;

	delete [] szName;

	return 0;
}

//----------------------------------------------------------------------------
// 加密2
int ku::CKU::GetEncryptCode( int nSize, int nOffset, int nIsLawless, int nSource, char* szResult )	// 移动
{
	if( 0 >= nSource )
	{
//			::MessageBox( NULL, "20003", "成吉思汗 提示", NULL );	// 无效的数字
		return 1;
	}

	// 
	char cCheckSum = 0;
	char szSource[16] = { 0 };
	_snprintf( szSource, 16, "%d", nSource );
	
	int nStrLen = (int)strlen( szSource );
	for( INT len = 0; len < nStrLen; ++len )
		cCheckSum = cCheckSum ^ szSource[ len ]; // 进行异或校验取值

	// 
//	char szCommun[nSize];
	for( INT num = 0; num < nSize; ++num )
		szResult[ num ] = rand() % 127;	// 

	char ch = ( cCheckSum >> 4 ) & 0x0F;	// 取高位数； 
	char cl = cCheckSum & 0x0F;				// 取低位数；

	int n3 = nOffset % 10;						// 个位
	int n2 = ( ( nOffset % 100 ) - n3 ) / 10;	// 十位
	int n1 = nOffset / 100;						// 百位

	if( n1 < 0 || n1 >= nSize )
		return 1;
	if( n2 < 0 || n2 >= nSize )
		return 1;
	if( n3 < 0 || n3 >= nSize )
		return 1;

	szResult[ n1 ] = nIsLawless + n1;
	szResult[ n2 ] = ch + n1;
	szResult[ n3 ] = cl;

	return 0;
}


//----------------------------------------------------------------------------
// 加密3
int ku::CKU::GetEncryptCode( int nSize, int nOffset, int nSource, char* szResult, int nIsLawless )	// 锁定目标
{
	int n3 = nOffset % 10;						// 个位
	int n2 = ( ( nOffset % 100 ) - n3 ) / 10;	// 十位
	int n1 = nOffset / 100;						// 百位

	nSource = nSource ^ nOffset;
	nSource += ( n2 * 100 + n1 * 10 + n3 );		// 颠倒偏移
	nSource = ~nSource ;

	char szSource[32] = { 0 };
	_snprintf( szSource, 32, "%d", nSource );

	for( INT num = 0; num < nSize; ++num )
		szResult[ num ] = rand() % 127;	// 

	int strLen = (int)strlen( szSource );
	for( INT len = 0; len < strLen; ++len )
		szResult[ len + 2 ] = szSource[ len ];

	szResult[ 0 ]		  = 1;
	szResult[ 1 ]		  = nIsLawless;

	szResult[ nSize - 2 ] = 0;
	szResult[ nSize - 1 ] = strLen;

	int nRand = rand() % 2;
	switch( nRand )
	{
	case 0:
		{
			szResult[ nSize - 2 ] = 1;
//			szResult[ nSize - 1 ] = 1;
		}
		break;

	case 1:
		{
			szResult[ nSize - 2 ] = 0;
//			szResult[ nSize - 1 ] = 0;
		}
		break;
	};

	return 0;
}


//----------------------------------------------------------------------------
// 加密4
int ku::CKU::GetEncryptCode( int nSize, int nOffset, int nSource, char* szResult )	// 心跳
{
	int n3 = nOffset % 10;						// 个位
	int n2 = ( ( nOffset % 100 ) - n3 ) / 10;	// 十位
	int n1 = nOffset / 100;						// 百位

	int nTmp = ( n3 & n2 ) | n1;

	nSource = nSource ^ nTmp;

	char szSource[32] = { 0 };
	_snprintf( szSource, 32, "%d", nSource );

	for( int num = 0; num < nSize; ++num )
		szResult[ num ] = rand() % 200;	// 

	int strLen = (int)strlen( szSource );
	for( int len = 0; len < strLen; ++len )
		szResult[ len + 4 ] = szSource[ len ];

	szResult[ nSize - 1 ] = strLen;

	return 0;
}

//----------------------------------------------------------------------------
// 通用算法，随机使用

// convert unsigned char to string of length 2
void Char2Hex( unsigned char ch, char* szHex )
{
	unsigned char byte[2];
	byte[0] = ch / 16;
	byte[1] = ch % 16;

	for( int i = 0; i < 2; i++ )
	{
		if( byte[i] >= 0 && byte[i] <= 9 )
			szHex[i] = '0' + byte[i];
		else
			szHex[i] = 'A' + byte[i] - 10;
	};

	szHex[2] = 0;
}

// convert string of length 2 to unsigned char
void Hex2Char( char const* szHex, unsigned char& rch )
{
	rch = 0;
	for( int i = 0; i < 2; i++ )
	{
		if( *(szHex + i) >='0' && *(szHex + i) <= '9' )
			rch = (rch << 4) + (*(szHex + i) - '0');
		else if( *(szHex + i) >='A' && *(szHex + i) <= 'F' )
			rch = (rch << 4) + (*(szHex + i) - 'A' + 10);
		else
			break;
	}
}

// convert string of unsigned chars to string of chars
void ku::CKU::CharStr2HexStr( unsigned char const* pucCharStr, char* pszHexStr, int iSize )
{
	char szHex[3];
	pszHexStr[0] = 0;

	for( int i = 0; i < iSize; i++ )
	{
		Char2Hex( pucCharStr[i], szHex );
		strcat( pszHexStr, szHex );
	}
}

// convert string of chars to string of unsigned chars
void ku::CKU::HexStr2CharStr( char const* pszHexStr, unsigned char* pucCharStr, int iSize )
{
	unsigned char ch;
	for( int i = 0; i < iSize; i++ )
	{
		Hex2Char( pszHexStr + 2 * i, ch );
		pucCharStr[i] = ch;
	}
}

//----------------------------------------------------------------------------
// 根据不同的类型处理加密算法
int ku::CKU::EncryptCode( int nType, int nKey, const char* szSource, char* szResult )
{
	if( NULL == szSource || NULL == szResult )
		return 1;

	int nStrLen = static_cast<int>( strlen( szSource ) );
	if( nStrLen <= 0 )
		return 1;

	switch( nType )
	{
	// 登录密码
	case 8:
		{
			for( int i = 0; i < 32; ++i )	// MD5码的固定长度
			szResult[ i ] = szSource[i] ^ nKey;
			return 1;
		}
		break;

	case 9:
		{
			// 加密处理
			int llKey   = 27854;
			int nOffset = 67;

			char szTmpKey[ 32 ] = { 0 };
			_snprintf( szTmpKey, 32, "kylin%d", nKey );
			int nKeyLen = strlen( szTmpKey );
			for( int nIdx = 0; nIdx < nKeyLen; ++nIdx )
				llKey ^= szTmpKey[ nIdx ] | 128;

			for( int nIdx = 0; nIdx < nStrLen; ++nIdx )
			{
				szResult[ nIdx ] = szSource[ nIdx ] ^ llKey;
				szResult[ nIdx ] = szSource[ nIdx ] ^ ( nStrLen + nOffset );
			};

			return 1;
		}
		break;

	default:
		break;
	};


	char* szHexStr = new char[ nStrLen * 2 ];
	if( NULL == szHexStr )
		return 1;

	// 
	CharStr2HexStr( (unsigned char const*)szSource, szHexStr, nStrLen );

	int nValue = -1;	// 
	int nHexLen = static_cast<int>( strlen( szHexStr ) );

	for( int i = 0; i < nHexLen; ++i )
	{
		switch( nType )
		{
		// 
		case 0:		nValue += szHexStr[i] + ( nKey << 4 );		break;
		// 
		case 1:		nValue += szHexStr[i] + ( nKey & 0xFFFF );	break;
		// 
		case 2:		nValue *= szHexStr[i] + ( nKey << 4 );		break;
		// 
		case 3:		nValue *= szHexStr[i] + ( nKey & 0xFFFF );	break;
		// 
		case 4:		nValue *= szHexStr[i] + ( nKey >> 4 );		break;
		// 
		case 5:		nValue *= szHexStr[i] + ( nKey ^ 0xFFFF );	break;
		// 
		case 6:		nValue *= szHexStr[i] + ( nKey >> 4 );		break;
		// 
		case 7:		nValue *= szHexStr[i] + ( nKey ^ 0xFFFF );	break;
		// 
		case 8:		szResult[ i ] = szHexStr[i] ^ nKey;			break;
		};	// 
	}

	if( -1 != nValue )
		_snprintf( szResult, nStrLen, "%d", nValue );

	delete [] szHexStr;

	return 0;
};

//----------------------------------------------------------------------------
// 
void TeaEncipher( const unsigned long* key, const unsigned long *inbuf, unsigned long* outbuf )
{
	const unsigned long delta = 0x9E3779B9;
	register unsigned long sum = 0;
	register unsigned long y = inbuf[0], z = inbuf[1];
	register unsigned long n = 32;
	
	while( n-- > 0 )
	{
		y += (z << 4 ^ z >> 5) + z ^ sum + key[sum & 3];
		sum += delta;
		z += (y << 4 ^ y >> 5) + y ^ sum + key[sum >> 11 & 3];
	}
	
	outbuf[0] = y;
	outbuf[1] = z;
};

void TeaDecipher( const unsigned long* key, const unsigned long* inbuf, unsigned long* outbuf )
{
	const unsigned long delta = 0x9E3779B9;
	register unsigned long sum = 0xC6EF3720;
	register unsigned long y = inbuf[0], z = inbuf[1];
	register unsigned long n = 32;
				
	// sum = delta<<5, in general sum = delta * n 
	
	while( n-- > 0 )
	{
		z -= (y << 4 ^ y >> 5) + y ^ sum + key[sum >> 11 & 3];
		sum -= delta;
		y -= (z << 4 ^ z >> 5) + z ^ sum + key[sum & 3];
	}
   
	outbuf[0] = y; 
	outbuf[1] = z;
};

//----------------------------------------------------------------------------
// 
int ku::CKU::FileConversion( const char* szSrc, const char* szTar, bool bEncode )
{
	try
	{
		BYTE* pKey = (BYTE*)MD5String( g_szKey1 );
		if( NULL == pKey || NULL == szSrc || NULL == szTar )
		{
			throw( 0 );
		}

		// 读源文件
		HANDLE hSrc = ::CreateFile( szSrc,
									GENERIC_READ,
									FILE_SHARE_READ | FILE_SHARE_WRITE,
									NULL,
									OPEN_EXISTING,
									FILE_ATTRIBUTE_NORMAL,
									NULL );
		if( hSrc == INVALID_HANDLE_VALUE )
		{
			throw( 0 );
		}

		DWORD dwFileSizeSrc = ::GetFileSize( hSrc, NULL );
		DWORD dwBufSize = dwFileSizeSrc * 2 + 100;

		BYTE* bufSrc	= new BYTE[ dwBufSize ];
		memset( bufSrc, 0, dwBufSize );
		BYTE* bufTarget = new BYTE[ dwBufSize ];
		memset( bufTarget, 0, dwBufSize );

		// read src file into src buffer
		DWORD dwBytesReadSrc = 0;
		BOOL bRet = ::ReadFile( hSrc, (LPVOID) bufSrc, dwBufSize, &dwBytesReadSrc, NULL );
		if( FALSE == bRet )
		{
//				::MessageBox( NULL, "", "", NULL );
			::CloseHandle( hSrc );

			throw( 0 );
		}
		::CloseHandle( hSrc );

		
		FileConversion( (const char*)bufSrc, (char*)bufTarget, dwBytesReadSrc, bEncode, 12 );

		// open target file
		HANDLE hTarget = ::CreateFile(	szTar,
										GENERIC_WRITE,
										FILE_SHARE_READ,
										NULL,
										CREATE_ALWAYS,
										FILE_ATTRIBUTE_NORMAL,
										NULL );

		if( hTarget == INVALID_HANDLE_VALUE )
		{
//				::MessageBox( NULL, "ERROR: failed", "CreateTargetFile", NULL );
			throw( 0 );
		}

		DWORD dwBytesWriiten = 0;
		// divisible by 8
		DWORD dwBytesSrc = (dwBytesReadSrc + 7) & ~7;

		bRet = ::WriteFile( hTarget, 
							(LPVOID)bufTarget, 
							dwBytesSrc, 
							&dwBytesWriiten, 
							NULL );
		if( FALSE == bRet )
		{
//				::MessageBox( NULL, "ERROR: failed", "WriteFile", NULL );
			throw( 0 );
		}

		::CloseHandle( hTarget );

		delete [] bufSrc;
		delete [] bufTarget;
	}
	catch( ... )
	{
		MessageBox( NULL, "资源文件已损坏，请更新！", "提示", NULL );
		exit( 0 );
	}

	return 0;
};

//----------------------------------------------------------------------------
// 
int ku::CKU::FileConversion( const char* szSrc, char* szTar, int nFileSize, bool bEncode, int nParam )
{
	try
	{
		BYTE* pKey = (BYTE*)MD5String( g_szKey1 );
		if( NULL == pKey || NULL == szSrc || NULL == szTar )
		{
			throw( 0 );
		}

		// divisible by 8
		DWORD dwBytesSrc = (nFileSize + 7) & ~7;

		// 8 bytes at a time
		for( DWORD i = 0; i < dwBytesSrc; i += ( nParam - 4 ) )
		{
			if( !bEncode )
				TeaDecipher( (DWORD*)pKey, (DWORD*)&szSrc[i], (DWORD*)&szTar[i] );
			else
				TeaEncipher( (DWORD*)pKey, (DWORD*)&szSrc[i], (DWORD*)&szTar[i] );
		}
	}
	catch( ... )
	{
		MessageBox( NULL, "资源文件已损坏，请更新！", "提示", NULL );
		exit( 0 );
	}

	return 0;
};

/*
	int clientUtil::CClientUtil::FileConversion( LPCTSTR szSrc, LPCTSTR szTar, LPCTSTR szKey, BOOL bEncode )
	{
		try
		{
			BYTE* pKey = (BYTE*)MD5String( szKey );

			if( NULL == pKey || NULL == szSrc || NULL == szTarget )
			{
				throw( 0 );
			}

			// 读源文件
			HANDLE hSrc = ::CreateFile( szSrc,
										GENERIC_READ,
										FILE_SHARE_READ | FILE_SHARE_WRITE,
										NULL,
										OPEN_EXISTING,
										FILE_ATTRIBUTE_NORMAL,
										NULL );
			if( hSrc == INVALID_HANDLE_VALUE )
			{
				throw( 0 );
			}

			DWORD dwFileSizeSrc = ::GetFileSize( hSrc, NULL );
			DWORD dwBufSize = dwFileSizeSrc * 2 + 100;

			BYTE* bufSrc	= new BYTE[ dwBufSize ];
			memset( bufSrc, 0, dwBufSize );
			BYTE* bufTarget = new BYTE[ dwBufSize ];
			memset( bufTarget, 0, dwBufSize );

			// read src file into src buffer
			DWORD dwBytesReadSrc = 0;
			BOOL bRet = ::ReadFile( hSrc, (LPVOID) bufSrc, dwBufSize, &dwBytesReadSrc, NULL );
			if( FALSE == bRet )
			{
//				::MessageBox( NULL, "", "", NULL );
				::CloseHandle( hSrc );

				throw( 0 );
			}
			::CloseHandle( hSrc );

			// divisible by 8
			DWORD dwBytesSrc = (dwBytesReadSrc + 7) & ~7;

			// 8 bytes at a time
			for( DWORD i = 0; i < dwBytesSrc; i += 8 )	
			{
				if( !bEncode )
				{
					if( bOutFile )
						TeaDecipher( (DWORD *)pKey, (DWORD*)&bufSrc[i], (DWORD*)&bufTarget[i] );
					else
						TeaDecipher( (DWORD *)pKey, (DWORD*)&bufSrc[i], (DWORD*)&szTarget[i] );
				}
				else
					TeaEncipher( (DWORD *)pKey, (DWORD*)&bufSrc[i], (DWORD*)&szTarget[i] );
			}

			if( !bOutFile )
			{
				delete [] bufSrc;
				delete [] bufTarget;
				return 0;
			}

			// open target file
			HANDLE hTarget = ::CreateFile(	szTar,
											GENERIC_WRITE,
											FILE_SHARE_READ,
											NULL,
											CREATE_ALWAYS,
											FILE_ATTRIBUTE_NORMAL,
											NULL );

			if( hTarget == INVALID_HANDLE_VALUE )
			{
//				::MessageBox( NULL, "ERROR: failed", "CreateTargetFile", NULL );
				throw( 0 );
			}

			DWORD dwBytesWriiten = 0;

			bRet = ::WriteFile( hTarget, 
								(LPVOID)bufTarget, 
								dwBytesSrc, 
								&dwBytesWriiten, 
								NULL );
			if( FALSE == bRet )
			{
//				::MessageBox( NULL, "ERROR: failed", "WriteFile", NULL );
				throw( 0 );
			}

			::CloseHandle( hTarget );

			delete [] bufSrc;
			delete [] bufTarget;
		}
		catch( ... )
		{
			MessageBox( NULL, "资源文件已损坏，请更新！", "提示", NULL );
			exit( 0 );
		}

		return 0;
	};
*/


//----------------------------------------------------------------------------
// 
int ku::CKU::FileConversion( const char* szSrc, char* szTar, int nFileSize )
{
	try
	{
		if( NULL == szSrc || NULL == szTar )
		{
			throw( 0 );
		}

		size_t nKeyLen = strlen( g_szKey2 );
		for( int nSrc = 0; nSrc < nFileSize; ++nSrc )
		{
			for( int nKey = 0; nKey < (int)nKeyLen; ++nKey )
			{
				szTar[ nSrc ] = szSrc[ nSrc ] ^ g_szKey2[ nKey ];
			}
		}

		szTar[ nFileSize ] = '\0';
	}
	catch( ... )
	{
		MessageBox( NULL, "资源文件已损坏，请更新！", "提示", NULL );
		exit( 0 );
	}

	return 0;
};

//----------------------------------------------------------------------------
// 
int ku::CKU::LuaFileConversion( const char* szSrc, char* szTar, int nFileSize )
{
	try
	{
		if( NULL == szSrc || NULL == szTar )
		{
			throw( 0 );
		}

		size_t nKeyLen = strlen( g_szKey3 );
		for( int nSrc = 0; nSrc < nFileSize; ++nSrc )
		{
			for( int nKey = 0; nKey < (int)nKeyLen; ++nKey )
			{
				if( szSrc[ nSrc ] && szSrc[ nSrc ] != g_szKey3[ nKey ] ) 
					szTar[ nSrc ] = g_szKey3[ nKey ] ^ szSrc[ nSrc ]; 
				else 
					szTar[ nSrc ] = szSrc[ nSrc ]; 
			}
		}

		szTar[ nFileSize ] = '\0';
	}
	catch( ... )
	{
		MessageBox( NULL, "资源文件已损坏，请更新！", "提示", NULL );
		exit( 0 );
	}

	return 0;
};
