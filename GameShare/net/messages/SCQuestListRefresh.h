#pragma once
#include "net/net_message.h"
class SCQuestListRefresh : public NetPacket
{
public:
	SCQuestListRefresh();
	~SCQuestListRefresh();

	virtual bool process();

	void setObjectId(int32_t id);
	void setSceneId(int32_t id);
private:
	int32_t mObjectId = -1;
	int32_t mSceneId = -1;
};