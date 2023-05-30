#include "stdafx.h"
#include "SCAddSkillToSkillList.h"
#include "server/server_manager.h"

SCAddSkillToSkillList::SCAddSkillToSkillList():
	NetPacket(SC_ADD_SKILL_TO_SKILL_LIST)
{

}

SCAddSkillToSkillList::~SCAddSkillToSkillList()
{

}

bool SCAddSkillToSkillList::process()
{
	
	if (NULL == OBJECT_MANAGER_PTR->GetMySelf()) return MP_CONTINUE;
	if (NULL == OBJECT_MANAGER_PTR->GetMySelf()->GetCharacterData()) return MP_CONTINUE;

	/* 确认是自己的数据 */
	KCharacter_Me* pMySelf = OBJECT_MANAGER_PTR->GetMySelf();
	if (pMySelf->GetServerID() != mObjectId)
	{
		return false;
	}

	pMySelf->GetCharacterData()->Set_Skill(mSpell.m_nSkillID, TRUE);
	pMySelf->GetCharacterData()->Set_SkillLevel(mSpell.m_nSkillID, mSpell.m_nLevel);

	/* 刷新到UI */
	COMMAND_SYS_PTR->AddCommand(GCD_SKILL_UPDATE);
	return true;
}

void SCAddSkillToSkillList::setObjectId(int32_t id)
{
	mObjectId = id;
}

void SCAddSkillToSkillList::setSpell(_PLAYER_SPELL& spell)
{
	mSpell = spell;
}

