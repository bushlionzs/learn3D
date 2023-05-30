#include "stdafx.h"
#include "SCNewItemBox.h"
#include "server/server_manager.h"
#include "object/OperateObj/KOperate_Box.h"
#include "object/OperateObj/KOperate_Resource.h"

SCNewItemBox::SCNewItemBox():
	NetPacket(SC_NEW_ITEMBOX)
{

}

SCNewItemBox::~SCNewItemBox()
{

}

bool SCNewItemBox::process()
{
	
	if (!SCENE_MANAGER_PTR->GetActiveScene()->IsValidPosition(vector2(mPos.m_fX, mPos.m_fZ)))
	{
		if (g_bDebug)
			KLThrow("ERROR POSITION @ XCNewItemBoxDispatch");
		return MP_CONTINUE;
	}

	if (ITYPE_DROPBOX == mType)
	{
		BOOL bMustCreater = TRUE;
		KObject* pObj = (KObject*)(OBJECT_MANAGER_PTR->FindServerObject(mDropMonsterId));
		if (pObj && pObj->CheckClassType(GET_CLASS(KCharacter)))
		{
			KCharacter* pCharacter = (KCharacter*)pObj;
			if (!pCharacter->IsDie())
			{
				ObjID_t		idItemBox = mObjectId;
				GUID_t		idOwner = mOwnerId;
				GLPos* posCreate = &mPos;
				bMustCreater = FALSE;
			}
		}

		if (bMustCreater)
		{
			//创建ItemBox
			//KOperate_Box* pBox = (KOperate_Box*)OBJECT_MANAGER_PTR->CreateNewObject( "KOperate_Box", pPacket->GetObjID());
			KOperate_Box* pBox = (KOperate_Box*)OBJECT_MANAGER_PTR->CreateNewObject(GET_CLASS(KOperate_Box), mObjectId);
			pBox->Initialize(vector3(mPos.m_fX, 0.f, mPos.m_fZ), vector3(0.f, 0.f, 0.f));
			//设置位置
			pBox->CalculateNodePos(vector2(mPos.m_fX, mPos.m_fZ));
			//设置掉落箱的归属
			pBox->SetOwnerGUID(mOwnerId);
		}
	}
	else
	{
		//创建矿物生长点
		//KOperate_Resource* pResource = (KOperate_Resource*)OBJECT_MANAGER_PTR->CreateNewObject( "KOperate_Resource", pPacket->GetObjID());
		KOperate_Resource* pResource = (KOperate_Resource*)OBJECT_MANAGER_PTR->CreateNewObject(GET_CLASS(KOperate_Resource), mObjectId);
		if (!(pResource->SetResourceID(mType)))
		{
			//非法的资源ID
			OBJECT_MANAGER_PTR->ImmeDestroyObject(pResource);
			return MP_CONTINUE;
		}

		pResource->Initialize
		(
			vector3(mPos.m_fX, 0.f, mPos.m_fZ),
			vector3(0.f, 0.f, 0.f)
		);

		/* 设置位置 */
		pResource->CalculateNodePos(vector2(mPos.m_fX, mPos.m_fZ));
	}
	return true;
}

void SCNewItemBox::setObjectId(int32_t id)
{
	mObjectId = id;
}

void SCNewItemBox::setObjType(int32_t type)
{
	mType = type;
}

void SCNewItemBox::setOwner(GUID_t id)
{
	mOwnerId = id;
}

void SCNewItemBox::setWorldPos(const GLPos* pos)
{
	mPos = *pos;
}

void SCNewItemBox::setDropMonsterId(int32_t id)
{
	mDropMonsterId = id;
}

void SCNewItemBox::setSceneId(int32_t id)
{
	mSceneId = id;
}

