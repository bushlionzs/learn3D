#ifndef __GAMESTRUCT_SKILL_H__
#define __GAMESTRUCT_SKILL_H__

#include "TypeDefine.h"
#include "Enum.h"
#include "StructEffect.h"

struct _DBC_DIRECT_EFFECT
{
	uint32	m_uID;
	char	*m_pszEffect;
	char	*m_pszSound;
	char	*m_pszEffectLocator;
	char	*m_pszReserved1;
	char	*m_pszReserved2;
	char	*m_pszInfo;
};
typedef _DBC_DIRECT_EFFECT	SDirectImpact;
typedef _DBC_DIRECT_EFFECT	_DIRECT_IMPACT;

struct _DBC_BUFF_EFFECT
{
	uint32	m_uID;
	uint32	m_uMutexID;
	int32	m_nPri;
	uint32	m_uMaxLayerNum;
	LPCSTR	m_szIconName;
	LPCSTR	m_lpszEffect_Active;
	LPCSTR	m_lpszSound_Active;
	LPCSTR	m_lpszBind_Active;
	LPCSTR	m_lpszEffect_Continuous;
	LPCSTR	m_lpszSound_Continuous;
	LPCSTR	m_lpszBind_Continuous;
	BOOL	m_bStillOnWhenOwnerDead;
	BOOL	m_bCanBeDispeled;
	BOOL	m_bHostileFlag;
	BOOL	m_bCanBeManualCancel;
	BOOL	m_bBullet;
	LPCSTR	m_szBulletName;
	LPCSTR	m_szBulletSendLocator;
	LPCSTR	m_szBulletHitLocator;
	BOOL	m_bLineEffect;
	LPCSTR	m_pszInfo;
	BOOL	m_bShow;
	LPCSTR	m_pszTargetInfo;
};
typedef _DBC_BUFF_EFFECT	SBuffImpact;
typedef _DBC_BUFF_EFFECT	_BUFF_EFFECT;

enum eBULLET_CONTRAIL_TYPE
{
	BULLET_CONTRAIL_TYPE_INVALID	= -1,
	BULLET_CONTRAIL_TYPE_BEELINE,
	BULLET_CONTRAIL_TYPE_PARABOLA,
	BULLET_CONTRAIL_TYPE_NONE,
	BULLET_CONTRAIL_TYPE_ROTATE,
	BULLET_CONTRAIL_TYPE_EXP,
	BULLET_CONTRAIL_TYPE_NUMBERS
};

struct SDBC_BulletData
{
	int32		m_nID;
	char const	*m_szDesc;
	char const	*szKeyword;
	char const	*m_szBulletSystemName;
	char const	*m_szReserved1;
	char const	*m_szReserved2;

	int32		m_bIsLogicBullet;
	int32		m_nContrailType;
	int32		m_nContrailParam;
	char const	*m_szFlyEffect;
	char const	*m_szFlySound;
	float		m_fSpeed;
	float		m_fAcceleration;
	char const	*m_szHitEffect;
	char const	*m_szHitSound;
	char const	*m_szHitEffectLocator;
};
typedef SDBC_BulletData	SSkillObjData;
typedef SDBC_BulletData	_SPELLOBJ_DATA;

enum eSPELL_TYPE
{
	SKILL_TYPE_INVALID		= -1,
	SKILL_TYPE_GATHER,
	SKILL_TYPE_LEAD,
	SKILL_TYPE_LAUNCH,
	SKILL_TYPE_PASSIVE,
	SKILL_TYPE_NUMBERS
};

// 转移类技能
enum ENUM_TRANSFER_SKILL
{
	TRANSFER_INVALID = -1, 
	TRANSFER_TWINKLING,		// 瞬移
	TRANSFER_TANTIVY,		// 冲锋
	TRANSFER_RECOIL,		// 后退
};

enum eSELECT_TYPE
{
	SELECT_TYPE_INVALID		= -1,
	SELECT_TYPE_NONE,
	SELECT_TYPE_CHARACTER,
	SELECT_TYPE_POS,
	SELECT_TYPE_DIR,
	SELECT_TYPE_SELF,
	SELECT_TYPE_HUMAN_GUID,
	SELECT_TYPE_NUMBERS
};
enum eTARGET_LOGIC
{
	TARGET_LOGIC_INVALID		= -1,
	TARGET_SELF,
	TARGET_MY_PET,
	TARGET_MY_SHADOW_GUARD,
	TARGET_MY_MASTER,
	TARGET_AE_AROUND_SELF,
	TARGET_SPECIFIC_UNIT,
	TARGET_AE_AROUND_UNIT,
	TARGET_AE_AROUND_POSITION,
	TARGET_POS,
	TARGET_LOGIC_NUMBERS
};

enum eBEHAVIOR_TYPE { BEHAVIOR_TYPE_HOSTILITY = -1, BEHAVIOR_TYPE_NEUTRALITY = 0, BEHAVIOR_TYPE_AMITY = 1, };
enum eSPELL_ACTION_TYPE
{
	SKILL_ACTION_TYPE_INVALID		= -1,
	SKILL_ACTION_TYPE_NONE,
	SKILL_ACTION_TYPE_CONCATENATION_EX,
	SKILL_ACTION_TYPE_CONCATENATION,
	SKILL_ACTION_TYPE_NUMBERS
};

#define MAX_SKILL_FRIEND_TMPACT (2)
#define MAX_SKILL_ENEMY_TMPACT	(2)

struct _DBC_SKILL_STUDY_DATA
{
	int32		m_nSkillID;
	const char	*m_szLevelQua;
	int32		m_nVocationQua;
	const char	*m_szSeriesSkillPointQua;
	int32		m_nFatherSkillIDQua;
	const char	*m_szFatherSkillLevelQua;
	const char	*m_szSkillPointQua;
	const char	*m_szMoneyQua;
	const char	*m_szExpQua;
	const char	*m_szItem1Qua;
	const char	*m_szItem1NumQua;
	const char	*m_szItem2Qua;
	const char	*m_szItem2NumQua;
	const char	*m_szItem3Qua;
	const char	*m_szItem3NumQua;
	BOOL		m_bSkillIsMutex;
};

struct _DBC_SPELL_DATA
{
	int32		m_nID;
	int32		m_nProfession;
	const char	*m_lpszName;
	const char	*m_lpszSkillExplain;
	const char	*m_lpszSkillExplainForTip;
	const char	*m_lpszSkillExplainForInterface;
	const char	*m_lpszIconName;
	int32		m_nSkillActionType;
	int32		m_nMaxLevel;
	const char	*m_lpsznCoolDownTime;
	const char	*m_lpszJiQiTime;
	const char	*m_lpszDirectTime;
	int32		m_nCondition11;
	int32		m_nCondition12;
	int32		m_bMustUseWeapon;
	int32		m_nDisableByFlag1;
	int32		m_nDisableByFlag2;
	int32		m_nDisableByFlag3;
	int32		m_nDisableByFlag4;
	int32		m_nRangeSkillFlag;
	int32		m_nType;
	int32		m_nCooldownID;
	const char	*m_lpszGatherLeadActionSetID;
	const char	*m_lpszSendActionSetID;
	int32		m_nTargetMustInSpecialState;
	int32		m_nClassByUser;
	int32		m_nPassiveFlag;
	int32		m_nSelectType;
	int32		m_nSkillClass;
	const char*	m_lpszMinAttackRange;
	const char*	m_lpszMaxAttackRange;
	int32		m_nFriendness;
	int32		m_nHitsOrINTerval;
	int32		m_bAutoRedo;
	float		m_fDamageRange;
	int32		m_nCanInterruptAutoShot;
	const char	*m_lpszImpcatExplain_1;
	const char	*m_lpszImpactParameter_1;
	int32		m_nTransferSkill;
	int32		m_nOperateModeForPetSkill;
	int32		m_nPetSkillKind;
};
typedef _DBC_SPELL_DATA SSkillData;
typedef _DBC_SPELL_DATA _SKILL_DATA;

struct _DBC_TALENT_DATA
{
	uint32		m_uID;
	uint32		m_uIDProfession;
	const char	*m_lpszName;
	char		*m_pszDesc;
	const char	*m_lpszIconName;
};
struct _PLAYER_SPELL
{
	enum _OWN_SKILL_STATE { OWN_SKILL_DISABLE, OWN_SKILL_CAN_LEARN, OWN_SKILL_CAN_USE, OWN_SKILL_CAN_UPGRADE };
	SpellID_t m_nSkillID;
	_OWN_SKILL_STATE m_eState;
	uchar m_nLevel;

	static uint32 GetSize()
	{
		return sizeof(SpellID_t) + sizeof(_OWN_SKILL_STATE) + sizeof(uchar);
	}

};

struct _PLAYER_INHERENCEBALANCE_LEVEL
{
	int8 m_nInherenceBalanceID;
	uint16 m_nLevel;

	static uint32 GetSize()
	{
		return sizeof(int8) + sizeof(uint16);
	}

};

struct _OWN_TALENT
{
	SpellID_t	m_nTalentID;
	uchar		m_nLevel;
};

#define DAMAGE_INFO_PARAM_NUMBER	(8)

struct SDamageInfo
{
	enum
	{
		TYPE_INVALID			= INVALID_ID,
		TYPE_EFFECT			= 0,
		TYPE_HEAL_AND_DAMAGE		= 1,
		TYPE_DROP_BOX			= 2,
		TYPE_SKILL_TEXT			= 3,
		TYPE_DIE			= 4,
	};
	SpellID_t m_nSkillID;
	ObjID_t m_nTargetID;
	ObjID_t m_nSenderID;
	int32 m_nSenderLogicCount;
	EffectID_t m_nImpactID;
	ID_t m_nType;
	int32 m_nHealthIncrement;
	BOOL m_bHealthDirty;
	int32 m_nManaIncrement;
	BOOL m_bManaDirty;
	int32 m_nRageIncrement;
	BOOL m_bRageDirty;
	int32 m_nStrikePointIncrement;
	BOOL m_bStrikePointDirty;
	BOOL m_bIsCriticalHit;
	int32 m_nExp;

	BOOL m_bDeathblow;
	GLPos m_BeatBackPos;
	GLPos m_CloseToPos;
	float m_fBeatFlyDist;
	float m_fAttackerAngle;
	BOOL m_bCloseTo;

	int32 m_nDelayTime;

	int32 m_aAttachedParams[DAMAGE_INFO_PARAM_NUMBER];

	SDamageInfo (void)
	{
		Reset();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Reset(void)
	{
		m_nTargetID = INVALID_ID;
		m_nSenderID = INVALID_ID;
		m_nSenderLogicCount = -1;
		m_nImpactID = INVALID_ID;
		m_nType = TYPE_INVALID;
		m_nHealthIncrement = 0;
		m_bHealthDirty = FALSE;
		m_nManaIncrement = 0;
		m_bManaDirty = FALSE;
		m_nRageIncrement = 0;
		m_bRageDirty = FALSE;
		m_nStrikePointIncrement = 0;
		m_bStrikePointDirty = FALSE;
		m_bIsCriticalHit = FALSE;
		m_bDeathblow = FALSE;
		m_fBeatFlyDist = 0;
		m_fAttackerAngle = 0;
		m_bCloseTo = FALSE;
		m_nDelayTime = 0;
		m_nExp = 0;
		memset(m_aAttachedParams, 0, sizeof(m_aAttachedParams));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const SDamageInfo &operator=(const SDamageInfo &in)
	{
		if(this != &in)
		{
			m_nTargetID = in.m_nTargetID;
			m_nSenderID = in.m_nSenderID;
			m_nSenderLogicCount = in.m_nSenderLogicCount;
			m_nImpactID = in.m_nImpactID;
			m_nType = in.m_nType;
			m_nHealthIncrement = in.m_nHealthIncrement;
			m_bHealthDirty = in.m_bHealthDirty;
			m_nManaIncrement = in.m_nManaIncrement;
			m_bManaDirty = in.m_bManaDirty;
			m_nRageIncrement = in.m_nRageIncrement;
			m_bRageDirty = in.m_bRageDirty;
			m_nStrikePointIncrement = in.m_nStrikePointIncrement;
			m_bStrikePointDirty = in.m_bStrikePointDirty;
			m_bIsCriticalHit = in.m_bIsCriticalHit;
			m_bDeathblow = in.m_bDeathblow;
			m_BeatBackPos = in.m_BeatBackPos;
			m_CloseToPos = in.m_CloseToPos;
			m_fBeatFlyDist = in.m_fBeatFlyDist;
			m_fAttackerAngle = in.m_fAttackerAngle;
			m_bCloseTo = in.m_bCloseTo;
			m_nDelayTime = in.m_nDelayTime;
			m_nExp = in.m_nExp;

			memcpy(m_aAttachedParams, in.m_aAttachedParams, sizeof(m_aAttachedParams));
		}

		return *this;
	}
};

#define BUFF_IMPACT_INFO_PARAM_NUMBER	(8)

struct _BUFF_EFFECT_INFO
{
	ObjID_t		m_nReceiverID;
	ObjID_t		m_nSenderID;
	EffectID_t	m_nBuffID;
	SpellID_t	m_nSkillID;
	int32		m_nSenderLogicCount;
	uint32		m_nSN;
	int32		m_nTimer;
	int32		m_nDelayTime;
	uint64		m_uCreateTime;

	_BUFF_EFFECT_INFO (void)
	{
		Reset();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Reset(void)
	{
		m_nReceiverID = INVALID_ID;
		m_nSenderID = INVALID_ID;
		m_nBuffID = INVALID_ID;
		m_nSkillID = INVALID_ID;
		m_nSenderLogicCount = -1;
		m_nSN = -1;
		m_nTimer = 0;
		m_nDelayTime = 0;
		m_uCreateTime = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const _BUFF_EFFECT_INFO &operator=(const _BUFF_EFFECT_INFO &in)
	{
		if(&in != this)
		{
			m_nReceiverID = in.m_nReceiverID;
			m_nSenderID = in.m_nSenderID;
			m_nBuffID = in.m_nBuffID;
			m_nSkillID = in.m_nSkillID;
			m_nSenderLogicCount = in.m_nSenderLogicCount;
			m_nSN = in.m_nSN;
			m_nTimer = in.m_nTimer;
			m_nDelayTime = in.m_nDelayTime;
			m_uCreateTime = in.m_uCreateTime;
		}

		return *this;
	}
};

struct SCallOfInfo
{
	GUID_t		m_guidCaller;
	MapID_t		m_SceneID;
	GLPos	m_Pos;
	uint32		m_uDuration;

	SCallOfInfo (void)
	{
		m_guidCaller = INVALID_GUID;
		m_SceneID = INVALID_ID;
		m_Pos = GLPos(-1.f, -1.f);
		m_uDuration = 0;
	}

	uint32 GetSize() const
	{
		return sizeof(m_guidCaller)+sizeof(m_SceneID)+sizeof(m_Pos)+sizeof(m_uDuration);
	}
	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Reset(void)
	{
		m_guidCaller = INVALID_GUID;
		m_SceneID = INVALID_ID;
		m_Pos = GLPos(-1.f, -1.f);
		m_uDuration = 0;
	}

};

class	CoolDown
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CoolDown(void) :
	m_nID(INVALID_ID),
	m_nCD(0),
	m_nCDElapsed(0)
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CoolDown(CoolDown const &rhs)
	{
		m_nID = rhs.GetID();
		m_nCD = rhs.GetCooldownTime();
		m_nCDElapsed = rhs.GetCooldownElapsed();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~CoolDown(void)
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CoolDown &operator=(CoolDown const &rhs)
	{
		m_nID = rhs.GetID();
		m_nCD = rhs.GetCooldownTime();
		m_nCDElapsed = rhs.GetCooldownElapsed();
		return *this;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void HeartBeat(Time_t nDeltaTime)
	{
		if( 0 > m_nCDElapsed )
		{
			m_nCDElapsed = 0;
		}

		if( 0 > nDeltaTime )
		{
			nDeltaTime = 0;
		}

		if(0 > m_nID || m_nCD <= m_nCDElapsed) return;
		m_nCDElapsed += nDeltaTime;
		if(m_nCD < m_nCDElapsed) m_nCD = m_nCDElapsed;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline BOOL IsCooldowned(void) const
	{
		return m_nCD <= m_nCDElapsed;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline Time_t GetRemainTime(void) const
	{
		return m_nCD - m_nCDElapsed;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline void Reset(void)
	{
		m_nID = INVALID_ID;
		m_nCD = 0;
		m_nCDElapsed = 0;
	};

	inline void ClearCD(void)
	{
		m_nCD = 0;
		m_nCDElapsed = 0;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline ID_t GetID(void) const
	{
		return m_nID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline void SetID(ID_t nID)
	{
		m_nID = nID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline Time_t GetCooldownTime(void) const
	{
		return m_nCD;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline void SetCooldownTime(Time_t nTime)
	{
		m_nCD = nTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline Time_t GetCooldownElapsed(void) const
	{
		return m_nCDElapsed;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetCooldownElapsed(Time_t nTime)
	{
		m_nCDElapsed = nTime;
	}

	uint32 GetSize() const
	{
		return sizeof(m_nID) + sizeof(m_nCD) + sizeof(m_nCDElapsed);
	}
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	ID_t	m_nID;
	Time_t	m_nCD;
	Time_t	m_nCDElapsed;
};

template<int32 size>
class CDList
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { list_size = size, };

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	CDList(void)
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CDList(CDList const &rhs)
	{
		for(int32 nIdx = 0; list_size > nIdx; ++nIdx) m_CDs[nIdx] = rhs.GetCooldownInfoByIndex(nIdx);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~CDList(void)
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear(void)
	{
		Reset();
	}

	void ClearCD()
	{
		for(int32 nIdx = 0; list_size > nIdx; ++nIdx) m_CDs[nIdx].ClearCD();
	}
	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Reset(void)
	{
		for(int32 nIdx = 0; list_size > nIdx; ++nIdx) m_CDs[nIdx].Reset();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CDList &operator=(CDList const &rhs)
	{
		for(int32 nIdx = 0; list_size > nIdx; ++nIdx) m_CDs[nIdx] = rhs.GetCooldownInfoByIndex(nIdx);
		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CoolDown const &GetCooldownInfoByIndex(int32 nIdx) const
	{
		if(0 > nIdx || list_size <= nIdx)
		{
			KCheckEx(FALSE, "[CDList::GetCooldownByIndex]:Illegal index found!!");
			return m_CDs[0];
		}

		return m_CDs[nIdx];
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	Time_t GetRemainTimeByID(CooldownID_t nCooldown) const
	{
		for(int32 nIdx = 0; list_size > nIdx; ++nIdx)
			if(m_CDs[nIdx].GetID() == nCooldown) return m_CDs[nIdx].GetRemainTime();
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline int32 GetSlotSize(void)
	{
		return list_size;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline int32 GetByteSize(void)
	{
		return sizeof(CDList);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void HeartBeat(Time_t nDeltaTime)
	{
		for(int32 nIdx = 0; list_size > nIdx; ++nIdx) m_CDs[nIdx].HeartBeat(nDeltaTime);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsSpecificSlotCooldownedByID(CooldownID_t nCooldown) const
	{
		if(0 > nCooldown) return TRUE;
		for(int32 nIdx = 0; list_size > nIdx; ++nIdx)
			if(m_CDs[nIdx].GetID() == nCooldown) return m_CDs[nIdx].IsCooldowned();
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void RegisterCooldown(CooldownID_t nCooldown, Time_t nCooldownTime)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nEmptySlot = INVALID_ID;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(0 > nCooldown) return;
		for(int32 nIdx = 0; list_size > nIdx; ++nIdx)
		{
			if(INVALID_ID == nEmptySlot)
			{
				if(INVALID_ID == m_CDs[nIdx].GetID())
					nEmptySlot = nIdx;
				else if(TRUE == m_CDs[nIdx].IsCooldowned())
					nEmptySlot = nIdx;
			}

			if(m_CDs[nIdx].GetID() == nCooldown)
			{
				m_CDs[nIdx].Reset();
				m_CDs[nIdx].SetID(nCooldown);
				m_CDs[nIdx].SetCooldownTime(nCooldownTime);
				return;
			}
		}

		if(INVALID_ID != nEmptySlot)
		{
			m_CDs[nEmptySlot].Reset();
			m_CDs[nEmptySlot].SetID(nCooldown);
			m_CDs[nEmptySlot].SetCooldownTime(nCooldownTime);
			return;
		}

		KCheckEx(FALSE, "[CDList::RegisterCooldown]: CD list full!!");
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	CoolDown	m_CDs[list_size];
};

class	CombatMissFlag
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { FLAG_NORMAL = 0, FLAG_MISS, FLAG_IMMU, FLAG_ABSORB, FLAG_COUNTERACT, FLAG_TRANSFERED, FLAG_RESIST, };
};

enum { MAX_WAY_POINT_NUM = 4 };

struct _SkillMissMSGDelayTime
{
	ObjID_t		m_nSender;
	SpellID_t	m_nSkill;
	uint32		m_nDelayTime;
	int32		m_nLogicCount;
	int32		m_nFlag;
	_SkillMissMSGDelayTime()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(this, -1, sizeof(_SkillMissMSGDelayTime));
	}
};

struct _Monster_Pet_DB_Struct
{
	int32		m_iDataIndex;
	int32		m_iHP;
	int32		iLifeTime;
	_OWN_EFFECT	m_aImpactList[MONSTER_PET_MAX_IMPACT];
	int32		m_aSkillList[MONSTER_PET_MAX_SKILL];
	int32		m_nCtrlState;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(this, -1, sizeof(_Monster_Pet_DB_Struct));
	}
};

typedef struct _InherenceBalanceRefixValue
{
	int32 values[CPROPERTY_LEVEL4_BALANCE_NUMBER];

	_InherenceBalanceRefixValue()
	{
		Clear();
	}

	void Clear()
	{
		memset(values, 0, sizeof(values));
	}

}InherenceBalanceRefixValue;
#endif
