#pragma once

#include "net/net_message.h"

class SCUnEquipResult : public NetPacket
{
public:
	SCUnEquipResult();
	virtual ~SCUnEquipResult();

	virtual bool process();


	void setResult(int32_t result);
	void setPlayerId(int32_t id);
	void setMapId(int32_t id);
	void setEquipPoint(int32_t p);
	void setBagIndex(int32_t bagIndex);
private:
	int32_t mResult = -1;
	int32_t mPlayerId = -1;
	int32_t mMapId = -1;
	int32_t mEquipPoint = -1;
	int32_t mBagIndex = -1;
};