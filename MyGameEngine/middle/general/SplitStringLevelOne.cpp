#include "OgreHeader.h"
#include "SplitStringLevelOne.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

bool SplitStringLevelOne::DoSplit(const char *strSplit)
{
	OGRE_CHECK(strSplit != NULL && m_SplitChar != 0, "SplitStringLevelOne::DoSplit");
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	OGRE_CHECK(strlen(strSplit) <= MAX_INPUT_STRING_LENGTH, "SplitStringLevelOne::DoSplit");

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	size_t	iPos = strcspn(strSplit, m_SplitChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iPos <= 0) return false;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iIndex = m_iLevelOneLineCount;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	while(iPos)
	{
		OGRE_CHECK(iIndex < MAX_LEVEL_ONE_LENGTH, "SplitStringLevelOne::DoSplit");
		OGRE_CHECK(iPos < MAX_SPLIT_STRING_LENGTH, "SplitStringLevelOne::DoSplit");

		if(iIndex >= MAX_LEVEL_ONE_LENGTH || iPos >= MAX_SPLIT_STRING_LENGTH) return FALSE;

		strncpy(m_strSplitLevelOne[iIndex], strSplit, iPos);
		++iIndex;

		if(*(strSplit + iPos) == 0) break;

		strSplit += iPos + 1;

		iPos = strcspn(strSplit, m_SplitChar);
	}

	m_iLevelOneLineCount = iIndex;
	DoSubSplit();

	return true;

}
