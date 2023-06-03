#include "OgreHeader.h"
#include "SCCharHumanBaseAttrib.h"
#include "game_scene_manager.h"
#include "KObjectManager.h"
#include "kplayer.h"
#include "data/GameDataCharacter.h"

bool SCCharHumanBaseAttrib::process()
{
	GameScene* pScene = GameSceneManager::getSingleton().GetActiveScene();

	if (NULL == pScene)
	{
		return false;
	}

	KObject* pObj = KObjectManager::GetSingleton().getObject(mPlayerId);
	if (pObj == nullptr)
	{
		pObj = KObjectManager::GetSingleton().createPlayer(mPlayerId);
	}

	
	if (pObj->getObjectType() != ObjectType_PlayerOfMe)
	{
		return false;
	}

	KCharacter* pCharObj = (KCharacter*)pObj;

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
	/* �淨ͷ�� */


	/* �ȼ� */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_LEVEL))
	{
		pCharacterData->Set_Level(mLevel);
	}

	/* HP�ٷֱ� */
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

	/* ŭ�� */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_RAGE))
	{
		pCharacterData->Set_Rage(mRage);
	}

	/* ŭ������ */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_MAX_RAGE))
	{
		pCharacterData->Set_MaxRage(mMaxRage);
	}

	/* ������ */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_STEALTH_LEVEL))
	{
		pCharacterData->Set_StealthLevel(mStealthLevel);
	}

	/* �Ƿ�Ϊ����״̬ */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_SIT))
	{
	}

	/* �ƶ��ٶ� */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_MOVE_SPEED))
	{
		pCharacterData->Set_MoveSpeed(mMoveSpeed);
	}

	/* �����ٶ� */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_ATTACK_SPEED))
	{
		pCharacterData->Set_AttackSpeed(mAttackSpeed);
	}

	/* ��ӪID */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_CAMP_ID))
	{
		pCharacterData->Set_CampData(&mCampData);
	}

	/* ͷ��ID */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_PORTRAIT_ID))
	{
		pCharacterData->Set_PortraitID(mPortraitId);
	}

	/* ����ͷ����ͷ����ɫ */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_PLAYER_DATA))
	{
		pCharacterData->Set_FaceMesh(mFaceMeshID);
		pCharacterData->Set_HairMesh(mHairMeshID);
	}

	/* ѡ���Ŀ�� */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_TARGETID))
	{
		pCharacterData->Set_TargetId(mTargetID);
	}

	/* PKֵ */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_PK_VALUE))
	{
		pCharacterData->Set_PKValue(mPKValue);
	}


	/* ��˴��� */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_BYGENERATION))
	{
		pCharacterData->Set_MountEra(mGeneration);
		bSecond = TRUE;
	}

	/* ��ɫ���壨����ģ�ͣ���������ԴID��, Ҫ�ŵ�����ģ������֮����, �Ա�֤һ���Դ��� */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_DATA_ID))
	{
		pCharacterData->Set_RaceID(mDataId);
	}

	/* ����ID, Ҫ������֮�󴴽� */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_MOUNT_ID))
	{
		pCharacterData->Set_MountID(mMountID);
	}

	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_CURRENT_HORSE_GUID))
	{
		pCharacterData->Set_CurrentPetGUID(mCurrentHorseGuid);
	}

	// ��Ҫ�츳��Ч�Ǵ�
	/* �츳 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_INHERENCE_EXP))
	{
		pCharacterData->Set_InherenceExp(mCurInherenceExp);
	}

	if (mFlags.isSetBit(UPDATE_CHARPLAYER_INHERENCE_LEVEL))
	{
		pCharacterData->Set_InherenceLevel(mInherenceLevel);
	}

	return true;
}