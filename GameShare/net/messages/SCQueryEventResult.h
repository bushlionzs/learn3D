#pragma once
#include "net/net_message.h"
#include "StructCommandScript.h"



class SCQueryEventResult : public NetPacket
{
public:
	SCQueryEventResult();
	~SCQueryEventResult();

	virtual bool process();

	void setObjectId(uint32_t id);
	uint32_t getObjectId();
public:
	SScriptParamEventList mParamEventList;
private:
	uint32_t mObjectID;
};