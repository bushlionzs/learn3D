/*$T MapServer/Server/Item/ItemRuler.h GC 1.140 10/10/07 10:07:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _ITEM_RULER_H_
#define _ITEM_RULER_H_

#include "TabDefine_Map_Item.h"
#include "Item_Base.h"
#include "Item_Helper.h"
#include "Item_Ruler.h"

struct ItemLogRecordInfo;

class	Monster;
class	Player;
class	CaculateMonsterExpRuler
{
public:
	uint32	CaculateBaseExp(int32 iMonsterLevel, int32 iKillerLevel, uint32 MonsterBaseExp, int32 TeamCount);
};

class	CheckItemRuler
{
public:
	static BOOL CheckRuler(eITEM_RULER_LIST ruler, const char &iRuler);
	static BOOL	CheckTypeRuler(eITEM_RULER_LIST ruler, const uint32 uItemIndex);
};

class	CaculateMonsterDropRuler
{
public:
	static eBOX_DISTRIBUTE_RULER	GetMonsterDropRuler(Monster *pMonster);
	static BOOL			CaculateCommOwnerList(Monster *pMonster);
	static BOOL			CaculateCommDropRuler(Monster *pMonster, eBOX_DISTRIBUTE_RULER DropRuler);
	static BOOL			CaculateBossDropRuler(Monster *pMonster, eBOX_DISTRIBUTE_RULER DropRuler);
	static BOOL			CaculateHuoDongBossDropRuler(Monster *pMonster, eBOX_DISTRIBUTE_RULER DropRuler);
	static BOOL			DropItemToTeam(Monster *pMonster, Obj_ItemContaner *pObjItemContainer);
};


class Obj_ItemRuler
{
public:
	enum FADE_OUT_TYPE { FADE_OUT_PERSION, FADE_OUT_TEAM, FADE_OUT_NOFADE, };

public:
	void	CreateItemFromMonsterDrop(int32	iMonsterID,	int32 iPlayerLvl,int32 iFadeoutType,float fControlValue, Obj_ItemContaner &OutContaner);
};

class	CreateItemRuler
{
public:
	static BOOL	CreateEquipProperty(SItemType itemType,int32 iPlayerJob,SItem &it,int32	iMonsterLvl = 0,int32 iMonsterType = 0);
	static BOOL	CreateGemProperty(SItemType itemType, SItem &it);
	static BOOL	CreateGemProperty(uint32 TableIndex, SItem &it);
	static BOOL	CreateMedicProperty(SItemType itemType, SItem &it);
	static BOOL	CreateTaskItemProperty(SItemType itemType, SItem &it);
	static BOOL	CreateMaterialProperty(SItemType itemType, SItem &it);
	static BOOL	CreateQuestItemProperty(SItemType itemType, SItem &it);
	static BOOL	CreateStoreMapProperty(SItemType itemType, SItem &it);
	static BOOL	CreateExtraBagProperty(SItemType itemType, SItem &it);

private:
	static BOOL	CaculateDropEquipEffectProperty(SItem &it,int32 iPlayerJob = -1,int32 iMonsterLvl = 0,int32 iMonsterType = 0);
	static BOOL	CaculateCreateEquipEffectProperty(SItem &it, int32 iPlayerJob = 0);
	static BOOL	CaculateEquipEffectProperty(SItem &it, int32 iPlayerLvl = 0);
	static BOOL CaculateEquipProperty(SItem& it);
	static BOOL CaculateEquipPropertyStrategy_1(SItem& it);//非橙装蓝属性随机
	static BOOL CaculateEquipPropertyStrategy_2(SItem& it);//橙装蓝属性随机
};


#endif
