#pragma once

#include "net/net_message.h"

class CSTick : public NetPacket
{
public:
	CSTick();
	virtual ~CSTick();

	virtual bool process();

	void setObjId(int32_t id);
	void setMapId(int32_t id);
	void setPosition(float x, float z);

	void setPlayerInfo(int32_t id, float x, float z);
private:
	int32_t mObjId = -1;
	int32_t mMapId = -1;
	float mPositionX;
	float mPositionZ;

	int32_t mPlayerId = -1;
	float mPlayerPositionX;
	float mPlayerPositionZ;
};