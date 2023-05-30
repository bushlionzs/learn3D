/*$T MapServer/Server/Obj/Horse/HorseStruct.h GC 1.140 10/10/07 10:07:30 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef HorseStruct_h__
#define HorseStruct_h__

#include "gameobject/Character.h"

struct _OBJ_HORSE_INIT :
	public _INIT_PLAYERACTER_OBJECT
{
	GUID_t	m_GUID;
	_HORSE_DB m_PetDB;
	uint32	m_nOwnerCount;
	GUID_t	m_aOwnerGUID[MAX_TEAM_MEMBER];
	int32	m_RespawnTime;
	_OBJ_HORSE_INIT (void)
	{
		m_GUID = INVALID_GUID;
		m_PetDB.Clear();
		m_nOwnerCount = 0;
		for(uint32 n = 0; n < MAX_TEAM_MEMBER; n++) m_aOwnerGUID[n] = INVALID_GUID;
		m_RespawnTime = -1;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void Clear(void)
	{
		m_GUID = INVALID_GUID;
		m_PetDB.Clear();
		m_nOwnerCount = 0;
		m_RespawnTime = -1;
		for(uint32 n = 0; n < MAX_TEAM_MEMBER; n++) m_aOwnerGUID[n] = INVALID_GUID;
		_INIT_PLAYERACTER_OBJECT::Clear();
	}
};

struct _HORSE_ATTR_BACKUP
{
public:
	BOOL		m_bNameModified;
	BOOL		m_bTitleModified;

	float		m_MoveSpeed;
	SCampData	m_CampData;
	ObjID_t		m_nOwnerID;
	int32		m_nAIType;
	int32		m_Level;

	int32		m_nDataID;
	int32		m_nModelID;
	int32		m_nMountID;

	SHorseGuid	m_GUID;
	uchar		m_byGeneration;
	uchar		m_byHappiness;

	uint32		m_nExp;

	int32		m_iStrengthPerception;
	int32		m_iSmartnessPerception;
	int32		m_iMindPerception;
	int32		m_iConstitutionPerception;

	int32		m_iPullulationRate;

	int32		m_nRemainPoint;

	int32		m_iStrength;
	int32		m_iSmartness;
	int32		m_iMind;
	int32		m_iConstitution;

	int32		m_nAtt_Near;
	int32		m_nAtt_Far;
	int32		m_nAtt_Magic;
	int32		m_nDef_Near;
	int32		m_nDef_Far;
	int32		m_nDef_Magic;

	int32		m_nHit;
	int32		m_nMiss;
	int32		m_nCritical;
public:
	_HORSE_ATTR_BACKUP (void);

	void	Clear(void);
};
#endif
