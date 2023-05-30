/*$T MapServer/Server/Spell/EffectLogic/Spell_EffectLogic_Base.h GC 1.140 10/10/07 10:07:56 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef EFFECT_LOGIC_BASE_H
#define EFFECT_LOGIC_BASE_H

#include "TypeDefine.h"
#include "gameobject/Character.h"
#include "StructEffect.h"
#include "SpellDataLoader.h"
#include "Spell_Helper.h"
#include "Spell_EffectInterface.h"


class Item;

typedef enum _EffectLogicID_T
{
	SPELL_EFFECT_000,
	SPELL_EFFECT_001,
	SPELL_EFFECT_002,
	SPELL_EFFECT_003,
	SPELL_EFFECT_004,
	SPELL_EFFECT_005,
	SPELL_EFFECT_006,
	SPELL_EFFECT_007,
	SPELL_EFFECT_008,
	SPELL_EFFECT_009,
	SPELL_EFFECT_010,
	SPELL_EFFECT_011,
	SPELL_EFFECT_012,
	SPELL_EFFECT_013,
	SPELL_EFFECT_014,
	SPELL_EFFECT_015,
	SPELL_EFFECT_016,
	SPELL_EFFECT_017,
	SPELL_EFFECT_018,
	SPELL_EFFECT_019,
	SPELL_EFFECT_020,
	SPELL_EFFECT_021,
	SPELL_EFFECT_022,
	SPELL_EFFECT_023,
	SPELL_EFFECT_024,
	SPELL_EFFECT_025,
	SPELL_EFFECT_026,
	SPELL_EFFECT_027,
	SPELL_EFFECT_028,
	SPELL_EFFECT_029,
	SPELL_EFFECT_030,
	SPELL_EFFECT_031,
	SPELL_EFFECT_032,
	SPELL_EFFECT_033,
	SPELL_EFFECT_034,
	SPELL_EFFECT_035,
	SPELL_EFFECT_036,
	SPELL_EFFECT_037,
	SPELL_EFFECT_038,
	SPELL_EFFECT_039,
	SPELL_EFFECT_040,
	SPELL_EFFECT_041,
	SPELL_EFFECT_042,
	SPELL_EFFECT_043,
	SPELL_EFFECT_044,
	SPELL_EFFECT_045,
	SPELL_EFFECT_046,
	SPELL_EFFECT_047,
	SPELL_EFFECT_048,
	SPELL_EFFECT_049,
	SPELL_EFFECT_050,
	SPELL_EFFECT_051,
	SPELL_EFFECT_052,
	SPELL_EFFECT_053,
	SPELL_EFFECT_054,
	SPELL_EFFECT_055,
	SPELL_EFFECT_056,
	SPELL_EFFECT_057,
	SPELL_EFFECT_058,
	SPELL_EFFECT_059,
	SPELL_EFFECT_060,
	SPELL_EFFECT_061,
	SPELL_EFFECT_062,
	SPELL_EFFECT_063,
	SPELL_EFFECT_064,
	SPELL_EFFECT_065,
	SPELL_EFFECT_066,
	SPELL_EFFECT_067,
	SPELL_EFFECT_068,
	SPELL_EFFECT_069,
	SPELL_EFFECT_070,
	SPELL_EFFECT_071,
	SPELL_EFFECT_072,
	SPELL_EFFECT_073,
	SPELL_EFFECT_074,
	SPELL_EFFECT_075,
	SPELL_EFFECT_076,
	SPELL_EFFECT_077,
	SPELL_EFFECT_078,
	SPELL_EFFECT_079,
	SPELL_EFFECT_080,
	SPELL_EFFECT_081,
	SPELL_EFFECT_082,
	SPELL_EFFECT_083,
	SPELL_EFFECT_084,
	SPELL_EFFECT_085,
	SPELL_EFFECT_086,
	SPELL_EFFECT_087,
	SPELL_EFFECT_088,
	SPELL_EFFECT_089,
	SPELL_EFFECT_090,
	NUMBER_OF_IMPACT_LOGIC_IDS
} EffectLogicID;


//����BUFF���߼�������� add by wujianping
class		EffectLogic
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { ID = INVALID_ID, };

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	EffectLogic()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~EffectLogic()
	{
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	/*
	===============================================================================================================
	===============================================================================================================
	*/

	virtual BOOL InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
	{
		return TRUE;
	};

	//�Ƿ��ǳ���BUFF add by wujianping
	virtual BOOL IsOverTimed(void) const
	{
		return FALSE;
	};

	//�Ƿ��Ǽ�Ъ����BUFF �׳�DOT-BUFF add by wujianping
	virtual BOOL IsIntervaled(void) const
	{
		return FALSE;
	};

	//BUFF������ add by wujianping
	void	HeartBeat(UNIT_EFFECT &rImp, Character &rMe) const;

	//�������� add by wujianping
	virtual void RefixSkill(UNIT_EFFECT &rImp, SpellInfo &rSkill) const
	{
	};

	//����BUFF add by wujianping
	virtual void RefixEffect(UNIT_EFFECT &rImp, Character &rMe, UNIT_EFFECT &rImpactNeedRefix) const
	{
	};

	//�������� add by wujianping
	virtual void RefixRageRegeneration(UNIT_EFFECT const &rImp, int32 &rRageRegeneration) const
	{
	};

	////�Ƿ��ܿ����������Ʒ ��һ����׽�ķŴ��õ����߼� add by wujianping
	//virtual BOOL CanViewSpecialObj(UNIT_EFFECT &rImp, SpecialCreature &rObj) const
	//{
	//	return FALSE;
	//}

	//�������͵Ĺ���(��Զħ�����)�������˺� add by wujianping
	virtual void OnEvent_Damages
		(
		UNIT_EFFECT		&rImp,
		Character		&rMe,
		Character *const	pAttacker,
		int32 *const		pDamageList,
		SpellID_t		nSkillID
		) const
	{
	};

	//�ܵ��˺� add by wujianping
	virtual void	OnEvent_Damage
		(
		UNIT_EFFECT		&rImp,
		Character		&rMe,
		Character *const	pAttacker,
		int32			&rDamage,
		SpellID_t		nSkillID
		) const
	{
	};

	//���յ��˺� ֱ�Ӽ��ٵ�HP���˺� add by wujianping
	virtual void OnEvent_FinalDamage
		(
		UNIT_EFFECT		&rImp,
		Character		&rMe,
		Character *const	pAttacker,
		int32			&rDamage,
		SpellID_t		nSkillID
		) const
	{
	};

	//�˺�Ŀ�� add by wujianping
	virtual void OnEvent_DamageTarget
		(
		UNIT_EFFECT	&rImp,
		Character	&rMe,
		Character	&rTar,
		int32		&rDamage,
		SpellID_t	nSkillID
		) const
	{
	};

	//BUFF ��Ч add by wujianping
	virtual void OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
	{
	};

	//������ add by wujianping
	virtual void OnEvent_BeCriticalHit(UNIT_EFFECT &rImp, Character &rMe) const
	{
	};

	//������ add by wujianping
	virtual void	OnEvent_BeHeal(UNIT_EFFECT &rImp, Character &rMe, int32 &nHealedHP) const
	{
	};

	//����Ŀ�� add by wujianping
	virtual void OnEvent_CriticalHitTarget(UNIT_EFFECT &rImp, Character &rMe) const
	{
	};

	//��INT���Ե����� add by wujianping
	virtual BOOL Get_Property_IntAttrRefix
		(
		UNIT_EFFECT			&rImp,
		Character			&rMe,
		CharIntAttrRefixs::Index_T	nIdx,
		int32				&rIntAttrRefix
		) const
	{
		return FALSE;
	};

	//��BOOL���Ե����� add by wujianping
	virtual BOOL Get_Property_BoolAttrRefix
		(
		UNIT_EFFECT		&rImp,
		Character		&rMe,
		CharBoolAttrs::Index_T	nIdx,
		BOOL			&rBoolAttrRefix
		) const
	{
		return FALSE;
	};


	//���� add by wujianping
	virtual void OnEvent_Die(UNIT_EFFECT &rImp, Character &rMe) const
	{
	};

	//BUFF��ʧ add by wujianping
	virtual void OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
	{
	};

	//����Ŀ�� add by wujianping
	virtual void OnEvent_HealTarget(UNIT_EFFECT &rImp, Character &rMe, int32 &rHealedHP) const
	{
	};

	//������ add by wujianping
	virtual void OnEvent_BeHit(UNIT_EFFECT &rImp, Character &rMe, Character &rAttacker) const
	{
	};

	//����Ŀ�� add by wujianping
	virtual void OnEvent_HitTarget(UNIT_EFFECT &rImp, Character &rMe, Character &rTar) const
	{
	};

	//��Ъ������BUFF���� add by wujianping
	virtual void OnEvent_IntervalOver(UNIT_EFFECT &rImp, Character &rMe) const
	{
	};

	//�ɹ�ʹ�ü��� add by wujianping
	virtual void OnEvent_UseSkillSuccessfully(UNIT_EFFECT &rImp, Character &rMe, SpellInfo &rSkill) const
	{
	};

	//����BUFF Ҳ��������һЩBUFF add by wujianping
	virtual int32 OnEvent_FiltrateImpact(UNIT_EFFECT &rImp, Character &rMe, UNIT_EFFECT &rImpactNeedCheck) const
	{
		return CombatMissFlag::FLAG_NORMAL;
	};


/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	//�����˺� add by wujianping
	virtual BOOL RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
	{
		return FALSE;
	};

	//ͨ���ٷֱ�����������ʱ�� add by wujianping
	virtual BOOL	RefixContinuanceByRate(UNIT_EFFECT &rImp, int32 nRate) const;
	//ͨ����ֵ����������ʱ�� add by wujianping
	virtual BOOL	RefixContinuanceByPoint(UNIT_EFFECT &rImp, int32 nPoint) const;

    //�������� ���ߵ�Ч�� Ҫ�õ����߼� �����ж϶Է��Ƿ��������� 
	//��������Ч��������������:�ڱ��������������һ������������BUFF �ͻ��˾��������BUFF����Һ�������֮�����һ����
	//add by wujianping
	BOOL	IsSupportStillOn(UNIT_EFFECT &rImp, Character &rMe) const;

	//֪ͨ������ �������� //add by wujianping
	BOOL	NotifyStopChannelToEffectCaster(UNIT_EFFECT &rImp, Character &rMe) const;

	//���������� add by wujianping
	virtual void CriticalRefix(UNIT_EFFECT &rImp) const
	{
	};

	//����Ŀ�� add by wujianping
	virtual BOOL IsScanedTargetValid(UNIT_EFFECT &rImp, Character &rMe, Character &rTar) const
	{
		return FALSE;
	};

	//������ add by wujianping
	virtual void MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
	{
	};

	//�Ƿ�����Pet������ add by wujianping
	virtual BOOL IsRefixPetInit() const
	{
		return FALSE;
	}

	//����Pet������ add by wujianping
	virtual int32 GetRefixPetInitPara(int32 iType, UNIT_EFFECT &rImp, UNIT_EFFECT &rImpOut) const
	{
		rImpOut.Clear();
		return 0;
	};

	//�����츳ƽ�� add by shangy
	virtual void RefixInherenceBalance(UNIT_EFFECT &rImp, InherenceBalanceRefixValue &rInherenceBalance) const
	{
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	//����һ���̶��ļ��㹫ʽ add by wujianping
	int32	GetResult(int32 iPara1, float fPara2, int32 iPara3, int32 iPara4, int32 iRate) const;

	//�õ�����������Ե����� add by wujianping
	int32	GetHorseRefix(int32 iPara, Item *pPetItem, int32 iRate) const;

	//�õ����յ��˺� add by wujianping
	void	FinalDamage(int32 *vDamage, Character &rMe) const;

	//����ʣ��ʱ�� add by wujianping
	virtual void	ContinuanceCalc(UNIT_EFFECT &rImp, Character &rMe, int32 nDeltaTime) const;
	//�����Ъʱ�� add by wujianping
	virtual void	IntervalCalc(UNIT_EFFECT &rImp, Character &rMe, int32 nDeltaTime) const;

	//����Ŀ�� add by wujianping
	BOOL	ScanUnitForTarget
		(
			UNIT_EFFECT	&rImp,
			Character	&rMe,
			GLPos const &rPos,
			float		fRadius,
			int32		nListSize,
			OBJLIST		&rTargets
		) const;

	//��������� add by wujianping
	virtual BOOL SpecialHeartBeatCheck(UNIT_EFFECT &rImp, Character &rMe) const
	{
		return TRUE;
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
};

EffectLogic const *GetEffectLogic(UNIT_EFFECT const &rImp);

#endif
