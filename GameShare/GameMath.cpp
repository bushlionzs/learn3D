#include "OgreHeader.h"
#include "GameMath.h"
#include <Shlwapi.h>

/*
 =======================================================================================================================
    数学相关
 =======================================================================================================================
 */
 
FLOAT CGameMath::KLU_GetDist(const vector2 &fvPos1, const vector2 &fvPos2)
{
	return sqrtf((fvPos1.x - fvPos2.x) * (fvPos1.x - fvPos2.x) + (fvPos1.y - fvPos2.y) * (fvPos1.y - fvPos2.y));
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
FLOAT CGameMath::KLU_GetDist(const vector3 &fvPos1, const vector3 &fvPos2)
{
	return sqrtf
		(
			(fvPos1.x - fvPos2.x) * (fvPos1.x - fvPos2.x) + (fvPos1.y - fvPos2.y) * (fvPos1.y - fvPos2.y) +
				(fvPos1.z - fvPos2.z) * (fvPos1.z - fvPos2.z)
		);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
FLOAT CGameMath::KLU_GetDistSq(const vector2 &fvPos1, const vector2 &fvPos2)
{
	return(fvPos1.x - fvPos2.x) * (fvPos1.x - fvPos2.x) + (fvPos1.y - fvPos2.y) * (fvPos1.y - fvPos2.y);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
FLOAT CGameMath::KLU_GetDistSq(const vector3 &fvPos1, const vector3 &fvPos2)
{
	return(fvPos1.x - fvPos2.x) * (fvPos1.x - fvPos2.x) + (fvPos1.y - fvPos2.y) * (fvPos1.y - fvPos2.y) + (fvPos1.z - fvPos2.z) * (fvPos1.z - fvPos2.z);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
FLOAT CGameMath::KLU_GetYAngle(const vector2 &fvPos1, const vector2 &fvPos2)
{
	DOUBLE dDistance = 0.f;
	DOUBLE fACos = 0.f;

	if (fabs(fvPos1.x - fvPos2.x) < 0.001f)
	{
		if (fvPos2.y > fvPos1.y)
			fACos = 1.f;
		else
			fACos = -1.f;
	}
	else
	{
		dDistance = (DOUBLE) CGameMath::KLU_GetDist(fvPos1, fvPos2);
		if(dDistance < 0.0001f)
			return 0.0f;

		fACos = (fvPos2.y - fvPos1.y) / dDistance;
	}

	if(fACos > 1.0)
		fACos = 0.0;
	if(fACos < -1.0)
		fACos = KLU_PI;

	if(fACos > -KLU_MINFLOAT && fACos < KLU_MINFLOAT)
	{
		if(fvPos2.x > fvPos1.x)
			return (FLOAT) KLU_PI * 0.5f;
		else
			return -(FLOAT) KLU_PI * 0.5f;
	}

	fACos = ::acos(fACos);

	/* [0~180] */
	if(fvPos2.x >= fvPos1.x) 
		return (FLOAT)fACos;

	/* (180, 360) */	
	return (FLOAT)(2 * KLU_PI - fACos);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
POINT CGameMath::HermiteCurve(int32 x1, int32 y1, int32 x2, int32 y2, int32 xr1, int32 yr1, int32 xr2, int32 yr2, int32 currIter)
{
	const int32 Iterative = 150;	/* 曲线仿真的线数(控制在150以内， 否则算法出错) */
	const int32 Iterative2 = Iterative * Iterative;
	const int32 Iterative3 = Iterative2 * Iterative;

	if(currIter > Iterative)
	{
		currIter = Iterative;
	}

	int32 oldx = x1, oldy = y1, m1 = Iterative3, m2 = 0, m3 = 0, m4 = 0, k1 = 0, k2 = 0;
	POINT point;

	for(int32 i = 0; i < 150; ++i)
	{
		k1 = (i << 1) + 1;
		k2 = (k1 + i) * i + k1;
		m4 += (k2 -= (k1 *= Iterative));
		m3 += (k1 = k2 - k1) + Iterative2;
		m2 -= (k2 += k1);
		m1 += k2;

		point.x = (int32) ((x1 * m1 + x2 * m2 + xr1 * m3 + xr2 * m4) / Iterative3);
		point.y = (int32) ((y1 * m1 + y2 * m2 + yr1 * m3 + yr2 * m4) / Iterative3);

		if(i >= currIter) return point;
	}

	return point;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
POINT CGameMath::BezierCurve(int32 x1, int32 y1, int32 x2, int32 y2, int32 xr1, int32 yr1, int32 xr2, int32 yr2, int32 currIter)
{
	return CGameMath::HermiteCurve(x1, y1, x2, y2, 3 * (xr1 - x1), 3 * (yr1 - y1), 3 * (x2 - xr2), 3 * (y2 - yr2), currIter);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
vector3 CGameMath::KLU_RotateAngle(const vector3 &pos, const vector3 &axis, FLOAT angle)
{
	const vector3 vector = pos;
	vector3 unitAxis = axis;

	unitAxis.normalise();

	const float halfAngle = angle / float(2);
	const float s = sin(halfAngle);
	const float c = cos(halfAngle);
	const float x = unitAxis.x * s;
	const float y = unitAxis.y * s;
	const float z = unitAxis.z * s;
	const float w = c;
	const float xx = x * x;
	const float xy = y * x;
	const float xz = z * x;
	const float yy = y * y;
	const float yz = z * y;
	const float zz = z * z;
	const float wx = w * x;
	const float wy = w * y;
	const float wz = w * z;
	const float M[3][3] =
	{
		{ float(1) - float(2) * (yy + zz), float(2) * (xy - wz), float(2) * (xz + wy) },
		{ float(2) * (xy + wz), float(1) - float(2) * (xx + zz), float(2) * (yz - wx) },
		{ float(2) * (xz - wy), float(2) * (yz + wx), float(1) - float(2) * (xx + yy) },
	};

	return vector3
		(
			vector.x * M[0][0] + vector.y * M[0][1] + vector.z * M[0][2],
			vector.x * M[1][0] + vector.y * M[1][1] + vector.z * M[1][2],
			vector.x * M[2][0] + vector.y * M[2][1] + vector.z * M[2][2]
		);
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
vector3 CGameMath::KLU_GetCenter(const vector3 &fvPos1, const vector3 &fvPos2)
{
	vector3 fvRet;

	fvRet.x = (fvPos1.x + fvPos2.x) / 2.0f;
	fvRet.y = (fvPos1.y + fvPos2.y) / 2.0f;
	fvRet.z = (fvPos1.z + fvPos2.z) / 2.0f;

	return fvRet;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
#if 0
vector2 KLU_Normalise(const vector2 &vec)
{
	vector2 fvRet = vec;
	float fLength = sqrt(fvRet.x * fvRet.x + fvRet.y * fvRet.y);

	/* Will also work for zero-sized vectors, but will change nothing */
	if(fLength > 1e-08)
	{
		float fInvLength = 1.0f / fLength;

		fvRet.x *= fInvLength;
		fvRet.y *= fInvLength;
	}

	return fvRet;
}
#endif

/*
 =======================================================================================================================
 =======================================================================================================================
 */
vector2 CGameMath::KLU_GetReflect(const vector2 &fvPos1, const vector2 &fvPos2, const vector2 &v1)
{
	/* pos1 -> pos2 */
	vector2 fvNormal = fvPos2 - fvPos1;

	fvNormal.normalise();

	/* pos1 -> v1 */
	vector2 fvLine1 = v1 - fvPos1;

	/* pos1 -> v2 */
	vector2 fvLine2 = 2 * fvLine1.dotProduct(fvNormal) * fvNormal - fvLine1;

	/* return v2 */
	return fvLine2 + fvPos1;
}


/*
 =======================================================================================================================
    检测是否为非数值, 并修正
 =======================================================================================================================
 */
BOOL CGameMath::KLU_IsNan(FLOAT &fValue)
{
	try
	{
		if(0 != _isnan(fValue) || fValue != fValue)
		{
			fValue = 0.f;
			return TRUE;	/* 说明是无效的数字 */
		}
	}
	catch(...)
	{
		fValue = 0.f;
		return TRUE;		/* 说明是无效的数字 */
	}

	return FALSE;			/* 说明是有效的数字 */
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */

BOOL CGameMath::KLU_IsNan(vector3 &fvPos)
{
	try
	{
		if(!CGameMath::KLU_IsNan(fvPos.x) && !CGameMath::KLU_IsNan(fvPos.y) && !CGameMath::KLU_IsNan(fvPos.z)) return FALSE;
	}
	catch(...)
	{
		return TRUE;
	}

	return TRUE;	/* 说明是无效的数字 */
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */

FLOAT CGameMath::KLU_Multiply(const vector2 &fvSp, const vector2 &fvEp, const vector2 &fvOp)
{
	return((fvSp.x - fvOp.x) * (fvEp.y - fvOp.y) - (fvEp.x - fvOp.x) * (fvSp.y - fvOp.y));
}

/*
 =======================================================================================================================
    判断点是否在线段上
 =======================================================================================================================
 */
BOOL CGameMath::KLU_PointInLine(const vector2 &fvTar, const vector2 &fvLineA, const vector2 &fvLineB)
{
	if(fvLineA == fvLineB)
	{
		if(fvTar == fvLineA)
			return TRUE;
		else
			return FALSE;
	}

	/* 共线 */
	FLOAT fMult = CGameMath::KLU_Multiply(fvLineA, fvTar, fvLineB);

	if(fabs(fMult) > 0.001f)
	{
		/* 容错0.1米 */
		FLOAT fDist = fMult / CGameMath::KLU_GetDist(fvLineA, fvLineB);

		if(fabs(fDist) > 0.1f)
		{
			return FALSE;
		}
	}

	/* 线段内, 容错1厘米 */
	if((fvTar.x - fvLineA.x) * (fvTar.x - fvLineB.x) > 0.f)
	{
		if(fabs(fvTar.x - fvLineA.x) > 0.01f && fabs(fvTar.x - fvLineB.x) > 0.01f)
		{
			return FALSE;
		}
	}

	if((fvTar.y - fvLineA.y) * (fvTar.y - fvLineB.y) > 0.f)
	{
		if(fabs(fvTar.y - fvLineA.y) > 0.01f && fabs(fvTar.y - fvLineB.y) > 0.01f)
		{
			return FALSE;
		}
	}

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
vector2 CGameMath::KLU_GetTargetPos(const vector2 &fvCurrPos, const vector2 &fvTargetPos, FLOAT fGoDist)
{
	vector2 fPos;
	FLOAT fMTDist = CGameMath::KLU_GetDist(fvCurrPos, fvTargetPos);

	fPos.x = fvCurrPos.x + fGoDist * (fvTargetPos.x - fvCurrPos.x) / fMTDist;
	fPos.y = fvCurrPos.y + fGoDist * (fvTargetPos.y - fvCurrPos.y) / fMTDist;

	return fPos;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
vector3 CGameMath::KLU_GetTargetPos(const vector3 &fvCurrPos, const vector3 &fvTargetPos, FLOAT fGoDist)
{
	vector3 fPos;
	FLOAT fMTDist = CGameMath::KLU_GetDist(fvCurrPos, fvTargetPos);

	fPos.x = fvCurrPos.x + fGoDist * (fvTargetPos.x - fvCurrPos.x) / fMTDist;
	fPos.y = fvCurrPos.y + fGoDist * (fvTargetPos.y - fvCurrPos.y) / fMTDist;
	fPos.z = fvCurrPos.z + fGoDist * (fvTargetPos.z - fvCurrPos.z) / fMTDist;

	return fPos;
}



/*
 =======================================================================================================================
    递归创建目录
 =======================================================================================================================
 */
BOOL CGameUtils::KLU_CreatePath(const char *szPath)
{
	/* 目录已经存在 */
	if(::PathFileExists(szPath)) return TRUE;

	/* 能够直接创建 */
	if(::CreateDirectory(szPath, 0)) return TRUE;

	/* 取得上一级目录 */
	char szParentPath[MAX_PATH] = { 0 };

	strncpy(szParentPath, szPath, MAX_PATH);
	if(!::PathRemoveFileSpec(szParentPath)) return FALSE;

	/* 创建上一级目录 */
	if(!CGameUtils::KLU_CreatePath(szParentPath)) return false;

	return TRUE == ::CreateDirectory(szPath, 0);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CGameUtils::KLU_CheckStringValid(const char *pStr)
{
	const char	*szInvalid = " #\\/`~!@~$%^&*()-_+=|{}[];:'\"<>,.?";
	typedef struct tagInvalidHanZi
	{
		BYTE cHigh;

		BYTE cLowBegin;
		BYTE cLowEnd;
	} InvalidHanZi;

	/* 不可见字符区 */
	static InvalidHanZi szHZInvalid[] =
	{
		{ 0xA1, 0xA1, 0xA1 },
		{ 0xA4, 0xF4, 0xFE },

		/* v4 */
		{ 0xA5, 0xF7, 0xFE },

		/* v5 */
		{ 0xA6, 0xB9, 0xFE },

		/* v6 */
		{ 0xA7, 0xC2, 0xFE },

		/* v7 */
		{ 0xA8, 0xC1, 0xFE },

		/* v8 */
		{ 0xA9, 0xA1, 0xFE },

		/* v9 */
	};

	if(NULL == pStr) return FALSE;

	std::string strName(pStr);

	if(strName.empty()) return FALSE;

	/* 查找是否有非法ascii字符 */
	String::size_type	nInvalidPos = strName.find_first_of(szInvalid);

	if(nInvalidPos == String::npos)
	{
		/* 中文检查 */
		for(int32 i = 0; i < (int32) strName.length(); ++i)
		{
			BYTE bNow = strName.at(i);

			if(IsDBCSLeadByte(bNow))
			{
				for(int32 k = 0; k < sizeof(szHZInvalid) / sizeof(InvalidHanZi); ++k)
				{
					if(bNow == szHZInvalid[k].cHigh && i + 1 < (int32) strName.length())
					{
						BYTE bNext = strName.at(i + 1);

						/* 发现非法字符 */
						if(bNext >= szHZInvalid[k].cLowBegin && bNext <= szHZInvalid[k].cLowEnd)
						{
							nInvalidPos = i;
							break;
						}
					}
				}

				i++;	/* 跳过DBCS的第二个字节 */
			}

			if(nInvalidPos != String::npos) break;
		}
	}

	if(nInvalidPos != String::npos)
	{
		return FALSE;
	}

	return TRUE;
}
