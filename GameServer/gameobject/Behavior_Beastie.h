#ifndef _AI_BEASTIE_H_
#define _AI_BEASTIE_H_
#include "TypeDefine.h"
#include "Behavior_Character.h"

class	Beastie;
class Behavior_Beastie :
	public Behavior_Character
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Behavior_Beastie(void);
	virtual ~Behavior_Beastie(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	void		Reset(void);
	virtual BOOL	Init(Character *pCharacter);
	virtual void	Clear(void);
	virtual void	Relive(BOOL bSkillRelive);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	Beastie *GetCharacter(void) const
	{
		return((Beastie *) Behavior_Character::GetCharacter());
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

	void		ToRandMove(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	CTinyTimer	m_RandMoveTimer;
	CTinyTimer	m_IdleTimer;
};
#endif
