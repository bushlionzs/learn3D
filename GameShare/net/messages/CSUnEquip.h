#pragma once

#include "net/net_message.h"

class CSUnEquip : public NetPacket
{
public:
	CSUnEquip();
	virtual ~CSUnEquip();

	virtual bool process();

	void setPlayerId(int32_t id);
	void setMapId(int32_t id);
	void setEquipPoint(int32_t p);
	void setBagIndex(int32_t bagIndex);
private:
	int32_t mPlayerId = -1;
	int32_t mMapId = -1;
	int32_t mEquipPoint = -1;
	int32_t mBagIndex = -1;
};