#pragma once

#include "net/net_message.h"

class SCPickItemResult : public NetPacket
{
public:
	SCPickItemResult();
	virtual ~SCPickItemResult();

	virtual bool process();

	void setObjId(int32_t id);
	void setResult(int32_t result);
private:
	int32_t mObjId;
	int32_t mResultCode;
};