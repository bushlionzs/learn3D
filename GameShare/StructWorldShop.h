/*$T Common/StructWorldShop.h GC 1.140 10/10/07 10:06:57 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __GAMESTRUCT_WORLD_SHOP_H__
#define __GAMESTRUCT_WORLD_SHOP_H__

#include "TypeDefine.h"

#define SHOP_LIST_NUM			10

#define USER_MAX_SELL_NUM		10

#define PAGE_MERCHANDISE_NUM		42

#define MAX_SHOP_PAGE_NUM		5

#define MERCHANDISE_NUM			(PAGE_MERCHANDISE_NUM * MAX_SHOP_PAGE_NUM)
#define MAX_SHOP_MERCHANDISE_POOL_SIZE	(MERCHANDISE_NUM * SHOP_LIST_NUM)
#define MAX_BANK_DATA_NUM		4096

struct ShopDataNode
{
	uint32	m_SerialId;
	int32	m_Gold;
	int32	m_Price;

	enum { struct_size = sizeof (uint32) +sizeof (int32) +sizeof (int32) };

	ShopDataNode()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init(uint32 id)
	{
		m_SerialId = id;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ShopDataNode &operator=(const ShopDataNode &other)
	{
		__GUARD__ if(&other != this)
		{
			m_SerialId = other.m_SerialId;
			m_Gold = other.m_Gold;
			m_Price = other.m_Price;
		}

		return *this;
		__UNGUARD__ return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetSize() const
	{
		return sizeof(m_SerialId) + sizeof(m_Gold) + sizeof(m_Price);
	}


	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_SerialId = -1;
		m_Gold = 0;
		m_Price = 0;
	}
};
#endif
