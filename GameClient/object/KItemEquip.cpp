#include "OgreHeader.h"
#include "KItemEquip.h"
#include "Basics.h"

KItemEquip::KItemEquip(uint64_t id)
	:KItem(id)
{
	mObjectType = ObjectType_ItemEquip;
	m_pExtraDefine = nullptr;
}

KItemEquip::~KItemEquip()
{

}

int32_t KItemEquip::GetVisualID(void) const
{
	if (m_theBaseDef.pEquipVisual)
	{
		return m_theBaseDef.pEquipVisual->nModelID;
	}

	return -1;
}

uint32_t KItemEquip::GetTermTime(void) const
{
	if (m_pExtraDefine)
	{
		return m_pExtraDefine->m_TermEndTime;
	}
	else
		return 0;
}

int32 KItemEquip::GetItemTableType(void) const
{
	if (m_theBaseDef.pDefineEquip)
	{
		return m_theBaseDef.pDefineEquip->nType;
	}

	return INVALID_ID;
}

bool KItemEquip::IsDefence() const
{
	int32 iType = GetItemTableType();

	switch (iType)
	{
	case EQUIP_SDUN:
	case EQUIP_SGU:
	case EQUIP_CRUSADE_ASSIST_HAND:
		return TRUE;
	default:
		break;
	}
	return FALSE;
}
