/*$T MapServer/Server/Spell/Spell_ScriptLogic.h GC 1.140 10/10/07 10:07:57 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef SCRIPTLOGIC_H
#define SCRIPTLOGIC_H
#include "TypeDefine.h"
#include "Player.h"

class	SpellScriptLogic
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SpellScriptLogic()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~SpellScriptLogic()
	{
	};

	BOOL	StartCharging(Character &rMe) const;
	BOOL	StartChanneling(Character &rMe) const;
	BOOL	StartLaunching(Character &rMe) const;
	BOOL	Action_ActivateOnceDispatch(Character &rMe) const;
	BOOL	Action_ActivateEachTickDispatch(Character &rMe) const;
	BOOL	Item_IsSpellLikeScript(Character &rMe, ScriptID_t nScript) const;
	BOOL	CallItemDefaultEvent(Character &rMe, ScriptID_t nScript, int32 nBagIndex) const;
	BOOL	Equip_CallDefaultEvent(Character &rMe, ScriptID_t nScript, int32 equipPoint, int32 opType) const;
	BOOL	RegisterImpactEvent
		(
			Character	&rReceiver,
			Character	&rSender,
			UNIT_EFFECT	&rImp,
			Time_t		nDelayTime,
			BOOL		bCriticalFlag
		) const;
	BOOL	RegisterSkillMissEvent
		(
			Character	&rReceiver,
			Character	&rSender,
			SpellID_t	nSkill,
			Time_t		nDelayTime
		) const;
	BOOL	RegisterBeSkillEvent
		(
			Character	&rReceiver,
			Character	&rSender,
			int32		nBehaviorType,
			Time_t		nDelayTime
		) const;
	BOOL	LUA_CancelImpacts(Character &rMe, ScriptID_t nScriptID) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	BOOL	LUA_OnConditionCheck_i(Character &rMe) const;
	BOOL	LUA_OnDeplete_i(Character &rMe) const;
	BOOL	LUA_OnActivateOnce_i(Character &rMe) const;
	BOOL	LUA_OnActivateEachTick_i(Character &rMe) const;

	void	SetCooldown(Character &rMe, CooldownID_t nID, int32 nCooldownTime) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
};
extern SpellScriptLogic g_ScriptLogic;
#endif
