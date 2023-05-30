#pragma once

#include "net/net_message.h"

class SCMonsterAttribute : public NetPacket
{
public:
	enum ENUM_UPDATE_CHARMONSTER_ATT
	{
		UPDATE_CHARMONSTER_ATT_DATA_ID = 0,
		UPDATE_CHARMONSTER_ATT_NAME,
		UPDATE_CHARMONSTER_ATT_COUNTRYTITLE,
		UPDATE_CHARMONSTER_ATT_GUILDTITLE,
		UPDATE_CHARMONSTER_ATT_NORMALTITLE,
		UPDATE_CHARMONSTER_ATT_LEVEL,
		UPDATE_CHARMONSTER_ATT_HP_PERCENT,
		UPDATE_CHARMONSTER_ATT_STEALTH_LEVEL,
		UPDATE_CHARMONSTER_ATT_SIT,
		UPDATE_CHARMONSTER_ATT_MOVE_SPEED,
		UPDATE_CHARMONSTER_ATT_ATTACK_SPEED,
		UPDATE_CHARMONSTER_ATT_CAMP_ID,
		UPDATE_CHARMONSTER_ATT_PORTRAIT_ID,
		UPDATE_CHARMONSTER_ATT_MODEL_ID,
		UPDATE_CHARMONSTER_ATT_MOUNT_ID,
		UPDATE_CHARMONSTER_ATT_AITYPE,
		UPDATE_CHARMONSTER_OCCUPANT,
		UPDATE_CHARMONSTER_OWNER,
		UPDATE_CHARMONSTER_TARGETID,
		UPDATE_CHARMONSTER_DIR,
		UPDATE_CHARMONSTER_CTRL_STATE,
		UPDATE_CHARMONSTER_SCALE,
		UPDATE_CHARMONSTER_ATT_NUMBERS
	};
public:
	SCMonsterAttribute();
	~SCMonsterAttribute();
	virtual bool process();

	void setObjId(int32_t id)
	{
		mObjId = id;
	}
	void setHpPercent(int32_t percent)
	{
		mHPPercent = percent;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_HP_PERCENT, true);
	}

	void setLevel(int32_t level)
	{
		mLevel = level;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_LEVEL, true);
	}

	void setDataID(int32_t id)
	{
		mDataId = id;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_DATA_ID, true);
	}

	void setStealthLevel(int32_t level)
	{
		mStealthLevel = level;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_STEALTH_LEVEL, true);
	}
	
	void setMoodState(int32_t state)
	{
		mMoodState = state;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_SIT, true);
	}

	void setMoveSpeed(float  speed)
	{
		mMoveSpeed = speed;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_MOVE_SPEED, true);
	}

	void setAttackSpeed(float  speed)
	{
		mAttackSpeed = speed;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_ATTACK_SPEED, true);
	}

	void setCampData(const SCampData & campData)
	{
		mCampData = campData;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_SIT, true);
	}

	void setPortraitID(int32_t  id)
	{
		mPortraitID = id;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_PORTRAIT_ID, true);
	}

	void setModelID(int32_t  id)
	{
		mModelID = id;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_MODEL_ID, true);
	}

	void setMountID(int32_t  id)
	{
		mMountID = id;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_MOUNT_ID, true);
	}

	void setAIType(int32_t  type)
	{
		mAIType = type;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_AITYPE, true);
	}

	void setName(const char* name)
	{
		strncpy(mName, name, sizeof(mName));
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_NAME, true);
	}

	void setCountryTitle(const char* title)
	{
		strncpy(mCountryTitle, title, sizeof(mCountryTitle));
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_COUNTRYTITLE, true);
	}

	void setGuildTitle(const char* title)
	{
		strncpy(mGuildTitle, title, sizeof(mGuildTitle));
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_GUILDTITLE, true);
	}

	void setNormalTitle(const char* title)
	{
		strncpy(mNormalTitle, title, sizeof(mNormalTitle));
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_NORMALTITLE, true);
	}

	void setCountryTitleType(int32_t  type)
	{
		mCountryTitleType = type;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_COUNTRYTITLE, true);
	}

	void setGuildTitleType(int32_t  type)
	{
		mGuildTitleType = type;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_GUILDTITLE, true);
	}

	void setNormalTitleType(int32_t  type)
	{
		mNormalTitleType = type;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_ATT_NORMALTITLE, true);
	}

	void setOccupantGUID(int32_t  type)
	{
		mOccupantGUID = type;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_OCCUPANT, true);
	}

	void setOwnerID(int32_t  ownerID)
	{
		mOwnerID = ownerID;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_OWNER, true);
	}

	void setTargetID(int32_t  targetID)
	{
		mTargetID = targetID;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_TARGETID, true);
	}

	void setDir(float  dir)
	{
		mDir = dir;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_DIR, true);
	}

	void setCtrlState(float  ctrlState)
	{
		mCtrlState = ctrlState;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_CTRL_STATE, true);
	}

	void setScale(float scale)
	{
		mScale = scale;
		mFlags.UpdateBits(UPDATE_CHARMONSTER_SCALE, true);
	}

	void setRefreshTag(uint8_t refresh)
	{
		mRefresh = refresh;
	}
private:
	uint8_t mRefresh = 0;
	SFlag64 mFlags;
	int32_t mObjId = -1;
	int32_t mDataId;
	int32_t mLevel;
	int32_t mHPPercent;
	int32_t mStealthLevel;
	int32_t mMoodState;
	float   mMoveSpeed;
	float   mAttackSpeed;
	SCampData mCampData;
	int32_t mPortraitID;
	int32_t mModelID;
	int32_t mMountID;
	int32_t mAIType;
	char mName[MAX_CHARACTER_NAME + 1];
	char mCountryTitle[MAX_CHARACTER_TITLE + 1];
	char mGuildTitle[MAX_CHARACTER_TITLE + 1];
	char mNormalTitle[MAX_CHARACTER_TITLE + 1];
	int32_t mCountryTitleType;
	int32_t mGuildTitleType;
	int32_t mNormalTitleType;
	GUID_t mOccupantGUID;
	int32_t mOwnerID;
	int32_t mTargetID;
	float mDir;
	int32_t mCtrlState;
	float mScale = 1.0f;
};