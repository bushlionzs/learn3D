/*$T MapServer/Server/Item/GatherPointManager.h GC 1.140 10/10/07 10:07:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _GROWPOINT_MANAGER_H_
#define _GROWPOINT_MANAGER_H_
#include "TypeDefine.h"
#include "script/LuaSystem.h"

enum GATHER_POINT_TYPE { GATHER_POINT_TYPE_NORMAL = 0, GATHER_POINT_TYPE_MASS, GATHER_POINT_TYPE_NUM };

struct GATHER_POINT_GROUP_MAP_SETUP
{
	uint16	m_GatherPointType;
	uint16	m_GatherPointMaxCount;
	int32	m_GatherPointInterval;

	GATHER_POINT_GROUP_MAP_SETUP()
	{
		m_GatherPointType = -1;
		m_GatherPointMaxCount = 0;
		m_GatherPointInterval = 1000000;
	}
};

struct GATHER_POINT_GROUPMAP_SETTING
{
	uint16	m_GatherPointType;
	float	m_GatherPointX;
	float	m_GatherPointY;
	int32	m_GatherPointRandValue;
	uchar	m_GatherPointTypeEnum;
	BOOL	Used;

	int32	SeedNum;
	uint32	SeedInterval;
	int32	CurrSeedCount;
	BOOL	IsStartCount;
	uint32	CurrentElapse;
	uint32	LastUpdateTime;

	GATHER_POINT_GROUPMAP_SETTING()
	{
		memset(this, 0, sizeof(GATHER_POINT_GROUPMAP_SETTING));
		m_GatherPointTypeEnum = GATHER_POINT_TYPE_NORMAL;
	}
};

struct SGatherOwner
{
	SGatherOwner()
	{
		OwnerID = INVALID_ID;
		OwnerCount = 0;
	}
	ObjID_t OwnerID;
	int32	OwnerCount;
};

struct GATHER_POINT_LOAD
{
	int32				m_DataCount;
	GATHER_POINT_GROUPMAP_SETTING	*m_pData;
	int32				m_SetupCount;
	GATHER_POINT_GROUP_MAP_SETUP	*m_pSetup;

	GATHER_POINT_LOAD()
		:
	m_DataCount(0),
		m_pData(NULL),
		m_SetupCount(0),
		m_pSetup(NULL)
	{
	}
	~GATHER_POINT_LOAD()
	{
		m_DataCount = 0;
		KSafeDelete_ARRAY(m_pData);
		m_SetupCount = 0;
		KSafeDelete_ARRAY(m_pSetup);
	}
};


class	TypeGatherPointManager
{
public:
	TypeGatherPointManager();
	~TypeGatherPointManager();

	uint32				m_IntervalPerSeed;
	uint32				m_CurrentElapse;
	uint32				m_LastUpdateTime;
	int32				m_CurrentCount;
	int32				m_MaxApperaCount;
	int32				m_TypeCount;
	int32				m_AddOffSet;
	int32				m_TypeOffSet;
	uint16				m_GatherPointType;
	BOOL				m_bStartCount;
	BOOL				m_bEnable;
	BOOL				m_IsCreateAll;
	ScriptID_t			m_ScriptID;
	GATHER_POINT_GROUPMAP_SETTING	*m_pData;
	ObjID_t				*m_pObjID;

	inline void			SetCount(int32 count);
	inline int32		GetCount();
	inline void			IncCount();
	inline void			IncCurrentCount();
	inline void			DecCurrentCount();
	inline void			SetIntervalSeed(uint32 time);
	inline void			SetCurrentSeedCount(int32 num);
	inline int32		GetCurrentSeedCount(void);
	inline void			SetCurrentSeedElapse(uint32 time);
	inline void			SetCurrentElapse(uint32 time);
	inline void			SetEnable(BOOL flag);
	inline BOOL			GetEnable();
	inline void			AddData(GATHER_POINT_GROUPMAP_SETTING &RefData);
	inline BOOL			CreateGatherPointPos(float &x, float &y);
	inline BOOL			ReleaseGatherPointPos(float x, float y);
	inline void			IncCurrentSeedCount(int32 index);
	inline void			DecCurrentSeedCount(int32 index);
	inline uint16		GetGatherPointType();
	inline void			SetGatherPointType(uint16 gpType);
	inline void			SetIntervalTime(uint32 iInterval);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	inline BOOL	DoTicks(uint32 uTime);
	inline BOOL	DoSeedTicks(uint32 uTime);
	void		RandSort();
	void		SetObjID(ObjID_t id, float x, float y);
};

class	GameMap;
class	GatherPointManager
{
public:
	GatherPointManager();;
	~GatherPointManager();;

	void	Clear();
	BOOL	Load(char *strGatherPointDataFile, char *strGatherPointSetupFile);
	BOOL	Load(GATHER_POINT_LOAD *pGPLoad, char *strGatherPointDataFile, char *strGatherPointSetupFile);
	BOOL	Load(GATHER_POINT_LOAD *pGPLoad);

	void	SetScene(GameMap *pMap){m_pMap = pMap;}
	GameMap*GetMap(){return m_pMap;}

	BOOL	HeartBeat(uint32 uTime);
	BOOL	AddGatherPointOwner(ObjID_t OwnerID);
	BOOL	DelGatherPointOwner(ObjID_t OwnerID);
	BOOL	DecGatherPointTypeCount(int32 GatherPointType, float x, float y);

	LuaSystem *GetLuaSystem(){return m_pLuaSystem;}
	inline TypeGatherPointManager	*GetGpManagerByGatherPointType(int32 GatherPointType);

	int32	GetGatherPointCountByOwner(ObjID_t OwnerID);
	int32	CallLUAOpenBoxFunc(ScriptID_t FileID, ObjID_t SelfId, ObjID_t TargetId, MapID_t MapID);
	int32	CallLUARecycleFunc(ScriptID_t FileID, ObjID_t SelfId, ObjID_t TargetId, MapID_t MapID);
	int32	CallLUAProcOverFunc(ScriptID_t FileID, ObjID_t SelfId, ObjID_t TargetId, MapID_t MapID);
	BOOL	CallLUACreateFunc(ScriptID_t FileID, float x, float y, int32 iItemBoxType, MapID_t SceneId);

private:
	TypeGatherPointManager	*m_GatherPointMgr[MAX_MAP_GATHER_POINT_NUM];
	int32			m_GatherPointCount;
	int32			m_GatherPointTypeCount;
	GameMap*m_pMap;
	SGatherOwner	m_GPOwner[MAX_SCENE_GP_OWNER];
	int32			m_OwnerCount;
	LuaSystem * m_pLuaSystem;

	BOOL	GatherPointDataInit(char *szGatherPointDataFile);
	BOOL	GatherPointSetupInit(char *szGatherPointSetupFile);
};

#include "Item_GrowPointManager.inl"

#endif
