#pragma once

#include "OGActor.h"
#include "OGSkeletonMeshComponent.h"
#include "engine_manager.h"

#include "PathComponent.h"
#include "demoHeader.h"
#include "TAB.h"
#include "demoHeader.h"
#include "CharacterCommon.h"

class MyCallback : public Orphigine::SkeletonMeshComponent::AASAnimEndCallback
{
public:
	void	onAnimationEnd(
		const char* animName, 
		const char* parentNodeType, 
		const char* parentNodeName,
		uint64_t info);
};

class PathComponent;
class PlayerLogicModelHaveCreateCallback;

class GameEntity;

class Character
{
protected:
	//Orphigine::ActorPtr		mOrphigineObj;
	Orphigine::ActorPtr     mMountObj;
	Ogre::Vector3 mGamePosition;
	Ogre::Real  mDirection = 0.0f;
	Orphigine::SkeletonMeshComponent::AASAnimEndCallback* callback = nullptr;

	PathComponent* mPathComponent;

	Orphigine::Impact* mProjectorEffect = nullptr;
	Ogre::SceneNode* mMouseNode = nullptr;

	Ogre::String mWeaponname;

	PlayerLogicModelHaveCreateCallback* mCallback = nullptr;

	Ogre::String mLastActionName;

	typedef std::map<Ogre::String, Orphigine::AASNode*>	AASNODE_MAP;
	AASNODE_MAP		m_mapCharAASNode;
	AASNODE_MAP		m_mapWeaponAASNode;

	std::map<Ogre::String, int32_t> mASSNodeTypeMap;

	const TAB::TABFile* m_pCharActionSet = nullptr;
	const TAB::TABFile* m_pMountActionSet = nullptr;

	std::shared_ptr<GameEntity> mMainEntity;
	std::shared_ptr<GameEntity> mMountEntity;

	int32_t mRaceId;
	int32_t mCurrCharModelID;
	int32_t mCurrMountModelID;
	std::string mModelName;
	std::string mMountModelName;
	std::string mWeaponModelName;
	eNPC_TYPE				m_eNpcType;

	// 基本跑步速度
	FLOAT					m_fRunBaseSpeed;

	// 基本步行速度
	FLOAT					m_fWalkBaseSpeed;
public:
	Character();

	const Ogre::Vector3& getPosition();
	void setPosition(const Ogre::Vector3& position, bool useTerrainHeight = true);

	Ogre::Real getDirection();
	void setDirection(float dir);

	
	void ChangeAction(int32_t nActionType, float fDegree, int32_t nActionID = -1);
	LPCSTR getCharActionNameByActionSetID(int32_t nActionSetID, int32_t nWeaponType, BOOL* pbHideWeapon, int32_t* pnAppointedWeaponID);
	eWEAPON_TYPE getMainWeaponType();
	void onAnimationEnd(const char* animName, const char* parentNodeType, const char* parentNodeName);

	

	bool setCharActionSlot(
		int32_t nAASNode, 
		int32_t nActionID, 
		bool bActionBySkill = false, 
		FLOAT fRate = 1.f, 
		bool bLoop = false, 
		bool bBlendIn = true, 
		bool bBlendOut = true);

	bool actorSetActionSlot
	(
		LPCTSTR szSlotName,
		LPCTSTR szActionName,
		bool bLoop,
		FLOAT fRate,
		bool bBlendIn,
		bool bBlendOut
	);
	void update(float deltatime);

	bool initialize();

	bool startSkill();
	bool createSkillImpact(int32_t nActionID, float fDir);

	bool startMood();

	void createMount();

	void setRaceId(int32_t raceId);
	void setCharModelId(int32_t modelId);
	void setMountId(int32_t mountId);


	
private:
	void OnChangeOfModelId();
	void OnChangeOfMountId();
	void UpdateModel_CharActionSet(void);
	void UpdateModel_MountActionSet(void);
	void CreateCharRenderInterface(void);
};