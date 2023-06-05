#include "stdafx.h"
#include "SCCharHumanBaseAttrib.h"


SCCharHumanBaseAttrib::SCCharHumanBaseAttrib():
	NetPacket(SC_DEL_QUEST)
{

}

SCCharHumanBaseAttrib::~SCCharHumanBaseAttrib()
{

}

void SCCharHumanBaseAttrib::setPlayerId(int32_t playerId)
{
	mPlayerId = playerId;
}



