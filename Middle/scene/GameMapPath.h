
#ifndef _MAP_PATH_H_
#define _MAP_PATH_H_


#include "Glpos.h"
#include "KDefine.h"
class CMap;
class CMapRegion;

#define MAX_PATH_NODE_NUM		(1024)

class CMapPath
{
public:
	CMapPath();
	virtual		~CMapPath();


public:

	struct PathUnit
	{
		vector2 fvStart;				/* 起始点 */
		vector2 fvTarget;				/* 目标点 */
	};

	/* 计算从开始点到结束点的路径。 */
	BOOL CreateMovePath(const vector2 &fvCurrent, const vector2 &fvTarget);

	/* 直接查找目的地。 */
	BOOL GetPathDirect(const vector2 &fvCurrent, const vector2 &fvTarget, BOOL bOffset = FALSE, FLOAT fMinDist = 1.5f);

	/* 查找当前的直线与一个区域是否相交，如果相交返回交点和区域中最近相交直线的索引值 */
	BOOL CheckCross
		(
			vector2 fvStart,			/* 直线的开始点。 */
			vector2 fvEnd,				/* 直线的结束点。 */
			const CMapRegion *pcr,			/* 要查找的直线。 */
			FLOAT &fFindx,				/* 找到的交点x。 */
			FLOAT &fFindY,				/* 找到的交点y */
			FLOAT &fFindDis,			/* 找到的直线的距离 */
			int32 &iFindLineIndex			/* 找到的直线的索引 */
		);

	/* 查找两个直线的交点， 并求交点。 */
	BOOL CheckLineCross
		(
			vector2 fv1Start,			/* 直线1的开始点。 */
			vector2 fv1End,				/* 直线1的结束点。 */
			vector2 fv2Start,			/* 直线2的开始点。 */
			vector2 fv2End,				/* 直线2的结束点。 */
			FLOAT &fcrossx,				/* 找到的交点x。 */
			FLOAT &fcrossy				/* 找到的交点y */
		);

	/*
	 * 当前点是否在不可行走区域之内 ;
	 */
	static BOOL				IsPointInUnreachRegion(const vector2 &fvTarget);
	int32					GetUnitNum(void) const								{ return(int32) m_vPosStack.size();}

	/* 取得路径中的某一段，如果nIndex非法，则抛出异常 */
	PathUnit				&GetPathUnit(int32 nIndex);
	const PathUnit			&GetConstPathUnit(int32 nIndex) const;


	// 计算路径
	BOOL					MoveTo(const vector2 fvCurPos , const vector2 fvTargetPos, FLOAT fModifyDist, BOOL bDirectMove);

	const GLPos*		GetFinalPath()		{ return m_posFinalPathNode; }
	uint32					GetFinalPathCount()	{ return m_uFinalPathNodeCount; }

	/* 目标距离偏移 */
	vector2					GetTargetPos(const vector2 &fvCurPos, const vector2 &TargetPos, FLOAT fDist, FLOAT fWarp = 0.5f);
	/* 根据距离修正路点 */
	void					ModifyPathNode(const vector2 &fvCurPos, const vector2 &TargetPos, GLPos *pPathNode, uint32 &uNodeNum, FLOAT fModifyDist);
	/* 修正目标点 */
	BOOL					ModifyTargetPos(const vector2 &fvCur, vector2 &fvTargetOut, FLOAT fModifyDist);

protected:
	std::vector<PathUnit>	m_vPosStack;	/* 关键点的集合，每两个点之间是一条路径单位 */

	GLPos	m_posFinalPathNode[MAX_PATH_NODE_NUM];
	uint32		m_uFinalPathNodeCount;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	static BOOL		CheckCross(vector2 fvmStart, vector2 fvmEnd, const CMapRegion *pcr);
	static BOOL		CheckCross(vector2 fvmStart, vector2 fvmEnd, vector2 fvnStart, vector2 fvnEnd);
	static vector2	fvAdd(vector2 fv1, vector2 fv2);
	static vector2	fvSub(vector2 fv1, vector2 fv2);
	static FLOAT	fvMulti(vector2 fv1, vector2 fv2);
	static BOOL		fvEuqual(vector2 fv1, vector2 fv2);
	static FLOAT	fvDistancePow(vector2 fv1, vector2 fv2);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	struct PassRegionInfo
	{
		vector2 fvRegionPos1;	/* 阻挡边顶点 */
		vector2 fvRegionPos2;
		vector2 fvCrossPos;		/* 交点 */
		vector2 fvVertexNormal; /* 阻挡边的法线 */
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	/* 阻挡偏移位置 */
	BOOL GetRegionOffsetPos
		(
			const vector2	&fvCurrPos,		/* 当前位置 */
			const vector2	&fvCrossPos,	/* 于阻挡边的交点 */
			const vector2 fvRegionPos1,		/* 阻挡边顶点1 */
			const vector2 fvRegionPos2,		/* 阻挡边顶点2 */
			FLOAT fOffsetDist,				/* 偏移距离 */
			vector2 &fvOutPos				/* 返回的偏移位置 */
		);

	/* 是否穿越阻挡 */
	bool IsPassRegion(
		const vector2 &fvCurrPos, 
		const vector2 &fvTargetPos, 
		PassRegionInfo &outRegionData);
};


namespace Ogre
{
	class SceneManager;
	class SceneNode;
} 

class Line3D;
/*
 =======================================================================================================================
    阻挡网格
 =======================================================================================================================
 */
class RegionGrid
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	std::vector<Line3D *>	m_vRegionLine;

	Ogre::SceneManager * m_pSceneMgr;
	Ogre::SceneNode * m_pBaseSceneNode;
	BOOL m_bWindowActive;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	RegionGrid(Ogre::SceneManager * sceneMgr);
	~	RegionGrid();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	void	CreateRenderable();
	void	DestroyRenderable();

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */

	BOOL IsActive(void)
	{
		return m_bWindowActive;
	}

	void	SetActive(BOOL bActive);
};	/* class */
#endif /* _MAP_PATH_H_ */
