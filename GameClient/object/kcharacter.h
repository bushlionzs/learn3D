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
#include "command/KCharStruct.h"

class KAI_Player;
class PathComponent;
class PlayerLogicModelHaveCreateCallback;
class KCharatcterBaseData;
class GameEntity;

class KCharacter: public KObject
{
protected:
	Ogre::Vector3 mGamePosition;
	Ogre::Vector3 mEnginePosition;
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
	bool						m_bIsCharBaseLogicEnd;
	bool						m_bIsCharActionLogicEnd;

	/// AI对象
	KAI_Player* m_pAI = nullptr;

	/// 正在执行的逻辑状态
	CHARATER_STATE_TYPE			m_nCharBaseState;
	CHARATER_STATE_TYPE			m_nCharActionState;

	//jump
	bool m_bInAir;
	int32 m_nJumpActionState;

	float	mFightStateTime = 0.0f;
	float   m_fMoveRate = 1.0f;

	/// 当前逻辑命令

	/// 逻辑命令列表
	typedef std::list<KCharCmdDate_Logic*>	ObjCommandList;
	ObjCommandList								m_listBaseStateCommand;
	ObjCommandList								m_listActionStateCommand;

	KCharCmdDate_Logic* m_pBaseLogicCommand = nullptr;
	KCharCmdDate_Logic* m_pActionLogicCommand;

	CharStateData_Idle			m_StateDate_Idle;
	CharStateData_Move			m_StateDate_Move;
	CharStateData_Charge		m_StateDate_Charge;
	CharStateData_Channel		m_StateDate_Channel;
	CharStateData_Send			m_StateDate_Send;
	CharStateData_Ability		m_StateDate_Ability;
	CharStateData_Stall			m_StateDate_Stall;
	CharStateData_Dead			m_StateDate_Dead;

	// 逻辑锁定状态。锁定状态时，人物不可切换逻辑状态
	bool m_bLogic_Locked = false;
	// 加锁计时器
	uint64_t m_uLogicLockTimer = 0;
	// 动作速度
	FLOAT m_fActionLogic_Speed;
	// 特效速度
	FLOAT m_fActionImpact_Speed;

	// 正在冲锋
	bool m_bSkillTantivyFlag = false;

	///// 当前逻揖执行的速度
	float m_fLogic_Speed;

	// 基本动作起始时间
	uint64_t m_uBaseAnimStartTime;

	// 行为动作起始时间
	uint64_t m_uActionAnimStartTime;

	// 朝向
	FLOAT m_fToRotation = 0.0f;
	FLOAT m_fRotationSpeed = 10.0f;
public:
	KCharacter();

	const Ogre::Vector3& getPosition();
	const Ogre::Vector3& getEnginePosition();
	void setPosition(const Ogre::Vector3& position, bool useTerrainHeight = true);

	Ogre::Real getDirection();
	void setDirection(float dir);


	KAI_Player* getAI()
	{
		return m_pAI;
	}
	
	void ChangeAction(int32 nActionType, FLOAT fDegree, int32 nActionID = INVALID_ID, FLOAT fSpeed = 1.0f, BOOL bShowWeapon = TRUE);

	BOOL ChangeMountAction(int32 nActionType, FLOAT fDegree, int32 nActionID);
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
	KCharCmdDate_Logic* GetNextCommand(CHARATER_LOGIC_TYPE nLogicTag);
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
	void ModifyMove(void);
	bool IsCanJump();
	bool DoJump(void);
	bool IsJumping() const;
	bool IsJumpMoving() const;

	// 逐渐改变朝向
	void toFaceDir(FLOAT fDir);

	bool BeginJump();
	bool EndJump();
	bool BeginRiding(void);
	bool IsDie(void);
	bool BeginCadaver();

	//
	bool IsAttached();
	bool IsInAir();
	bool IsMoving();
	bool IsUseSkill();
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

	void calculateNodePos(
		const Ogre::Vector2& fvPosition,
		FLOAT fModifyHeight);

	bool AddCommand(const ObjectCmd* pCmd);
	eRUN_CMD_RESULT_CODE HandleCommand(const ObjectCmd* pCmd);
	KCharCmdDate_Logic* FindBaseStateCommand(int32 nLogicCount);
	KCharCmdDate_Logic* FindActionStateCommand(int32 nLogicCount);
	KCharCmdDate_Logic* GetBaseStateCommand(void);
	void SetBaseStateCommand(KCharCmdDate_Logic* pLogicCommand);
	KCharCmdDate_Logic* GetActionStateCommand(void);
	void SetActionStateCommand(KCharCmdDate_Logic* pLogicCommand);
	void DelAllMoveCommand();
	BOOL AddBaseStateCommand(KCharCmdDate_Logic* pCmd);
	BOOL AddActionStateCommand(KCharCmdDate_Logic* pCmd);
	BOOL ProcessBaseStateCommand(void);
	BOOL ProcessActionStateCommand(void);
	BOOL CheckNextActionStateCommand();
	BOOL ProcessNextCommand(CHARATER_LOGIC_TYPE nLogicTag);
	BOOL ProcessStateCommand(KCharCmdDate_Logic* pLogicCmd);

	void SetLogicSpeed(FLOAT fSpeed)
	{
		if (fabsf(m_fLogic_Speed - fSpeed) > 0.1f)
		{
			m_fLogic_Speed = fSpeed;
		}
	}

	FLOAT GetLogicSpeed(void) const 
	{ 
		return m_fLogic_Speed; 
	}

	bool IsEmpty_BaseStateCommand(void)
	{
		return m_listBaseStateCommand.empty();
	}
	bool IsEmpty_ActionStateCommand(void)
	{
		return m_listActionStateCommand.empty();
	}

	bool IsIdle(void) const;

	bool IsMoving(void) const;

	bool IsGather(void) const;

	bool IsLead(void) const;

	bool IsUseSkill(void) const;

	bool IsLogicLocked();
	void SetLogicLocked(BOOL bLock);

	void SetActionImpactSpeed(FLOAT fSpeed);
	void ModifyCurrPos(const Ogre::Vector2& fvServerPos);

	void ShutDown_CharacterState(CHARATER_LOGIC_TYPE nLogicTag);
	void Exit_CharacterState(CHARATER_LOGIC_TYPE nLogicTag);
	void Active_CharacterState(CHARATER_STATE_TYPE eLogic, CHARATER_LOGIC_TYPE nLogicTag);

	void SetActionLogicSpeed(FLOAT fSpeed);
	FLOAT GetActionLogicSpeed() const;

	// 休闲
	bool	EnterState_Idle(void);
	// 动作
	bool	EnterState_Action(KCharCmdDate_Logic* pLogicCommand);
	// 移动
	bool	EnterState_Move(KCharCmdDate_Logic* pLogicCommand);
	// 法术聚气
	bool	EnterState_Charge(KCharCmdDate_Logic* pLogicCommand);
	// 法术引导
	bool	EnterState_Channel(KCharCmdDate_Logic* pLogicCommand);
	// 法术发招
	bool	EnterState_Send(KCharCmdDate_Logic* pLogicCommand);
	// 死亡
	bool	EnterState_Dead(BOOL bPlayDieAni = TRUE);
	// 生活技能
	bool	EnterState_Ability(KCharCmdDate_Logic* pLogicCommand);
	// 摆摊
	bool	EnterState_Stall(BOOL bPlayAni);

	// 执行事件
	void	AddEvent(const LogicEventData* pLogicEvent);
	void	RemoveEvent(int32 nLogicCount);
	void	RemoveAllEvent(void);
	void	Update_Event(void);

	// 更新朝向
	void Update_ToFaceDir(float deltatime);

	virtual bool UpdateState_Idle(uint32 uElapseTime);
	virtual bool UpdateState_Move(uint32 uElapseTime);
	virtual bool UpdateState_Dead(uint32 uElapseTime);
	virtual bool UpdateState_Stall(uint32 uElapseTime);

	bool	ProcessEvent(const LogicEventData* pLogicEvent);
	bool	ProcessEvent_Damage(const LogicEventData* pLogicEvent);

	//
	void	UpdateModel_BuffEffect(void);

	bool	AddImpact(uint32 nSN, int32 idImpact, ObjID_t nCreatorID, int32 nNumOflayer, int32 nSenderLogicCount);
	void	DelImpact(uint32 nSN);

	void	ClearBuffEffectHandle();
	void	ClearMountBuffEffect();

	bool	AddBindEffect(const String&, const String&);

	bool	AddMountEffect(const String&, const String&);
public:
	virtual void UpdateCharBaseData(void) {}
	virtual void UpdateModel_WeaponActionSet(void) {}
	virtual void UpdateModel_Visible();
	virtual void update(float deltatime);

	virtual int32 AnalyseCharModel(void)const;

	virtual void UpdateEquip(PLAYER_EQUIP point) {}
	virtual bool UpdateFashion() { return true; }

	// 客气端的本地指令
	eRUN_CMD_RESULT_CODE AddLocalCommand(const ObjectCmd* pCmd);
protected:
	void OnChangeOfMountId();
	void UpdateModel_CharActionSet(void);
	void UpdateModel_MountActionSet(void);
	
	virtual void createCharRenderInterface(void);
	virtual GameEntity* CreateMountRenderInterface(int32 nMountID);
	//
	// 上马
	virtual BOOL			Mounting(GameEntity* mountInterface, int32 nMountID);
	// 下马
	virtual void			Dismount();
	
	virtual void   OnQueryRay(GameEntity* entity) {}

	
};