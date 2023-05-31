///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FileName:Spell_Helper.h
//Author:
//Date:
//Describe:ս��������صĲ����ṹ���壬�����ָ������ܵ�ʵ��
//History:
//		1.
//		2.
//		3.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SPELL_HELP_H
#define SPELL_HELP_H

#include "TypeDefine.h"
#include "SpellDataLoader.h"
#include "Enum.h"
#include "Struct.h"
#include "StructDB.h"

class Character;
class SpellInfo;

enum SpellControlType	//�����༼�ܵ����ͣ�����Զ��ħ add by shangy
{
	SCT_NULL = -1,
	SCT_NEAR = 0,
	SCT_FAR,
	SCT_MAGIC
};

enum TargetCamp	//Ŀ����Ӫ���� add by shangy
{
	TC_PARTNER = 0,
	TC_ENEMY,
	TC_PARTNER_PET,
	TC_PARTNER_EXCEPT_SELF,
	TC_ENEMY_AND_PLAYER,
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CombatSystem
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum	//����Ч������ add by shangy
{
	DAMAGE_SPECIAL_EFFECT_NEAR	= 0,
	DAMAGE_SPECIAL_EFFECT_FAR,
	DAMAGE_SPECIAL_EFFECT_MAGIC,
	DAMAGE_SPECIAL_EFFECT_COLD,
	DAMAGE_SPECIAL_EFFECT_FIRE,
	DAMAGE_SPECIAL_EFFECT_LIGHT,
	DAMAGE_SPECIAL_EFFECT_POISON
} DamageSEID_T;

/*
====================================================================================================================== =
add by shangy
CombatSystem;
ͨ�����趨�Ļ�����ֵ�����������ֵ�ͼ��ܵ�����ֵ����ս���е���ֵ���м��㣬��������ӦImpact
====================================================================================================================== =
*/
class	CombatSystem
{
public:

	CombatSystem();
	~CombatSystem();
	//���ݹ����ߵ����к�Ŀ������ܼ��������� ��Сֵ10 add by shangy
	int32	CalculateHitRate(Character& rAttacker, Character& rTag);
	//���ݹ����߿��Ƽ��ܵ����к�Ŀ��Ŀ��Ƽ��ܵ����ܼ��������� ��Сֵ25 add by shangy
	int32	CalculateHitRateForControlSpell(Character& rAttacker, Character& rTag, SpellControlType eType);
	//�Ƿ����
	BOOL	IsHit(int32 nHitRate, int32 nRand);
	//�Ƿ񱩻�  ������ = �������� + �������������� - �Է����� add by shangy
	BOOL	IsCriticalHit(Character& rAttacker, int32 nCriticalRate, int32 nRand, Character& rTar, int32 iToughness);
	void	Reset();
	//�����˺�����Impactע�ᵽĿ��֮ǰ�����������������ԣ���Impact�Ľ���Զ��ħ�������𣬹⣬�����м��㡣 add by shangy
	BOOL	GetResultImpact(Character& rAttacker, Character& rDefenceer, UNIT_EFFECT& rImp);
	//��Impact�ϵĵĽ���Զ��ħ�������𣬹⣬�����Ե��ӵ���ǰ�����˺��ϡ� add by shangy
	void	InitAttackValueData(UNIT_EFFECT& rImp);
	void	InitAttackRateData(UNIT_EFFECT& rImp, Character& rMe);
public:
	//��ú����õ�ǰ����Զ��ħ�������𣬹⣬������ add by shangy
	int32	GetAdditionalAttackNear(void) const;
	void	SetAdditionalAttackNear(int32 nValue);
	int32	GetAdditionalAttackFar(void) const;
	void	SetAdditionalAttackFar(int32 nValue);
	int32	GetAdditionalAttackMagic(void) const;
	void	SetAdditionalAttackMagic(int32 nValue);
	int32	GetAdditionalAttackCold(void) const;
	void	SetAdditionalAttackCold(int32 nValue);
	int32	GetAdditionalAttackFire(void) const;
	void	SetAdditionalAttackFire(int32 nValue);
	int32	GetAdditionalAttackLight(void) const;
	void	SetAdditionalAttackLight(int32 nValue);
	int32	GetAdditionalAttackPoison(void) const;
	void	SetAdditionalAttackPoison(int32 nValue);

	//�츳ƽ��
	int32 RefixCritRatebyInherenceBalance(int32 nCrit, int32 nToughness, Character& rAttacker, Character& rTar);

	int32 RefixHitbyInherenceBalance(int32 nHit, int32 nMiss, Character& rAttacker, Character& rTar);

	float RefixCritDamagebyInherenceBalance(int32 nCritDamageRate, int32 nCritDamageDerateRatrByToughness, Character& rAttacker, Character& rTar);

	//��ȡְҵ�˺�������(����װ��������ר������)
	int32	GetProfessionDamageRefixRate(Character& rAttacker, Character& rTar);

protected:
	//�������Զ��ħ�������𣬹⣬�����˺�����NormalDamage����Ľ���ϼ���Ŀ����˺����������ĺ����˺���������Ӱ�� add by shangy
	int32	NearDamage(Character& rMe, Character& rTar, int32 iLogicID, int32 nAdditionAttack = 0, int32 nAdditionDefence = 0);
	int32	FarDamage(Character& rMe, Character& rTar, int32 iLogicID, int32 nAdditionAttack = 0, int32 nAdditionDefence = 0);
	int32	MagicalDamage(Character& rMe, Character& rTar, int32 iLogicID, int32 nAdditionAttack = 0, int32 nAdditionDefence = 0);
	int32	ColdDamage(Character& rMe, Character& rTar, int32 iLogicID, int32 nAdditionAttack = 0, int32 nAdditionDefence = 0);
	int32	FireDamage(Character& rMe, Character& rTar, int32 iLogicID, int32 nAdditionAttack = 0, int32 nAdditionDefence = 0);
	int32	LightDamage(Character& rMe, Character& rTar, int32 iLogicID, int32 nAdditionAttack = 0, int32 nAdditionDefence = 0);
	int32	PoisonDamage(Character& rMe, Character& rTar, int32 iLogicID, int32 nAdditionAttack = 0, int32 nAdditionDefence = 0);
	//�����˺��Ĺ�������������Զ��ħ�� �˺� = ���� - Ŀ��� - Ŀ����Ʒ�����ж�Ӧ�ķ���ֵ add by shangy
	int32	NormalDamage(Character& rTar, int32 nAttack, int32 nDefence, int32 iType);
	//�����˺��Ĺ��������������𣬹⣬���� �˺� = ���� - Ŀ����Ʒ�����ж�Ӧ�ķ���ֵ add by shangy
	int32	AttrDamage(Character& rTar, int32& nResist, int32 nAttack, int32 iType);
	//���������ԭʼ���Ժ������������Լ���ӳ�֮�������ֵ add by shangy
	int32	GetValueByCalType(int32 iSrc, int32 iAddition, int32 iType, int32 iParaTab);


private:
	int32	m_nAdditionalAttackNear;
	int32	m_nAdditionalAttackFar;
	int32	m_nAdditionalAttackMagic;
	int32	m_nAdditionalAttackCold;
	int32	m_nAdditionalAttackFire;
	int32	m_nAdditionalAttackLight;
	int32	m_nAdditionalAttackPoison;
	int32	m_nAdditionalDefenceNear;
	int32	m_nAdditionalDefenceFar;
	int32	m_nAdditionalDefenceMagic;
	int32	m_nAdditionalDefenceCold;
	int32	m_nAdditionalDefenceFire;
	int32	m_nAdditionalDefenceLight;
	int32	m_nAdditionalDefencePoison;
	int32	m_ImpactDataTbl[DAMAGE_TYPE_NUMBER];
};

typedef enum _ConditionAndDepleteID
{
	CD_INVALID				= INVALID_ID,
	C_UNIT_MUST_HAVE_IMPACT			= 0,
	C_UNIT_HP_MUST_LESS_THAN_BY_RATE,
	C_UNIT_HP_MUST_MORE_THAN_BY_RATE,
	C_TARGET_MUST_HAVE_IMPACT,
	C_TARGET_HP_MUST_LESS_THAN_BY_RATE,
	C_TARGET_HP_MUST_MORE_THAN_BY_RATE,
	CD_HP_BY_VALUE,
	CD_HP_BY_RATE,
	CD_RAGE0_BY_VALUE,
	CD_RAGE0_BY_RATE,
	CD_RAGE1_BY_VALUE,
	CD_RAGE1_BY_RATE,
	CD_RAGE2_BY_VALUE,
	CD_RAGE2_BY_RATE,
	CD_RAGE3_BY_VALUE,
	CD_RAGE3_BY_RATE,
	CD_RAGE4_BY_VALUE,
	CD_RAGE4_BY_RATE,
	CD_RAGE5_BY_VALUE,
	CD_RAGE5_BY_RATE,
	D_CANCEL_SPECIFIC_IMPACT,
	CD_CANCEL_SPECIFIC_IMPACT,
	C_TARGET_MUST_BE_MY_SPOUSE,
} ConditionAndDepleteID;

/*
=======================================================================================================================
add by shangy
CDSystem ;
�����CD��ʾConditionCheckAndDeplete���뼼����ȴû�й�ϵ��
��ʹ�ü���ʱ�Լ��ܵ�ʹ�����������ж��Լ�������Ӧ����Ʒ��ŭ����MP��
ÿ�����ܿ���������������������������һ���������������Ʒ
ÿ���������£�
��spell_logic.tab��
�����������Ĳ���˵������ ����
�������������߼��������ö�Ӧ��ID ��ֵ������ ConditionAndDepleteID��
�����������Ĳ���ֵp1��v=p1*level+p2����	����1
�����������Ĳ���ֵp2��v=p1*level+p2���� ����2
ÿ�����ݶ�ӦConditionAndDepleteTerm�ṹ

��������SpellTargetingAndDepletingParams�е�m_bIgnoreConditionCheckΪtrueʱ������������
����Ҫ�Ǹ��ű����ṩһ��ֱ������������ȴʱ����⣩ʹ�ü��ܵķ���
=======================================================================================================================
*/

class Player;
typedef class	CDSystem
{
public:
	//����ID���зַ��������߼��ɳ�Ա�ദ�� add by shangy
	BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	//��������Ʒ�ļ������� add by shangy
	BOOL	ConditionCheckByItem(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	BOOL	DepleteByItem(Character& rMe, ConditionAndDepleteTerm const& rData) const;

private:
	class	ConDepLogic
	{
	public:
		enum { ID = CD_INVALID, };
		virtual BOOL ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const { return TRUE; };
		virtual BOOL Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const { return TRUE; };
	protected:
		int32	NotEnoughRageForProfession(Player& rMe) const;
		//��������Buff(SpellEffect021,SpellEffect029,SpellEffect075)�Ե�ǰʹ�ü��ܵ������������Ľ��������� add by shangy
		int32	RefixValue(int32 iValue, Character& rMe, ConditionAndDepleteTerm const& rData) const;
		//���ͨ�����ģ���ʽ:Param0 * SkillLevel + Param1 add by shangy
		int32	GetCommonDeplete(ConditionAndDepleteTerm const& rData, SpellInfo& rSkillInfo) const;
		BOOL	RageConditionCheckByValue(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	RageDepleteByValue(Character& rMe, ConditionAndDepleteTerm const& rData) const;

		BOOL	RageConditionCheckByRate(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	RageDepleteByRate(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//�ж����������Ƿ����ض����ϵ�buff, Param0: CollectionID 
	//��ӦCollection���ݶ�����FILE_ID_COLLECTION�� add by shangy
	class CDUnitHaveImpact : public ConDepLogic
	{
	public:
		enum { ID = C_UNIT_MUST_HAVE_IMPACT, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//����ͨ�����Ĺ�ʽ�����HP���ްٷֱȡ����Ѫ���Ƿ��������Ѫ��
	//����Ѫ��:�������Ѫ�� * HP���ްٷֱ� �پ���Buff������õ�����Ѫ�� add by shangy
	class CDUnitHpLessThanByRate : public ConDepLogic
	{
	public:
		enum { ID = C_UNIT_HP_MUST_LESS_THAN_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//����Ѫ����������Ѫ���ļ�� add by shangy
	class CDUnitHpMoreThanByRate : public ConDepLogic
	{
	public:
		enum { ID = C_UNIT_HP_MUST_MORE_THAN_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//���ݱ�����Ѫ add by shangy
	class CDHpByValue : public ConDepLogic
	{
	public:
		enum { ID = CD_HP_BY_VALUE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//Ŀ��Ѫ����������Ѫ���ļ�� add by shangy
	class CDTargetHpLessThanByRate : public ConDepLogic
	{
	public:
		enum { ID = C_TARGET_HP_MUST_LESS_THAN_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//Ŀ��Ѫ����������Ѫ���ļ�� add by shangy
	class CDTargetHpMoreThanByRate : public ConDepLogic
	{
	public:
		enum { ID = C_TARGET_HP_MUST_MORE_THAN_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//Ŀ�����ӵ���ض����ϵ�buff, Param0: CollectionID 
	//��ӦCollection���ݶ�����FILE_ID_COLLECTION�� add by shangy
	class CDTargetMustHaveImpact : public ConDepLogic
	{
	public:
		enum { ID = C_TARGET_MUST_HAVE_IMPACT, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//��ɢ�ض����ϵ�buff, Param0: CollectionID 
	//��ӦCollection���ݶ�����FILE_ID_COLLECTION�� add by shangy
	class CDCancelSpecialImpact_D : public ConDepLogic
	{
	public:
		enum { ID = D_CANCEL_SPECIFIC_IMPACT, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//Ŀ������ǰ��� add by shangy
	class CDTargetMustBeMySpouse : public ConDepLogic
	{
	public:
		enum { ID = C_TARGET_MUST_BE_MY_SPOUSE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//��������Ѫ add by shangy
	class CDHpByRate : public ConDepLogic
	{
	public:
		enum { ID = CD_HP_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//����ŭ�� by value ��ʿ��ʮ�־� add by shangy
	class CDRage0ByValue : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE0_BY_VALUE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//����ŭ�� by Rate ��ʿ��ʮ�־� add by shangy
	class CDRage0ByRate : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE0_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//����ŭ�� by value ������ʥ��ʹ add by shangy
	class CDRage1ByValue : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE1_BY_VALUE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//����ŭ�� by Rate ������ʥ��ʹ add by shangy
	class CDRage1ByRate : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE1_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//����ŭ�� by value ���䣬�̿� add by shangy
	class CDRage2ByValue : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE2_BY_VALUE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//����ŭ�� by Rate ���䣬�̿� add by shangy
	class CDRage2ByRate : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE2_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//����ŭ�� by value ��ǹ�������� add by shangy
	class CDRage3ByValue : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE3_BY_VALUE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//����ŭ�� by Rate ��ǹ�������� add by shangy
	class CDRage3ByRate : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE3_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//����ŭ�� by value ��֪������ʿ add by shangy
	class CDRage4ByValue : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE4_BY_VALUE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//����ŭ�� by Rate ��֪������ʿ add by shangy
	class CDRage4ByRate : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE4_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//����ŭ�� by value ���������� add by shangy
	class CDRage5ByValue : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE5_BY_VALUE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//����ŭ�� by Rate ���������� add by shangy
	class CDRage5ByRate : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE5_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//��ɢ�ض����ϵ�buff, Param0: CollectionID 
	//��ӦCollection���ݶ�����FILE_ID_COLLECTION�� add by shangy
	class CDCancelSpecialImpact_CD : public ConDepLogic
	{
	public:
		enum { ID = CD_CANCEL_SPECIFIC_IMPACT, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

private:
	CDUnitHaveImpact			m_C_UnitHaveImpact;
	CDUnitHpLessThanByRate		m_C_UnitHpLessThanByRate;
	CDUnitHpMoreThanByRate		m_C_UnitHpMoreThanByRate;
	CDTargetMustHaveImpact		m_C_TargetMustHaveImpact;
	CDTargetHpLessThanByRate	m_C_TargetHpLessThanByRate;
	CDTargetHpMoreThanByRate	m_C_TargetHpMoreThanByRate;
	CDHpByValue					m_CD_HpByValue;
	CDHpByRate					m_CD_HpByRate;
	CDRage0ByValue				m_CD_Rage0ByValue;
	CDRage1ByValue				m_CD_Rage1ByValue;
	CDRage2ByValue				m_CD_Rage2ByValue;
	CDRage3ByValue				m_CD_Rage3ByValue;
	CDRage4ByValue				m_CD_Rage4ByValue;
	CDRage5ByValue				m_CD_Rage5ByValue;
	CDRage0ByRate				m_CD_Rage0ByRate;
	CDRage1ByRate				m_CD_Rage1ByRate;
	CDRage2ByRate				m_CD_Rage2ByRate;
	CDRage3ByRate				m_CD_Rage3ByRate;
	CDRage4ByRate				m_CD_Rage4ByRate;
	CDRage5ByRate				m_CD_Rage5ByRate;
	CDCancelSpecialImpact_D		m_D_CancelSpecialImpact;
	CDCancelSpecialImpact_D		m_CD_CancelSpecialImpact;
	CDTargetMustBeMySpouse		m_C_TargetMustBeMySpouse;
} ConditionAndDepleteCore_T;

/*
=======================================================================================================================
add by shangy
SpellTargetingAndDepletingParams ;
ս��������Ե�Ŀ������ĵ����ݲ���
=======================================================================================================================
*/
class	SpellTargetingAndDepletingParams
{

public:
	enum { MAX_PARAM_NUMBER = 8, };

	//�ò�����Ӧ�ļ���ID add by shangy
	SpellID_t			GetActivatedSpell(void) const;
	void				SetActivatedSpell(SpellID_t nSpell);

	//�ò�����Ӧ�Ľű�ID add by shangy
	//Ŀǰֻ��ʹ����Ʒ�Ĳ�����󶨽ű���ʹ�ü���û�а󶨽ű���
	ScriptID_t			GetActivatedScript(void) const;
	void				SetActivatedScript(ScriptID_t nScript);

	//���ܻ�ʹ����ƷĿ�� add by shangy
	ObjID_t				GetTargetObj(void) const;
	void				SetTargetObj(ObjID_t nObj);

	//����ʹ��Ŀ���GUID add by shangy
	GUID_t				GetTargetGuid(void) const;
	void				SetTargetGuid(GUID_t nGuid);

	//Ŀ��λ�� add by shangy
	GLPos const &	GetTargetPosition(void) const;
	void				SetTargetPosition(GLPos const &rPos);

	//Ŀ�곯�� add by shangy
	float				GetTargetDirection(void) const;
	void				SetTargetDirection(float fDir);

	//��Ʒ�ڱ����е�λ�� add by shangy
	int32				GetTargetBagSlot(void) const;
	void				SetTargetBagSlot(int32 nSlot);

	//Pet GUID (TargetID and TargetGUID) add by shangy
	SHorseGuid const &	GetTargetPetGuid(void) const;
	void				SetTargetPetGuid(SHorseGuid const &rGuid);
	
	//�Ƿ���Լ������ ֻ�ڽű����õ�ʱ������ø�ֵ��LuaFunction_UnitUseSkill����Ϊtrueʱ�����ʹ�ü���������ֻҪ��ȴʱ������ֱ��ʹ�ü��ܡ�
	//��Ӧ�ļ������spell_logic.tab�С������������߼��������ã���CDSystem�еĶ�Ӧ���н��м�顣ÿ�����ܹ��������������������� add by shangy
	BOOL				GetIgnoreConditionCheckFlag(void) const;
	void				SetIgnoreConditionCheckFlag(BOOL bFlag);
	//����ŭ�� add by shangy
	int32				GetDepletedRage(void) const;
	void				SetDepletedRage(int32 nDepleted);
	//����StrikePoints add by shangy
	int32				GetDepletedStrikePoints(void) const;
	void				SetDepletedStrikePoints(int32 nDepleted);
	//����Item��GUID add by shangy
	SItemGuid const &	GetDepletedItemGuid(void) const;
	void				SetDepletedItemGuid(SItemGuid const &rGuid);
	//����Item�ı���Index add by shangy
	int32				GetBagIndexOfDepletedItem(void) const;
	void				SetBagIndexOfDepletedItem(int32 nIndex);
	//����Item�ڱ����е�Index add by shangy
	int32				GetItemIndexOfDepletedItem(void) const;
	void				SetItemIndexOfDepletedItem(int32 nIndex);
	//�����ƷΪ�󶨣������ð� add by shangy
	void				SetItemBind();
	BOOL				IsDepletedItemBind();
	//�ӳ�ʱ�� spell_logic.tab�����õ�ʱ�� add by shangy
	Time_t				GetDelayTime(void) const;
	void				SetDelayTime(Time_t nTime);
	//Ŀ����� add by shangy
	int32				GetTargetCount(void) const;
	void				SetTargetCount(int32 nCount);
	//������ add by shangy
	ID_t				GetErrCode(void) const;
	void				SetErrCode(ID_t nErr);
	//������� add by shangy
	int32				GetErrParam(void) const;
	void				SetErrParam(int32 nParam);
	//��̬���� add by shangy
	BOOL				IsDynamicParamIndexLegal(int32 nIndex) const;
	int32				GetDynamicParamByIndex(int32 nIndex) const;
	void				SetDynamicParamByIndex(int32 nIndex, int32 nValue);
	//�˺��ӳ�ʱ�� ���������ڶ�ӦImpact�� add by shangy
	int32				GetHurtDelayTime() const;
	void				SetHurtDelayTime(int32 val);

	// ׷�ٷ�
	void SetFindPlayerItemDataName(const char* name);
	const char* GetFindPlayerItemDataName();

public:
	SpellTargetingAndDepletingParams(void);
	~SpellTargetingAndDepletingParams(void){};
	SpellTargetingAndDepletingParams &operator	=(SpellTargetingAndDepletingParams const &rhs);
	void Reset(void);

private:
	SpellID_t	m_nActivatedSpell;
	ScriptID_t	m_nActivatedScript;
	ObjID_t		m_nTargetObj;
	GUID_t		m_guidTargetPartner;
	GLPos	m_posTargetPosition;
	float		m_fTargetDirection;
	int32		m_nTargetBagSlot;
	SHorseGuid	m_guidTargetPet;
	BOOL		m_bIgnoreConditionCheck;
	int32		m_nDepletedRage;
	int32		m_nDepletedStrikePoints;
	SItemGuid	m_guidDepletedItem;
	int32		m_nBagIndexOfDepletedItem;
	int32		m_nItemIndexOfDepletedItem;
	Time_t		m_nDelayTime;
	int32		m_nTargetCount;
	int32		m_aDynamicParams[MAX_PARAM_NUMBER];
	ID_t		m_nErrCode;
	int32		m_nErrParam;
	int32		m_iHurtDelayTime;
	BOOL		m_bDeletedItemBind;
	char		m_szFindPlayerItemName[MAX_CHARACTER_NAME];
};


/*
=======================================================================================================================
add by shangy
SpellTargetChecker ;
��鼼��ʹ��Ŀ����Ч��
=======================================================================================================================
*/
class	SpellTargetChecker
{

public:
	typedef enum
	{
		INVALID_CHECKER_ID	= INVALID_ID,
		ALL_TYPE_ARE_LEGAL	= 0,
		NPCS_ARE_LEGAL		= 1,
		ONLY_PC_IS_LEGAL	= 2,
		ONLY_PET_IS_LEGAL	= 3,
		NON_TYPE_IS_LEGAL	= 4,
		NUMBER_OF_CHECKERS
	} TargetTypeCheckerID_T;

	enum { ID = INVALID_CHECKER_ID, };
	virtual BOOL	IsLegal(Character const &rTarget) const;
};

class AllTypesAreLegal : public SpellTargetChecker
{
public:
	enum { ID = SpellTargetChecker::ALL_TYPE_ARE_LEGAL, };
	virtual BOOL	IsLegal(Character const &rTarget) const;
};

class NonPlayerCharactersAreLegal : public SpellTargetChecker
{
public:
	enum { ID = SpellTargetChecker::NPCS_ARE_LEGAL, };
	virtual BOOL	IsLegal(Character const &rTarget) const;
};

class OnlyPlayerCharacterIsLegal : public SpellTargetChecker
{
public:
	enum { ID = SpellTargetChecker::ONLY_PC_IS_LEGAL, };
	virtual BOOL	IsLegal(Character const &rTarget) const;
};

class OnlyPetIsLegal : public SpellTargetChecker
{
public:
	enum { ID = SpellTargetChecker::ONLY_PET_IS_LEGAL, };
	virtual BOOL	IsLegal(Character const &rTarget) const;
};

class NonTypeIsLegal : public SpellTargetChecker
{
public:
	enum { ID = SpellTargetChecker::NON_TYPE_IS_LEGAL, };
	virtual BOOL	IsLegal(Character const &rTarget) const;
};

/*
=======================================================================================================================
add by shangy
SpellInfo ;
������Ϣ�������˼��ܴ󲿷ֵĻ���������Ϣ��
=======================================================================================================================
*/

class	SpellInfo
{
public:
	SpellInfo();
	SpellInfo(SpellInfo const &rSrc);
	~SpellInfo(){};

	void			Init(void);
	SpellID_t		GetSpellID(void) const;
	void			SetSpellID(SpellID_t const nID);;
	int32			GetAccuracy(void) const;
	void			SetAccuracy(int32 const nID);
	int32			GetCriticalRate(void) const;
	void			SetCriticalRate(int32 const nRate);
	int32			GetDepleteRefixByValue(void) const;
	void			SetDepleteRefixByValue(int32 nValue);
	int32			GetDepleteRefixByRate(void) const;
	void			SetDepleteRefixByRate(int32 nRate);
	int32			GetPowerRefixByValue(void) const;
	void			SetPowerRefixByValue(int32 nValue);
	int32			GetPowerRefixByRate(void) const;
	void			SetPowerRefixByRate(int32 nRate);
	int32			GetTimeRefixByValue(void) const;
	void			SetTimeRefixByValue(int32 nValue);
	int32			GetTimeRefixByRate(void) const;
	void			SetTimeRefixByRate(int32 nRate);
	Time_t			GetCooldownTime(void) const;
	void			SetCooldownTime(Time_t const nTime);
	Time_t			GetChargeTime(void) const;
	void			SetChargeTime(Time_t const nTime);
	Time_t			GetChannelTime(void) const;
	void			SetChannelTime(Time_t const nTime);
	float			GetMinSkillDistance() const;
	void			SetMinSkillDistance(float val);
	float			GetMaxSkillDistance() const;
	void			SetMaxSkillDistance(float val);
	void			SetChargesOrInterval(int32 val);
	int16_t			GetProfession(void) const;
	char const		*GetName(void) const;
	int32			GetTalentLevelRequirement(void) const;
	BOOL			GetMustUseWeaponFlag(void) const;
	BOOL			GetDisableByFlag1(void) const;
	BOOL			GetDisableByFlag2(void) const;
	BOOL			GetDisableByFlag3(void) const;
	int32			GetRangedSkillFlag(void) const;
	BOOL			IsForceBreakPreSkill(void) const;
	int32			GetTargetMustInSpecialState(void) const;
	ID_t			GetSpellType(void) const;
	CooldownID_t	GetCooldownID(void) const;
	ID_t			GetSelectType(void) const;
	ID_t			GetOperateModeForPetSpell(void) const;
	ID_t			GetPetRateOfSpell(void) const;
	ID_t			GetTypeOfPetSpell(void) const;
	ID_t			GetImpactID(void) const;
	ID_t			GetTargetingLogic(void) const;
	Time_t			GetPlayActionTime(void) const;
	float			GetOptimalRangeMin() const;
	float			GetOptimalRangeMax() const;
	void			SetOptimalRangeMax(float fDistance);
	ID_t			GetStandFlag(void) const;
	ID_t			GetTargetLogicByStand(void) const;
	int32			GetSpeedOfBullet(void) const;
	int32			GetHurtDelayTime(void) const;
	ID_t			GetTargetCheckByObjType(void) const;
	BOOL			IsPartyOnly(void) const;
	int32			GetChargesOrInterval(void) const;
	BOOL			IsAutoShotSpell(void) const;
	BOOL			UseNormalAttackRate(void) const;
	float			GetRadius(void) const;
	float			GetAngle(void) const;
	float			GetRectangleWidth(void) const;
	int32			Get_Property_MaxTargetNumber(void) const;
	void			SetMaxTargetNumber(int32 val);
	BOOL			CanInterruptAutoShot(void) const;
	Time_t			GetDelayTime(void) const;
	ID_t			GetLogicID(void) const;
	ConditionAndDepleteTerm const*	Get_Property_ConDepTermByIndex(int32 const nIdx) const;
	int32				GetSpellLevel(void) const;
	Descriptor const*	GetDescriptorByIndex(int32 const nIdx) const;
	int32				GetCharacterSpellLevel() const;
	void				SetCharacterSpellLevel(int32 val);
	int32				GetChannelBackRate() const;
	void				SetChannelBackRate(int32 val);
	int32				GetChannelBackHappanRate() const;
	void				SetChannelBackHappanRate(int32 val);
	int32				GetSpellLogicCount() const;
	void				SetSpellLogicCount(int32 val);
	int32				GetControlType(void) const;

	SpellInfo &operator	=(SpellTemplateData const &rSrc);
	SpellInfo &operator	=(SpellInstanceData const &rSrc);
	SpellInfo &operator	=(SpellInfo const &rSrc);

protected:

	SpellID_t	GetInstanceID(void) const;
	void		SetInstanceID(SpellID_t const nID);
	void		InitOptimalRangeMin();
	void		InitOptimalRangeMax();
	void		InitChargesOrInterval();
	void		InitMaxTargetNumber();

private:
	SpellID_t	m_nSpellID;
	int32		m_nInstanceID;
	int32		m_nAccuracy;
	int32		m_nCriticalRate;
	int32		m_nDepleteRefixByValue;
	int32		m_nDepleteRefixByRate;
	int32		m_nPowerRefixByValue;
	int32		m_nPowerRefixByRate;
	int32		m_nTimeRefixByValue;
	int32		m_nTimeRefixByRate;
	Time_t		m_nCooldownTime;
	Time_t		m_nChargeTime;
	Time_t		m_nChannelTime;
	float		m_fMinSkillDistance;
	float		m_fMaxSkillDistance;
	int32		m_ChargesOrInterval;
	int32		m_iMaxTargetNumber;
	int32		m_iSpellLevel;
	int32		m_iSpellLogicCount;
	int32		m_iChannelBackRate;
	int32		m_iChannelBackHappanRate;
};

#endif
