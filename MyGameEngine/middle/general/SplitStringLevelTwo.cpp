#include "OgreHeader.h"
#include "SplitStringLevelTwo.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

bool SplitStringLevelTwo::DoSplit(const char *strSplit)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	OGRE_CHECK(strSplit != NULL && m_SplitChar != 0, "SplitStringLevelTwo::DoSplit 1");
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	OGRE_CHECK(strlen(strSplit) < MAX_SPLIT_STRING_LENGTH, "SplitStringLevelTwo::DoSplit 2");
	if(strlen(strSplit) >= MAX_SPLIT_STRING_LENGTH) return false;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32_t	iPos = (int32_t) strcspn(strSplit, m_SplitChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iPos <= 0) return false;

	if(strSplit[iPos] != m_SplitChar[0])
	{
		OGRE_CHECK(strlen(strSplit) < MAX_FINAL_STRING_LENGTH, "SplitStringLevelTwo::DoSplit 3");
		if(strlen(strSplit) >= MAX_FINAL_STRING_LENGTH) return FALSE;

		strcpy(m_strSplitLevelOne[m_iLevelOneLineCount++], strSplit);
		return false;
	}

	DoSubLevelSplit(iPos, strSplit);

	DoSubSplit();
	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SplitStringLevelTwo::DoSubLevelSplit(int32 iPos, const char *strSplit)
{
	memset(m_strSplitLevelTwo, 0, sizeof(m_strSplitLevelTwo));
	int32		iIndex = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	while(iPos)
	{
		strncpy(m_strSplitLevelTwo[iIndex], strSplit, iPos);

		strSplit += iPos + 1;
		++iIndex;

		iPos = (int32) strcspn(strSplit, m_SplitChar);
	}

	OGRE_CHECK(iIndex % 2 == 0, "SplitStringLevelTwo::DoSubLevelSplit");

	if(iIndex % 2 != 0) return;

	/*~~~~~~~~~~~~~~~*/
	int32	iStart;
	int32	iEnd;
	char	strTmp[32];
	/*~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iIndex; i += 2)
	{
		iStart = atoi(m_strSplitLevelTwo[i]);
		iEnd = atoi(m_strSplitLevelTwo[i + 1]);
		if(iEnd - iStart >= MAX_LEVEL_ONE_LENGTH)
		{
			iEnd = iEnd - (iEnd - iStart - MAX_LEVEL_ONE_LENGTH + 1);
		}

		for(int32 j = iStart; j <= iEnd; ++j)
		{
			snprintf(strTmp, 32, "%d", j);
			if(m_iLevelOneLineCount >= MAX_LEVEL_ONE_LENGTH)
			{
				break;
			}

			strcpy(m_strSplitLevelOne[m_iLevelOneLineCount++], strTmp);
		}
	}
}
