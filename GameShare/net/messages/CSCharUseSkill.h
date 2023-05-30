#pragma once
#include "net/net_message.h"
class CSCharUseSkill : public NetPacket
{
public:
	CSCharUseSkill();
	~CSCharUseSkill();

	virtual bool process();
	void setPlayerId(int32_t id);
	void setSkillID(int32_t id);
	void setTargetID(int32_t id);
	void setTargetPos(float x, float z);
	void setCharDir(float dir);
	void setGuidTarget(GUID_t guidtarget);
	void setMapID(int32_t id);
private:
	int32_t mPlayerId = -1;
	int32_t mSkillID = -1;
	uint32_t mTargetID = 0;
	uint32_t mMapID = 87;
	GLPos mTargetPos;
	float mDir = 0.0f;
	GUID_t mGuidTarget;
	int32_t mHurtDelayTime = 0;
};