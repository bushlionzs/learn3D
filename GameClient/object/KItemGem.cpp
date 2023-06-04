#include "OgreHeader.h"
#include "KItemGem.h"

KItemGem::KItemGem(uint64_t id)
	:KItem(id)
{
	mObjectType = ObjectType_ItemEquip;
}

KItemGem::~KItemGem()
{

}
