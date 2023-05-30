/*$T MapServer/Server/Item/PlayerBaseContainer.h GC 1.140 10/10/07 10:07:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _PLAYER_ITEM_BASE_CONTAINER_H_
#define _PLAYER_ITEM_BASE_CONTAINER_H_
#include "Item_Container.h"

class	PlayerArchive;
class	Player;

class PlayerBaseContainer :
	public ItemContainer
{
public:
	virtual BOOL	Init(const SItemContainerInit *pInit);
	//物品是否在容器内
	virtual BOOL	IsInContainer(uint32 uBagIndex);
	//容器索引转换为背包索引
	virtual uint32	ConIndex2BagIndex(uint32 uConIndex);
	//背包索引转换为容器索引
	virtual uint32	BagIndex2ConIndex(uint32 uBagIndex);

protected:
	//装备打孔
	virtual BOOL	AddHole(int32 nIndex);
	//装备绑定
	virtual BOOL	Bind(int32 nIndex, uchar bindType);
	//装备升星
	virtual BOOL	ItemLevelup(int32 nIndex, int32 nLevel);
	//装备荣誉铭刻
	virtual BOOL	EquipHonorBindLevelup(int32 nIndex, int32 nLevel);
	//设置装备属性(装备打造或做装备）)
	virtual BOOL	SetItemProperty(int32 nIndex, int32 nAtt, _ITEM_PROPERTY iA);
	//装备麻将牌
	virtual BOOL	SetItemPaiType(int32 nIndex, uchar nPaiType);
	//设置物品伤害度
	virtual BOOL	SetItemDamagePoint(int32 nIndex, int32 nPoint);
	//设置物品最大耐久
	virtual BOOL	SetItemCurMaxDur(int32 nIndex, int32 nDur);
	//重置容器中指定位置(nIndex)处的物品数据(修改的是数据)
	virtual BOOL	SetItemValue(int32 nIndex, SItem *pItem);
	//重置容器中指定物品绑定方式为BIND_NORMAL
	virtual BOOL	SetItemBind(int32 nIndex);
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
	//重置容器中指定位置(nIndex)处的物品指针(修改的是一个指针)
	virtual BOOL	SetItem(const int32 nIndex, const Item *pItem);
	//设置物品叠加数量
	virtual BOOL	SetItemLayedNum(int32 nIndex, int32 nCount);
	//减少物品叠加数量
	virtual BOOL	DecItemLayedNum(int32 nIndex, int32 nCount = 1);
	//增加物品叠加数量	
	virtual BOOL	IncItemLayedNum(int32 nIndex, int32 nCount = 1);
	//删除物品
	virtual BOOL	EraseItem(uint32 uIndex);
	//设置物品耐久
	virtual BOOL	SetItemDurability(int32 nIndex, int32 nDur);
	//装备镶嵌宝石
	virtual BOOL	AddGemInfo(int32 nIndex, int32 GemIndex, uint32 GemHolePos);
	//宝石拆卸
	virtual BOOL	DelGemInfo(int32 nIndex, int32 GemIndex);
	//装备绑定
	virtual BOOL	ItemLevelBind(int32 nIndex, uint32 nBindLevel);
	virtual BOOL	SetItemScore(int32 nIndex, uint32 nScore);
	//设置装备
	virtual BOOL	SetEquipFromType(int32 nIndex, uchar nType);
	//设置物品锁
	virtual BOOL	SetItemPWLock(int32 nIndex, BOOL bLock);
	//锁定装备
	virtual BOOL	LockEquip(int32 nIndex);
	//解锁装备
	virtual BOOL	UnLockEquip(int32 nIndex);
	virtual BOOL	SetDBDirty(int32 OffSet);

protected:
	uint32			m_DBOffSet;

};
#endif
