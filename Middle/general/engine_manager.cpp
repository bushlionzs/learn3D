#include "OgreHeader.h"
#include "engine_manager.h"
#include "OgreRoot.h"
#include "OgreSceneManager.h"
#include "OgreCamera.h"
#include "OGSkeletonMeshComponentManager.h"
#include "OgreControllerManager.h"
#include "terrain.h"
#include "terrain_info.h"
#include "GameMath.h"
#include "renderSystem.h"
#include "OgreViewport.h"
#include "OGProjector.h"
#include "ResourceParserManager.h"
#include "OGSkeletonMeshComponentManager.h"
#include "OGAdvancedAnimationSystemManager.h"
#include "OGSpellManager.h"
#include "OGImpactManager.h"
#include "skbFileParser.h"
#include "OGBulletFlowSystemManager.h"
#include "OGActorFactoryManager.h"
#include "game_scene_manager.h"

template<> EngineManager* Ogre::Singleton<EngineManager>::msSingleton = 0;

EngineManager::EngineManager()
{
	new Orphigine::SkeletonMeshComponentManager(nullptr);
	mPosition = Ogre::Vector3::ZERO;
	mSceneManager = nullptr;
	mMainCamera = nullptr;
	mTerrain = nullptr;
}

EngineManager::~EngineManager()
{

}

bool EngineManager::initialise()
{
	Ogre::Root::getSingleton().addMovableObjectFactory(new Orphigine::ProjectorFactory);
	new Ogre::Root();
	new Orphigine::ActorFactoryManager;
	new GameSceneManager;
	new Orphigine::AdvancedAnimationSystemManager;

	new Orphigine::SpellManager;
	ResourceParserManager::getSingleton()._initialise();
	ResourceParserManager::getSingleton().registerParser(new Orphigine::ImpactManager);
	ResourceParserManager::getSingleton().registerParser(new SkbfileParser);
	ResourceParserManager::getSingleton().registerParser(Orphigine::SkeletonMeshComponentManager::getSingletonPtr());
	ResourceParserManager::getSingleton().registerParser(Orphigine::AdvancedAnimationSystemManager::getSingletonPtr());
	ResourceParserManager::getSingleton().registerParser(new Orphigine::BulletFlowSystemManager);
	return true;
}

Ogre::Vector3 EngineManager::getMyPosition()
{
	return mPosition;
}

void EngineManager::setMyPosition(Ogre::Vector3& position)
{
	mPosition = position;
}

Ogre::SceneManager* EngineManager::getSceneManager()
{
	if (nullptr == mSceneManager)
	{
		mSceneManager = Ogre::Root::getSingletonPtr()->createSceneManger(std::string("main"));
	}
	return mSceneManager;
}

Ogre::SceneNode* EngineManager::getBaseSceneNode()
{
	if (nullptr == mSceneManager)
	{
		mSceneManager = Ogre::Root::getSingletonPtr()->createSceneManger(MAIN_SCENE_MANAGER);
	}
	return mSceneManager->getRoot();
}

Ogre::Camera* EngineManager::getMainCamera()
{
	if (nullptr == mMainCamera)
	{
		mMainCamera = mSceneManager->createCamera(MAIN_CAMERA);
	}
	
	return mMainCamera;
}

Ogre::Viewport* EngineManager::getMainViewPort()
{
	return mMainViewport;
}

void EngineManager::setViewPort(Ogre::Viewport* vp)
{
	mMainViewport = vp;
}

Terrain* EngineManager::getTerrain()
{
	return mTerrain;
}

void EngineManager::setTerrain(Terrain* pTerrain)
{
	mTerrain = pTerrain;
}

void EngineManager::setCameraPosition(Ogre::Vector3& eyePos)
{
	assert(false);
}

bool EngineManager::getTerrainIntersects(const Ogre::Ray& ray,
	Ogre::Vector3& position, Ogre::Vector3* normal, bool allowOutside) const
{
	return mTerrain->getTerrainInfo()->isRayIntersectGround(ray, position, normal, allowOutside);
}

bool EngineManager::getTerrainIntersects(Real winx, Real winy,
	Ogre::Vector3& position, Ogre::Vector3* normal, bool allowOutside) const
{
	auto vp = mMainViewport;
	float screenX = (winx - vp->getActualLeft()) / vp->getActualWidth();
	float screenY = (winy - vp->getActualTop()) / vp->getActualHeight();
	auto ray = mMainCamera->getCameraToViewportRay(screenX, screenY);
	return getTerrainIntersects(ray, position, normal, allowOutside);
}

Orphigine::Actor* EngineManager::getRegisterObject(Ogre::String& ObjName)
{
	auto itLMO = mObjectMap.find(ObjName);
	if (itLMO != mObjectMap.end())//找到
	{
		return itLMO->second;
	}
	return NULL;
}

bool EngineManager::registerObject(const Ogre::String& ObjName, Orphigine::Actor* pObj)
{
	if (!ObjName.empty() && pObj)
	{
		auto itor = mObjectMap.find(ObjName);
		if (itor != mObjectMap.end())//注册新名字失败
		{
		
			return false;
		}
		else
		{
			mObjectMap.insert(std::make_pair(ObjName, pObj));
			return true;
		}
	}
	else
	{
		return false;
	}
}

void EngineManager::unregisterObject(const Ogre::String& ObjName)
{
	auto itor = mObjectMap.find(ObjName);

	if (itor != mObjectMap.end())
	{
		mObjectMap.erase(itor);
	}
}

bool EngineManager::positionAxisTrans(
	GAME_AXIS_TYPE typeSource,
	const Ogre::Vector3& fvSource,
	GAME_AXIS_TYPE	typeTar,
	Ogre::Vector3& fvTarget,
	bool bTerrainHeight)
{
	auto pTerrainData = mTerrain->getTerrainInfo();

	/* 尚未加载 */
	if (pTerrainData && (pTerrainData->getXGridSize() == 0 || pTerrainData->getZGridSize() == 0))
	{
		pTerrainData = NULL;
	}

	Ogre::Vector3 fvScale = Ogre::Vector3::UNIT_SCALE;

	/* 检查是否是合法的坐标 */
	fvTarget = fvSource;

	if (CGameMath::KLU_IsNan(fvTarget)) /* 无效的不计算 */
	{
		return false;
	}

	if (!axisCheckValid(typeSource, fvSource))
	{
		return false;
	}

	if (typeSource == typeTar)
		return true;

	auto rs = Ogre::Root::getSingleton().getRenderSystem();
	switch (typeSource)
	{
	case GAT_SCENE:
	{
		if (GAT_GAME == typeTar)
		{
			return true;
		}
		else if (GAT_ENGINE == typeTar)
		{
			if (NULL == pTerrainData)
			{
				fvTarget.x = (FLOAT)fvSource.x * fvScale.x;
				fvTarget.y = (FLOAT)fvSource.y * fvScale.y;
				fvTarget.z = (FLOAT)fvSource.z * fvScale.z;
			}
			else
			{
				fvTarget.x = pTerrainData->mFirstGridWorldPos.x + (FLOAT)fvSource.x * pTerrainData->mWorldUnit.x - pTerrainData->mExtraLeft * pTerrainData->mWorldUnit.x;
				fvTarget.y = pTerrainData->mFirstGridWorldPos.y + (FLOAT)fvSource.y * pTerrainData->mWorldUnit.y;
				fvTarget.z = pTerrainData->mFirstGridWorldPos.z + (FLOAT)fvSource.z * pTerrainData->mWorldUnit.z - pTerrainData->mExtraTop * pTerrainData->mWorldUnit.z;
			}

			return true;
		}
		else if (GAT_SCREEN == typeTar)
		{
		}
	}
	break;

	case GAT_GAME:
	{
		if (NULL == pTerrainData)
			return false;

		FLOAT fGfxX = pTerrainData->mFirstGridWorldPos.x + (FLOAT)fvSource.x * pTerrainData->mWorldUnit.x - pTerrainData->mExtraLeft * pTerrainData->mWorldUnit.x;
		FLOAT fGfxZ = pTerrainData->mFirstGridWorldPos.z + (FLOAT)fvSource.z * pTerrainData->mWorldUnit.z - pTerrainData->mExtraTop * pTerrainData->mWorldUnit.z;

		if (GAT_SCENE == typeTar)
		{
			std::pair<Ogre::Real, Ogre::Real> world = pTerrainData->getWorldIndexFromRealGridIndex(fvSource.x - pTerrainData->mExtraLeft, fvSource.z - pTerrainData->mExtraTop);
			Ogre::Real height = pTerrainData->getWorldIndexWorldHeight(world.first, world.second);
			fvTarget.y = (height - pTerrainData->mFirstGridWorldPos.y) / pTerrainData->mWorldUnit.y;
			return true;
		}
		else if (GAT_ENGINE == typeTar)
		{
			/* 取得相地形高度作为Y坐标 */
			fvTarget.x = fGfxX;
			fvTarget.z = fGfxZ;

			if (bTerrainHeight)
			{
				std::pair<Ogre::Real, Ogre::Real> world = pTerrainData->getWorldIndexFromRealGridIndex(fvSource.x - pTerrainData->mExtraLeft, fvSource.z - pTerrainData->mExtraTop);
				fvTarget.y = pTerrainData->getWorldIndexWorldHeight(world.first, world.second);
			}
			else
			{
				fvTarget.y = pTerrainData->mFirstGridWorldPos.y + (FLOAT)fvSource.y * pTerrainData->mWorldUnit.y;
			}
			return true;
		}
		else if (GAT_SCREEN == typeTar)
		{

		}
	}
	break;

	case GAT_ENGINE:
	{
		if (GAT_SCENE == typeTar || GAT_GAME == typeTar)
		{

			if (pTerrainData)
			{
				fvTarget.x = (fvSource.x - pTerrainData->mFirstGridWorldPos.x) / pTerrainData->mWorldUnit.x + pTerrainData->mExtraLeft;
				fvTarget.y = (fvSource.y - pTerrainData->mFirstGridWorldPos.y) / pTerrainData->mWorldUnit.y;
				fvTarget.z = (fvSource.z - pTerrainData->mFirstGridWorldPos.z) / pTerrainData->mWorldUnit.z + pTerrainData->mExtraTop;
			}
			else
			{
				fvTarget.x = (fvSource.x) / fvScale.x;
				fvTarget.y = (fvSource.y) / fvScale.y;
				fvTarget.z = (fvSource.z) / fvScale.z;
			}

			return true;
		}
		else if (GAT_SCREEN == typeTar)
		{
			if (NULL == pTerrainData)
				return false;

			Ogre::Camera* pOgreCamera = getMainCamera();

			if (!(pOgreCamera->isVisible(fvSource)))
			{
				return false;
			}

			/* x:[-1w, 1w] z:[-1h, 1h] */
			Ogre::Vector3	vRet = pOgreCamera->getProjectMatrix() * 
				pOgreCamera->getViewMatrix() * fvSource;
			int32_t nWidth = rs->_getViewport()->getActualWidth();
			int32_t nHeight = rs->_getViewport()->getActualHeight();

			fvTarget.x = ((vRet.x + 1.0f) * nWidth / 2.0f);
			fvTarget.y = ((-vRet.y + 1.0f) * nHeight / 2.0f);

			return true;
		}
	}
	break;

	case GAT_SCREEN:
	{
		if (!pTerrainData)
		{
			return false;
		}
		Ogre::Vector3	vRenderPos;
		bool bRet = getTerrainIntersects(fvSource.x, fvSource.y, vRenderPos);

		if (!bRet)
		{
			return false;
		}


		if (GAT_SCENE == typeTar || GAT_GAME == typeTar)
		{
			return positionAxisTrans(GAT_ENGINE, Ogre::Vector3(vRenderPos.x, vRenderPos.y, vRenderPos.z), GAT_SCENE, fvTarget);
		}
		else if (GAT_ENGINE == typeTar)
		{
			fvTarget = Ogre::Vector3(vRenderPos.x, vRenderPos.y, vRenderPos.z);
			return true;
		}
	}
	break;
	}

	return false;
}

bool EngineManager::axisCheckValid(GAME_AXIS_TYPE typeSource, const Ogre::Vector3& fvAxis)
{
	auto pTerrainData = mTerrain->getTerrainInfo();

	/* 尚未加载 */
	if (pTerrainData && (pTerrainData->getXGridSize() == 0 || pTerrainData->getZGridSize() == 0))
	{
		pTerrainData = 0;
	}

	switch (typeSource)
	{
	case GAT_SCENE:
	case GAT_GAME:
	{
		if (pTerrainData)
			return pTerrainData->isValidGridIndex((int32_t)fvAxis.x, (int32_t)fvAxis.z);
		else
			return TRUE;
	}
	break;

	case GAT_ENGINE:
	{
		if (pTerrainData)
			return pTerrainData->isValidWorldIndex(fvAxis.x, fvAxis.z);
		else
			return TRUE;
	}
	break;

	case GAT_SCREEN:
	{
		auto rs = Ogre::Root::getSingleton().getRenderSystem();

		auto vp = rs->_getViewport();
		auto rect = vp->getActualDimensions();

		POINT pt;

		pt.x = (int32_t)fvAxis.x;
		pt.y = (int32_t)fvAxis.y;

		RECT rt;
		rt.left = rect.left;
		rt.right = rect.right;
		rt.top = rect.top;
		rt.bottom = rect.bottom;
		return(PtInRect(&rt, pt) == TRUE);
	}
	break;

	default:
		return FALSE;
	}

	return FALSE;
}
