#include "stdafx.h"
#include "SCQueryEventResult.h"

SCQueryEventResult::SCQueryEventResult():
	NetPacket(SC_QUERY_EVENT_RESULT)
{

}

SCQueryEventResult::~SCQueryEventResult()
{
	char buffer[128];
	sprintf(buffer, "~SCQueryEventResult:%p\n", this);
	::OutputDebugString(buffer);
}

bool SCQueryEventResult::process()
{
	//GAME_DATA_QUEST_PTR->QuestEventListResponse(&mParamEventList);
	return true;
}

void SCQueryEventResult::setObjectId(uint32_t id)
{
	mObjectID = id;
}

uint32_t SCQueryEventResult::getObjectId()
{
	return mObjectID;
}