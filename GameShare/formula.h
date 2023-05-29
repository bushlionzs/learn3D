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
const int32	HORSEGROWRATETYPE_NORMAL_MAXVALUE = 100;		/* һ��� */
const int32	HORSEGROWRATETYPE_GOOD_MAXVALUE = 200;			/* ���õ� */
const int32	HORSEGROWRATETYPE_EXCELLENCE_MAXVALUE = 300;		/* ����� */
const int32	HORSEGROWRATETYPE_ESPECIALLY_EXCELLENCE_MAXVALUE = 400; /* ׿Խ�� */

enum HorseGrowRateType
{
	HORSEGROWRATETYPE_NORMAL		= 0,			/* һ��� */
	HORSEGROWRATETYPE_GOOD			= 1,			/* ���õ� */
	HORSEGROWRATETYPE_EXCELLENCE		= 2,			/* ����� */
	HORSEGROWRATETYPE_ESPECIALLY_EXCELLENCE = 3,			/* ׿Խ�� */

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
