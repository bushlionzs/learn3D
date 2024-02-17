#include "stdafx.h"
#include "KObjectManager.h"
#include "kplayer.h"
#include "KNpc.h"
#include "engine_manager.h"
#include "game_scene_manager.h"
#include "game_scene.h"
#include "OgreSceneQuery.h"
#include "GameEntity.h"
#include "OGActorProxy.h"

template<>
KObjectManager* GameSingleton<KObjectManager>::m_sSingleton = NULL;

KObjectManager::KObjectManager()
{
	mPlayer = nullptr;
	mSceneQuery = EngineManager::getSingleton().getSceneManager()->createRayQuery(Ogre::Ray());
	mSceneQuery->setSortByDistance(true);
}

KObjectManager::~KObjectManager()
{

}

KObject* KObjectManager::createPlayer(int64_t id)
{
	auto player = new KPlayer();
	addObject(id, player);
	player->initialize();
	mPlayer = player;
	mPlayer->setId(id);
	
	return player;
}

KObject* KObjectManager::createNPC(int64_t id)
{
	auto npc = new KNpc;
	addObject(id, npc);
	npc->initialize();
	npc->setId(id);

	return npc;
}

KObject* KObjectManager::createItem(int64_t id)
{
	return nullptr;
}

KObject* KObjectManager::getObject(int64_t id)
{
	auto itor = mObjectMap.find(id);
	if (itor != mObjectMap.end())
	{
		return itor->second;
	}

	return nullptr;
}

KPlayer* KObjectManager::getMySelf()
{
	return (KPlayer*)mPlayer;
}

void KObjectManager::update(float delta)
{
	for (auto& pair : mObjectMap)
	{
		pair.second->update(delta);
	}
}

KObject* KObjectManager::GetMouseOverObject(int32 nX, int32 nY, Ogre::Vector3& fvMouseHitPlan)
{
	
	BOOL bIsHitObj = TRUE;

	// 根据屏幕上的坐标取得3D世界中的坐标

	POINT pt;
	pt.x = nX;
	pt.y = nY;

	Ogre::Vector3 fvSource((FLOAT)pt.x, (FLOAT)pt.y, 0.0f);
	if (FALSE == EngineManager::getSingleton().positionAxisTrans(GAT_SCREEN, fvSource, GAT_GAME, fvMouseHitPlan))
	{
		// 与世界没有相交的物体
		bIsHitObj = FALSE;
	}

	// 取得鼠标射线
	Ogre::Ray rayScreen;
	EngineManager::getSingleton().getMainCamera()->getCameraToViewportRay(nX, nY, &rayScreen);

	GameScene* pMap = (GameScene*)GameSceneManager::getSingleton().GetActiveScene();
	if (pMap == nullptr)
	{
		return nullptr;
	}
	//和行走面相交
	Ogre::Vector3 fvBuilding;
	BOOL bInBuilding = pMap->getCollision().IsIntersection(
		rayScreen.getOrigin().x, rayScreen.getOrigin().y, rayScreen.getOrigin().z,
		rayScreen.getDirection().x, rayScreen.getDirection().y, rayScreen.getDirection().z,
		(int32)fvMouseHitPlan.x, (int32)fvMouseHitPlan.z,
		fvBuilding.x, fvBuilding.y, fvBuilding.z);

	if (bInBuilding)
	{
		if ((rayScreen.getOrigin() - fvMouseHitPlan).squaredLength() > (rayScreen.getOrigin() - fvBuilding).squaredLength())
			fvMouseHitPlan = fvBuilding;

		bIsHitObj = TRUE;
	}

	// 与世界没有相交的物体
	if (FALSE == bIsHitObj)
		return NULL;


	// 查找鼠标接触物体
	static int32 s_nLastHitObj = INVALID_ID;

	KObject* pHitObject = Find_HitOrphigineObject(pt.x, pt.y);
	

	int32 nHitObjID = INVALID_ID;

	if (pHitObject)
	{
		nHitObjID = pHitObject->getId();
	}

	if (s_nLastHitObj != nHitObjID)
	{
		// 设定选择
		if (pHitObject)
		{
			
		}

		// 取消选择
		KObject* pLastHitObj = (KObject*)getObject(s_nLastHitObj);
		if (pLastHitObj)
		{
			
		}
		s_nLastHitObj = nHitObjID;
	}
	return pHitObject;
}


KObject* KObjectManager::Find_HitOrphigineObject(int32 nX, int32 nY)
{
	Ogre::Ray	ray = EngineManager::getSingleton().getMainCamera()->getCameraToViewportRay(nX, nY);
	mSceneQuery->setRay(ray);
	const Ogre::RaySceneQueryResult& queryResult = mSceneQuery->execute();
	std::map<int32, KObject*>	mapRayQuery;
	for (Ogre::RaySceneQueryResult::const_iterator it = queryResult.begin(); it != queryResult.end(); ++it)
	{
	    Ogre:MoveObject* pMovable = it->movable;

		Orphigine::ActorPtr	object = Orphigine::getObjectFromMovable(pMovable);

		if (object && object->getData())
		{
			GameEntity* pEntityNode = (GameEntity*)(object->getData());

			/* 不是游戏逻辑中动态生成的 */
			if (!pEntityNode) continue;

			/* 不再被关心 */
			if (!(pEntityNode->GetRayQuery())) continue;

			KObject* pObject = pEntityNode->getOwner();
			if (pObject->getObjectType() == ObjectType_Npc)
			{
				Orphigine::SkeletonMeshActor* logicModelObject = static_cast<Orphigine::SkeletonMeshActor*>(object.get());


				Orphigine::SkeletonMeshComponent* model = logicModelObject->getLogicModel();


				/* 不再自定义BoundingBox中 */
				if (model->isUseExternalBoundingBox() && !(model->rayIntersect(ray)))
				{
					continue;
				}
			}

			/* 如果已经有同级存在，按照摄像机远近排序 */
			if (mapRayQuery.find(pEntityNode->GetRayQueryLevel()) != mapRayQuery.end()) continue;

			/* 放入查询队列 */
			mapRayQuery.insert(std::make_pair(pEntityNode->GetRayQueryLevel(), pObject));
		}
	}

	/* 返回优先级最高的逻辑对象 */
	if (!mapRayQuery.empty())
	{
		return mapRayQuery.begin()->second;
	}
	return nullptr;
}

bool KObjectManager::addObject(int64_t id, KObject* obj)
{
	auto itor = mObjectMap.insert(std::pair<int64_t, KObject*>(id, obj));
	assert(itor.second);
	return itor.second;
}