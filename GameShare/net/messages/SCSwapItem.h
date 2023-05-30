#pragma once

#include "net/net_message.h"
class SCSwapItem : public NetPacket
{
public:
	SCSwapItem();
	virtual ~SCSwapItem();

	virtual bool process();
	void setResult(int32_t result);
	void setSourcePos(int32_t pos);
	void setDestPos(int32_t pos);
private:
	int32_t mResult;
	int32_t mSourcePos;
	int32_t mDestPos;
};