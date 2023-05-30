/*$T MapServer/Server/Spell/SpecialObjLogic/Spell_TrapObjLogic_Trap.h GC 1.140 10/10/07 10:07:56 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef TRAPLOGIC_H
#define TRAPLOGIC_H
#include "TypeDefine.h"
#include "Spell_TrapObjLogic.h"
#include "gameobject/Character.h"

//ÏÝÚåÂß¼­ ÈçÆïÉäµÄÃÔ»êË÷ add by wujianping
class TrapObjectLogic :
	public SpecialObjectLogic
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { TYPE = TRAP_OBJ, };
	enum { ID = TRAP_LOGIC_ID, };
	enum
	{
		MASK_ACTIVATE_WHEN_FADE_OUT	= 1,
		MASK_TRIGGER_BY_CHARACTER	= 2,
		MASK_TRIGGER_BY_TRAP		= 4,
	};
	class DescriptorIndex
	{
	public: enum { INDEX_EFFECT0 = 0, INDEX_EFFECT1, INDEX_EFFECT2_ACTIVATE_ODDS, INDEX_EFFECT2, };
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	TrapObjectLogic()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~TrapObjectLogic()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual int32 GetType(void) const
	{
		return TYPE;
	};
	virtual void	ForceActivate(SpecialCreature &rThis) const;
	virtual void	ForceFadeOut(SpecialCreature &rThis) const;
	void		OnEvent_Tick(SpecialCreature &rThis) const;
	void		OnEvent_TimeOver(SpecialCreature &rThis) const;
	BOOL		TriggerCheck(SpecialCreature &rMe) const;

	virtual BOOL	CanTriggerBySpecificObj(SpecialCreature &rMe, Character &rTar) const;
	virtual BOOL	CanTriggerBySpecificObj(SpecialCreature &rMe, SpecialCreature &rOther) const;
	virtual BOOL	IsScanedTargetValid(SpecialCreature &rThis, Character &rScaned) const;
	virtual BOOL	IsScanedTargetValid(SpecialCreature &rThis, SpecialCreature &rScaned) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	int32		GetEffect0(SpecialCreature &rThis) const;
	int32		GetEffect1(SpecialCreature &rThis) const;
	int32		GetEffect2(SpecialCreature &rThis) const;
	int32		GetEffect2ActivateOdds(SpecialCreature &rThis) const;
	BOOL		CanTriggerByTrap(SpecialCreature &rThis) const;
	BOOL		ActivateWhenFadeOut(SpecialCreature &rThis) const;
	BOOL		CanTriggerByCharacter(SpecialCreature &rThis) const;
	BOOL		EffectOnTrap(SpecialCreature &rThis, SpecialCreature &rTar) const;

	virtual BOOL	EffectOnChar(SpecialCreature &rThis, Character &rTar) const;
	BOOL CheckEffectAvailability(Character &rMe, Character &rTar, ID_t nDataIndex) const;
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	void	Activate(SpecialCreature &rMe) const;
};
#endif
