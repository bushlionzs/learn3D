
#ifndef _KYLIN_UTILS_H_
#define _KYLIN_UTILS_H_


namespace ku
{

	// ��������
	enum eHttpVerb	{ HVT_POST = 0, HVT_GET };

	// 
	class CKU
	{
	public:

		/**
		*	У����Ϸ�ļ�������
		*/
		// ������
		int		CheckGame( const char*, const char*, int& );


		/**
		*	��ȡ�û�ϵͳ��Ϣ
		*/

		// �Կ���Ϣ���Դ棩
		bool	FreeVideoMemory( float& );

		// MAC��ַ
		// ���������ص�Mac��ַ����������ݶ���ߴ�
		bool	GetMac( char*, int/* 32 */ );

		// IP��ַ
		// ������
		bool	GetIP( char*, int/* 32 */ );

		// 
		// ������
		bool	GetTR( const char*, char* );

	public:

		/**
		*	MD5
		*/

		// �����ַ�����MD5
		// ������
		char*	GetMd5String( const char* );
		char*	GetMd5File  ( const char* );

		/**
		*	CRC
		*/

		// �����ַ�����CRC
		// �����������ԭ�����������ͣ�0--����1--���򣩡�ԭ���ߴ磨����0�����ԭ����ʵ�ʳ��ȣ�
		unsigned int GetCrcString( const char*, int nType = 0, int nSize = 0 );

	public:

		/**
		*	���ܹ���
		*/
		int		GetEncryptCode( int, int, const char*, char* );	// ��½
		int		GetEncryptCode( int, int, int, int, char* );	// �ƶ�
		int		GetEncryptCode( int, int, int, char*, int );	// ����Ŀ��
		int		GetEncryptCode( int, int, int, char* );			// ����

		int		EncryptCode( int, int, const char*, char* );

		// ��Դ���ܽ���
		int		FileConversion( const char*, const char*, bool );
		int		FileConversion( const char*, char*, int, bool, int );
		int		FileConversion( const char*, char*, int );
		int		LuaFileConversion( const char*, char*, int );

		// 16�����ַ���ת��
		void	CharStr2HexStr( unsigned char const*, char*, int );
		void	HexStr2CharStr( char const*, unsigned char*, int );

		/**
		*	GM����
		*/
		// gm�ʺš�ip��������
		int		GMFilter( const char*, const char*, const char*, char* );

		// ���Ӽ��
		bool	ConnectCheck( void );

	};	// class

};	// namespace

#endif	// _KYLIN_UTILS_H_
