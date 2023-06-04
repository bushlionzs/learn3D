#include "OgreHeader.h"
#include "KItem.h"

KItem::KItem(uint64_t id)
{
	mObjectType = ObjectType_Item;
	mRuleId = -1;
}

KItem::~KItem()
{

}

void KItem::setRule(int32_t nRuleId)
{
	mRuleId = nRuleId;
}

int32_t KItem::getRule()
{
	return mRuleId;
}
