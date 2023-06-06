#pragma once
#include "TypeDefine.h"
#include "Enum.h"
#include "Util.h"

typedef enum eDIRECT_EFFECT_SEID
{
	SPECIAL_DROPBOX		= -3,
	SPECIAL_DIE		= -2,
	DISPLAY_MISS		= -1,
	DAMAGE_PHYSICS		= 0,
	DAMAGE_MAGIC		= 1,
	DAMAGE_COLD		= 2,
	DAMAGE_FIRE		= 3,
	DAMAGE_LIGHT		= 4,
	DAMAGE_POISON		= 5,
	DISPEL_RAGE		= 6,
	MAX_DIRECT_IMPACT_SEID,
} DIRECT_IMPACT_SEID;

#define DEF_IMPACT_DIRECT_PARAM_NUMBERS (4)
struct SEffectDirect
{
	int32	m_nID;
	int32	m_nCreaterID;
	int32	m_nLogicCountOfCreater;
	int32	m_aParams[DEF_IMPACT_DIRECT_PARAM_NUMBERS];

	SEffectDirect (void)
	{
		m_nID = INVALID_ID;
		m_nCreaterID = INVALID_ID;
		m_nLogicCountOfCreater = -1;
		memset(m_aParams, 0, sizeof(m_aParams));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Reset(void)
	{
		m_nID = INVALID_ID;
		m_nCreaterID = INVALID_ID;
		m_nLogicCountOfCreater = -1;
		memset(m_aParams, 0, sizeof(m_aParams));
	}
};

class	_OWN_EFFECT_DB
{
public:
	enum 
	{ 
		IDX_FADE_OUT = 0, 
		IDX_CRITICAL = 1, 
		IDX_CREATE_BY_PLAYER, 
		IDX_MAX, 
	};

	enum { MAX_FLAG_NUMBER = IDX_MAX };


protected:
	typedef BitFlags<MAX_FLAG_NUMBER>	InternalFlags_T;

public:
	_OWN_EFFECT_DB()
	{
		Clear();
	};

	~_OWN_EFFECT_DB()
	{
	};

	void Clear(void)
	{
		m_nSN = INVALID_ID;
		m_nDataIndex = INVALID_ID;
		m_nImpactID = INVALID_ID;
		m_nSkillID = INVALID_ID;
		m_nCasterObjID = INVALID_ID;
		m_nCasterUniqueID = INVALID_ID;
		m_nCasterLogicCount = 0;
		m_nContinuance = 0;
		m_nContinuanceElapsed = 0;
		m_nIntervalElapsed = 0;
		m_iSkillLevel = 0;
		m_Flags.ClearAllFlags();
	};

	_OWN_EFFECT_DB &operator=(_OWN_EFFECT_DB const &rhs)
	{
		m_nSN = rhs.m_nSN;
		m_nDataIndex = rhs.m_nDataIndex;
		m_nImpactID = rhs.m_nImpactID;
		m_nSkillID = rhs.m_nSkillID;
		m_nCasterObjID = rhs.m_nCasterObjID;
		m_nCasterUniqueID = rhs.m_nCasterUniqueID;
		m_nCasterLogicCount = rhs.m_nCasterLogicCount;
		m_nContinuance = rhs.m_nContinuance;
		m_nContinuanceElapsed = rhs.m_nContinuanceElapsed;
		m_nIntervalElapsed = rhs.m_nIntervalElapsed;
		m_Flags = rhs.m_Flags;
		m_iSkillLevel = rhs.m_iSkillLevel;
		return *this;
	};

	int32 GetSN(void) const
	{
		return m_nSN;
	}

	void SetSN(int32 nSN)
	{
		m_nSN = nSN;
	}

	ID_t GetDataIndex(void) const
	{
		return m_nDataIndex;
	}

	void SetDataIndex(ID_t nIdx)
	{
		m_nDataIndex = nIdx;
	}

	ID_t GetImpactID(void) const
	{
		return m_nImpactID;
	}

	void SetImpactID(ID_t nID)
	{
		m_nImpactID = nID;
	}

	ID_t GetSkillID(void) const
	{
		return m_nSkillID;
	}

	void SetSkillID(ID_t nID)
	{
		m_nSkillID = nID;
	}

	ObjID_t GetCasterObjID(void) const
	{
		return m_nCasterObjID;
	}

	void SetCasterObjID(ObjID_t nID)
	{
		m_nCasterObjID = nID;
	}

	ObjID_t GetCasterUniqueID(void) const
	{
		return m_nCasterUniqueID;
	}

	void SetCasterUniqueID(ObjID_t nID)
	{
		m_nCasterUniqueID = nID;
	}

	int32 GetCasterLogicCount(void) const
	{
		return m_nCasterLogicCount;
	}

	void SetCasterLogicCount(int32 nCount)
	{
		m_nCasterLogicCount = nCount;
	}

	Time_t GetContinuance(void) const
	{
		return m_nContinuance;
	}

	void SetContinuance(Time_t nTime)
	{
		m_nContinuance = nTime;
	}

	Time_t GetContinuanceElapsed(void) const
	{
		return m_nContinuanceElapsed;
	}

	void SetContinuanceElapsed(Time_t nTime)
	{
		m_nContinuanceElapsed = nTime;
	}

	Time_t GetIntervalElapsed(void) const
	{
		return m_nIntervalElapsed;
	}

	void SetIntervalElapsed(Time_t nTime)
	{
		m_nIntervalElapsed = nTime;
	}

	BOOL IsCreateByPlayer(void) const
	{
		return m_Flags.GetFlagByIndex(IDX_CREATE_BY_PLAYER);
	}

	void MarkCreateByPlayerFlag(void)
	{
		m_Flags.MarkFlagByIndex(IDX_CREATE_BY_PLAYER);
	}

	void ClearCreateByPlayerFlag(void)
	{
		m_Flags.ClearFlagByIndex(IDX_CREATE_BY_PLAYER);
	}

	BOOL IsFadeOut(void) const
	{
		return m_Flags.GetFlagByIndex(IDX_FADE_OUT);
	}

	void MarkFadeOutFlag(void)
	{
		m_Flags.MarkFlagByIndex(IDX_FADE_OUT);
	}

	void ClearFadeOutFlag(void)
	{
		m_Flags.ClearFlagByIndex(IDX_FADE_OUT);
	}

	BOOL IsCriticalHit(void) const
	{
		return m_Flags.GetFlagByIndex(IDX_CRITICAL);
	}

	void MarkCriticalFlag(void)
	{
		m_Flags.MarkFlagByIndex(IDX_CRITICAL);
	}

	void ClearCriticalFlag(void)
	{
		m_Flags.ClearFlagByIndex(IDX_CRITICAL);
	}

	int32 GetSkillLevel() const
	{
		return m_iSkillLevel;
	}

	void SetSkillLevel(int32 val)
	{
		m_iSkillLevel = val;
	}

protected:
	int32		m_nSN;

	ID_t		m_nDataIndex;
	ID_t		m_nImpactID;

	ID_t		m_nSkillID;

	ObjID_t		m_nCasterObjID;
	int32		m_nCasterUniqueID;
	int32		m_nCasterLogicCount;

	Time_t		m_nContinuance;

	Time_t		m_nContinuanceElapsed;

	Time_t		m_nIntervalElapsed;

	InternalFlags_T m_Flags;

	int32		m_iSkillLevel;
} ;

enum _IMPACT_BUFF_VISABLE_TYPE 
{ 
	IMPACT_BUFF_VISABLE_INVALID, 
	IMPACT_BUFF_VISABLE_CAN, 
	IMPACT_BUFF_VISABLE_CANNOT, 
};

class _OWN_EFFECT : public _OWN_EFFECT_DB
{
public:
	enum { MAX_IMPACT_PARAM_NUMBER = 11 };

	_OWN_EFFECT()
	{
		Clear();
	}

	~_OWN_EFFECT()
	{
	};

	void Clear(void)
	{
		m_nDelayTime = 0;
		memset((void *) m_aParams, 0, sizeof(m_aParams));
	}

	_OWN_EFFECT &operator=(_OWN_EFFECT const &rhs)
	{
		m_nSN = rhs.m_nSN;
		m_nDataIndex = rhs.m_nDataIndex;
		m_nImpactID = rhs.m_nImpactID;
		m_nSkillID = rhs.m_nSkillID;
		m_nCasterObjID = rhs.m_nCasterObjID;
		m_nCasterUniqueID = rhs.m_nCasterUniqueID;
		m_nCasterLogicCount = rhs.m_nCasterLogicCount;
		m_nContinuance = rhs.m_nContinuance;
		m_nContinuanceElapsed = rhs.m_nContinuanceElapsed;
		m_nIntervalElapsed = rhs.m_nIntervalElapsed;
		m_Flags = rhs.m_Flags;
		m_iSkillLevel = rhs.m_iSkillLevel;
		m_nDelayTime = rhs.m_nDelayTime;
		for(int32 nIdx = 0; MAX_IMPACT_PARAM_NUMBER > nIdx; ++nIdx)
		{
			m_aParams[nIdx] = rhs.GetParamByIndex(nIdx);
		}

		return *this;
	};

	void SetDelayTime(uint32 iTime)
	{
		m_nDelayTime = iTime;
	}

	uint32 GetDelayTime(void)
	{
		return m_nDelayTime;
	}

	int32 GetParamByIndex(int32 nIdx) const
	{
		if(0 > nIdx || MAX_IMPACT_PARAM_NUMBER <= nIdx)
		{
			KCheck(NULL == "[UNIT_EFFECT::GetParamByIndex]:Illegal index found!!");
			return 0;
		}

		return m_aParams[nIdx];
	}

	void SetParamByIndex(int32 nIdx, int32 nValue)
	{
		if(0 > nIdx || MAX_IMPACT_PARAM_NUMBER <= nIdx)
		{
			KCheck(NULL == "[UNIT_EFFECT::SetParamByIndex]:Illegal index found!!");
			return;
		}

		m_aParams[nIdx] = nValue;
	}

private:
	int32	m_aParams[MAX_IMPACT_PARAM_NUMBER];
	uint32	m_nDelayTime;
};


typedef _OWN_EFFECT UNIT_EFFECT;
enum _IMPACT_CALL_SCRIPT_TYPE 
{ 
	IMPACT_CALL_SCRIPT_ADD = 0, 
	IMPACT_CALL_SCRIPT_DEL 
};

