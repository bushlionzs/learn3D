#pragma once
#include "KObject.h"
#include "StructItem.h"

class KItem : public KObject
{
public:
	/* 从服务器传来的数据标示(用于和服务器通讯) */
	union ITEM_GUID
	{
		/* 合并后的ID */
		unsigned __int64	m_idUnion;

		/* 服务器传来的数据 ref GameStruct_Item.h */
		struct ID_FROMSERVER
		{
			USHORT	m_nServerID;	/* 世界号: (例)101 */
			USHORT	m_idWorld;		/* 服务端程序号：(例)5 */
			uint32	m_uSerial;		/* 物品序列号：(例)123429 */
		} m_idOrg;
	} m_ID;
public:
	KItem(uint64_t id);
	~KItem();

	void setRule(int32_t nRuleID);
	int32_t getRule();

	void SetExtraInfo(const SItem* pItemInfo);

	void SetPosIndex(int32 nPosIndex)
	{
		m_nPosIndex = nPosIndex;
	}

	void SetGUID(USHORT idWorld, USHORT idServer, uint32 idSerial);

	int32_t GetIdTable(void) const
	{
		return m_idTable;
	}
	void setIdTable(int32_t id)
	{
		m_idTable = id;
	}
private:
	int32_t mRuleId;

	SItem mItemInfo;

	int32_t m_nPosIndex = -1;

	int32_t m_idTable = -1;
};