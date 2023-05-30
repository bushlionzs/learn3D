#pragma once
#include "net/net_message.h"
class SCAbilitySuccess : public NetPacket
{
public:
	SCAbilitySuccess();
	~SCAbilitySuccess();

	virtual bool process();
	void setPlayerId(int32_t id);
	void setMapId(int32_t id);
	void setAbilityId(int32_t id);
	void setPrescriptionId(int32_t id);
	void setResult(int32_t res);
private:
	int32_t mPlayerId;
	int32_t mMapId;

	int32_t mAbilityId;
	int32_t mPrescriptionId;
	int32_t mResultCode;
	int32_t mItemSerial = INVALID_ID;
};