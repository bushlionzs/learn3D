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
	//各种属性
	typedef enum
	{
		PROPERTY_STR,				//力量
		PROPERTY_CON,				//体质
		PROPERTY_INT,				//智力
		PROPERTY_DEX,				//敏捷
		PROPERTY_MAX_HP,
		PROPERTY_HP_REGENERATE,		//重生后的HP
		PROPERTY_MAX_MP,
		PROPERTY_MP_REGENERATE,		//重生后的MP
		PROPERTY_MAX_STRIKE_POINT,	//箭支最大拥有上限
		PROPERTY_MAX_RAGE,			//怒气
		PROPERTY_RAGE_REGENERATE,	//怒气恢复
		PROPERTY_CAMP,				//陈营
		PROPERTY_MODEL_ID,			//模型ID
		PROPERTY_MOUNT_ID,			//骑乘模型ID
		PROPERTY_EXP_REFIX,			//双倍经验修正
		PROPERTY_STEALTH_LEVEL,		//隐身等级
		PROPERTY_DETECT_LEVEL,		//反隐等级
		PROPERTY_ATTACK_NEAR,		//近攻
		PROPERTY_ATTACK_FAR,		//远攻
		PROPERTY_DEFENCE_NEAR,		//近防
		PROPERTY_DEFENCE_FAR,		//远防
		PROPERTY_TOUGHNESS,			//韧性
		PROPERTY_NEARATT_REDUCE,	//近冻碳趺
		PROPERTY_FARATT_REDUCE,		//远程减免
		PROPERTY_MAGICATT_REDUCE,	//魔法减免
		PROPERTY_DREAD_RESIST,		//恐惧抗性
		PROPERTY_COMA_RESIST,		//昏迷抗性
		PROPERTY_HUSH_RESIST,		//
		PROPERTY_UNARMY_RESIST,		
		PROPERTY_ATTACKSPEED_RESIST,//攻击速度抗性
		PROPERTY_SKILLSPEED_RESIST,	//技能速度抗性
		PROPERTY_MOVEREDUCE_RESIST,	//移动减免抗性
		PROPERTY_ATTACK_MAGIC,		//魔攻
		PROPERTY_DEFENCE_MAGIC,		//魔防备
		PROPERTY_ATTACK_COLD,		//冰攻
		PROPERTY_RESIST_COLD,		//冰防
		PROPERTY_ATTACK_FIRE,		//火攻
		PROPERTY_RESIST_FIRE,		//火防
		PROPERTY_ATTACK_LIGHT,		//电攻
		PROPERTY_RESIST_LIGHT,		//电防
		PROPERTY_ATTACK_POISON,		//毒攻
		PROPERTY_RESIST_POISON,		//毒防
		PROPERTY_MISS,				//闪避
		PROPERTY_HIT,				//命中
		PROPERTY_CRITICAL,			//暴击
		PROPERTY_MOVE_SPEED,		//移动速度
		PROPERTY_ATTACK_SPEED,		//攻击速度
		PROPERTY_REDUCE_SLOWER_DURATION,	//减少减速持续时间
		PROPERTY_REDUCE_WEAKEN_DURATION,	//减少虚弱持续时间
		PROPERTY_REDUCE_FAINT_DURATION,		//减少晕持续时间
		PROPERTY_REDUCE_POISONED_DURATION,	//减少毒的持续时间
		PROPERTY_VISION_RANGE,				//可视范围
		PROPERTY_VIGOR_INC_RATE,			//活力恢复
		PROPERTY_MAX_VIGOR,					//最大活力上限
		PROPERTY_CRITICAL_HURT,				//暴击伤害
		PROPERTY_IGNORE_NEAR_IMMUNITY,		//忽视近攻免疫
		PROPERTY_IGNORE_FAR_IMMUNITY,		//忽视远攻免疫
		PROPERTY_IGNORE_MAGIC_IMMUNITY,		//忽视魔攻免疫
		PROPERTY_NEAR_HIT_FOR_CONTROL_SPELL,//近攻控制技能命中
		PROPERTY_FAR_HIT_FOR_CONTROL_SPELL,	//远攻控制技能命中
		PROPERTY_MAGIC_HIT_FOR_CONTROL_SPELL,//魔攻控制技能命中
		PROPERTY_NEAR_MISS_FOR_CONTROL_SPELL,//近攻控制技能闪避
		PROPERTY_FAR_MISS_FOR_CONTROL_SPELL,//远攻控制技能闪避
		PROPERTY_MAGIC_MISS_FOR_CONTROL_SPELL,//魔攻控制技能闪避
		PROPERTY_ZOOM_SCALE,				//模型大小缩放比例
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
		PROPERTY_ALIVE,			//是否存活
		PROPERTY_IN_COMBAT,		//是否战斗中
		PROPERTY_CAN_MOVE,		//能否移动
		PROPERTY_CAN_ACTION1,		
		PROPERTY_CAN_ACTION2,
		PROPERTY_CAN_ACTION3,
		PROPERTY_DISABLE_FLAG2,
		PROPERTY_UNBREAKABLE,
		PROPERTY_IN_STEALTH_MODE,	//隐身模式
		PROPERTY_CAN_DETECT_STEALTH,//反隐
		PROPERTY_TERROR,			//恐惧
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
	//对属性的对应修正，参照对应属性说明
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
