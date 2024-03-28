#pragma once
#include "KObject.h"
#include "StructItem.h"

class KItem : public KObject
{
public:
	/* �ӷ��������������ݱ�ʾ(���ںͷ�����ͨѶ) */
	union ITEM_GUID
	{
		/* �ϲ����ID */
		unsigned __int64	m_idUnion;

		/* ���������������� ref GameStruct_Item.h */
		struct ID_FROMSERVER
		{
			USHORT	m_nServerID;	/* �����: (��)101 */
			USHORT	m_idWorld;		/* ����˳���ţ�(��)5 */
			uint32	m_uSerial;		/* ��Ʒ���кţ�(��)123429 */
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

	int32_t getPosIndex()
	{
		return m_nPosIndex;
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

	int32_t GetNumber()
	{
		return m_nNum;
	}

	void SetNumber(int32_t num)
	{
		m_nNum = num;
	}

	virtual std::string getBasePropertyString() { return std::string(); }

	virtual int32 GetItemProfession() { return -1; }

	virtual int32 GetItemLevel() { return 0; }

private:
	int32_t mRuleId;

	SItem mItemInfo;

	int32_t m_nPosIndex = -1;

	int32_t m_idTable = -1;

	int32_t m_nNum = 1;

};