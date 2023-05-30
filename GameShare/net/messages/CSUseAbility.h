#pragma once
#include "net/net_message.h"
class CSUseAbility : public NetPacket
{
public:
	CSUseAbility();
	~CSUseAbility();

	virtual bool process();
	void setPlayerId(int32_t id);
	void setMapId(int32_t id);
	void setAbilityId(int32_t id);
	void setPlatformGUID(int32_t id);
	void setPrescriptionId(int32_t id);

private:
	int32_t mPlayerId;
	int32_t mMapId;

	int32_t mAbilityId;
	int32_t mObjectGuid;
	int32_t mPrescriptionId;

};