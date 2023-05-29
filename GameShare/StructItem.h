/*$T Common/StructItem.h GC 1.140 10/10/07 10:06:56 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __GAMESTRUCT_ITEM_H__
#define __GAMESTRUCT_ITEM_H__

#include "TypeDefine.h"


uchar	GetTypeBySerial(uint32_t Serial);
uchar	GetClassBySerial(uint32_t Serial);
uint32_t	GetIndexBySerial(uint32_t Serial);
BOOL	ISCommonEquip(uint32_t Serial);
uint32_t	GenMaterialIndex(uint32_t nMaterialType, uint32_t nMaterialLevel);

struct SRangeValue
{
	uint16	m_MinValue;
	uint16	m_MaxValue;
};

struct SItemSpell
{
	BOOL	m_bActive;
	uint16	m_SkillID;
	uint16	m_SkillRate;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	BOOL IsActive()
	{
		return m_bActive;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetActive(BOOL bActive)
	{
		m_bActive = bActive;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(this, 0, sizeof(SItemSpell));
	}

	SItemSpell()
	{
		Clear();
	}
};

struct _EQUIP_EFFECT
{
	uint16	m_EffectID;
	uint16	m_EffectSum;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		memset(this, 0, sizeof(_EQUIP_EFFECT));
	}

	_EQUIP_EFFECT()
	{
		Clear();
	}
};

struct _ITEM_EFFECT_SKILL
{
	uint16	m_nSkillID;
	uchar	m_nLevel;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_nSkillID = -1;
		m_nLevel = 0;
	}
};

struct _ITEM_AFFIX_SKILL
{
	uint16	m_nSkillID;
	uchar	m_nLevel;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_nSkillID = -1;
		m_nLevel = -1;
	}
};

struct _ITEM_ALLVALUE
{
	int32	m_Value;

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
	BOOL operator==(_ITEM_ALLVALUE &iV)
	{
		return iV.m_Value == m_Value;
	}
};

struct SItemValue
{
	int16	m_Value;

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
	BOOL operator==(SItemValue &iV)
	{
		return iV.m_Value == m_Value;
	}
};

struct _ITEM_PROPERTY
{
	uchar		m_AttrType;
	uchar		m_IntensifyCount;	//属性强化次数
	SItemValue	m_Value;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_AttrType = -1;
		m_IntensifyCount = 0;
		m_Value.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator==(_ITEM_PROPERTY &iA)
	{
		return(iA.m_AttrType == m_AttrType) && (iA.m_Value == m_Value) && (iA.m_IntensifyCount == m_IntensifyCount);
	}
};

struct _GEM_REQ_ATT
{
	uchar		m_GemType;
	SItemValue	m_Value;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_GemType = -1;
		m_Value.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator==(_GEM_REQ_ATT &iA)
	{
		return(iA.m_GemType == m_GemType) && (iA.m_Value == m_Value);
	}
};

struct SItemGuid
{
	uchar	m_World;
	uchar	m_Server;
	int32	m_Serial;

	SItemGuid()
	{
		m_Serial = 0;
		m_Server = 0;
		m_World = 0;
	}

	static uint32 GetSize()
	{
		return sizeof(uchar) + sizeof(uchar) + sizeof(int32);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Reset(void)
	{
		m_Serial = 0;
		m_Server = 0;
		m_World = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SItemGuid &operator=(SItemGuid const &rhs)
	{
		m_Serial = rhs.m_Serial;
		m_Server = rhs.m_Server;
		m_World = rhs.m_World;
		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator==(SItemGuid &Ref) const
	{
		return(Ref.m_Serial == m_Serial) && (Ref.m_Server == m_Server) && (Ref.m_World == m_World);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator==(const SItemGuid &Ref) const
	{
		return(Ref.m_Serial == m_Serial) && (Ref.m_Server == m_Server) && (Ref.m_World == m_World);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL isNull() const
	{
		return(m_World == 0) && (m_Serial == 0) && (m_Server == 0);
	}

	void Send(SendStream &oStream) const;
	void Reci(RecieveStream &iStream) const;
};

struct SItemType
{
	struct
	{
		uint32	m_Class : 7;
		uint32	m_Type : 7;
		uint32	m_Index : 14;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 ToUINT()
	{
		uint32	uid = 0;

		uid += m_Class;
		uid = uid << 7;
		uid += m_Type;
		uid = uid << 14;
		uid += m_Index;

		return uid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 ToSerial() const
	{
		uint32	Serial;
		Serial = m_Class;
		Serial = Serial * 100 + m_Type;
		Serial = Serial * 10000 + m_Index;
		return Serial;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL isNull() const
	{
		return(m_Class == 0) && (m_Type == 0) && (m_Index == 0);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator==(SItemType &Ref) const
	{
		return(m_Class == Ref.m_Class) && (m_Type == Ref.m_Type) && (m_Index == Ref.m_Index);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator>(SItemType &Ref) const
	{
		return ToSerial() > Ref.ToSerial();
	}

	BOOL operator < (SItemType & Ref) const
	{
		return
		ToSerial()
		< Ref.ToSerial();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_Class = 0;
		m_Type = 0;
		m_Index = 0;
	}
};

SItemType	Serial2ItemType(uint32 Serial);

struct SItemRuler
{
	BOOL	m_Discard;
	BOOL	m_Tile;
	BOOL	m_ShortCut;
	BOOL	m_CanSell;
	BOOL	m_CanExchange;
	BOOL	m_CanUse;
	BOOL	m_PickBind;
	BOOL	m_EquipBind;
	BOOL	m_Unique;

	BOOL	m_Ident;
	BOOL	m_DummyItem;
	BOOL	m_Bank;
	BOOL	m_Consume;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	BOOL CanDiscard()
	{
		return m_Discard;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL CanTile()
	{
		return m_Tile;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL CanShortCut()
	{
		return m_ShortCut;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL CanSell()
	{
		return m_CanSell;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL CanExchange()
	{
		return m_CanExchange;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL CanUse()
	{
		return m_CanUse;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL isPickBind()
	{
		return m_PickBind;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL isEquipBind()
	{
		return m_EquipBind;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL isUnique()
	{
		return m_Unique;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL isIdent()
	{
		return m_Ident;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL isDummyItem()
	{
		return m_DummyItem;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL isBack()
	{
		return m_Bank;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL isConsume()
	{
		return m_Consume;
	}
};

enum eITEM_RULER_LIST
{
	IRL_DISCARD,
	IRL_TILE,
	IRL_SHORTCUT,
	IRL_CANSELL,
	IRL_CANEXCHANGE,
	IRL_CANUSE,
	IRL_PICKBIND,
	IRL_EQUIPBIND,
	IRL_UNIQUE,
	IRL_IDENT,
	IRL_DUMMYITEM,
	IRL_BANK,
	IRL_CONSUME,
};

enum ITEM_LOCK_STATE { ITEM_UNLOCK = 0, ITEM_LOCK, ITEM_UNLOCKING, };
enum PET_LOCK_STATE { PET_UNLOCK = 0, PET_LOCK, PET_UNLOCKING, };

struct SItemGemInfo
{
	uint32	m_GemIndex;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_GemIndex = INVALID_ITEM_ID;
	}
};

//星座信息
struct SItemConstInfo
{
	uchar	m_ConstId;          //星座Id:0~11
	_ITEM_PROPERTY m_ConstAttr[CONST_ATTR_TYPE_NUMBER];  //星座基础属性及激活属性
	void Clear()
	{
		m_ConstId = -1;
		for (int32 i = 0; i < CONST_ATTR_TYPE_NUMBER; ++i)
		{
			m_ConstAttr[i].Clear();
		}
	}
};

struct SGemInfo
{
};

struct SMedicInfo
{
	uchar	m_nCount;
	uchar	m_Level;		//打星个数

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_nCount = 0;
		m_Level = 0;
	}
};

struct EXTRABAG_INFO
{
	uint32	m_nBeginTime;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_nBeginTime = INVALID_TIME;
	}
};
enum VAR_ATT { ATT_CUR_DUR, ATT_CUR_DAMAGE, };

struct SEquipInfo
{
	uchar		m_NeedLevel;	//装备等级
	uchar		m_Bind;//低4位灵魂铭刻，高4位荣誉铭刻
	uchar		m_PaiType;
	uchar		m_EquipType;
	uint32		m_EquipScore;
	uchar		m_Level;		//打星个数
	uchar		m_CurMaxDur;
	uchar		m_CurDurPoint;
	uint16		m_CurDamagePoint;
	uchar		m_CurGemHole;
	uchar		m_StoneCount;
	SItemGemInfo	m_pGemInfo[MAX_ITEM_GEM];
	uchar		m_AttrCount;
	_ITEM_PROPERTY	m_pAttr[MAX_EQUIP_EXT_ATTR];
	uchar		m_byLock;
	uchar		m_ConstCount;
	uint32		m_UnLockTime;
	SItemConstInfo  m_pConst[MAX_EQUIP_CONST_ATTR];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		memset(this, 0, sizeof(SEquipInfo));
	};

	uchar GetSoulBindLevel()
	{
		return (m_Bind & 0x0F);
	};

	void  SetSoulBindLevel(uchar cLevel)
	{
		m_Bind = (m_Bind & 0xF0) | (cLevel & 0x0F);
	};

	uchar GetHonorBindLevel()
	{
		return m_Bind >> 4;
	};

	void SetHonorBindLevel(uchar cLevel)
	{
		m_Bind = (cLevel << 4) | (m_Bind & 0x0F);	
	};

};

#define MAX_ITEM_LIST_COUNT	8

struct SItemList
{
	int32		m_ListCount;
	SItemType	m_ListType[MAX_ITEM_LIST_COUNT];
	int32		m_TypeCount[MAX_ITEM_LIST_COUNT];
	BOOL		m_bBind[MAX_ITEM_LIST_COUNT];
	SItemList()
	{
		memset(this, 0, sizeof(SItemList));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddType(SItemType it, int32 Count, BOOL bBind = FALSE)
	{
		KCheck(Count > 0);
		KCheck(!it.isNull());

		/*~~~~~~~~~~~~~~~~~~~~~~*/
		BOOL	bFindSame = FALSE;
		/*~~~~~~~~~~~~~~~~~~~~~~*/

		for(int32 i = 0; i < m_ListCount; i++)
		{
			if(m_ListType[i] == it)
			{
				m_TypeCount[i] += Count;
				bFindSame = TRUE;
				break;
			}
		}

		if(m_ListCount >= MAX_ITEM_LIST_COUNT)
		{
			KCheckEx(FALSE, "添加物品个数太多!");
		}

		if(!bFindSame)
		{
			m_TypeCount[m_ListCount] = Count;
			m_ListType[m_ListCount] = it;
			m_bBind[m_ListCount] = bBind;
			m_ListCount++;
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init()
	{
		memset(this, 0, sizeof(SItemList));
	}
};

#define IS_VALID_ITEM(ITEM)		(ITEM.m_ItemIndex != 0)
#define IS_VALID_ITEM_REF_OR_PTR(PITEM)	((PITEM == NULL) ? FALSE : PITEM->GetItemTableIndex())
#define MAX_FIX_ATTR_LENGTH		1000
#define MAX_PET_SKILL_LENGTH		50
#define MAX_ITEM_CREATOR_NAME		13
#define MAX_ITEM_PARAM			3

enum eITEM_PARAM_VALUE { IPV_CHAR = 0, IPV_SHORT = 1, IPV_INT = 2 };

struct SItem
{
	SItemGuid	m_ItemGUID;
	uint32		m_ItemIndex;

	char		m_nsBind;
	char		m_Creator[MAX_ITEM_CREATOR_NAME];
	int32		m_Param[MAX_ITEM_PARAM];
	uint32		m_TermEndTime;

	union
	{
		SEquipInfo	m_Equip;
		SGemInfo	m_Gem;
		SMedicInfo	m_Medic;
		EXTRABAG_INFO	m_ExtraBag;
	};

	SItem()
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
	uchar ItemClass() const
	{
		return GetClassBySerial(m_ItemIndex);
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uchar ItemType() const
	{
		return GetTypeBySerial(m_ItemIndex);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uchar GetIndex() const
	{
		return GetIndexBySerial(m_ItemIndex);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SEquipInfo *GetEquipData() const
	{
		return(SEquipInfo *) (&m_Equip);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SGemInfo *GetGemData() const
	{
		return(SGemInfo *) (&m_Gem);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SMedicInfo *GetMedicData() const
	{
		return(SMedicInfo *) (&m_Medic);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	EXTRABAG_INFO *GetExtraBagData() const
	{
		return(EXTRABAG_INFO *) (&m_ExtraBag);
	}

	uchar	GetItemCount() const;

	void	SetItemCount(int32 nCount);

	BOOL	IncCount(uint32 nCount = 1);

	BOOL	DecCount(uint32 nCount = 1);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	BOOL IsNullType() const
	{
		return (m_ItemIndex == 0 || m_ItemIndex == (uint32)INVALID_ID);
	}

	void	ReadItemRandomProperty(RecieveStream &iStream);
	void	WriteItemRandomProperty(SendStream &oStream) const;

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;

	BOOL	WriteFixProperty(char *pIn, int32 BuffLength);
	BOOL	ReadFixProperty(char *pOut, int32 &OutLength, int32 BuffLength);

	BOOL	WriteRandomProperty(char *pIn, int32 BuffLength);
	BOOL	ReadRandomProperty(char *pOut, int32 &OutLength, int32 BuffLength);

	BOOL	IsFixProperty(uchar attrType);
	uchar	GetFixPropertyCount();

	uchar	GetItemBindType() const;
	void	SetItemBindType(uchar bBind);

	BOOL	IsNormalBound() const ;
	BOOL	IsGoldBound() const ;

	BOOL	GetItemIdent() const;
	void	SetItemIdent(BOOL bIdent);

	BOOL	GetItemPLock() const;
	void	SetItemPLock(BOOL bIdent);

	BOOL	GetCreatorVar() const;
	void	SetCreatorVar(BOOL bCreator);

	int32	GetItemFreeParamValue(uint32 Start, eITEM_PARAM_VALUE &ipv) const;
	void	SetItemFreeParam(uint32 start, eITEM_PARAM_VALUE &ipv, int32 value);

};

BOOL	Item2String(SItem *pItem, char *pOut, int32 &OutLength, int32 BuffLength);
BOOL	String2Item(char *pIn, int32 BuffLength, SItem *pItem);

void	SwapItem(SItem *pItemA, SItem *pItemB);
uint32	GetItemVarSize(const SItem &it);

uint32	GetNewItemVarSize(const SItem &it);

struct SItemBoxContaner
{
	SItemBoxContaner()
	{
		memset(m_Item, 0, sizeof(SItem) * MAX_BOXITEM_NUMBER);
		memset(m_nQuality, 0, sizeof(int32) * MAX_BOXITEM_NUMBER);
		m_nCount = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddItemType(SItemType &it, int32 iQuality)
	{
		m_Item[m_nCount].m_ItemIndex = it.ToSerial();
		m_nQuality[m_nCount] = iQuality;
		m_nCount++;
	}

	SItem	m_Item[MAX_BOXITEM_NUMBER];
	int32	m_nQuality[MAX_BOXITEM_NUMBER];
	int32	m_nCount;
	uint32	m_uDropType;
};

struct MajiangArgInfo
{
	MajiangArgInfo()
	{
		memset(this, 0, sizeof(MajiangArgInfo));
	}
	PLAYER_EQUIP equip1;
	PLAYER_EQUIP equip2;
	PLAYER_EQUIP equip3;
	uchar*		pPaiType;
	uint32*		pPaiTypeCount;
	int32*		pSoulType;
};

struct SHOP_INFO_t
{
	char			m_ShopName[MAX_SHOP_NAME];
	uchar			m_StallNumOpened;
	uchar			m_StallNumOnSale;
	uchar			m_Type;
	SPlayerShopGuid	m_ID;
	GUID_t			m_OwnerGuid;
	char			m_OwnerName[MAX_CHARACTER_NAME];
	uint32			m_Year;
	uchar			m_Month;
	uchar			m_Day;
	char			m_ShopDesc[MAX_SHOP_DESC_SIZE];
	uchar			m_bIsInFavor;

	SHOP_INFO_t()
	{
		memset(this, 0, sizeof(SHOP_INFO_t));
		m_ID.Reset();
	}

	static uint32 GetSize()
	{
		return	sizeof(char) * MAX_SHOP_NAME +
				sizeof(uchar) +
				sizeof(uchar) +
				sizeof(uchar) +
				SPlayerShopGuid::GetSize() +
				sizeof(GUID_t) +
				sizeof(char) * MAX_CHARACTER_NAME +
				sizeof(uint32) +
				sizeof(uchar) +
				sizeof(uchar) +
				sizeof(char) * MAX_SHOP_DESC_SIZE +
				sizeof(uchar);
	}

	void Send(SendStream &oStream) const;
	void Reci(RecieveStream &iStream) const;
	
};

//玩家身上的商店文件夹中的元素
struct SPlayerShopElement
{
	short	m_nShopId;
	short	m_nIndex;
	uint32	m_ItemId;

	SPlayerShopElement()
	{
		Clear();
	}

	void Clear()
	{
		m_nShopId = INVALID_ID;
		m_nIndex = INVALID_ID;
		m_ItemId = 0;
	}

	SPlayerShopElement& operator= (const SPlayerShopElement &value)
	{
		this->m_nShopId = value.m_nShopId;
		this->m_nIndex = value.m_nIndex;
		this->m_ItemId = value.m_ItemId;
		return *this;
	}

	BOOL operator==(const SPlayerShopElement &right)
	{
		return ((this->m_nShopId == right.m_nShopId) 
			&& (this->m_nIndex == right.m_nIndex) 
			&& (this->m_ItemId == right.m_ItemId));
	}

	static uint32 GetSize()
	{
		return	sizeof(short) + sizeof(short) + sizeof(uint32);
	}

	void Send(SendStream &oStream) const;

	void Reci(RecieveStream &iStream) const;
};

//玩家身上的商店文件夹
struct SPlayerShopFolder
{
	uint32 m_count;	
	int32 m_index;//最后一个元素的位置

	SPlayerShopElement m_list[MAX_SHOP_ELEMENT_NUMBER];

	SPlayerShopFolder()
	{
		Clear();
	}

	void Clear()
	{
		for(int32 i = 0; i < MAX_SHOP_ELEMENT_NUMBER; ++i)
		{
			m_list[i].m_nShopId = INVALID_ID;
			m_list[i].m_nIndex = INVALID_ID;
			m_list[i].m_ItemId = INVALID_ID;
		}

		m_count = 0;
		m_index = -1;
	}

	void Read(char *pIn, int32 BuffLength);

	void Write(char *pOut, int32 &OutLength, int32 BuffLength);

	BOOL AddElement(const SPlayerShopElement& element);

	BOOL DelElement(const SPlayerShopElement& element);

	BOOL UpdateElement(const SPlayerShopElement& element);

};


#endif
