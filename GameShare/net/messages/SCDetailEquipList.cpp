#include "stdafx.h"
#include "SCDetailEquipList.h"


SCDetailEquipList::SCDetailEquipList() :
	NetPacket(SC_DELETE_OBJECT)
{

}

SCDetailEquipList::~SCDetailEquipList()
{

}



void SCDetailEquipList::setObjectId(int32_t id)
{
	mObjectId = id;
}

void SCDetailEquipList::addItem(int32_t part, SItem& item)
{
	mItemMap[part] = item;
}


