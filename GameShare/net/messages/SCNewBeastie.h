#pragma once

#include "net/net_message.h"

class SCNewBeastie : public NetPacket
{
public:
	SCNewBeastie();
	virtual ~SCNewBeastie();

	virtual bool process();

	void setObjID(uint32_t id);
	void setPosition(float x, float z);
	void setDir(float dir);
	void setSpeed(float speed);

	void setHandleId(int32_t handleId);
	void setTargetPosition(float x, float z);
private:
	uint32_t mObjID;
	std::string mName;
	float mPositionX;
	float mPositionZ;
	float mDir;
	float mMoveSpeed;
	bool  mMoving = false;
	int32_t mHandleId;
	float mTargetX;
	float mTargetZ;
};