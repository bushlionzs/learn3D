#include "OgreHeader.h"
#include "KItem.h"

KItem::KItem(uint64_t id)
{
	mObjectType = ObjectType_Item;
	mRuleId = -1;
	setId(id);
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

void KItem::SetExtraInfo(const SItem* pItemInfo)
{
	memcpy(&mItemInfo, pItemInfo, sizeof(SItem));
}

void KItem::SetGUID(USHORT idWorld, USHORT idServer, uint32 idSerial)
{
	m_ID.m_idOrg.m_idWorld = idWorld;
	m_ID.m_idOrg.m_nServerID = idServer;
	m_ID.m_idOrg.m_uSerial = idSerial;
}