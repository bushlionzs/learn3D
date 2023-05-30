#pragma once
#include "net/net_message.h"
class SCSkillUpgrade : public NetPacket
{
public:
	SCSkillUpgrade();
	~SCSkillUpgrade();

	virtual bool process();

	void setObjectId(int32_t id);
	void setSkillId(int32_t id);
	void setSkillLevel(int32_t level);
	void setSuccess(bool success);
	void setType(int32_t type);
private:
	int32_t mObjectId;
	int32_t mSkillId;
	int32_t mSkillLevel;
	bool mSuccess;
	int32_t mType;
};