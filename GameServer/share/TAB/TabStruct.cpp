#include "stdafx.h"
#include "TabStruct.h"
#include "SplitStringLevelOne.h"
#include "SplitStringLevelTwo.h"


/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CommonStringSplit
(
	SplitStringLevelOne	*pSplitL1,
	SplitStringLevelTwo	*pSplitL2,
	const char		*pSplitString,
	int32			iMaxNum,
	int32			*pArry
)
{
	__GUARD__ 
	pSplitL1->Reset();
	pSplitL2->Reset();
	pSplitL1->Init('|', pSplitL2);
	pSplitL2->Init('~', NULL);
	pSplitL1->DoSplit(pSplitString);

	int32	iLineCount = pSplitL2->GetResultLineCount();

	KCheck(iMaxNum >= iLineCount);
	for(int32 i = 0; i < iLineCount; ++i)
	{
		pArry[i] = atoi(pSplitL2->GetResultLine(i));
	}

	return iLineCount;
	__UNGUARD__ 
	return 0;
}
