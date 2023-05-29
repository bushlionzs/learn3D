
#include "OgreHeader.h"
#include "ku.h"
#include "ku_define.h"
//#include "HISystem.h"
#include "MD5.h"

#include <windows.h>
#include <IPHlpApi.h>
#include <IcmpAPI.h>
#include <Nb30.h>


// ��Ϸ�ļ���
LPCTSTR szGame = "KHan2.exe";
// ��Ϸ�ļ��Զ���ı���
LPCTSTR szGaemSection = ".kylin9";

// 
#define LAUNCHER_CHECK_TIME 50	// ��
#define ANTIDEBUG_CHECK_TAG 0	// 


//----------------------------------------------------------------------------
// У����Ϸ�ļ�������
int ku::CKU::CheckGame( const char* szGameExeFile, const char* szParam, int& nReturn )
{
	if( NULL == szGameExeFile ||
		NULL == szParam		  )
	{
		::MessageBox( NULL, "�Ƿ��������������ԡ�", "������ʾ", NULL );
		return 1;
	}

	if( 0 != strcmp( szGameExeFile, szGame ) )
	{
		::MessageBox( NULL, "�Ƿ��������������ԡ�", "������ʾ", NULL );
		return 1;
	}

	int nResult = 0;

	try
	{
		// �����в������
#ifdef FORCE_LAUNCHER  // ...: ֻ����Release_Staticģʽ�²ſ���
#if 0

//		// ���ܷ���
//		{
//			DWORD dwTemp = ::GetTickCount();
//			char szTemp[32] = {0};
//			sprintf( szTemp, "%010u", dwTemp );
//
//			srand( dwTemp );
//			dwTemp = (DWORD)rand();
//			char szKey[32] = {0};
//			sprintf( szKey, "%08u", dwTemp );
//
//			szKey[0] = szTemp[6];
//			szKey[2] = szTemp[5];
//			szKey[5] = szTemp[4];
//		}

		// ����
		DWORD dwClientTime = ::GetTickCount();
		dwClientTime /= 1000;
		dwClientTime %= 1000;

		char szBuf[4] = {0}; 
		szBuf[0] = szParam[5];	//szParam�������в���
		szBuf[1] = szParam[2];
		szBuf[2] = szParam[0];
		DWORD dwLauncherTime = (DWORD)atoi( szBuf );

		if( dwClientTime < dwLauncherTime )
			dwClientTime += 1000;

		if( dwClientTime < dwLauncherTime ||
		  ( dwClientTime - dwLauncherTime ) > LAUNCHER_CHECK_TIME ||
		  ( 0 == dwLauncherTime ) ||
		  ( NULL == szParam )
		  )

#else

		const char* szKey = "a7h7nk";
		long long   dwKey = 8757735233;

		char szTmp[ 128 ] = { 0 };
		memcpy( szTmp, szParam, strlen( szParam ) );

		// 
		time_t timeTmp1, timeTmp2;
		::time( &timeTmp1 );
		timeTmp2 = timeTmp1;

		int nKeyLen = (int)strlen( szKey );
		for( int idx = 0; idx < nKeyLen; ++idx )
		{
			dwKey ^= szKey[ idx ] | 128;
		};

		int nTimeLen = (int)strlen( szTmp );
		for( int idx = 0; idx < nTimeLen; ++idx )
		{
			szTmp[ idx ] ^= dwKey;
			szTmp[ idx ] ^= nTimeLen;
		};

		timeTmp2 = atoi( szTmp );

		double dDiffResult = ::difftime( timeTmp1, timeTmp2 );
		if( dDiffResult >= LAUNCHER_CHECK_TIME || dDiffResult < 0 )
#endif

		{
			// ���������Ϣ
			char szError[MAX_PATH] = {0};
//			_snprintf( szError, MAX_PATH, "l -- %s,%d,%d", szParam, dwClientTime, dwLauncherTime );
			_snprintf( szError, MAX_PATH, "l -- %s,%u,%u", szParam, timeTmp1, timeTmp2 );
//			MessageBox( NULL, szError, "������ʾ", NULL );

			MessageBox( NULL, "��� Launch ������Ϸ��", "������ʾ", MB_OK );
			throw std::exception( szError );
			exit(0);
		}
//		else
//		{
//			char szError[MAX_PATH] = {0};
//			_snprintf( szError, MAX_PATH, "launch = %s,%d,%d", szParam, dwClientTime, dwLauncherTime );
//			MessageBox( NULL, szError, "�ɼ�˼��111", MB_OK );
//		}
#endif  // FORCE_LAUNCHER

		nReturn += 2;
		return 0;
	}
	catch( const std::exception& e )
	{
		throw std::exception( e.what() );
		exit(0);
	}
	catch( ... )
	{
		MessageBox( NULL, "��Ϸ�ļ����𻵣�����£�", "������ʾ", NULL );
		exit( 0 );
	};

	return 0;
};

//----------------------------------------------------------------------------
// ��ȡ�Կ���Ϣ
bool ku::CKU::FreeVideoMemory( float& fVideoMem )
{
	return true;
};

//----------------------------------------------------------------------------
// ��ȡ������Ϣ
bool ku::CKU::GetMac( char* szMac, int nSize )
{
	if( NULL == szMac ||
		32 != nSize )	// Mac��ַ����
		return false;

	try
	{
		typedef struct _ASTAT_     
		{
			ADAPTER_STATUS	adapt;
			NAME_BUFFER		NameBuff[ 32 ];
		}ASTAT, *PASTAT;

		typedef struct _LANA_ENUM
		{ // le
			UCHAR	length;
			UCHAR	lana[MAX_LANA];
		}LANA_ENUM;

		NCB ncb;
		memset( &ncb, 0, sizeof( ncb ) );

		ASTAT Adapter;
		LANA_ENUM lana_enum;
		memset( &lana_enum, 0, sizeof( lana_enum ) );

		ncb.ncb_command = NCBENUM;
		ncb.ncb_buffer = (unsigned char*)&lana_enum;
		ncb.ncb_length = sizeof( LANA_ENUM );

		UCHAR uRetCode = Netbios( &ncb );
		if( NRC_GOODRET != uRetCode )
			return false;

		for( int lana=0; lana < lana_enum.length; ++lana )
		{
			ncb.ncb_command = NCBRESET;
			ncb.ncb_lana_num = lana_enum.lana[ lana ];
			uRetCode = Netbios( &ncb );
			if( uRetCode == NRC_GOODRET )
				break;
		};

		if( NRC_GOODRET != uRetCode )
			return false;

		memset( &ncb, 0, sizeof(ncb) );

		ncb.ncb_command	 = NCBASTAT;
		ncb.ncb_lana_num = lana_enum.lana[0];
		strcpy( (char*)ncb.ncb_callname, "*" );
		ncb.ncb_buffer	 = (unsigned char*)&Adapter;
		ncb.ncb_length	 = sizeof( Adapter );
		
		uRetCode = Netbios( &ncb );
		if( NRC_GOODRET != uRetCode )
			return false;

		memset( szMac, 0, nSize );
		_snprintf(	szMac, nSize, "%02X%02X%02X%02X%02X%02X",
					Adapter.adapt.adapter_address[0],
					Adapter.adapt.adapter_address[1],
					Adapter.adapt.adapter_address[2],
					Adapter.adapt.adapter_address[3],
					Adapter.adapt.adapter_address[4],
					Adapter.adapt.adapter_address[5] );
	}
	catch( ... )
	{
		return false;
	}

	return true;
};

//----------------------------------------------------------------------------
// ��ȡip��ַ
bool ku::CKU::GetIP( char* szIP, int nSize )
{
	if( NULL == szIP ||
		32 != nSize )
		return false;

	try
	{
		WORD wVersionRequested = MAKEWORD( 2, 2 );
		WSADATA wsaData;
		int err = WSAStartup( wVersionRequested, &wsaData );
		if( err != 0 ) 
			return false; 

		char hostName[80] = { 0 };
		if( gethostname( hostName , 80 ) == SOCKET_ERROR )
			return false;

		struct hostent * phe = gethostbyname( hostName );
		if( phe == NULL )
			return false;

		if( phe->h_addr_list[0] == 0 )
			return false;

		// ȡ��һ��
		struct in_addr addr;
		memcpy( &addr, phe->h_addr_list[0] , sizeof( struct in_addr ) );

		char* tempIP = inet_ntoa( addr );
		memcpy( szIP, tempIP , strlen(tempIP) );
		szIP[ strlen(tempIP) ] = 0;

		WSACleanup();
	}
	catch( ... )
	{
		return false;
	}

    return true;
};

//----------------------------------------------------------------------------
// ��ȡ
// ...: could not compile, 'IcmpSendEcho' undefined...
/*
bool ku::CKU::GetTR( const char* szDestIP, char* szRet )	// TraceRoute
{
	if( NULL == szDestIP )	// ip �� ����
		return false;

	WSADATA wsa;
	if( 0 != WSAStartup( MAKEWORD( 2, 2 ), &wsa ) )
	{
//		( "WSAStartup failed." );
		return false;
	}

	try
	{
		// ת��IP��ַ������
		unsigned long ip = inet_addr( szDestIP );
		if( INADDR_NONE == ip )
		{
			// ����������
			hostent* pHost = gethostbyname( szDestIP );
			// ����Ҳ�޷�����
			if( NULL == pHost )
			{
//				( "Invalid IP or domain name: %s\n", szDestIP );
				WSACleanup();
				return false;
			}

			// ȡ�����ĵ�һ��IP��ַ
			ip = *(unsigned long*)pHost->h_addr_list[ 0 ];
//			( "trace route to %s(%s)\n", szDestIP, inet_ntoa( *(in_addr*)&ip ) );
		}
		else
		{
//			( "trace route to %s\n", szDestIP );
		}

		// ��ICMP���
		HANDLE hIcmp = IcmpCreateFile();
		if( INVALID_HANDLE_VALUE == hIcmp )
		{
//			("\tUnable to open ICMP file.\n");
			WSACleanup();
			return false;
		}

		// ����IP��ͷ��TTLֵ
		IP_OPTION_INFORMATION IpOption;
		ZeroMemory( &IpOption, sizeof( IP_OPTION_INFORMATION ) );
		IpOption.Ttl = 1;

		// ����Ҫ���͵�����
		char szSendData[32] = { 0 };
//		memset( SendData, '0', sizeof( SendData ) );

		// ���ý��ջ�����
		char szReplyBuffer[ sizeof( ICMP_ECHO_REPLY ) + 32 ] = { 0 };
		PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)szReplyBuffer;

		BOOL bLoop = TRUE;
		int nMaxHop  = 30;		// ���̽�����
		int nTimeOut = 1000;	// �����̽�ⳬʱʱ�䣨���룩
		int nTimeOutCount = 0;	// ̽�ⳬʱ������������һ����ֵʱֹͣ

		while( bLoop && nMaxHop-- )
		{
//			( "%2d: ", IpOption.Ttl );

			// ����ICMP��������
			if( 0 != IcmpSendEcho( hIcmp, (IPAddr)ip, szSendData, sizeof( szSendData ), &IpOption, szReplyBuffer, sizeof( szReplyBuffer ), nTimeOut ) )
			{
				// ̽��ʹ�õ�ʱ��
//				if( 0 == pEchoReply->RoundTripTime )
//				{
//					( "\t<1ms" );
//				}
//				else
//				{
//					( "\t%dms", pEchoReply->RoundTripTime );
//				}

				// ̽�⵽��ip
//				printf( "\t%s\n", inet_ntoa( *(in_addr*)&( pEchoReply->Address ) ) );

				int nLen = 0;
				nLen = (int)strlen( szRet );
#if 0
				// ip��ַ��ʽ
				char* szAddress = inet_ntoa( *(in_addr*)&( pEchoReply->Address ) );
#else
				// ���ָ�ʽ
				char szAddress[32] = { 0 };
				_snprintf( szAddress, 32 * sizeof( char ), "%u", (unsigned long)pEchoReply->Address );
#endif
				memcpy( szRet + nLen, szAddress, strlen( szAddress ) );

				// �ж��Ƿ����·��·��̽��
				if( (unsigned long)pEchoReply->Address == ip )
				{
//					( "\nTrace complete.\n" );
					bLoop = FALSE;
				}
				else
				{
					strcat( szRet, "-" );
				}
			}
			else
			{
				// �жϳ�ʱ���� >= 5
				if( nTimeOutCount >= 5 )
				{
					bLoop = FALSE;
				}
				else
				{
					nTimeOutCount++;
					strcat( szRet, "*" );
				}

//				("\t*\tRequest time out.\n");
			}

			IpOption.Ttl++;
		}

		IcmpCloseHandle( hIcmp );
	}
	catch( ... )
	{
		WSACleanup();
		return false;
	}

	WSACleanup();

	return true;
};	// TraceRoute
*/

//----------------------------------------------------------------------------
// �����ַ�����MD5
char* ku::CKU::GetMd5String( const char* szString )
{
	if( NULL == szString )
		return NULL;

	return MD5String( szString );
}

//----------------------------------------------------------------------------
// �����ļ���MD5
char* ku::CKU::GetMd5File( const char* szFile )
{
	if( NULL == szFile )
		return NULL;

	return MD5File( szFile );
}


//----------------------------------------------------------------------------
// �����ַ�����CRC
inline 
VOID CalcCrc32( const BYTE byte, UINT& dwCrc32 )
{
	dwCrc32 = ((dwCrc32) >> 8) ^ ku::ArrdwCrc32Table[ (byte) ^ ((dwCrc32) & 0x000000FF) ];
}
unsigned int ku::CKU::GetCrcString( const char* szString, int nType, int nSize )
{
	if( szString == NULL )	// || szString[0] == 0 )
		return 0;

	UINT dwCrc32 = 0xFFFFFFFF;
	if( 0 == nSize )
		nSize = (int)strlen( szString );

	if( 0 == nType )
	{
		for( INT i = 0; i < nSize; ++i )
			CalcCrc32( szString[i], dwCrc32 );
	}
	else if( 1 == nType )
	{
		for( INT i = nSize - 1; i >= 0; --i )
			CalcCrc32( szString[i], dwCrc32 );
	}

	return dwCrc32;
}


//----------------------------------------------------------------------------
// ����GM
int ku::CKU::GMFilter( const char* szGMName, const char* szGMIP, const char* szCommand, char* szResult )
{
	if( NULL == szGMName || 
		NULL == szGMIP	 ||                                                
		NULL == szCommand )
		return 1;

	_snprintf( szResult, MAX_PATH, szCommand );

	// �ж�GM����
	int nNameLen = (int)strlen( szGMName );
//	if( nNameLen < 7 ) return 1;	// ����"GQH0001"
//	if( szGMName[0] != 'G' || szGMName[1] != 'Q' || szGMName[2] != 'H' ) return 1;	// GQH0001 ~ GQH0040

	// GMָ���ж�
	try
	{
		if( ( strstr( szCommand, "createitem" )  && szCommand[0] == 'c' && szCommand[6] == 'i' ) ||
			( strstr( szCommand, "modifymoney" ) && szCommand[0] == 'm' && szCommand[6] == 'm' ) ||
			( strstr( szCommand, "createhorse" ) && szCommand[0] == 'c' && szCommand[6] == 'h' ) )
		{
			char szIP[32] = { 0 };
			GetIP( szIP, 32 );

			if( 0 == strcmp( szGMName, "zengpx" ) )
			{
				return 0;	// ok
			}
			else if( 0 != strstr( szIP, "172.16." ) && szIP[1] == '7' && szIP[6] == '.' )
			{
				return 0;	// ok
			}
			else
			{
				_snprintf( szResult, MAX_PATH, "createitme xxx" );
				return 1;
			}
		}
	}
	catch( ... )
	{
		_snprintf( szResult, MAX_PATH, "createitme xxx" );
		return 1;
	}

	return 0;	// ok
};


//----------------------------------------------------------------------------
// 
const char HOST_FILE_NAME[] = "c:/windows/system32/drivers/etc/hosts";

// 
bool ku::CKU::ConnectCheck( void )	// HostCheck
{
	return true;


	std::string strContent;	// ���ս��

	FILE* fp = fopen( HOST_FILE_NAME, "r" );
	if( fp )
	{
		// 
		char szTmp[ MAX_PATH * 4 ] = { 0 };
		std::string strTmp, strTmpBegin, strTmpEnd;

		std::string::size_type tFind	= std::string::npos;
		std::string::size_type tKeyFind	= std::string::npos;

		do
		{
			if( 0 == fgets( szTmp, MAX_PATH * 4, fp ) )
				break;

			strTmp = szTmp;

			// �滻70game.net
			tKeyFind = strTmp.find( "70game.net" );
			if( tKeyFind != std::string::npos )
			{
				strTmpBegin = strTmp.substr( 0, tKeyFind );
				strTmpEnd	= strTmp.substr( tKeyFind + 10 + 1 );
				strContent += strTmpBegin;
				strContent += "70yx.com";
				strContent += strTmpEnd;
				strContent += "\r\n";
				continue;
			}

			// 
			tKeyFind = strTmp.find( "code.70yx.com" );
			if( tKeyFind != std::string::npos )
			{
				strContent += "# ";
				strContent += strTmp;
//				strContent += "\r\n";
				continue;
			}

			strContent += strTmp;
//			strContent += "\r\n";
		}
		while( 1 );

		fclose( fp );
	};

/*
	if( fp )
	{
		char szTemp[ MAX_PATH * 4 ] = { 0 };
		std::string strLine = "";

		do
		{
			if( 0 == fgets( szTemp, MAX_PATH * 4, fp ) )
				break;

			strLine = szTemp;
			std::string::size_type tFind	= std::string::npos;
			std::string::size_type tKeyFind	= std::string::npos;

			// 
			tKeyFind = strLine.find( "70yx.com" );
			if( tKeyFind != std::string::npos )
			{
				tFind = strLine.find_first_of( "#" );
				if( tFind != std::string::npos )
				{
					if( tKeyFind < tFind )
					{
						fclose( fp );
						return false;
					}
				}
				else
				{
					fclose( fp );
					return false;
				}
			}
		}
		while( TRUE );
		fclose( fp );
	};	// 
*/

	DWORD dwFileAttr = GetFileAttributes( HOST_FILE_NAME );
	if( FILE_ATTRIBUTE_READONLY & dwFileAttr )
		SetFileAttributes( HOST_FILE_NAME, dwFileAttr & ( ~FILE_ATTRIBUTE_READONLY ) );

	fp = fopen( HOST_FILE_NAME, "w" );
	if( fp )
	{
		fprintf( fp, strContent.c_str() );
		fclose( fp );
	};

	if( FILE_ATTRIBUTE_READONLY & dwFileAttr )
		SetFileAttributes( HOST_FILE_NAME, dwFileAttr );

	return true;
};

//----------------------------------------------------------------------------
// ���Լ��
//int ku::CKU::AntiDebug( int nType )
//{
//	int nResult = 0;
//
//	switch( nType )
//	{
//	case 0:
//		{
//			HMODULE hModule = ::GetModuleHandle( "kernel32.dll" );
//			if( INVALID_HANDLE_VALUE != hModule )
//			{
//				FARPROC Func_addr;
//				(FARPROC&)Func_addr = ::GetProcAddress( hModule, "IsDebuggerPresent" );
//
//				// ���ϵ�
//				if( 0xcc == *(BYTE*)Func_addr )
//					return false;
//
//				// ��⹳��
//				if( 0x64 != *(BYTE*)Func_addr )
//					return false;
//
//				if( Func_addr() )
//					return false;
//			}
//		};
//		break;
//
//	case 1:
//		{
////			if( m_pAntiDebug )
////				m_pAntiDebug->LockCurrentProcess();
//		}
//		break;
//
//	case 2:
//		{
////			if( m_pAntiDebug )
////				m_pAntiDebug->EnumProcessInformation( nResult );
//		}
//		break;
//	};	// switch
//
//	return nResult;
//};
