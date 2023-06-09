#include "OgreHeader.h"
#include "GameMapCollisionManager.h"
#include <limits>
#include "engine_manager.h"
#include "KDefine.h"

const int32_t	BUILD_COLLISION_SEARCH_RANGE = 30;

/*
 =======================================================================================================================
 =======================================================================================================================
 */

CMapCollisionManager::CMapCollisionManager(void) :
	m_physicsWorld(NULL)
{
	/*if (Orphigine::PhysicsManager::getSingletonPtr() == nullptr)
	{
		new Orphigine::PhysicsManager;
		new Orphigine::PhyCookedTriangleMeshManager;
	}
	m_physicsWorld = Orphigine::PhysicsManager::getSingleton().getWorld();*/
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CMapCollisionManager::~CMapCollisionManager(void)
{
	m_physicsWorld = NULL;
}


uint32 CMapCollisionManager::LoadCollisionTriInfoFromFile(const char *szFileName)
{
	return 0;
}

BOOL CMapCollisionManager::Get3DMapHeight(FLOAT fx, FLOAT fy, FLOAT fz, FLOAT &outY)
{
	BOOL hasIntersection = FALSE;
	vector3 fvAtTerrain;


	EngineManager::getSingleton().positionAxisTrans(GAT_SCENE, vector3(fx, fy, fz), GAT_ENGINE, fvAtTerrain);


	Ogre::Vector3 tmpStart		= Ogre::Vector3(fvAtTerrain.x, fvAtTerrain.y + 20000.0f, fvAtTerrain.z);
	Ogre::Vector3 tmpDir		= Ogre::Vector3(-0.0001f, -30000.0f, -0.0001f);
	Ogre::Vector3 tmpResultPos	= Ogre::Vector3(0.0f, 0.0f, 0.0f);


	hasIntersection = true;
		


	vector3	resultPosGameCoord;
	EngineManager::getSingleton().positionAxisTrans(GAT_ENGINE,vector3(tmpResultPos.x, tmpResultPos.y, tmpResultPos.z),GAT_SCENE,	resultPosGameCoord);
	outY = resultPosGameCoord.y;

	return hasIntersection;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CMapCollisionManager::GetMapHeight(FLOAT fx, FLOAT fz, FLOAT &outY)
{
	vector3 fvAtTerrain;

	EngineManager().getSingleton().positionAxisTrans(GAT_GAME, vector3(fx, 0.0f, fz), GAT_ENGINE, fvAtTerrain);

	Ogre::Vector3	tmpStart = Ogre::Vector3(fvAtTerrain.x, 20000.0f, fvAtTerrain.z);
	Ogre::Vector3	tmpDir = Ogre::Vector3(-0.0001f, -30000.0f, -0.0001f);
	Ogre::Vector3	tmpResultPos = Ogre::Vector3(0.0f, 0.0f, 0.0f);
	vector3			resultPosGameCoord;

	EngineManager().getSingleton().positionAxisTrans
		(
			GAT_ENGINE,
			vector3(tmpResultPos.x, tmpResultPos.y, tmpResultPos.z),
			GAT_SCENE,
			resultPosGameCoord
		);

	outY = resultPosGameCoord.y;

	return true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CMapCollisionManager::IsIntersection
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
)
{
	vector3 rayOrigin;

	EngineManager().getSingleton().positionAxisTrans(GAT_SCENE, vector3(fOrigx, fOrigy, fOrigz), GAT_ENGINE, rayOrigin);

	vector3	tmpStart = rayOrigin;
	vector3	tmpDir = Ogre::Vector3(fDirx, fDiry, fDirz) * 30000.0f;
	vector3	tmpResultPos = Ogre::Vector3(0.0f, 0.0f, 0.0f);
	bool			hasIntersection = true;
	vector3			resultPosGameCoord;

	EngineManager().getSingleton().positionAxisTrans
		(
			GAT_ENGINE,
			vector3(tmpResultPos.x, tmpResultPos.y, tmpResultPos.z),
			GAT_SCENE,
			resultPosGameCoord
		);

	fPosx = resultPosGameCoord.x;
	fPosy = resultPosGameCoord.y;
	fPosz = resultPosGameCoord.z;

	return hasIntersection;
}
