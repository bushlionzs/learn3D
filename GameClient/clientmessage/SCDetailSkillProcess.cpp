#include "stdafx.h"
#include "SCDetailSkillList.h"
#include "KObjectManager.h"
#include "kplayer.h"
#include "KItem.h"
#include "KItemManager.h"
#include "data/GameDataCharacter.h"
#include "data/GameDataManager.h"
#include "GameTableManager.h"
#include "KTable.h"


//bool SCDetailSkillList::process()
//{
//	KObject* pObj = KObjectManager::GetSingleton().getObject(mPlayerId);
//
//	KPlayer* pPlayer = dynamic_cast<KPlayer*>(pObj);
//
//
//	/* 清空所有技能 */
//	pPlayer->GetCharacterData()->Skill_CleanAll();
//
//	const CGameTable* pTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_GIFT_LEARN);
//
//
//	int32_t count = mSkillList.size();
//	/* 刷新到用户数据 */
//	for (int32_t i = 0; i < count; i++)
//	{
//		const _PLAYER_SPELL& pOwnerSkill = mSkillList[i];
//
//		// 天赋
//		if (pTable)
//		{
//			const _TABLE_GIFT_LEARN* pLearnData = (const _TABLE_GIFT_LEARN*)pTable->GetFieldDataByIndex(pOwnerSkill.m_nSkillID);
//			if (pLearnData)
//			{
//				pPlayer->GetCharacterData()->Set_AttrGift(pOwnerSkill.m_nSkillID, pOwnerSkill.m_nLevel);
//				continue;
//			}
//		}
//		// 技能
//		pPlayer->GetCharacterData()->Set_Skill(pOwnerSkill.m_nSkillID, TRUE);
//		pPlayer->GetCharacterData()->Set_SkillLevel(pOwnerSkill.m_nSkillID, pOwnerSkill.m_nLevel);
//	}
//
//
//	/* 设置第一个技能为默认技能 */
//	const _PLAYER_SPELL* pDefaultSkill = mSkillList.data();
//	if (pDefaultSkill)
//	{
//		GameDataManager::GetSingleton().SetMyDefaultSkillID(pDefaultSkill->m_nSkillID);
//	}
//	else
//	{
//		GameDataManager::GetSingleton().SetMyDefaultSkillID(INVALID_ID);
//	}
//
//
//	return true;
//}