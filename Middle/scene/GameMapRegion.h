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
	struct VisibilityPoints /* ���ӵ�ṹ */
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
	 * �õ�һ����������,���������㲻�ڶ������,����-1
	 */
	int32				GetIndex(const Ogre::Vector2*pfvPoint) const;

	/* �õ����ڵ�͹�� */
	int32				GetNeighborBulgeIndex(int32 nIndex, BOOL bCountSelf, BOOL bClockwise) const;
	int32				GetNeighborBulgeIndex(const Ogre::Vector2*pfvPoint, BOOL bCountSelf, BOOL bClockwise) const;
	const Ogre::Vector2*GetNeighborBulge(int32 nIndex, BOOL bCountSelf, BOOL bClockwise) const;
	const Ogre::Vector2*GetNeighborBulge(const Ogre::Vector2*pfvPoint, BOOL bCountSelf, BOOL bClockwise) const;

	/* �����nStart�㵽nEnd���Ʊ߾����ľ��� */
	FLOAT			GetDistanceSq(int32 nStart, int32 nEnd, BOOL bClockwise, BOOL bOnlyBugle) const;

	const Ogre::Vector2*GetPoint(int32 nIndex, BOOL bLoop) const;
	const Ogre::Vector2*GetPoint(int32 nIndex) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	int32 m_ID;			/* IDӦ��û��Ҫ���ļ��ж��� */
	int32 m_nCount;
	bool m_bDynamic;	/* �Ƿ�Ϊ��̬�� */

	/* ����Щ������һ���������»���ʧ���� */
	std::vector<VisibilityPoints> m_vfPoints;
	std::vector<BOOL> m_vbBulge;
};						/* class */
#endif /* __REGION_H__ */
