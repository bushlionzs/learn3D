#pragma once
#include "net/net_message.h"
class SCTargetListAndHitFlags : public NetPacket
{
private:
	int32_t mObjId;
	int32_t mLogicCount;
	int32_t mSkillId;
	std::vector<int32_t> mTargetList;
	float mPositionX;
	float mPositionZ;
public:
	SCTargetListAndHitFlags();
	~SCTargetListAndHitFlags();

	virtual bool process();

	void setObjId(int32_t id);
	void setObjPosition(float x, float z);
	void setLogicCout(int32_t logicCount);
	void setSkillId(int32_t skillId);
	void addTargetId(int32_t targetId);
};