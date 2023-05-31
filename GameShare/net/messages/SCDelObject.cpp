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

	///* 清除人物查看信息 */
	//if (pObj == GAME_DATA_PLAYER_PTR->GetTargetEquip())
	//{
	//	GAME_DATA_PLAYER_PTR->SetTargetEquip(NULL);
	//}

	//// 删除敌人
	//OBJECT_MANAGER_PTR->RemoveHostile(mObjectId);

	///* 开始消亡 */
	//pObj->DieOut();

	//
	///* 取消加载 */
	//OBJECT_MANAGER_PTR->GetLoadQueue()->CancelLoadTask(pObj->GetServerID());

	///* 加入消亡队列 */
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

