
#ifndef SplitStringLevelTwo_h__
#define SplitStringLevelTwo_h__

#include "SplitStringBase.h"

class SplitStringLevelTwo :
	public SplitStringBase
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual bool DoSplit(const char *strSplit);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	void	DoSubLevelSplit(int32_t iPos, const char *strSplit);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	char	m_strSplitLevelTwo[MAX_LEVEL_ONE_LENGTH][MAX_SPLIT_STRING_LENGTH];
};
#endif
