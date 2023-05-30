/*$T MapServer/Server/Item/ItemInterface.h GC 1.140 10/10/07 10:07:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __ItemInterface_H__
#define __ItemInterface_H__

#include "TypeDefine.h"
#include "item/Item_Container.h"
#include "StructDB.h"

class	Player;
class	Item;
class	ItemContainer;
struct STradeItemList;
struct ItemLogRecordInfo;
struct _CREATEITEM_INIT;
struct ItemLogRecordInfo;
struct SItemBoxContaner;

class	ItemInterface
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	ItemInterface();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	~	ItemInterface();

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	static ItemInterface &GetInstance()
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		static ItemInterface	instance;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		return instance;
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	BOOL	EraseItem(ItemLogRecordInfo *pLogParam, Player *pPlayer, ItemContainer *pDestContainer, uint32 uSlot);
	BOOL	EraseBagItemBySlot
		(
			ItemLogRecordInfo	*pLogParam,
			Player			*pPlayer,
			uint32			uSlot,
			BOOL			bCheckEquipLock = TRUE,
			uint32			uCount = 0
		);
	BOOL	EraseBankItemBySlot(ItemLogRecordInfo *pLogParam, Player *pPlayer, uint32 uSlot);
	BOOL	EraseEquipItemBySlot(ItemLogRecordInfo *pLogParam, Player *pPlayer, uint32 uSlot);
	BOOL	EraseBagItemByIndex(ItemLogRecordInfo *pLogParam, Player *pPlayer, uint32 uItemIndex, uint32 uCount);
	BOOL	EraseBagItemByItemList(ItemLogRecordInfo *pLogParam, Player *pPlayer, SItemList &List);

	BOOL	DropBagItem(ItemLogRecordInfo *pLogParam, Player *pPlayer, uint32 uSlot);
	BOOL	DropEquip(ItemLogRecordInfo *pLogParam, Player *pPlayer, PLAYER_EQUIP uEquipPoint);

	BOOL	CreateMultiItemToInventory
		(
			ItemLogRecordInfo	*pLogParam,
			Player			*pPlayer,
			uint32			uItemIndex,
			uint32			uCount,
			uchar			bBind = 0
		);
	BOOL	CreateItemToBagByItemIndex
		(
			ItemLogRecordInfo	*pLogParam,
			Player			*pPlayer,
			uint32			uItemIndex,
			uint32			&uSlot,
			uchar			bBind = 0
		);
	BOOL	CreateItemToBagByINIT
		(
			ItemLogRecordInfo	*pLogParam,
			Player			*pPlayer,
			_CREATEITEM_INIT	*pInit,
			uint32			&uSlot,
			uchar			&bRetBind ,
			uchar			bBind = 0	
		);
	BOOL	CreateItemToContainer
		(
			ItemLogRecordInfo	*pLogParam,
			uint32			uItemIndex,
			ItemContainer		*pDestContainer,
			BOOL			&bNewEmptyPos,
			uint32			&uConIndex,
			int32			nDestIndex = INVALID_INDEX
		);

	BOOL	RecieveItemToInventory(ItemLogRecordInfo *pLogParam, Player *pPlayer, SItem *pItem);
	BOOL	ReceiveBagItemList(ItemLogRecordInfo *pLogParam, Player *pPlayer, SItemList &List);
	BOOL	RecieveItemToInventory
		(
			ItemLogRecordInfo	*pLogParam,
			Player			*pPlayer,
			ItemContainer		*pContainer,
			uint32			uIndex
		);

	BOOL	DecBagItemLayCount(ItemLogRecordInfo *pLogParam, Player *, uint32 uSlot, uint32 uCount = 1);
	BOOL	IncBagItemLayCount(ItemLogRecordInfo *pLogParam, Player *, uint32 uSlot, uint32 uCount = 1);

	int32	MoveItemToBag(ItemLogRecordInfo *pLogParam, Player *pPlayer, ItemContainer *pContainer, uint32 uSlot);
	int32	MoveItemInSameContainer
		(
			ItemLogRecordInfo	*pLogParam,
			Player			*pPlayer,
			ItemContainer		*pContainer,
			uint32			uSrcSlot,
			uint32			uDstSlot
		);
	int32	MoveItemBt2Containers
		(
			ItemLogRecordInfo	*pLogParam,
			Player			*pPlayer,
			ItemContainer		*pSrcCon,
			uint32			uSrcSlot,
			ItemContainer		*pDstCon,
			uint32			uDstSlot = INVALID_INDEX
		);
	int32	MoveItemToHumanBag
		(
			ItemLogRecordInfo	*pLogParam,
			Player			*pSrc,
			Player			*pDst,
			ItemContainer		*pSrcCon,
			uint32			uSrcSlot
		);
	int32	MoveItemToHumanEmptyPos
		(
			ItemLogRecordInfo	*pLogParam,
			Player			*pSrc,
			Player			*pDst,
			ItemContainer		*pSrcCon,
			uint32			uSrcSlot
		);

	int32	ExchangeItem
		(
			ItemLogRecordInfo	*pLogParam,
			Player			*pPlayer,
			Player			*pDestHuman,
			ItemContainer		*pSourContainer,
			int32			nSourIndex,
			ItemContainer		*pDestContainer,
			int32			nDestIndex
		);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	void	TryWriteIBCostLog(ItemLogRecordInfo	*pLogParam, Player *pPlayer, uchar uBindType);
	BOOL	EraseBagItemBySlot_i(Player *pPlayer, uint32 uSlot, Item *pReturnItem, uchar& uBindType, BOOL bCheckEquipLock = TRUE, uint32 uCount = 0);
	int32	EraseBagItem_i(Player *pPlayer, ItemContainer *pContainer, uint32 uItemIndex, int32 uCount, BOOL bCareIBLog = FALSE, uint32 OPType = 0);
	int32	CreateItem_i(Item *pTemplateItem, ItemContainer *pDestContainer, int32 nDestIndex = INVALID_INDEX);
	BOOL	CreateItem_i
		(
			uchar			bBind,
			ItemContainer		*pDestContainer,
			uint32			&uConIndex,
			_CREATEITEM_INIT	*pInit = NULL
		);
	BOOL	CreateItemToContainer_i
		(
			uint32		uItemIndex,
			uchar		bBind,
			ItemContainer	*pDestContainer,
			BOOL		&bNewEmptyPos,
			uint32		&uConIndex,
			int32		nDestIndex = INVALID_INDEX
		);
	BOOL	CreateItemToBagByItemIndex_i
		(
			Player	*pPlayer,
			uint32	uItemIndex,
			uint32	&uSlot,
			uchar	bBind = 0,
			BOOL	bNotifyChangeItem = TRUE
		);

/*
 -----------------------------------------------------------------------------------------------------------------------
 装备相关玩法
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	//装备打孔
	int32			AddHole(Player *pPlayer, uint32 BagIndex);

	//装备绑定/铭刻
	int32			EquipBind(Player *pPlayer, uint32 BagIndex);

	//装备麻将牌
	int32			EquipChangePai(Player *pPlayer, uint32 BagIndex, uint32 GemBagIndex);

	//装备打造（类似于做装备）
	int32			EquipRemould(Player *pPlayer, uint32 BagIndex, uint32 nMaterialScore);

	//装备换牌
	int32			EquipChangePai(Player *pPlayer, uint32 BagIndex1, uint32 BagIndex2, uint32 GemBagIndex);

	//装备升星
	int32			EquipLevelup(Player	*pPlayer,uint32	BagIndex,EQUIP_LEVEL_TYPE nType,uint32 nGemID,uint32 nGemCount);

	//使用装备
	int32			UseEquip(Player *pPlayer, int32 BagIndex);

	//装备镶嵌
	int32			UseGem(Player *pPlayer, uint32 BagIndex, uint32 GemBagIndex, uint32 GemHolePos);

	// 使用物品
	int32			UseItem(Player	*pPlayer,ID_t nBagIndex,ObjID_t	nTargetObj,const GLPos &posTarget, SHorseGuid const &guidTargetPet,ID_t TargetItem);

	//锁定装备
	BOOL			LockEquip(Player *pPlayer, uint32 BagIndex);

	// 解锁装备
	BOOL			UnLockEquip(Player *pPlayer, uint32 BagIndex);

	//更新装备伤害点
	void			UpdataEquipDamagePoint(Player *pPlayer, int32 nType);

	//更新装备过期属性
	void			UpdateEquipTermEnd(Player *pPlayer);

	//更新装备过期属性
	BOOL			UpdateItemContainerTermEnd(Player *pPlayer,ItemContainer *pContainer,BOOL bNotifyClient,uchar byPosType);

	//装备颜色改变
	EQUIP_WANFA_RESULT	Equip_ColorChange(Player *pPlayer, uint32 BagIndex);

	//紫装打造
	EQUIP_WANFA_RESULT	Equip_PurpleRework(Player *pPlayer, uint32 BagIndex);

	//紫装备属性随机
	void			Equip_PurpleAttrRand(SItem &item) const;

	//紫装备随机率
	uint32			Equip_PurpleRandIndex() const;

	//紫装备属性刷新
	void			Equip_PurpleAttrRefresh(SItem &item) const;

	//取得紫装备属性值
	int32			Equip_PurpleAttrValue(const SItem &item, uint32 index) const;

	//宝石加工
	EQUIP_WANFA_RESULT	GemRework(Player *pPlayer, uint32 BagIndex);

	//宝石合成
	EQUIP_WANFA_RESULT	GemSynthesize(Player *pPlayer, uint32 BagIndex);

	//宝石卸载
	EQUIP_WANFA_RESULT	GemUninst(Player *pPlayer, uint32 BagIndex, uchar HolePos);

	//装备拷贝
	EQUIP_WANFA_RESULT	EquipCopy(Player *pPlayer,uint32 srcBagIndex,uint32	tarBagIndex,const SItemGuid &targGUID,uchar type);

	//装备回收
	EQUIP_WANFA_RESULT EquipRecall(Player* pPlayer, uint32 BagIndex);

	//多彩宝石回收
	EQUIP_WANFA_RESULT ItemRecall(Player* pPlayer, uint32 BagIndex);

	//装备蓝属性吸收
	EQUIP_WANFA_RESULT EquipBlueIn(Player *pPlayer,uint32 equipIndex,uint32 itemIndex,const SItemGuid	&itemGUID);

	//装备蓝属性附加
	EQUIP_WANFA_RESULT EquipBlueAdd(Player *pPlayer,uint32	equipIndex,uint32 itemIndex,const SItemGuid &itemGUID);

	//物品蓝属性合成
	EQUIP_WANFA_RESULT ItemBlueSyn(Player *pPlayer,const uint32 itemIndex1,const uint32 itemIndex2);
	

	//装备转化
	EQUIP_WANFA_RESULT			EquipSwitch(Player *pPlayer, uint32 BagIndex);

	void			UpdateItemUnLockTime(Player *pPlayer);

	//装备蓝属性全部随机
	void			Equip_BlueAttrRand(SItem &item);

	//从表中恢复装备的基础蓝属性
	void			ResetEquipBlueAttFromTB(Player *pPlayer, uint32 BagIndex);

	//根据属性ID重置属性值
	void			SetEquipExtAttrByAttrId(Player *pPlayer, uint32 BagIndex,uchar attrType,int16 attrVal);

	//更换形象
	int32 CharChangeAppearance(Player *pPlayer,uint32 BagIndex,int32 nPortraitID,uchar byFaceModel,uchar byHairModel);

	//橙装打造蓝属性
	EQUIP_WANFA_RESULT NewEquipProduce(Player *pPlayer,
										const uint32 nEquipItemIndex,
										const uint32 nAtlasBagIndex,
										const uint32 nAdditiveBagIndex
										);

	//橙装蓝属性随机
	void	Equip_NewEquipBlueAttrRand(SItem &item,const NEW_EQUIP_PRODUCE_TB* pProduceTab,const BOOL bHasAdditive);

	//星座铭刻
	EQUIP_WANFA_RESULT	EquipConstBind(Player *pPlayer, uint32 nEquipBagIndex, uint32 nItemBagIndex);	

	//荣誉铭刻
	EQUIP_WANFA_RESULT	EquipHonorBind(Player *pPlayer,uint32 BagIndex,uint32 nGemID);	

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	BOOL	ActivateItem_i(Player *pPlayer);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	int32	CalcBagSpace(Player *pPlayer) const;
	int32	CalcInventoryItemCount(Player *pPlayer, uint32 uItemIndex) const;
	int32	CalcEquipItemCount(Player *pPlayer, uint32 uItemIndex) const;
	int32	GetItemLockStatus(Player *pPlayer, uint32 uItemIndex) const;

	BOOL	CanBagReceiveItemList(Player *pPlayer, SItemList &List) const;
	BOOL	CanBagEraseItemList(Player *pPlayer, SItemList &List) const;
	BOOL	CanReceiveExchangeItemList(Player *pPlayer, STradeItemList &List) const;

	BOOL	VerifyItem(Player *pPlayer);
	BOOL	IsHaveEquip(Player *pPlayer, const SItemGuid& ItemGuid) const;
	BOOL	IsHaveItem(Player *pPlayer, uint32 itemIndex) const;
	BOOL	IsVisualPart(Player *pPlayer, PLAYER_EQUIP EquipPoint) const;
	BOOL	IsCarrayItem(Player *pPlayer, uint32 ItemType, uint32 ItemCount) const;
	BOOL	HaveEnoughBagItemSpace
		(
			Player	*pPlayer,
			uint32	uItemIndex,
			int32	Number,
			int32	&NewSpace,
			uchar	bBindType = BIND_NONE
		) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	int32	CalcBagItemSpace_i
		(
			Player		*pPlayer,
			ItemContainer	*pItemContainer,
			uint32		uItemIndex,
			int32		Number,
			int32		&NewSpace,
			uchar		bBindType = BIND_NONE
		) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	void	LockItem(ItemContainer *pContainer, int32 nIndex);
	void	UnlockItem(ItemContainer *pContainer, int32 nIndex);
	int32	ExchangeEquipItem(ItemContainer *pSourContainer, int32 nSourIndex, int32 nDestIndex);
	int32	SplitItem
		(
			ItemContainer	*pSourContainer,
			uchar		uSourIndex,
			uchar		uCount,
			ItemContainer	*pDestContainer,
			int32		nDestIndex = INVALID_INDEX
		);
	BOOL	SplitItem
		(
			Player		*pPlayer,
			ItemContainer	*pSourContainer,
			uchar		uSourIndex,
			uchar		uCount,
			ItemContainer	*pDestContainer,
			int32		nDestIndex,
			int32		opType = 0
		);
	int32	SplitItemToEmptyPos
		(
			Player		*pPlayer,
			ItemContainer	*pSourContainer,
			uchar		uSourIndex,
			uchar		uCount,
			Player		*pDestHuman
		);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	BOOL	EraseItem_i(Player *pPlayer, ItemContainer *pDestContainer, uchar uIndex, BOOL bCheckEquipLock = TRUE, uint32 uCount = 0);
	int32	MoveItem_i(ItemContainer *pDestContainer, SItem *pSourItem, int32 nDestIndex = INVALID_INDEX);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	ItemContainer	*GetEquipContainer(Player *pPlayer) const;
	ItemContainer	*GetBagContainer(Player *pPlayer, uint32 uSlot) const;
	ItemContainer	*GetBagItemContain(Player *pPlayer, SItemGuid *pItemID) const;
	ItemContainer	*GetBagByExtraContainPos(Player *pPlayer, uint32 uExtraIndex) const;
	ItemContainer	*GetBagItemContain(Player *pPlayer, SItemGuid *pItemID, int32 &nBagIndex) const;

	Item		*GetExtraContainerItem(Player *pPlayer, uint32 uSlot) const;
	Item		*GetExtraBagFromBagIndex(Player *pPlayer, uint32 uSlot) const;
	Item		*GetBankItem(Player *pPlayer, uint32 BankIndex) const;

	Item		*GetBagItem(Player *pPlayer, uint32 uSlot) const;
	Item		*GetEquip(Player *pPlayer, PLAYER_EQUIP EquipPoint) const;

	int32		GetBagItemPosByGUID(Player *pPlayer, SItemGuid guid) const;
	int32		GetBagItemPosByType(Player *pPlayer, uint32 uItemIndex) const;

	int32		GetBagItemCountByLessLevel(Player *pPlayer, uint32 uLevel,uint32 nDataId)const;
	int32		GetEquipItemCountByLessLevel(Player *pPlayer, uint32 uLevel,uint32 nDataId)const;

	int32		GetBagItemCountByLessHole(Player *pPlayer,uint32 uHole,uint32 nDataId)const;
	int32		GetEquipItemCountByLessHole(Player *pPlayer,uint32 uHole,uint32 nDataId)const;

	int32		GetBagItemCountByLessGem(Player *pPlayer,uint32 uGem,uint32 nDataId)const;
	int32		GetEquipItemCountByLessGem(Player *pPlayer,uint32 uGem,uint32 nDataId)const;

	int32		GetBagItemCountByLessSoulBind(Player *pPlayer,uint32 uBindLevel,uint32 nDataId)const;
	int32		GetEquipItemCountByLessSoulBind(Player *pPlayer,uint32 uBindLevel,uint32 nDataId)const;

	int32		GetBagItemCountByLessPurple(Player *pPlayer,uint32 uPurpleCount,uint32 nDataId)const;
	int32		GetEquipItemCountByLessPurple(Player *pPlayer,uint32 uPurpleCount,uint32 nDataId)const;

	BOOL		SetInventoryItemDurability(Player *pPlayer, uint32 uSlot, int32 iDur);
	BOOL		SetBagItemCurMaxDur(Player *pPlayer, uint32 uSlot, int32 iDur);
	BOOL		SetInventoryItemIdentify(Player *pPlayer, uint32 uSlot);
	BOOL		SetInventoryItemFreeParam(Player *pPlayer, uint32 uSlot, uint32 Start, int32 Type, int32 value);
	BOOL		SetBagEquipDur(Player *pPlayer, uint32 uSlot, int32 iDur);
	BOOL		SetCurBagEquipMaxDur(Player *pPlayer, uint32 uSlot, int32 iDur);
	BOOL		SetBagEquipBind(Player *pPlayer, uint32 uSlot, uchar bBindType);
	BOOL		SetEquipDur(Player *pPlayer, PLAYER_EQUIP EquipPoint, int32 iDur);
	BOOL		SetCurEquipMaxDur(Player *pPlayer, PLAYER_EQUIP EquipPoint, int32 iDur);
	BOOL		SetEquipDamagePoint(Player *pPlayer, PLAYER_EQUIP EquipPoint, uint32 nDamagePoint);
	BOOL		SetEquipBind(Player *pPlayer, PLAYER_EQUIP EquipPoint, uchar bBindType);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	int32	MoveSpliceItem
		(
			ItemContainer	*pSourContainer,
			uchar		uSourIndex,
			ItemContainer	*pDestContainer,
			int32		nDestIndex
		);
	int32	ExchangeItem
		(
			ItemContainer	*pSourContainer,
			int32		nSourIndex,
			ItemContainer	*pDestContainer,
			int32		nDestIndex
		);
	int32	CopyItem
		(
			ItemContainer	*pSourContainer,
			int32		nSourIndex,
			ItemContainer	*pDestContainer,
			int32		nDestIndex = INVALID_INDEX
		);
	int32	CopyItemFromItemBox
		(
			SItemBoxContaner *pSourceContainer,
			int32		nSourceIndex,
			BOOL		&bNewPos,
			ItemContainer	*pDestContainer,
			int32		nDestIndex = INVALID_INDEX
		);
	int32	SpliceItem
		(
			ItemContainer	*pSourContainer,
			uchar		uSourIndex,
			ItemContainer	*pDestContainer,
			int32		nDestIndex
		);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	int32	MoveItem_i
		(
			ItemContainer	*pSourContainer,
			int32		nSourIndex,
			ItemContainer	*pDestContainer,
			int32		nDestIndex = INVALID_INDEX
		);
	int32	MoveItem_i
		(
			ItemContainer	*pSourContainer,
			int32		nSourIndex,
			BOOL		&bNewPos,
			ItemContainer	*pDestContainer,
			int32		nDestIndex = INVALID_INDEX
		);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	BOOL	SetItemLayedNum(ItemContainer *pContainer, int32 nIndex, int32 nCount);
	BOOL	DecItemLayedNum(ItemContainer *pContainer, int32 nIndex, int32 nCount = 1);
	BOOL	IncItemLayedNum(ItemContainer *pContainer, int32 nIndex, int32 nCount = 1);
	BOOL	SetItemDurability(ItemContainer *pContainer, int32 nIndex, int32 nDur);
	BOOL	SetItemIdent(ItemContainer *pContainer, int32 nIndex);
	BOOL	SetItemDamagePoint(ItemContainer *pContainer, int32 nIndex, int32 nPoint);
	BOOL	SetItemCurMaxDur(ItemContainer *pContainer, int32 nIndex, int32 nDur);
	BOOL	SetItemBind(ItemContainer *pContainer, int32 nIndex);
	BOOL	SetItemPWLock(ItemContainer *pContainer, int32 nIndex, BOOL bLock);
	BOOL	SetItemCreator(ItemContainer *pContainer, int32 nIndex, const char *CreatorName);
	BOOL	SetItemFreeParam(ItemContainer *pContainer, int32 nIndex, uint32 start, int32 type, int32 value);
	int32	GetItemFreeParamValue(ItemContainer *pContainer, int32 nIndex, uint32 Start, eITEM_PARAM_VALUE &ipv);
	BOOL	AddItemProperty(ItemContainer *pContainer, int32 nIndex, _ITEM_PROPERTY iA);
	BOOL	DelItemProperty(ItemContainer *pContainer, int32 nIndex, _ITEM_PROPERTY iA);
	BOOL	DelGemInfo(ItemContainer *pContainer, int32 nIndex, int32 GemIndex);
	BOOL	AddGemInfo(ItemContainer *pContainer, int32 nIndex, int32 GemIndex, uint32 GemHolePos);

	BOOL	Bind(ItemContainer *pContainer, int32 nIndex, uchar bindType);
	BOOL	ItemLevelup(ItemContainer *pContainer, int32 nIndex, int32 nLevel);
	BOOL	EquipHonorBindLevelup(ItemContainer *pContainer, int32 nIndex, int32 nLevel);
	BOOL	SetItemAttr(ItemContainer *pContainer, int32 nIndex, int32 nAtt, _ITEM_PROPERTY iA);
	BOOL	SetItemPaiType(ItemContainer *pContainer, int32 nIndex, uchar nPaiType);
	BOOL	ItemLevelBind(ItemContainer *pContainer, int32 nIndex, uint32 nBindLevel);
	BOOL	SetItemScore(ItemContainer *pContainer, int32 nIndex, uint32 nScore);
	BOOL	SetEquipFromType(ItemContainer *pContainer, int32 nIndex, uchar nType);
	BOOL	SetItemBeginTime(ItemContainer *pContainer, int32 nIndex);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	BOOL	AddHole(ItemContainer *pContainer, int32 nIndex);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	BOOL	SetItemValue(ItemContainer *pContainer, int32 nIndex, const _HORSE_DB_LOAD *pPet);
	BOOL	SetHorseGUID(ItemContainer *pContainer, int32 nIndex, SHorseGuid GUID);
	BOOL	SetDataID(ItemContainer *pContainer, int32 nIndex, int32 ID);
	BOOL	SetName(ItemContainer *pContainer, int32 nIndex, const char *pName);
	BOOL	SetNick(ItemContainer *pContainer, int32 nIndex, const char *pNick);
	BOOL	SetLevel(ItemContainer *pContainer, int32 nIndex, int32 level);
	BOOL	SetTakeLevel(ItemContainer *pContainer, int32 nIndex, int32 takeLevel);
	BOOL	SetAttackType(ItemContainer *pContainer, int32 nIndex, int32 attackType);
	BOOL	SetAIType(ItemContainer *pContainer, int32 nIndex, int32 AIType);
	BOOL	SetCampData(ItemContainer *pContainer, int32 nIndex, const SCampData *pCamp);
	BOOL	SetHP(ItemContainer *pContainer, int32 nIndex, int32 hp);
	BOOL	SetLife(ItemContainer *pContainer, int32 nIndex, int32 Life);
	BOOL	SetPetType(ItemContainer *pContainer, int32 nIndex, uchar PetType);
	BOOL	Set_Property_Generation(ItemContainer *pContainer, int32 nIndex, uchar Gen);
	BOOL	SetHappiness(ItemContainer *pContainer, int32 nIndex, uchar byHappiness);
	BOOL	Set_Property_StrPer(ItemContainer *pContainer, int32 nIndex, int32 strper);
	BOOL	SetSmartnessPer(ItemContainer *pContainer, int32 nIndex, int32 conper);
	BOOL	SetMindPer(ItemContainer *pContainer, int32 nIndex, int32 dexper);
	BOOL	SetConstitutionPer(ItemContainer *pContainer, int32 nIndex, int32 intper);
	BOOL	Set_Property_GrowRate(ItemContainer *pContainer, int32 nIndex, float rate);
	BOOL	SetRemainPoint(ItemContainer *pContainer, int32 nIndex, int32 rPoint);
	BOOL	SetExp(ItemContainer *pContainer, int32 nIndex, uint32 exp);
	BOOL	SetLvl1Attr(ItemContainer *pContainer, int32 nIndex, PLAYER_PROPERTY_LEVEL1 type, int32 value);
	BOOL	SetSkill(ItemContainer *pContainer, int32 nIndex, uint32 SkillIndex, SHorseSkill skill);
	BOOL	SetMatingFlag(ItemContainer *pContainer, int32 nIndex, BOOL bFlag);
	BOOL	SetComposeFlag(ItemContainer *pContainer, int32 nIndex, BOOL bFlag);
	BOOL	SetStrengthPoint(ItemContainer *pContainer, int32 nIndex, int32 iPoint);
	BOOL	SetSmartnessPoint(ItemContainer *pContainer, int32 nIndex, int32 iPoint);
	BOOL	SetMindPoint(ItemContainer *pContainer, int32 nIndex, int32 iPoint);
	BOOL	SetConstitutionPoint(ItemContainer *pContainer, int32 nIndex, int32 iPoint);

	BOOL	LockPet(Player *pPlayer, const SHorseGuid&petGUID);
	BOOL	UnLockPet(Player *pPlayer, const SHorseGuid&petGUID);
	int32	GetPetLockStatus(Player *pPlayer, const SHorseGuid&petGUID) const;

	void	UpdatePetUnLockTime(Player *pPlayer);

	BOOL	MovePetToBank(Player *pPlayer, const SHorseGuid&petGUID);
	BOOL	MovePetFromBank(Player *pPlayer, const SHorseGuid&petGUID);
	BOOL	ActiveBankPetSlot(Player *pPlayer);
	uint32	GetActiveBankPetSlot(Player *pPlayer);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetBindType() const
	{
		return m_uBind;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetSlotByItemGUID() const
	{
		return 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetSlotByItemIndex() const
	{
		return 0;
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	const SItem	*GetItem(Player *pPlayer, uint32 uDBPos);
	BOOL		IsEquipCon2BagCon(Player *pPlayer, const ItemContainer *pSrcCon, const ItemContainer *pDstCon);
	BOOL		IsBagCon2EquipCon(Player *pPlayer, const ItemContainer *pSrcCon, const ItemContainer *pDstCon);
	BOOL		IsBagCon2BagCon(Player *pPlayer, const ItemContainer *pSrcCon, const ItemContainer *pDstCon);
	void		SetItemGUID(ItemContainer *pContainer, int32 nIndex, SItemGuid *pGuid);
	void		SetItemGUID(ItemContainer *pContainer, int32 nIndex, SHorseGuid*pGuid);

	BOOL		GenItemGUID(SItemGuid &ig);
	BOOL		GenItemGUID(SHorseGuid&ig);

	void		FillAndSaveItemLog(ItemLogRecordInfo *pLogParam, Player *pPlayer = NULL, Item *pItem = NULL);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	uint32	m_uBind;
};

#define sItemInterface	ItemInterface::GetInstance()
#endif
