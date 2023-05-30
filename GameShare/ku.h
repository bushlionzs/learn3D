
#ifndef _KYLIN_UTILS_H_
#define _KYLIN_UTILS_H_


namespace ku
{

	// 操作类型
	enum eHttpVerb	{ HVT_POST = 0, HVT_GET };

	// 
	class CKU
	{
	public:

		/**
		*	校验游戏文件完整性
		*/
		// 参数：
		int		CheckGame( const char*, const char*, int& );


		/**
		*	获取用户系统信息
		*/

		// 显卡信息（显存）
		bool	FreeVideoMemory( float& );

		// MAC地址
		// 参数：返回的Mac地址、传入的数据定义尺寸
		bool	GetMac( char*, int/* 32 */ );

		// IP地址
		// 参数：
		bool	GetIP( char*, int/* 32 */ );

		// 
		// 参数：
		bool	GetTR( const char*, char* );

	public:

		/**
		*	MD5
		*/

		// 产生字符串的MD5
		// 参数：
		char*	GetMd5String( const char* );
		char*	GetMd5File  ( const char* );

		/**
		*	CRC
		*/

		// 产生字符串的CRC
		// 参数：传入的原串、操作类型（0--正向，1--反向）、原串尺寸（传入0会计算原串的实际长度）
		unsigned int GetCrcString( const char*, int nType = 0, int nSize = 0 );

	public:

		/**
		*	加密过程
		*/
		int		GetEncryptCode( int, int, const char*, char* );	// 登陆
		int		GetEncryptCode( int, int, int, int, char* );	// 移动
		int		GetEncryptCode( int, int, int, char*, int );	// 锁定目标
		int		GetEncryptCode( int, int, int, char* );			// 心跳

		int		EncryptCode( int, int, const char*, char* );

		// 资源加密解密
		int		FileConversion( const char*, const char*, bool );
		int		FileConversion( const char*, char*, int, bool, int );
		int		FileConversion( const char*, char*, int );
		int		LuaFileConversion( const char*, char*, int );

		// 16进制字符串转换
		void	CharStr2HexStr( unsigned char const*, char*, int );
		void	HexStr2CharStr( char const*, unsigned char*, int );

		/**
		*	GM过滤
		*/
		// gm帐号、ip、命令、结果
		int		GMFilter( const char*, const char*, const char*, char* );

		// 连接检测
		bool	ConnectCheck( void );

	};	// class

};	// namespace

#endif	// _KYLIN_UTILS_H_
