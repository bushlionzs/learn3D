/*$T MapServer/Server/Spell/Spell_EffectInterface.h GC 1.140 10/10/07 10:07:56 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef EFFECT_INTERFACE_H
#define EFFECT_INTERFACE_H

#include "TypeDefine.h"
#include "gameobject/Character.h"
#include "SpellDataLoader.h"

class	EffectInterface
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
	EffectInterface()
	{
		m_uUniqueID = 1;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~EffectInterface()
	{
	};
	uint32	GetUniqueID();
	BOOL	SendEffectToUnit
		(
			Character	&rTar,
			ID_t		nDataIndex,
			ObjID_t		nSender,
			Time_t		nDelayTime = 0,
			BOOL		bCriticalFlag = FALSE,
			int32		nRefixRate = 0
		) const;
	BOOL	SendEffectToUnit
		(
			Character	&rTar,
			ID_t		nDataIndex,
			ObjID_t		nSender,
			SpellID_t	nSkillID,
			Time_t		nDelayTime = 0,
			BOOL		bCriticalFlag = FALSE,
			int32		nRefixRate = 0
		) const;
	BOOL	InitEffectFromData(ID_t nDataIndex, UNIT_EFFECT &rImp, Character &rTar) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	uint32	m_uUniqueID;
};

int32			GetEffectDataDescriptorValueByIndex(int32 nDataIndex, int32 nIndex, int32 iLevel);
int32			GetEffectScriptID(UNIT_EFFECT &rImp);
ID_t			GetEffectLogicID(UNIT_EFFECT const &rImp);
ID_t			GetEffectID(UNIT_EFFECT &rImp);
ID_t			GetEffectMutexID(UNIT_EFFECT &rImp);
ID_t			GetEffectLevel(UNIT_EFFECT &rImp);
ID_t			GetEffectStandFlag(UNIT_EFFECT &rImp);
ID_t			IgnoreEffectFliter(UNIT_EFFECT &rImp);
BOOL			IsEffectOverTimed(UNIT_EFFECT &rImp);
BOOL			GetEffectMutexByCasterFlag(UNIT_EFFECT &rImp);
BOOL			IsEffectsABMutexed(UNIT_EFFECT &rImpactA, UNIT_EFFECT &rImpactB);
BOOL			CanEffectAReplaceB(UNIT_EFFECT &rImpactA, UNIT_EFFECT &rImpactB);
BOOL			IsEffectRemainOnCorpse(UNIT_EFFECT &rImp);
BOOL			CanEffectBeDispeled(UNIT_EFFECT &rImp);
BOOL			CanEffectBeCanceled(UNIT_EFFECT &rImp);
BOOL			NeedEffectChannelSupport(UNIT_EFFECT &rImp);
BOOL			IsEffectFadeOutWhenUnitOnDamage(UNIT_EFFECT &rImp);
BOOL			IsEffectFadeOutWhenUnitStartActions(UNIT_EFFECT &rImp);
BOOL			IsEffectFadeOutWhenUnitOffline(UNIT_EFFECT &rImp);
BOOL			IsEffectStillTimingWhenUnitOffline(UNIT_EFFECT &rImp);
BOOL			IsEffectInCollection(UNIT_EFFECT &rImp, int32 nCollection);
BOOL			IsEffectPassive(UNIT_EFFECT &rImp);
Time_t			GetEffectTableContinuance(UNIT_EFFECT &rImp);
Time_t			GetEffectInterval(UNIT_EFFECT &rImp);
EffectData const	*GetEffectDataBlock(ID_t nDataIndex);
Object			*GetEffectCaster(Object &rMe, UNIT_EFFECT &rImp);
Character		*GetEffectCharacterObj(UNIT_EFFECT &rImp, Character &rMe);
int32			GetEffectPKRateCtr(UNIT_EFFECT &rImp);

extern EffectInterface	g_EffectInterface;
#endif

