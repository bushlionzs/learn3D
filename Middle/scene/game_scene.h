#pragma once
#include "OGActor.h"
#include "GameMapCollisionManager.h"
#include "OGNavigate.h"
#include "GameMapZone.h"

class Terrain;
class CMapRegion;
struct _TABLE_SCENE_DEFINE;
class GameScene
{
	enum { SIZE_OF_ZONE = 10 }; /* Zone的大小 */
	friend class SceneSerializer;
public:
	GameScene(const _TABLE_SCENE_DEFINE* define);
	~GameScene();

	bool load();

	void addObject(Orphigine::ActorPtr& obj);

	Orphigine::NeSDK* getNeSDK();

	int32_t GetZoneX(Real fx) const;

	int32_t GetZoneZ(Real fz) const;

	int32_t GetRegionCount();
	CMapRegion* GetRegion(int32_t index);

	CMapCollisionManager& getCollision();

	bool getIntersectObject(
		Real winx, Real winy,
		std::vector<Orphigine::ActorPtr>& objects);
private:
	void loadRegionBinary(LPCTSTR szRegionFile);
	void registeAllRegion(void);
	CMapZone* GetZone(int32_t nXPos, int32_t nZPos);
	void loadImpl();
private:
	int32_t mSceneId;

	String mSceneName;
	String mTerrainFilename;
	std::vector<Orphigine::ActorPtr> mActors;
	std::unique_ptr<Terrain> mTerrain;


	int32_t m_nZoneXSize;
	int32_t m_nZoneZSize;
	std::vector<CMapZone> mZoneBuf;
	/* Region链表 */
	std::vector<CMapRegion*>	mRegionList;

	/* 建筑物行走面管理 */
	CMapCollisionManager m_WalkCollisionMng;

	Orphigine::NeSDK* m_neSDK;
	Orphigine::NeSpace* m_neSpace;

	const _TABLE_SCENE_DEFINE* mSceneDefine;
};