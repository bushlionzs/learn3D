#include "stdafx.h"
#include "SCDeltailOfHealsAndDamage.h"

SCDeltailOfHealsAndDamage::SCDeltailOfHealsAndDamage()
	:NetPacket(SC_DETAIL_HEALS_DAMAGE)
{

}

SCDeltailOfHealsAndDamage::~SCDeltailOfHealsAndDamage()
{

}

bool SCDeltailOfHealsAndDamage::process()
{
	//KObject* pObj = (KObject*)(OBJECT_MANAGER_PTR->FindServerObject(m_ObjId));

	//if (nullptr == pObj)
	//	return false;

	//SDamageInfo	infoDamage;
	//infoDamage.m_nSkillID = INVALID_ID;
	//infoDamage.m_nTargetID = m_ObjId;
	//infoDamage.m_nSenderID = mSenderId;
	//infoDamage.m_nSenderLogicCount = mSenderLogicCount;
	//infoDamage.m_nImpactID = INVALID_ID;
	//infoDamage.m_nType = infoDamage.TYPE_HEAL_AND_DAMAGE;

	//infoDamage.m_bDeathblow = mDeathBlow;

	//
	//infoDamage.m_bHealthDirty = TRUE;
	//infoDamage.m_nHealthIncrement = m_nHpModification;



	//infoDamage.m_bIsCriticalHit = mCriticalHit;

	//static LogicEventData*	logicEvent = nullptr;

	//if (logicEvent == nullptr)
	//{
	//	logicEvent = new LogicEventData;
	//}
	//logicEvent->Initialize(mSenderId, mSenderLogicCount, &infoDamage);

	///* 如果是子弹技能就缓冲起来，等待子弹碰撞回调 */
	////if (pPacket->IsHpModificationDirty())
	//{
	//	if (BULLET_ENTITY_MANAGER_PTR->PushDamageEvent(*logicEvent)) return MP_CONTINUE;
	//}

	//if (infoDamage.m_bDeathblow)
	//{
	//	int kk = 0;
	//}
	//ObjectCmd	cmdTemp;
	//cmdTemp.m_wID = OBJ_CMD_LOGIC_EVENT;
	//cmdTemp.pParam[0] = (void*)(&logicEvent);
	//pObj->AddCommand(&cmdTemp);
	return true;
}

void SCDeltailOfHealsAndDamage::setHpModification(int32 nValue)
{
	m_nHpModification = nValue;
}

void SCDeltailOfHealsAndDamage::setObjId(int32_t id)
{
	m_ObjId = id;
}

void SCDeltailOfHealsAndDamage::setSenderId(int32_t id)
{
	mSenderId = id;
}

void SCDeltailOfHealsAndDamage::setSenderLogicCount(int32_t count)
{
	mSenderLogicCount = count;
}

void SCDeltailOfHealsAndDamage::setCriticalHit()
{
	mCriticalHit = true;;
}

void SCDeltailOfHealsAndDamage::setDeathBlow()
{
	mDeathBlow = true;
}