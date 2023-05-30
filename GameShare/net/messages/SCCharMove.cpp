#include "stdafx.h"
#include "SCCharMove.h"
#include "server/server_manager.h"

SCCharMove::SCCharMove():
	NetPacket(SC_CHARACTER_MOVE)
{

}

SCCharMove::~SCCharMove()
{

}

bool SCCharMove::process()
{
	CMap * pScene = (CMap*)(SCENE_MANAGER_PTR->GetActiveScene());
	if (NULL == pScene)
	{
		return false;
	}

	/* 检查位置是否合法 */
	vector2 vTargetPos = vector2(mTargetPos.m_fX, mTargetPos.m_fZ);
	if (NULL == pScene->IsValidPosition(vTargetPos))
	{
		return false;
	}

	KObject* pObj = (KObject*)OBJECT_MANAGER_PTR->FindServerObject(mObjectID);
	if (pObj == NULL)
	{
		return false;
	}

	KCharacter* pCharObj = (KCharacter*)pObj;
	
	if (pCharObj->GetCharacterType() == CHAR_BASE_TYPE_ME)
	{
		return false;
	}
	
	/* 停止信息 */
	if (mHaveStopInfo)
	{
		ObjectCmd	cmdTemp;

		cmdTemp.m_wID = OBJ_CMD_STOP_MOVE;
		cmdTemp.nParam[0] = mHandleID - 1;
		cmdTemp.nParam[1] = 0;
		cmdTemp.fParam[2] = mStopPos.m_fX;
		cmdTemp.fParam[3] = mStopPos.m_fZ;
		cmdTemp.nParam[4] = FALSE;

		pObj->AddCommand(&cmdTemp);
	}

	/* 移动信息 */
	if (mHaveMoveInfo)
	{
		/* 立即瞬移到位置 */
		if (false)
		{
			/* 停止移动 */
			
			pCharObj->StopMove();

			/* 设置位置 */
			ObjectCmd	cmdTemp;
			cmdTemp.m_wID = OBJ_CMD_TELEPORT;
			cmdTemp.fParam[0] = mTargetPos.m_fX;
			cmdTemp.fParam[1] = mTargetPos.m_fZ;
			pObj->AddCommand(&cmdTemp);
		}

		/* 移动到位置 */
		else
		{
			ObjectCmd	cmdTemp;
			cmdTemp.m_wID = OBJ_CMD_MOVE;
			cmdTemp.uParam[0] = 0;
			cmdTemp.nParam[1] = mHandleID;
			cmdTemp.nParam[2] = 1;
			cmdTemp.pParam[3] = &mTargetPos;
			cmdTemp.bParam[4] = TRUE;
			pObj->AddCommand(&cmdTemp);
		}
	}
	return true;
}

void SCCharMove::setObjectID(uint32_t objID)
{
	mObjectID = objID;
}

uint32_t SCCharMove::getObjectID()
{
	return mObjectID;
}

void SCCharMove::setHandleID(int32_t handle)
{
	mHandleID = handle;
}

void SCCharMove::setTargetPos(const GLPos* pos)
{
	mTargetPos = *pos;
	mHaveMoveInfo = true;
}

void SCCharMove::setStopInfo(const GLPos* pos)
{
	mStopPos = *pos;
	mHaveStopInfo = true;
}