#pragma once
#include "net/net_message.h"
class CSQuestSubmit : public NetPacket
{
public:
	CSQuestSubmit();
	~CSQuestSubmit();

	virtual bool process();

	void setPlayerId(int32_t playerId);
	void setMapId(int32_t mapId);
	void setScriptId(int32_t scriptId);
	void setTargetId(int32_t targetId);
	void setSelectRadioId(int32_t radioId);
private:
	int32_t mPlayerId;
	int32_t mMapId;
	int32_t mScriptId;
	int32_t mTargetId;
	int32_t mRadioId;
};