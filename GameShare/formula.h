/*$T Common/formula.h GC 1.140 10/10/07 10:06:30 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _FORMULA_H_
#define _FORMULA_H_

#include "TypeDefine.h"

namespace	formula
{
const int32	HORSEGROWRATETYPE_NORMAL_MAXVALUE = 100;		/* 一般的 */
const int32	HORSEGROWRATETYPE_GOOD_MAXVALUE = 200;			/* 良好的 */
const int32	HORSEGROWRATETYPE_EXCELLENCE_MAXVALUE = 300;		/* 优秀的 */
const int32	HORSEGROWRATETYPE_ESPECIALLY_EXCELLENCE_MAXVALUE = 400; /* 卓越的 */

enum HorseGrowRateType
{
	HORSEGROWRATETYPE_NORMAL		= 0,			/* 一般的 */
	HORSEGROWRATETYPE_GOOD			= 1,			/* 良好的 */
	HORSEGROWRATETYPE_EXCELLENCE		= 2,			/* 优秀的 */
	HORSEGROWRATETYPE_ESPECIALLY_EXCELLENCE = 3,			/* 卓越的 */

	HORSEGROWRATETYPE_COUNT
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */

int32 GetHorseGrowRateType(int32 iHorseGrowRate)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iType = HORSEGROWRATETYPE_NORMAL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iHorseGrowRate < HORSEGROWRATETYPE_NORMAL_MAXVALUE)
	{
		iType = HORSEGROWRATETYPE_NORMAL;
	}
	else if(iHorseGrowRate < HORSEGROWRATETYPE_GOOD_MAXVALUE)
	{
		iType = HORSEGROWRATETYPE_GOOD;
	}
	else if(iHorseGrowRate < HORSEGROWRATETYPE_EXCELLENCE_MAXVALUE)
	{
		iType = HORSEGROWRATETYPE_EXCELLENCE;
	}
	else if(iHorseGrowRate < HORSEGROWRATETYPE_ESPECIALLY_EXCELLENCE_MAXVALUE)
	{
		iType = HORSEGROWRATETYPE_ESPECIALLY_EXCELLENCE;
	}

	return iType;
}
}
#endif
