#pragma once

#include "GameSingleton.h"
#include "GameDataDefine.h"
#include "QuestManager.h"

class KItem;
class KObject;
class GameDataManager :public GameSingleton<GameDataManager>
{
public:
	GameDataManager();
	~GameDataManager();
	bool Initialize();
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
	KItem* UserBag_GetItem(int32_t nBagIndex);
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

	const std::vector<KItem*>& getUserEquip()
	{
		return m_vUserEquip;
	}

	QuestManager* getQuestManager()
	{
		return &mQuestManager;
	}

	const std::string& getQuestFileName(int32_t nID);
private:
	void LoadQuestFile();
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

	QuestManager mQuestManager;

	std::map<int32_t, std::string> m_QuestFileMap;		/* 解析任务脚本列表 */
};