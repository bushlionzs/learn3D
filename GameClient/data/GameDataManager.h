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
	/* ���װ��ʵ������ */
	std::vector<KItem*> m_vUserEquip;

	/*
	 * ���Ǳ����б� ;
	 * ��ұ���װ��ʵ������
	 */
	std::vector<KItem*> m_vUserBag;

	/* ��ȴʱ���� */
	GDataDef::VECTOR_COOLDOWN			m_CoolDownGroup;
	GDataDef::VECTOR_COOLDOWN			m_PetSkillCoolDownGroup;

	QuestManager mQuestManager;

	std::map<int32_t, std::string> m_QuestFileMap;		/* ��������ű��б� */
};