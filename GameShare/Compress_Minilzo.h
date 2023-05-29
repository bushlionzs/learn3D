#include "Basics.h"
#include "minilzo.h"
#include "MiniLock.h"

#define MAX_THREAD_SIZE		128
#define WRKMEM_SIZE			((LZO1X_1_MEM_COMPRESS+sizeof(lzo_align_t)-1) / sizeof(lzo_align_t))

class Compress_Minilzo
{
	struct WRKMEM
	{
		void*	pMem;
		TID		threadID;
	};
public:
	Compress_Minilzo();
	~Compress_Minilzo();

public:
	static Compress_Minilzo& GetInstance()
	{
		static Compress_Minilzo instance;
		return instance;
	}

	BOOL	Init();
	void	Close();
	void*	AllocWrkMem(TID threadID);
	BOOL	Compress( const uchar* pIn, lzo_uint uInsize, uchar* pOut, lzo_uint& uOutSize, void* wrkmem );
	int32	DeCompress( const uchar* pIn, uint32 uInsize, uchar* pOut, uint32& uOutSize );

	void	AddUnCmDataSize(uint64 uSize);
	void	AddCmDataSize(uint64 uSize);
	uint64	GetUnCmDataSize();
	uint64	GetCmDataSize();

	BOOL	IsEnableLog();
	void	EnableLog(BOOL bEnable);

private:
	BOOL	m_bEnableLog;

	WRKMEM	m_wrkmem[MAX_THREAD_SIZE];
	uint32	m_uWrkmemSize;
	
	uint64	m_uUnCmDataSize;
	uint64	m_uCmDataSize;
	
	MiniLock m_Lock;

};


class Compress_Assistant
{
public:
	Compress_Assistant();
	~Compress_Assistant();

	void	SetWrkMem(void* pMem);
	void*	GetWrkMem();
	BOOL	IsEanble();
	void	Enable(BOOL bEnable,TID threadID=0);
	BOOL	IsEnableLog();
	void	EnableLog(BOOL bEnable);

	void	IncCmFrame();
	uint32	GetCmFrame();
	void	IncCmSuccFrame();
	uint32	GetCmSuccFrame();

private:
	void*	m_wrkmem;
	BOOL	m_bEnable;
	BOOL	m_bEnableLog;
	uint32	m_uCmFrame;
	uint32	m_uCmSuccFrame;
};
