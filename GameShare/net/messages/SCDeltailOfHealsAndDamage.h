#pragma once

#include "net/net_message.h"
class SCDeltailOfHealsAndDamage : public NetPacket
{
public:
	SCDeltailOfHealsAndDamage();
	~SCDeltailOfHealsAndDamage();

	bool process();

	void setHpModification(int32 nValue);
	void setObjId(int32_t id);
	void setSenderId(int32_t id);
	void setSenderLogicCount(int32_t count);
	void setCriticalHit();
	void setDeathBlow();
private:
	int32_t m_nHpModification = 0;
	int32_t m_ObjId = -1;
	int32_t mSenderId = -1;
	int32_t mSenderLogicCount = 0;

	bool    mCriticalHit = false;
	bool    mDeathBlow = false;
};