#pragma once
#include "KItem.h"
#include "OGActor.h"
#include "OGSkeletonMeshComponent.h"
#include "engine_manager.h"
#include "InputManager.h"
#include "PathComponent.h"
#include "demoHeader.h"
#include "TAB.h"
#include "demoHeader.h"
#include "CharacterCommon.h"
#include "InputManager.h"
#include "kcharacter.h"
#include "GameTableData.h"


class PathComponent;
class PlayerLogicModelHaveCreateCallback;
class CDirectlyEffectMgr;
class GameEntity;

class KPlayer: public KCharacter
{

public:
	KPlayer();
	~KPlayer();

	void injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id);
	void input(KeyCode _key);
	void UpdateBodyPartModel();
private:
	void createCharRenderInterface(void);
	
	void UpdateFaceMesh(void);
	void UpdateHairMesh(void);
	bool isRightHandHabit();
	int32 GetWeaponIDByModelID(PLAYER_EQUIP point);
	bool isCanUpdateEquipByModelID(PLAYER_EQUIP point);
	bool isCanUpdatePartModelByModelID(BODY_PART_MODEL part);
	
	int32 GetFashionEquipParth(PLAYER_EQUIP point);
	int32 GetFashionHead(BODY_PART_MODEL part);

	void EquipItem_BodyLocator(
		int32_t nEquipId,
		int32_t nWeaponId,
		ENUM_WEAPON_LOCATOR_TYPE loc,
		bool bUpdateWeaponAnimType = false);
	void EquipItem_BodyPart(PLAYER_EQUIP nPart, int32 nID);

	void SetBodyEquipEffect(int32 nEquipId, PLAYER_EQUIP nPart);
	void SetBodyEquipEffect(
		PLAYER_EQUIP nPart,
		LPCTSTR szBindPoint,
		LPCTSTR szEffect);
	void AddEquipEffect(int32 nEquipId, PLAYER_EQUIP eEquipType);

	bool IsRightHandHabit();

	void SetWeaponActionName(LPCSTR szDown, LPCSTR szUp);

	void DelEquipEffect(PLAYER_EQUIP nPart);

	void UnEquipItem(PLAYER_EQUIP nPart, bool bUseDefaultEquip = true);
public:
	virtual void UpdateCharBaseData(void);
	virtual void UpdateModel_WeaponActionSet(void);
	virtual void UpdateModel_Visible();
	virtual int32 AnalyseCharModel(void)const;
	virtual void UpdateEquip(PLAYER_EQUIP point);

	virtual bool UpdateFashion();

	virtual void update(float deltatime);
private:
	// 模型更新
	ModelPartDataList m_ModelPartDateList;

	/// CharRace表中的定义
	const _TABLE_CHAR_RACE* m_pCharRace;

	// 装备上的特效列表
	typedef std::map<int32, std::vector<String> > EquipEffectMap;

	EquipEffectMap m_EquipEffectMap;

	// 武器动作名
	String	m_strWeaponActorFile_Down;
	String	m_strWeaponActorFile_Up;

	std::vector<Orphigine::Impact*> mPathEffect;

	CDirectlyEffectMgr* mDirectlyImpact = nullptr;
};