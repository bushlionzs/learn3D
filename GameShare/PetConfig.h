/*$T MapServer/Server/Base/PetConfig.h GC 1.140 10/10/07 10:07:21 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _PET_CONFIG_H_
#define _PET_CONFIG_H_

#define GENGU_NUM	(5)

struct SPetConfig
{
	enum { VARIANCEPET_LEVEL_NUM = 8, };

	int32 m_VariancePetRate;
	int32 m_BabyPetRate;

	int32 m_WilenessPetRate_TakeLevel;
	int32 m_WilenessPetRate_Delta1;
	int32 m_WilenessPetRate_Delta2;
	int32 m_WilenessPetRate_Delta3;

	int32 m_GrowRate0;
	int32 m_GrowRate1;
	int32 m_GrowRate2;
	int32 m_GrowRate3;
	int32 m_GrowRate4;

	int32 m_aRateOfLevelVariancePet[VARIANCEPET_LEVEL_NUM];

	struct SGenGu
	{
		int32	m_Begin;
		int32	m_End;
		int32	m_Rate;
	};
	SGenGu	m_vGenGu[GENGU_NUM];

	int32	m_IntelligenceRange;

	int32	m_MoveSpeed;

	int32	m_AttackSpeed;

	int32	m_PetAI0_MagicRate;
	int32	m_PetAI1_MagicRate;
	int32	m_PetAI2_MagicRate;
	int32	m_PetAI3_MagicRate;

	int32	m_BaseHP;

	int32	m_BaseNearAttack;
	int32	m_BaseFarAttack;
	int32	m_BaseMgcAttack;

	int32	m_BaseNearDefence;
	int32	m_BaseFarDefence;
	int32	m_BaseMgcDefence;
	int32	m_BaseHit;
	int32	m_BaseMiss;
	int32	m_BaseCritical;

	float	m_Con_HP_Pram;

	float	m_Str_NearAttack_Pram;

	float	m_Int_MgcDefence_Pram;
	float	m_Dex_Miss_Pram;
	float	m_Dex_Critical_Pram;
	float	m_Dex_Hit_Pram;

	float	m_Level_HP_Pram;

	float	m_Level_NearAttack_Pram;
	float	m_Level_FarAttack_Pram;

	float	m_Level_MgcAttack_Pram;
	float	m_Level_NearDefence_Pram;
	float	m_Level_FarDefence_Pram;

	float	m_Level_MgcDefence_Pram;
	float	m_Level_Miss_Pram;
	float	m_Level_Critical_Pram;
	float	m_Level_Hit_Pram;

	int32	m_Level_FindingHorseMate;
	int32	m_Happiness_FindingHorseMate;
	int32	m_Money_FindingHorseMate;
};
#endif
