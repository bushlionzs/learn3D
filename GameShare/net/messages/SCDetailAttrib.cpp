#include "stdafx.h"
#include "SCDetailAttrib.h"


SCDetailAttrib::SCDetailAttrib():
	NetPacket(SC_DETAIL_ATTR)
{

}

SCDetailAttrib::~SCDetailAttrib()
{

}

bool SCDetailAttrib::process()
{
	
	return true;
}

const SHorseSkill* SCDetailAttrib::GetSkill(uint32 uIndex) const
{
	return((uIndex < PET_MAX_SKILL_COUNT) ? (&(m_aSkill[uIndex])) : (NULL));
}

void SCDetailAttrib::SetSkill(uint32 uIndex, const SHorseSkill* pSkill)
{
	
}

uchar* SCDetailAttrib::GetExtraInfoData(void)
{
	return m_ExtraInfoData;
}

void SCDetailAttrib::SetExtraInfoData(uchar* ExtraInfoData)
{
	memcpy(m_ExtraInfoData, ExtraInfoData, sizeof(m_ExtraInfoData)* sizeof(uchar));
}

void SCDetailAttrib::setObjectId(int32_t id)
{
	mObjectId = id;
}

void SCDetailAttrib::setSceneId(int32_t id)
{
	mMapId = id;
}

