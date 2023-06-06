#pragma once
#include "KItem.h"
#include "GameTableData.h"
#include "ItemCommon.h"
#include "StructItem.h"

class KItemEquip : public KItem
{
public:
	/* ������ͨ�͸߼�װ�� */
	enum EQUIP_ENUM
	{
		INVAILD_EQUIP = -1,					/* ��Ч */
		COMMON_EQUIP,							/* ��ͨ */
		ADVANCED_EQUIP,							/* �߼� */
	};
	/* ���Ժͱ�ʯ */
	typedef std::vector<_ITEM_PROPERTY>			EQUIP_ATTRIBUTES;
	typedef std::vector<SItemGemInfo>		EQUIP_ATTACH_GEM;

	/* ���Ӽ��ܺ�Ӱ�켼�� */
	typedef std::vector<_ITEM_AFFIX_SKILL>	EQUIP_AFFIX_SKILL_VEC;
	typedef std::vector<_ITEM_EFFECT_SKILL> EQUIP_EFFECT_SKILL_VEC;

	/*����*/
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
		/* װ�����ݱ� */
		const _TABLE_ITEM_EQUIP* pDefineEquip;

		/*
		 * union ;
		 * { //�߼�װ������ ;
		 * const _TABLE_ITEM_ADVANCED_EQUIP_VISUAL* pAdvVisual;
		 * //��ͨװ������ ;
		 * const _TABLE_ITEM_COMMON_EQUIP_VISUAL* pCommonVisual;
		 * };
		 * װ������
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

	/* ��չ���Զ��� */
	struct EXTRA_DEFINE
	{
		/*
		 * ���շ��������� ;
		 * int32 m_nAttSet;
		 * //������ ��ʱ����
		 */
		BYTE m_StartLevel;						/* �Ǽ� q */
		BYTE m_CurDurPoint;						/* ��ǰ�;�ֵ q */
		USHORT m_CurDamagePoint;				/* ��ǰ���˶� q */
		BYTE m_GemCount;						/* ��Ƕ�ı�ʯ���� q */

		/*
		 * EQUIP_BIND_INFO m_nEquipBindInfo;
		 * //װ���Ƿ�� ���� ʹ�û����m_BindInfo
		 */
		EQUIP_BIND_INFO m_nEquipBindInfo2;		/* װ���Ƿ�ǿ���󶨣�2���󶨣� q */
		BYTE m_HonorBindLevel;						/* �������̼���*/
		EQUIP_ATTACH_GEM m_vEquipAttachGem;		/* ���ӵı�ʯ q */
		int32 m_nEquipHoleNum;					/* װ���Ѿ��еĿ׶�����Ŀ q */

		int32 m_nEquipScore;						/* װ���ķ������÷�������ĳֵ��װ��������������Լ�����װ�������� q */
		EQUIP_ATTRIBUTES m_vEquipAttributes;	/* װ������ q */

		/*
		 * int32 m_nSellPrice;
		 * //�۳��۸�
		 */
		int32 m_nLevelNeed;						/* ����ȼ� q */
		int32 m_nMaxDurPoint;						/* ����;�ֵ q */

		/*
		 * int32 m_SetNum;
		 * //��װid
		 */
		EQUIP_AFFIX_SKILL_VEC m_Affix_Skill;	/* ���Ӽ��� */
		EQUIP_EFFECT_SKILL_VEC m_Effect_Skill;	/* Ӱ�켼�� */

		/*
		 * STRING m_szAttrGroup;
		 * //�������� ��ʱ���� ;
		 * char m_RulerID;
		 * //�¹��� q
		 */
		BYTE m_EquipType;						/* װ������ q */
		BYTE m_AttrCount;						/* ���Ե����� q */
		int32 m_PaiXing;			/* װ�������� q */
		uint32 m_TermEndTime;		/* ����ʱ��,0��ʾ������Ч������ڣ�1��ʾ�Ѿ����ڣ�2��ʾ��û��ʼ��ʱ */
		BYTE m_byEquipLock;		/* �Ƿ���� */
		uint32 m_UnLockEquipTime; /* �ϴν���ʱ�� */
		std::vector<int32> m_BlueAddInfo; /* �����Ը��ӵ���Ϣ */
		uint32	m_BlueAttrIntensifyCount;	//������ǿ������
		EQUIP_CONST_VEC m_vecConsts; /*������Ϣ*/
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
	/* ������ͨװ���͸߼�װ�� */
	EQUIP_ENUM m_eEquipStyle;
	/* �������� */
	BASE_DEFINE m_theBaseDef;
	/* ��չ����(��Ҫ����������) */
	EXTRA_DEFINE* m_pExtraDefine;
	String m_strExtraDesc;
	/* ��Ʒ����ϸ��� = ((nClass*100+nQuality)*100+nType)*1000+nIndex */
	int32					m_nParticularID;
};