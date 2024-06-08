/*$T Client/Game/Temp/GameMath.h GC 1.140 08/23/09 04:52:44 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


/* 工具函数集 */
#ifndef _GAME_MATH_H_
#define _GAME_MATH_H_


class CGameMath
{
public:
		
	/* 取得两点间的距离 */
	static
	FLOAT	KLU_GetDist(const vector2 &fvPos1, const vector2 &fvPos2);
	static
	FLOAT	KLU_GetDist(const vector3 &fvPos1, const vector3 &fvPos2);
	
	/* 取得两点间的距离平方 */
	static
	FLOAT	KLU_GetDistSq(const vector2 &fvPos1, const vector2 &fvPos2);
	static
	FLOAT	KLU_GetDistSq(const vector3 &fvPos1, const vector3 &fvPos2);


	/*
	* | | 求两个向量的点积 | ;
	* inline float KLU_DotProduct(const vector2& vec1, const vector2& vec2) ;
	* { ;
	* return vec1.x * vec2.x + vec1.y * vec2.y;
	* } ;
	* | | 取得从Pos1到Pos2的矢量相对于Y轴的旋转角度, 以z轴为0度 | | ->x | o pos1 | |
	* |\ | z v | \ | | \ | | \ | | o pos2 | | Return [0 ~ 2pi
	*/
	static
	FLOAT KLU_GetYAngle(const vector2 &fvPos1, const vector2 &fvPos2);

	/*
	* | | 取得从Pos1与Pos2之间的中心点 | | ->x | o pos2 | | / | z v o <- This point!
	* | / | o | pos1 |
	*/
	static
	vector3 KLU_GetCenter(const vector3 &fvPos1, const vector3 &fvPos2);

	/*
	* | | 取得v1相对于从Pos1与Pos2之间直线的镜像点 | | ->x | o pos2 | | v1 / | z v \
	* / | \/ | / \ | o \ | pos1 v2 <- This point! |
	*/
	static
	vector2 KLU_GetReflect(const vector2 &fvPos1, const vector2 &fvPos2, const vector2 &v1);


	/*
	* | CGameMath::KLU_RotateAngle 使目标点根据方向轴旋转，返回旋转后的坐标。 | | pos
	* 要旋转的目标点坐标 | axis 以原点为起点的矢量方向轴 | angle 旋转的角度 | |
	* 注：axis会被单位化，变以原点为起始点的矢量方向。如果想根据任意轴做旋转， |
	* 需要先将目标点做相应的平移，调用该函数旋转后，再平移回去即可。 |
	*/
	static
	vector3 KLU_RotateAngle(const vector3 &pos, const vector3 &axis, FLOAT angle);

	/*
	* | hermite曲线差值算法。曲线被划分为150段，返回所需段数的2D坐标位置 | |
	* x1,y1,x2,y2 曲线端点，最好数值限制在1000以内，否侧运算时会超出运算范围 |
	* xr1,yr1,xr2,yr2 曲线两参考向量, 最好限制在1000以内 | currIter
	* 当前段数，值限定在150以内?
	*/
	static
	POINT HermiteCurve(int32 x1, int32 y1, int32 x2, int32 y2, int32 xr1, int32 yr1, int32 xr2, int32 yr2, int32 currIter);

	/* | 同 CGameMath::HermiteCurve */
	static
	POINT BezierCurve(int32 x1, int32 y1, int32 x2, int32 y2, int32 xr1, int32 yr1, int32 xr2, int32 yr2, int32 currIter);


	/* 检测是否为非数值, 并修正 */
	static
	BOOL KLU_IsNan(FLOAT &fValue);
	static
	BOOL KLU_IsNan(vector3 &fvPos);

	/*
	* | r=CGameMath::KLU_Multiply(sp,ep,op), 得到(sp-op)*(ep-op)的叉积 | r>0 :
	* ep在矢量opsp的逆时针方向； | r=0 ：三点共线； | r<0 : ep在矢量opsp的顺时针方向
	*/
	static
	FLOAT KLU_Multiply(const vector2 &fvSp, const vector2 &fvEp, const vector2 &fvOp);

	/* 判断点是否在线段上 */
	static
	BOOL KLU_PointInLine(const vector2 &fvTar, const vector2 &fvLineA, const vector2 &fvLineB);

	/* 得到偏移位置 */
	static
	vector2 KLU_GetTargetPos(const vector2 &fvCurrPos, const vector2 &fvTargetPos, FLOAT fGoDist);
	static
	vector3 KLU_GetTargetPos(const vector3 &fvCurrPos, const vector3 &fvTargetPos, FLOAT fGoDist);

};	// class CGameMath


class CGameUtils
{
public:

	/* 递归创建目录 */
	static
	BOOL KLU_CreatePath(const char *szPath);

	/* 检查字符串的非法字符 返回值： TRUE 不含有非法字符 FALSE 有非法字符 */
	static
	BOOL KLU_CheckStringValid(const char *pStr);

};	// class 

#endif /* _GAME_MATH_H_ */
