#pragma once

#include "net/net_message.h"
class CSSwapItem : public NetPacket
{
public:
	CSSwapItem();
	virtual ~CSSwapItem();

	virtual bool process();
	void setPlayerId(int32_t id);
	void setMapId(int32_t id);
	void setObjId(int32_t id);
	void setSourcePos(int32_t pos);
	void setDestPos(int32_t pos);
private:
	int32_t mPlayerId;
	int32_t mMapId;
	int32_t mObjId;
	int32_t mSourcePos;
	int32_t mDestPos;
};