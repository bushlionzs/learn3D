
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
		Ogre::Vector2 fvStart;				/* ��ʼ�� */
		Ogre::Vector2 fvTarget;				/* Ŀ��� */
	};

	/* ����ӿ�ʼ�㵽�������·���� */
	BOOL CreateMovePath(const Ogre::Vector2&fvCurrent, const Ogre::Vector2&fvTarget);

	/* ֱ�Ӳ���Ŀ�ĵء� */
	BOOL GetPathDirect(
		const Ogre::Vector2&fvCurrent,
		const Ogre::Vector2&fvTarget,
		BOOL bOffset = FALSE, 
		FLOAT fMinDist = 1.5f);

	/* ���ҵ�ǰ��ֱ����һ�������Ƿ��ཻ������ཻ���ؽ��������������ֱཻ�ߵ�����ֵ */
	BOOL CheckCross
		(
			Ogre::Vector2 fvStart,			/* ֱ�ߵĿ�ʼ�㡣 */
			Ogre::Vector2 fvEnd,				/* ֱ�ߵĽ����㡣 */
			const CMapRegion *pcr,			/* Ҫ���ҵ�ֱ�ߡ� */
			FLOAT &fFindx,				/* �ҵ��Ľ���x�� */
			FLOAT &fFindY,				/* �ҵ��Ľ���y */
			FLOAT &fFindDis,			/* �ҵ���ֱ�ߵľ��� */
			int32 &iFindLineIndex			/* �ҵ���ֱ�ߵ����� */
		);

	/* ��������ֱ�ߵĽ��㣬 ���󽻵㡣 */
	BOOL CheckLineCross
		(
			Ogre::Vector2 fv1Start,			/* ֱ��1�Ŀ�ʼ�㡣 */
			Ogre::Vector2 fv1End,				/* ֱ��1�Ľ����㡣 */
			Ogre::Vector2 fv2Start,			/* ֱ��2�Ŀ�ʼ�㡣 */
			Ogre::Vector2 fv2End,				/* ֱ��2�Ľ����㡣 */
			FLOAT &fcrossx,				/* �ҵ��Ľ���x�� */
			FLOAT &fcrossy				/* �ҵ��Ľ���y */
		);

	/*
	 * ��ǰ���Ƿ��ڲ�����������֮�� ;
	 */
	static BOOL				IsPointInUnreachRegion(const Ogre::Vector2&fvTarget);
	int32					GetUnitNum(void) const								{ return(int32) m_vPosStack.size();}

	/* ȡ��·���е�ĳһ�Σ����nIndex�Ƿ������׳��쳣 */
	PathUnit				&GetPathUnit(int32 nIndex);
	const PathUnit			&GetConstPathUnit(int32 nIndex) const;


	// ����·��
	BOOL					MoveTo(
		const Ogre::Vector2 fvCurPos , 
		const Ogre::Vector2 fvTargetPos, 
		FLOAT fModifyDist, 
		BOOL bDirectMove);

	const GLPos*		GetFinalPath()		{ return m_posFinalPathNode; }
	uint32					GetFinalPathCount()	{ return m_uFinalPathNodeCount; }

	/* Ŀ�����ƫ�� */
	Ogre::Vector2 GetTargetPos(
		const Ogre::Vector2&fvCurPos,
		const Ogre::Vector2&TargetPos,
		FLOAT fDist, 
		FLOAT fWarp = 0.5f);
	/* ���ݾ�������·�� */
	void					ModifyPathNode(
		const Ogre::Vector2&fvCurPos,
		const Ogre::Vector2&TargetPos,
		GLPos *pPathNode, 
		uint32 &uNodeNum, FLOAT fModifyDist);
	/* ����Ŀ��� */
	BOOL ModifyTargetPos(
		const Ogre::Vector2&fvCur, Ogre::Vector2&fvTargetOut, FLOAT fModifyDist);

protected:
	std::vector<PathUnit>	m_vPosStack;	/* �ؼ���ļ��ϣ�ÿ������֮����һ��·����λ */

	GLPos	m_posFinalPathNode[MAX_PATH_NODE_NUM];
	uint32		m_uFinalPathNodeCount;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	static BOOL		CheckCross(
		Ogre::Vector2 fvmStart, Ogre::Vector2 fvmEnd, const CMapRegion *pcr);
	static BOOL		CheckCross(
		Ogre::Vector2 fvmStart, 
		Ogre::Vector2 fvmEnd, 
		Ogre::Vector2 fvnStart, 
		Ogre::Vector2 fvnEnd);
	static Ogre::Vector2	fvAdd(Ogre::Vector2 fv1, Ogre::Vector2 fv2);
	static Ogre::Vector2	fvSub(Ogre::Vector2 fv1, Ogre::Vector2 fv2);
	static FLOAT	fvMulti(Ogre::Vector2 fv1, Ogre::Vector2 fv2);
	static BOOL		fvEuqual(Ogre::Vector2 fv1, Ogre::Vector2 fv2);
	static FLOAT	fvDistancePow(Ogre::Vector2 fv1, Ogre::Vector2 fv2);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	struct PassRegionInfo
	{
		Ogre::Vector2 fvRegionPos1;	/* �赲�߶��� */
		Ogre::Vector2 fvRegionPos2;
		Ogre::Vector2 fvCrossPos;		/* ���� */
		Ogre::Vector2 fvVertexNormal; /* �赲�ߵķ��� */
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	/* �赲ƫ��λ�� */
	BOOL GetRegionOffsetPos
		(
			const Ogre::Vector2&fvCurrPos,		/* ��ǰλ�� */
			const Ogre::Vector2&fvCrossPos,	/* ���赲�ߵĽ��� */
			const Ogre::Vector2 fvRegionPos1,		/* �赲�߶���1 */
			const Ogre::Vector2 fvRegionPos2,		/* �赲�߶���2 */
			FLOAT fOffsetDist,				/* ƫ�ƾ��� */
			Ogre::Vector2&fvOutPos				/* ���ص�ƫ��λ�� */
		);

	/* �Ƿ�Խ�赲 */
	bool IsPassRegion(
		const Ogre::Vector2&fvCurrPos,
		const Ogre::Vector2&fvTargetPos,
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
    �赲����
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
