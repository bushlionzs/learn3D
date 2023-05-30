#include "stdafx.h"
#include "SCNewBeastie.h"
#include "game_world.h"
SCNewBeastie::SCNewBeastie()
	:NetPacket(SC_NEW_BEASTIE)
{

}

SCNewBeastie::~SCNewBeastie()
{

}


bool SCNewBeastie::process()
{
	CMap* pMap = SCENE_MANAGER_PTR->GetActiveScene();
	if (pMap == nullptr)
	{
		return false;
	}

	if (!pMap->IsValidPosition(vector2(mPositionX, mPositionZ)))
	{
		return false;
	}
	KCharacter_NPC* pObj = (KCharacter_NPC*)(OBJECT_MANAGER_PTR->FindServerObject(mObjID));

	vector3			fvGame;
	ENGINE_INTERFACE_PTR->PositionAxisTrans
	(
		GAT_GAME,
		vector3(mPositionX, 0.0f, mPositionZ),
		GAT_SCENE,
		fvGame
	);

	if (pObj == nullptr)
	{
		pObj = (KCharacter_NPC*)(OBJECT_MANAGER_PTR->NewPlayerBeastie(mObjID));
		pObj->Initialize(fvGame, vector3(0.f, mDir, 0.f));
	}
	else
	{
		vector2 mapPos(fvGame.x, fvGame.z);
		pObj->CalculateNodePos(mapPos);
		pObj->SetFaceDir(mDir);
		pObj->Reset();
	}

	pObj->SetNpcType(NPC_TYPE_MONSTER);
	pObj->GetCharacterData()->Set_MoveSpeed(mMoveSpeed);


	if (mMoving)
	{
		GLPos	posTarget;
		posTarget.m_fX = mTargetX;
		posTarget.m_fZ = mTargetZ;

		ObjectCmd	cmdTemp;
		cmdTemp.m_wID = OBJ_CMD_MOVE;
		cmdTemp.uParam[0] = 0;
		cmdTemp.nParam[1] = mHandleId;
		cmdTemp.nParam[2] = 1;
		cmdTemp.pParam[3] = &posTarget;
		cmdTemp.bParam[4] = TRUE;
		pObj->AddCommand(&cmdTemp);
	}
	else
	{
		ObjectCmd	cmdTemp;
		cmdTemp.m_wID = OBJ_CMD_IDLE;
		cmdTemp.fParam[0] = fvGame.x;
		cmdTemp.fParam[1] = fvGame.z;
		cmdTemp.bParam[2] = FALSE;

		pObj->AddCommand(&cmdTemp);
	}
	

	/* 放入Ask队列 */
	OBJECT_MANAGER_PTR->GetLoadQueue()->TryAddLoadTask(mObjID, KObjectLoadQueue::OT_BEASTIE);

	
	return true;
}

void SCNewBeastie::setObjID(uint32_t id)
{
	mObjID = id;
}

void SCNewBeastie::setPosition(float x, float z)
{
	mPositionX = x;
	mPositionZ = z;
}

void SCNewBeastie::setDir(float dir)
{
	mDir = dir;
}

void SCNewBeastie::setSpeed(float speed)
{
	mMoveSpeed = speed;
}

void SCNewBeastie::setHandleId(int32_t handleId)
{
	mMoving = true;
	mHandleId = handleId;
}

void SCNewBeastie::setTargetPosition(float x, float z)
{
	mTargetX = x;
	mTargetZ = z;
}
