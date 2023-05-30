#pragma once

#include "net/net_message.h"


class SCDetailItemList : public NetPacket
{
public:
	SCDetailItemList();
	~SCDetailItemList();

	virtual bool process();

	void setObjectId(int32_t id);

	void addItem(int32_t part, SItem& item);
private:
	int32_t mObjectId = -1;
	std::map<int32_t, SItem> mItemMap;
};