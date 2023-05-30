#include "stdafx.h"
#include "SCDetailSkillList.h"
#include "server/server_manager.h"

SCDetailSkillList::SCDetailSkillList():
	NetPacket(SC_CHARACTER_MOVE)
{

}

SCDetailSkillList::~SCDetailSkillList()
{

}

bool SCDetailSkillList::process()
{
	KObject* pObj = (KObject*)OBJECT_MANAGER_PTR->FindServerObject(mPlayerId);

	if (nullptr == pObj || FALSE == pObj->CheckClassType(GET_CLASS(KCharacter)))
	{
		return false;
	}

	KCharacter* pChar = (KCharacter*)pObj;

	/* 清空所有技能 */
	pChar->GetCharacterData()->Skill_CleanAll();

	const CGameTable* pTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_GIFT_LEARN);


	int32_t count = mSkillList.size();
	/* 刷新到用户数据 */
	for (int32_t i = 0; i < count; i++)
	{
		const _PLAYER_SPELL& pOwnerSkill = mSkillList[i];

		// 天赋
		if (pTable)
		{
			const _TABLE_GIFT_LEARN* pLearnData = (const _TABLE_GIFT_LEARN*)pTable->GetFieldDataByIndex(pOwnerSkill.m_nSkillID);
			if (pLearnData)
			{
				pChar->GetCharacterData()->Set_AttrGift(pOwnerSkill.m_nSkillID, pOwnerSkill.m_nLevel);
				continue;
			}
		}
		// 技能
		pChar->GetCharacterData()->Set_Skill(pOwnerSkill.m_nSkillID, TRUE);
		pChar->GetCharacterData()->Set_SkillLevel(pOwnerSkill.m_nSkillID, pOwnerSkill.m_nLevel);
	}

	if (OBJECT_MANAGER_PTR->GetMySelf() == pChar)
	{
		/* 设置第一个技能为默认技能 */
		const _PLAYER_SPELL* pDefaultSkill = mSkillList.data();
		if (pDefaultSkill)
		{
			GAME_DATA_SKILL_PTR->SetMyDefaultSkillID(pDefaultSkill->m_nSkillID);
		}
		else
		{
			GAME_DATA_SKILL_PTR->SetMyDefaultSkillID(INVALID_ID);
		}
		/* 刷新到UI */
		COMMAND_SYS_PTR->AddCommand(GCD_SKILL_UPDATE);
	}
	return true;
}


void SCDetailSkillList::setPlayerId(uint32_t id)
{
	mPlayerId = id;
}

void SCDetailSkillList::setSkillList(int32_t count, const _PLAYER_SPELL* paSkill)
{
	mSkillList.reserve(count);

	for (int32_t i = 0; i < count; i++)
	{
		mSkillList.push_back(*paSkill);
		paSkill++;
	}
}