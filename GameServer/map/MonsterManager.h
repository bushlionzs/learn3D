/*$T MapServer/Server/Obj/MonsterObjectManager.h GC 1.140 10/10/07 10:07:32 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __MONSTERMANAGER_H__
#define __MONSTERMANAGER_H__

#include "TypeDefine.h"
#include "ObjectSingleManager.h"
#include "gameobject/InitMonsterVisitor.h"

class	Monster;

struct _MONSTER_INIT;

enum eMONSTER_VALUE
{
	MONSTER_VALUE_GUID = 0,		//怪物guid
	MONSTER_VALUE_TYPE = 1,		//类型
	MONSTER_VALUE_NAME = 2,		//名字
	MONSTER_VALUE_POS = 3,		//位置
	MONSTER_VALUE_SCRIPTID = 4,	//脚本ID
	MONSTER_VALUE_GROUPID = 5,	//组ID
	MONSTER_VALUE_TEAMID = 6,	//队伍ID
	MONSTER_VALUE_BASEAI = 7,	//AI
	MONSTER_VALUE_AIFILE = 8,	//AI文件
	MONSTER_VALUE_PATROLID = 9,	//巡逻路径
	MONSTER_VALUE_TRAND = 10,		//队伍ID
	MONSTER_VALUE_GRAND = 11,		//组ID
};

struct SFloatPos
{
	float	m_fX;
	float	m_fZ;
};

struct SMonsterAttrValue
{
	union
	{
		GUID_t		m_GUID;			//怪物guid
		int32		m_Type;			//类型
		char		m_Name[NPC_NAME_LEN + 1]; //名字
		SFloatPos	m_Pos;			//位置
		ScriptID_t	m_ScriptID;		//脚本ID
		GroupID_t	m_GroupID;		//组ID
		TeamID_t	m_TeamID;		//队伍ID
		int32		m_BaseAI;		//AI
		int32		m_AIFile;		//AI文件
		int32		m_PatrolID;		//巡逻路径
	};
};

struct _INIT_MONSTER_OPT
{
	int32			m_SelectType;
	SMonsterAttrValue	m_Value;
	int32			m_DataDef;
	int32			m_MaxLeft;
};
struct _INIT_MONSTER_DATA
{
	int32			m_DataType;
	int32			m_DataCount;
	SMonsterAttrValue* m_pDataValue;

	_INIT_MONSTER_DATA()
	{
		m_DataType = 0;
		m_DataCount = 0;
		m_pDataValue = NULL;
	};
	~_INIT_MONSTER_DATA()
	{
		KSafeDelete_ARRAY(m_pDataValue);
	};
};

struct _INIT_MONSTER_OBJECT;
struct SMonsterFile
{
	char			m_szFileName[_MAX_PATH];
	_INIT_MONSTER_OBJECT* m_pInit;
	BOOL* m_pAllocFlag;
	int32			m_Count;
	_INIT_MONSTER_OBJECT* m_pInitUsing;
	int32			m_CountUsing;
	int32			m_OperateCount;
	_INIT_MONSTER_OPT* m_pOperate;
	int32			m_DataCount;
	_INIT_MONSTER_DATA* m_pData;

	SMonsterFile()
	{
		memset(m_szFileName, 0, _MAX_PATH);
		m_pInit = NULL;
		m_pAllocFlag = NULL;
		m_Count = 0;
		m_pInitUsing = NULL;
		m_CountUsing = 0;

		m_OperateCount = 0;
		m_pOperate = NULL;

		m_DataCount = 0;
		m_pData = NULL;
	};
	~SMonsterFile();

	void	Clear();

	BOOL	LoadData();
protected:
	BOOL	LoadData_i(int32 iIndex);
};

class MonsterObjectManager :
	public ObjectSingleManager
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	MonsterObjectManager(void);
	virtual		~MonsterObjectManager(void);

	Monster		*GetMonster(ObjID_t idObj);

	virtual BOOL	HeartBeat(uint32_t uTime = 0);

	ObjID_t		FindMonsterByGUID(GUID_t guid);

	BOOL		InitMonsterData(_MONSTER_INIT *pInit, int32 nDataID);


/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	BOOL	LoadMonster(const char *pszFileName, MapID_t MapID);
	BOOL	LoadMonsterTab(const char *pszFileName, MapID_t MapID);
	BOOL	RemoveAllMonster(void);

private:
	InitMonsterVisitor	m_MonsterVisitor;
};
#endif
