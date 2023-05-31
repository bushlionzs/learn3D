#pragma once
#include "net/net_message.h"
#include "StructDB.h"
class SCRetSkillSetting : public NetPacket
{
public:
	SCRetSkillSetting();
	~SCRetSkillSetting();

	virtual bool process();

	void setObjectId(int32_t id);
	void setPlayerSetting(_PLAYER_SETTING& setting);
	void setIndex(int32_t index);
private:
	int32_t mObjectId = -1;
	_PLAYER_SETTING mPlayerSetting;
	int32_t mIndex;
};