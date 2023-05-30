#pragma once
#include "net/net_message.h"
class SCOperateResult : public NetPacket
{
public:
	SCOperateResult();
	~SCOperateResult();

	virtual bool process();
	void setPlayerId(int32_t id);
	void setMapId(int32_t id);
	void setResType(int32_t type);
	void setResult(int32_t res);
private:
	int32_t mPlayerId;
	int32_t mMapId;
	int32_t mResType;
	int32_t mResultCode;
};