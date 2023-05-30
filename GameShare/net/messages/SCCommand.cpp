#include "stdafx.h"
#include "SCCommand.h"

SCCommand::SCCommand():
    NetPacket(SC_COMMAND)
{

}

SCCommand::~SCCommand()
{

}

bool SCCommand::process()
{
    GAME_DATA_QUEST_PTR->ProcessCommand_(&mSXParam, mUIIndex);
    return true;
}

void SCCommand::setUIIndex(int32_t uiIndex)
{
    mUIIndex = uiIndex;
}

void SCCommand::setParam(SXParam& param)
{
    mSXParam = param;
}