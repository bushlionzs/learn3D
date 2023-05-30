/*$T MapServer/Server/Obj/Horse/HorseAttrCalculater.h GC 1.140 10/10/07 10:07:30 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef HorseAttrCalculater_h__
#define HorseAttrCalculater_h__

#include "TypeDefine.h"
#include "StructDB.h"
#include "HorseStruct.h"

class	Player;

class	HorseAttrCalculater
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	HorseAttrCalculater();
	~	HorseAttrCalculater();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetOwner(Player *pOwner)
	{
		m_pOwner = pOwner;
	}

	void		HeartBeat(uint32 uTime = 0);

	BOOL		AttachHorse(SHorseGuid horseGUID);
	BOOL		AttachHorse(_HORSE_DB *pPetDB);

	BOOL		Clear();

	BOOL		ResetCallUpHorse(BOOL bNewCallUp);

	BOOL		OnExpChange(uint32 iIncExp, BOOL bAccumulate = FALSE, BOOL bLvupMsg = TRUE, BOOL bRelateHappiness = TRUE/*是否用快乐度修正*/);

	void		SetChangeFade(int32 iMountID);

	void		DecHappiness(int32 iDecNum, BOOL bKillByMonster);

	static void	SkillRealization(_HORSE_DB *pPetDB, GameMap *pMap);

	void		SetHappiness(int32 iHappiness, BOOL bRefreshToClient);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	BOOL	DoLevelUpWhenExpChange(BOOL &bOverMaxLevel);

	BOOL	IsCanLevelup();

	uint32	GetRealExpByHappiness(uint32 iExp);
	uint32	GetCheckedValue(uint32 iValue);

	BOOL	IsActive();

	void	SetExp(uint32 iExp);

	void	LevelUp();

	int32	GetLevel(void);

	uint32	GetExp();

	void	HappinessHeartBeat(uint32 uTime);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	int32			m_nIndex;
	_HORSE_DB			*m_pPetDB;
	Player			*m_pOwner;
	_HORSE_ATTR_BACKUP	m_AttrBackUp;
	uint32			m_LastHeartBeatTick;
};
#endif
