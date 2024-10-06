#include "OgreHeader.h"
#include "game_scene.h"
#include "OgreDataStream.h"
#include "OgreResourceManager.h"
#include "terrain.h"
#include "scene_serializer.h"
#include "game_scene_data.h"
#include "OgreMeshManager.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "renderSystem.h"
#include "engine_manager.h"
#include "GameTableData.h"
#include "myutils.h"
#include "GameMapRegion.h"
#include "OGNavigateRegion.h"
#include "OGNavigateSpace.h"
#include "GameMapZone.h"
#include "OGPhyCollectionSerializer.h"

GameScene::GameScene(const _TABLE_SCENE_DEFINE* define)
{
	mSceneDefine = define;
	mTerrain = std::make_unique<Terrain>();

	mActors.reserve(2000);

	m_neSpace = nullptr;
	m_neSDK = Orphigine::NeCreateSDK();
}

GameScene::~GameScene()
{

}

bool GameScene::load()
{
	m_neSpace = m_neSDK->createSpace();
	m_nZoneXSize = mSceneDefine->nXSize / SIZE_OF_ZONE;

	if (m_nZoneXSize * SIZE_OF_ZONE < mSceneDefine->nXSize)
		m_nZoneXSize++;

	m_nZoneZSize = mSceneDefine->nZSize / SIZE_OF_ZONE;
	if (m_nZoneZSize * SIZE_OF_ZONE < mSceneDefine->nZSize)
		m_nZoneZSize++;

	mZoneBuf.resize(m_nZoneXSize * m_nZoneZSize);

	for (int32 i = 0; i < (int32)mZoneBuf.size(); i++)
	{
		auto& theZone = mZoneBuf[i];

		/* 网格初始化 */
		theZone.Initialize(NULL);
	}

	String	strSceneName = mSceneDefine->szSceneName;

	String baseName = removeSuffix(strSceneName);

	String strRegion = baseName + ".region";

	loadRegionBinary(strRegion.c_str());

	String	strPov = baseName + ".pov";
	loadPOVBinary(strPov.c_str());



	Orphigine::PhyCollectionSerializer physicsSerializer;
	String phyName = baseName + ".phy";
	Ogre::DataStreamPtr	phyDataStream = Ogre::ResourceManager::getSingleton().openResource(phyName);
	Orphigine::PhyCollection phyiscsCollection;
	physicsSerializer.importPhyCollection(phyDataStream, &phyiscsCollection);
	phyiscsCollection.instantiate();

	SceneSerializer serializer;
	std::shared_ptr<DataStream> stream = ResourceManager::getSingletonPtr()->openResource(strSceneName);
	serializer.import(stream, this);

	stream = ResourceManager::getSingletonPtr()->openResource(mTerrainFilename);

	mTerrain->load(stream);

	loadImpl();

	

	return true;
}

void GameScene::loadPOVBinary(LPCTSTR szPOVFile)
{
	if (!szPOVFile || szPOVFile[0] == '\0') return;
	if (!m_neSpace) return;

	const char* lpAddress = NULL;

	auto stream = ResourceManager::getSingleton().openResource(szPOVFile);

	DWORD	dwSize = stream->getStreamLength();

	lpAddress = stream->getStreamData();

	if (dwSize > 0)
	{
		const char* pPoint = lpAddress;

		/* 遍历每个Region */
		for (int32 i = 0; i < m_neSpace->getNumRegions(); i++)
		{
			Orphigine::NeRegion* tmpRegion = m_neSpace->getRegionByIndex(i);

			/* 遍历每个Region中的可视点 */
			for (int32 j = 0; j < tmpRegion->getNumPointsOfVisibility(); j++)
			{
				Orphigine::NeVisibilityPoints* tmpCurrentPOV = tmpRegion->getPointOfVisibility(j);

				int32 tmpNumLinkedPOV;

				memcpy(&tmpNumLinkedPOV, pPoint, sizeof(int32));
				pPoint += sizeof(int32);

				/* 遍历每个连接点 */
				for (int32 m = 0; m < tmpNumLinkedPOV; m++)
				{
					int32 tmpBelongRegionID;

					memcpy(&tmpBelongRegionID, pPoint, sizeof(int32));
					pPoint += sizeof(int32);

					int32 tmpLinkingPOVID;

					memcpy(&tmpLinkingPOVID, pPoint, sizeof(int32));
					pPoint += sizeof(int32);

					Orphigine::NeRegion* tmpTargetRegion = m_neSpace->getRegionByID(tmpBelongRegionID);

					const Orphigine::NeVisibilityPoints* tmpLinkingPOV = tmpTargetRegion->getPointOfVisibility(tmpLinkingPOVID);

					tmpCurrentPOV->m_visibilityPointsList.push_back(tmpLinkingPOV);
				}
			}
		}

	}
}


void GameScene::loadRegionBinary(LPCTSTR szRegionFile)
{
	if (!szRegionFile || szRegionFile[0] == '\0') return;
	if (!m_neSpace) return;


	mRegionList.clear();

	const char* lpAddress = NULL;
	auto stream = ResourceManager::getSingleton().openResource(szRegionFile);

	DWORD	dwSize = stream->getStreamLength();

	lpAddress = stream->getStreamData();

	if (dwSize > 0)
	{
		const char* pPoint = lpAddress;
		int32								iRegionCount = 0;
		int32								iPointCount = 0;
		int32								iId = 0;
		int32								RegionId = 0;
		FLOAT							fTemp = 0;
		Ogre::Vector2							fvp;
		CMapRegion::VisibilityPoints		tmpPointofVisibility;
		Orphigine::NeVisibilityPoints	tmpPOV;

		/* 文件版本 */
		int32	iVerLen = (int32)sizeof("REGION_EDIT_01");

		pPoint += iVerLen - 1;

		/* 读取区域的个数 */
		memcpy(&iRegionCount, pPoint, sizeof(iRegionCount));
		pPoint += sizeof(iRegionCount);

		unsigned int	globalHandle = 0;

		for (int32 i = 0; i < iRegionCount; i++)
		{
			/* 读取区域的id */
			memcpy(&(iId), pPoint, sizeof(iId));
			pPoint += sizeof(iId);

			CMapRegion* cr = new CMapRegion();

			Orphigine::NeRegion* tmpRegion = m_neSpace->createRegion(iId);

			cr->m_ID = (int32)iId;

			/* 读取区域的Flag */
			int32 iFlag;

			memcpy(&(iFlag), pPoint, sizeof(iFlag));

			/* 设置是否动态 */
			cr->m_bDynamic = (iFlag & 0x2) ? true : false;	/* 判断其第31位, 标识是否可以动态移除 */
			pPoint += sizeof(int32);

			/* 读取点的个数. */
			memcpy(&iPointCount, pPoint, sizeof(iPointCount));
			pPoint += sizeof(iPointCount);

			for (int32 k = 0; k < iPointCount; k++)
			{
				/* 读取x， z 数据 */
				memcpy(&fvp.x, pPoint, sizeof(fvp.x));
				pPoint += sizeof(fvp.x);
				memcpy(&fvp.y, pPoint, sizeof(fvp.y));
				pPoint += sizeof(fvp.y);
				memcpy(&fTemp, pPoint, sizeof(fTemp));
				pPoint += sizeof(fTemp);

				tmpPointofVisibility.m_position = fvp;
				tmpPointofVisibility.m_belongRegionID = cr->m_ID;
				cr->AddPoint(&tmpPointofVisibility);

				Orphigine::NeVector3	tmpVP = Orphigine::NeVector3(fvp.x, 0.0f, fvp.y);

				tmpRegion->addPointOfVisibility(tmpVP);

				globalHandle++;
			}

			tmpRegion->updateAABB();
			tmpRegion->computeSurfaceNormal();
			tmpRegion->computeVerticesNormal();
			tmpRegion->computeConvexVertices();

			/*
			 * tmpRegion->extending(1.3f);
			 */
			mRegionList.push_back(cr);
		}

	}

	/* 将Region注册到Zone */
	registeAllRegion();
}

void GameScene::registeAllRegion(void)
{
	Ogre::Vector2	sp, ep;
	int32_t sGridX = 0, sGridZ = 0, eGridX = 0, eGridZ = 0;
	FLOAT div = 0, dividend = 0;
	int32_t	tempint0;
	FLOAT fb, fk;

	/* 所有多边形 */
	std::vector<CMapRegion*>::iterator	itCRegion;

	for (itCRegion = mRegionList.begin(); itCRegion != mRegionList.end(); itCRegion++)
	{
		CMapRegion* pCRegion = *itCRegion;

		/* 所有边 */
		for (int32 i = 0; i < (int32)(pCRegion->m_vfPoints.size()); i++)
		{
			/* 起点和终点 */
			sp = pCRegion->m_vfPoints[i].m_position;
			ep = pCRegion->m_vfPoints[(i + 1) % (int32)(pCRegion->m_vfPoints.size())].m_position;

			sGridX = GetZoneX(sp.x);
			eGridX = GetZoneX(ep.x);
			sGridZ = GetZoneZ(sp.y);
			eGridZ = GetZoneZ(ep.y);

			if (sGridZ == eGridZ)
			{
				/* Zone水平的情况,在同一Zone内必然是同一水平ZONE */
				for (tempint0 = std::min(sGridX, eGridX); tempint0 <= std::max(sGridX, eGridX); tempint0++)
				{
					CMapZone* pcz;

					pcz = GetZone(tempint0, sGridZ);
					if (pcz != NULL)
					{
						pcz->AddRegion(pCRegion->m_ID);
					}
				}
			}
			else if (sGridX == eGridX)
			{
				/* Zone垂直的情况 */
				for (tempint0 = std::min(sGridZ, eGridZ); tempint0 <= std::max(sGridZ, eGridZ); tempint0++)
				{
					CMapZone* pcz;

					pcz = GetZone(sGridX, tempint0);
					if (pcz != NULL)
					{
						pcz->AddRegion(pCRegion->m_ID);
					}
				}
			}
			else
			{
				/*
				 * 斜边的情况,用区域内的网格切割多边形边 ;
				 * 计算斜率和位移
				 */
				fk = (sp.y - ep.y) / (sp.x - ep.x);
				fb = ep.y - ep.x * fk;
				for (tempint0 = std::min(sGridZ, eGridZ) + 1; tempint0 <= std::max(sGridZ, eGridZ); tempint0++)
				{
					/* 计算多边形边同垂直切线的交点,将切点上下的两个zone注册 */
					FLOAT cross = (tempint0 * SIZE_OF_ZONE - fb) / fk;
					CMapZone* pcz;

					pcz = GetZone(GetZoneX(cross), tempint0);
					if (pcz != NULL)
					{
						pcz->AddRegion(pCRegion->m_ID);
					}

					pcz = GetZone(GetZoneX(cross), tempint0 - 1);
					if (pcz != NULL)
					{
						pcz->AddRegion(pCRegion->m_ID);
					}
				}

				for (tempint0 = std::min(sGridX, eGridX) + 1; tempint0 <= std::max(sGridX, eGridX); tempint0++)
				{
					/* 计算多边形边同垂直切线的交点,将切点左右两个zone注册 */
					FLOAT cross = ((tempint0)*SIZE_OF_ZONE) * fk + fb;
					CMapZone* pcz;

					pcz = GetZone(tempint0, GetZoneZ(cross));
					if (pcz != NULL)
					{
						pcz->AddRegion(pCRegion->m_ID);
					}

					pcz = GetZone(tempint0 - 1, GetZoneZ(cross));
					if (pcz != NULL)
					{
						pcz->AddRegion(pCRegion->m_ID);
					}
				}
			}
		}
	}
}

CMapZone* GameScene::GetZone(int32_t nXPos, int32_t nZPos)
{
	/* 物体位置非法 */
	if (nXPos < 0 || nXPos >= m_nZoneXSize || nZPos < 0 || nZPos >= m_nZoneZSize)
	{
		/* Warning.... 该物体定义的位置不在地图之内 */
		return NULL;
	}

	return &(mZoneBuf[nZPos * m_nZoneXSize + nXPos]);
}

void GameScene::addObject(Orphigine::ActorPtr& obj)
{
	mActors.push_back(obj);
}

Orphigine::NeSDK* GameScene::getNeSDK()
{
	return m_neSDK;
}

int32_t GameScene::GetZoneX(Real fx) const
{
	return(int32_t)(fx / static_cast<int>(SIZE_OF_ZONE));
}

int32_t GameScene::GetZoneZ(Real fz) const
{
	return(int32_t)(fz / static_cast<int>(SIZE_OF_ZONE));
}

int32_t GameScene::GetRegionCount()
{
	return (int32_t)mRegionList.size();
}


CMapRegion* GameScene::GetRegion(int32_t index)
{
	return mRegionList[index];
}

CMapCollisionManager& GameScene::getCollision()
{
	return m_WalkCollisionMng;
}
#include "OgreCamera.h"
#include "OgreViewport.h"
#include "OgreRoot.h"
bool GameScene::getIntersectObject(
	Real winx, Real winy,
	std::vector<Orphigine::ActorPtr>& objects)
{
	auto mainCamera = EngineManager::getSingleton().getMainCamera();
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	
	float screenX = winx/ ogreConfig.width;
	float screenY = winy/ ogreConfig.height;
	auto ray = mainCamera->getCameraToViewportRay(screenX, screenY);

	std::map<uint64_t, Orphigine::ActorPtr> aa;
	for (uint32_t i = 0; i < mActors.size(); i++)
	{
		Orphigine::ActorPtr& actor = mActors.at(i);
		auto result = actor->queryIntersect(ray);
		if (result.first)
		{
			aa[result.second] = actor;
		}
	}

	for (auto& pair : aa)
	{
		objects.push_back(pair.second);
	}
	return true;
}

bool GameScene::IsValidPosition(const Ogre::Vector2& fvPos)
{
	if (NULL == mSceneDefine)
	{
		return false;
	}

	if (fvPos.x < 0.0f || fvPos.x >(FLOAT) (mSceneDefine->nXSize))
	{
		return false;
	}

	if (fvPos.y < 0.0f || fvPos.y >(FLOAT) (mSceneDefine->nZSize))
	{
		return false;
	}

	return true;
}

void GameScene::loadImpl()
{
	mTerrain->buildTerrain();
	EngineManager::getSingleton().setTerrain(mTerrain.get());

	uint32_t count = 7;

	count = std::min(count, (uint32_t)mActors.size());
	for (int32_t i = 0; i < mActors.size(); i++)
	{
		mActors[i]->createRenderInstance();
	}

	//load physics


}