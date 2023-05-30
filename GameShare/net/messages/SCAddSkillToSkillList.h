#pragma once
#include "net/net_message.h"
class SCAddSkillToSkillList : public NetPacket
{
public:
	SCAddSkillToSkillList();
	~SCAddSkillToSkillList();

	virtual bool process();

	void setObjectId(int32_t id);
	void setSpell(_PLAYER_SPELL& spell);
private:
	int32_t mObjectId = -1;
	_PLAYER_SPELL mSpell;
};