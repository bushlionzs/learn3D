#pragma once

#include "net/net_message.h"

class SCUseEquipResult : public NetPacket
{
public:
	SCUseEquipResult();
	virtual ~SCUseEquipResult();

	virtual bool process();
	void setResult(int32_t result);
	void setEquipPoint(int32_t p);
	void setBagIndex(int32_t bagIndex);
private:
	int32_t mResult = -1;
	int32_t mEquipPoint = -1;
	int32_t mBagIndex = -1;
};