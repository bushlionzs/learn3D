#include "stdafx.h"
#include "SCDetailAbilityInfo.h"

SCDetailAbilityInfo::SCDetailAbilityInfo():
	NetPacket(SC_DETAIL_ABILITY_INFO)
{

}

SCDetailAbilityInfo::~SCDetailAbilityInfo()
{

}

bool SCDetailAbilityInfo::process()
{
	////生活技能刷新 ;
	//_ARG_SCLIENT_LIFEABILITY	arg;

	//for (int32 i = 0; i < m_wNumAbility; i++)
	//{
	//	arg.m_ID = m_uAbilityIDList[i];
	//	arg.m_nLevel = m_aAbility[i].m_Level;
	//	arg.m_nExp = m_aAbility[i].m_Exp;
	//	arg.m_nNextExp = m_NextNeedExp[i];
	//	arg.m_nNextLevel = m_NextNeedLevel[i];
	//	arg.m_nNextMoney = m_NextNeedMoney[i];

	//	OBJECT_MANAGER_PTR->GetMySelf()->GetCharacterData()->Set_LifeAbility(arg);
	//}

	//// 生活技能配方表刷新 ;
	//for (int32 i = 0; i < MAX_SKILL_PRESCRIPTION_NUM; i++)
	//{
	//	BOOL	bCando = ((BYTE)((char*)(&m_aPrescr[0])[i >> 3]) & (1 << (i % 8))) != 0;
	//	if (!bCando) continue;

	//	/* 配方id从“1”开始 */
	//	OBJECT_MANAGER_PTR->GetMySelf()->GetCharacterData()->Set_Prescr(i, TRUE);
	//}
	return true;
}

void SCDetailAbilityInfo::setObjectId(int32_t id)
{
	mObjectId = id;
}

void SCDetailAbilityInfo::setSceneId(int32_t id)
{
	mSceneId = id;
}

void SCDetailAbilityInfo::setAbility(_PLAYER_ABILITY const& ability, int32 id, int32 nextLevel, int32 nextExp, int32 nextMoney)
{
	KCheck(m_wNumAbility >= 0 && m_wNumAbility < MAX_CHAR_ABILITY_NUM);

	m_aAbility[m_wNumAbility] = ability;
	m_uAbilityIDList[m_wNumAbility] = id;
	m_NextNeedLevel[m_wNumAbility] = nextLevel;
	m_NextNeedExp[m_wNumAbility] = nextExp;
	m_NextNeedMoney[m_wNumAbility] = nextMoney;

	++m_wNumAbility;
}

void SCDetailAbilityInfo::setPrescrList(const char* paPrescr)
{
	memcpy(m_aPrescr, paPrescr, sizeof(char) * MAX_CHAR_PRESCRIPTION_BYTE);
}
