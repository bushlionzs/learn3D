/*$T MapServer/Server/AI/Behavior_Pet.h GC 1.140 10/10/07 10:07:19 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __PETAI_H__
#define __PETAI_H__

#include "TypeDefine.h"
#include "Behavior_Character.h"
#include "Behavior_Const.h"

class	Pet;
class Behavior_Pet :
	public Behavior_Character
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { BODYSTAYTIME = 5000, };

	Behavior_Pet(void);
	virtual~Behavior_Pet(void);

	virtual BOOL Init(Character *pCharacter);
	virtual void Clear(void);

	virtual void Relive(BOOL bSkillRelive);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	Pet *GetCharacter(void) const
	{
		return((Pet *) Behavior_Character::GetCharacter());
	}

	OPT_RESULT PushCommand_UseSpell
		(
			ObjID_t idSkill,
			ObjID_t idTarget,
			float	fTargetX,
			float	fTargetZ,
			float	fDir,
			GUID_t	guidTarget
		);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	virtual void	Event_OnDie(Object *pKiller = NULL);

	virtual void	Idle_Logic(uint32 uTime);
	virtual void	Dead_Logic(uint32 uTime);
	virtual void	Combat_Logic(uint32 uTime);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	struct SLogicSpell_Param
	{
		SpellID_t	idSpell;
		ObjID_t		idTarget;
		GLPos	TargetPos;
		float		fDir;
		GUID_t		guidTarget;

		SLogicSpell_Param()
		{
			Clear();
		}

		/*
		 =======================================================================================================
		 =======================================================================================================
		 */
		void Clear()
		{
			idSpell = INVALID_ID;
			idTarget = INVALID_ID;
			TargetPos.Clear();
			fDir = 0.f;
			guidTarget = INVALID_ID;
		}

		/*
		 =======================================================================================================
		 =======================================================================================================
		 */
		BOOL IsValid() const
		{
			if(idSpell != INVALID_ID)
			{
				return TRUE;
			}

			return FALSE;
		}
	};

	void	Baby_Go(const GLPos *paTargetPos);

	void	GetStandPos
		(
			Character	*pChar,
			int32		iIndex,
			const GLPos *paTargetPos,
			float		fDistanceRefix,
			GLPos	&oOutPos
		);

	void	BabyToAttack(void);
	void	After_Die(void);

	BOOL	ProcessSpellInCache(BOOL IsAttackState = TRUE);
	BOOL	ToApproachTar(Object *pTarObj, ObjID_t idSpell);
	BOOL	GetBestPos(GLPos &Tar, Object *pTarObj, ObjID_t idSpell);
	void	ForceChangeState(_PET_CTRL_STATE eState);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsForceKill() const
	{
		return m_bForceKill;
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetSpellParamCache(const SLogicSpell_Param &rSkillParam)
	{
		m_SpellParamCache = rSkillParam;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const SLogicSpell_Param &GetSpellParamCache(void) const
	{
		return m_SpellParamCache;
	}

	void	ChangeMoveMode(void);
	float	CalcDistSqrOfToOwner(void);
	BOOL	ApproachToOwner(void);
	void	ToRandMove(void);
	BOOL	IsCombatBeOver(void);

	float	GetGoodRefix(float iBase, float iRefix);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	SLogicSpell_Param	m_SpellParamCache;
	CTinyTimer		m_RandMoveTimer;
	CTinyTimer		m_BodyTimer;
	CTinyTimer		m_ScanImpactOfOwnerTimer;
	int32			m_nDelayTime;
	BOOL			m_bCallupFlag;
	BOOL			m_bForceIdle;
	BOOL			m_bForceKill;
};
#endif
