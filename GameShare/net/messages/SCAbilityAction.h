#pragma once
#include "net/net_message.h"
class SCAbilityAction : public NetPacket
{
public:
	enum 
	{ 
		ABILITY_BEGIN = 1, 
		ABILITY_END, 
	};
public:
	SCAbilityAction();
	~SCAbilityAction();

	virtual bool process();

	void setObjID(int32_t id);
	void setLogicCount(int32_t logicCount);
	void setAbilityId(int32_t id);
	void setPrescriptionId(int32_t id);
	void setTargetId(int32_t id);
	void setBeginOrEnd(int32_t value);
private:
	int32_t mObjectId = -1;
	int32_t mLogicCount = -1;
	int32_t mAbilityId = -1;
	int32_t mPrescriptionId = -1;
	int32_t mTargetId = -1;
	int32_t mBeginEnd = ABILITY_BEGIN;
};