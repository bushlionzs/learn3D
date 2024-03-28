#include "OgreHeader.h"
#include "string_util.h"
#include "KItemEquip.h"
#include "Basics.h"
#include "SplitStringLevelOne.h"
#include "SplitStringLevelTwo.h"
#include "GameTableDefine.h"
#include "GameTableManager.h"
#include "KTable.h"

KItemEquip::KItemEquip(uint64_t id)
	:KItem(id)
{
	mObjectType = ObjectType_ItemEquip;
	m_pExtraDefine = nullptr;
}

KItemEquip::~KItemEquip()
{

}

int32_t KItemEquip::GetVisualID(void) const
{
	if (m_theBaseDef.pEquipVisual)
	{
		return m_theBaseDef.pEquipVisual->nModelID;
	}

	return -1;
}

uint32_t KItemEquip::GetTermTime(void) const
{
	if (m_pExtraDefine)
	{
		return m_pExtraDefine->m_TermEndTime;
	}
	else
		return 0;
}

int32 KItemEquip::GetItemTableType(void) const
{
	if (m_theBaseDef.pDefineEquip)
	{
		return m_theBaseDef.pDefineEquip->nType;
	}

	return INVALID_ID;
}

bool KItemEquip::IsDefence() const
{
	int32 iType = GetItemTableType();

	switch (iType)
	{
	case EQUIP_SDUN:
	case EQUIP_SGU:
	case EQUIP_CRUSADE_ASSIST_HAND:
		return TRUE;
	default:
		break;
	}
	return FALSE;
}

void KItemEquip::AsEquip(const _TABLE_ITEM_EQUIP* pDefine)
{
	if (NULL == pDefine) return;

	m_theBaseDef.pDefineEquip = pDefine;

	m_nParticularID = 
		((pDefine->nClass * 100 + pDefine->nType) * 10000) + pDefine->nIndex;

	if (NULL == m_pExtraDefine) m_pExtraDefine = new EXTRA_DEFINE;

	/*
		* m_pExtraDefine->m_nSellPrice = pDefine->nBasePrice;
		* //售出价格 ;
		* SetNeedLevel(pDefine->nLevelRequire);
		* //需求等级
		*/
	const char* pSplitString = pDefine->nLevelRequire;
	SplitStringLevelOne pSplitL1;
	SplitStringLevelTwo pSplitL2;

	pSplitL1.Reset();
	pSplitL2.Reset();
	pSplitL1.Init('|', &pSplitL2);
	pSplitL2.Init('~', NULL);
	pSplitL1.DoSplit(pSplitString);

	int32 iLineCount = pSplitL2.GetResultLineCount();

	SetNeedLevel(atoi(pSplitL2.GetResultLine(iLineCount - 1)));
	SetEquipHoleNum(m_theBaseDef.pDefineEquip->nNatureHoleNum);
	m_pExtraDefine->m_nMaxDurPoint = pDefine->nBMaxDur;	/* 最大耐久值 */
	m_pExtraDefine->m_TermEndTime = 2;	/* 2表示尚未开始计时 */

	/*
	 * m_pExtraDefine->m_SetNum = pDefine->nSetID;
	 * //套装id ;
	 * m_pExtraDefine->m_nSellPrice = pDefine->nBasePrice;
	 * //价格 ;
	 * 当前耐久值
	 */
	m_pExtraDefine->m_CurDurPoint = pDefine->nBMaxDur;

	/* max耐久 */
	const char* pSplitString_Start_Level = pDefine->nStarLeveL;
	SplitStringLevelOne		pSplitL1_Start_Level;
	SplitStringLevelTwo		pSplitL2_Start_Level;

	pSplitL1_Start_Level.Reset();
	pSplitL2_Start_Level.Reset();
	pSplitL1_Start_Level.Init('|', &pSplitL2_Start_Level);
	pSplitL2_Start_Level.Init('~', NULL);
	pSplitL1_Start_Level.DoSplit(pSplitString_Start_Level);

	int32 iLineCount_Star_Levvel = 1;		/* pSplitL2_Start_Level.GetResultLineCount();
										 * */

	SetStartLevel(atoi(pSplitL2_Start_Level.GetResultLine(iLineCount_Star_Levvel - 1)));

	/*
		* 打开数据表 ;
		* TABLE_DEFINEHANDLE(s_pItem_Visual, TABLE_ITEM_EQUIP_VISUAL);
		*/
	const CGameTable* pItem_Visual = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_EQUIP_VISUAL);

	if (NULL == pItem_Visual) return;

	/* 搜索纪录 */
	const _TABLE_ITEM_EQUIP_VISUAL* pVisual = 
		(const _TABLE_ITEM_EQUIP_VISUAL*)pItem_Visual->GetFieldDataByIndex(pDefine->nID);

	if (NULL == pVisual) return;

	m_theBaseDef.pEquipVisual = pVisual;

	m_theBaseDef.m_Base.m_nBase_Atack_Near = pDefine->nBaseAttackNear;
	m_theBaseDef.m_Base.m_nBase_Atack_Far = pDefine->nBaseAttackFar;
	m_theBaseDef.m_Base.m_nBase_Atack_Magic = pDefine->nBaseAttackMagic;

	m_theBaseDef.m_Base.m_nBase_Def_Near = pDefine->nBaseDEefNear;
	m_theBaseDef.m_Base.m_nBase_Def_Far = pDefine->nBaseDefFar;
	m_theBaseDef.m_Base.m_nBase_Def_Magic = pDefine->nBaseDefMagic;
	CalcEquipBaseAttrByAddStar();

	/* 高级装备 */
	if (!ISCommonEquip(pDefine->nID))
	{
		m_eEquipStyle = ADVANCED_EQUIP;
		AsAdvancedEquip(pDefine);
	}

/* 普通装备 */
	else
	{
		m_eEquipStyle = COMMON_EQUIP;
	}
}

void KItemEquip::AsAdvancedEquip(const _TABLE_ITEM_EQUIP* pDefine)
{
	if (NULL == pDefine || NULL == m_pExtraDefine) return;


	/*
		* 装备属性 ;
		* _ITEM_PROPERTY attr;
		* m_pExtraDefine->m_vEquipAttributes.clear();
		* for(int32 i=0;
		* i<EQUIP_EFFECT_ATTR_MAXNUM;
		* i++) ;
		* { ;
		* if(-1 != pDefine->stEffectAttr[i].nAttrID ) ;
		* { ;
		* attr.m_AttrType = (BYTE)pDefine->stEffectAttr[i].nAttrID;
		* attr.m_Value.m_Value = (SHORT)pDefine->stEffectAttr[i].nEffectNum;
		* ;
		* m_pExtraDefine->m_vEquipAttributes.push_back(attr);
		* } ;
		* } ;
		* 附加技能
		*/
	_ITEM_AFFIX_SKILL	affx_skill;

	m_pExtraDefine->m_Affix_Skill.clear();

	for (int32 i = 0; i < EQUIP_ADDEFFECT_SKILL_MAXNUM; i++)
	{
		if (-1 != pDefine->stADDEffectSkill[i].nSkillID)
		{
			affx_skill.m_nSkillID = (WORD)pDefine->stADDEffectSkill[i].nSkillID;
			affx_skill.m_nLevel = (BYTE)pDefine->stADDEffectSkill[i].nEffectLevel;
			m_pExtraDefine->m_Affix_Skill.push_back(affx_skill);
		}
	}


		/* 影响技能 */
	_ITEM_EFFECT_SKILL	effect_skill;

	m_pExtraDefine->m_Effect_Skill.clear();

	for (int32 i = 0; i < EQUIP_EFFECT_SKILL_MAXNUM; i++)
	{
		if (-1 != pDefine->stEffectSkill[i].nSkillID)
		{
			effect_skill.m_nSkillID = (WORD)pDefine->stEffectSkill[i].nSkillID;
			effect_skill.m_nLevel = (BYTE)pDefine->stEffectSkill[i].nEffectLevel;
			m_pExtraDefine->m_Effect_Skill.push_back(effect_skill);
		}
	}
}

void KItemEquip::SetNeedLevel(int32_t level)
{
	if (m_pExtraDefine)
	{
		m_pExtraDefine->m_nLevelNeed = level;
	}
}

void KItemEquip::SetEquipHoleNum(int32_t hole)
{
	if (hole < 0 || hole > MAX_GEM_HOLE)
	{
		return;
	}

	if (m_pExtraDefine)
	{
		m_pExtraDefine->m_nEquipHoleNum = hole;
	}
}

void KItemEquip::SetStartLevel(int32_t level)
{
	if (m_pExtraDefine)
	{
		m_pExtraDefine->m_StartLevel = level;
	}
}

int32_t KItemEquip::GetStartLevel()
{
	if (m_pExtraDefine)
	{
		return m_pExtraDefine->m_StartLevel;
	}

	return -1;
}

PLAYER_EQUIP KItemEquip::GetEquipPoint()
{
	if (m_theBaseDef.pDefineEquip)
	{
		return(PLAYER_EQUIP)m_theBaseDef.pDefineEquip->nEquipPoint;
	}

	return(PLAYER_EQUIP)-1;
}

void KItemEquip::CalcEquipBaseAttrByAddStar()
{
	/*
	 * TABLE_DEFINEHANDLE(s_Add_Star, TABLE_EQUIP_ADD_START);
	 */
	const CGameTable* pAdd_Star = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_EQUIP_ADD_START);
	PLAYER_EQUIP		ep = GetEquipPoint();
	int32					nSearchIndex = 0;

	if (ep <= HEQUIP_RING1)
	{
		nSearchIndex = ep * EQUIP_STAR_NUM_LIMIT;
	}
	else if (ep <= HEQUIP_ADORN1)
	{
		nSearchIndex = (ep - 1) * EQUIP_STAR_NUM_LIMIT;
	}

	/* 搜索纪录 */
	const _TABLE_EQUIP_ADD_START* p_Add_Star = 
		(const _TABLE_EQUIP_ADD_START*)pAdd_Star->GetFieldDataByIndex((uint32)(nSearchIndex + GetStartLevel()));

	if (p_Add_Star && GetStartLevel() > 0)
	{
		EQUIP_ADD_STAR_INFO add_star_info = p_Add_Star->Add_Star_Info[0];
		int32					IntensifyInfo = add_star_info.nIntensifyInfo;

		m_theBaseDef.m_Base.m_nBase_Atack_Near = int32(m_theBaseDef.pDefineEquip->nBaseAttackNear * (1 + IntensifyInfo / 100.0f) + 0.5f);
		m_theBaseDef.m_Base.m_nBase_Atack_Far = int32(m_theBaseDef.pDefineEquip->nBaseAttackFar * (1 + IntensifyInfo / 100.0f) + 0.5f);
		m_theBaseDef.m_Base.m_nBase_Atack_Magic = int32(m_theBaseDef.pDefineEquip->nBaseAttackMagic * (1 + IntensifyInfo / 100.0f) + 0.5f);
		m_theBaseDef.m_Base.m_nBase_Def_Near = int32(m_theBaseDef.pDefineEquip->nBaseDEefNear * (1 + IntensifyInfo / 100.0f) + 0.5f);
		m_theBaseDef.m_Base.m_nBase_Def_Far = int32(m_theBaseDef.pDefineEquip->nBaseDefFar * (1 + IntensifyInfo / 100.0f) + 0.5f);
		m_theBaseDef.m_Base.m_nBase_Def_Magic = int32(m_theBaseDef.pDefineEquip->nBaseDefMagic * (1 + IntensifyInfo / 100.0f) + 0.5f);
	}
	else
	{
		if (m_theBaseDef.pDefineEquip)
		{
			m_theBaseDef.m_Base.m_nBase_Atack_Near = m_theBaseDef.pDefineEquip->nBaseAttackNear;
			m_theBaseDef.m_Base.m_nBase_Atack_Far = m_theBaseDef.pDefineEquip->nBaseAttackFar;
			m_theBaseDef.m_Base.m_nBase_Atack_Magic = m_theBaseDef.pDefineEquip->nBaseAttackMagic;
			m_theBaseDef.m_Base.m_nBase_Def_Near = m_theBaseDef.pDefineEquip->nBaseDEefNear;
			m_theBaseDef.m_Base.m_nBase_Def_Far = m_theBaseDef.pDefineEquip->nBaseDefFar;
			m_theBaseDef.m_Base.m_nBase_Def_Magic = m_theBaseDef.pDefineEquip->nBaseDefMagic;
		}
	}
}

const char* getProfessionDesc(int profession)
{
	switch (profession)
	{
	case 0:
		return "武士";
	case 1:
		return "武士";
	default:
		return "不限";
	}
}
std::string KItemEquip::getBasePropertyString()
{
	return dy::str_format("等级: %d\n职业: %s\n耐久:", GetItemLevel(), getProfessionDesc(GetItemProfession()));

}

int32 KItemEquip::GetItemProfession()
{
	if (m_theBaseDef.pDefineEquip)
	{
		return m_theBaseDef.pDefineEquip->nProfessionalReq;
	}

	return -1;
}

int32 KItemEquip::GetItemLevel()
{
	if (m_pExtraDefine)
	{
		return m_pExtraDefine->m_nLevelNeed;
	}

	return -1;
}