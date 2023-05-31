#include "stdafx.h"
#include "SCCharImpactListUpdate.h"


SCCharImpactListUpdate::SCCharImpactListUpdate():
	NetPacket(SC_IMPACTLIST_UPDATE)
{

}

SCCharImpactListUpdate::~SCCharImpactListUpdate()
{

}

bool SCCharImpactListUpdate::process()
{
	
	
	return true;
}


void SCCharImpactListUpdate::setImpactList(_EFFECT_LIST const& rList, bool bVisableOnly)
{
	for (int32 i = 0; i < rList.m_Count; ++i)
	{
		if (0 > mNumOfImpacts || MAX_IMPACT_NUM <= mNumOfImpacts) return;
		if (rList.m_aImpacts[i].IsFadeOut()) continue;
		if (IMPACT_BUFF_VISABLE_INVALID == rList.m_VisableType[i]) continue;
		if (bVisableOnly && IMPACT_BUFF_VISABLE_CANNOT == rList.m_VisableType[i]) continue;

		m_aImpact[mNumOfImpacts].m_nBuffID = rList.m_aImpacts[i].GetImpactID();
		m_aImpact[mNumOfImpacts].m_nSN = rList.m_aImpacts[i].GetSN();
		++mNumOfImpacts;
	}
}

void SCCharImpactListUpdate::setOwnerId(int32_t id)
{
	mOwnerId = id;
}

void SCCharImpactListUpdate::setSceneId(int32_t id)
{
	mSceneId = id;
}

void SCCharImpactListUpdate::setLastSN(uint32_t sn)
{
	mLastSN = sn;
}

