/*$T MapServer/Server/Obj/GuardManager.h GC 1.140 10/10/07 10:07:32 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __PETMANAGER_H__
#define __PETMANAGER_H__

#include "TypeDefine.h"
#include "server/map/ObjectSingleManager.h"
#include "StructPet.h"

class	Pet;
class GameMap;
class GuardManager :
	public ObjectSingleManager
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	friend class	Pet;

	GuardManager(void);
	virtual		~GuardManager(void);

	virtual BOOL	HeartBeat(uint32 uTime = 0);

	void		Clear();

	Pet		*GetPet(ObjID_t idObj);

	BOOL		LoadPet(const char *pszFileName);

	BOOL		RemoveAllPet(void);

	BOOL		RemovePet(ObjID_t idObj);

	BOOL		CreatePet(int32 nDataID, GLPos *pPos, ObjID_t &rPetID);

	BOOL		CreateGUIDOfPet(_HORSE_DB *pPetDB, ObjID_t idHuman, ObjID_t idPet);

	BOOL		MakeCapturePetAttrib
			(
				_HORSE_DB *pPetDB,
				BOOL	bNeedLevelFluctuate = TRUE,
				BOOL	bReturnToChild = FALSE
			);

	BOOL		InitPetDB(_HORSE_DB *pPetDB, int32 nDataID);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMap(GameMap *pMap)
	{
		m_pMap = pMap;
	}

	void			SetInitData(_MONSTER_PET_ATTR &oInit);
	const _MONSTER_PET_ATTR &GetInitData();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	void	CreateAITypeOfPet(_HORSE_DB &rPetDB);

	void	CreateTypeOfPet(_HORSE_DB &rPetDB, BOOL bNeedLevelFluctuate, BOOL bReturnToChild);

	void	CreateRemainPointOfHorse(_HORSE_DB &rPetDB);

	void	CreateSkillOfPet(_HORSE_DB &rPetDB);

	void	CreateGrowRateOfPet(_HORSE_DB &rPetDB);

	void	CreatePerceptionOfPet(_HORSE_DB &rPetDB);

	void	AddPetSkill(SHorseSkill *paSkillList, int32 &rSkillIndex);

	int32	GetRand(int32 iMin, int32 iMax);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	GameMap*m_pMap;
	_MONSTER_PET_ATTR	m_oInit;
};
#endif
