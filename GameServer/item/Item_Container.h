/*$T MapServer/Server/Item/ItemContainer.h GC 1.140 10/10/07 10:07:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __ITEMCONTAINER_H__
#define __ITEMCONTAINER_H__

#include "TypeDefine.h"
#include "Item_Base.h"

struct SItemContainerInit
{
	int32	m_nContainerSize;
};

struct SHorseContainerInit :
	public SItemContainerInit
{
	PlayerArchive		*m_pPlayerDB;
	eITEM_CONTAINER_TYPE	m_ICTType;
};

struct SPlayerContainerInit :
	public SItemContainerInit
{
	PlayerArchive		*m_pPlayerDB;
	eITEM_CONTAINER_TYPE	m_ICTType;
	uint32			m_DBOffSet;
};

struct SPlayerItemExtrBagInit :
	public SItemContainerInit
{
	PlayerArchive		*m_pPlayerDB;
	Item			*m_pExtraBagItem;
	eITEM_CONTAINER_TYPE	m_ICTType;
	uint32			m_DBOffSet;
};

struct SPlayerItemExtraContainerInit :
	public SItemContainerInit
{
	PlayerArchive		*m_pPlayerDB;
	eITEM_CONTAINER_TYPE	m_ICTType;
	uint32			m_DBOffSet;
};

/*
-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/


class	ItemContainer
{
	friend class	ItemInterface;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	ItemContainer();
	virtual		~ItemContainer();
	virtual BOOL	Init(const SItemContainerInit *pInit);
	virtual uint32	CalcItemFreeSlot();
	virtual BOOL	IsFree();
	virtual uint32	CalcExchangeItemSlot();
	virtual int32	GetFreeItemIndex();

	virtual int32 GetContainerSize(){return m_nContainerSize;}
	virtual BOOL	ExpandSize(const int32 nSize);
	virtual BOOL	SetSize(const int32 nSize);
	virtual int32	GetIndexByGUID(const SItemGuid *pGuid);
	virtual int32	GetIndexByType(const uint32 uType);
	virtual int32	GetIndexByType(const uint32 uType, uint32 emptyCount);
	virtual int32	GetIndexByTypeAndBind(const uint32 uType, uchar bBindType);
	virtual int32	GetIndexByTypeAndBind(const uint32 uType, uint32 emptyCount, uchar bBindType);
	virtual Item	*GetItem(const int32 nIndex);
	virtual int32	GetNoFullItemIndex(uint32 uItemIndex);
	virtual int32	GetNoFullItemIndexAndBind(uint32 uItemIndex, uchar bBindType);
	virtual int32	GetIndexByGUID(const SHorseGuid*pGuid);
	virtual int32	GetValidCount();
	virtual BOOL	ResetHorseStallOrder(int32 nDeleteOrder);

	//容器索引转换为背包索引
	virtual uint32 ConIndex2BagIndex(uint32 uConIndex){return uConIndex;}
	//背包索引转换为容器索引
	virtual uint32 BagIndex2ConIndex(uint32 uBagIndex){	return uBagIndex;}
	//物品是否在容器内
	virtual BOOL	IsInContainer(uint32 uBagIndex);
	//是否能使用
	virtual BOOL	IsCanUse();
	//是否有效
	virtual BOOL	IsValid();
	//得到容器类型
	int32			GetContainerType();
	void			Clear();
	void			ClearItemByIndex(int32 nIndex);

	int32		StallOrderToIndex(int32 iStallOrder);
	void		SetBankPetStallOrder(int32 nIndex, int32 iStallOrder);
	virtual BOOL		ForceLockPet(int32 nIndex);
	virtual BOOL		ForceUnlockPet(int32 nIndex);

/*
-----------------------------------------------------------------------------------------------------------------------
通用接口
-----------------------------------------------------------------------------------------------------------------------
*/
protected:
	//重置容器中指定位置(nIndex)处的物品指针(修改的是一个指针)
	virtual BOOL	SetItem(const int32 nIndex, const Item *pItem);
	//重置容器中指定物品绑定方式为BIND_NORMAL
	virtual BOOL	SetItemBind(int32 nIndex);
	//删除物品
	virtual BOOL	EraseItem(uint32 uIndex);

/*
-----------------------------------------------------------------------------------------------------------------------
Horse相关接口
-----------------------------------------------------------------------------------------------------------------------
*/
protected:
	virtual BOOL	SetMindPoint(int32 nIndex, int32 iPoint);
	virtual BOOL	SetConstitutionPoint(int32 nIndex, int32 iPoint);
	virtual BOOL	LockPet(int32 nIndex);
	virtual BOOL	UnlockPet(int32 nIndex);
	virtual BOOL	SetItemGuid(int32 nIndex, SHorseGuid*pGUID);
	virtual BOOL	Set_Property_Generation(int32 nIndex, uchar Gen);
	virtual BOOL	SetHappiness(int32 nIndex, uchar byHappiness);
	virtual BOOL	SetStrengthPer(int32 nIndex, int32 strper);
	virtual BOOL	SetSmartnessPer(int32 nIndex, int32 conper);
	virtual BOOL	SetMindPer(int32 nIndex, int32 dexper);
	virtual BOOL	SetConstitutionPer(int32 nIndex, int32 intper);
	virtual BOOL	Set_Property_GrowRate(int32 nIndex, float rate);
	virtual BOOL	SetRemainPoint(int32 nIndex, int32 rPoint);
	virtual BOOL	SetExp(int32 nIndex, uint32 exp);
	virtual BOOL	SetLvl1Property(int32 nIndex, PLAYER_PROPERTY_LEVEL1 type, int32 value);
	virtual BOOL	SetItemValue(int32 nIndex, const _HORSE_DB_LOAD *pPet);
	virtual BOOL	SetHorseGUID(int32 nIndex, SHorseGuid GUID);
	virtual BOOL	SetDataID(int32 nIndex, int32 ID);
	virtual BOOL	SetName(int32 nIndex, const char *pName);
	virtual BOOL	SetNick(int32 nIndex, const char *pNick);
	virtual BOOL	SetLevel(int32 nIndex, int32 level);
	virtual BOOL	SetTakeLevel(int32 nIndex, int32 takeLevel);
	virtual BOOL	SetAttackType(int32 nIndex, int32 attackType);
	virtual BOOL	SetBHVClass(int32 nIndex, int32 BHVClass);
	virtual BOOL	SetCampData(int32 nIndex, const SCampData *pCamp);
	virtual BOOL	SetPetType(int32 nIndex, uchar PetType);
	virtual BOOL	SetSkill(int32 nIndex, uint32 SkillIndex, SHorseSkill skill);
	virtual BOOL	SetMatingFlag(int32 iIndex, BOOL bFlag);
	virtual BOOL	SetComposeFlag(int32 iIndex, BOOL bFlag);
	virtual BOOL	SetStrengthPoint(int32 nIndex, int32 iPoint);
	virtual BOOL	SetSmartnessPoint(int32 nIndex, int32 iPoint);

/*
 -----------------------------------------------------------------------------------------------------------------------
 物品相关接口
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	//宝石拆卸
	virtual BOOL	DelGemInfo(int32 nIndex, int32 GemIndex);
	//装备镶嵌宝石
	virtual BOOL	AddGemInfo(int32 nIndex, int32 GemIndex, uint32 GemHolePos);
	//装备打孔
	virtual BOOL	AddHole(int32 nIndex);
	//装备绑定
	virtual BOOL	Bind(int32 nIndex, uchar bindType);
	//装备升星
	virtual BOOL	ItemLevelup(int32 nIndex, int32 nLevel);
	//荣誉铭刻
	virtual BOOL	EquipHonorBindLevelup(int32 nIndex, int32 nLevel);
	//设置装备属性(装备打造或做装备）)
	virtual BOOL	SetItemProperty(int32 nIndex, int32 nAtt, _ITEM_PROPERTY iA);
	//重置容器中指定位置(nIndex)处的物品数据(修改的是数据)
	virtual BOOL	SetItemValue(int32 nIndex, SItem *pItem);
	//设置物品锁
	virtual BOOL	SetItemPWLock(int32 nIndex, BOOL bLock);	
	//设置物品耐久
	virtual BOOL	SetItemDurability(int32 nIndex, int32 nDur);
	//设置物品伤害度
	virtual BOOL	SetItemDamagePoint(int32 nIndex, int32 nPoint);
	//设置物品最大耐久
	virtual BOOL	SetItemCurMaxDur(int32 nIndex, int32 nDur);
	//设置物品鉴定标记
	virtual BOOL	SetItemIdent(int32 nIndex);
	//重置容器中指定物品的主人名字
	virtual BOOL	SetItemCreator(int32 nIndex, const char *CreatorName);
	//设置物品参数
	virtual BOOL	SetItemFreeParam(int32 nIndex, uint32 start, int32 type, int32 value);
	//增加装备属性
	virtual BOOL	AddItemProperty(int32 nIndex, _ITEM_PROPERTY iA);
	//删除装备属性
	virtual BOOL	DelItemProperty(int32 nIndex, _ITEM_PROPERTY iA);
	//装备麻将牌
	virtual BOOL	SetItemPaiType(int32 nIndex, uchar nPaiType);
	//装备绑定
	virtual BOOL	ItemLevelBind(int32 nIndex, uint32 nBindLevel);
	virtual BOOL	SetItemScore(int32 nIndex, uint32 nScore);
	//设置物品叠加数量
	virtual BOOL	SetItemLayedNum(int32 nIndex, int32 nCount);
	//减少物品叠加数量
	virtual BOOL	DecItemLayedNum(int32 nIndex, int32 nCount = 1);
	//增加物品叠加数量	
	virtual BOOL	IncItemLayedNum(int32 nIndex, int32 nCount = 1);
	//设置装备
	virtual BOOL	SetEquipFromType(int32 nIndex, uchar nType);
	virtual BOOL	SetItemBeginTime(int32 nIndex);
	virtual BOOL	SetItemGuid(int32 nIndex, SItemGuid *pGUID);
	//锁定装备
	virtual BOOL	LockEquip(int32 nIndex);
	//解锁装备
	virtual BOOL	UnLockEquip(int32 nIndex);

/*
-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/
protected:
	int32			m_nContainerSize;
	PlayerArchive		*m_pPlayerDB;
	eITEM_CONTAINER_TYPE	m_ICTType;

private:
	Item	m_aItem[MAX_ITEMCONTAINER_SIZE];

};

#endif
