/*$T Common/Util.cpp GC 1.140 10/10/07 10:06:30 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "TypeDefine.h"
#include "Util.h"

#ifdef __LINUX__
#include <execinfo.h>
#include <signal.h>
#include <exception>
#include <setjmp.h>
#include "Atomic.h"

#endif
ThreadIndent	g_ThreadIndent;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ThreadIndent::ThreadIndent()
{
	for(int32 i = 0; i < THREAD_CAPS; i++)
	{
		m_ThreadID[i] = 0;
		m_ThreadIndent[i] = 0;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ThreadIndent::~ThreadIndent()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ThreadIndent::AddThread(TID tid)
{
	{
		/*~~~~~~~~~~~~~~~~~~*/
		static FastLock tlock;
		/*~~~~~~~~~~~~~~~~~~*/

		lock_guard<FastLock> autolock(tlock);

		for(int32 i = 0; i < THREAD_CAPS; i++)
		{
			if(m_ThreadID[i] == tid)
			{
				break;
			}

			if(m_ThreadID[i] == 0)
			{
				m_ThreadID[i] = tid;
				break;
			}
		}
	}

	while(FALSE);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ThreadIndent::SetThreadIndent(TID tid, int32 nValue)
{
	for(int32 i = 0; i < THREAD_CAPS; i++)
	{
		if(m_ThreadID[i] == 0)
		{
			break;
		}

		if(m_ThreadID[i] == tid)
		{
			m_ThreadIndent[i] = nValue;
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ThreadIndent::GetThreadIndent(TID tid)
{
	for(int32 i = 0; i < THREAD_CAPS; i++)
	{
		if(m_ThreadID[i] == 0)
		{
			return 0;
		}

		if(m_ThreadID[i] == tid)
		{
			return m_ThreadIndent[i];
		}
	}

	return 0;
}

int32		g_CMDArgv;

GLTime	g_GLTime = WT_IND_1;

/*
 =======================================================================================================================
 =======================================================================================================================
 */

void shm_lock(atword *flag, char type)
{
	if(g_CMDArgv == CMD_MODE_RECOVER) return;

	/*~~~~~~~~~~~~~~*/
	int32	count = 0;
	/*~~~~~~~~~~~~~~*/

#ifdef __LINUX__
	while(!atomic_inc_and_test(reinterpret_cast < atomic_t * > (flag)))
	{
		int32 count2 = 0;
		count++;
		count2++;
		atomic_dec(reinterpret_cast < atomic_t * > (flag));
		SafeSleep(0);
		if(count > 1000)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			char	message[256] = { 0 };
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			sprintf(message, "sm_lock error flag=%d,count=%d", (*flag), count2);
			QLogSystem::SLOW_LOG("./Log/smError.log", message);
			count = 0;
		}
	}

#else
	while(InterlockedCompareExchange (const_cast<LPLONG>(flag), 0, SM_FREE) != SM_FREE)
	{
		count++;
		SafeSleep(0);
		if(count > 10)
		{
			printf("lock fails.....\r\n");
			count = 0;
		}
	}
#endif
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void shm_unlock(atword *flag, char type)
{
	if(g_CMDArgv == CMD_MODE_RECOVER) return;

	/*~~~~~~~~~~~~~~*/
	int32	count = 0;
	/*~~~~~~~~~~~~~~*/

#ifdef __LINUX__
	if((int32) reinterpret_cast < int32 * > (flag) != SM_FREE) atomic_dec(reinterpret_cast < atomic_t * > (flag));
#else
	while(InterlockedCompareExchange (const_cast<LPLONG>(flag), SM_FREE, 0) != 0)
	{
		printf("unlock fails.....\r\n");
		SafeSleep(0);
		count++;
		if(count > 100)
		{
			InterlockedExchange (const_cast<LPLONG>(flag), SM_FREE);
			throw;
		}
	}
#endif
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SafeSleep(uint32 millionseconds)
{
	if(millionseconds > (uint32) 30000) KCheck(FALSE);
#if defined(__WINDOWS__)
	Sleep(millionseconds);

	/*~~~~~~~~~~~~~~~*/
#elif defined(__LINUX__)
	struct timeval	to;
	/*~~~~~~~~~~~~~~~*/

	to.tv_sec = 0;
	to.tv_usec = millionseconds * 1000;
	select(0, NULL, NULL, NULL, &to);
#endif
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
TID KGetCurrentTID()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	TID	tRet = GetOrigineThreadID();
	int32	nValue = g_ThreadIndent.GetThreadIndent(tRet);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	tRet += nValue;

	return tRet;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
TID GetOrigineThreadID()
{
#if defined(__WINDOWS__)
	return GetCurrentThreadId() * 1000;
#elif defined(__LINUX__)
	return pthread_self();
#endif
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 MyGetCurrentPID()
{
	/*~~~~~~~~*/
	uint32	pid;
	/*~~~~~~~~*/

#if defined(__WINDOWS__)
	pid = GetCurrentProcessId();
#elif defined(__LINUX__)
	pid = getpid();
#endif
	return pid;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
float KLSqrt(const GLPos *pCur, const GLPos *pTar)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pCur);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pTar);
	return (float) sqrt
		(
			((float64) pCur->m_fX - (float64) pTar->m_fX) * ((float64) pCur->m_fX - (float64) pTar->m_fX) +
				((float64) pCur->m_fZ - (float64) pTar->m_fZ) *
					((float64) pCur->m_fZ - (float64) pTar->m_fZ)
		);
	__UNGUARD__ return 0.0f;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
float KLLengthSq(const GLPos *pCur, const GLPos *pTar)
{
	return (float)
		(
			((float64) pCur->m_fX - (float64) pTar->m_fX) * ((float64) pCur->m_fX - (float64) pTar->m_fX) +
				((float64) pCur->m_fZ - (float64) pTar->m_fZ) *
					((float64) pCur->m_fZ - (float64) pTar->m_fZ)
		);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
float KLAngle(const GLPos *pCur, const GLPos *pTar)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float64 Sqrt = (float64) sqrt
		(
			(pCur->m_fX - pTar->m_fX) * (pCur->m_fX - pTar->m_fX) + (pCur->m_fZ - pTar->m_fZ) *
				(pCur->m_fZ - pTar->m_fZ)
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(Sqrt <= 0.0f) return 0.0f;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float64 fACos = (pTar->m_fZ - pCur->m_fZ) / Sqrt;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fACos > 1.0) fACos = 0.0;
	if(fACos < -1.0) fACos = __PI;

	fACos = ::acos(fACos);

	if(pTar->m_fX >= pCur->m_fX)
		return (float) fACos;
	else
		return (float) (2 * __PI - fACos);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL KLPosEqual(const GLPos *pA, const GLPos *pB)
{
#define ZERO_VALUE1	0.001
	if(pA->m_fX > pB->m_fX)
	{
		if(pA->m_fX - pB->m_fX > ZERO_VALUE1) return FALSE;
	}
	else
	{
		if(pB->m_fX - pA->m_fX > ZERO_VALUE1) return FALSE;
	}

	if(pA->m_fZ > pB->m_fZ)
	{
		if(pA->m_fZ - pB->m_fZ > ZERO_VALUE1) return FALSE;
	}
	else
	{
		if(pB->m_fZ - pA->m_fZ > ZERO_VALUE1) return FALSE;
	}

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KLRandomPos(GLPos *pPos, const GLPos *pDir, float fRadioMax, float fRadioMin)
{
	/*~~~~~~~~~~~~~~~~~~~~~*/
#define COS_ANGLE_MIN	0.7071f
#define COS_ANGLE_MAX	1.0f

#define ANGLE_MIN	0
#define ANGLE_MAX	__PI / 4
	float	fR1 = fRadioMin;
	float	fR2 = fRadioMax;
	float	fAx = pPos->m_fX;
	float	fAz = pPos->m_fZ;
	float	fBx = pDir->m_fX;
	float	fBz = pDir->m_fZ;
	float	fPx, fPz;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	if((fR1 < 0) || (fR2 < 0))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~*/
	float	fVec1X = 0;
	float	fVec1Y = 0;
	float	fRandThi = 0;
	float	fRandLength = 0;
	int32	iR1 = 0;
	int32	iR2 = 0;
	/*~~~~~~~~~~~~~~~~~~~~*/

	iR1 = (int32) (fR1 * 100);
	iR2 = (int32) (fR2 * 100);
	if(iR1 > iR2)
	{
		/*~~~~~~~~~~~~~~~~*/
		int32	iTmep = iR1;
		/*~~~~~~~~~~~~~~~~*/

		iR1 = iR2;
		iR2 = iTmep;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iLenDeta = iR2 - iR1;
	int32	iRandLength = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 == iR1)
	{
		iRandLength = rand() % (iR2 + 1);
	}
	else
	{
		iRandLength = rand() % iR1 + iLenDeta;
	}

	fRandLength = (float) (iRandLength * 1.0) / 100;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iThiMin = (int32) (ANGLE_MIN * 100);
	int32	iThiMax = (int32) (ANGLE_MAX * 100);
	int32	iThiDeta = iThiMax - iThiMin;
	int32	iRandThi = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 == iThiMin)
	{
		iRandThi = rand() % (iThiMax + 1);
	}
	else
	{
		iRandThi = rand() % iThiMin + iThiDeta;
	}

	fRandThi = (float) (iRandThi * 1.0) / 100;

	/*~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDir = rand() % 2;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 == iDir)
	{
		fRandThi = -fRandThi;
	}

	fVec1X = fBx - fAx;
	fVec1Y = fBz - fAz;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fVec1Len = ::sqrtf(fVec1X * fVec1X + fVec1Y * fVec1Y);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fabs(float(fVec1Len)) < 0.00001f)
	{
		fPx = fAx;
		fPz = fAz;
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fThi = ::asin(float(fVec1X / fVec1Len));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	fThi += fRandThi;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	x = ::cos(fThi) * fRandLength;
	float	y = ::sin(fThi) * fRandLength;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	fPx = x + fAx;
	fPz = y + fAz;

	pPos->m_fX = fPx;
	pPos->m_fZ = fPz;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const char *KLSocketError()
{
	return "";
}

uint32	__crc32[256] =
{
	0x00000000,
	0x77073096,
	0xEE0E612C,
	0x990951BA,
	0x076DC419,
	0x706AF48F,
	0xE963A535,
	0x9E6495A3,
	0x0EDB8832,
	0x79DCB8A4,
	0xE0D5E91E,
	0x97D2D988,
	0x09B64C2B,
	0x7EB17CBD,
	0xE7B82D07,
	0x90BF1D91,
	0x1DB71064,
	0x6AB020F2,
	0xF3B97148,
	0x84BE41DE,
	0x1ADAD47D,
	0x6DDDE4EB,
	0xF4D4B551,
	0x83D385C7,
	0x136C9856,
	0x646BA8C0,
	0xFD62F97A,
	0x8A65C9EC,
	0x14015C4F,
	0x63066CD9,
	0xFA0F3D63,
	0x8D080DF5,
	0x3B6E20C8,
	0x4C69105E,
	0xD56041E4,
	0xA2677172,
	0x3C03E4D1,
	0x4B04D447,
	0xD20D85FD,
	0xA50AB56B,
	0x35B5A8FA,
	0x42B2986C,
	0xDBBBC9D6,
	0xACBCF940,
	0x32D86CE3,
	0x45DF5C75,
	0xDCD60DCF,
	0xABD13D59,
	0x26D930AC,
	0x51DE003A,
	0xC8D75180,
	0xBFD06116,
	0x21B4F4B5,
	0x56B3C423,
	0xCFBA9599,
	0xB8BDA50F,
	0x2802B89E,
	0x5F058808,
	0xC60CD9B2,
	0xB10BE924,
	0x2F6F7C87,
	0x58684C11,
	0xC1611DAB,
	0xB6662D3D,
	0x76DC4190,
	0x01DB7106,
	0x98D220BC,
	0xEFD5102A,
	0x71B18589,
	0x06B6B51F,
	0x9FBFE4A5,
	0xE8B8D433,
	0x7807C9A2,
	0x0F00F934,
	0x9609A88E,
	0xE10E9818,
	0x7F6A0DBB,
	0x086D3D2D,
	0x91646C97,
	0xE6635C01,
	0x6B6B51F4,
	0x1C6C6162,
	0x856530D8,
	0xF262004E,
	0x6C0695ED,
	0x1B01A57B,
	0x8208F4C1,
	0xF50FC457,
	0x65B0D9C6,
	0x12B7E950,
	0x8BBEB8EA,
	0xFCB9887C,
	0x62DD1DDF,
	0x15DA2D49,
	0x8CD37CF3,
	0xFBD44C65,
	0x4DB26158,
	0x3AB551CE,
	0xA3BC0074,
	0xD4BB30E2,
	0x4ADFA541,
	0x3DD895D7,
	0xA4D1C46D,
	0xD3D6F4FB,
	0x4369E96A,
	0x346ED9FC,
	0xAD678846,
	0xDA60B8D0,
	0x44042D73,
	0x33031DE5,
	0xAA0A4C5F,
	0xDD0D7CC9,
	0x5005713C,
	0x270241AA,
	0xBE0B1010,
	0xC90C2086,
	0x5768B525,
	0x206F85B3,
	0xB966D409,
	0xCE61E49F,
	0x5EDEF90E,
	0x29D9C998,
	0xB0D09822,
	0xC7D7A8B4,
	0x59B33D17,
	0x2EB40D81,
	0xB7BD5C3B,
	0xC0BA6CAD,
	0xEDB88320,
	0x9ABFB3B6,
	0x03B6E20C,
	0x74B1D29A,
	0xEAD54739,
	0x9DD277AF,
	0x04DB2615,
	0x73DC1683,
	0xE3630B12,
	0x94643B84,
	0x0D6D6A3E,
	0x7A6A5AA8,
	0xE40ECF0B,
	0x9309FF9D,
	0x0A00AE27,
	0x7D079EB1,
	0xF00F9344,
	0x8708A3D2,
	0x1E01F268,
	0x6906C2FE,
	0xF762575D,
	0x806567CB,
	0x196C3671,
	0x6E6B06E7,
	0xFED41B76,
	0x89D32BE0,
	0x10DA7A5A,
	0x67DD4ACC,
	0xF9B9DF6F,
	0x8EBEEFF9,
	0x17B7BE43,
	0x60B08ED5,
	0xD6D6A3E8,
	0xA1D1937E,
	0x38D8C2C4,
	0x4FDFF252,
	0xD1BB67F1,
	0xA6BC5767,
	0x3FB506DD,
	0x48B2364B,
	0xD80D2BDA,
	0xAF0A1B4C,
	0x36034AF6,
	0x41047A60,
	0xDF60EFC3,
	0xA867DF55,
	0x316E8EEF,
	0x4669BE79,
	0xCB61B38C,
	0xBC66831A,
	0x256FD2A0,
	0x5268E236,
	0xCC0C7795,
	0xBB0B4703,
	0x220216B9,
	0x5505262F,
	0xC5BA3BBE,
	0xB2BD0B28,
	0x2BB45A92,
	0x5CB36A04,
	0xC2D7FFA7,
	0xB5D0CF31,
	0x2CD99E8B,
	0x5BDEAE1D,
	0x9B64C2B0,
	0xEC63F226,
	0x756AA39C,
	0x026D930A,
	0x9C0906A9,
	0xEB0E363F,
	0x72076785,
	0x05005713,
	0x95BF4A82,
	0xE2B87A14,
	0x7BB12BAE,
	0x0CB61B38,
	0x92D28E9B,
	0xE5D5BE0D,
	0x7CDCEFB7,
	0x0BDBDF21,
	0x86D3D2D4,
	0xF1D4E242,
	0x68DDB3F8,
	0x1FDA836E,
	0x81BE16CD,
	0xF6B9265B,
	0x6FB077E1,
	0x18B74777,
	0x88085AE6,
	0xFF0F6A70,
	0x66063BCA,
	0x11010B5C,
	0x8F659EFF,
	0xF862AE69,
	0x616BFFD3,
	0x166CCF45,
	0xA00AE278,
	0xD70DD2EE,
	0x4E048354,
	0x3903B3C2,
	0xA7672661,
	0xD06016F7,
	0x4969474D,
	0x3E6E77DB,
	0xAED16A4A,
	0xD9D65ADC,
	0x40DF0B66,
	0x37D83BF0,
	0xA9BCAE53,
	0xDEBB9EC5,
	0x47B2CF7F,
	0x30B5FFE9,
	0xBDBDF21C,
	0xCABAC28A,
	0x53B39330,
	0x24B4A3A6,
	0xBAD03605,
	0xCDD70693,
	0x54DE5729,
	0x23D967BF,
	0xB3667A2E,
	0xC4614AB8,
	0x5D681B02,
	0x2A6F2B94,
	0xB40BBE37,
	0xC30C8EA1,
	0x5A05DF1B,
	0x2D02EF8D,
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */

uint32 KLCRC(const char *szString)
{
	if(szString == NULL || szString[0] == 0) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	dwCrc32 = 0xFFFFFFFF;
	int32	nSize = (int32) strlen(szString);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < nSize; i++)
	{
		dwCrc32 = dwCrc32 * 33 + (uchar) szString[i];
	}

	return dwCrc32;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
char Data2Ascii(char in)
{
	__GUARD__ switch(in)
	{
	case 0:		return '0';
	case 1:		return '1';
	case 2:		return '2';
	case 3:		return '3';
	case 4:		return '4';
	case 5:		return '5';
	case 6:		return '6';
	case 7:		return '7';
	case 8:		return '8';
	case 9:		return '9';
	case 10:	return 'A';
	case 11:	return 'B';
	case 12:	return 'C';
	case 13:	return 'D';
	case 14:	return 'E';
	case 15:	return 'F';
	default:	KCheck(FALSE); return '?';
	}

	__UNGUARD__ return '?';
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
char Ascii2Data(char in)
{
	__GUARD__ switch(in)
	{
	case '0':	return 0;
	case '1':	return 1;
	case '2':	return 2;
	case '3':	return 3;
	case '4':	return 4;
	case '5':	return 5;
	case '6':	return 6;
	case '7':	return 7;
	case '8':	return 8;
	case '9':	return 9;
	case 'A':	return 10;
	case 'B':	return 11;
	case 'C':	return 12;
	case 'D':	return 13;
	case 'E':	return 14;
	case 'F':	return 15;
	default:	KCheck(FALSE); return '?';
	}

	__UNGUARD__ return '?';
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CharToString(const char *pIn, uint32 InLength, char *pOut)
{
	__GUARD__ if(InLength == 0)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~*/
	uint32	iOut = 0;
	/*~~~~~~~~~~~~~*/

	for(uint32 i = 0; i < InLength; i++)
	{
		if(pIn[i] == 0)
		{
			pOut[iOut] = -125;
		}
		else
		{
			pOut[iOut] = pIn[i];
		}

		iOut++;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL StringToChar(const char *pIn, uint32 InLength, char *pOut, uint32 OutLimit, uint32 &OutLength)
{
	__GUARD__ if(InLength == 0)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~*/
	uint32	iOut = 0;
	uint32	i;
	/*~~~~~~~~~~~~~*/

	for(i = 0; i < InLength - 1; ++i)
	{
		if(pIn[i] == '\0')
		{
			break;
		}

		if(pIn[i] == -125)
		{
			pOut[iOut] = 0;
		}
		else
		{
			pOut[iOut] = pIn[i];
		}

		iOut++;
		if(iOut >= OutLimit) break;
	}

	OutLength = iOut;
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Binary2Str(const char *pIn, uint32 InLength, char *pOut, uint32 OutLimit)
{
	__GUARD__ if(InLength == 0)
	{
		return FALSE;
	}

	KCheck(InLength * 2 < OutLimit);

	/*~~~~~~~~~~~~~*/
	uint32	iOut = 0;
	/*~~~~~~~~~~~~~*/

	for(uint32 i = 0; i < InLength; i++)
	{
		pOut[iOut] = Data2Ascii(((uchar) pIn[i] & 0xF0) >> 4);
		iOut++;
		pOut[iOut] = Data2Ascii(pIn[i] & 0x0F);
		iOut++;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Str2Binary(const char *pIn, uint32 InLength, char *pOut, uint32 OutLimit, uint32 &OutLength)
{
	__GUARD__ if(InLength == 0)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~*/
	uint32	iOut = 0;
	uint32	i;
	/*~~~~~~~~~~~~~*/

	for(i = 0; i < InLength - 1;)
	{
		if(pIn[i] == '\0' || pIn[i + 1] == '\0')
		{
			break;
		}

		pOut[iOut] = (Ascii2Data(pIn[i]) << 4) + Ascii2Data(pIn[i + 1]);
		iOut++;
		i += 2;
		if(iOut >= OutLimit) break;
	}

	OutLength = iOut;
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CheckStr(const char *pIn, uint32 InLength)
{
	if(InLength == 0)
	{
		return FALSE;
	}

	for(uint32 i = 0; i < InLength; i++)
	{
		switch(pIn[i])
		{
		case '\0':
			{
				return TRUE;
				break;
			}

		case '\'':
		case '\"':
		case ')':
		case '(':
		case '=':
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ODBCEscapeString(const char *in, uint32 len, char *out)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	char	*from = (char *) in;
	char	*to = out;
	uint32	tolen = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(len < 2) return;

	len--;
	while(*from != '\0' && tolen < len)
	{
		if(*from == '\\' || *from == '\'')
		{
			if(tolen >= (len - 2)) break;
			*to++ = '\\';
			tolen++;
		}

		*to++ = *from++;
		tolen++;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
char MyToLower(char c)
{
	return(c < 'A' || c > 'Z') ? (c) : (c + 'a' - 'A');
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void StringLower(char *pStr)
{
	KCheck(pStr);
	for(int32 i = 0; i < strlen(pStr); i++)
	{
		pStr[i] = MyToLower(pStr[i]);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 GetSizeOfMail(const SMail &mail)
{
	if(mail.m_uFlag == MAIL_TYPE_SCRIPT)
	{
		return sizeof(GUID_t) +
			sizeof(uchar) +
			sizeof(char) *
			mail.m_SourSize +
			sizeof(int32) +
			sizeof(uchar) +
			sizeof(char) *
			mail.m_DestSize +
			sizeof(uint16) +
			sizeof(char) *
			mail.m_ContexSize +
			sizeof(uint32) +
			sizeof(uint32) +
			sizeof(uint32) +
			sizeof(uint32) +
			sizeof(uint32) +
			sizeof(uint32);
	}
	else
	{
		return sizeof(GUID_t) +
			sizeof(uchar) +
			sizeof(char) *
			mail.m_SourSize +
			sizeof(int32) +
			sizeof(uchar) +
			sizeof(char) *
			mail.m_DestSize +
			sizeof(uint16) +
			sizeof(char) *
			mail.m_ContexSize +
			sizeof(uint32) +
			sizeof(uint32);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 GetSizeOfMailList(const SMailList &maillist)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uSize = sizeof(uchar) + sizeof(uchar);
	int32	i = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(i = 0; i < maillist.m_Count; i++)
	{
		uSize += GetSizeOfMail(maillist.m_aMail[i]);
	}

	return uSize;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 GetValueByBit(uint32 nDataValue, int32 nOffset, int32 nSize)
{
	KCheck(nOffset >= 0);
	KCheck(nSize > 0);
	KCheck((nOffset + nSize) <= 32);

	if(nOffset >= 0) nDataValue = nDataValue << (32 - nSize - nOffset);
	if(nSize != 32) nDataValue = nDataValue >> (32 - nSize);

	return nDataValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 SetValueByBit(uint32 nDataValue, int32 nOffset, int32 nSize, int32 nValue)
{
	KCheck(nOffset >= 0);
	KCheck(nSize > 0);
	KCheck((nOffset + nSize) <= 32);

	for(int32 i = nOffset; i < nSize + nOffset; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nBit = nValue & (1 << (i - nOffset));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(nBit)
		{
			nDataValue |= (1 << i);
		}
		else
		{
			nDataValue &= (~(1 << i));
		}
	}

	return nDataValue;
}

#if defined(_70_CLIENT) && defined(_70_LOGIN) && defined(_70_WORLD)
#define DUMP_LOG	"./Log/logincenter_dump.log"
#endif
#if defined(_70_CLIENT) && defined(_70_SERVER) && defined(_70_WORLD)
#define DUMP_LOG	"./Log/mapserver_dump.log"
#endif
#if defined(_70_SERVER) && defined(_70_WORLD) && defined(_70_LOGIN)
#define DUMP_LOG	"./Log/glserver_dump.log"
#endif
#if defined(__SHARE_MEM__)
#define DUMP_LOG	"./Log/shm_dump.log"
#endif
#if defined(_70_BILLING) && defined(_70_LOGIN) && (!defined(_70_WORLD))
#define DUMP_LOG	"./Log/billing_dump.log"
#endif
#if defined(_LOG_CENTER_DB) && defined(_70_DBCENTER) && defined(_70_LOGIN) && defined(_70_SHAREMEM)
#define DUMP_LOG	"./Log/dbcenter_dump.log"
#endif

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void StackDump(const char *type)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifdef __LINUX__
	void	*DumpArray[100];
	int32	Size = backtrace(DumpArray, 100);
	char	**symbols = backtrace_symbols(DumpArray, Size);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(symbols)
	{
		if(Size > 95) Size = 95;
		if(Size > 0)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			FILE	*f = fopen(DUMP_LOG, "a");
			char	threadinfo[256] = { 0 };
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			sprintf( threadinfo, 
					"Version=%X threadid = %lu cause dump, (T=%d-%d-%d_%d:%d:%d) \r\n", 
					CURRENT_VERSION, 
					KGetCurrentTID(),
					GET_TIME().year(),
					GET_TIME().month(),
					GET_TIME().day(),
					GET_TIME().hour(),
					GET_TIME().minute(),
					GET_TIME().second() );
			fwrite(threadinfo, 1, strlen(threadinfo), f);
			fwrite(type, 1, strlen(type), f);
			for(int32 i = 0; i < Size; i++)
			{
				printf("%s\r\n", symbols[i]);
				fwrite(symbols[i], 1, strlen(symbols[i]), f);
				fwrite("\r\n", 1, 2, f);
			}

			fwrite("\r\n", 1, 2, f);

			fclose(f);
		}

		free(symbols);
	}
	else
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		FILE	*f = fopen(DUMP_LOG, "a");
		char	buffer[256] = { 0 };
		char	threadinfo[256] = { 0 };
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		sprintf( threadinfo, 
				"Version=%X threadid = %lu cause dump, (T=%d-%d-%d_%d:%d:%d) \r\n", 
				CURRENT_VERSION, 
				KGetCurrentTID(),
				GET_TIME().year(),
				GET_TIME().month(),
				GET_TIME().day(),
				GET_TIME().hour(),
				GET_TIME().minute(),
				GET_TIME().second() );
		fwrite(threadinfo, 1, strlen(threadinfo), f);
		fwrite(type, 1, strlen(type), f);
		fclose(f);
	}
#endif
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void tsnprintf_s(char *buffer, size_t count, const char *format, ...)
{
	/*~~~~~~~~~~~*/
	va_list argptr;
	/*~~~~~~~~~~~*/

	va_start(argptr, format);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nchars = tvsnprintf((char *) buffer, count, format, argptr);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	va_end(argptr);

	if(nchars == count)
	{
		buffer[count - 1] = '\0';
	}

	if(nchars == -1)
	{
		KCheck(FALSE);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ReachTime(uint32 desttime, uint32 now)
{
	if(desttime > now)
	{
		return((uint32) (desttime - now)) > ((uint32) 0x7FFFFFFF);
	}
	else
	{
		return((uint32) (now - desttime)) < ((uint32) 0x7FFFFFFF);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
inline void CalcCrc32(const uchar byte, uint32 &dwCrc32)
{
	dwCrc32 = ((dwCrc32) >> 8) ^ __crc32[(byte) ^ ((dwCrc32) & 0x000000FF)];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 CRC(const char *szBuff, int32 nLen)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	dwCrc32 = 0xFFFFFFFF;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < nLen; i++)
	{
		CalcCrc32(szBuff[i], dwCrc32);
	}

	return dwCrc32;
}

uint32 CheckSum(const char *szBuff, int32 nLen)
{
	uint32	dwCrc32 = 0xFFFFFFFF;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = nLen - 1; i >= 0 ; --i)
	{
		CalcCrc32(szBuff[i], dwCrc32);
	}

	return dwCrc32;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint64 StrToUINT64(const char *szBuff)
{
	/*~~~~~~~~~~~~*/
	uint64	ret = 0;
	/*~~~~~~~~~~~~*/

#if defined(__WINDOWS__)
	sscanf(szBuff, "%I64u", &ret);
#elif defined(__LINUX__)
	sscanf(szBuff, "%llu", &ret);
#endif
	return ret;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PrintU64(uint64 value)
{
#if defined(__WINDOWS__)
	printf("%I64u\n", value);
#elif defined(__LINUX__)
	printf("%llu", value);
#endif
}

uint32			GetHighSection(uint64 uValue)
{
	return (uint32)((uValue >> 32) & 0xFFFFFFFF);
}

uint32			GetLowSection(uint64 uValue)
{
	return (uint32)(uValue & 0xFFFFFFFF);
}

uint64			ToUint64(uint32 uHigh, uint32 uLow)
{
	uint64 u64 = uHigh;
	u64 = ((u64 << 32) | uLow);
	return u64;
}



uint32 KLRandom::		m_uKey = 0;
char KLRandom::		m_pKey[MAX_KEY_SIZE];
FastLock KLRandom::	m_Lock;

RandGenerator				g_RandGenerator = RandGenerator((unsigned) time(NULL));

/*
=======================================================================================================================
=======================================================================================================================
*/

KLRandom::KLRandom()
{
}

/*
=======================================================================================================================
=======================================================================================================================
*/
KLRandom::~KLRandom()
{
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void KLRandom::SetRand(uint32 uKey)
{
	lock_guard<FastLock> autolock(m_Lock);

	m_uKey = uKey % MAX_KEY_SIZE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
uint32 KLRandom::Rand()
{
	lock_guard<FastLock> autolock(m_Lock);

	if(m_uKey == 0)
	{
		srand((unsigned) time(NULL));
		for(int32 i = 0; i < MAX_KEY_SIZE; i++)
		{
			m_pKey[i] = rand() % 255;
		}
	}

	m_uKey++;
	if(m_uKey >= MAX_KEY_SIZE - sizeof(uint32)) m_uKey = 1;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	nRet = *((uint32 *) (m_pKey + m_uKey));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return nRet;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
uint32 RandGenerator::GetRand(int32 nStart, int32 nEnd)
{
	KCheck((nEnd - nStart + 1) > 0);
	return(g_RandGenerator.RandUInt()) % (nEnd - nStart + 1) + (nStart);
}

/*
=======================================================================================================================
=======================================================================================================================
*/
SeedRand::SeedRand()
{
	holdrand = 1;
	seed = 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
SeedRand::~SeedRand()
{
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void SeedRand::SetSeed(int32 s)
{
	holdrand = seed = s;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 SeedRand::Rand()
{
	return(((holdrand = holdrand * 214013 + 2531011) >> 16) & 0x7fff);
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 SeedRand::GetSeed()
{
	return seed;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 SeedRand::GetRandByKey(int32 s, int32 key)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	rand = key * 214013 + s;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return rand;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 SeedRand::GetKeyByRand(int32 s, int32 rand)
{
	/*~~~~~~~~~~~~~~~~~~~*/
	int32	key = rand - s;
	/*~~~~~~~~~~~~~~~~~~~*/

	key = key / 214013;

	return key;
}


#if defined(_70_WORLD)

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL MyDecoder::DecodeLogin(const char *szVerifyCode, char *szAccount)
{
	if(NULL == szVerifyCode)
	{
		return FALSE;
	}

	if(strlen(szAccount) > MAX_ACCOUNT) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char	tmpAccount[MAX_ACCOUNT + 1] = { 0 };
	char	szCode[MAX_CL_VERIFY_CODE + 1] = { 0 };
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memcpy(szCode, szVerifyCode, MAX_CL_VERIFY_CODE);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char	offset = szCode[MAX_CL_VERIFY_CODE - 1];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 verifyIndex = 0; verifyIndex < MAX_ACCOUNT; verifyIndex++)
	{
		szCode[verifyIndex] += szCode[verifyIndex + MAX_ACCOUNT];
	}

	if(offset >= 0 && offset < MAX_ACCOUNT)
	{
		memcpy(tmpAccount, &szCode[offset], MAX_ACCOUNT - offset);

		if(strlen(tmpAccount) < strlen(szAccount))
		{
			memcpy(tmpAccount + strlen(tmpAccount), szCode, strlen(szAccount) - strlen(tmpAccount));
		}

		tmpAccount[strlen(szAccount)] = 0;
	}

	if(strcmp(szAccount, tmpAccount) == 0)
	{
		return TRUE;
	}

	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL MyDecoder::DecodeCharMove(const char *szVerifyCode, const GLPos *paTarPos, uint32 offset)
{
	__GUARD__ if(NULL == paTarPos || NULL == szVerifyCode)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char	checkSum = 0;
	char	szTmp[MAX_CHAR_PATH_NODE_NUMBER + 1] = { 0 };
	int32	nPosX = Float2Int(paTarPos[0].m_fX);
	int32	nPosZ = Float2Int(paTarPos[0].m_fZ);
	int32	nPos = nPosX + nPosZ;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	tsnprintf(szTmp, MAX_CHAR_PATH_NODE_NUMBER, "%d", nPos);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nStrLen = (int32) strlen(szTmp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nStrLen >= MAX_CHAR_PATH_NODE_NUMBER)
	{
		return FALSE;
	}

	for(int32 len = 0; len < nStrLen; ++len) checkSum = checkSum ^ szTmp[len];

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	n3 = offset % 10;
	uint32	n2 = ((offset % 100) - n3) / 10;
	uint32	n1 = offset / 100;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(n3 >= MAX_CHAR_MOVE_VERIFY_CODE || n2 >= MAX_CHAR_MOVE_VERIFY_CODE || n1 >= MAX_CHAR_MOVE_VERIFY_CODE)
	{
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char	csh = (char) ((szVerifyCode[n3] & 0x0F) + ((szVerifyCode[n2] - n1) << 4));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(checkSum != csh || 0 < szVerifyCode[n1] - n1)
	{
		return FALSE;
	}

	return TRUE;
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL MyDecoder::DecodeLockTarget(const char *szVerifyCode, ObjID_t nTargetID, uint32 offset)
{
	if(NULL == szVerifyCode)
	{
		return FALSE;
	}

	if(szVerifyCode[1] == TRUE)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	n3 = offset % 10;
	uint32	n2 = ((offset % 100) - n3) / 10;
	uint32	n1 = offset / 100;
	char	szTarget[MAX_LOCK_TARGET_VERIFY_CODE + 1] = { 0 };
	char	len = szVerifyCode[MAX_LOCK_TARGET_VERIFY_CODE - 1];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(len < 0 || len >= MAX_LOCK_TARGET_VERIFY_CODE)
	{
		return FALSE;
	}

	memcpy(szTarget, szVerifyCode + 2, len);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ObjID_t target = (ObjID_t) atoi(szTarget);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	target = ~target;
	target -= (n2 * 100 + n1 * 10 + n3);
	target = target ^ offset;

	if(nTargetID != target)
	{
		return FALSE;
	}

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL MyDecoder::DecodeHeartBeat(const char *szVerifyCode, uint32 randNum, uint32 offset)
{
	if(NULL == szVerifyCode)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	n3 = offset % 10;
	uint32	n2 = ((offset % 100) - n3) / 10;
	uint32	n1 = offset / 100;
	char	szTarget[MAX_LOCK_HEARTBEAT_VERIFY_CODE] = { 0 };
	char	len = szVerifyCode[MAX_LOCK_HEARTBEAT_VERIFY_CODE - 1];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(len < 0 || len >= MAX_LOCK_HEARTBEAT_VERIFY_CODE)
	{
		return FALSE;
	}

	memcpy(szTarget, szVerifyCode + 4, len);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ObjID_t targetId = (ObjID_t) atoi(szTarget);
	int32	tmp = (n3 & n2) | n1;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	targetId = targetId ^ tmp;

	if(randNum != targetId)
	{
		return FALSE;
	}

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL MyDecoder::DecodeMD5PW(const char *szVerifyCode, char *szSource, int32 iSize, uint32 key)
{
	if(NULL == szVerifyCode || NULL == szSource)
	{
		return FALSE;
	}

	for(int32 i = 0; i < iSize; ++i) szSource[i] = szVerifyCode[i] ^ key;

	return TRUE;
}
#endif
