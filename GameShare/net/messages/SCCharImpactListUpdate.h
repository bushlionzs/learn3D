#pragma once
#include "net/net_message.h"
class SCCharImpactListUpdate : public NetPacket
{
typedef struct BriefImpact
{
	BriefImpact()
	{
		Clear();
	}

	void Clear(void)
	{
		m_nBuffID = INVALID_ID;
		m_nSN = INVALID_ID;
	};

	EffectID_t	m_nBuffID;
	uint32		m_nSN;
} ImpactStruct_T;
public:
	SCCharImpactListUpdate();
	~SCCharImpactListUpdate();

	virtual bool process();
	void setImpactList(_EFFECT_LIST const& rList, bool bVisableOnly = false);
	void setOwnerId(int32_t id);
	void setSceneId(int32_t id);
	void setLastSN(uint32_t sn);
private:
	int32_t mOwnerId = -1;
	int32_t mSceneId = -1;
	int32_t mNumOfImpacts = 0;
	uint32_t mLastSN;
	ImpactStruct_T	m_aImpact[MAX_IMPACT_NUM];
};