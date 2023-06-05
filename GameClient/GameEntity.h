#pragma once

#include "OGActor.h"
#include "OGSpell.h"
#include "OGSkeletonMeshActor.h"

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
	GameEntity();
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
};