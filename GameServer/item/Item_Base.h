/*$T MapServer/Server/Item/Item.h GC 1.140 10/10/07 10:07:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __ITEM_H__
#define __ITEM_H__

#include "TypeDefine.h"
#include "gameobject/Object.h"
struct _HORSE_DB_LOAD;
struct SHorseGuid;
struct SHorseSkill;

struct _CREATEITEM_INIT
{
	uint32	m_nItemIndex;
	uchar	m_nEquipFromType;
};

struct _PLAYER_EQUIPCREATE_INIT :
	public _CREATEITEM_INIT
{
	uint32	m_nEquipScore;
	uint32	m_nPlayerJob;
};

struct _PLAYER_EQUIPDROP_INIT :
	public _CREATEITEM_INIT
{
	uint32	m_nMonsterLevel;
	uint32	m_nMonsterType;
};

class	CItemInit
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
	CItemInit(const SItem *pItem)
	{
		m_pItem = pItem;
		m_pPet = NULL;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CItemInit(const _HORSE_DB_LOAD *pPet)
	{
		m_pPet = pPet;
		m_pItem = NULL;
	}

	const SItem		*m_pItem;
	const _HORSE_DB_LOAD	*m_pPet;
};

enum eITEM_DATA_TYPE { IDT_ITEM, IDT_PET, };

struct SCampData;
class Item
{
	friend class	ItemInterface;
	friend class	ItemContainer;
	friend struct Obj_ItemContaner;
	friend class	ItemInstanceManager;

public:
	Item();
	~	Item();

	eITEM_DATA_TYPE GetDataType(){return m_Type;}
	_HORSE_DB_LOAD* GetPet(){return m_pPet;}
	SItem *GetItemData(){return m_pItem;};

	inline SHorseGuid	GetHorseGUID();
	inline int32		GetDataID();
	inline const char	*GetName() const;
	inline const char	*GetNick() const;
	inline int32		GetLevel() const;
	inline int32		GetNeedLevel() const;
	inline int32		GetTakeLevel() const;
	inline int32		GetAttackType() const;
	inline int32		GetAIType() const;
	inline const SCampData *GetCampData() const;
	inline uchar		GetPetType() const;
	inline uchar		GetGeneration() const;
	inline uchar		GetHappiness() const;

	inline int32		GetStrengthPer() const;
	inline int32		GetSmartnessPer() const;
	inline int32		GetMindPer() const;
	inline int32		GetConstitutionPer() const;
	inline int32		GetStrengthPoint() const;
	inline int32		GetSmartnessPoint() const;
	inline int32		GetMindPoint() const;
	inline int32		GetConstitutionPoint() const;
	inline float		GetGrowRate() const;
	inline int32		IsCheckup();
	inline int32		GetRemainPoint() const;
	inline int32		GetExp() const;
	inline int32		GetStallOrder() const;
	inline int32		GetLvl1Attr(PLAYER_PROPERTY_LEVEL1 type) const;
	inline SHorseSkill	GetSkill(uint32 SkillIndex);
	inline BOOL			IsMating() const;
	inline BOOL			IsCompose() const;
	inline int32		GetHorseModelID() const;
	inline BOOL			IsPetLocked() const;
	inline uint32		GetPetUnLockTime() const;
	inline void			SetPetUnLock() const;
	inline void			SetPetStatus(int32 nStatus) const;
	inline int32		GetHP() const{	return 0;};
	inline int32		Get_BaseProperty_MaxHP() const{return 0;};
	inline int32		GetLife() const{return 0;};

	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/

	void				SaveValueTo(SItem *pItem);
	void				SaveValueTo(_HORSE_DB_LOAD *pPet);
	BOOL				IsCanEquipBind() const;
	BOOL				IsRuler(eITEM_RULER_LIST ruler) const;
	uchar				GetRuler() const;
	BOOL				IsBound() const;
	BOOL				IsNormalBound() const;
	BOOL				IsGoldBound() const;
	uint32				GetPrice() const;
	uint32				GetSellPrice() const;
	int32				GetItemFreeParam(uint32 start, eITEM_PARAM_VALUE &ipv);
	int32				GetItemFreeParamType();
	int32				GetItemTableParamValue();
	int32				GetConsumeValue();
	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/

	inline SItemGuid		GetGUID();
	inline uint32			GetItemTableIndex() const;
	inline uchar			GetItemClass() const;
	inline uchar			GetItemType() const;
	inline uchar			GetItemIndex() const;
	inline BOOL				IsEquipLocked() const;
	inline uint32			GetEquipUnLockTime() const;
	inline int32			GetSetNum() const;
	inline uchar			GetMaxSetCount() const;
	inline uchar			GetEquipPoint() const;
	inline uchar			GetMaxDurPoint() const;
	inline uchar			GetRequireLevel() const;
	inline uchar			GetCurLevel() const;
	inline uchar			GetCurLevelType() const;
	inline uchar			GetGemSlotMax() const;
	inline uchar			GetModelID() const;
	inline uchar			GetDurability() const;
	inline uchar			GetCurMaxDurability() const;
	inline uint32			GetTermTime() const;
	inline BOOL				IsTermEnd() const;
	inline uchar			GetPropertyCount() const;
	uchar					GetPurplePropertyCount() const;
	inline uint16			GetDamagePoint() const;
	inline uchar			GetItemBindType() const;
	inline BOOL				GetItemIdentify() const;
	inline uchar			GetEquipGemCount() const;
	inline uchar			GetAffixSpellCount() const;
	inline uchar			GetEffectSpellCount() const;
	inline _ITEM_EFFECT_SKILL	*GetEffectSpell(uint32 pos) const;
	inline uchar			GetReqJob() const;
	inline uchar			GetBaseGemHole() const;
	inline uchar			GetCurGemHole() const;
	inline uchar			GetEquipBindLevel();
	inline void				SetEquipBindLevel(uchar uLevel);
	inline uchar			GetEquipHonorBindLevel();
	inline void				SetEquipHonorBindLevel(uchar uLevel);
	inline uint32			GetEquipGem(int32 nPos) const;
	inline uint32			GetEquipScore() const;
	inline uchar			GetEquipFromType() const;
	inline const _ITEM_PROPERTY		GetEquipProperty(uchar nIndex) const;
	inline const SItemGemInfo	GetEquipGemInfo(uchar nIndex) const;
	inline uchar			GetEquipPaiType() const;
	inline BOOL				IsEquipCanOp(uchar opType);
	uchar					GetColorType() const;
	inline uchar			GetItemLevel() const;
	inline uchar			GetReqSpellLevel() const;
	inline int32			GetReqSpell() const;
	inline int32			GetScriptID() const;
	inline int32			GetSpellID() const;
	inline uchar			GetTargetType() const;
	inline BOOL				IsBroadCast() const;
	inline const _ITEM_PROPERTY		GetGemProperty(uint32 i) const;
	inline uint32			GetGemReqNum() const;
	inline const _GEM_REQ_ATT	GetReqGemProperty(int32 nPos) const;
	inline uint32			GetReqEquip(int32 nEquipType) const;
	inline uint32			GetGemShowLevel() const;
	inline int32			GetGemUsePrice();
	inline uint32			GetExtraBagSellPrice() const;
	inline uint32			GetExtraBagBasePrice() const;
	inline uint32			GetExtraBagValidTime() const;
	inline uint32			GetExtraBagRemainTime() const;
	inline BOOL				IsExtraBagCanUse() const;
	inline uint32			GetExtraBagSize() const;
	inline uint32			GetExtraBagBeginTime() const;
	inline BOOL			IsValid() const;
	inline int32		GetLayedNum() const;
	inline int32		GetMaxLayedNum() const;
	inline BOOL			IsFull() const;
	inline BOOL			IsPWLock() const;
	inline BOOL			IsOverTime() const;
	inline uchar		GetMedicLevel(void);
	inline void			SetMedicLevel(const uchar cLevel);

	// rj 2010-8-23 天赋等级和个人等级获取
	inline int32		GetReqInherenceLevel();
	inline int32		GetReqPersonLevel();

	//星座铭刻
	inline int32				GetEquipConstCount();
	inline SItemConstInfo*		GetEquipConst();

public:
	void SetInExchange(BOOL bIsInExchange){	m_bIsInExchange = bIsInExchange;}
	void SetTermTime(uint32 newTime);
	void SetItemFreeParam( uint32 start, eITEM_PARAM_VALUE &ipv, int32 value);

	BOOL	Init(const CItemInit *pInit);
	BOOL	IsFree();
	BOOL	IsEquip() const;
	BOOL	IsLock(){return m_bLock;};
	BOOL	IsCanLay() const;
	BOOL	IsCanExchange();
	BOOL	IsInExchange(){return m_bIsInExchange;}

//protected:
	void	 Lock(){m_bLock = TRUE;}
	void	Unlock(){m_bLock = FALSE;}
protected:
	void	SetItemValue(SItem *pItem);
	void	Clear();

private:
	eITEM_DATA_TYPE	m_Type;
	SItem		*m_pItem;
	_HORSE_DB_LOAD	*m_pPet;
	BOOL		m_bLock;
	BOOL		m_bIsInExchange;
};

#include "Item_Base.inl"

struct STradeItemList
{
	int32	m_ListCount;
	Item	*m_ListItem[EXCHANGE_BOX_SIZE + EXCHANGE_PET_BOX_SIZE];

	STradeItemList(){memset(this, 0, sizeof(STradeItemList));}
	void AddItem(Item *it);
	void Init(){memset(this, 0, sizeof(STradeItemList));}
};

struct Obj_ItemContaner
{
	Obj_ItemContaner()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(m_Item, 0, sizeof(SItem) * MAX_DROP_ITEM_NUMBER);
		m_nCount = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddItem(SItem &item)
	{
		KCheck(!item.IsNullType());
		memcpy(&m_Item[m_nCount], &item, sizeof(SItem));
		m_nCount++;
	}

	SItem	m_Item[MAX_DROP_ITEM_NUMBER];
	int32	m_nCount;
	uint32	m_uDropType;
};
#endif
