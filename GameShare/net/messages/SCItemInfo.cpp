#include "stdafx.h"
#include "SCItemInfo.h"

SCItemInfo::SCItemInfo()
    :NetPacket(SC_ITEM_INFO)
{

}

SCItemInfo::~SCItemInfo()
{

}

bool SCItemInfo::process()
{
	GAME_DATA_ITEM_PTR->UserBag_SetItemInfo
	(
		mBagIndex,
		mNull,
		&mItem,
		mTips
	);
	ACTION_SYS_PTR->UserBag_Update();

	/*
	 * ACTION_SYS_PTR->UserBag_Update(pPacket->getID());
	 */
	if (!GAME_DATA_ITEM_PTR->GetPacketResetFlag())
		COMMAND_SYS_PTR->AddCommand(GCD_PACKAGE_ITEM_CHANGED, mBagIndex);

	GAME_DATA_ITEM_PTR->SetPacketResetSwapReturn();

	/* 得到详细信息后， 更新surpper tooltip. */
	COMMAND_SYS_PTR->AddCommand(GCD_UPDATE_SUPERTOOLTIP);

	return true;
}

SItem* SCItemInfo::getItem()
{
    return &mItem;
}

void SCItemInfo::setIsNull(bool bnull)
{
	mNull = bnull;
}

void SCItemInfo::setId(int32_t bagIndex)
{
	mBagIndex = bagIndex;
}

void SCItemInfo::setTips(int32_t tips)
{
	mTips = tips;
}