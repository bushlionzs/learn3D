#pragma once

#include "net/net_message.h"

class SCNewItem : public NetPacket
{
public:
	SCNewItem();
	virtual ~SCNewItem();

	virtual bool process();
	void setObjId(int32_t id);
	void setSceneId(int32_t id);
	void setItemIndex(int32_t itemIndex);
	void setItemCount(int32_t itemCount);
	void setPosition(float x, float z);
private:
	int32_t mObjId = -1;
	int32_t mSceneId = -1;
	int32_t mItemIndex = -1;
	int32_t mItemCount = 0;

	float mPositionX;
	float mPositionZ;
};