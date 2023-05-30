#pragma once

#include "net/net_message.h"

class SCNewMonster : public NetPacket
{
public:
	SCNewMonster();
	virtual ~SCNewMonster();

	virtual bool process();

	void setObjID(uint32_t id);
	void setPosition(float x, float z);
	void setDir(float dir);
	void setSpeed(float speed);
	void setHourseID(int32_t id);
	void setWeaponID(int32_t id);
	void setMonsterType(int32_t type);
	void setGUID(uint32_t id);
	void setRaceID(int32_t id);
	void setName(const char* name);
	void setCampID(int32_t id);
private:
	uint32_t mObjID;
	std::string mName;
	float mPositionX;
	float mPositionZ;
	float mDir;
	float mMoveSpeed;
	int32_t mHorseID = -1;
	int32_t mWeaponID = -1;
	int32_t mMonsterType;
	uint32_t mGUID;
	int32_t mRaceID = -1;
	int32_t mCampID = -1;
};