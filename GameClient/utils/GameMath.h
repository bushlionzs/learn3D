/*$T Client/Game/Temp/GameMath.h GC 1.140 08/23/09 04:52:44 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


/* ���ߺ����� */
#ifndef _GAME_MATH_H_
#define _GAME_MATH_H_


class CGameMath
{
public:
		
	/* ȡ�������ľ��� */
	static
	FLOAT	KLU_GetDist(const vector2 &fvPos1, const vector2 &fvPos2);
	static
	FLOAT	KLU_GetDist(const vector3 &fvPos1, const vector3 &fvPos2);
	
	/* ȡ�������ľ���ƽ�� */
	static
	FLOAT	KLU_GetDistSq(const vector2 &fvPos1, const vector2 &fvPos2);
	static
	FLOAT	KLU_GetDistSq(const vector3 &fvPos1, const vector3 &fvPos2);


	/*
	* | | �����������ĵ�� | ;
	* inline float KLU_DotProduct(const vector2& vec1, const vector2& vec2) ;
	* { ;
	* return vec1.x * vec2.x + vec1.y * vec2.y;
	* } ;
	* | | ȡ�ô�Pos1��Pos2��ʸ�������Y�����ת�Ƕ�, ��z��Ϊ0�� | | ->x | o pos1 | |
	* |\ | z v | \ | | \ | | \ | | o pos2 | | Return [0 ~ 2pi
	*/
	static
	FLOAT KLU_GetYAngle(const vector2 &fvPos1, const vector2 &fvPos2);

	/*
	* | | ȡ�ô�Pos1��Pos2֮������ĵ� | | ->x | o pos2 | | / | z v o <- This point!
	* | / | o | pos1 |
	*/
	static
	vector3 KLU_GetCenter(const vector3 &fvPos1, const vector3 &fvPos2);

	/*
	* | | ȡ��v1����ڴ�Pos1��Pos2֮��ֱ�ߵľ���� | | ->x | o pos2 | | v1 / | z v \
	* / | \/ | / \ | o \ | pos1 v2 <- This point! |
	*/
	static
	vector2 KLU_GetReflect(const vector2 &fvPos1, const vector2 &fvPos2, const vector2 &v1);


	/*
	* | CGameMath::KLU_RotateAngle ʹĿ�����ݷ�������ת��������ת������ꡣ | | pos
	* Ҫ��ת��Ŀ������� | axis ��ԭ��Ϊ����ʸ�������� | angle ��ת�ĽǶ� | |
	* ע��axis�ᱻ��λ��������ԭ��Ϊ��ʼ���ʸ������������������������ת�� |
	* ��Ҫ�Ƚ�Ŀ�������Ӧ��ƽ�ƣ����øú�����ת����ƽ�ƻ�ȥ���ɡ� |
	*/
	static
	vector3 KLU_RotateAngle(const vector3 &pos, const vector3 &axis, FLOAT angle);

	/*
	* | hermite���߲�ֵ�㷨�����߱�����Ϊ150�Σ��������������2D����λ�� | |
	* x1,y1,x2,y2 ���߶˵㣬�����ֵ������1000���ڣ��������ʱ�ᳬ�����㷶Χ |
	* xr1,yr1,xr2,yr2 �������ο�����, ���������1000���� | currIter
	* ��ǰ������ֵ�޶���150����?
	*/
	static
	POINT HermiteCurve(int32 x1, int32 y1, int32 x2, int32 y2, int32 xr1, int32 yr1, int32 xr2, int32 yr2, int32 currIter);

	/* | ͬ CGameMath::HermiteCurve */
	static
	POINT BezierCurve(int32 x1, int32 y1, int32 x2, int32 y2, int32 xr1, int32 yr1, int32 xr2, int32 yr2, int32 currIter);


	/* ����Ƿ�Ϊ����ֵ, ������ */
	static
	BOOL KLU_IsNan(FLOAT &fValue);
	static
	BOOL KLU_IsNan(vector3 &fvPos);

	/*
	* | r=CGameMath::KLU_Multiply(sp,ep,op), �õ�(sp-op)*(ep-op)�Ĳ�� | r>0 :
	* ep��ʸ��opsp����ʱ�뷽�� | r=0 �����㹲�ߣ� | r<0 : ep��ʸ��opsp��˳ʱ�뷽��
	*/
	static
	FLOAT KLU_Multiply(const vector2 &fvSp, const vector2 &fvEp, const vector2 &fvOp);

	/* �жϵ��Ƿ����߶��� */
	static
	BOOL KLU_PointInLine(const vector2 &fvTar, const vector2 &fvLineA, const vector2 &fvLineB);

	/* �õ�ƫ��λ�� */
	static
	vector2 KLU_GetTargetPos(const vector2 &fvCurrPos, const vector2 &fvTargetPos, FLOAT fGoDist);
	static
	vector3 KLU_GetTargetPos(const vector3 &fvCurrPos, const vector3 &fvTargetPos, FLOAT fGoDist);

};	// class CGameMath


class CGameUtils
{
public:

	/* �ݹ鴴��Ŀ¼ */
	static
	BOOL KLU_CreatePath(const char *szPath);

	/* ����ַ����ķǷ��ַ� ����ֵ�� TRUE �����зǷ��ַ� FALSE �зǷ��ַ� */
	static
	BOOL KLU_CheckStringValid(const char *pStr);

};	// class 

#endif /* _GAME_MATH_H_ */
