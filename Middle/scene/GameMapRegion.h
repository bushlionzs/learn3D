#ifndef __REGION_H__
#define __REGION_H__

class	KEntityBase;

class	CMapRegion
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	struct VisibilityPoints /* 可视点结构 */
	{
		Ogre::Vector2									m_position;
		int32										m_belongRegionID;
		std::vector<const VisibilityPoints *>	m_visibilityPointsList;
	};

	CMapRegion(void);
	~				CMapRegion(void);

	BOOL			AddPoint(const VisibilityPoints *pfvPoint);
	BOOL			IsBulge		(int32 nIndex) const;
	BOOL			JudgeBulge		(int32 nIndex);
	void			JudgeAllBulge	(void);

	/*
	 * 得到一个顶点的序号,如果这个顶点不在多边形上,返回-1
	 */
	int32				GetIndex(const Ogre::Vector2*pfvPoint) const;

	/* 得到相邻的凸点 */
	int32				GetNeighborBulgeIndex(int32 nIndex, BOOL bCountSelf, BOOL bClockwise) const;
	int32				GetNeighborBulgeIndex(const Ogre::Vector2*pfvPoint, BOOL bCountSelf, BOOL bClockwise) const;
	const Ogre::Vector2*GetNeighborBulge(int32 nIndex, BOOL bCountSelf, BOOL bClockwise) const;
	const Ogre::Vector2*GetNeighborBulge(const Ogre::Vector2*pfvPoint, BOOL bCountSelf, BOOL bClockwise) const;

	/* 计算从nStart点到nEnd点绕边经过的距离 */
	FLOAT			GetDistanceSq(int32 nStart, int32 nEnd, BOOL bClockwise, BOOL bOnlyBugle) const;

	const Ogre::Vector2*GetPoint(int32 nIndex, BOOL bLoop) const;
	const Ogre::Vector2*GetPoint(int32 nIndex) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	int32 m_ID;			/* ID应该没必要从文件中读入 */
	int32 m_nCount;
	bool m_bDynamic;	/* 是否为动态的 */

	/* （有些区域在一定的条件下会消失掉） */
	std::vector<VisibilityPoints> m_vfPoints;
	std::vector<BOOL> m_vbBulge;
};						/* class */
#endif /* __REGION_H__ */
