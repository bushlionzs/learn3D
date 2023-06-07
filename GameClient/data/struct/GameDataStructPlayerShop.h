/*$T Client/Game/DataPool/GameDataStructPlayerShop.h GC 1.140 08/23/09 04:52:32 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#pragma once

/* �̵����� */
enum TYPE_PLAYER_SHOP
{
	TYPE_PLAYER_SHOP_INVALID	= 0,		/* ��Ч��𣬻�û�з����ȥ */
	TYPE_PLAYER_SHOP_ITEM,					/* ��Ʒ�� */
	TYPE_PLAYER_SHOP_GEM,					/* ��ʯ�� */
	TYPE_PLAYER_SHOP_WEAPON,				/* ������ */
	TYPE_PLAYER_SHOP_ARMOR,					/* ���׵� */
	TYPE_PLAYER_SHOP_MATERIAL,				/* ���ϵ� */
	TYPE_PLAYER_SHOP_PET,					/* ����� */
};

struct SPlayershopApplyInfo
{
	FLOAT	m_ComFactor;					/* ��ǰ��ҵָ�� */
	uint32	m_Cost;							/* ������ */
	BYTE	m_Type;							/* �ɿ������� */
	SPlayershopApplyInfo()
	{
		memset(this, 0, sizeof(SPlayershopApplyInfo));
	}
};

struct SPlayerShopInfo
{
	String				m_szShopName;		/* �̵��� */
	String				m_szShopDesc;		/* �̵����� */
	String				m_szOwnerName;		/* ̯���� */
	BYTE				m_StallNumOpened;	/* ���ŵĹ�̨�� */
	BYTE				m_StallNumOnSale;	/* ���ŵĹ�̨�� */
	BYTE				m_Type;				/* ���̵����� */
	SPlayerShopGuid	m_ID;				/* ���̵�ΨһID */
	uint32				m_OwnerGuid;		/* ̯��GUID */
	String				m_szFoundedTime;	/* ����ʱ�� */
	BYTE				m_Serial;			/* �̵����к� */
	BYTE				m_bIsFavor;			/* �Ƿ����ղؼ��� */

	SPlayerShopInfo()
	{
		m_szShopName = "";					/* �̵��� */
		m_szShopDesc = "";					/* �̵����� */
		m_szOwnerName = "";					/* ̯���� */
		m_StallNumOpened = 0;				/* ���ŵĹ�̨�� */
		m_StallNumOnSale = 0;				/* ���ŵĹ�̨�� */
		m_Type = 0;				/* ���̵����� */
		m_ID.Reset();			/* ���̵�ΨһID */
		m_OwnerGuid = 0;		/* ̯��GUID */
		m_szFoundedTime = "";	/* ����ʱ�� */
		m_Serial = 0;
		m_bIsFavor = 0;			/* �Ƿ����ղؼ��� */
	}
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    ����̵�ϻ��� ;
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SPlayerShopPartners
{
	GUID_t	m_Guid;
	String	m_szName;

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	void Clear()
	{
		m_Guid = INVALID_GUID;
		m_szName = "";
	}
};
