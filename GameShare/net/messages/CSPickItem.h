#pragma once

#include "net/net_message.h"

class CSPickItem : public NetPacket
{
public:
	CSPickItem();
	virtual ~CSPickItem();

	virtual bool process();

	void setObjId(int32_t id);
	void setMapId(int32_t id);
	void setPlayerId(int32_t id);
	
private:
	int32_t mObjId = -1;
	int32_t mMapId = -1;
	int32_t mPlayerId = -1;
};