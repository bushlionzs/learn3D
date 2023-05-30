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
	MONSTER_VALUE_GUID = 0,		//����guid
	MONSTER_VALUE_TYPE = 1,		//����
	MONSTER_VALUE_NAME = 2,		//����
	MONSTER_VALUE_POS = 3,		//λ��
	MONSTER_VALUE_SCRIPTID = 4,	//�ű�ID
	MONSTER_VALUE_GROUPID = 5,	//��ID
	MONSTER_VALUE_TEAMID = 6,	//����ID
	MONSTER_VALUE_BASEAI = 7,	//AI
	MONSTER_VALUE_AIFILE = 8,	//AI�ļ�
	MONSTER_VALUE_PATROLID = 9,	//Ѳ��·��
	MONSTER_VALUE_TRAND = 10,		//����ID
	MONSTER_VALUE_GRAND = 11,		//��ID
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
		GUID_t		m_GUID;			//����guid
		int32		m_Type;			//����
		char		m_Name[NPC_NAME_LEN + 1]; //����
		SFloatPos	m_Pos;			//λ��
		ScriptID_t	m_ScriptID;		//�ű�ID
		GroupID_t	m_GroupID;		//��ID
		TeamID_t	m_TeamID;		//����ID
		int32		m_BaseAI;		//AI
		int32		m_AIFile;		//AI�ļ�
		int32		m_PatrolID;		//Ѳ��·��
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
