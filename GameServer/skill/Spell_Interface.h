/*$T MapServer/Server/Spell/Spell_Interface.h GC 1.140 10/10/07 10:07:58 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef SKILL_CORE_H
#define SKILL_CORE_H

#include "TypeDefine.h"
#include "gameobject/Character.h"
#include "Spell_Helper.h"

BOOL			IsSpellInCollection(SpellInfo const &rSkillInfo, int32 nCollection);
int32			GetSpellInfoDescriptorValueByIndex(SpellInfo const &rSkillInfo, int32 nIndex);
ConditionAndDepleteTerm const	*Get_Property_ConDepTermByIndex(SpellInfo const &rSkillInfo, int32 nIndex);
int32			GetSpellHurtDelayTime(int32 iSkillID);
int32			GetSpellStandFlag(SpellID_t nSkill);


class	SpellInterface
{
	friend class	CombatSystem;
	friend class	Character;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SpellInterface()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~SpellInterface()
	{
	};
	BOOL	InstanceSpell(SpellInfo &rSkillInfoOut, Character &rMe, SpellID_t nSkill) const;
	BOOL	ProcessSpellRequest
		(
			Character	&rMe,
			SpellID_t	nSkillID,
			ObjID_t		nTargetID,
			GLPos const &rTargetPos,
			float		fTargetDir,
			GUID_t		guidTarget,
			int32		iHurtDelayTime,
			BOOL		bSubSkill = FALSE
		) const;
	void	OnException(Character &rMe) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	BOOL	ProcessSpellRequestImp
		(
			Character	&rMe,
			SpellID_t	nSkillID,
			ObjID_t		nTargetID,
			GLPos const &rTargetPos,
			float		fTargetDir,
			GUID_t		guidTarget,
			int32		iHurtDelayTime,
			BOOL		bSubSkill
		) const;
	BOOL	CheckCanUseSpellByHorse(Character &rMe, SpellID_t nSkillID) const;
	BOOL	CheckCanUseSpellByBus(Character &rMe, SpellID_t nSkillID) const;
	BOOL	ActiveSpellNow(Character &rMe, BOOL bSubSkill) const;
	BOOL	IsCanPassCheckByWeapon
		(
			SpellInfo				&rSkillInfo,
			Character				&rMe,
			SpellTargetingAndDepletingParams	&rParams
		) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
};

extern SpellInterface	g_SpellCore;

#endif
