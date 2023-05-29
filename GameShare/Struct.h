#ifndef __GAMESTRUCT_H__
#define __GAMESTRUCT_H__

#include "TypeDefine.h"
#include "Define.h"
#include "Debug.h"
#include "Glpos.h"


struct SMapPos
{
	Coord_t m_nX;
	Coord_t m_nZ;

	SMapPos (void)
	:
	m_nX(0),
	m_nZ(0)
	{
	}
	SMapPos(Coord_t nX, Coord_t nZ)
	:
	m_nX(nX),
	m_nZ(nZ)
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_nX = 0;
		m_nX = 0;
	};
};

struct SEffect
{
	BOOL	m_bActive;
	int32	m_Value;
	int32	m_Time;

	SEffect()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_bActive = FALSE;
		m_Value = 0;
		m_Time = 0;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	BOOL IsActive()
	{
		return m_bActive;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetActive(BOOL bActive)
	{
		m_bActive = bActive;
	};
};

struct SMonsterCreaterInit
{
	char		m_FileName[_MAX_PATH];
	GLPos	m_Position;
};

#define DEFAULT_ITEMBOX_RECYCLE_TIME	300000

struct SEquipList
{
	GUID_t	m_GUID;
	uint32	m_uParam1;
	uint32	m_uParam2;
};
#define EQUIP_PLAYER_FIXNUM	(8)

struct SEmbellishList
{
	GUID_t	m_GUID;
	uint32	m_uParam1;
	uint32	m_uParam2;
};
#define EMBELLISH_PLAYER_FIXNUM (6)

struct SPlayerOwn
{
	GUID_t	m_nGUID;
	char	m_szName[MAX_CHARACTER_NAME];

	Coord_t m_nX;
	Coord_t m_nZ;

	float	m_fDir;

	SPlayerOwn()
	{
		m_nGUID = INVALID_ID;
		memset(m_szName, 0, MAX_CHARACTER_NAME);
		m_nX = 0;
		m_nZ = 0;
		m_fDir = 0.0;
	};
};

struct SPlayerS
{
	GUID_t	m_nGUID;
	char	m_szName[MAX_CHARACTER_NAME];

	Coord_t m_nX;
	Coord_t m_nZ;

	float	m_fDir;

	SPlayerS()
	{
		m_nGUID = INVALID_ID;
		memset(m_szName, 0, MAX_CHARACTER_NAME);
		m_nX = 0;
		m_nZ = 0;
		m_fDir = 0.0;
	};
};

struct VRECT
{
	int32	nStartx;
	int32	nStartz;
	int32	nEndx;
	int32	nEndz;

	VRECT()
	{
		nStartx = 0;
		nStartz = 0;
		nEndx = 0;
		nEndz = 0;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	BOOL IsContinue(int32 x, int32 z) const
	{
		if(x < nStartx || x > nEndx || z < nStartz || z > nEndz)
			return FALSE;
		else
			return TRUE;
	}
};

struct _PROPERTY_LEVEL1
{
	int32	m_pAttr[CPROPERTY_LEVEL1_NUMBER];

	_PROPERTY_LEVEL1()
	{
		Clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 Get(int32 iAttr) const
	{
		KCheck(iAttr >= 0 && iAttr < CPROPERTY_LEVEL1_NUMBER);
		return m_pAttr[iAttr];
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Set(int32 iAttr, int32 iValue)
	{
		KCheck(iAttr >= 0 && iAttr < CPROPERTY_LEVEL1_NUMBER);
		m_pAttr[iAttr] = iValue;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(m_pAttr, 0, sizeof(int32) * CPROPERTY_LEVEL1_NUMBER);
	};
};

struct _PROPERTY_LEVEL2
{
	int32	m_pAttr[CPROPERTY_LEVEL2_NUMBER];

	_PROPERTY_LEVEL2()
	{
		memset(m_pAttr, 0, sizeof(int32) * CPROPERTY_LEVEL2_NUMBER);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 Get(int32 iAttr)
	{
		KCheck(iAttr >= 0 && iAttr < CPROPERTY_LEVEL2_NUMBER);
		return m_pAttr[iAttr];
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Set(int32 iAttr, int32 iValue)
	{
		KCheck(iAttr >= 0 && iAttr < CPROPERTY_LEVEL2_NUMBER);
		m_pAttr[iAttr] = iValue;
	};
};

struct SPlayerInherenceBalance
{
	int32	m_pBalance[CPROPERTY_LEVEL4_BALANCE_NUMBER];

	SPlayerInherenceBalance()
	{
		Clear();	
	}

	void Clear()
	{
		memset(m_pBalance, 0, sizeof(int32) * CPROPERTY_LEVEL4_BALANCE_NUMBER);
	}
	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 Get(int32 iBalanceIndex)
	{
		KCheck(iBalanceIndex >= 0 && iBalanceIndex < CPROPERTY_LEVEL4_BALANCE_NUMBER);
		return m_pBalance[iBalanceIndex];
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Set(int32 iBalanceIndex, int32 iValue)
	{
		KCheck(iBalanceIndex >= 0 && iBalanceIndex < CPROPERTY_LEVEL4_BALANCE_NUMBER);
		m_pBalance[iBalanceIndex] = iValue;
	};
};

struct SPlayerInherenceZhanJing
{
	int32	m_pZhanGong_Level[PROFESSION_NUMBER];
	int32	m_pZhanGong_Point[PROFESSION_NUMBER];
	int32	m_nZhanGong_Total_Coefficient;
	int32	m_pZhanGong_Coefficient[PROFESSION_NUMBER];

	int32	m_nZhanFang_Total_Point;
	int32	m_pZhanFang_Level[PROFESSION_NUMBER];

	SPlayerInherenceZhanJing()
	{
		Clear();	
	}

	void Clear()
	{
		memset(m_pZhanGong_Level, 0, sizeof(int32) * PROFESSION_NUMBER);
		memset(m_pZhanGong_Point, 0, sizeof(int32) * PROFESSION_NUMBER);
		memset(m_pZhanGong_Coefficient, 0, sizeof(int32) * PROFESSION_NUMBER);
		memset(m_pZhanFang_Level, 0, sizeof(int32) * PROFESSION_NUMBER);

		m_nZhanGong_Total_Coefficient = 0;
		m_nZhanFang_Total_Point = 0;
	}
};

#define ID2STR(str, strid, strsize) \
	char	str[strsize]; \
	memset(str, 0, strsize); \
	sprintf(str, "#%d", strid);

#define STR2ID(str, strid) \
	int32	 strid = atoi((char *) (str + 1));

class				SendStream;
class					RecieveStream;

struct STitle
{
	enum { NO_TITLE = -1, GUOJIA_TITLE = 0, BANGPAI_TITLE, WANFA_TITLE, MOOD_TITLE, MAX_NUM_TITLE, };

	enum { MARRY_TITLE_ID = 4, PRENTICE_TITLE_ID = 5, };

	struct TITLE_TABLE_INFO
	{
		uchar	m_TitleID;
		int32	m_iSuitID;
		int32	m_iTitleType;
		int32	m_iBuffID;
		uint32	m_uTime;
		char	m_szMaleTitle[MAX_CHARACTER_TITLE];
		char	m_szFemaleTitle[MAX_CHARACTER_TITLE];

		TITLE_TABLE_INFO()
		{
			m_TitleID = INVALID_TITLE_ID;
			m_iSuitID = INVALID_ID;
			m_iTitleType = INVALID_ID;
			m_iBuffID = INVALID_ID;
			m_uTime = 0;
			memset(m_szMaleTitle, 0, MAX_CHARACTER_TITLE);
			memset(m_szFemaleTitle, 0, MAX_CHARACTER_TITLE);
		}
	};

	struct TITLE_INFO
	{
		uchar	m_TitleID;
		uint32	m_uTime;

		TITLE_INFO()
		{
			m_TitleID = INVALID_TITLE_ID;
			m_uTime = 0;
		}

		/*
		 =======================================================================================================
		 =======================================================================================================
		 */
		int32 GetSize() const
		{
			return sizeof(m_TitleID) + sizeof(m_uTime);
		}

		void	Read(RecieveStream &iStream);
		void	Write(SendStream &oStream) const;
	};

	struct TITLE_COMBINATION
	{
		int32	m_iGroupID;
		int32	m_comTitleID;
		int32	m_arPart[MAX_TITLE_COMBINATION];

		TITLE_COMBINATION()
		{
			m_comTitleID = INVALID_TITLE_ID;
			memset(m_arPart, 0, sizeof(int32) * MAX_TITLE_COMBINATION);
		}
	};
public:
	uchar		m_CurCountryTitle;
	uchar		m_CurGuildTitle;
	uchar		m_CurNormalTitle;

	TITLE_INFO	m_TitleArray[MAX_TITLE_SIZE];
	uchar		m_TitleArraySize;

	char		m_szCurCountryTitle[MAX_CHARACTER_TITLE];
	char		m_szCurGuildTitle[MAX_CHARACTER_TITLE];
	char		m_szCurNormalTitle[MAX_CHARACTER_TITLE];

	char		m_szOfficialTitleName[MAX_CHARACTER_TITLE];

    //! 头顶称号变化标记，用来在角色离线时获得称号（比如帮会参加世界杯获得前3名），上线后设置此标记，MapServer通过它执行Title完整逻辑
    uint8       m_Update;

	STitle()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_CurCountryTitle = INVALID_TITLE_ID;
		m_CurGuildTitle = INVALID_TITLE_ID;
		m_CurNormalTitle = INVALID_TITLE_ID;
		m_TitleArraySize = 0;
        m_Update = FALSE;

		memset((void *) m_szOfficialTitleName, 0, MAX_CHARACTER_TITLE);
		memset((void *) m_szCurCountryTitle, 0, MAX_CHARACTER_TITLE);
		memset((void *) m_szCurGuildTitle, 0, MAX_CHARACTER_TITLE);
		memset((void *) m_szCurNormalTitle, 0, MAX_CHARACTER_TITLE);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetSize() const
	{
		return sizeof(m_CurCountryTitle) +
			sizeof(m_CurGuildTitle) +
			sizeof(m_CurNormalTitle) +
			m_TitleArray->GetSize() *
			MAX_TITLE_SIZE +
			sizeof(m_TitleArraySize) +
			sizeof(m_szCurCountryTitle) +
			sizeof(m_szCurGuildTitle) +
			sizeof(m_szCurNormalTitle) +
			sizeof(m_szOfficialTitleName) + 
            sizeof( m_Update);
	}

	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};

struct ITEM_PICK_CTL
{
	ObjID_t		OwnerID;
	uint32		uBetTime;
	uchar		uMaxBetPoint;
	ePICK_RULER_TYPE	ePickRuler;

	ITEM_PICK_CTL()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		OwnerID = INVALID_ID;
		ePickRuler = IPR_FREE_PICK;
		uBetTime = 0;
		uMaxBetPoint = 0;
	}
};

typedef ITEM_PICK_CTL	IPC;

#define MAX_PICKER_COUNT	6

struct TEAM_PICKER
{
	uint32	m_uCount;
	ObjID_t m_PickerID[MAX_PICKER_COUNT];

	TEAM_PICKER()
	{
		memset(this, 0, sizeof(TEAM_PICKER));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddPicker(ObjID_t id)
	{
		for(uint32 nIndex = 0; nIndex < m_uCount; nIndex++)
		{
			if(m_PickerID[nIndex] == id) return;
		}

		m_PickerID[m_uCount] = id;
		m_uCount++;
	}
};

#define MAX_DAMAGE_REC_COUNT	10

struct SDamageRecord
{
	GUID_t		m_Killer;
	ObjID_t		m_KillerObjID;
	TeamID_t	m_TeamID;
	uint32		m_uDamage;

	SDamageRecord()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_Killer = INVALID_ID;
		m_KillerObjID = INVALID_ID;
		m_TeamID = INVALID_ID;
		m_uDamage = 0;
	}
};

struct SDamageMemList
{
	uint32		m_uCount;
	SDamageRecord	m_DamageRec[MAX_DAMAGE_REC_COUNT];

	SDamageMemList()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_uCount = 0;
		for(int32 i = 0; i < MAX_DAMAGE_REC_COUNT; i++) m_DamageRec[i].Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddMember(GUID_t KillerID, ObjID_t KillerObjID, TeamID_t KillerTeam, uint32 Damage)
	{
		if(KillerTeam != INVALID_ID)
		{
			m_DamageRec[m_uCount].m_Killer = KillerID;
			m_DamageRec[m_uCount].m_KillerObjID = KillerObjID;
			m_DamageRec[m_uCount].m_TeamID = KillerTeam;
			m_DamageRec[m_uCount].m_uDamage = Damage;
		}
		else
		{
			m_DamageRec[m_uCount].m_Killer = KillerID;
			m_DamageRec[m_uCount].m_KillerObjID = KillerObjID;
			m_DamageRec[m_uCount].m_TeamID = INVALID_ID;
			m_DamageRec[m_uCount].m_uDamage = Damage;
		}

		m_uCount++;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddMember(SDamageRecord &dRec)
	{
		if(dRec.m_TeamID != INVALID_ID)
		{
			m_DamageRec[m_uCount].m_Killer = dRec.m_Killer;
			m_DamageRec[m_uCount].m_TeamID = dRec.m_TeamID;
			m_DamageRec[m_uCount].m_uDamage = dRec.m_uDamage;
		}
		else
		{
			m_DamageRec[m_uCount].m_Killer = dRec.m_Killer;
			m_DamageRec[m_uCount].m_TeamID = INVALID_ID;
			m_DamageRec[m_uCount].m_uDamage = dRec.m_uDamage;
		}

		m_uCount++;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SDamageRecord *FindMember(GUID_t KillerID)
	{
		for(uint32 i = 0; i < m_uCount; i++)
		{
			if(m_DamageRec[i].m_Killer == KillerID && KillerID != INVALID_ID)
			{
				return &m_DamageRec[i];
			}
		}

		return NULL;
	}
};

struct _PLAYER_ABILITY
{
	uint32	m_Level;
	uint32	m_Exp;

	uint32 GetSize() const
	{
		return sizeof(m_Level) + sizeof(m_Exp);
	}
};

#define MAX_MONSTER_DROP_TASK_ITEM	5
#define MAX_MONSTER_KILLER_NUM		18

struct PLAYER_OWNER_DROP_LIST
{
	ObjID_t HumanID;
	uint32	DropItemIndex[MAX_MONSTER_DROP_TASK_ITEM];
	uint32	DropCount;

	PLAYER_OWNER_DROP_LIST()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddItem(uint32 ItemIndex)
	{
		KCheck(DropCount < MAX_MONSTER_DROP_TASK_ITEM);
		DropItemIndex[DropCount] = ItemIndex;
		DropCount++;
	}
};

struct OWNERCHARACTER
{
	GUID_t	m_Guid;
	ObjID_t m_ObjID;
};

struct SMonsterOwnerList
{
	OWNERCHARACTER	OwnerDropList[MAX_TEAM_MEMBER];
	uint32		OwnerCount;
	uchar		OwnerLock;

	SMonsterOwnerList()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void LockOwner()
	{
		OwnerLock = 1;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void UnLockOwner()
	{
		OwnerLock = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsLockOwner()
	{
		return OwnerLock == 1;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddOwner(GUID_t HumanID, ObjID_t HumanObjID)
	{
		if(OwnerCount == MAX_TEAM_MEMBER) return;
		if(OwnerLock) return;

		/*~~~~~~~~~~~~~~~~~~~*/
		BOOL	bAlive = FALSE;
		/*~~~~~~~~~~~~~~~~~~~*/

		for(uint32 i = 0; i < OwnerCount; ++i)
		{
			if(OwnerDropList[i].m_Guid == HumanID)
			{
				bAlive = TRUE;
			}
		}

		if(!bAlive)
		{
			OwnerDropList[OwnerCount].m_Guid = HumanID;
			OwnerDropList[OwnerCount].m_ObjID = HumanObjID;
			OwnerCount++;
		}
	}
};

struct SMarriageInfo
{
	GUID_t	m_SpouseGUID;
	Time_t	m_uMarriageTime;
	uchar	m_bHaveWedding;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_SpouseGUID = INVALID_ID;
		m_uMarriageTime = 0;
		m_bHaveWedding = FALSE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init(const SMarriageInfo *pCopy)
	{
		Clear();
		m_SpouseGUID = pCopy->m_SpouseGUID;
		m_uMarriageTime = pCopy->m_uMarriageTime;
		m_bHaveWedding = pCopy->m_bHaveWedding;
	}

	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};

struct SPrenticeInfo
{
	struct Prentice
	{
		GUID_t	m_nGuid;
		uint32	m_nOfflineTime;
	};
	Time_t		m_DeleteRelationTime;
	uint16		m_uTitleForMaxCount;
	Prentice	m_aPrentice[MAX_PRENTICE_COUNT];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	BOOL IsHavePrentice() const
	{
		for(int32 i = 0; i < MAX_PRENTICE_COUNT; ++i)
		{
			if(INVALID_GUID != m_aPrentice[i].m_nGuid) return TRUE;
		}

		return FALSE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint16 GetPrenticeNum() const
	{
		uint16	uNum = 0;
		for(int32 i = 0; i < MAX_PRENTICE_COUNT; ++i)
		{
			if(INVALID_GUID != m_aPrentice[i].m_nGuid) ++uNum;
		}

		return uNum;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_DeleteRelationTime = 0;
		m_uTitleForMaxCount = MASTER_TITLE_INVALID;
		for(int32 i = 0; i < MAX_PRENTICE_COUNT; ++i)
		{
			m_aPrentice[i].m_nGuid = INVALID_ID;
			m_aPrentice[i].m_nOfflineTime = 0;
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init(const SPrenticeInfo *pCopy)
	{
		Clear();
		m_DeleteRelationTime = pCopy->m_DeleteRelationTime;
		m_uTitleForMaxCount = pCopy->m_uTitleForMaxCount;
		for(int32 i = 0; i < MAX_PRENTICE_COUNT; ++i)
		{
			m_aPrentice[i].m_nGuid = pCopy->m_aPrentice[i].m_nGuid;
			m_aPrentice[i].m_nOfflineTime = pCopy->m_aPrentice[i].m_nOfflineTime;
		}
	}

	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};

struct SMasterInfo
{
	GUID_t	m_MasterGUID;
	Time_t	m_DeleteRelationTime;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_MasterGUID = INVALID_ID;
		m_DeleteRelationTime = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init(const SMasterInfo *pCopy)
	{
		Clear();
		m_MasterGUID = pCopy->m_MasterGUID;
		m_DeleteRelationTime = pCopy->m_DeleteRelationTime;
	}

	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};

struct SMail
{
	GUID_t	m_GUID;								// 邮件发送者GUID
	uchar	m_SourSize;							// 邮件发送者名字长度
	char	m_szSourName[MAX_CHARACTER_NAME];	// 邮件发送者名字

	int32	m_nPortrait;						// 发送者头像ID

	uchar	m_DestSize;							// 邮件接收者名字长度
	char	m_szDestName[MAX_CHARACTER_NAME];	// 邮件接收者名字

	uint16	m_ContexSize;						// 邮件内容长度
	char	m_szContex[MAX_MAIL_CONTEX];		// 邮件内容

	uint32	m_uFlag;							// 邮件类型
	uint32	m_uCreateTime;						// 邮件创建时间，GetCTime类型

	uint32	m_uParam0;							// 附加参数，脚本邮件使用
	uint32	m_uParam1;
	uint32	m_uParam2;
	uint32	m_uParam3;

    static int32 GetSize()
    {
        return ( sizeof( GUID_t) + sizeof( uchar) * 2 + sizeof( int32) + sizeof(uint32) + sizeof( uint16) + sizeof( uint32) * 5 + MAX_CHARACTER_NAME * 2 + MAX_MAIL_CONTEX);
    }

	SMail()
	{
		Clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_GUID = INVALID_INDEX;
		m_SourSize = 0;
		memset(m_szSourName, 0, sizeof(char) * MAX_CHARACTER_NAME);

		m_nPortrait = -1;

		m_DestSize = 0;
		memset(m_szDestName, 0, sizeof(char) * MAX_CHARACTER_NAME);

		m_ContexSize = 0;
		memset(m_szContex, 0, sizeof(char) * MAX_MAIL_CONTEX);

		m_uFlag = MAIL_TYPE_NORMAL;
		m_uCreateTime = 0;

		m_uParam0 = 0;
		m_uParam1 = 0;
		m_uParam2 = 0;
		m_uParam3 = 0;
	};
	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

#define MAX_MAIL_SIZE	30
struct SMailList
{
	SMail	m_aMail[MAX_MAIL_SIZE];
	uchar	m_Count;
	uchar	m_TotalLeft;

	SMailList()
	{
		Clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_Count = 0;
		m_TotalLeft = 0;
		for(int32 i = 0; i < MAX_MAIL_SIZE; i++)
		{
			m_aMail[i].Clear();
		}
	};
	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct SETGAMEOPEN
{
	enum { struct_size = sizeof (int32) +sizeof (int32) };

	int32 m_nGameId;
	int32 m_nValue;

	SETGAMEOPEN()
	{
		Clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_nGameId = 0;
		m_nValue = 0;
	};
	uint32	GetSize() const;
	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
	void	Init(const SETGAMEOPEN *pCopy);
};

#define MAX_RECEIVER	100
struct SBatchMail
{
	GUID_t	m_GUID;

	uchar	m_SourSize;
	char	m_szSourName[MAX_CHARACTER_NAME];

	uchar	m_ReceiverCount;
	struct
	{
		uchar	m_DestSize;
		char	m_szDestName[MAX_CHARACTER_NAME];
	} m_Receivers[MAX_RECEIVER];

	uint16	m_ContentSize;
	char	m_szContent[MAX_MAIL_CONTEX];

	uchar	m_uFlag;
	Time_t	m_uCreateTime;

	SBatchMail()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	GUID_t GetGUID()
	{
		return m_GUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetGUID(GUID_t guid)
	{
		m_GUID = guid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const char *GetSourName()
	{
		return m_szSourName;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetSourName(const char *szName)
	{
		strncpy(m_szSourName, szName, MAX_CHARACTER_NAME - 1);
		m_SourSize = (uchar) strlen(m_szSourName);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uchar GetReceiverCount()
	{
		return m_ReceiverCount;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const char *GetDestName(uchar idx)
	{
		if(idx >= m_ReceiverCount)
		{
			KCheck(idx);
			return NULL;
		}

		return m_Receivers[idx].m_szDestName;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddDestName(const char *szName)
	{
		strncpy(m_Receivers[m_ReceiverCount].m_szDestName, szName, MAX_CHARACTER_NAME - 1);
		m_Receivers[m_ReceiverCount].m_DestSize = (uchar) strlen(m_Receivers[m_ReceiverCount].m_szDestName);
		++m_ReceiverCount;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const char *GetMailContent()
	{
		return m_szContent;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMailContent(const char *szContent)
	{
		strncpy(m_szContent, szContent, MAX_MAIL_CONTEX - 1);
		m_ContentSize = (uchar) strlen(m_szContent);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uchar GetMailFlag()
	{
		return m_uFlag;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMailFlag(uchar uFlag)
	{
		m_uFlag = uFlag;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	Time_t GetCreateTime()
	{
		return m_uCreateTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetCreateTime(Time_t uCreateTime)
	{
		m_uCreateTime = uCreateTime;
	}

	void	Clear();
	uint32	GetSize() const;
	void	Reci(RecieveStream &iStream); //Modified by Jerry Huang
	void	Send(SendStream &oStream) const; //Modified by Jerry Huang
};

struct PLAYER_SIMPLE_DATA
{
	char		m_szAccountName[MAX_ACCOUNT];
	char		m_Name[MAX_CHARACTER_NAME];
	int32		m_nCreateTime;
	GUID_t		m_GUID;
	int32		m_nCountry;
	uint32		m_uProfession;
	int32		m_nPortrait;
	uchar		m_uFaceMeshID;
	uchar		m_uHairMeshID;
	uint32		m_uHairColor;
	int32		m_nLevel;
	uint16		m_uRoleSex;
	uint16		m_uUserSex;
	char		m_szTitle[MAX_CHARACTER_TITLE];
	GuildID_t	m_GuildID;
	char		m_szGuildName[MAX_GUILD_NAME_SIZE];
	char		m_szFamilyName[MAX_GUILD_FAMILY_NAME_SIZE];
	int32		m_iPostCode;

	uint32		m_uSiller;
	uint32		m_uBindSiller;
	uint32		m_uGold;
	uint32		m_uBindGold;
	uint32		m_uBankMoney;
	uint32		m_uAge;
	int32		m_nLastMuteTime;
	int32		m_nLastEnjailTime;
	int32		m_iShengWang;
	int32		m_iHotValue;
	int32		m_iGP;
	int32		m_iHonor;
	int32		m_iPKValue;
	uint16		m_nKillCountToday;
	uint16		m_nPVP2V2Level;
	uint16		m_nPVP2V2Mark;
	ID_t		m_nWorldID;
    //! 天赋等级
    uint16      m_uiInherenceLevel;

	PLAYER_SIMPLE_DATA()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(m_szAccountName, 0, sizeof(m_szAccountName));
		memset(m_Name, 0, sizeof(m_Name));
		m_nCreateTime = 0;
		m_GUID = INVALID_ID;
		m_nCountry = INVALID_COUNTRY;
		m_uProfession = INVALID_JOB;
		m_nPortrait = -1;
		m_nLevel = 0;
		m_uRoleSex = 0;
		m_uUserSex = 0;
		memset(m_szTitle, 0, sizeof(m_szTitle));
		memset(m_szGuildName, 0, sizeof(m_szGuildName));
		memset(m_szFamilyName, 0, sizeof(m_szFamilyName));
		m_GuildID = INVALID_ID;
		m_iPostCode = INVALID_ID;
		m_uSiller = 0;
		m_uBindSiller = 0;
		m_uGold = 0;
		m_uBindGold = 0;
		m_uBankMoney = 0;
		m_uAge = 0;
		m_nLastEnjailTime = 0;
		m_nLastMuteTime = 0;
		m_iShengWang = INVALID_ID;
		m_iHotValue = INVALID_ID;
		m_iGP = INVALID_ID;
		m_iHonor = INVALID_ID;
		m_iPKValue = INVALID_ID;
		m_nKillCountToday = 0;
		m_nPVP2V2Level = 0;
		m_nPVP2V2Mark = 0;
		m_nWorldID = INVALID_ID;
        m_uiInherenceLevel = 0;
	}
};

#define MAX_SQL_LENGTH	409600

struct SQLString
{
	uchar	m_SqlStr[MAX_SQL_LENGTH];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		memset(m_SqlStr, 0, MAX_SQL_LENGTH);
	}

	void	Parse(const char *pTemplate, ...);
};

struct SArchivePlayerEquipList
{
	SArchivePlayerEquipList()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}

	uint32	m_Equip[HEQUIP_NUMBER];
};

struct SArchivePlayerBaseInfo
{
	SArchivePlayerBaseInfo()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(this, 0, sizeof(*this));

		m_Profession = INVALID_JOB;
		m_Country = INVALID_COUNTRY;
		m_Sex = INVALID_SEX;
		m_bShowSuit = 1;
		m_GUID = INVALID_GUID;
		m_nGuildId = INVALID_GUILD_ID;
		memset(m_szGuildName, 0, sizeof(m_szGuildName));
		m_nIsCharNeedRename = 0;
		m_nIsGuildNeedRename = 0;
		m_MountModelID = -1;
	}

	GUID_t			m_GUID;
	uchar			m_Sex;
	char			m_Name[MAX_CHARACTER_NAME];
	int32			m_Level;
	uint32			m_HairColor;
	uchar			m_FaceColor;
	uchar			m_HairModel;
	uchar			m_FaceModel;
	MapID_t			m_StartScene;
	int32			m_Profession;
	int32			m_HeadID;
	SArchivePlayerEquipList	m_EquipList;
	int32			m_Country;
	BOOL			m_bFirstLogin;
	BOOL			m_bShowSuit;
	int32			m_SoulID;
	uint32			m_GemAff;
	uint32			m_SetSuit;
	uint32			m_LevelAff;
	GuildID_t		m_nGuildId;
	char			m_szGuildName[MAX_GUILD_NAME_SIZE];
	int32			m_nIsCharNeedRename;
	int32			m_nIsGuildNeedRename;
	int32			m_MountModelID;
};

struct TEAMMEMBER_BASEINFO
{
	TEAMMEMBER_BASEINFO()
	{
		Clear();
	}
	GUID_t		m_Member;
	MapID_t		m_SceneID;
	MapID_t		m_SceneResID;
	ConnectorID_t	m_playerID;
	ObjID_t		m_ObjID;
	uchar		m_IsMomentLeave;
	uchar		m_IsDead;
	char		m_Name[MAX_CHARACTER_NAME];
	int32		m_nPortrait;
	uint16		m_uDataID;
	uint32		m_uFamily;
	int32		m_Level;
	GLPos	m_WorldPos;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_Member = INVALID_ID;
		m_SceneID = INVALID_ID;
		m_SceneResID = INVALID_ID;
		m_ObjID = INVALID_ID;
		m_IsMomentLeave = 0;
		m_IsDead = 0;
		memset(m_Name, 0, MAX_CHARACTER_NAME);
		m_nPortrait = INVALID_ID;
		m_uDataID = 0;
		m_uFamily = INVALID_ID;
		m_Level = 0;
		m_WorldPos.Clear();
	}

	uint32	GetSize() const;
	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct TEAMMEMBER_EUQIPINFO
{
	TEAMMEMBER_EUQIPINFO()
	{
		Clear();
	}
	GUID_t	m_Member;
	uint32	m_WeaponID;
	uint32	m_AssihandID;
	uint32	m_CapID;
	uint32	m_ScapularID;
	uint32	m_ArmourID;
	uint32	m_CuffID;
	uint32	m_FootID;
	uint32	m_Suit;
	uint32	m_GemID;
	uint32	m_SoulID;
	uint32	m_SetSuit;
	uint32	m_LevelAff;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_Member = INVALID_ID;
		m_WeaponID = INVALID_ID;
		m_AssihandID = INVALID_ID;
		m_CapID = INVALID_ID;
		m_ScapularID = INVALID_ID;
		m_ArmourID = INVALID_ID;
		m_CuffID = INVALID_ID;
		m_FootID = INVALID_ID;
		m_Suit = INVALID_ID;
		m_GemID = INVALID_ID;
		m_SoulID = INVALID_ID;
		m_SetSuit = INVALID_ID;
		m_LevelAff = INVALID_ID;
	}

	uint32	GetSize() const;
	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct TEAMMEMBER_HEADINFO
{
	TEAMMEMBER_HEADINFO()
	{
		Clear();
	}
	int32	m_nHP;
	uint32	m_uMaxHP;
	int32	m_nAnger;
	int32	m_nMaxAnger;
	uint32	m_uFaceMeshID;
	uint32	m_uHairMeshID;
	uint32	m_uHairColor;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_nHP = 0;
		m_uMaxHP = 0;
		m_nAnger = 0;
		m_nMaxAnger = 0;
		m_uFaceMeshID = INVALID_ID;
		m_uHairMeshID = INVALID_ID;
		m_uHairColor = INVALID_ID;
	}

	uint32	GetSize() const;
	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct STeamListEntry
{
	GUID_t		m_GUID;
	MapID_t		m_SceneID;
	ID_t		m_SceneResID;
	uint32		m_ExtraID;
	uchar		m_NameSize;
	char		m_Name[MAX_CHARACTER_NAME];
	int32		m_nPortrait;
	uint16		m_uDataID;
	uint32		m_uFamily;
	int32		m_Level;
	int32		m_nHP;
	uint32		m_uMaxHP;
	int32		m_nAnger;
	int32		m_nMaxAnger;
	GLPos	m_WorldPos;
	uchar		m_IsMomentLeave;
	uchar		m_IsDead;

	uint32		m_WeaponID;
	uint32		m_AssihandID;
	uint32		m_CapID;
	uint32		m_ScapularID;
	uint32		m_ArmourID;
	uint32		m_CuffID;
	uint32		m_FootID;
	uint32		m_Suit;
	uint32		m_GemID;
	uint32		m_SoulID;
	uint32		m_SetSuit;
	uint32		m_LevelAff;

	uint32		m_uFaceMeshID;
	uint32		m_uHairMeshID;
	uint32		m_uHairColor;
	STeamListEntry()
	{
		Clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_GUID = INVALID_ID;
		m_SceneID = INVALID_ID;
		m_SceneResID = INVALID_ID;
		m_ExtraID = INVALID_ID;
		m_NameSize = 0;
		memset(m_Name, 0, sizeof(m_Name));
		m_nPortrait = -1;
		m_uDataID = 0;
		m_uFamily = 0;
		m_Level = 0;
		m_nHP = 0;
		m_uMaxHP = 0;
		m_nAnger = 0;
		m_nMaxAnger = 0;
		m_WorldPos.Clear();
		m_IsMomentLeave = 0;
		m_IsDead = 0;
		m_WeaponID = INVALID_ID;
		m_AssihandID = INVALID_ID;
		m_CapID = INVALID_ID;
		m_ScapularID = INVALID_ID;
		m_ArmourID = INVALID_ID;
		m_CuffID = INVALID_ID;
		m_FootID = INVALID_ID;
		m_Suit = INVALID_ID;
		m_GemID = INVALID_ID;
		m_SoulID = INVALID_ID;
		m_SetSuit = INVALID_ID;
		m_LevelAff = INVALID_ID;
		m_uFaceMeshID = INVALID_ID;
		m_uHairMeshID = INVALID_ID;
		m_uHairColor = INVALID_ID;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	STeamListEntry &operator=(const STeamListEntry &entry)
	{
		m_GUID = entry.m_GUID;
		m_SceneID = entry.m_SceneID;
		m_SceneResID = entry.m_SceneResID;
		m_ExtraID = entry.m_ExtraID;
		m_NameSize = entry.m_NameSize;
		strncpy(m_Name, entry.m_Name, sizeof(m_Name) - 1);
		m_nPortrait = entry.m_nPortrait;
		m_uDataID = entry.m_uDataID;
		m_uFamily = entry.m_uFamily;
		m_Level = entry.m_Level;
		m_nHP = entry.m_nHP;
		m_uMaxHP = entry.m_uMaxHP;
		m_nAnger = entry.m_nAnger;
		m_nMaxAnger = entry.m_nMaxAnger;
		m_IsDead = entry.m_IsDead;
		m_IsMomentLeave = entry.m_IsMomentLeave;
		m_WorldPos.m_fX = entry.m_WorldPos.m_fX;
		m_WorldPos.m_fZ = entry.m_WorldPos.m_fZ;
		m_WeaponID = entry.m_WeaponID;
		m_AssihandID = entry.m_AssihandID;
		m_CapID = entry.m_CapID;
		m_ScapularID = entry.m_ScapularID;
		m_ArmourID = entry.m_ArmourID;
		m_CuffID = entry.m_CuffID;
		m_FootID = entry.m_FootID;
		m_Suit = entry.m_Suit;
		m_GemID = entry.m_GemID;
		m_SoulID = entry.m_SoulID;
		m_uFaceMeshID = entry.m_uFaceMeshID;
		m_uHairMeshID = entry.m_uHairMeshID;
		m_uHairColor = entry.m_uHairColor;
		m_SetSuit = entry.m_SetSuit;
		m_LevelAff = entry.m_LevelAff;
		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetGUID(GUID_t guid)
	{
		m_GUID = guid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	GUID_t GetGUID() const
	{
		return m_GUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetSceneID(MapID_t MapID)
	{
		m_SceneID = MapID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	MapID_t GetSceneID() const
	{
		return m_SceneID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetSceneResID(ID_t MapID)
	{
		m_SceneResID = MapID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ID_t GetSceneResID() const
	{
		return m_SceneResID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetExtraID(uint32 id)
	{
		m_ExtraID = id;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetExtraID() const
	{
		return m_ExtraID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetName(const char *pName)
	{
		if(pName == NULL) return;
		strncpy(m_Name, pName, MAX_CHARACTER_NAME - 1);
		m_NameSize = (uchar) strlen(m_Name);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const char *GetName() const
	{
		return m_Name;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetIcon(int32 icon)
	{
		m_nPortrait = icon;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetIcon() const
	{
		return m_nPortrait;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetDataID(uint16 dataid)
	{
		m_uDataID = dataid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint16 GetDataID() const
	{
		return m_uDataID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetFamily(uint32 uFamily)
	{
		m_uFamily = uFamily;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetFamily() const
	{
		return m_uFamily;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetLevel(int32 Level)
	{
		m_Level = Level;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetLevel() const
	{
		return m_Level;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetHP(int32 nHP)
	{
		m_nHP = nHP;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetHP() const
	{
		return m_nHP;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMaxHP(int32 nHP)
	{
		m_uMaxHP = nHP;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetMaxHP() const
	{
		return m_uMaxHP;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetAnger(int32 nAnger)
	{
		m_nAnger = nAnger;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetAnger() const
	{
		return m_nAnger;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMaxAnger(int32 nAnger)
	{
		m_nMaxAnger = nAnger;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetMaxAnger() const
	{
		return m_nMaxAnger;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetWeaponID(uint32 weaponid)
	{
		m_WeaponID = weaponid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetWeaponID()
	{
		return m_WeaponID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetAssihandID(uint32 AssihandID)
	{
		m_AssihandID = AssihandID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetAssihandID()
	{
		return m_AssihandID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetCapID(uint32 capid)
	{
		m_CapID = capid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetCapID()
	{
		return m_CapID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetScapularID(uint32 ScapularID)
	{
		m_ScapularID = ScapularID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetScapularID()
	{
		return m_ScapularID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetArmourID(uint32 armorid)
	{
		m_ArmourID = armorid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetArmourID()
	{
		return m_ArmourID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetCuffID(uint32 cuffid)
	{
		m_CuffID = cuffid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetCuffID()
	{
		return m_CuffID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetFootID(uint32 footid)
	{
		m_FootID = footid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetFootID()
	{
		return m_FootID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetSuitID(uint32 SuitID)
	{
		m_Suit = SuitID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetSuitID()
	{
		return m_Suit;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetGemID(uint32 gemid)
	{
		m_GemID = gemid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetGemID()
	{
		return m_GemID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetSoulID(uint32 soulid)
	{
		m_SoulID = soulid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetSoulID()
	{
		return m_SoulID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetFaceMeshID(uint32 FaceMeshID)
	{
		m_uFaceMeshID = FaceMeshID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetFaceMeshID()
	{
		return m_uFaceMeshID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetHairMeshID(uint32 HairMeshID)
	{
		m_uHairMeshID = HairMeshID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetHairMeshID()
	{
		return m_uHairMeshID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetHairColor(uint32 HairColor)
	{
		m_uHairColor = HairColor;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 Get_Property_HairColor()
	{
		return m_uHairColor;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void setSetSuit(uint32 ID)
	{
		m_SetSuit = ID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 getSetSuit()
	{
		return m_SetSuit;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void setLevelAff(uint32 ID)
	{
		m_LevelAff = ID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 getLevelAff()
	{
		return m_LevelAff;
	}

	uint32	GetSize() const;
	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct MEMBERENTRY_INFO
{
	uchar	m_NameSize;
	char	m_Name[MAX_CHARACTER_NAME];
	uchar	m_uJob;
	uchar	m_Level;

	MEMBERENTRY_INFO()
	{
		Clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_NameSize = 0;
		memset(m_Name, 0, sizeof(m_Name));
		m_uJob = 0;
		m_Level = 0;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void SetName(const char *pName)
	{
		if(pName == NULL) return;
		strncpy(m_Name, pName, MAX_CHARACTER_NAME - 1);
		m_NameSize = (uchar) strlen(m_Name);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const char *GetName() const
	{
		return m_Name;
	}

	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};

struct TEAMINFO_LIST_ENTRY
{
	TeamID_t		m_TeamID;
	char			m_szTeamEnounce[TEAM_ENOUNCE_LEN];
	uchar			m_nTeamCount;
	MEMBERENTRY_INFO	m_memberInfo[MAX_TEAM_MEMBER];
	TEAMINFO_LIST_ENTRY()
	{
		Clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_TeamID = INVALID_ID;
		m_nTeamCount = 0;
		memset(m_szTeamEnounce, 0, TEAM_ENOUNCE_LEN);
		for(int32 i = 0; i < MAX_TEAM_MEMBER; ++i)
		{
			m_memberInfo[i].Clear();
		}
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	TEAMINFO_LIST_ENTRY &operator=(const TEAMINFO_LIST_ENTRY &entry)
	{
		m_TeamID = entry.m_TeamID;
		m_nTeamCount = entry.m_nTeamCount;
		strncpy(m_szTeamEnounce, entry.m_szTeamEnounce, sizeof(char) * (TEAM_ENOUNCE_LEN - 1));
		for(int32 i = 0; i < m_nTeamCount; ++i)
		{
			m_memberInfo[i].m_uJob = entry.m_memberInfo[i].m_uJob;
			m_memberInfo[i].m_Level = entry.m_memberInfo[i].m_Level;
			m_memberInfo[i].m_NameSize = entry.m_memberInfo[i].m_NameSize;
			strncpy(m_memberInfo[i].m_Name, entry.m_memberInfo[i].m_Name, MAX_CHARACTER_NAME - 1);
		}

		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetTeamID(TeamID_t TeamID)
	{
		m_TeamID = TeamID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	TeamID_t GetTeamID()
	{
		return m_TeamID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetTeamEnounce(const char *pTeamEnounce)
	{
		if(pTeamEnounce == NULL) return;
		strncpy(m_szTeamEnounce, pTeamEnounce, TEAM_ENOUNCE_LEN - 1);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const char *GetTeamEnounce() const
	{
		return m_szTeamEnounce;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddTeamMember(const MEMBERENTRY_INFO &entry)
	{
		KCheck(m_nTeamCount < MAX_TEAMINFOLIST_NUM);
		m_memberInfo[m_nTeamCount++] = entry;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const MEMBERENTRY_INFO &GetTeamMember(uchar i)
	{
		KCheck(i < m_nTeamCount);
		return m_memberInfo[i];
	}

	uint32	GetSize() const;
	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

typedef struct SObjIDList
{
	enum { MAX_LIST_SIZE = 512, };
	SObjIDList()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear(void)
	{
		m_nCount = 0;
		memset((void *) m_aIDs, INVALID_ID, sizeof(m_aIDs));
	}

	int32	m_nCount;
	ObjID_t m_aIDs[MAX_LIST_SIZE];

	uint32 GetSize() const
	{
		return sizeof(ObjID_t) * m_nCount;
	}
	void Send(SendStream &oStream) const;
	void Reci(RecieveStream &iStream);
} ObjID_List;

struct SPlayerShopGuid
{
	ID_t	m_World;
	ID_t	m_Server;
	ID_t	m_Scene;
	int32	m_PoolPos;

	SPlayerShopGuid()
	{
		Reset();
	}

	static uint32 GetSize()
	{
		return	sizeof(ID_t) +
				sizeof(ID_t) +
				sizeof(ID_t) +
				sizeof(int32);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SPlayerShopGuid &operator=(SPlayerShopGuid const &rhs)
	{
		m_PoolPos = rhs.m_PoolPos;
		m_Server = rhs.m_Server;
		m_World = rhs.m_World;
		m_Scene = rhs.m_Scene;
		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator==(SPlayerShopGuid &Ref) const
	{
		return(Ref.m_Scene == m_Scene) && (Ref.m_PoolPos == m_PoolPos) && (Ref.m_Server == m_Server)
	&&	(Ref.m_World == m_World);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL isNull() const
	{
		return(m_Scene == INVALID_ID) && (m_World == INVALID_ID) && (m_PoolPos == -1)
	&&	(m_Server == INVALID_ID);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Reset()
	{
		m_PoolPos = -1;
		m_Server = INVALID_ID;
		m_World = INVALID_ID;
		m_Scene = INVALID_ID;
	}

	void Send(SendStream &oStream) const;
	void Reci(RecieveStream &iStream) const;
};

enum SM_COMMANDS { CMD_UNKNOW, CMD_SAVE_ALL, CMD_CLEAR_ALL, };

struct SM_COMMANDS_STATE
{
	SM_COMMANDS	cmdType;
	union
	{
		int32	iParam[6];
		float	fParam[6];
		char	cParam[24];
	};
};

struct GLOBAL_CONFIG
{
	GLOBAL_CONFIG()
	{
		Commands.cmdType = CMD_UNKNOW;
	}
	SM_COMMANDS_STATE	Commands;
};

class	Flag_T
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	Flag_T()
	{
		Clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	~Flag_T()
	{
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsSetBit(int32 bit) const
	{
		/*~~~~~~~~~~~~~~~~~*/
		uint32	i = bit / 32;
		/*~~~~~~~~~~~~~~~~~*/

		if(i < FLAG_BIT / 32)
		{
			if(m_uFlags[i] & (1 << (uint32) (bit - 32 * i))) return TRUE;
		}
		else
		{
			KCheckEx(FALSE, "数组越界！");
		}

		return FALSE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void UpdateBit(int32 bit, BOOL bUpDate)
	{
		/*~~~~~~~~~~~~~~~~~*/
		uint32	i = bit / 32;
		/*~~~~~~~~~~~~~~~~~*/

		if(i < FLAG_BIT / 32)
		{
			if(bUpDate)
			{
				m_uFlags[i] |= (1 << (uint32) (bit - 32 * i));
			}
			else
			{
				m_uFlags[i] &= (~(1 << (uint32) (bit - 32 * i)));
			}
		}
		else
		{
			KCheckEx(FALSE, "数组越界！");
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(m_uFlags, 0, sizeof(m_uFlags));
	}

	BOOL	Read(RecieveStream &iStream);

	BOOL	Write(SendStream &oStream) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	const static int32	FLAG_BIT = 256;
	uint32			m_uFlags[FLAG_BIT / 32];
};


/************************************************************************/
/* 固定大小的Flag,为模块类,需要声明的时候指定,此类为Flag_T的增强版      */
/* NUM_FixedLen的值如果不是为2的次方值,则取最接近并且小于他的2的次方值  */
/************************************************************************/
template<uint32 NUM_FixedLen > class FixedFlag
{
public:

	///////////////////////////////////////////////////////////////////////////////////////////////
	//构造函数
	///////////////////////////////////////////////////////////////////////////////////////////////
	FixedFlag()																	
	{
		Clear();
	};


	///////////////////////////////////////////////////////////////////////////////////////////////
	//析构函数
	///////////////////////////////////////////////////////////////////////////////////////////////
	~FixedFlag()																
	{
	};

	///////////////////////////////////////////////////////////////////////////////////////////////
	//清空数据
	///////////////////////////////////////////////////////////////////////////////////////////////
	void Clear( void )															
	{
		memset(m_uFlags, 0, sizeof(m_uFlags));
	}

public:

	///////////////////////////////////////////////////////////////////////////////////////////////
	//检查位是否已经设置
	///////////////////////////////////////////////////////////////////////////////////////////////
	BOOL IsSetBit(int32 bit) const												
	{
		uint32	i = bit / 32;
		if(i < NUM_FixedLen / 32)
		{
			if(m_uFlags[i] & (1 << (uint32) (bit - 32 * i))) 
				return TRUE;
		}
		else
		{
			KCheckEx(FALSE, "数组越界！");
		}

		return FALSE;
	}
    
	///////////////////////////////////////////////////////////////////////////////////////////////
	//更新位状态
	///////////////////////////////////////////////////////////////////////////////////////////////
	void UpdateBit(int32 bit, BOOL bUpDate)										
	{
		uint32	i = bit / 32;
		if(i < NUM_FixedLen / 32)
		{
			if(bUpDate)		m_uFlags[i] |= (1 << (uint32) (bit - 32 * i));
			else			m_uFlags[i] &= (~(1 << (uint32) (bit - 32 * i)));
		}
		else
		{
			KCheckEx(FALSE, "数组越界！");
		}
	}

public:

	///////////////////////////////////////////////////////////////////////////////////////////////
	//取得大小
	///////////////////////////////////////////////////////////////////////////////////////////////
	uint32 GetMsgSize( void ) const												
	{
		return sizeof(m_uFlags);
	}
private:

	///////////////////////////////////////////////////////////////////////////////////////////////
	//内部数据
	///////////////////////////////////////////////////////////////////////////////////////////////
	uint32	m_uFlags[ NUM_FixedLen/32 ];										
};

typedef struct SHORT_WORLD_POS
{
	uint16	iPosX;
	uint16	iPosZ;
	SHORT_WORLD_POS()
	{
		iPosX = 0;
		iPosZ = 0;
	};
	SHORT_WORLD_POS (const GLPos *pPos)
	{
		iPosX = (uint16) (pPos->m_fX * 100.0f + 0.5f);
		iPosZ = (uint16) (pPos->m_fZ * 100.0f + 0.5f);
	}
	SHORT_WORLD_POS (float fX, float fZ)
	{
		iPosX = (uint16) (fX * 100.0f + 0.5f);
		iPosZ = (uint16) (fZ * 100.0f + 0.5f);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SHORT_WORLD_POS &operator=(const GLPos *pPos)
	{
		if(NULL == pPos)
		{
			return *this;
		}

		iPosX = (uint16) (pPos->m_fX * 100.0f + 0.5f);
		iPosZ = (uint16) (pPos->m_fZ * 100.0f + 0.5f);
		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SHORT_WORLD_POS &operator=(const GLPos &pos)
	{
		iPosX = (uint16) (pos.m_fX * 100.0f + 0.5f);
		iPosZ = (uint16) (pos.m_fZ * 100.0f + 0.5f);
		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void ToWorldPos(GLPos &oPos) const
	{
		oPos.m_fX = iPosX * 0.01f;
		oPos.m_fZ = iPosZ * 0.01f;
	}

	uint32 GetSize() const
	{
		return sizeof(iPosX) + sizeof(iPosZ);
	}
}
short_pos;

struct FightInfo
{
	FightInfo()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_nSceneId = INVALID_ID;
		m_fPosX = 0.f;
		m_fPosZ = 0.f;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	FightInfo &operator=(const FightInfo &p)
	{
		if(&p != this)
		{
			m_nSceneId = p.m_nSceneId;
			m_fPosX = p.m_fPosX;
			m_fPosZ = p.m_fPosZ;
		}

		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init(const FightInfo *p)
	{
		m_nSceneId = p->m_nSceneId;
		m_fPosX = p->m_fPosX;
		m_fPosZ = p->m_fPosZ;
	}

	MapID_t m_nSceneId;
	float	m_fPosX;
	float	m_fPosZ;
};

struct _MERCHANDISE_ITEM
{
	uint32	idTable;
	uchar	byNumber;
	uchar	nPriceType;
	uint32	nPrice;
	int32	MaxNumber;
	uchar	byActiveState;
	float	AppearRate;
	uchar	IconType;

	_MERCHANDISE_ITEM()
	{
		Clear();
	}

	void Clear()
	{
		idTable = 0;
		byNumber = 0;
		nPrice = 0;
		nPriceType = 0;
		MaxNumber = 0;
		byActiveState = 0;
		AppearRate = 100.0;
		IconType = 0;
	}

	_MERCHANDISE_ITEM &operator=(const _MERCHANDISE_ITEM &value)
	{
		this->idTable = value.idTable;
		this->byNumber = value.byNumber;
		this->nPriceType = value.nPriceType;
		this->nPrice = value.nPrice;
		this->MaxNumber = value.MaxNumber;
		this->byActiveState = value.byActiveState;
		this->AppearRate = value.AppearRate;
		this->IconType = value.IconType;

		return *this;
	}

	static uint32 GetSize()
	{
		return sizeof(uint32) +
			sizeof(uchar) +
			sizeof(uchar) +
			sizeof(uint32) +
			sizeof(int32) +
			sizeof(uchar) +
			sizeof(float) +
			sizeof(uchar);
	}
	void Reci(RecieveStream &iStream);
	void Send(SendStream &oStream) const;
	
};

struct _GUILD_MERCH_INFO
{
	int32	m_nMerchID;
	int32	m_nGuildLevel;
	int32	m_nGuildExp;
	_GUILD_MERCH_INFO()
	{
		m_nMerchID = 0;
		m_nGuildLevel = 0;
		m_nGuildExp = 0;
	}
};

struct _GUILD_MERCH_EXINFO
{
	int32	m_nGuildLevel;
	int32	m_nGuildExp;
	_GUILD_MERCH_EXINFO()
	{
		m_nGuildLevel = 0;
		m_nGuildExp = 0;
	}
	static uint32 GetSize()
	{
		return sizeof(int32) + sizeof(int32);
	}
	void Reci(RecieveStream &iStream);
	void Send(SendStream &oStream) const;
};

struct _STRING_FILTER_INFO
{
	enum { FILTER_TYPE_CHAT = 1, FILTER_TYPE_MAIL = 2, };

	uchar m_Type;
	uchar m_MsgType;
	uchar m_ChatType;
	char *m_StringBuff;
	GUID_t m_GUID;
	const char *m_szSourName;
	const char *m_szAccName;
	int32 m_nLevel;
	uchar m_CountryId;
	_STRING_FILTER_INFO()
	{
		memset(this, 0, sizeof(_STRING_FILTER_INFO));
	}
};

#define RSA_PACKET_ARRAY_NUM 34

struct RSA_VLOLG_PACKET 
{
	int		m_Negative;
	uint32	m_Share;
	uint32	m_Num;
	uint32	m_Array[RSA_PACKET_ARRAY_NUM];

	void Clear()
	{
		m_Negative = 0;
		m_Share = 0;
		m_Num = 0;
		memset( m_Array,0,sizeof(uint32) * RSA_PACKET_ARRAY_NUM );
	}

	void SetNegative(int val)
	{
		m_Negative = val;
	}

	int GetNegative()
	{
		return m_Negative;
	}

	void SetShare(uint32 val)
	{
		m_Share = val;
	}

	uint32 GetShare()
	{
		return m_Share;
	}

	void SetNum(uint32 val)
	{
		m_Num = val;
	}

	uint32 GetNum()
	{
		return m_Num;
	}

	void SetArray(uint32 index,uint32 val);
	uint32 GetArray(uint32 index);

	void Reci(RecieveStream &iStream);
	void Send(SendStream &oStream) const;

	uint32 GetSize() const
	{
		return sizeof(m_Negative) + sizeof(m_Share) + sizeof(m_Num) + sizeof(uint32) * RSA_PACKET_ARRAY_NUM;
	}

	enum
	{
		struct_size	= sizeof(int) + sizeof(uint32) + sizeof(uint32) + sizeof(uint32) * RSA_PACKET_ARRAY_NUM
	};

};

#include "StructItem.h"
#include "StructSpell.h"
#include "StructMap.h"

#include "StructGuild.h"
#include "StructCity.h"

#include "StructMinorPasswd.h"
#endif
