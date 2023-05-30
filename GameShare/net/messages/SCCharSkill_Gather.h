#pragma once
#include "net/net_message.h"
class SCCharSkill_Gather : public NetPacket
{
public:
	SCCharSkill_Gather();
	~SCCharSkill_Gather();

	virtual bool process();

	void setObjId(int32_t id);
	void setLogicCount(int32_t logicCount);
	void setSkillDataId(int32_t id);
	void setUserPosition(const GLPos* pos);
	void setTargetId(int32_t id);
	void setTargetPosition(const GLPos* pos);
	void setDir(float dir);
	void setTotalTime(Time_t total);
private:
	int32_t mObjId = -1;
	int32_t mLogicCount;
	int32_t mSkillDataId;
	GLPos mUserPosition;
	int32_t mTargetId;
	GLPos mTargetPos;
	float mDir;
	Time_t mTotalTime;
};