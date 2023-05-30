#pragma once

#include "net/net_message.h"

class SCNotifyEquip : public NetPacket
{
public:
	SCNotifyEquip();
	virtual ~SCNotifyEquip();

	virtual bool process();

	SItem* getItem();
	void setBagIndex(int32_t index);
private:
	int32_t mBagIndex = -1;
	SItem mItem;
};