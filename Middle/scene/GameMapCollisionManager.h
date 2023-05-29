#ifndef _MAP_COLLISION_MANAGER_H_
#define _MAP_COLLISION_MANAGER_H_

namespace	Orphigine
{
class	PhyWorld;
}
class	CMapCollisionManager
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	CMapCollisionManager(void);
	~CMapCollisionManager(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	/* 从行走面数据文件中读取数据。 参数：行走面数据文件， 包含路径。 */
	uint32	LoadCollisionTriInfoFromFile(const char *szFileName);

	/*
	 * 通过传入的 平面fx, fz位置得到高度。 参数1： FLOAT fx 游戏逻辑坐标。 参数2：
	 * FLOAT fz 游戏逻辑坐标。 参数3： FLOAT& fy 游戏逻辑坐标 返回的高度。 return： 1
	 * － 成功， fy有意义。 0 － 失败， fy无意义， 表明此处无碰撞数据。
	 */
	BOOL	Get3DMapHeight(FLOAT fx, FLOAT fy, FLOAT fz, FLOAT &outY);

	BOOL	GetMapHeight(FLOAT fx, FLOAT fz, FLOAT &outY);

	/*
	 * 通过传入的 平面fx, fz位置得到高度。 参数1： FLOAT fx 游戏逻辑坐标。 参数2：
	 * FLOAT fz 游戏逻辑坐标。 参数3： FLOAT& fy 游戏逻辑坐标 返回的高度。 return： 1
	 * － 成功， fy有意义。 0 － 失败， fy无意义， 表明此处无碰撞数据。
	 */
	BOOL	IsIntersection
			(
				FLOAT	fOrigx,
				FLOAT	fOrigy,
				FLOAT	fOrigz, /* 射线的原点。 */
				FLOAT	fDirx,
				FLOAT	fDiry,
				FLOAT	fDirz,	/* 射线的方向。 */
				int32		ix,
				int32		iz,		/* 选中地图的位置 */
				FLOAT	&fPosx,
				FLOAT	&fPosy,
				FLOAT	&fPosz	/* 返回建筑物的行走面位置。 */
			);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	Orphigine::PhyWorld * m_physicsWorld;
};

/* class */
#endif /* _MAP_COLLISION_MANAGER_H_ */
