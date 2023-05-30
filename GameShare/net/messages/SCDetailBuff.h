#pragma once
#include "net/net_message.h"
class SCDetailBuff : public NetPacket
{
public:
	SCDetailBuff();
	~SCDetailBuff();

	virtual bool process();

	void setObjectId(int32_t id);
	void setReceiverId(int32_t id);
	void setSenderId(int32_t id);
	void setEnable(bool enable);
	void setSkillId(bool id);
	void setSN(int32_t sn);
	void setBuffId(int32_t id);
	void setContinuance(int32_t value);
	void setDelayTime(int32_t delay);
	void setSenderLogicCount(int32_t logicCount);
private:
	int32_t mObjectId;
	int32_t mReceiverId;
	int32_t mSenderId;
	bool mEnable = false;
	int32_t mSkillId;
	int32_t mSN;
	int32_t mBuffId;
	int32_t mContinuance;
	int32_t mDelayTime;
	int32_t mSenderLogicCount;
};