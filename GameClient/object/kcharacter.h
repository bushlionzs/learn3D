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

	std::string mModelName;
	std::string mMountModelName;
	std::string mWeaponModelName;
	eNPC_TYPE				m_eNpcType;
	KCharatcterBaseData* m_pCharacterData;
	// �����ܲ��ٶ�
	FLOAT					m_fRunBaseSpeed;

	// ���������ٶ�
	FLOAT					m_fWalkBaseSpeed;

	// ��ǰ��������
	eWEAPON_TYPE		m_theLWeaponType;
	eWEAPON_TYPE		m_theRWeaponType;

	/// ����ģ�Ͷ�Ӧ���е�ID
	int32						m_nCurrCharModelID;
	int32						m_nCurrMountModelID;

	// ��ID
	int32						m_nAttachID;

	/// �߼��Ƿ�ֹͣ
	bool						m_bIsCharBaseLogicEnd;
	bool						m_bIsCharActionLogicEnd;

	/// ����ִ�е��߼�״̬
	CHARATER_STATE_TYPE			m_nCharBaseState;
	CHARATER_STATE_TYPE			m_nCharActionState;

	//jump
	bool m_bInAir;
	int32 m_nJumpActionState;

	float	mFightStateTime = 0.0f;
	float   m_fMoveRate = 1.0f;

	/// ��ǰ�߼�����

	/// �߼������б�
	typedef std::list<KCharCmdDate_Logic*>	ObjCommandList;
	ObjCommandList								m_listBaseStateCommand;
	ObjCommandList								m_listActionStateCommand;

	KCharCmdDate_Logic* m_pBaseLogicCommand;
	KCharCmdDate_Logic* m_pActionLogicCommand;

	CharStateData_Idle			m_StateDate_Idle;
	CharStateData_Move			m_StateDate_Move;
	CharStateData_Charge		m_StateDate_Charge;
	CharStateData_Channel		m_StateDate_Channel;
	CharStateData_Send			m_StateDate_Send;
	CharStateData_Ability		m_StateDate_Ability;
	CharStateData_Stall			m_StateDate_Stall;
	CharStateData_Dead			m_StateDate_Dead;

	// �߼�����״̬������״̬ʱ�����ﲻ���л��߼�״̬
	bool m_bLogic_Locked = false;
	// ������ʱ��
	uint64_t m_uLogicLockTimer = 0;
	// �����ٶ�
	FLOAT m_fActionLogic_Speed;
	// ��Ч�ٶ�
	FLOAT m_fActionImpact_Speed;

	FLOAT m_fRotationSpeed;
	// ���ڳ��
	bool m_bSkillTantivyFlag = false;

	///// ��ǰ��Ҿִ�е��ٶ�
	float m_fLogic_Speed;
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
	bool DoJump(void);
	bool IsJumping() const;
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
	// ����һ������
	bool	SetActionSlot(
		int32 nAASNode, 
		int32 nActionID, 
		BOOL bActionBySkill = FALSE, 
		FLOAT fRate = 1.f, 
		BOOL bLoop = FALSE, 
		BOOL bBlendIn = TRUE, 
		BOOL bBlendOut = TRUE);
	// ���������Ӷ���
	bool	SetCharActionSlot(
		int32 nAASNode, 
		int32 nActionID, 
		BOOL bActionBySkill = FALSE, 
		FLOAT fRate = 1.f, 
		BOOL bLoop = FALSE, 
		BOOL bBlendIn = TRUE, 
		BOOL bBlendOut = TRUE);
	// ������
	bool	SetMountActionSlot(
		int32 nAASNode, 
		int32 nActionID, 
		BOOL bActionBySkill = FALSE, 
		FLOAT fRate = 1.f, 
		BOOL bLoop = FALSE, 
		BOOL bBlendIn = TRUE, 
		BOOL bBlendOut = TRUE);
	// ������
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

	bool IsEmpty_BaseStateCommand(void)
	{
		return m_listBaseStateCommand.empty();
	}
	bool IsEmpty_ActionStateCommand(void)
	{
		return m_listActionStateCommand.empty();
	}

	bool IsLogicLocked();
	void SetLogicLocked(BOOL bLock);

	void SetActionImpactSpeed(FLOAT fSpeed);
	void ModifyCurrPos(const Ogre::Vector2& fvServerPos);

	void ShutDown_CharacterState(CHARATER_LOGIC_TYPE nLogicTag);
	void Exit_CharacterState(CHARATER_LOGIC_TYPE nLogicTag);

	void SetActionLogicSpeed(FLOAT fSpeed);
	FLOAT GetActionLogicSpeed() const;
	void SetLogicSpeed(FLOAT fSpeed);
	// ����
	bool	EnterState_Idle(void);
	// ����
	bool	EnterState_Action(KCharCmdDate_Logic* pLogicCommand);
	// �ƶ�
	bool	EnterState_Move(KCharCmdDate_Logic* pLogicCommand);
	// ��������
	bool	EnterState_Charge(KCharCmdDate_Logic* pLogicCommand);
	// ��������
	bool	EnterState_Channel(KCharCmdDate_Logic* pLogicCommand);
	// ��������
	bool	EnterState_Send(KCharCmdDate_Logic* pLogicCommand);
	// ����
	bool	EnterState_Dead(BOOL bPlayDieAni = TRUE);
	// �����
	bool	EnterState_Ability(KCharCmdDate_Logic* pLogicCommand);
	// ��̯
	bool	EnterState_Stall(BOOL bPlayAni);

	// ִ���¼�
	void	AddEvent(const LogicEventData* pLogicEvent);
	void	RemoveEvent(int32 nLogicCount);
	void	RemoveAllEvent(void);
	void	Update_Event(void);

	
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
protected:
	void OnChangeOfMountId();
	void UpdateModel_CharActionSet(void);
	void UpdateModel_MountActionSet(void);
	
	virtual void createCharRenderInterface(void);

	//
	
	
};