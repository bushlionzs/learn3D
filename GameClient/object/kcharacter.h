#pragma once

#include "OGActor.h"
#include "OGSkeletonMeshComponent.h"
#include "engine_manager.h"

#include "PathComponent.h"
#include "demoHeader.h"
#include "TAB.h"
#include "demoHeader.h"
#include "CharacterCommon.h"
#include "DefineItem.h"
#include "KObject.h"
#include "GameEntity.h"
#include "Basics.h"

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
class KCharatcterBaseData;
class GameEntity;

class KCharacter: public KObject
{
protected:
	std::shared_ptr<GameEntity>     mMountObj;
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
	const TAB::TABFile* m_pWeaponActionSet;

	
	std::shared_ptr<GameEntity> mMountEntity;

	int32_t mCurrCharModelID;
	int32_t mCurrMountModelID;
	std::string mModelName;
	std::string mMountModelName;
	std::string mWeaponModelName;
	eNPC_TYPE				m_eNpcType;
	KCharatcterBaseData* m_pCharacterData;
	// 基本跑步速度
	FLOAT					m_fRunBaseSpeed;

	// 基本步行速度
	FLOAT					m_fWalkBaseSpeed;

	// 当前武器类型
	eWEAPON_TYPE		m_theLWeaponType;
	eWEAPON_TYPE		m_theRWeaponType;

	/// 人物模型对应表中的ID
	int32						m_nCurrCharModelID;
	int32						m_nCurrMountModelID;

	// 绑定ID
	int32						m_nAttachID;

	/// 逻辑是否停止
	BOOL						m_bIsCharBaseLogicEnd;
	BOOL						m_bIsCharActionLogicEnd;

	/// 正在执行的逻辑状态
	CHARATER_STATE_TYPE			m_nCharBaseState;
	CHARATER_STATE_TYPE			m_nCharActionState;

	//jump
	bool m_bInAir;
	int32 m_nJumpActionState;

	float	mFightStateTime = 0.0f;
	float   m_fMoveRate = 1.0f;
public:
	KCharacter();

	const Ogre::Vector3& getPosition();
	void setPosition(const Ogre::Vector3& position, bool useTerrainHeight = true);

	Ogre::Real getDirection();
	void setDirection(float dir);

	
	void ChangeAction(int32 nActionType, FLOAT fDegree, int32 nActionID = INVALID_ID, FLOAT fSpeed = 1.0f, BOOL bShowWeapon = TRUE);
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
	

	bool initialize();

	bool startSkill();
	void ChangeActionSpeed(FLOAT fSpeed);
	bool createSkillImpact(int32_t nActionID, float fDir);

	bool startMood();

	void createMount();

	void setMountId(int32_t mountId);

	virtual CHARACTER_BASE_TYPE	GetCharacterType(void) const
	{
		return CHAR_BASE_TYPE_INVALID;
	}

	
	void DoDataEvent_DataID();
	void DoDataEvent_ModelID();
	void DoDataEvent_MountID();
	void DoDataEvent_Dir();
	void DoDataEvent_Level();
	void DoDataEvent_MoveSpeed();
	void DoDataEvent_Equip(PLAYER_EQUIP point);
	void OnDataChanged_FaceImage();
	void OnDataChanged_HairMesh();
	void OnDataChanged_FaceMesh();

	int32_t GetCurrCharModelID();

	KCharatcterBaseData* GetCharacterData(void);

	void ChangeWeaponEffect(
		GameEntity::eWEAPATTR ePart,
		LPCTSTR szEffectName,
		LPCTSTR nLocatorName,
		uint32 color);

	int32 getEffectPriority();

	eWEAPON_TYPE GetMainWeaponType();
	eWEAPON_TYPE GetWeaponType(ENUM_WEAPON_LOCATOR_TYPE loc) const;

	void SetWeaponType(
		eWEAPON_TYPE type,
		ENUM_WEAPON_LOCATOR_TYPE loc = WL_BOTH);

	void SetWeaponAction(LPCTSTR szWeaponAnimName);

	bool IsModelCreateAllCompleted();

	bool IsFollowAttach();

	void UpdateCharModel(void);

	void ReleaseCharRenderInterface(void);

	int32_t GetAttachModelNum();
	bool IsCanUpdateMountByModelID();
	bool IsStopped_CharacterState(
		CHARATER_LOGIC_TYPE nLogicTag) const;
	CHARATER_STATE_TYPE GetCharacterState(
		CHARATER_LOGIC_TYPE nLogicTag) const;
	void RefreshBaseAnimation();
	void RefreshActionAnimation();
	void RefreshAnimation();
	void UpdateModel_Scale();
	void UpdateModel_Effect();
	void UpdateModel_AllAttr(bool bAfresh = false);
	bool UpdateMountingState();
	bool AddAttachMember(int32 nObjId);
	bool RemoveAttachMember(int32 nObjId);
	void StopMove();
	int32 GetSpecifyMountIDByModleID();
	void UpdateMountModel(void);
	void UpdateAttached();
	void UpdateModel_Attach();
	void UpdateModel_State();

	void ReadyPlayWalkSound();
	void StopWalkSound();
	void SetJumpActionState(int32 nJumping) 
	{ 
		m_nJumpActionState = nJumping; 
	}
	bool IsFightState(void) const;
	FLOAT	GetMoveRate() 
	{ 
		return m_fMoveRate; 
	}
	//action
	bool BeginIdle(void);
	bool EndIdle(void);
	bool BeginMove(bool bPlayMoveSound = true);
	bool EndMove(void);
	bool DoJump(void);
	bool IsJumping() const;
	bool BeginJump();
	bool EndJump();
	bool BeginRiding(void);
	bool IsDie(void);
	bool BeginCadaver();

	//
	// 添加一个动作
	bool	SetActionSlot(
		int32 nAASNode, 
		int32 nActionID, 
		BOOL bActionBySkill = FALSE, 
		FLOAT fRate = 1.f, 
		BOOL bLoop = FALSE, 
		BOOL bBlendIn = TRUE, 
		BOOL bBlendOut = TRUE);
	// 给人物添加动作
	bool	SetCharActionSlot(
		int32 nAASNode, 
		int32 nActionID, 
		BOOL bActionBySkill = FALSE, 
		FLOAT fRate = 1.f, 
		BOOL bLoop = FALSE, 
		BOOL bBlendIn = TRUE, 
		BOOL bBlendOut = TRUE);
	// 给坐骑
	bool	SetMountActionSlot(
		int32 nAASNode, 
		int32 nActionID, 
		BOOL bActionBySkill = FALSE, 
		FLOAT fRate = 1.f, 
		BOOL bLoop = FALSE, 
		BOOL bBlendIn = TRUE, 
		BOOL bBlendOut = TRUE);
	// 给武器
	bool	SetWeaponActionSlot(
		int32 nAASNode, 
		int32 nActionID, 
		BOOL bActionBySkill = FALSE, 
		FLOAT fRate = 1.f, 
		BOOL bLoop = FALSE, 
		BOOL bBlendIn = TRUE, 
		BOOL bBlendOut = TRUE);
	LPCSTR GetMainWeaponTypeName();
	LPCSTR GetCharActionNameByActionSetID(
		int32 nActionSetID,
		int32 nWeaponType,
		BOOL* pbHideWeapon,
		int32* pnAppointedWeaponID);
	LPCSTR GetMountActionNameByActionSetID(
		int32 nActionSetID);
	LPCSTR GetWeaponActionNameByActionSetID(
		int32 nActionSetID, int32 nWeaponType);
	bool SetSlotIndex(int32 nAASNode, int32 nActionID);
	bool SetCharSlotIndex(int32 nAASNode, int32 nActionID);
public:
	virtual void UpdateCharBaseData(void) {}
	virtual void UpdateModel_WeaponActionSet(void) {}
	virtual void UpdateModel_Visible();
	virtual void update(float deltatime);

	virtual int32 AnalyseCharModel(void)const;
protected:
	void OnChangeOfMountId();
	void UpdateModel_CharActionSet(void);
	void UpdateModel_MountActionSet(void);
	
	virtual void createCharRenderInterface(void);

	//
	
	
};