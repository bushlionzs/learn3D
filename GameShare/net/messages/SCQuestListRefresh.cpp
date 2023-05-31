#include "stdafx.h"
#include "SCQuestListRefresh.h"


SCQuestListRefresh::SCQuestListRefresh():
	NetPacket(SC_QUESTLIST_REFRESH)
{

}

SCQuestListRefresh::~SCQuestListRefresh()
{

}

bool SCQuestListRefresh::process()
{
	
	
	return true;
}

void SCQuestListRefresh::setObjectId(int32_t id)
{
	mObjectId = id;
}

void SCQuestListRefresh::setSceneId(int32_t id)
{
	mSceneId = id;
}

