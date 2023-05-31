#pragma once
#include "net/net_message.h"
#include "StructDB.h"
class SCDetailAttrib : public NetPacket
{
public:
	

	enum HorseState 
	{ 
		HorseState_Normal, 
		HorseState_Mating, 
		HorseState_Compose 
	};
public:
	SCDetailAttrib();
	~SCDetailAttrib();

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
	bool    mCurrentHorseFlag = false;
};