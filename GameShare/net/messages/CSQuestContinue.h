#pragma once
#include "net/net_message.h"
class CSQuestContinue : public NetPacket
{
public:
	CSQuestContinue();
	~CSQuestContinue();

	virtual bool process();

	void setPlayerId(int32_t playerId);
	void setMapId(int32_t mapId);
	void setTargetId(int32_t objId);
	void setIdScript(int32_t idScript);
private:
	int32_t mPlayerId;
	int32_t mMapId;
	int32_t mTargetId;
	int32_t mIdScript;
};