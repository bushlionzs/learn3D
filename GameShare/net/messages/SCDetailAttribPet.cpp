#include "stdafx.h"
#include "SCDetailAttribPet.h"


SCDetailAttribPet::SCDetailAttribPet():
	NetPacket(SC_DETAIL_ATTRIB_PET)
{

}

SCDetailAttribPet::~SCDetailAttribPet()
{

}

bool SCDetailAttribPet::process()
{
	//if (mExtraInfoLength != 0 && m_ExtraInfoData[0] != TYPE_COMPOSE_PET)
	//{
	//	return false;
	//}

	//if (0 == mFlag64.m_uHighFlags && 0 == mFlag64.m_uLowFlags) 
	//	return false;

	//if (mHorseGuid.IsNull())
	//	return false;


	//BOOL		bNewPet = TRUE; /* �Ƿ��½� */
	//int32			iStallOrder = INVALID_ID;
	//SDataPet* pMyPet = GAME_DATA_PET_PTR->GetPetByIndex(mHorseGuid, nullptr);

	//if (pMyPet)
	//{
	//	iStallOrder = GAME_DATA_PET_PTR->GetPetByGuid(pMyPet->m_GUID);
	//	bNewPet = FALSE;
	//}
	//else
	//{
	//	/* ����˱����stallorder */
	//	if (!mFlag64.isSetBit(PET_DETAIL_ATTR_STALLORDER)) 
	//		return false;
	//	iStallOrder = mStallOrder;
	//	pMyPet = GAME_DATA_PET_PTR->GetPetByIndex(iStallOrder);
	//}

	//if (!pMyPet) 
	//	return false;
	//if (INVALID_ID == iStallOrder) 
	//	return false;
	//if (NULL == pMyPet) 
	//	return false;

	//BOOL	bEffectUpdate = FALSE;
	//BOOL	bBaseAttrChanged = FALSE;
	//BOOL	bSkillUpdate = FALSE;

	///* ����GUID */
	//pMyPet->m_GUID = mHorseGuid;

	///* ����״̬ */
	//if (HorseState_Mating == mHorseState)
	//{
	//	pMyPet->m_nState = MOUNT_STATE_MATING;
	//}
	//else if (MOUNT_STATE_MATING == pMyPet->m_nState)
	//{
	//	pMyPet->m_nState = MOUNT_STATE_IDLE;
	//}

	//if (mIndex >= 0) pMyPet->m_nServerIndex = mIndex;

	///* ��������ID */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_DATA_ID)) 
	//	pMyPet->m_nBaseID = mDataID;

	///* ���� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_NAME)) 
	//	pMyPet->m_szName = mName;

	///* �ǳ� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_NICK_NAME)) 
	//	pMyPet->m_szNickname = mNickName;

	///*
	// * �Ա� ;
	// * if ( flagDetail.isSetBit(PET_DETAIL_ATTR_SEX) ) pMyPet->m_nGender = pPacket->GetSex();
	// * ;
	// * ��żID ;
	// * if ( flagDetail.isSetBit(PET_DETAIL_ATTR_SPOUSE_GUID) ) pMyPet->m_SpouseGUID = pPacket->GetSpouseGUID();
	// * ;
	// * �ȼ�
	// */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_LEVEL)) 
	//	pMyPet->m_nLevel = mLevel;

	///* ������ */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_GENERATION)) 
	//	pMyPet->m_nEraCount = mGeneration;

	///* ���ֶ� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_HAPPINESS))
	//{
	//	pMyPet->m_nHappiness = mHappiness;
	//	COMMAND_SYS_PTR->AddCommand(GCD_MOUNT_HAPPINESS_UPDATE);
	//}

	///* ���� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_EXP))
	//{
	//	int64 nOldExp = pMyPet->m_nExp;

	//	pMyPet->m_nExp = mExp;

	//	/* ��ʾ�����þ���ֵ����ʾ��Ϣ */
	//	if (pMyPet->m_nExp > nOldExp && FALSE == bNewPet)
	//	{
	//		STRING	strTemp = UI_SYSTEM_PTR->ParserString_VarParam
	//		(
	//			"XCDetailAttrib_Pet_PetExpUp",
	//			pMyPet->m_szName.c_str(),
	//			pMyPet->m_nExp - nOldExp
	//		);

	//		SHOW_TALKMSG(strTemp.c_str());
	//	}
	//}

	///* �������� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_STRPERCEPTION))
	//{
	//	if (pMyPet->m_nAttrStrApt != mStrPerception)
	//	{
	//		pMyPet->m_nAttrStrApt = mStrPerception;
	//		bEffectUpdate = TRUE;
	//	}
	//}

	///* �������� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_CONPERCEPTION))
	//{
	//	if (pMyPet->m_nAttrConApt != mConPerception)
	//	{
	//		pMyPet->m_nAttrConApt = mConPerception;
	//		bEffectUpdate = TRUE;
	//	}
	//}

	///* �������� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_DEXPERCEPTION))
	//{
	//	if (pMyPet->m_nAttrDexApt != mDexPerception)
	//	{
	//		pMyPet->m_nAttrDexApt = mDexPerception;
	//		bEffectUpdate = TRUE;
	//	}
	//}

	///* �������� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_INTPERCEPTION))
	//{
	//	if (pMyPet->m_nAttrIntApt != mIntPerception)
	//	{
	//		pMyPet->m_nAttrIntApt = mIntPerception;
	//		bEffectUpdate = TRUE;
	//	}
	//}

	///* ����������� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_MAX_STR_PER))
	//	pMyPet->m_nAttrMaxStrApt = mStrPerceptionLimit;

	///* ����������� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_MAX_CON_PER))
	//	pMyPet->m_nAttrMaxConApt = mConPerceptionLimit;

	///* ����������� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_MAX_DEX_PER))
	//	pMyPet->m_nAttrMaxDexApt = mDexPerceptionLimit;

	///* ����������� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_MAX_INT_PER))
	//	pMyPet->m_nAttrMaxIntApt = mIntPerceptionLimit;

	///* �Ƿ����� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_LOCK)) 
	//	pMyPet->m_byLock = mPetLock;

	///* ����ʱ�� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_UNLOCKTIME)) 
	//	pMyPet->m_UnLockTime = mUnLockTime;

	///* ���� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_STR))
	//{
	//	pMyPet->m_nAttrStr = mStrength;
	//	bBaseAttrChanged = TRUE;
	//}

	///* ���� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_CON))
	//{
	//	pMyPet->m_nAttrCon = mCon;
	//	bBaseAttrChanged = TRUE;
	//}

	///* ���� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_DEX))
	//{
	//	pMyPet->m_nAttrDex = mDex;
	//	bBaseAttrChanged = TRUE;
	//}

	///* ���� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_INT))
	//{
	//	pMyPet->m_nAttrInt = mIntelligence;
	//	bBaseAttrChanged = TRUE;
	//}

	///* ������ֵ */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_STR_POINT))
	//{
	//	pMyPet->m_nAttrStrAdd = mStrengthPoint;
	//	bBaseAttrChanged = TRUE;
	//}

	///* ������ֵ */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_CON_POINT))
	//{
	//	pMyPet->m_nAttrConAdd = mConstitutionPoint;
	//	bBaseAttrChanged = TRUE;
	//}

	///* ���ݼ�ֵ */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_DEX_POINT))
	//{
	//	pMyPet->m_nAttrDexAdd = mSmartnessPoint;
	//	bBaseAttrChanged = TRUE;
	//}

	///* ������ֵ */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_INT_POINT))
	//{
	//	pMyPet->m_nAttrIntAdd = mMindPoint;
	//	bBaseAttrChanged = TRUE;
	//}

	///*
	// * ���� ;
	// * if ( flagDetail.isSetBit(PET_DETAIL_ATTR_GENGU) ) pMyPet->m_nBasic = pPacket->GetGenGu();
	// * ;
	// * Ǳ��
	// */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_POINT_REMAIN))
	//{
	//	pMyPet->m_nPotential = mRemainPoint;
	//	bBaseAttrChanged = TRUE;
	//}

	///*
	// * ���� ;
	// * if ( flagDetail.isSetBit(PET_DETAIL_ATTR_SAVVY) ) pMyPet->m_nSavvy = pPacket->GetSavvy();
	// * ;
	// * �ɳ���
	// */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_GROWRATE)) 
	//	pMyPet->m_nUpRate = mGrowRate;

	///* ����1 */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_SKILL_0))
	//{
	//	bSkillUpdate = TRUE;

	//	const SHorseSkill* pOwnerSkill = GetSkill(0);

	//	if (pOwnerSkill)
	//		GAME_DATA_PET_PTR->Pet_SetSkill(iStallOrder, 0, pOwnerSkill->m_nSkillID, pOwnerSkill->m_bCanUse);
	//}

	///* ����2 */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_SKILL_1))
	//{
	//	bSkillUpdate = TRUE;

	//	const SHorseSkill* pOwnerSkill = GetSkill(1);

	//	if (pOwnerSkill)
	//		GAME_DATA_PET_PTR->Pet_SetSkill(iStallOrder, 1, pOwnerSkill->m_nSkillID, pOwnerSkill->m_bCanUse);
	//}

	///* ����3 */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_SKILL_2))
	//{
	//	bSkillUpdate = TRUE;

	//	const SHorseSkill* pOwnerSkill = GetSkill(2);

	//	if (pOwnerSkill)
	//		GAME_DATA_PET_PTR->Pet_SetSkill(iStallOrder, 2, pOwnerSkill->m_nSkillID, pOwnerSkill->m_bCanUse);
	//}

	///* ����4 */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_SKILL_3))
	//{
	//	bSkillUpdate = TRUE;

	//	const SHorseSkill* pOwnerSkill = GetSkill(3);

	//	if (pOwnerSkill)
	//		GAME_DATA_PET_PTR->Pet_SetSkill(iStallOrder, 3, pOwnerSkill->m_nSkillID, pOwnerSkill->m_bCanUse);
	//}

	///* ����5 */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_SKILL_4))
	//{
	//	bSkillUpdate = TRUE;

	//	const SHorseSkill* pOwnerSkill = GetSkill(4);

	//	if (pOwnerSkill)
	//		GAME_DATA_PET_PTR->Pet_SetSkill(iStallOrder, 4, pOwnerSkill->m_nSkillID, pOwnerSkill->m_bCanUse);
	//}

	///* ����6 */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_SKILL_5))
	//{
	//	bSkillUpdate = TRUE;

	//	const SHorseSkill* pOwnerSkill = GetSkill(5);

	//	if (pOwnerSkill)
	//		GAME_DATA_PET_PTR->Pet_SetSkill(iStallOrder, 5, pOwnerSkill->m_nSkillID, pOwnerSkill->m_bCanUse);
	//}

	///* ����7 */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_SKILL_6))
	//{
	//	bSkillUpdate = TRUE;

	//	const SHorseSkill* pOwnerSkill = GetSkill(6);

	//	if (pOwnerSkill)
	//		GAME_DATA_PET_PTR->Pet_SetSkill(iStallOrder, 6, pOwnerSkill->m_nSkillID, pOwnerSkill->m_bCanUse);
	//}

	///* ����8 */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_SKILL_7))
	//{
	//	bSkillUpdate = TRUE;

	//	const SHorseSkill* pOwnerSkill = GetSkill(7);

	//	if (pOwnerSkill)
	//		GAME_DATA_PET_PTR->Pet_SetSkill(iStallOrder, 7, pOwnerSkill->m_nSkillID, pOwnerSkill->m_bCanUse);
	//}

	///* ����9 */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_SKILL_8))
	//{
	//	bSkillUpdate = TRUE;

	//	const SHorseSkill* pOwnerSkill = GetSkill(8);

	//	if (pOwnerSkill)
	//		GAME_DATA_PET_PTR->Pet_SetSkill(iStallOrder, 8, pOwnerSkill->m_nSkillID, pOwnerSkill->m_bCanUse);
	//}

	///* ����10 */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_SKILL_9))
	//{
	//	bSkillUpdate = TRUE;

	//	const SHorseSkill* pOwnerSkill = GetSkill(9);

	//	if (pOwnerSkill)
	//		GAME_DATA_PET_PTR->Pet_SetSkill(iStallOrder, 9, pOwnerSkill->m_nSkillID, pOwnerSkill->m_bCanUse);
	//}

	///* ����11 */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_SKILL_10))
	//{
	//	bSkillUpdate = TRUE;

	//	const SHorseSkill* pOwnerSkill = GetSkill(10);

	//	if (pOwnerSkill)
	//		GAME_DATA_PET_PTR->Pet_SetSkill(iStallOrder, 10, pOwnerSkill->m_nSkillID, pOwnerSkill->m_bCanUse);
	//}

	///* ����12 */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_SKILL_11))
	//{
	//	bSkillUpdate = TRUE;

	//	const SHorseSkill* pOwnerSkill = GetSkill(11);

	//	if (pOwnerSkill)
	//		GAME_DATA_PET_PTR->Pet_SetSkill(iStallOrder, 11, pOwnerSkill->m_nSkillID, pOwnerSkill->m_bCanUse);
	//}

	///* ������� */
	//if (mFlag64.isSetBit(PET_DETAIL_ATTR_MOUNTID))
	//{
	//	/* TABLE_DEFINEHANDLE(s_pCharMountDBC, TABLE_CHARACTER_MOUNT) */
	//	const CGameTable* pCharMount = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MOUNT);

	//	if (pCharMount)
	//	{
	//		const _TABLE_CHARACTER_MOUNT* pMount = (const _TABLE_CHARACTER_MOUNT*)
	//			(pCharMount->GetFieldDataByIndex(mMountID));

	//		if (pMyPet->m_pModelData != pMount || bEffectUpdate)
	//		{
	//			pMyPet->m_pModelData = pMount;

	//			/* ����UIģ�� */
	//			GAME_DATA_PET_PTR->Pet_SetPetFakeModel(iStallOrder, mMountID, pMyPet);
	//		}
	//	}
	//}

	///* ˢ�µ�ǰ������Ч */
	//if (bEffectUpdate)
	//{
	//	if (NULL == OBJECT_MANAGER_PTR->GetMySelf()) return MP_CONTINUE;
	//	if (NULL == OBJECT_MANAGER_PTR->GetMySelf()->GetCharacterData()) return MP_CONTINUE;

	//	int32 nMountID = OBJECT_MANAGER_PTR->GetMySelf()->GetCharacterData()->Get_MountID();

	//	if
	//		(
	//			INVALID_ID != nMountID
	//			&& pMyPet->m_GUID == OBJECT_MANAGER_PTR->GetMySelf()->GetCharacterData()->Get_CurrentPetGUID()
	//			)
	//	{
	//		//OBJECT_MANAGER_PTR->GetMySelf()->MountEffectUpdate(pMyPet);
	//		COMMAND_SYS_PTR->AddCommand(GCD_MOUNT_ATTR_UPDATE, "all");
	//	}
	//}

	//if (bNewPet)
	//{
	//	/* ���������ʱ, ����ע������Ϊ������ */
	//	SCRIPT_FUNCTION::CScriptFunMount::s_Mount.SetSelectMount(pMyPet->m_GUID);
	//}

	//if (bNewPet || mFlag64.isSetBit(PET_DETAIL_ATTR_NICK_NAME))
	//{
	//	COMMAND_SYS_PTR->AddCommand(GCD_MOUNT_ATTR_UPDATE, "all");
	//	GAME_DATA_PET_PTR->Pet_UpdatePetState(iStallOrder);

	//	/* ˢ������б� */
	//	COMMAND_SYS_PTR->AddCommand(GCD_UPDATE_PET_LIST);
	//	COMMAND_SYS_PTR->AddCommand(GCD_UPDATE_BANKPET);
	//}
	//else if (bBaseAttrChanged)
	//{
	//	COMMAND_SYS_PTR->AddCommand(GCD_MOUNT_ATTR_UPDATE, "attr", "base", iStallOrder);
	//}
	//else
	//{
	//	COMMAND_SYS_PTR->AddCommand(GCD_MOUNT_ATTR_UPDATE, "attr", CLIENT_GAME_other, iStallOrder);
	//}

	//if (bSkillUpdate)
	//{
	//	/* ֪ͨActionSystem */
	//	ACTION_SYS_PTR->UserPetSkill_Update(iStallOrder);
	//}


	//if (m_ExtraInfoData[0] == TYPE_COMPOSE_PET)
	//{
	//	GAME_DATA_PET_PTR->SetPassSkillNum((int32)m_ExtraInfoData[1]);
	//	ACTION_SYS_PTR->UserComposePetSkill_Update();
	//	/* ˢ�½��� */
	//	SCRIPT_FUNCTION::CScriptFunMount::s_Mount.SetComposeTimerState(TRUE);
	//	COMMAND_SYS_PTR->AddCommand(GCD_TOGLE_MOUNT_COMPOSE_PAGE2);
	//}
	return true;
}

const SHorseSkill* SCDetailAttribPet::GetSkill(uint32 uIndex) const
{
	return((uIndex < PET_MAX_SKILL_COUNT) ? (&(m_aSkill[uIndex])) : (NULL));
}

void SCDetailAttribPet::SetSkill(uint32 uIndex, const SHorseSkill* pSkill)
{
	if (pSkill != NULL && uIndex < PET_MAX_SKILL_COUNT)
	{
		m_aSkill[uIndex] = *pSkill;
		mFlag64.UpdateBits((ePET_DETAIL_PROPERTY)(uIndex + PET_DETAIL_ATTR_SKILL_0), TRUE);
	}
	else
	{
		KCheck((pSkill != NULL && uIndex < PET_MAX_SKILL_COUNT) && "XCDetailAttrib_Pet::SetSkill");
	}
}

uchar* SCDetailAttribPet::GetExtraInfoData(void)
{
	return m_ExtraInfoData;
}

void SCDetailAttribPet::SetExtraInfoData(uchar* ExtraInfoData)
{
	memcpy(m_ExtraInfoData, ExtraInfoData, sizeof(m_ExtraInfoData)* sizeof(uchar));
}

void SCDetailAttribPet::setObjectId(int32_t id)
{
	mObjectId = id;
}

void SCDetailAttribPet::setSceneId(int32_t id)
{
	mMapId = id;
}

