/*$T MapServer/Server/AI/Behavior_Horse.h GC 1.140 10/10/07 10:07:19 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef AI_Horse_h__
#define AI_Horse_h__

#include "TypeDefine.h"
#include "gameobject/Behavior_Character.h"
#include "gameobject/Behavior_Const.h"

class	Horse;
class Behavior_Horse :
	public Behavior_Character
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { BODYSTAYTIME = 5000, };

	Behavior_Horse(void);
	virtual~Behavior_Horse(void);

	virtual BOOL Init(Character *pCharacter);
	virtual void Clear(void);

	virtual void Relive(BOOL bSpellRelive);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	Horse *GetCharacter(void) const
	{
		return((Horse *) Behavior_Character::GetCharacter());
	}

	OPT_RESULT PushCommand_UseSpell
		(
			ObjID_t idSpell,
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

	void	Go_Baby(const GLPos *paTargetPos);
	void	Attack_Baby(void);
	void	After_Die(void);
	BOOL	ProcessSpellInCache(BOOL IsAttackState = TRUE);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetSpellParamCache(const SLogicSpell_Param &rSpellParam)
	{
		m_SpellParamCache = rSpellParam;
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
};
#endif
