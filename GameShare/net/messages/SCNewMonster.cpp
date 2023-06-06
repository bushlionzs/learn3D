#include "stdafx.h"
#include "SCNewMonster.h"
//#include "game_world.h"
SCNewMonster::SCNewMonster()
	:NetPacket(SC_NEWMONSTER)
{

}

SCNewMonster::~SCNewMonster()
{

}




void SCNewMonster::setObjID(uint32_t id)
{
	mObjID = id;
}

void SCNewMonster::setPosition(float x, float z)
{
	mPositionX = x;
	mPositionZ = z;
}

void SCNewMonster::setDir(float dir)
{
	mDir = dir;
}

void SCNewMonster::setSpeed(float speed)
{
	mMoveSpeed = speed;
}

void SCNewMonster::setHourseID(int32_t id)
{
	mHorseID = id;
}

void SCNewMonster::setWeaponID(int32_t id)
{
	mWeaponID = id;
}

void SCNewMonster::setMonsterType(int32_t type)
{
	mMonsterType = type;
}

void SCNewMonster::setGUID(uint32_t id)
{
	mGUID = id;
}

void SCNewMonster::setRaceID(int32_t id)
{
	mRaceID = id;
}

void SCNewMonster::setName(const char* name)
{
	mName = name;
}

void SCNewMonster::setCampID(int32_t id)
{
	mCampID = id;
}
