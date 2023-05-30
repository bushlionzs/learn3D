#include "stdafx.h"
#include "SCPickItemResult.h"

SCPickItemResult::SCPickItemResult():
    NetPacket(SC_PICK_ITEM_RESULT)
{

}

SCPickItemResult::~SCPickItemResult()
{

}

bool SCPickItemResult::process()
{
    if (mResultCode == PICK_SUCCESS)
    {
        INPUT_SYS_PTR->SetCaptureType(IC_NONE);
        GAME_CURSOR_PTR->EndUICursor();
        GAME_CURSOR_PTR->SetCursor(CURSOR_NORMAL);
    }
    
    return true;
}

void SCPickItemResult::setObjId(int32_t id)
{
    mObjId = id;
}

void SCPickItemResult::setResult(int32_t result)
{
    mResultCode = result;
}
