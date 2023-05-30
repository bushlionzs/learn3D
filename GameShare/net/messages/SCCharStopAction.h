#pragma once
#include "net/net_message.h"
class SCCharStopAction : public NetPacket
{
public:
	SCCharStopAction();
	~SCCharStopAction();

	virtual bool process();

	void setObjectId(int32_t id);
	void setLogicCount(int32_t logicCount);
	void setStopTime(Time_t stopTime);
private:
	int32_t mObjectId = -1;
	int32_t mLogicCount;
	Time_t mStopTime;

};