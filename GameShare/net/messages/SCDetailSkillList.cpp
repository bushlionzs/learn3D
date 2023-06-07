#include "stdafx.h"
#include "SCDetailSkillList.h"

SCDetailSkillList::SCDetailSkillList():
	NetPacket(SC_CHARACTER_MOVE)
{

}

SCDetailSkillList::~SCDetailSkillList()
{

}

void SCDetailSkillList::setPlayerId(uint32_t id)
{
	mPlayerId = id;
}

void SCDetailSkillList::setSkillList(int32_t count, const _PLAYER_SPELL* paSkill)
{
	mSkillList.reserve(count);

	for (int32_t i = 0; i < count; i++)
	{
		mSkillList.push_back(*paSkill);
		paSkill++;
	}
}