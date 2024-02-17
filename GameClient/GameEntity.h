#pragma once

#include "OGActor.h"
#include "OGSpell.h"
#include "OGSkeletonMeshActor.h"

enum RAYQUERY_LEVEL
{
	RL_ITEMBOX = 1,	/* 掉落包 1 */
	RL_PLAYER_DEADBODY = 2,	/* 玩家尸体 2 */
	RL_CREATURE = 3,	/* NPC & Monster 3 */
	RL_TRIPPEROBJ = 4,	/* 资源 4 */
	RL_PLAYEROTHER = 5,	/* 玩家 5 */
	RL_PLAYERMYSLEF = 6,	/* 自己 6 */
	RL_PET = 7,	/* 宠物 7 */
	RL_CREATURE_DEADBODY = 8,	/* 怪物尸体 8 */
	RL_PLATFORM = 9,	/* 操作平台 9 */
	RL_UNKNOWN = 10,
};

class KObject;
class GameEntity
{
public:
	/* 武器绑定点类型 */
	enum eWEAPATTR
	{
		WEAP_NONE,						/* 空 */
		WEAP_RIGHT,						/* 右手 */
		WEAP_LEFT,						/* 左手 */
		WEAP_LEFT_SHIELD,				/* 左盾牌 */
	};
public:
	GameEntity(KObject* owner);
	~GameEntity();

	bool setModelName(const String& modelName);
	bool changeAttributes(
		const std::vector<String>& name, 
		const std::vector<String>& value);
	void setWeapon(const String& weaponName);

	const Ogre::Vector3& getEntityPosition();
	void setEntityPosition(Ogre::Vector3& position);

	Ogre::Real getDirection();
	void setDirection(float dir);

	void setAnimationDegree(int32_t nActionType, float fDegree);

	Orphigine::Spell* getCurrentSpell();

	Orphigine::SkeletonMeshComponent* getLogicModel();

	Orphigine::SkeletonMeshActor* getSkeletonMeshActor();

	//
	void SetModelType(int32 nType);

	virtual String	AddEffect
	(
		LPCSTR effectName,
		LPCSTR locatorName,
		int32 id = 0,
		LPCSTR name = "",
		int32 priority = 2
	);

	void Weapon_RemoveEffect(eWEAPATTR eWeaponAttr);

	void LeftWeapon_SetEffect(
		LPCTSTR szEffectName,
		LPCSTR szLocatorName,
		uint32 color, int32 priority);

	void RightWeapon_SetEffect(
		LPCTSTR szEffectName,
		LPCSTR szLocatorName,
		uint32 color,
		int32 priority);

	void Shield_SetEffect(
		LPCTSTR szEffectName,
		LPCSTR szLocatorName,
		uint32 color,
		int32 priority);

	void Weapon_SetAasAnim(int32 eWeqaponType);

	void DeleteEffect(LPCSTR effect);

	void SetVisible(bool bVisible);

	void DeleteAllEffect(void);

	void Destroy(void);

	bool Attach_Object(
		GameEntity* pObject, LPCTSTR szAttachLocator);

	bool Detach_Object(GameEntity* pObject);

	bool Actor_SetSlotIndex(
		LPCTSTR szSlotName, USHORT uSlotIndex);

	bool Actor_SetActionSlot
	(
		LPCTSTR szSlotName,
		LPCTSTR szActionName,
		BOOL bLoop,
		FLOAT fRate,
		BOOL bBlendIn,
		BOOL bBlendOut
	);

	bool Actor_SetWeaponActionSlot
	(
		LPCTSTR szSlotName,
		LPCTSTR szActionName,
		LPCTSTR	szWeaponTypeName,
		BOOL bLoop,
		FLOAT fRate,
		BOOL bBlendIn,
		BOOL bBlendOut
	);

	void SetScaleFactor(FLOAT fScale);

	Orphigine::Spell* GetCurrentSkill();
	void ChangeModelActionRate(FLOAT fRate);

	void SetModel_RayQuery(BOOL bQuery)
	{
		mQuery = bQuery;
	}
	bool GetRayQuery(void)
	{
		return mQuery;
	}

	/* 鼠标选择级别 */
	void			SetRayQueryLevel(RAYQUERY_LEVEL nLevel)
	{
		mQueryLevel = nLevel;
	}

	RAYQUERY_LEVEL	GetRayQueryLevel(void)
	{
		return mQueryLevel;
	}

	KObject* getOwner()
	{
		return mOwner;
	}
private:
	Orphigine::ActorPtr		mOrphigineObj;
	Ogre::Vector3 mEntityPosition;
	Ogre::Real  mDirection = 0.0f;

	std::string mModelName;
	bool mVisible = false;

	/* 插槽节点缓冲 */
	typedef std::map<String, Orphigine::AASNode*>	AASNODE_MAP;
	AASNODE_MAP		m_mapCharAASNode;
	AASNODE_MAP		m_mapWeaponAASNode;

	String			m_strLastActionName;

	Ogre::Vector3	m_fvDefaultScale = Ogre::Vector3::UNIT_SCALE;
	float m_fScale = 1.0f;

	KObject* mOwner = nullptr;

	bool mQuery = false;
	RAYQUERY_LEVEL mQueryLevel = RL_UNKNOWN;
};