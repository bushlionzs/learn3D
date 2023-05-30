#pragma once
#include "net/net_message.h"
class SCCharHumanBaseAttrib : public NetPacket
{
public:
	enum ENUM_UPDATE_CHARPLAYER_ATT
	{
		UPDATE_CHARPLAYER_ATT_JOB = 0,
		UPDATE_CHARPLAYER_ATT_COUNTRY,
		UPDATE_CHARPLAYER_ATT_DATA_ID,
		UPDATE_CHARPLAYER_ATT_NAME,
		UPDATE_CHARPLAYER_ATT_COUNTRYTITLE,
		UPDATE_CHARPLAYER_ATT_GUILDTITLE,
		UPDATE_CHARPLAYER_ATT_NORMALTITLE,
		UPDATE_CHARPLAYER_ATT_LEVEL,
		UPDATE_CHARPLAYER_ATT_HP_PERCENT,
		UPDATE_CHARPLAYER_ATT_HP,
		UPDATE_CHARPLAYER_ATT_HP_MAX,
		UPDATE_CHARPLAYER_ATT_RAGE,
		UPDATE_CHARPLAYER_ATT_MAX_RAGE,
		UPDATE_CHARPLAYER_ATT_STEALTH_LEVEL,
		UPDATE_CHARPLAYER_ATT_SIT,
		UPDATE_CHARPLAYER_ATT_MOVE_SPEED,
		UPDATE_CHARPLAYER_ATT_ATTACK_SPEED,
		UPDATE_CHARPLAYER_ATT_CAMP_ID,
		UPDATE_CHARPLAYER_ATT_PORTRAIT_ID,
		UPDATE_CHARPLAYER_ATT_MODEL_ID,
		UPDATE_CHARPLAYER_ATT_MOUNT_ID,
		UPDATE_CHARPLAYER_ATT_CURRENT_HORSE_GUID,
		UPDATE_CHARPLAYER_ATT_PLAYER_DATA,
		UPDATE_CHARPLAYER_IS_IN_STALL,
		UPDATE_CHARPLAYER_STALL_NAME,
		UPDATE_CHARPLAYER_BUS_STATE,
		UPDATE_CHARPLAYER_BUSID,
		UPDATE_CHARPLAYER_GUILD,
		UPDATE_CHARPLAYER_GUILDPOSITION,
		UPDATE_CHARPLAYER_TARGETID,
		UPDATE_CHARPLAYER_PK_VALUE,
		UPDATE_CHARPLAYER_TEAM_ID,
		UPDATE_CHARPLAYER_BYGENERATION,
		UPDATE_CHARPLAYER_HIDE_NAME,
		UPDATE_CHARPLAYER_SCALE,
		UPDATE_CHARPLAYER_WORLDID,
		//需要天赋特效时打开
		UPDATE_CHARPLAYER_INHERENCE_EXP,
		UPDATE_CHARPLAYER_INHERENCE_LEVEL,
		UPDATE_CHARPLAYER_ATT_NUMBERS
	};
public:
	SCCharHumanBaseAttrib();
	~SCCharHumanBaseAttrib();

	virtual bool process();

	void setPlayerId(int32_t playerId);
	void setJob(int32_t job)
	{
		mJob = job;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_JOB, TRUE);
	}
	void setCountry(int32_t country)
	{
		mCountry = country;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_COUNTRY, TRUE);
	}

	void setDataId(int32_t dataId)
	{
		mDataId = dataId;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_DATA_ID, TRUE);
	}

	void setLevel(int32_t level)
	{
		mLevel = level;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_LEVEL, TRUE);
	}

	void setHPPercent(int32_t hpPercent)
	{
		mHPPercent = hpPercent;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_HP_PERCENT, TRUE);
	}

	void setHP(int32_t hp)
	{
		mHP = hp;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_HP, TRUE);
	}

	void setHPMAX(int32_t hp_max)
	{
		mHPMax = hp_max;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_HP_MAX, TRUE);
	}

	void setRage(int32_t rage)
	{
		mRage = rage;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_RAGE, TRUE);
	}

	void setMaxRage(int32_t maxRage)
	{
		mMaxRage = maxRage;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_MAX_RAGE, TRUE);
	}

	void setStealthLevel(int32_t level)
	{
		mStealthLevel = level;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_STEALTH_LEVEL, TRUE);
	}

	void setMoodState(int32_t state)
	{
		mMoodState = state;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_SIT, TRUE);
	}

	void setMoveSpeed(float speed)
	{
		mMoveSpeed = speed;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_MOVE_SPEED, TRUE);
	}

	void setAttackSpeed(float speed)
	{
		mAttackSpeed = speed;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_ATTACK_SPEED, TRUE);
	}

	void setCampData(const SCampData& campData)
	{
		mCampData = campData;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_CAMP_ID, TRUE);
	}

	void setPortraitID(int32_t id)
	{
		mPortraitId = id;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_PORTRAIT_ID, TRUE);
	}

	void setModelID(int32_t id)
	{
		mModelID = id;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_MODEL_ID, TRUE);
	}

	void setMountID(int32_t id)
	{
		mMountID = id;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_MOUNT_ID, TRUE);
	}

	void setCurentHorseGuid(SHorseGuid guid)
	{
		mCurrentHorseGuid = guid;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_CURRENT_HORSE_GUID, TRUE);
	}

	void setName(const char* name)
	{
		strncpy(mName, name, sizeof(mName));
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_NAME, TRUE);
	}


	void setCountryTitle(const char* title)
	{
		strncpy(mCountryTitle, title, sizeof(mName));
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_COUNTRYTITLE, TRUE);
	}

	void setGuildTitle(const char* title)
	{
		strncpy(mGuildTitle, title, sizeof(mName));
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_GUILDTITLE, TRUE);
	}

	void setNormalTitle(const char* title)
	{
		strncpy(mNormalTitle, title, sizeof(mName));
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_NORMALTITLE, TRUE);
	}
	void setCountryTitleType(int32_t type)
	{
		mCountryTitleType = type;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_COUNTRYTITLE, TRUE);
	}

	void setGuildTitleType(int32_t type)
	{
		mGuildTitleType = type;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_GUILDTITLE, TRUE);
	}

	void setNormalTitleType(int32_t type)
	{
		mNormalTitleType = type;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_NORMALTITLE, TRUE);
	}

	void setStallIsOpen(int32_t value)
	{
		mStallIsOpen = value;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_IS_IN_STALL, TRUE);
	}

	void setTargetID(int32_t id)
	{
		mTargetID = id;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_TARGETID, TRUE);
	}

	void setWorldID(int32_t id)
	{
		mWorldID = id;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_WORLDID, TRUE);
	}

	void setCurInherenceExp(uint32_t exp)
	{
		mCurInherenceExp = exp;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_NORMALTITLE, TRUE);
	}

	void setInherenceLevel(int32_t level)
	{
		mInherenceLevel = level;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_INHERENCE_LEVEL, TRUE);
	}

	void setFaceMeshID(uint32 uMeshID)
	{
		mFaceMeshID = uMeshID;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_PLAYER_DATA, TRUE);
	}
	void setHairMeshID(uint32 uMeshID)
	{
		mHairMeshID = uMeshID;
		mFlags.UpdateBits(UPDATE_CHARPLAYER_ATT_PLAYER_DATA, TRUE);
	}


private:
	int32_t mPlayerId = -1;
	SFlag64 mFlags;

	int32_t mJob;
	int32_t mCountry;
	int32_t mDataId;
	int32_t mLevel;
	int32_t mHairMeshID;
	int32_t mFaceMeshID;
	int32_t mHPPercent;
	int32_t mHP;
	int32_t mHPMax;
	int32_t mRage;
	int32_t mMaxRage;
	int32_t mStealthLevel;
	int32_t mMoodState;
	float   mMoveSpeed;
	float   mAttackSpeed;
	SCampData mCampData;
	int32_t mPortraitId;
	int32_t mModelID;
	int32_t mMountID;
	char    mName[MAX_CHARACTER_NAME + 1];
	char    mCountryTitle[MAX_CHARACTER_TITLE + 1];
	char    mGuildTitle[MAX_CHARACTER_TITLE + 1];
	char    mNormalTitle[MAX_CHARACTER_TITLE + 1];
	int32_t mCountryTitleType;
	int32_t mGuildTitleType;
	int32_t mNormalTitleType;
	int32_t mStallIsOpen;
	int32_t mTargetID;
	int32_t mPKValue;
	int32_t mGeneration;
	int32_t mWorldID;
	uint32_t  mCurInherenceExp;
	uint32_t mInherenceLevel;
	SHorseGuid mCurrentHorseGuid;
};