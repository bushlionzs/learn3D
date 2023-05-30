/*$T MapServer/Server/Obj/Horse/HorseManager.h GC 1.140 10/10/07 10:07:30 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef HorseManager_h__
#define HorseManager_h__

#include "TypeDefine.h"
#include "map/ObjectSingleManager.h"

class	Horse;
class HorseManager :
	public ObjectSingleManager
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	friend class	Horse;

	HorseManager(void);
	virtual		~HorseManager(void);

	void		Clear();

	virtual BOOL	HeartBeat(uint32 uTime = 0);

	Horse		*GetHorse(ObjID_t idObj);

	BOOL		LoadHorse(const char *pszFileName);

	BOOL		RemoveAllHorse(void);

	BOOL		RemoveHorse(ObjID_t idObj);

	BOOL		CreateHorse
			(
				int32		nDataID,
				GLPos	*pPos,
				ObjID_t		&rPetID,
				GUID_t		*pGUIDOwner,
				uint32		nOwnerCount
			);

	BOOL		CreateGUIDOfHorse(_HORSE_DB *pPetDB, ObjID_t idHuman, ObjID_t idPet);

	void		InitHorseGUID(SHorseGuid&guidPet, Player *pPlayer);

	BOOL		MakeCapturePetAttrib
			(
				_HORSE_DB *pPetDB,
				BOOL	bNeedLevelFluctuate = TRUE,
				BOOL	bReturnToChild = FALSE
			);

	BOOL		InitHorseDB(_HORSE_DB *pPetDB, int32 nDataID, BOOL bInitNewSkill = TRUE);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMap(GameMap *pMap)
	{
		m_pMap = pMap;
	}

	int32	GetPerceptionLimit(int32 iGeneration);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	void	CreateBHVClassOfHorse(_HORSE_DB &rPetDB);

	void	CreateClassOfHorse(_HORSE_DB &rPetDB, BOOL bNeedLevelFluctuate, BOOL bReturnToChild);

	void	CreateRemainPointOfHorse(_HORSE_DB &rPetDB);

	void	CreateSpellOfHorse(_HORSE_DB &rPetDB);

	void	CreateGrowRateOfHorse(_HORSE_DB &rPetDB);

	void	CreatePerceptionOfHorse(_HORSE_DB &rPetDB);

	void	AddHorseSpell(SHorseSkill *paSkillList, int32 &rSkillIndex);

	int32	GetRand(int32 iMin, int32 iMax);

	void	DeleteDeadHorse(int32 nRemoveCount, int32 *aNeedRemovePet);
	void	ClearRemoveArray(int32 *aNeedRemovePet);
	BOOL	InitHorseSkills(_HORSE_DB *pPetDB, _HORSE_ATTR *pPetAttr);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	GameMap	*m_pMap;
};
#endif
