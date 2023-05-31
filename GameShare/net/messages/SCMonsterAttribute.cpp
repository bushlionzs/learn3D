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

	///* 拥有者(是谁控制的) */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_OWNER))
	//{
	//	KYLIN_TRY pCharacterData->Set_OwnerID(mOwnerID);
	//	KYLIN_CATCH("MonsterBaseAttrib 1")
	//}

	///* 占有者(是谁打的，死了算谁的) */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_OCCUPANT))
	//{
	//	KYLIN_TRY pCharacterData->Set_OccupantGUID(mOccupantGUID);
	//	KYLIN_CATCH("MonsterBaseAttrib 2")
	//}

	///* 数据资源ID */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_DATA_ID))
	//{
	//	KYLIN_TRY pCharacterData->Set_RaceID(mDataId);
	//	KYLIN_CATCH("MonsterBaseAttrib 3")
	//}

	///* 姓名 */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_NAME))
	//{
	//	KYLIN_TRY pCharacterData->Set_Name(mName);
	//	KYLIN_CATCH("MonsterBaseAttrib 4")
	//}

	///* 国家头衔 */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_COUNTRYTITLE))
	//{
	//	KYLIN_TRY pCharacterData->Set_CurTitle(mCountryTitle, STitle::GUOJIA_TITLE);
	//	COMMAND_SYS_PTR->AddCommand(GCD_CUR_TITLE_CHANGEED);
	//	KYLIN_CATCH("MonsterBaseAttrib 5")
	//}

	///* 帮会头衔 */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_GUILDTITLE))
	//{
	//	KYLIN_TRY pCharacterData->Set_CurTitle(mGuildTitle, STitle::BANGPAI_TITLE);
	//	COMMAND_SYS_PTR->AddCommand(GCD_CUR_TITLE_CHANGEED);
	//	KYLIN_CATCH("MonsterBaseAttrib 6")
	//}

	///* 玩法头衔 */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_NORMALTITLE))
	//{
	//	KYLIN_TRY pCharacterData->Set_CurTitle(mNormalTitle, STitle::WANFA_TITLE);
	//	COMMAND_SYS_PTR->AddCommand(GCD_CUR_TITLE_CHANGEED);
	//	KYLIN_CATCH("MonsterBaseAttrib 7")
	//}

	///* 等级 */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_LEVEL))
	//{
	//	KYLIN_TRY pCharacterData->Set_Level(mLevel);
	//	KYLIN_CATCH("MonsterBaseAttrib 8")
	//}

	///* HP百分比 */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_HP_PERCENT))
	//{
	//	KYLIN_TRY pCharacterData->Set_HPPercent(mHPPercent / 100.0f);
	//	KYLIN_CATCH("MonsterBaseAttrib 9")
	//}

	///* 隐身级别 */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_STEALTH_LEVEL))
	//{
	//	KYLIN_TRY pCharacterData->Set_StealthLevel(mStealthLevel);
	//	KYLIN_CATCH("MonsterBaseAttrib 10")
	//}

	///*
	// * 是否为坐下状态 ;
	// * if( pPacket->GetFlags()->isSetBit( UPDATE_CHARMONSTER_ATT_SIT ) ) ;
	// * { ;
	// * } ;
	// * 移动速度
	// */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_MOVE_SPEED))
	//{
	//	KYLIN_TRY pCharacterData->Set_MoveSpeed(mMoveSpeed);
	//	KYLIN_CATCH("MonsterBaseAttrib 11")
	//}

	///* 攻击速度 */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_ATTACK_SPEED))
	//{
	//	KYLIN_TRY pCharacterData->Set_AttackSpeed(mAttackSpeed);
	//	KYLIN_CATCH("MonsterBaseAttrib 12")
	//}

	///* 阵营ID */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_CAMP_ID))
	//{
	//	KYLIN_TRY pCharacterData->Set_CampData(&mCampData);
	//	KYLIN_CATCH("MonsterBaseAttrib 13")
	//}

	///* 头像ID */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_PORTRAIT_ID))
	//{
	//	KYLIN_TRY pCharacterData->Set_PortraitID(mPortraitID);
	//	KYLIN_CATCH("MonsterBaseAttrib 14")
	//}

	///* 缩放尺寸 */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_SCALE))
	//{
	//	pCharacterData->Set_CharScale(mScale * 0.001f);
	//}

	////模型ID ;
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_MODEL_ID))
	//{
	//	KYLIN_TRY
	//		pCharacterData->Set_ModelID(mModelID);
	//	KYLIN_CATCH("MonsterBaseAttrib 20")
	//}

	////座骑ID

	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_MOUNT_ID))
	//{
	//	KYLIN_TRY pCharacterData->Set_MountID(mMountID);
	//	KYLIN_CATCH("MonsterBaseAttrib 15")
	//}

	///* AI类型 */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_ATT_AITYPE))
	//{
	//	KYLIN_TRY pCharacterData->Set_AIType(mAIType);
	//	KYLIN_CATCH("MonsterBaseAttrib 16")
	//}

	///* 选择的目标 */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_TARGETID))
	//{
	//	KYLIN_TRY pCharacterData->Set_TargetId(mTargetID);
	//	KYLIN_CATCH("MonsterBaseAttrib 17")
	//}

	///* 方向 */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_DIR))
	//{
	//	KYLIN_TRY pCharacterData->Set_Dir(mDir);
	//	KYLIN_CATCH("MonsterBaseAttrib 18")
	//}

	///* 控制状态 */
	//if (mFlags.isSetBit(UPDATE_CHARMONSTER_CTRL_STATE))
	//{
	//	KYLIN_TRY pCharacterData->Set_ControlState(mCtrlState);
	//	KYLIN_CATCH("MonsterBaseAttrib 19")
	//}

	return true;
}
