#pragma once
#include "net/net_message.h"
class CSPlayerRequestBaseAttrib : public NetPacket
{
public:
	CSPlayerRequestBaseAttrib();
	~CSPlayerRequestBaseAttrib();

	virtual bool process();

	void setTargetId(int32_t id);
	void setPlayerId(int32_t id);
	void setMapId(int32_t id);
private:
	int32_t mTargetId = -1;
	int32_t mPlayerId = -1;
	int32_t mMapId = -1;
};