#pragma once
#include "net/net_message.h"
class CSEventRequest : public NetPacket
{
public:
	CSEventRequest();
	~CSEventRequest();

	virtual bool process();

	void setPlayerId(int32_t playerId);
	void setMapId(int32_t mapId);
	void setidExIndex(int32_t exIndex);
	void setidScript(int32_t idScript);
	void setTargetId(int32_t targetId);
private:
	int32_t mPlayerId;
	int32_t mMapId;
	int32_t mTargetId;
	int32_t mExindex;
	int32_t midScript;
};