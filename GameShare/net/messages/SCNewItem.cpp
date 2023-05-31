#include "stdafx.h"
#include "SCNewItem.h"
//#include "game_world.h"
//#include "object/Manager/KObjManager.h"
//#include "object/OperateObj/KOperate_Loot.h"

SCNewItem::SCNewItem()
	:NetPacket(SC_NEWMONSTER)
{

}

SCNewItem::~SCNewItem()
{

}


bool SCNewItem::process()
{
	//if (SCENE_MANAGER_PTR->GetActiveSceneID() != mSceneId)
	//{
	//	return false;
	//}

	//CMap* pMap = SCENE_MANAGER_PTR->GetActiveScene();
	//
	//KItem* pItemObj = ITEM_MANAGER_PTR->CreateNewItem(mItemIndex);
	//pItemObj->SetTypeOwner(IO_ITEMDROP);
	//pItemObj->SetNumber(mItemCount);

	//if (!GAME_DATA_ITEM_PTR->ItemDrop_SetItem(mObjId, pItemObj))
	//{
	//	return false;
	//}

	//KOperate_Loot* pDrop = (KOperate_Loot*)OBJECT_MANAGER_PTR->CreateNewObject(GET_CLASS(KOperate_Loot), mObjId);

	//if (pDrop)
	//{
	//	pDrop->SetDropCanPick(true);


	//	pDrop->Initialize(vector3(mPositionX, 0.f, mPositionZ), vector3(0.f, 0.f, 0.f));
	//	// ÉèÖÃÎ»ÖÃ
	//	pDrop->CalculateNodePos(vector2(mPositionX, mPositionZ));
	//	// ÉèÖÃµôÂäÏäµÄ¹éÊô
	//	pDrop->SetOwnerGUID(nullptr);
	//	pDrop->SetProtectTime(0);
	//	pDrop->SetStartTime(GAME_TIME_PTR->GetTimeNow());	// timeGetTime()

	//}

	return true;
}

void SCNewItem::setObjId(int32_t id)
{
	mObjId = id;
}

void SCNewItem::setSceneId(int32_t id)
{
	mSceneId = id;
}

void SCNewItem::setItemIndex(int32_t itemIndex)
{
	mItemIndex = itemIndex;
}

void SCNewItem::setItemCount(int32_t itemCount)
{
	mItemCount = itemCount;
}

void SCNewItem::setPosition(float x, float z)
{
	mPositionX = x;
	mPositionZ = z;
}