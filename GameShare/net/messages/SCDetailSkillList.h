#pragma once
#include "net/net_message.h"
#include "StructSpell.h"
class SCDetailSkillList : public NetPacket
{
public:
	SCDetailSkillList();
	~SCDetailSkillList();

	//virtual bool process();

	void setPlayerId(uint32_t id);
	void setSkillList(int32_t count, const _PLAYER_SPELL* paSkill);


private:
	uint32_t mPlayerId = -1;
	std::vector< _PLAYER_SPELL> mSkillList;
};