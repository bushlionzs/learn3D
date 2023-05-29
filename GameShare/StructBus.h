/*$T Common/StructBus.h GC 1.140 10/10/07 10:06:55 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __GAMESTRUCT_BUS_H__
#define __GAMESTRUCT_BUS_H__

#include "TypeDefine.h"
#include "Message.h"

#define MAX_VALID_FOLLOW_DIST	25

#define MIN_VALID_FOLLOW_DIST	3

enum _BUS_STATE { NORMAL_STATE = -2, STEALTH_STATE = -1, };

enum BusType
{
	BUS_TYPE_INVALID	= -1,
	BUS_TYPE_CASHBOX,
	BUS_TYPE_NORMAL,
	BUS_TYPE_GUILD_CASHBOX,
	BUS_TYPE_ONLY_FLLOW,
	BUS_TYPE_NUMBERS
};

struct ESCORT_MEMBER
{
	ESCORT_MEMBER()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_GUID = INVALID_ID;
		m_IsInDist = TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ESCORT_MEMBER &operator=(const ESCORT_MEMBER &entry)
	{
		m_GUID = entry.m_GUID;
		m_IsInDist = entry.m_IsInDist;
		return *this;
	}

	GUID_t	m_GUID;
	BOOL	m_IsInDist;
};

struct BUSMEMBER
{
	BUSMEMBER()
	{
		Clear();
	}
	GUID_t	m_Member;
	char	m_Name[MAX_CHARACTER_NAME];
	int32	m_Level;
	int16	m_Profession;
	BOOL	m_IsInBus;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_Member = INVALID_ID;
		memset(m_Name, 0, MAX_CHARACTER_NAME);
		m_Profession = INVALID_ID;
		m_Level = 0;
		m_IsInBus = FALSE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetSize() const
	{
		return sizeof(GUID_t) +
			sizeof(char) *
			MAX_CHARACTER_NAME +
			sizeof(int32) +
			sizeof(int16) +
			sizeof(BOOL);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Reci(RecieveStream &iStream)
	{
		iStream.Reci((char *) &m_Member, sizeof(m_Member));
		iStream.Reci((char *) m_Name, sizeof(char) * MAX_CHARACTER_NAME);
		iStream.Reci((char *) &m_Level, sizeof(m_Level));
		iStream.Reci((char *) &m_Profession, sizeof(m_Profession));
		iStream.Reci((char *) &m_IsInBus, sizeof(m_IsInBus));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Send(SendStream &oStream) const
	{
		oStream.Send((char *) &m_Member, sizeof(m_Member));
		oStream.Send((char *) m_Name, sizeof(char) * MAX_CHARACTER_NAME);
		oStream.Send((char *) &m_Level, sizeof(m_Level));
		oStream.Send((char *) &m_Profession, sizeof(m_Profession));
		oStream.Send((char *) &m_IsInBus, sizeof(m_IsInBus));
	}
};

struct BUS_LIST_ENTRY
{
	ObjID_t m_ObjID;
	uchar	m_NameSize;
	char	m_Name[MAX_CHARACTER_NAME];
	int16	m_Profession;
	int32	m_Level;
	BOOL	m_IsControlBus;
	BOOL	m_IsShowPlayer;
	BOOL	m_IsLeader;
	uchar	m_Index;

	BUS_LIST_ENTRY()
	{
		Clear();
	};

	enum
	{
		struct_size	= sizeof (ObjID_t) +sizeof (uchar) +sizeof (char) *MAX_CHARACTER_NAME +sizeof (int16) +sizeof
			(int32) +sizeof (BOOL) +sizeof (BOOL) +sizeof (BOOL) +sizeof (uchar)
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_ObjID = INVALID_ID;
		m_NameSize = 0;
		memset(m_Name, 0, sizeof(m_Name));
		m_Profession = 0;
		m_Level = 0;
		m_IsControlBus = FALSE;
		m_IsShowPlayer = FALSE;
		m_IsLeader = FALSE;
		m_Index = 0;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	BUS_LIST_ENTRY &operator=(const BUS_LIST_ENTRY &entry)
	{
		m_ObjID = entry.m_ObjID;
		m_NameSize = entry.m_NameSize;
		strncpy(m_Name, entry.m_Name, sizeof(m_Name) - 1);
		m_Profession = entry.m_Profession;
		m_Level = entry.m_Level;
		m_IsControlBus = entry.m_IsControlBus;
		m_IsShowPlayer = entry.m_IsShowPlayer;
		m_IsLeader = entry.m_IsLeader;
		m_Index = entry.m_Index;

		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetObjID(GUID_t guid)
	{
		m_ObjID = guid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	GUID_t GetObjID() const
	{
		return m_ObjID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetName(const char *pName)
	{
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
	void SetProfession(int16 uFamily)
	{
		m_Profession = uFamily;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int16 GetProfession() const
	{
		return m_Profession;
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
	void SetControlBus(BOOL flag)
	{
		m_IsControlBus = flag;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL GetControlBus() const
	{
		return m_IsControlBus;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetShowFlag(BOOL flag)
	{
		m_IsShowPlayer = flag;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL GetShowFlag() const
	{
		return m_IsShowPlayer;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetLeaderFlag(BOOL flag)
	{
		m_IsLeader = flag;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL GetLeaderFlag()
	{
		return m_IsLeader;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetIndex(uchar index)
	{
		m_Index = index;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uchar GetIndex()
	{
		return m_Index;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetSize() const
	{
		return sizeof(m_ObjID) + sizeof(m_NameSize) + sizeof(char) * m_NameSize + sizeof(m_Profession) + sizeof(m_Level) + sizeof(m_IsControlBus) + sizeof(m_IsShowPlayer) + sizeof(m_IsLeader) + sizeof(m_Index);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Read(RecieveStream &iStream)
	{
		iStream.Reci((char *) &m_ObjID, sizeof(m_ObjID));
		iStream.Reci((char *) &m_NameSize, sizeof(m_NameSize));

		if(m_NameSize > 0)
		{
			iStream.Reci((char *) m_Name, sizeof(char) * m_NameSize);
		}

		iStream.Reci((char *) &m_Profession, sizeof(m_Profession));
		iStream.Reci((char *) &m_Level, sizeof(m_Level));
		iStream.Reci((char *) &m_IsControlBus, sizeof(m_IsControlBus));
		iStream.Reci((char *) &m_IsShowPlayer, sizeof(m_IsShowPlayer));
		iStream.Reci((char *) &m_IsLeader, sizeof(m_IsLeader));
		iStream.Reci((char *) &m_Index, sizeof(m_Index));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Write(SendStream &oStream) const
	{
		oStream.Send((char *) &m_ObjID, sizeof(m_ObjID));
		oStream.Send((char *) &m_NameSize, sizeof(m_NameSize));

		if(m_NameSize > 0)
		{
			oStream.Send((char *) m_Name, sizeof(char) * m_NameSize);
		}

		oStream.Send((char *) &m_Profession, sizeof(m_Profession));
		oStream.Send((char *) &m_Level, sizeof(m_Level));
		oStream.Send((char *) &m_IsControlBus, sizeof(m_IsControlBus));
		oStream.Send((char *) &m_IsShowPlayer, sizeof(m_IsShowPlayer));
		oStream.Send((char *) &m_IsLeader, sizeof(m_IsLeader));
		oStream.Send((char *) &m_Index, sizeof(m_Index));
	}


	void Send(SendStream &oStream) const	{ Write(oStream); }
	void Reci(RecieveStream &iStream)		{ Read(iStream); }
};
#endif
