#include "stdafx.h"
#include "SCCharHumanBaseAttrib.h"
#include "server/server_manager.h"

SCCharHumanBaseAttrib::SCCharHumanBaseAttrib():
	NetPacket(SC_DEL_QUEST)
{

}

SCCharHumanBaseAttrib::~SCCharHumanBaseAttrib()
{

}

bool SCCharHumanBaseAttrib::process()
{
	CMap * pScene = (CMap*)(SCENE_MANAGER_PTR->GetActiveScene());
	if (NULL == pScene)
	{
		return false;
	}

	KObject* pObj = (KObject*)OBJECT_MANAGER_PTR->FindServerObject(mPlayerId);
	if (pObj == NULL)
	{
		return false;
	}

	KCharacter* pCharObj = (KCharacter*)pObj;

	if (pCharObj->GetCharacterType() != CHAR_BASE_TYPE_ME)
	{
		return false;
	}

	KCharatcterBaseData* pCharacterData = pCharObj->GetCharacterData();

	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_JOB))
	{
		pCharacterData->SetProfession(mJob);
	}

	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_COUNTRY))
	{
		pCharacterData->Set_Country(mCountry);
	}

	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_MODEL_ID))
	{
		//pCharacterData->Set_ModelID(mModelID);
	}

	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_NAME))
	{
		pCharacterData->Set_Name(mName);
	}

	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_COUNTRYTITLE))
	{
		pCharacterData->Set_CurTitle(mCountryTitle, STitle::GUOJIA_TITLE);
	}

	
	bool bSecond = false;
	/* 玩法头衔 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_NORMALTITLE))
	{
		//pCharacterData->Set_CurTitle(mNormalTitle, STitle::WANFA_TITLE);

		//bSecond = true;
	}

	/* 等级 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_LEVEL))
	{
		pCharacterData->Set_Level(mLevel);
	}

	/* HP百分比 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_HP_PERCENT))
	{
		pCharacterData->Set_HPPercent(mHPPercent / 100.0f);

	}

	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_HP))
	{
		pCharacterData->Set_HP(mHP);

	}

	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_HP_MAX))
	{
		pCharacterData->Set_MaxHP(mHPMax);

	}

	/* 怒气 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_RAGE))
	{
		pCharacterData->Set_Rage(mRage);
	}

	/* 怒气上限 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_MAX_RAGE))
	{
		pCharacterData->Set_MaxRage(mMaxRage);
	}

	/* 隐身级别 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_STEALTH_LEVEL))
	{
		pCharacterData->Set_StealthLevel(mStealthLevel);
	}

	/* 是否为坐下状态 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_SIT))
	{
	}

	/* 移动速度 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_MOVE_SPEED))
	{
		pCharacterData->Set_MoveSpeed(mMoveSpeed);
	}

	/* 攻击速度 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_ATTACK_SPEED))
	{
		pCharacterData->Set_AttackSpeed(mAttackSpeed);
	}

	/* 阵营ID */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_CAMP_ID))
	{
		pCharacterData->Set_CampData(&mCampData);
	}

	/* 头像ID */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_PORTRAIT_ID))
	{
		pCharacterData->Set_PortraitID(mPortraitId);
	}

	/* 脸、头发、头发颜色 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_PLAYER_DATA))
	{
		pCharacterData->Set_FaceMesh(mFaceMeshID);
		pCharacterData->Set_HairMesh(mHairMeshID);
	}

	/* 选择的目标 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_TARGETID))
	{
		pCharacterData->Set_TargetId(mTargetID);
	}

	/* PK值 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_PK_VALUE))
	{
		pCharacterData->Set_PKValue(mPKValue);
	}


	/* 骑乘代数 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_BYGENERATION))
	{
		pCharacterData->Set_MountEra(mGeneration);
		bSecond = TRUE;
	}

	/* 角色种族（更换模型）（数据资源ID）, 要放到其他模型数据之后处理, 以保证一次性创建 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_DATA_ID))
	{
		pCharacterData->Set_RaceID(mDataId);
	}

	/* 座骑ID, 要在人物之后创建 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_MOUNT_ID))
	{
		pCharacterData->Set_MountID(mMountID);
	}

	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_CURRENT_HORSE_GUID))
	{
		pCharacterData->Set_CurrentPetGUID(mCurrentHorseGuid);
	}

	/* WorldID */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_WORLDID))
	{
		pCharacterData->Set_WorldID(mWorldID);
	}

	// 需要天赋特效是打开
	/* 天赋 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_INHERENCE_EXP))
	{
		pCharacterData->Set_InherenceExp(mCurInherenceExp);
	}

	if (mFlags.isSetBit(UPDATE_CHARPLAYER_INHERENCE_LEVEL))
	{
		pCharacterData->Set_InherenceLevel(mInherenceLevel);
	}

	if (!bSecond)
	{
		//OBJECT_MANAGER_PTR->GetLoadQueue()->OnRecieveAttribute(pObj->GetServerID());
	}

	return true;
}

void SCCharHumanBaseAttrib::setPlayerId(int32_t playerId)
{
	mPlayerId = playerId;
}



