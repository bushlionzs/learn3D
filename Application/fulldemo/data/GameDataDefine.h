/*$T Client/Game/DataPool/GameDataDefine.h GC 1.140 08/23/09 04:52:30 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


/*
 * ;
 * ��Ϸ���ݶ��� ;
 * ;
 */
#ifndef _GAME_DATA_DEFINE_H_
#define _GAME_DATA_DEFINE_H_

#include "StructDB.h"
#include "GameTableData.h"
#include "Data\Struct\GameDataStructPet.h"
#include "Data\Struct\GameDataStructPlayerShop.h"
#include "StructCommandScript.h"
namespace	GDataDef
{
/*
 -----------------------------------------------------------------------------------------------------------------------
    ��ȴ��
 -----------------------------------------------------------------------------------------------------------------------
 */
struct COOLDOWN_GROUP
{
	int32		nTotalTime;
	int32		nTimeElapsed;
	UINT64	nCreateTime;

	COOLDOWN_GROUP (void)
	{
		Reset();
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	void Reset(void)
	{
		nTotalTime = 0;
		nTimeElapsed = 0;
		nCreateTime = 0;
	};
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    �������
 -----------------------------------------------------------------------------------------------------------------------
 */
struct PRIVATE_INFO
{
	STRING	m_szName;		/* ��CleanUp�в�Ҫ��� */
	int32		m_nInfoType;	/* ���̶ܳ� */
	uint32	m_unCharGUID;	/* ��ɫ��� */
	int32		m_nAge;			/* ���� */
	int32		m_nSex;			/* �Ա� */
	STRING	m_szJobInfo;	/* ְҵ��Ϣ */
	STRING	m_szSchoolInfo; /* ��ҵԺУ */
	int32		m_nBloodType;	/* Ѫ�� */
	int32		m_nYearAnimal;	/* ��Ф */
	int32		m_birthMonth;
	int32		m_birthDay;
	int32		m_nConsella;	/* ���� */
	STRING	m_szProvince;	/* ʡ�� */
	STRING	m_szCity;		/* ���� */
	STRING	m_szEmailInfo;	/* �ʼ� */
	STRING	m_szLuckWord;	/* ������� */

	STRING	m_szHomePage;	/* ��ҳ */
	STRING	m_szQQ;			/* QQ */
	STRING	m_szMSN;		/* MSN */

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */

	void CleanUp(void)
	{
		m_nInfoType = 0;
		m_unCharGUID = 0;
		m_nAge = 0;
		m_nSex = 0;
		m_szJobInfo = "";
		m_szSchoolInfo = "";
		m_nBloodType = 0;
		m_nYearAnimal = 0;
		m_nConsella = 0;
		m_szProvince = "";
		m_szCity = "";
		m_szEmailInfo = "";
		m_szLuckWord = "";

		m_szHomePage = "";
		m_szQQ = "";
		m_szMSN = "";

		m_birthMonth = 0;
		m_birthDay = 0;
	};
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    ͬ�����
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SameCityData
{
	GUID_t		m_playerGUID;
	string		m_strName;
	int32			m_iLevel;
	int32			m_iZhiYe;
	int32			m_iCountry;
	string		m_strGuild;
	int32			m_nGuildId;
	int32			m_nGuildPos;
	POSTCODE	m_postCode;

	SameCityData (void)
	{
		m_nGuildId = -1;
		m_nGuildPos = -1;
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	SameCityData &operator=(const SameCityData &data)
	{
		m_playerGUID = data.m_playerGUID;
		m_strName = data.m_strName;
		m_iLevel = data.m_iLevel;
		m_iZhiYe = data.m_iZhiYe;
		m_iCountry = data.m_iCountry;
		m_strGuild = data.m_strGuild;
		m_nGuildId = data.m_nGuildId;
		m_nGuildPos = data.m_nGuildPos;
		m_postCode = data.m_postCode;
		m_nGuildId = data.m_nGuildId;
		m_nGuildPos = data.m_nGuildPos;

		return *this;
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	BOOL operator==(const SameCityData &data)
	{
		if(data.m_playerGUID == m_playerGUID) return TRUE;

		return FALSE;
	}
};
enum { MAX_SHOW_NUM_ONEPAGE = 2, };

/*
 -----------------------------------------------------------------------------------------------------------------------
    ��������
 -----------------------------------------------------------------------------------------------------------------------
 */
struct TopData
{
	GUID_t	m_Guid;			/* ���GUID */
	int32		m_nLevel;		/* �ȼ� */
	int32		m_nCountry;		/* ���� */
	STRING	m_strName;		/* ���� */
	int32		m_nMenPai;		/* ְҵ */
	STRING	m_strGuildName; /* ������� */
	int32		m_nKeyValue;	/* ���а�ؼ�ֵ���������а�����Ͳ�ͬ������ֵ����Ҳ��ͬ */
	uint32	m_uTopVersion;	/* ���а�汾�� */
	int32		m_nReserved[3];

	TopData (void)
	{
		m_Guid = INVALID_ID;
		m_nLevel = 0;
		m_nCountry = INVALID_ID;
		m_nMenPai = INVALID_ID;
		m_nKeyValue = INVALID_ID;
		m_uTopVersion = 0;

		//memset(m_nReserved, 0, sizeof(m_nReserved));
		m_nReserved[0] = -1;
		m_nReserved[1] = -1;
		m_nReserved[2] = -1;
		
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	TopData &operator=(const TopData &val)
	{
		m_Guid = val.m_Guid;
		m_nLevel = val.m_nLevel;
		m_nCountry = val.m_nCountry;
		m_strName = val.m_strName;
		m_nMenPai = val.m_nMenPai;
		m_strGuildName = val.m_strGuildName;
		m_nKeyValue = val.m_nKeyValue;
		m_uTopVersion = val.m_uTopVersion;

		memcpy(m_nReserved, val.m_nReserved, sizeof(m_nReserved));

		return *this;
	}
};

typedef std::map<int32, TopData>	TOP_DATA_MAP;

/*
 -----------------------------------------------------------------------------------------------------------------------
    ���а�����
 -----------------------------------------------------------------------------------------------------------------------
 */
struct TopTypeData
{
	int32 nMaxTopNum;				/* ��ǰ���յ������������ */
	int32 nTotalTopNum;			/* ��ǰ��¼���� */
	uint32 uTopVersion;			/* ���а�汾�� */
	UINT64 uCreateTime;			/* ����ʱ�� */
	TOP_DATA_MAP TopDataMap;	/* �����а����� */

	TopTypeData (void)
	{
		nMaxTopNum = 0;
		uTopVersion = -1;
		uCreateTime = 0;
		nTotalTopNum = 0;
	}
};


typedef std::map<INT, TopTypeData, std::less<INT>,
Ogre::StlAllocator<pair<INT, TopTypeData>, Ogre::CompactablePoolAllocPolicy> >									TOP_TYPE_MAP;

typedef std::map<INT, KCharatcterBaseData*, std::less<INT>,
Ogre::StlAllocator<pair<INT, KCharatcterBaseData*>, Ogre::CompactablePoolAllocPolicy> >							MAP_CHARDATA;

typedef std::vector< COOLDOWN_GROUP, Ogre::StlAllocator<COOLDOWN_GROUP, Ogre::CompactablePoolAllocPolicy> >		VECTOR_COOLDOWN;
typedef std::vector< INT, Ogre::StlAllocator<INT, Ogre::CompactablePoolAllocPolicy> >							VECTOR_INT;

typedef std::map<INT, _BUFF_EFFECT_INFO*, std::less<INT>,
Ogre::StlAllocator<pair<INT, _BUFF_EFFECT_INFO*>, Ogre::CompactablePoolAllocPolicy> >							CBuffImpactMap;

typedef std::vector< SameCityData, Ogre::StlAllocator<SameCityData, Ogre::CompactablePoolAllocPolicy> >			SameCityDataVec;

typedef std::map<STRING, SameCityData, std::less<STRING>,
Ogre::StlAllocator<pair<STRING, SameCityData>, Ogre::CompactablePoolAllocPolicy> >								SameCityDataMap;


typedef std::vector< _TABLE_PROVINCE_ZONE >	ZoneVec;				//����
typedef std::map< STRING, ZoneVec >			ProvinceZoneMap;		//ʡ��������
typedef std::pair< STRING, STRING >			ProvinceZonePair;		//����ʡ�ݶ�
typedef std::map< INT, ProvinceZonePair >	PostCodeProvinceZoneMap;//���ʡ��������
typedef std::vector< STRING >				ProvinceVec;

typedef std::deque< INT, Ogre::StlAllocator<INT, Ogre::CompactablePoolAllocPolicy> >							LinkItemQue;
typedef std::vector< SDataPet,  Ogre::StlAllocator<SDataPet, Ogre::CompactablePoolAllocPolicy> >				LinkHorseQue;


/*
 -----------------------------------------------------------------------------------------------------------------------
    BBS�ϵ�����
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SMessageEntry
{
	STRING AuthorName;
	uint32 nID;
	BYTE nHour;
	BYTE nMin;
	BOOL bHasReply;
	STRING szMessage;
	BYTE nReHour;
	BYTE nReMin;
	STRING szReplyMessage;

	SMessageEntry (void)
	{
		AuthorName = "";
		nID = 0;
		nHour = 0;
		nMin = 0;
		bHasReply = 0;
		szMessage = "";
		nReHour = 0;
		nReMin = 0;
		szReplyMessage = "";
	}
};

struct BBS_t
{
	STRING m_szTitle;
	uint32 m_nSerial;
	int32 m_nMessageNum;
	std::vector<SMessageEntry> m_MessageList;

	BBS_t (void)
	{
		CleanUp();
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	void CleanUp(void)
	{
		m_nMessageNum = 0;
		m_szTitle = "";
		m_nSerial = 0;

		SMessageEntry BBSinital;

		m_MessageList.resize(MAX_BBS_MESSAGE_NUM, BBSinital);	/* ���԰� */
	};
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    ̯λ��Ʒ
 -----------------------------------------------------------------------------------------------------------------------
 */
struct BAITAN_ITEM
{
	BAITAN_ITEM (void)
	{
		pItem = NULL;
		nPrice = 0;
		nSerial = 0;
		nbIsEnable = 0;
	}
	KItem	*pItem;		/* ��Ʒָ�� */
	uint32 nPrice;		/* �۸� */
	uint32 nSerial;		/* ���к� */
	BYTE nbIsEnable;	/* �����Ʒ�Ƿ��ϼ� */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    ̯λ����
 -----------------------------------------------------------------------------------------------------------------------
 */
struct STALL_PET
{
	STALL_PET (void)
	{
		pPet = NULL;
		nPrice = 0;
		nSerial = 0;
		nbIsEnable = TRUE;
		m_GUID.Reset();
	}
	SDataPet	*pPet;	/* ����ָ�� */
	uint32 nPrice;		/* �۸� */
	uint32 nSerial;		/* ���к� */
	BYTE nbIsEnable;	/* �����Ʒ�Ƿ��ϼ� */
	SHorseGuid m_GUID;
};

enum STALL_DEFAULT_PAGE { ITEM_PAGE = 0,	/* ��Ʒҳ */ PET_PAGE, };

/*
 -----------------------------------------------------------------------------------------------------------------------
    ̯λ��
 -----------------------------------------------------------------------------------------------------------------------
 */
struct CLIENT_BAITAN_BOX
{
	int32 m_nDefaultPage;					/* ȱʡ��ҳ�� */
	uint32 m_ObjID;
	BOOL m_bIsOpen;						/* �Լ�̯λ�Ƿ��Ѿ��򿪣��Ƿ��ڽ���״̬�� */
	uint32 m_PosTax;						/* ̯λ�� */
	uint32 m_TradeTax;					/* ÿ�ν���˰�� */
	STRING m_szStallName;				/* ��ʾ̯λ�� */
	STRING m_szOwnerName;				/* ��ʾ̯���� */
	uint32 m_nFirstPage;					/* ��ʼҳ */
	std::vector<BAITAN_ITEM> m_ItemList; /* ��ʾ̯λ�е�������Ʒ */
	std::vector<STALL_PET> m_PetList;	/* ��ʾ̯λ�е����г��� */
	BBS_t m_BBS;						/* ̯λ���԰� */
	uint32 m_OtGUID;

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */

	void CleanUp()
	{
		m_nDefaultPage = ITEM_PAGE;
		m_ObjID = 0;		/* ̯λӵ���ߵ�ID */
		m_bIsOpen = FALSE;	/* �Լ�̯λ�Ƿ��Ѿ��� */

		/*
		 * m_PosTax = 0;
		 * //̯λ�� ;
		 * m_TradeTax = 0;
		 * //ÿ�ν���˰��
		 */
		m_szStallName = ""; /* ��ʾ̯λ�� */
		m_szOwnerName = ""; /* ��ʾ̯���� */
		m_nFirstPage = 0;	/* ��ʼҳ */
		m_OtGUID = 0;
		m_BBS.CleanUp();

		/* ̯λ���԰� */
		BAITAN_ITEM stallinital;

		m_ItemList.resize(BAITAN_BOX_SIZE, stallinital);

		/* ��ʾ̯λ�е�������Ʒ */
		STALL_PET stallPetinital;

		m_PetList.resize(BAITAN_HORSE_BOX_SIZE, stallPetinital);	/* ��ʾ̯λ�е����г��� */
	};
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    ��ʾ̯λ�е�������Ʒ
 -----------------------------------------------------------------------------------------------------------------------
 */
struct PLAYERSHOP_STALL_BOX
{
	int32 m_bIsEnable;
	std::vector<BAITAN_ITEM> m_ItemList;
	std::vector<STALL_PET> m_PetList;

	PLAYERSHOP_STALL_BOX()
	{
		m_bIsEnable = FALSE;
		BAITAN_ITEM ItemInit;
		m_ItemList.resize(BAITAN_BOX_SIZE, ItemInit);
		STALL_PET PetInit;
		m_PetList.resize(BAITAN_BOX_SIZE, PetInit);
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	void CleanUp()
	{
		m_bIsEnable = FALSE;
		for(int32 i = 0; i < BAITAN_BOX_SIZE; i++)
		{
			BAITAN_ITEM ItemInit;

			m_ItemList[i] = ItemInit;

			STALL_PET PetInit;

			m_PetList[i] = PetInit;
		}
	}
};
enum SHOP_TYPE { NO_SHOP = 0, ITEM_SHOP, PET_SHOP, };

/*
 -----------------------------------------------------------------------------------------------------------------------
    ��ʾ�̵��е����й�̨
 -----------------------------------------------------------------------------------------------------------------------
 */
struct PLAYERSHOP_BOX
{
	std::vector<PLAYERSHOP_STALL_BOX>	m_StallList;
	uint32 m_BaseMoney;
	uint32 m_ProfitMoney;
	SPlayerShopGuid m_ShopID;
	STRING m_szShopName;	/* ��ʾ�̵��� */
	STRING m_szShopDesc;	/* ��ʾ�̵����� */
	STRING m_szOwnerName;	/* ��ʾ������ */
	uint32 m_OwnerGuid;		/* ����GUID */
	BYTE m_bIsSaleOut;		/* ���̵��ѱ��̳� */
	uint32 m_uSaleOutPrice;	/* �̵���̳��� */
	BYTE m_Serial;			/* �̵�����к� */
	int32 m_nShopType;		/* �̵������ */
	BYTE m_ExRecListNum;	/* ���׼�¼���� */
	BYTE m_MaRecListNum;	/* �����¼���� */
	BYTE m_StallOpenNum;	/* �Ѿ�ӵ�еĹ�̨�� */
	BYTE m_ShopSubType;		/* �̵������� */
	std::vector<SPlayerShopPartners> m_PartnerList;	/* �ϻ����б� */

	PLAYERSHOP_BOX (void)
	{
		m_BaseMoney = 0;
		m_ProfitMoney = 0;
		m_szShopName = "";
		m_szOwnerName = "";
		m_szShopDesc = "";
		m_OwnerGuid = 0;
		m_bIsSaleOut = FALSE;
		m_uSaleOutPrice = 0;
		m_Serial = 0;
		m_ExRecListNum = 0;
		m_MaRecListNum = 0;
		m_StallOpenNum = 0;
		PLAYERSHOP_STALL_BOX StallInit;
		m_StallList.resize(MAX_STALL_NUM_PER_SHOP, StallInit);
		SPlayerShopPartners PartnerInit;
		m_PartnerList.resize(MAX_PARTNER_PER_SHOP, PartnerInit);
		m_nShopType = NO_SHOP;
		m_ShopSubType = 0;
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	void CleanUp(void)
	{
		m_BaseMoney = 0;
		m_ProfitMoney = 0;
		m_szShopName = "";
		m_szOwnerName = "";
		m_OwnerGuid = 0;
		m_bIsSaleOut = FALSE;
		m_uSaleOutPrice = 0;
		m_Serial = 0;
		m_ExRecListNum = 0;
		m_MaRecListNum = 0;
		m_StallOpenNum = 0;
		m_ShopID.Reset();
		m_nShopType = NO_SHOP;
		m_ShopSubType = 0;

		for(int32 i = 0; i < MAX_STALL_NUM_PER_SHOP; i++)
		{
			m_StallList[i].CleanUp();
		}

		for(int32 i = 0; i < MAX_PARTNER_PER_SHOP; i++)
		{
			m_PartnerList[i].Clear();
		}
	}
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    �̵������ѡ�е���Ʒ
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SELECT_ITEM
{
	int32 m_nConIndex;
	int32 m_nPosition;

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */

	void CleanUp()
	{
		m_nConIndex = -1;
		m_nPosition = -1;
	}
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    ��������Ʒ
 -----------------------------------------------------------------------------------------------------------------------
 */
struct sQuestRewardItem
{
	SQuestBonus	*pItemData;
	KItem			*pItemImpl;
	BOOL bSelected;

	sQuestRewardItem (void)
	:
	pItemData(0),
	pItemImpl(0),
	bSelected(FALSE)
	{
	}
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    ������Ҫ��Ʒ
 -----------------------------------------------------------------------------------------------------------------------
 */
struct sQuestDemandItem
{
	SQuestBonusItem	*pDemandItem;
	KItem				*pItemImpl;

	sQuestDemandItem (void)
	:
	pDemandItem(0),
	pItemImpl(0)
	{
	}
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    ��ǰ�򿪵�����
 -----------------------------------------------------------------------------------------------------------------------
 */
struct ShopItemActive
{
	int32 m_nNeedGuildLevel;
	int32 m_nNeedGuildExp;

	ShopItemActive()
	{
		CleanUp();
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	void CleanUp()
	{
		m_nNeedGuildLevel = 0;
		m_nNeedGuildExp = 0;
	}
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    ���׺�
 -----------------------------------------------------------------------------------------------------------------------
 */
struct CLIENT_EXCHANGCD_BOX
{
	BOOL m_IsLocked;					/* ��ʾ������lockѡ���Ƿ��� */
	BOOL m_CanConform;					/* ��ʾ�Ƿ���ʾȷ����ť */
	uint32 m_Siller;					/* ��ʾ���׵����� */
	std::vector<KItem *> m_ItemList;	/* ��ʾ���������Լ�����Ʒ */
	std::vector<SDataPet *> m_Petlist; /* ��ʾ���������Լ��ĳ��� */

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */

	void CleanUp(void)
	{
		m_CanConform = FALSE;
		m_IsLocked = FALSE;
		m_Siller = 0;

		m_ItemList.resize(EXCHANGE_BOX_SIZE, 0);
		m_Petlist.resize(EXCHANGE_PET_BOX_SIZE, 0);
	};
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    ��ս��Ϣ
 -----------------------------------------------------------------------------------------------------------------------
 */
struct COUNTRYFIGHTALARMINFO
{
	char m_PlayerName[MAX_CHARACTER_NAME];
	int32 m_SceneID;
	int32 m_PosX;
	int32 m_PosZ;
	int32 m_StartTime;

	COUNTRYFIGHTALARMINFO (void)
	{
		ClearUp();
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	void ClearUp(void)
	{
		memset(m_PlayerName, 0, sizeof(m_PlayerName));
		m_SceneID = -1;
		m_PosX = 0;
		m_PosZ = 0;
		m_StartTime = 0;
	}
};
};
/* namespace */
#endif /* _GAME_DATA_DEFINE_H_ */
