#include "stdafx.h"
#include "SCCharMove.h"
#include "Glpos.h"

class CSCharMove : public NetPacket
{
public:
	CSCharMove();
	~CSCharMove();

	virtual bool process();

	void setObjectId(int32_t id);
	void setMapID(int32_t id);
	void setHandleID(int32_t handle);
	void setTargetPos(const GLPos*);
	void setStopLogicCount(int32_t count);
	void setWorldPos(const GLPos& pos);
private:
	int32_t mObjectId = -1;
	int32_t  mMapID;
	int32_t  mHandleID;
	int32_t  mStopLogicCount;
	GLPos    mTargetPos;
	GLPos    mWorldPos;
};