#pragma once
#include "net/net_message.h"
class SCCharMove : public NetPacket
{
public:
	SCCharMove();
	~SCCharMove();

	virtual bool process();

	void setObjectID(uint32_t objID);
	uint32_t getObjectID();

	void setHandleID(int32_t handle);
	void setTargetPos(const GLPos*);
	void setStopInfo(const GLPos*);
private:
	uint32_t mObjectID = 0;
	int32_t  mHandleID = -1;
	GLPos    mTargetPos;
	GLPos    mStopPos;
	bool mHaveStopInfo = false;
	bool mHaveMoveInfo = false;
};