/*$T MapServer/Server/Item/HorseContainer.h GC 1.140 10/10/07 10:07:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _ITEM_HORSE_CONTAINER_H_
#define _ITEM_HORSE_CONTAINER_H_

#include "Item_Container.h"
#include "StructDB.h"

class	PlayerArchive;
struct _HORSE_DB_LOAD;
class	Player;

class HorseContainer :
	public ItemContainer
{
public:
	virtual BOOL	Init(const SItemContainerInit *pInit);

protected:
	virtual BOOL	SetItem(const int32 nIndex, const Item *pItem);
	virtual BOOL	EraseItem(uint32_t uIndex);
	virtual BOOL	SetItemBind(int32 nIndex);

private:
	BOOL	SetDBDirty(int32 index);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	virtual BOOL	SetItemValue(int32 nIndex, const _HORSE_DB_LOAD *pPet);
	//设置物品叠加数量
	virtual BOOL	SetItemLayedNum(int32 nIndex, int32 nCount);
	//减少物品叠加数量
	virtual BOOL	DecItemLayedNum(int32 nIndex, int32 nCount = 1);
	//增加物品叠加数量	
	virtual BOOL	IncItemLayedNum(int32 nIndex, int32 nCount = 1);
	virtual BOOL	SetLvl1Property(int32 nIndex, PLAYER_PROPERTY_LEVEL1 type, int32 value);
	virtual BOOL	SetSkill(int32 nIndex, uint32_t SkillIndex, SHorseSkill skill);
	virtual BOOL	SetMatingFlag(int32 iIndex, BOOL bFlag);
	virtual BOOL	LockPet(int32 nIndex);
	virtual BOOL	ForceLockPet(int32 nIndex);
	virtual BOOL	UnlockPet(int32 nIndex);
	virtual BOOL	ForceUnlockPet(int32 nIndex);
	virtual BOOL	Set_Property_GrowRate(int32 nIndex, float rate);
	virtual BOOL	SetRemainPoint(int32 nIndex, int32 rPoint);
	virtual BOOL	SetExp(int32 nIndex, uint32_t exp);
	virtual BOOL	SetLevel(int32 nIndex, int32 level);
	virtual BOOL	SetTakeLevel(int32 nIndex, int32 takeLevel);
	virtual BOOL	SetAttackType(int32 nIndex, int32 attackType);
	virtual BOOL	SetBHVClass(int32 nIndex, int32 AIType);
	virtual BOOL	SetHorseGUID(int32 nIndex, SHorseGuid GUID);
	virtual BOOL	SetDataID(int32 nIndex, int32 ID);
	virtual BOOL	SetName(int32 nIndex, const char *pName);
	virtual BOOL	SetNick(int32 nIndex, const char *pNick);
	virtual BOOL	SetCampData(int32 nIndex, const SCampData *pCamp);
	virtual BOOL	SetPetType(int32 nIndex, uint8_t PetType);
	virtual BOOL	Set_Property_Generation(int32 nIndex, uint8_t Gen);
	virtual BOOL	SetHappiness(int32 nIndex, uint8_t byHappiness);
	virtual BOOL	SetStrengthPer(int32 nIndex, int32 strper);
	virtual BOOL	SetSmartnessPer(int32 nIndex, int32 conper);
	virtual BOOL	SetMindPer(int32 nIndex, int32 dexper);
	virtual BOOL	SetConstitutionPer(int32 nIndex, int32 intper);

};
#endif
