/*$T Common/HumanStateMutex.cpp GC 1.140 10/10/07 10:06:30 */

/*
 * created: 2008/10/10 created: 10:10:2008 12:11 filename:
 * Common\HumanStateMutex.cpp file path: Common file base: HumanStateMutex file
 * ext: cpp author: Richard purpose:
 */
#include "stdafx.h"
#include "TypeDefine.h"
#include "TAB.h"
#include "HumanStateMutex.h"

PlayerStateMutex	g_HumanStateMutex;

/*
 =======================================================================================================================
 =======================================================================================================================
 */

PlayerStateMutex::PlayerStateMutex()
{
	Clear();

	m_iMutexStateCode = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
PlayerStateMutex::~PlayerStateMutex()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerStateMutex::Clear(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	memset(&m_oStateMutex, 0, sizeof(m_oStateMutex));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL PlayerStateMutex::InitStateMutexTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ TAB::TABFile	ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_HUMAN_MUTEX);
	int32			iTableCount = ThirdFile.GetRecordsNum();
	int32			iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/* 此断言是防止意外的文件改变 */
	KCheck(iTableCount > 0 && iTableCount == MS_NumOfMutexState && "./../Public/Config/PlayerStateMutex.tab");

	/* 末尾有注释列 */
	KCheck(iColumnCount > 0 && iColumnCount == ME_NumOfStateEvent + 2 && "./../Public/Config/PlayerStateMutex.tab");

	for(int32 i = 0; i < iTableCount; ++i)
	{
		InitTableLine(ThirdFile, iColumnCount, i);
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerStateMutex::InitTableLine(TAB::TABFile &ThirdFile, int32 iColumnCount, int32 i)
{
	__GUARD__

	/* 跳过序号列 */
	for(int32 iColum = 1; iColum < iColumnCount - 1; ++iColum)
	{
		m_oStateMutex.aMutexState[i][iColum - 1] = ThirdFile.Search_Posistion(i, iColum)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL PlayerStateMutex::IsCanAccptEvent(const Player *pPlayer, _MutexStateEvent eEvent)
{
	return true;
}
