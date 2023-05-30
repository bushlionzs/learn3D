#pragma once
#include "net/net_message.h"
class CSQueryEvent : public NetPacket
{
public:
	CSQueryEvent();
	~CSQueryEvent();

	virtual bool process();

	void setPlayerId(int32_t playerId);
	void setMapId(int32_t mapId);
	void setObjectId(int32_t objID);
	uint32_t getObjectID();
private:
	int32_t mPlayerId;
	int32_t mMapId;
	int32_t mObjectId;
};