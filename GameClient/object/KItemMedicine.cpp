#include "OgreHeader.h"
#include "KItemMedicine.h"

KItemMedicine::KItemMedicine(uint64_t id)
	:KItem(id)
{
	mObjectType = ObjectType_ItemMedicine;
}

KItemMedicine::~KItemMedicine()
{

}
