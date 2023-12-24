#pragma once

#include "GameSingleton.h"
#include "GameDataDefine.h"

class KItem;
class KObject;
class GameDataManager :public GameSingleton<GameDataManager>
{
public:
	GameDataManager();
	~GameDataManager();

	void UserEquip_SetItem(
		PLAYER_EQUIP ptEquip,
		KItem* pEquipItem,
		bool bClearOld);

	//bag
	void UserBag_Clear();
	void UserBag_SetItem(
		int32 nBagIndex,
		KItem* pItem,
		bool bClearOld = true,
		bool reCalulate = false);

	//skill

	void SetMyDefaultSkillID(int32_t skillId);

	uint64_t GetSpecialCoolDown();

	int32 GetCoolDownGroupTime(int32 nCoolDownID);

	int32_t GetCommonCoolDown();

	//camp
	eRELATION GetCampType(
		KObject* pObj_A, KObject* pObj_B);

	const std::vector<KItem*>& getUserBag()
	{
		return m_vUserBag;
	}
private:
	/* 玩家装备实例数组 */
	std::vector<KItem*> m_vUserEquip;

	/*
	 * 主角背包列表 ;
	 * 玩家背包装备实例数组
	 */
	std::vector<KItem*> m_vUserBag;

	/* 冷却时间组 */
	GDataDef::VECTOR_COOLDOWN			m_CoolDownGroup;
	GDataDef::VECTOR_COOLDOWN			m_PetSkillCoolDownGroup;
};