#pragma once

#include "net/net_message.h"
#include "StructItem.h"

class SCItemInfo : public NetPacket
{
public:
	SCItemInfo();
	~SCItemInfo();

	virtual bool process();

	SItem* getItem();
	void setIsNull(bool bnull);
	void setId(int32_t bagIndex);
	void setTips(int32_t tips);
private:
	int32_t mBagIndex = -1;
	SItem mItem;
	bool mNull = false;
	int32_t mTips = 1;
};