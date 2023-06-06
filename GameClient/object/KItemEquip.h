#pragma once
#include "KItem.h"
#include "GameTableData.h"
#include "ItemCommon.h"
#include "StructItem.h"

class KItemEquip : public KItem
{
public:
	/* 区分普通和高级装备 */
	enum EQUIP_ENUM
	{
		INVAILD_EQUIP = -1,					/* 无效 */
		COMMON_EQUIP,							/* 普通 */
		ADVANCED_EQUIP,							/* 高级 */
	};
	/* 属性和宝石 */
	typedef std::vector<_ITEM_PROPERTY>			EQUIP_ATTRIBUTES;
	typedef std::vector<SItemGemInfo>		EQUIP_ATTACH_GEM;

	/* 附加技能和影响技能 */
	typedef std::vector<_ITEM_AFFIX_SKILL>	EQUIP_AFFIX_SKILL_VEC;
	typedef std::vector<_ITEM_EFFECT_SKILL> EQUIP_EFFECT_SKILL_VEC;

	/*星座*/
	typedef std::vector<SItemConstInfo>    EQUIP_CONST_VEC;

	struct Base_Attr
	{
		int32 m_nBase_Atack_Near;
		int32 m_nBase_Atack_Far;
		int32 m_nBase_Atack_Magic;

		int32 m_nBase_Def_Near;
		int32 m_nBase_Def_Far;
		int32 m_nBase_Def_Magic;
		Base_Attr()
		{
			m_nBase_Atack_Near = -1;
			m_nBase_Atack_Far = -1;
			m_nBase_Atack_Magic = -1;
			m_nBase_Def_Near = -1;
			m_nBase_Def_Far = -1;
			m_nBase_Def_Magic = -1;
		}
		~Base_Attr()
		{
			m_nBase_Atack_Near = -1;
			m_nBase_Atack_Far = -1;
			m_nBase_Atack_Magic = -1;

			m_nBase_Def_Near = -1;
			m_nBase_Def_Far = -1;
			m_nBase_Def_Magic = -1;
		}
	};

	struct BASE_DEFINE
	{
		/* 装备数据表 */
		const _TABLE_ITEM_EQUIP* pDefineEquip;

		/*
		 * union ;
		 * { //高级装备外形 ;
		 * const _TABLE_ITEM_ADVANCED_EQUIP_VISUAL* pAdvVisual;
		 * //普通装备外形 ;
		 * const _TABLE_ITEM_COMMON_EQUIP_VISUAL* pCommonVisual;
		 * };
		 * 装备外形
		 */
		const _TABLE_ITEM_EQUIP_VISUAL* pEquipVisual;
		Base_Attr m_Base;
		BASE_DEFINE()
		{
			pEquipVisual = nullptr;
			pDefineEquip = nullptr;
		}
		~BASE_DEFINE()
		{
			pEquipVisual = nullptr;
			pDefineEquip = nullptr;
		}
	};

	/* 扩展属性定义 */
	struct EXTRA_DEFINE
	{
		/*
		 * 接收服务器参数 ;
		 * int32 m_nAttSet;
		 * //属性组 临时废弃
		 */
		BYTE m_StartLevel;						/* 星级 q */
		BYTE m_CurDurPoint;						/* 当前耐久值 q */
		USHORT m_CurDamagePoint;				/* 当前损伤度 q */
		BYTE m_GemCount;						/* 镶嵌的宝石个数 q */

		/*
		 * EQUIP_BIND_INFO m_nEquipBindInfo;
		 * //装备是否绑定 废弃 使用基类的m_BindInfo
		 */
		EQUIP_BIND_INFO m_nEquipBindInfo2;		/* 装备是否强化绑定（2级绑定） q */
		BYTE m_HonorBindLevel;						/* 荣誉铭刻级别*/
		EQUIP_ATTACH_GEM m_vEquipAttachGem;		/* 附加的宝石 q */
		int32 m_nEquipHoleNum;					/* 装备已经有的孔洞的数目 q */

		int32 m_nEquipScore;						/* 装备的分数（该分数大于某值后装备产生灵魂属性以及区分装备质量） q */
		EQUIP_ATTRIBUTES m_vEquipAttributes;	/* 装备属性 q */

		/*
		 * int32 m_nSellPrice;
		 * //售出价格
		 */
		int32 m_nLevelNeed;						/* 需求等级 q */
		int32 m_nMaxDurPoint;						/* 最大耐久值 q */

		/*
		 * int32 m_SetNum;
		 * //套装id
		 */
		EQUIP_AFFIX_SKILL_VEC m_Affix_Skill;	/* 附加技能 */
		EQUIP_EFFECT_SKILL_VEC m_Effect_Skill;	/* 影响技能 */

		/*
		 * STRING m_szAttrGroup;
		 * //属性组名 临时废弃 ;
		 * char m_RulerID;
		 * //新规则 q
		 */
		BYTE m_EquipType;						/* 装备类型 q */
		BYTE m_AttrCount;						/* 属性的数量 q */
		int32 m_PaiXing;			/* 装备的牌型 q */
		uint32 m_TermEndTime;		/* 到期时间,0表示永久生效不会过期，1表示已经过期，2表示还没开始计时 */
		BYTE m_byEquipLock;		/* 是否加锁 */
		uint32 m_UnLockEquipTime; /* 上次解锁时间 */
		std::vector<int32> m_BlueAddInfo; /* 蓝属性附加的信息 */
		uint32	m_BlueAttrIntensifyCount;	//蓝属性强化次数
		EQUIP_CONST_VEC m_vecConsts; /*星座信息*/
		EXTRA_DEFINE()
		{
			/*
			 * m_nAttSet = 0;
			 */
			m_StartLevel = 0;
			m_CurDurPoint = 0;
			m_CurDamagePoint = 0;
			m_GemCount = 0;

			/*
			 * m_nEquipBindInfo = FREE_BIND;
			 */
			m_nEquipBindInfo2 = FREE_BIND;
			m_HonorBindLevel = 0;
			m_nEquipHoleNum = 0;
			m_nEquipScore = 0;

			/*
			 * m_nSellPrice = 0;
			 */
			m_nLevelNeed = 0;
			m_nMaxDurPoint = 0;

			/*
			 * m_SetNum = -1;
			 * m_szAttrGroup = "";
			 * m_RulerID = -1;
			 */
			m_EquipType = -1;
			m_AttrCount = 0;
			m_PaiXing = -1;
			//m_vEquipAttachGem.clear();
			m_vEquipAttachGem.resize(7);
			m_vEquipAttributes.clear();
			m_Affix_Skill.clear();
			m_Effect_Skill.clear();
			m_byEquipLock = 0;
			m_UnLockEquipTime = 0;
			m_TermEndTime = 0;
			m_BlueAddInfo.resize(BLUE_ADD_MAX_ENCHASE, 0);
			m_BlueAttrIntensifyCount = 0;
			m_vecConsts.clear();
		}
	};
public:
	KItemEquip(uint64_t id);
	~KItemEquip();

	int32_t GetVisualID(void) const;
	uint32_t GetTermTime(void) const;

	int32 GetItemTableType(void) const;
	bool IsDefence() const;
	void AsEquip(const _TABLE_ITEM_EQUIP* pDefine);
	void AsAdvancedEquip(const _TABLE_ITEM_EQUIP* pDefine);
	void SetNeedLevel(int32_t level);
	void SetEquipHoleNum(int32_t hole);
	void SetStartLevel(int32_t level);
	int32_t GetStartLevel();
	PLAYER_EQUIP GetEquipPoint();
	void CalcEquipBaseAttrByAddStar();
private:
	/* 区分普通装备和高级装备 */
	EQUIP_ENUM m_eEquipStyle;
	/* 基本属性 */
	BASE_DEFINE m_theBaseDef;
	/* 扩展属性(需要服务器传输) */
	EXTRA_DEFINE* m_pExtraDefine;
	String m_strExtraDesc;
	/* 物品的详细编号 = ((nClass*100+nQuality)*100+nType)*1000+nIndex */
	int32					m_nParticularID;
};