#include "OgreHeader.h"
#include "KItemBag.h"

KItemBag::KItemBag(uint64_t id)
	:KItem(id)
{
	mObjectType = ObjectType_ItemBag;
}

KItemBag::~KItemBag()
{

}
