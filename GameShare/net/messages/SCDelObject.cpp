#include "stdafx.h"
#include "SCDelObject.h"

SCDelObject::SCDelObject():
	NetPacket(SC_DELETE_OBJECT)
{

}

SCDelObject::~SCDelObject()
{

}

bool SCDelObject::process()
{
	//if (mSceneId != SCENE_MANAGER_PTR->GetActiveSceneID())
	//{
	//	return false;
	//}

	//CMap * pScene = (CMap*)(SCENE_MANAGER_PTR->GetActiveScene());
	//if (NULL == pScene)
	//{
	//	return false;
	//}
	//

	//KObject* pObj = (KObject*)OBJECT_MANAGER_PTR->FindServerObject(mObjectId);
	//if (NULL == pObj)
	//{
	//	return false;
	//}


	//if (pObj == OBJECT_MANAGER_PTR->GetMainTarget())
	//{
	//	GAME_OPERATE_PTR->Object_SelectAsMainTarget(INVALID_ID, 0);
	//}

	///* �������鿴��Ϣ */
	//if (pObj == GAME_DATA_PLAYER_PTR->GetTargetEquip())
	//{
	//	GAME_DATA_PLAYER_PTR->SetTargetEquip(NULL);
	//}

	//// ɾ������
	//OBJECT_MANAGER_PTR->RemoveHostile(mObjectId);

	///* ��ʼ���� */
	//pObj->DieOut();

	//
	///* ȡ������ */
	//OBJECT_MANAGER_PTR->GetLoadQueue()->CancelLoadTask(pObj->GetServerID());

	///* ������������ */
	//OBJECT_MANAGER_PTR->GetDestoryQueue()->TryAddDestoryTask(pObj->GetServerID());
	//
	//
	return true;
}

void SCDelObject::setObjectId(int32_t id)
{
	mObjectId = id;
}

void SCDelObject::setSceneId(int32_t id)
{
	mSceneId = id;
}

