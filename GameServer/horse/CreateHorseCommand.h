/*$T MapServer/Server/Obj/Horse/CreateHorseCommand.h GC 1.140 10/10/07 10:07:29 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef CreateHorseCommand_h__
#define CreateHorseCommand_h__

#include "HorseManipulateCommand.h"

class Horse_CreateHorseCommand :
	public HorseManipulateCommand
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Horse_CreateHorseCommand();
	~	Horse_CreateHorseCommand();

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual int32 GetManipulateType()
	{
		return MANIPULATE_CREATEHORSE;
	}

	virtual void	ExecutManipulate(_HorseManipulate *pMamipulate, Player *pPlayer);
	virtual BOOL	IsCanManipulate(_HorseManipulate *pMamipulate, Player *pPlayer);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	void	AddPassiveSkillToOnwerOpen(Player *pPlayer, _HORSE_DB *pPetDB);	//Add by Huangqinqi

private:
	void	AddPassiveSkillToOnwer(Player *pPlayer, _HORSE_DB *pPetDB);

	void	StartPassiveSkill(SpellID_t iSkillID, Player *pPlayer, int32 iSkillLevel, int32 iIndex);
};
#endif
