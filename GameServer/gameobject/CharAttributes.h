/*$T MapServer/Server/Obj/CharAttributes.h GC 1.140 10/10/07 10:07:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "TypeDefine.h"
#include "Util.h"
#define RETURNREFIX(attr) CharIntAttrRefixs::REFIX_##attr
#define RETURNITEMREFIX(attr) IPROPERTY_##attr
class	CharIntProperty
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	//��������
	typedef enum
	{
		PROPERTY_STR,				//����
		PROPERTY_CON,				//����
		PROPERTY_INT,				//����
		PROPERTY_DEX,				//����
		PROPERTY_MAX_HP,
		PROPERTY_HP_REGENERATE,		//�������HP
		PROPERTY_MAX_MP,
		PROPERTY_MP_REGENERATE,		//�������MP
		PROPERTY_MAX_STRIKE_POINT,	//��֧���ӵ������
		PROPERTY_MAX_RAGE,			//ŭ��
		PROPERTY_RAGE_REGENERATE,	//ŭ���ָ�
		PROPERTY_CAMP,				//��Ӫ
		PROPERTY_MODEL_ID,			//ģ��ID
		PROPERTY_MOUNT_ID,			//���ģ��ID
		PROPERTY_EXP_REFIX,			//˫����������
		PROPERTY_STEALTH_LEVEL,		//����ȼ�
		PROPERTY_DETECT_LEVEL,		//�����ȼ�
		PROPERTY_ATTACK_NEAR,		//����
		PROPERTY_ATTACK_FAR,		//Զ��
		PROPERTY_DEFENCE_NEAR,		//����
		PROPERTY_DEFENCE_FAR,		//Զ��
		PROPERTY_TOUGHNESS,			//����
		PROPERTY_NEARATT_REDUCE,	//����̼��
		PROPERTY_FARATT_REDUCE,		//Զ�̼���
		PROPERTY_MAGICATT_REDUCE,	//ħ������
		PROPERTY_DREAD_RESIST,		//�־忹��
		PROPERTY_COMA_RESIST,		//���Կ���
		PROPERTY_HUSH_RESIST,		//
		PROPERTY_UNARMY_RESIST,		
		PROPERTY_ATTACKSPEED_RESIST,//�����ٶȿ���
		PROPERTY_SKILLSPEED_RESIST,	//�����ٶȿ���
		PROPERTY_MOVEREDUCE_RESIST,	//�ƶ����⿹��
		PROPERTY_ATTACK_MAGIC,		//ħ��
		PROPERTY_DEFENCE_MAGIC,		//ħ����
		PROPERTY_ATTACK_COLD,		//����
		PROPERTY_RESIST_COLD,		//����
		PROPERTY_ATTACK_FIRE,		//��
		PROPERTY_RESIST_FIRE,		//���
		PROPERTY_ATTACK_LIGHT,		//�繥
		PROPERTY_RESIST_LIGHT,		//���
		PROPERTY_ATTACK_POISON,		//����
		PROPERTY_RESIST_POISON,		//����
		PROPERTY_MISS,				//����
		PROPERTY_HIT,				//����
		PROPERTY_CRITICAL,			//����
		PROPERTY_MOVE_SPEED,		//�ƶ��ٶ�
		PROPERTY_ATTACK_SPEED,		//�����ٶ�
		PROPERTY_REDUCE_SLOWER_DURATION,	//���ټ��ٳ���ʱ��
		PROPERTY_REDUCE_WEAKEN_DURATION,	//������������ʱ��
		PROPERTY_REDUCE_FAINT_DURATION,		//�����γ���ʱ��
		PROPERTY_REDUCE_POISONED_DURATION,	//���ٶ��ĳ���ʱ��
		PROPERTY_VISION_RANGE,				//���ӷ�Χ
		PROPERTY_VIGOR_INC_RATE,			//�����ָ�
		PROPERTY_MAX_VIGOR,					//����������
		PROPERTY_CRITICAL_HURT,				//�����˺�
		PROPERTY_IGNORE_NEAR_IMMUNITY,		//���ӽ�������
		PROPERTY_IGNORE_FAR_IMMUNITY,		//����Զ������
		PROPERTY_IGNORE_MAGIC_IMMUNITY,		//����ħ������
		PROPERTY_NEAR_HIT_FOR_CONTROL_SPELL,//�������Ƽ�������
		PROPERTY_FAR_HIT_FOR_CONTROL_SPELL,	//Զ�����Ƽ�������
		PROPERTY_MAGIC_HIT_FOR_CONTROL_SPELL,//ħ�����Ƽ�������
		PROPERTY_NEAR_MISS_FOR_CONTROL_SPELL,//�������Ƽ�������
		PROPERTY_FAR_MISS_FOR_CONTROL_SPELL,//Զ�����Ƽ�������
		PROPERTY_MAGIC_MISS_FOR_CONTROL_SPELL,//ħ�����Ƽ�������
		PROPERTY_ZOOM_SCALE,				//ģ�ʹ�С���ű���
		PROPERTY_MAX_INDEX,
	} Index_T;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CharIntProperty()
	{
		ResetAttrs();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~CharIntProperty()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetAttr(Index_T const nIdx) const
	{
		KCheck( nIdx >= 0 && nIdx < PROPERTY_MAX_INDEX );
		return m_aAttrs[nIdx];
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetAttr(Index_T const nIdx, int32 const nValue)
	{
		KCheck( nIdx >= 0 && nIdx < PROPERTY_MAX_INDEX );
		m_aAttrs[nIdx] = nValue;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void ResetAttrs(void)
	{
		memset((void *) m_aAttrs, '\0', sizeof(m_aAttrs));
		m_aAttrs[PROPERTY_CAMP] = INVALID_ID;
		m_aAttrs[PROPERTY_MOUNT_ID] = INVALID_ID;
		m_aAttrs[PROPERTY_MODEL_ID] = INVALID_ID;
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	int32	m_aAttrs[PROPERTY_MAX_INDEX];
};
class	CharBoolAttrs
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	typedef enum
	{
		PROPERTY_ALIVE,			//�Ƿ���
		PROPERTY_IN_COMBAT,		//�Ƿ�ս����
		PROPERTY_CAN_MOVE,		//�ܷ��ƶ�
		PROPERTY_CAN_ACTION1,		
		PROPERTY_CAN_ACTION2,
		PROPERTY_CAN_ACTION3,
		PROPERTY_DISABLE_FLAG2,
		PROPERTY_UNBREAKABLE,
		PROPERTY_IN_STEALTH_MODE,	//����ģʽ
		PROPERTY_CAN_DETECT_STEALTH,//����
		PROPERTY_TERROR,			//�־�
		PROPERTY_MAX_INDEX,
	} Index_T;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CharBoolAttrs()
	{
		ResetAttrs();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~CharBoolAttrs()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL GetAttr(Index_T const nIdx) const
	{
		KCheck( nIdx >= 0 && nIdx < PROPERTY_MAX_INDEX );
		return m_FlagSet.GetFlagByIndex(nIdx);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetAttr(Index_T const nIdx, BOOL bFlag)
	{
		KCheck( nIdx >= 0 && nIdx < PROPERTY_MAX_INDEX );
		TRUE == bFlag ? m_FlagSet.MarkFlagByIndex(nIdx) : m_FlagSet.ClearFlagByIndex(nIdx);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void ResetAttrs(void)
	{
		SetAttr(PROPERTY_ALIVE, TRUE);
		SetAttr(PROPERTY_IN_COMBAT, FALSE);
		SetAttr(PROPERTY_CAN_MOVE, TRUE);
		SetAttr(PROPERTY_CAN_ACTION1, TRUE);
		SetAttr(PROPERTY_CAN_ACTION2, TRUE);
		SetAttr(PROPERTY_CAN_ACTION3, TRUE);
		SetAttr(PROPERTY_UNBREAKABLE, FALSE);
		SetAttr(PROPERTY_IN_STEALTH_MODE, FALSE);
		SetAttr(PROPERTY_CAN_DETECT_STEALTH, FALSE);
		SetAttr(PROPERTY_TERROR, FALSE);
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	BitFlags<PROPERTY_MAX_INDEX> m_FlagSet;
};
class	CharIntAttrRefixs
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	//�����ԵĶ�Ӧ���������ն�Ӧ����˵��
	typedef enum
	{
		REFIX_PROPERTY_STR,
		REFIX_PROPERTY_CON,
		REFIX_PROPERTY_INT,
		REFIX_PROPERTY_DEX,
		REFIX_PROPERTY_MAX_HP,
		REFIX_PROPERTY_HP_REGENERATE,
		REFIX_PROPERTY_MAX_MP,
		REFIX_PROPERTY_MP_REGENERATE,
		REFIX_PROPERTY_MAX_STRIKE_POINT,
		REFIX_PROPERTY_MAX_RAGE,
		REFIX_PROPERTY_RAGE_REGENERATE,
		REFIX_PROPERTY_CAMP,
		REFIX_PROPERTY_MODEL_ID,
		REFIX_PROPERTY_MOUNT_ID,
		REFIX_PROPERTY_EXP_REFIX,
		REFIX_PROPERTY_STEALTH_LEVEL,
		REFIX_PROPERTY_DETECT_LEVEL,
		REFIX_PROPERTY_ATTACK_NEAR,
		REFIX_PROPERTY_ATTACK_FAR,
		REFIX_PROPERTY_DEFENCE_NEAR,
		REFIX_PROPERTY_DEFENCE_FAR,
		REFIX_PROPERTY_TOUGHNESS,
		REFIX_PROPERTY_NEARATT_REDUCE,
		REFIX_PROPERTY_FARATT_REDUCE,
		REFIX_PROPERTY_MAGICATT_REDUCE,
		REFIX_PROPERTY_DREAD_RESIST,
		REFIX_PROPERTY_COMA_RESIST,
		REFIX_PROPERTY_HUSH_RESIST,
		REFIX_PROPERTY_UNARMY_RESIST,
		REFIX_PROPERTY_ATTACKSPEED_RESIST,
		REFIX_PROPERTY_SKILLSPEED_RESIST,
		REFIX_PROPERTY_MOVEREDUCE_RESIST,
		REFIX_PROPERTY_ATTACK_MAGIC,
		REFIX_PROPERTY_DEFENCE_MAGIC,
		REFIX_PROPERTY_ATTACK_COLD,
		REFIX_PROPERTY_RESIST_COLD,
		REFIX_PROPERTY_ATTACK_FIRE,
		REFIX_PROPERTY_RESIST_FIRE,
		REFIX_PROPERTY_ATTACK_LIGHT,
		REFIX_PROPERTY_RESIST_LIGHT,
		REFIX_PROPERTY_ATTACK_POISON,
		REFIX_PROPERTY_RESIST_POISON,
		REFIX_PROPERTY_MISS,
		REFIX_PROPERTY_HIT,
		REFIX_PROPERTY_CRITICAL,
		REFIX_PROPERTY_MOVE_SPEED,
		REFIX_PROPERTY_ATTACK_SPEED,
		REFIX_PROPERTY_REDUCE_SLOWER_DURATION,
		REFIX_PROPERTY_REDUCE_WEAKEN_DURATION,
		REFIX_PROPERTY_REDUCE_FAINT_DURATION,
		REFIX_PROPERTY_REDUCE_POISONED_DURATION,
		REFIX_PROPERTY_VISION_RANGE,
		REFIX_ITEM_DUR_ON_DIE,
		REFIX_HORSE_HAPPINESS_ON_DIE,
		REFIX_STALL_EXCHANGE_TAX,
		REFIX_PROPERTY_VIGOR_INC_RATE,
		REFIX_MULT_EXP,
		REFIX_PROPERTY_MAX_VIGOR,
		REFIX_PROPERTY_CRITICAL_HURT,
		REFIX_HORSE_HAPPINESS_ON_DIE_PLUS,
		REFIX_PROPERTY_IGNORE_NEAR_IMMUNITY,
		REFIX_PROPERTY_IGNORE_FAR_IMMUNITY,
		REFIX_PROPERTY_IGNORE_MAGIC_IMMUNITY,
		REFIX_PROPERTY_NEAR_HIT_FOR_CONTROL_SPELL,
		REFIX_PROPERTY_FAR_HIT_FOR_CONTROL_SPELL,
		REFIX_PROPERTY_MAGIC_HIT_FOR_CONTROL_SPELL,
		REFIX_PROPERTY_NEAR_MISS_FOR_CONTROL_SPELL,
		REFIX_PROPERTY_FAR_MISS_FOR_CONTROL_SPELL,
		REFIX_PROPERTY_MAGIC_MISS_FOR_CONTROL_SPELL,
		REFIX_PROPERTY_ZOOM_SCALE,
		REFIX_PROPERTY_MAX_INDEX,
	} Index_T;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CharIntAttrRefixs()
	{
		ResetAttrs();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~CharIntAttrRefixs()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetAttr(Index_T const nIdx) const
	{
		KCheck( nIdx >= 0 && nIdx < REFIX_PROPERTY_MAX_INDEX );
		return m_aAttrRefixs[nIdx];
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetAttr(Index_T const nIdx, int32 const nValue)
	{
		KCheck( nIdx >= 0 && nIdx < REFIX_PROPERTY_MAX_INDEX );
		m_aAttrRefixs[nIdx] = nValue;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void ResetAttrs(void)
	{
		memset((void *) m_aAttrRefixs, '\0', sizeof(m_aAttrRefixs));
		m_aAttrRefixs[REFIX_PROPERTY_CAMP] = INVALID_ID;
		m_aAttrRefixs[REFIX_PROPERTY_MODEL_ID] = INVALID_ID;
		m_aAttrRefixs[REFIX_PROPERTY_MOUNT_ID] = INVALID_ID;
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	int32	m_aAttrRefixs[REFIX_PROPERTY_MAX_INDEX];
};
#endif
