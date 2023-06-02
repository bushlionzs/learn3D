#pragma once

#include "OGActor.h"
#include "OGSkeletonMeshComponent.h"
#include "engine_manager.h"
#include "InputManager.h"
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



class KPlayer
{
private:
	Orphigine::ActorPtr		mOrphigineObj;
	Ogre::Vector3 mGamePosition;
	Ogre::Real  mDirection = 0.0f;
	Ogre::Real  mCurrentDirection = 0.0f;
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
public:
	KPlayer();

	const Ogre::Vector3& getGamePosition();
	void setGamePosition(Ogre::Vector3& position);

	Ogre::Real getDirection();
	void setDirection(float dir);

	void setWeaponname(Ogre::String& name);

	void input(KeyCode _key);
	void ChangeAction(int32_t nActionType, float fDegree, int32_t nActionID = -1);
	LPCSTR getCharActionNameByActionSetID(int32_t nActionSetID, int32_t nWeaponType, BOOL* pbHideWeapon, int32_t* pnAppointedWeaponID);
	eWEAPON_TYPE getMainWeaponType();
	void onAnimationEnd(const char* animName, const char* parentNodeType, const char* parentNodeName);

	void injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id);

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
};