/*$T MapServer/Server/Spell/Spell_EffectLogicManager.h GC 1.140 10/10/07 10:07:56 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef LOGICMANAGER_H
#define LOGICMANAGER_H

#include "TypeDefine.h"
#include "Spell_EffectLogic_All.h"
#include "Spell_Helper.h"
#include "Spell_Logic_Misc.h"
#include "Spell_Logic_EffectsToTarget.h"
#include "Spell_Logic_Base.h"
#include "Spell_Logic_Profession.h"
#include "Spell_TrapObjLogic.h"
#include "gameobject/Profession_All.h"

template<typename T, int32 nSize>
class EffectLogicManager
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	EffectLogicManager();
	~	EffectLogicManager();
	BOOL	Init(void);
	T const *GetLogicById(int32 const nId);
	void	RegisterLogic(int32 nID, T *pLogic);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	BOOL	m_bReady;
	T	*m_apLogics[nSize];
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */

template<typename T, int32 nSize>
EffectLogicManager<T, nSize>::EffectLogicManager()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	memset((void *) m_apLogics, 0, sizeof(m_apLogics));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_bReady = Init();
	__UNGUARD__
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */

template<typename T, int32 nSize>
inline BOOL EffectLogicManager<T, nSize>::Init(void)
{
	__GUARD__ return FALSE;
	__UNGUARD__ return FALSE;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */

template<typename T, int32 nSize>
inline EffectLogicManager<T, nSize>::~EffectLogicManager()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_bReady = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; nSize > i; ++i)
	{
		if(NULL != m_apLogics[i])
		{
			KSafeDelete(m_apLogics[i]);
		};
	};
	__UNGUARD__
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */

template<typename T, int32 nSize>
inline T const *EffectLogicManager<T, nSize>::GetLogicById(int32 const nId)
{
	__GUARD__ if(0 <= nId && nSize > nId && TRUE == m_bReady)
	{
		return m_apLogics[nId];
	}

	return NULL;
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<typename T, int32 nSize>
inline void EffectLogicManager<T, nSize>::RegisterLogic(int32 nID, T *pLogic)
{
	KCheck(m_apLogics[nID] == NULL);
	m_apLogics[nID] = pLogic;
}

#define REGISTER_LOGIC(LOGIC)	{ RegisterLogic(LOGIC::ID, (new(LOGIC))); }

/*
 =======================================================================================================================
 =======================================================================================================================
 */

template<>
inline BOOL EffectLogicManager<EffectLogic, NUMBER_OF_IMPACT_LOGIC_IDS>::Init(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	REGISTER_LOGIC(SpellEffect000);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	REGISTER_LOGIC(SpellEffect001);
	REGISTER_LOGIC(SpellEffect002);
	REGISTER_LOGIC(SpellEffect003);
	REGISTER_LOGIC(SpellEffect004);
	REGISTER_LOGIC(SpellEffect005);
	REGISTER_LOGIC(SpellEffect006);
	REGISTER_LOGIC(SpellEffect007);
	REGISTER_LOGIC(SpellEffect008);
	REGISTER_LOGIC(SpellEffect009);
	REGISTER_LOGIC(SpellEffect010);
	REGISTER_LOGIC(SpellEffect011);
	REGISTER_LOGIC(SpellEffect012);
	REGISTER_LOGIC(SpellEffect013);
	REGISTER_LOGIC(SpellEffect014);
	REGISTER_LOGIC(SpellEffect015);
	REGISTER_LOGIC(SpellEffect016);
	REGISTER_LOGIC(SpellEffect017);
	REGISTER_LOGIC(SpellEffect018);
	REGISTER_LOGIC(SpellEffect019);
	REGISTER_LOGIC(SpellEffect020);
	REGISTER_LOGIC(SpellEffect021);
	REGISTER_LOGIC(SpellEffect022);
	REGISTER_LOGIC(SpellEffect023);
	REGISTER_LOGIC(SpellEffect024);
	REGISTER_LOGIC(SpellEffect025);
	REGISTER_LOGIC(SpellEffect026);
	REGISTER_LOGIC(SpellEffect027);
	REGISTER_LOGIC(SpellEffect028);
	REGISTER_LOGIC(SpellEffect029);
	REGISTER_LOGIC(SpellEffect030);
	REGISTER_LOGIC(SpellEffect031);
	REGISTER_LOGIC(SpellEffect032);
	REGISTER_LOGIC(SpellEffect033);
	REGISTER_LOGIC(SpellEffect034);
	REGISTER_LOGIC(SpellEffect035);
	REGISTER_LOGIC(SpellEffect036);
	REGISTER_LOGIC(SpellEffect037);
	REGISTER_LOGIC(SpellEffect038);
	REGISTER_LOGIC(SpellEffect039);
	REGISTER_LOGIC(SpellEffect040);
	REGISTER_LOGIC(SpellEffect041);
	REGISTER_LOGIC(SpellEffect042);
	REGISTER_LOGIC(SpellEffect043);
	REGISTER_LOGIC(SpellEffect044);
	REGISTER_LOGIC(SpellEffect045);
	REGISTER_LOGIC(SpellEffect046);
	REGISTER_LOGIC(SpellEffect047);
	REGISTER_LOGIC(SpellEffect048);
	REGISTER_LOGIC(SpellEffect049);
	REGISTER_LOGIC(SpellEffect050);
	REGISTER_LOGIC(SpellEffect051);
	REGISTER_LOGIC(SpellEffect052);
	REGISTER_LOGIC(SpellEffect053);
	REGISTER_LOGIC(SpellEffect054);
	REGISTER_LOGIC(SpellEffect055);
	REGISTER_LOGIC(SpellEffect056);
	REGISTER_LOGIC(SpellEffect057);

	REGISTER_LOGIC(SpellEffect058);
	REGISTER_LOGIC(SpellEffect059);
	REGISTER_LOGIC(SpellEffect060);
	REGISTER_LOGIC(SpellEffect061);
	REGISTER_LOGIC(SpellEffect062);
	REGISTER_LOGIC(SpellEffect063);
	REGISTER_LOGIC(SpellEffect064);
	REGISTER_LOGIC(SpellEffect065);
	REGISTER_LOGIC(SpellEffect066);
	REGISTER_LOGIC(SpellEffect067);
	REGISTER_LOGIC(SpellEffect068);
	REGISTER_LOGIC(SpellEffect069);
	REGISTER_LOGIC(SpellEffect070);
	REGISTER_LOGIC(SpellEffect071);
	REGISTER_LOGIC(SpellEffect072);
	REGISTER_LOGIC(SpellEffect073);
	REGISTER_LOGIC(SpellEffect074);
	REGISTER_LOGIC(SpellEffect075);
	REGISTER_LOGIC(SpellEffect076);
	REGISTER_LOGIC(SpellEffect077);
	REGISTER_LOGIC(SpellEffect078);
	REGISTER_LOGIC(SpellEffect079);
	REGISTER_LOGIC(SpellEffect080);
	REGISTER_LOGIC(SpellEffect081);
	REGISTER_LOGIC(SpellEffect082);
	REGISTER_LOGIC(SpellEffect083);
	REGISTER_LOGIC(SpellEffect084);
	REGISTER_LOGIC(SpellEffect085);
	REGISTER_LOGIC(SpellEffect086);
	REGISTER_LOGIC(SpellEffect087);
	REGISTER_LOGIC(SpellEffect088);
	REGISTER_LOGIC(SpellEffect089);
	REGISTER_LOGIC(SpellEffect090);
	m_bReady = TRUE;
	return TRUE;
	__UNGUARD__ return FALSE;
};


/*
 =======================================================================================================================
 =======================================================================================================================
 */

template<>
inline BOOL EffectLogicManager<BaseSpellLogic, MAX_SKILL_LOGIC_ID>::Init(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	REGISTER_LOGIC(EffectsToTarget);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	REGISTER_LOGIC(EffectsToTargetAndSelf);
	REGISTER_LOGIC(TeleportAndEffects);
	REGISTER_LOGIC(EffectsToTargetAndSelfForRun);

	REGISTER_LOGIC(ArmorMastery);
	REGISTER_LOGIC(WeaponMastery);

	REGISTER_LOGIC(CommonSpell001);
	REGISTER_LOGIC(CommonSpell002);
	REGISTER_LOGIC(CommonSpell003);
	REGISTER_LOGIC(CommonSpell004);

	REGISTER_LOGIC(WuShi_Spell001);
	REGISTER_LOGIC(WuShi_Spell002);
	REGISTER_LOGIC(JianXia_Spell001);
	REGISTER_LOGIC(QiShe_Spell001);
	REGISTER_LOGIC(HuoQiang_Spell001);
	REGISTER_LOGIC(XianZhi_Spell001);
	REGISTER_LOGIC(SaMan_Spell001);
	REGISTER_LOGIC(JianXia_SpellTrap);
	REGISTER_LOGIC(Profession_9_Spell002);

	m_bReady = TRUE;
	return TRUE;
	__UNGUARD__ return FALSE;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */

template<>
inline BOOL EffectLogicManager<Profession, PROFESSION_NUMBER>::Init(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	REGISTER_LOGIC(XianZhiProfession);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	REGISTER_LOGIC(QiSheProfession);
	REGISTER_LOGIC(JianXiaProfession);
	REGISTER_LOGIC(WuShiProfession);
	REGISTER_LOGIC(HuoQiangProfession);
	REGISTER_LOGIC(SaManProfession);
	REGISTER_LOGIC(ShiZiJunProfession);
	REGISTER_LOGIC(ShengHuoShiProfession);
	REGISTER_LOGIC(CiKeProfession);
	REGISTER_LOGIC(JinWeiJunProfession);
	REGISTER_LOGIC(YinXiuShiProfession);
	REGISTER_LOGIC(LaMaProfession);

	m_bReady = TRUE;
	return TRUE;
	__UNGUARD__ return FALSE;
};


typedef class EffectLogicManager<Profession, PROFESSION_NUMBER> ProfessionLogicManager_T;
typedef class EffectLogicManager<EffectLogic, NUMBER_OF_IMPACT_LOGIC_IDS> ImpactLogicManager_T;
typedef class EffectLogicManager<SpecialObjectLogic, SpecialObjectLogic::MAX_ID> SpecialObjLogicManager_T;
typedef class EffectLogicManager<BaseSpellLogic, MAX_SKILL_LOGIC_ID> SkillLogicManager_T;

extern ProfessionLogicManager_T g_ProfessionLogicList;
extern ImpactLogicManager_T g_EffectLogicList;
extern SkillLogicManager_T g_SpellLogicList;

#endif
