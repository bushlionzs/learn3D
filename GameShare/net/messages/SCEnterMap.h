#pragma once

#include "net/net_message.h"

class SCEnterMap : public NetPacket
{
public:
	SCEnterMap();
	~SCEnterMap();

	//virtual bool process();

	void setActorID(int32_t objId, int32_t serverGuid);
	void setSceneId(int32_t id);
	void setPosition(float x, float z);
private:
	uint32_t mSceneId = 87;
	float mPositionX = 196.578;
	float mPositionZ = 79.62;

	int32_t mGUID;
	int32_t mObjectID;
};