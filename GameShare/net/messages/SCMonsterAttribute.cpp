#include "stdafx.h"
#include "SCMonsterAttribute.h"

SCMonsterAttribute::SCMonsterAttribute():
	NetPacket(SC_MONSTER_ATTRBUTE)
{

}

SCMonsterAttribute::~SCMonsterAttribute()
{

}

bool SCMonsterAttribute::process()
{
	//KObject* pObj = (KObject*)OBJECT_MANAGER_PTR->FindServerObject(mObjId);
	//if (pObj == NULL)
	//{
	//	return false;
	//}

	//if (NULL == pObj || FALSE == pObj->CheckClassType(GET_CLASS(KCharacter)))
	//	return MP_CONTINUE;

	//KCharacter* pCharObj = (KCharacter*)pObj;


	//int type = pCharObj->GetCharacterType();


	//if (type != CHAR_BASE_TYPE_NPC)
	//{
	//	return false;
	//}

	//KCharatcterBaseData* pCharacterData = pCharObj->GetCharacterData();

	///* ӵ����(��˭���Ƶ�) */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_OWNER))
	//{
	//	KYLIN_TRY pCharacterData->Set_OwnerID(mOwnerID);
	//	KYLIN_CATCH("MonsterBaseAttrib 1")
	//}

	///* ռ����(��˭��ģ�������˭��) */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_OCCUPANT))
	//{
	//	KYLIN_TRY pCharacterData->Set_OccupantGUID(mOccupantGUID);
	//	KYLIN_CATCH("MonsterBaseAttrib 2")
	//}

	///* ������ԴID */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_DATA_ID))
	//{
	//	KYLIN_TRY pCharacterData->Set_RaceID(mDataId);
	//	KYLIN_CATCH("MonsterBaseAttrib 3")
	//}

	///* ���� */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_NAME))
	//{
	//	KYLIN_TRY pCharacterData->Set_Name(mName);
	//	KYLIN_CATCH("MonsterBaseAttrib 4")
	//}

	///* ����ͷ�� */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_COUNTRYTITLE))
	//{
	//	KYLIN_TRY pCharacterData->Set_CurTitle(mCountryTitle, STitle::GUOJIA_TITLE);
	//	COMMAND_SYS_PTR->AddCommand(GCD_CUR_TITLE_CHANGEED);
	//	KYLIN_CATCH("MonsterBaseAttrib 5")
	//}

	///* ���ͷ�� */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_GUILDTITLE))
	//{
	//	KYLIN_TRY pCharacterData->Set_CurTitle(mGuildTitle, STitle::BANGPAI_TITLE);
	//	COMMAND_SYS_PTR->AddCommand(GCD_CUR_TITLE_CHANGEED);
	//	KYLIN_CATCH("MonsterBaseAttrib 6")
	//}

	///* �淨ͷ�� */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_NORMALTITLE))
	//{
	//	KYLIN_TRY pCharacterData->Set_CurTitle(mNormalTitle, STitle::WANFA_TITLE);
	//	COMMAND_SYS_PTR->AddCommand(GCD_CUR_TITLE_CHANGEED);
	//	KYLIN_CATCH("MonsterBaseAttrib 7")
	//}

	///* �ȼ� */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_LEVEL))
	//{
	//	KYLIN_TRY pCharacterData->Set_Level(mLevel);
	//	KYLIN_CATCH("MonsterBaseAttrib 8")
	//}

	///* HP�ٷֱ� */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_HP_PERCENT))
	//{
	//	KYLIN_TRY pCharacterData->Set_HPPercent(mHPPercent / 100.0f);
	//	KYLIN_CATCH("MonsterBaseAttrib 9")
	//}

	///* ������ */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_STEALTH_LEVEL))
	//{
	//	KYLIN_TRY pCharacterData->Set_StealthLevel(mStealthLevel);
	//	KYLIN_CATCH("MonsterBaseAttrib 10")
	//}

	///*
	// * �Ƿ�Ϊ����״̬ ;
	// * if( pPacket->GetFlags()->isSetBit( UPDATE_CHARMONSTER_ATT_SIT ) ) ;
	// * { ;
	// * } ;
	// * �ƶ��ٶ�
	// */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_MOVE_SPEED))
	//{
	//	KYLIN_TRY pCharacterData->Set_MoveSpeed(mMoveSpeed);
	//	KYLIN_CATCH("MonsterBaseAttrib 11")
	//}

	///* �����ٶ� */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_ATTACK_SPEED))
	//{
	//	KYLIN_TRY pCharacterData->Set_AttackSpeed(mAttackSpeed);
	//	KYLIN_CATCH("MonsterBaseAttrib 12")
	//}

	///* ��ӪID */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_CAMP_ID))
	//{
	//	KYLIN_TRY pCharacterData->Set_CampData(&mCampData);
	//	KYLIN_CATCH("MonsterBaseAttrib 13")
	//}

	///* ͷ��ID */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_PORTRAIT_ID))
	//{
	//	KYLIN_TRY pCharacterData->Set_PortraitID(mPortraitID);
	//	KYLIN_CATCH("MonsterBaseAttrib 14")
	//}

	///* ���ųߴ� */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_SCALE))
	//{
	//	pCharacterData->Set_CharScale(mScale * 0.001f);
	//}

	////ģ��ID ;
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_MODEL_ID))
	//{
	//	KYLIN_TRY
	//		pCharacterData->Set_ModelID(mModelID);
	//	KYLIN_CATCH("MonsterBaseAttrib 20")
	//}

	////����ID

	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_MOUNT_ID))
	//{
	//	KYLIN_TRY pCharacterData->Set_MountID(mMountID);
	//	KYLIN_CATCH("MonsterBaseAttrib 15")
	//}

	///* AI���� */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_AITYPE))
	//{
	//	KYLIN_TRY pCharacterData->Set_AIType(mAIType);
	//	KYLIN_CATCH("MonsterBaseAttrib 16")
	//}

	///* ѡ���Ŀ�� */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_TARGETID))
	//{
	//	KYLIN_TRY pCharacterData->Set_TargetId(mTargetID);
	//	KYLIN_CATCH("MonsterBaseAttrib 17")
	//}

	///* ���� */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_DIR))
	//{
	//	KYLIN_TRY pCharacterData->Set_Dir(mDir);
	//	KYLIN_CATCH("MonsterBaseAttrib 18")
	//}

	///* ����״̬ */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_CTRL_STATE))
	//{
	//	KYLIN_TRY pCharacterData->Set_ControlState(mCtrlState);
	//	KYLIN_CATCH("MonsterBaseAttrib 19")
	//}

	return true;
}
