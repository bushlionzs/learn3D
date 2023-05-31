#pragma once

#include "net/net_message.h"
#include "StructDB.h"
#include "StructPet.h"
class Player;

class CSManipulatePet : public NetPacket
{
public:
	CSManipulatePet();
	virtual ~CSManipulatePet();

	virtual bool process();

	void setPlayerId(int32_t id);
	void setMapId(int32_t id);
	void setGUID(const SHorseGuid& guid);
	void setManipulateType(ENUM_MANIPULATE_TYPE type);
private:
	void addPassiveSkillToOnwer(Player* pPlayer, _HORSE_DB* pPetDB);
	void startPassiveSkill(SpellID_t iSkillID, Player* pPlayer, int32 iSkillLevel, int32 iIndex);
private:
	int32_t mPlayerId;
	int32_t mMapId;
	SHorseGuid mGUID;
	ENUM_MANIPULATE_TYPE mType;
};