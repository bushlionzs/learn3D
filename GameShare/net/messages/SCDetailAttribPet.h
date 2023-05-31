#pragma once
#include "net/net_message.h"
#include "StructDB.h"

class SCDetailAttribPet : public NetPacket
{
public:
	enum { 
		TYPE_NORMAL = 0, 
		TYPE_EXCHANGE, 
		TYPE_STALL, 
		TYPE_PLAYERSHOP, 
		TYPE_CONTEX_MENU_OTHER_PET, 
		TYPE_COMPOSE_PET, 
	};

	enum ePET_DETAIL_PROPERTY
	{
		PET_DETAIL_ATTR_INVALID = -1,
		PET_DETAIL_ATTR_OBJ_ID,
		PET_DETAIL_ATTR_DATA_ID,
		PET_DETAIL_ATTR_NAME,
		PET_DETAIL_ATTR_NICK_NAME,
		PET_DETAIL_ATTR_AI_TYPE,
		PET_DETAIL_ATTR_LEVEL,
		PET_DETAIL_ATTR_EXP,
		PET_DETAIL_ATTR_HP,
		PET_DETAIL_ATTR_HPMAX,
		PET_DETAIL_ATTR_GENERATION,
		PET_DETAIL_ATTR_HAPPINESS,
		PET_DETAIL_ATTR_ATT_NEAR,
		PET_DETAIL_ATTR_ATT_FAR,
		PET_DETAIL_ATTR_ATT_MAGIC,
		PET_DETAIL_ATTR_DEF_NEAR,
		PET_DETAIL_ATTR_DEF_FAR,
		PET_DETAIL_ATTR_DEF_MAGIC,
		PET_DETAIL_ATTR_HIT,
		PET_DETAIL_ATTR_MISS,
		PET_DETAIL_ATTR_CRITICAL,
		PET_DETAIL_ATTR_MODELID,
		PET_DETAIL_ATTR_MOUNTID,
		PET_DETAIL_ATTR_STRPERCEPTION,
		PET_DETAIL_ATTR_CONPERCEPTION,
		PET_DETAIL_ATTR_DEXPERCEPTION,
		PET_DETAIL_ATTR_INTPERCEPTION,
		PET_DETAIL_ATTR_STR,
		PET_DETAIL_ATTR_CON,
		PET_DETAIL_ATTR_DEX,
		PET_DETAIL_ATTR_INT,
		PET_DETAIL_ATTR_POINT_REMAIN,
		PET_DETAIL_ATTR_SKILL_0,
		PET_DETAIL_ATTR_SKILL_1,
		PET_DETAIL_ATTR_SKILL_2,
		PET_DETAIL_ATTR_SKILL_3,
		PET_DETAIL_ATTR_SKILL_4,
		PET_DETAIL_ATTR_SKILL_5,
		PET_DETAIL_ATTR_SKILL_6,
		PET_DETAIL_ATTR_SKILL_7,
		PET_DETAIL_ATTR_SKILL_8,
		PET_DETAIL_ATTR_SKILL_9,
		PET_DETAIL_ATTR_SKILL_10,
		PET_DETAIL_ATTR_SKILL_11,
		PET_DETAIL_ATTR_GROWRATE,
		PET_DETAIL_ATTR_MAX_STR_PER,
		PET_DETAIL_ATTR_MAX_CON_PER,
		PET_DETAIL_ATTR_MAX_DEX_PER,
		PET_DETAIL_ATTR_MAX_INT_PER,
		PET_DETAIL_ATTR_STR_POINT,
		PET_DETAIL_ATTR_CON_POINT,
		PET_DETAIL_ATTR_DEX_POINT,
		PET_DETAIL_ATTR_INT_POINT,
		PET_DETAIL_ATTR_STALLORDER,
		PET_DETAIL_ATTR_LOCK,
		PET_DETAIL_ATTR_UNLOCKTIME,
		PET_DETAIL_ATTR_NUMBERS
	};

	enum HorseState 
	{ 
		HorseState_Normal, 
		HorseState_Mating, 
		HorseState_Compose 
	};
public:
	SCDetailAttribPet();
	~SCDetailAttribPet();

	virtual bool process();


	const SHorseSkill* GetSkill(uint32 uIndex) const;
	void SetSkill(uint32 uIndex, const SHorseSkill* pSkill);
	uchar* GetExtraInfoData(void);
	void SetExtraInfoData(uchar* ExtraInfoData);

	void setObjectId(int32_t id);
	void setSceneId(int32_t id);
	void setHorseGuid(SHorseGuid& guid)
	{
		mHorseGuid = guid;
	}

	void setTradeIndex(int32_t tradeIndex)
	{
		mTradeIndex = tradeIndex;
	}

	void setDataID(int32_t dataID)
	{
		mDataID = dataID;
		
		mFlag64.UpdateBits(PET_DETAIL_ATTR_DATA_ID, true);
	}

	void setName(const char* name)
	{
		strncpy(mName, name, sizeof(mName));

		mFlag64.UpdateBits(PET_DETAIL_ATTR_NAME, true);
	}

	void setNickName(const char* name)
	{
		strncpy(mNickName, name, sizeof(mName));
		mFlag64.UpdateBits(PET_DETAIL_ATTR_NICK_NAME, true);
	}

	void setAIType(int32_t aiType)
	{
		mAIType = aiType;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_AI_TYPE, true);
	}

	void setLevel(int32_t level)
	{
		mLevel = level;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_LEVEL, true);
	}

	void setExp(int32_t exp)
	{
		mExp = exp;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_EXP, true);
	}

	void setHP(int32_t hp)
	{
		mHP = hp;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_HP, true);
	}

	void setHPMax(int32_t maxHP)
	{
		mHPMax = maxHP;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_HPMAX, true);
	}

	void setHorseState(int32_t state)
	{
		mHorseState = state;
	}

	void setGeneration(int32_t generation)
	{
		mGeneration = generation;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_GENERATION, true);
	}

	void setHappiness(int32_t happiness)
	{
		mHappiness = happiness;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_HAPPINESS, true);
	}

	void setAtt_Near(int32_t att_Near)
	{
		mAtt_Near = att_Near;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_ATT_NEAR, true);
	}

	void setAtt_Far(int32_t att_Far)
	{
		mAtt_Far = att_Far;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_ATT_FAR, true);
	}

	void setAtt_Magic(int32_t att_Magic)
	{
		mAtt_Magic = att_Magic;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_ATT_MAGIC, true);
	}

	void setDef_Near(int32_t def_Near)
	{
		mDef_Near = def_Near;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_DEF_NEAR, true);
	}

	void setDef_Far(int32_t def_Far)
	{
		mDef_Far = def_Far;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_DEF_FAR, true);
	}

	void setDef_Magic(int32_t def_Magic)
	{
		mDef_Magic = def_Magic;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_DEF_MAGIC, true);
	}

	void setHit(int32_t hit)
	{
		mHit = hit;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_HIT, true);
	}

	void setMiss(int32_t miss)
	{
		mMiss = miss;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_MISS, true);
	}

	void setCritical(int32_t critical)
	{
		mCritical = critical;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_CRITICAL, true);
	}

	void setModelID(int32_t modelID)
	{
		mModelID = modelID;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_MODELID, true);
	}

	void setMountID(int32_t mountID)
	{
		mMountID = mountID;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_MOUNTID, true);
	}

	void setStrPerception(int32_t strPerception)
	{
		mStrPerception = strPerception;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_STRPERCEPTION, true);
	}

	void setConPerception(int32_t conPerception)
	{
		mConPerception = conPerception;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_CONPERCEPTION, true);
	}

	void setDexPerception(int32_t dexPerception)
	{
		mDexPerception = dexPerception;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_DEXPERCEPTION, true);
	}

	void setIntPerception(int32_t intPerception)
	{
		mIntPerception = intPerception;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_INTPERCEPTION, true);
	}

	void setStrPerceptionLimit(int32_t strPerceptionLimit)
	{
		mStrPerceptionLimit = strPerceptionLimit;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_MAX_STR_PER, true);
	}

	void setConPerceptionLimit(int32_t conPerceptionLimit)
	{
		mConPerceptionLimit = conPerceptionLimit;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_MAX_CON_PER, true);
	}

	void setDexPerceptionLimit(int32_t dexPerceptionLimit)
	{
		mDexPerceptionLimit = dexPerceptionLimit;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_MAX_DEX_PER, true);
	}

	void setIntPerceptionLimit(int32_t intPerceptionLimit)
	{
		mIntPerceptionLimit = intPerceptionLimit;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_MAX_INT_PER, true);
	}

	void setStrength(int32_t strength)
	{
		mStrength = strength;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_STR, true);
	}


	void setCon(int32_t con)
	{
		mCon = con;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_CON, true);
	}

	void setDex(int32_t dex)
	{
		mDex = dex;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_DEX, true);
	}

	void setIntelligence(int32_t intelligence)
	{
		mIntelligence = intelligence;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_INT, true);
	}

	void setGrowRate(int32_t growRate)
	{
		mGrowRate = growRate;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_GROWRATE, true);
	}

	void setRemainPoint(int32_t remainPoint)
	{
		mRemainPoint = remainPoint;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_POINT_REMAIN, true);
	}

	void setStrengthPoint(int32_t strengthPoint)
	{
		mStrengthPoint = strengthPoint;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_STR_POINT, true);
	}

	void setSmartnessPoint(int32_t smartnessPoint)
	{
		mSmartnessPoint = smartnessPoint;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_DEX_POINT, true);
	}

	void setMindPoint(int32_t mindPoint)
	{
		mMindPoint = mindPoint;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_INT_POINT, true);
	}

	void setConstitutionPoint(int32_t constitutionPoint)
	{
		mConstitutionPoint = constitutionPoint;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_CON_POINT, true);
	}

	void setExtraInfoLength(int32_t value)
	{
		mExtraInfoLength = value;
	}

	void setIndex(int32_t index)
	{
		mIndex = index;
	}

	void setStallOrder(int32_t stallOrder)
	{
		mStallOrder = stallOrder;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_STALLORDER, true);
	}

	void setPetLock(int32_t petLock)
	{
		mPetLock = petLock;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_LOCK, true);
	}

	void setUnLockTime(uint32_t unLockTime)
	{
		mUnLockTime = unLockTime;
		mFlag64.UpdateBits(PET_DETAIL_ATTR_UNLOCKTIME, true);
	}
private:
	SHorseSkill	m_aSkill[PET_MAX_SKILL_COUNT];
	uchar		m_ExtraInfoData[256];
	int32_t mExtraInfoLength = 0;

	SFlag64 mFlag64;
	int32_t mMapId = -1;
	int32_t mObjectId = -1;
	SHorseGuid mHorseGuid;
	int32_t mTradeIndex;
	int32_t mDataID;
	char mName[MAX_CHARACTER_NAME + 1];
	char mNickName[MAX_CHARACTER_NAME + 1];
	int32_t mAIType;
	int32_t mLevel;
	uint32_t mExp;
	int32_t mHP;
	int32_t mHPMax;
	int32_t mHorseState;
	int32_t mGeneration;
	int32_t mHappiness;
	int32_t mAtt_Near;
	int32_t mAtt_Far;
	int32_t mAtt_Magic;
	int32_t mDef_Near;
	int32_t mDef_Far;
	int32_t mDef_Magic;
	int32_t mHit;
	int32_t mMiss;
	int32_t mCritical;
	int32_t mModelID;
	int32_t mMountID;
	int32_t mStrPerception;
	int32_t mConPerception;
	int32_t mDexPerception;
	int32_t mIntPerception;
	int32_t mStrPerceptionLimit;
	int32_t mConPerceptionLimit;
	int32_t mDexPerceptionLimit;
	int32_t mIntPerceptionLimit;
	int32_t mStrength;
	int32_t mCon;
	int32_t mDex;
	int32_t mIntelligence;
	int32_t mGrowRate;
	int32_t mRemainPoint;
	
	int32_t mStrengthPoint;
	int32_t mSmartnessPoint;
	int32_t mMindPoint;
	int32_t mConstitutionPoint;
	int32_t mIndex;
	int32_t mStallOrder;
	int32_t mPetLock;
	int32_t mUnLockTime;
};