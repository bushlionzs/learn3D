#include "stdafx.h"
#include "data_define.h"

int32_t MonsterAIData::get(uint32_t aiType, uint32_t aiParam)
{
	if (aiType >= mAIData.size() || aiParam >= mAIData[aiType].size())
	{
		assert(false);
	}

	return mAIData[aiType][aiParam];
}