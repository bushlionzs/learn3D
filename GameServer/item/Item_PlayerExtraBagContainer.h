/*$T MapServer/Server/Item/PlayerExtraBagContainer.h GC 1.140 10/10/07 10:07:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */

//扩展背包容器

#ifndef _HUMAN_ITEM_EXTRACONTAINER_H_
#define _HUMAN_ITEM_EXTRACONTAINER_H_
#include "Item_Container.h"
#include "Item_PlayerBaseContainer.h"

class	PlayerArchive;
class	Player;

class PlayerExtraBagContainer :
	public PlayerBaseContainer
{

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual BOOL	Init(const SItemContainerInit *pInit);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:

	virtual BOOL	SetItem(const int32 nIndex, const Item *pItem);

	virtual BOOL	SetItemValue(int32 nIndex, SItem *pItem);

	virtual BOOL	SetItemBeginTime(int32 nIndex);

	//设置物品叠加数量
	virtual BOOL	SetItemLayedNum(int32 nIndex, int32 nCount);

	//减少物品叠加数量
	virtual BOOL	DecItemLayedNum(int32 nIndex, int32 nCount = 1);

	//增加物品叠加数量	
	virtual BOOL	IncItemLayedNum(int32 nIndex, int32 nCount = 1);

	//设置物品耐久
	virtual BOOL	SetItemDurability(int32 nIndex, int32 nDur);

	//设置物品伤害度
	virtual BOOL	SetItemDamagePoint(int32 nIndex, int32 nPoint);

	//设置物品最大耐久
	virtual BOOL	SetItemCurMaxDur(int32 nIndex, int32 nDur);

	//设置物品鉴定标记
	virtual BOOL	SetItemIdent(int32 nIndex);

	//设置物品参数
	virtual BOOL	SetItemFreeParam(int32 nIndex, uint32 start, int32 type, int32 value);

	//增加装备属性
	virtual BOOL	AddItemProperty(int32 nIndex, _ITEM_PROPERTY iA);

	//删除装备属性
	virtual BOOL	DelItemProperty(int32 nIndex, _ITEM_PROPERTY iA);

	//装备镶嵌宝石
	virtual BOOL	AddGemInfo(int32 nIndex, int32 GemIndex, uint32 GemHolePos);

	//宝石拆卸
	virtual BOOL	DelGemInfo(int32 nIndex, int32 GemIndex);

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

	//装备麻将牌
	virtual BOOL	SetItemPaiType(int32 nIndex, uchar nPaiType);

	//装备绑定
	virtual BOOL	ItemLevelBind(int32 nIndex, uint32 nBindLevel);

	virtual BOOL	SetItemScore(int32 nIndex, uint32 nScore);

	//设置装备
	virtual BOOL	SetEquipFromType(int32 nIndex, uchar nType);

/*
-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/
private:
	BOOL	SetDBDirty(int32 OffSet);

};
#endif
