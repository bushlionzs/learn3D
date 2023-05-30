#pragma once
#include "net/net_message.h"
class SCDetailAbilityInfo : public NetPacket
{
public:
	SCDetailAbilityInfo();
	~SCDetailAbilityInfo();

	virtual bool process();

	void setObjectId(int32_t id);
	void setSceneId(int32_t id);

	void setAbility(_PLAYER_ABILITY const& ability, int32 id, int32 nextLevel, int32 nextExp, int32 nextMoney);
	void setPrescrList(const char* paPrescr);

private:
	int32_t mObjectId = -1;
	int32_t mSceneId = -1;

	uint32_t		m_wNumAbility = 0;
	uchar		m_uAbilityIDList[MAX_CHAR_ABILITY_NUM];
	_PLAYER_ABILITY	m_aAbility[MAX_CHAR_ABILITY_NUM];
	char		m_aPrescr[MAX_CHAR_PRESCRIPTION_BYTE];
	int32		m_NextNeedLevel[MAX_CHAR_ABILITY_NUM];
	int32		m_NextNeedMoney[MAX_CHAR_ABILITY_NUM];
	int32		m_NextNeedExp[MAX_CHAR_ABILITY_NUM];
};