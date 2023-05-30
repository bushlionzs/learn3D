#pragma once
#include "net/net_message.h"
class SCNewItemBox : public NetPacket
{
public:
	SCNewItemBox();
	~SCNewItemBox();

	virtual bool process();

	void setObjectId(int32_t id);
	void setObjType(int32_t type);
	void setOwner(GUID_t id);
	void setWorldPos(const GLPos* pos);
	void setDropMonsterId(int32_t id);
	void setSceneId(int32_t id);
private:
	int32_t mObjectId = -1;
	int32_t mType;
	GUID_t  mOwnerId;
	int32_t mSceneId = -1;
	GLPos mPos;
	int32_t mDropMonsterId;
};