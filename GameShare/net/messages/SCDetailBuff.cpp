#include "stdafx.h"
#include "SCDetailBuff.h"
#include "server/server_manager.h"

SCDetailBuff::SCDetailBuff():
	NetPacket(SC_DETAIL_BUFF)
{

}

SCDetailBuff::~SCDetailBuff()
{

}

bool SCDetailBuff::process()
{
	
	if (mEnable && INVALID_ID != mSN)
	{
		_BUFF_EFFECT_INFO	infoBuffImpact;
		infoBuffImpact.m_nReceiverID = mReceiverId;
		infoBuffImpact.m_nSenderID = mSenderId;
		infoBuffImpact.m_nBuffID = mBuffId;
		infoBuffImpact.m_nSkillID = mSkillId;
		infoBuffImpact.m_nSenderLogicCount = mSenderLogicCount;
		infoBuffImpact.m_nSN = mSN;
		infoBuffImpact.m_nTimer = mContinuance;
		infoBuffImpact.m_nDelayTime = mDelayTime;
		infoBuffImpact.m_uCreateTime = GAME_TIME_PTR->GetTimeNow();

		GAME_DATA_SKILL_PTR->BuffEffect_Add(&infoBuffImpact);
	}
	else
	{
		GAME_DATA_SKILL_PTR->BuffEffect_Remove(mSN);
	}
	return true;
}

void SCDetailBuff::setObjectId(int32_t id)
{
	mObjectId = id;
}

void SCDetailBuff::setReceiverId(int32_t id)
{
	mReceiverId = id;
}

void SCDetailBuff::setSenderId(int32_t id)
{
	mSenderId = id;
}

void SCDetailBuff::setEnable(bool enable)
{
	mEnable = enable;
}

void SCDetailBuff::setSkillId(bool id)
{
	mSkillId = id;
}

void SCDetailBuff::setSN(int32_t sn)
{
	mSN = sn;
}

void SCDetailBuff::setBuffId(int32_t id)
{
	mBuffId = id;
}

void SCDetailBuff::setContinuance(int32_t value)
{
	mContinuance = value;
}

void SCDetailBuff::setDelayTime(int32_t delay)
{
	mDelayTime = delay;
}

void SCDetailBuff::setSenderLogicCount(int32_t logicCount)
{
	mSenderLogicCount = logicCount;
}

