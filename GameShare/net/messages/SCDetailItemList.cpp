#include "stdafx.h"
#include "SCDetailItemList.h"


SCDetailItemList::SCDetailItemList() :
	NetPacket(SC_DELETE_OBJECT)
{

}

SCDetailItemList::~SCDetailItemList()
{

}



void SCDetailItemList::setObjectId(int32_t id)
{
	mObjectId = id;
}

void SCDetailItemList::addItem(int32_t part, SItem& item)
{
	mItemMap[part] = item;
}


