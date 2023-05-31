#include "stdafx.h"
#include "SCSkillUpgrade.h"


SCSkillUpgrade::SCSkillUpgrade():
	NetPacket(SC_SKILL_UPGRADE)
{

}

SCSkillUpgrade::~SCSkillUpgrade()
{

}

bool SCSkillUpgrade::process()
{
	//KCharacter_Me* pMySelf = OBJECT_MANAGER_PTR->GetMySelf();
	//if (NULL == pMySelf)
	//	return false;

	//// 学习成功
	//if (false == mSuccess)
	//	return false;

	//switch (mType)
	//{
	//case TYPE_SKILL:
	//{
	//	const SkillDetail* skill = pMySelf->GetCharacterData()->Get_Skill(mSkillId);
	//	if (NULL == skill)
	//	{
	//		pMySelf->GetCharacterData()->Set_Skill(mSkillId, TRUE);
	//	}
	//	pMySelf->GetCharacterData()->Set_SkillLevel(mSkillId, mSkillLevel);

	//	/* 通知技能框刷新 */
	//	COMMAND_SYS_PTR->AddCommand(GCD_SKILL_UPDATE);
	//}
	//break;
	//case TYPE_INHERENCE:
	//{
	//	pMySelf->GetCharacterData()->Set_AttrGift(mSkillId, mSkillLevel);
	//	COMMAND_SYS_PTR->AddCommand(GCD_UPDATE_SELF_GIFT);
	//}
	//break;
	//default:
	//	break;
	//}
	
	return true;
}

void SCSkillUpgrade::setObjectId(int32_t id)
{
	mObjectId = id;
}

void SCSkillUpgrade::setSkillId(int32_t id)
{
	mSkillId = id;
}

void SCSkillUpgrade::setSkillLevel(int32_t level)
{
	mSkillLevel = level;
}

void SCSkillUpgrade::setSuccess(bool success)
{
	mSuccess = success;
}

void SCSkillUpgrade::setType(int32_t type)
{
	mType = type;
}

