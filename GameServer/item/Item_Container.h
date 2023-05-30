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

	//��������ת��Ϊ��������
	virtual uint32 ConIndex2BagIndex(uint32 uConIndex){return uConIndex;}
	//��������ת��Ϊ��������
	virtual uint32 BagIndex2ConIndex(uint32 uBagIndex){	return uBagIndex;}
	//��Ʒ�Ƿ���������
	virtual BOOL	IsInContainer(uint32 uBagIndex);
	//�Ƿ���ʹ��
	virtual BOOL	IsCanUse();
	//�Ƿ���Ч
	virtual BOOL	IsValid();
	//�õ���������
	int32			GetContainerType();
	void			Clear();
	void			ClearItemByIndex(int32 nIndex);

	int32		StallOrderToIndex(int32 iStallOrder);
	void		SetBankPetStallOrder(int32 nIndex, int32 iStallOrder);
	virtual BOOL		ForceLockPet(int32 nIndex);
	virtual BOOL		ForceUnlockPet(int32 nIndex);

/*
-----------------------------------------------------------------------------------------------------------------------
ͨ�ýӿ�
-----------------------------------------------------------------------------------------------------------------------
*/
protected:
	//����������ָ��λ��(nIndex)������Ʒָ��(�޸ĵ���һ��ָ��)
	virtual BOOL	SetItem(const int32 nIndex, const Item *pItem);
	//����������ָ����Ʒ�󶨷�ʽΪBIND_NORMAL
	virtual BOOL	SetItemBind(int32 nIndex);
	//ɾ����Ʒ
	virtual BOOL	EraseItem(uint32 uIndex);

/*
-----------------------------------------------------------------------------------------------------------------------
Horse��ؽӿ�
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
 ��Ʒ��ؽӿ�
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	//��ʯ��ж
	virtual BOOL	DelGemInfo(int32 nIndex, int32 GemIndex);
	//װ����Ƕ��ʯ
	virtual BOOL	AddGemInfo(int32 nIndex, int32 GemIndex, uint32 GemHolePos);
	//װ�����
	virtual BOOL	AddHole(int32 nIndex);
	//װ����
	virtual BOOL	Bind(int32 nIndex, uchar bindType);
	//װ������
	virtual BOOL	ItemLevelup(int32 nIndex, int32 nLevel);
	//��������
	virtual BOOL	EquipHonorBindLevelup(int32 nIndex, int32 nLevel);
	//����װ������(װ���������װ����)
	virtual BOOL	SetItemProperty(int32 nIndex, int32 nAtt, _ITEM_PROPERTY iA);
	//����������ָ��λ��(nIndex)������Ʒ����(�޸ĵ�������)
	virtual BOOL	SetItemValue(int32 nIndex, SItem *pItem);
	//������Ʒ��
	virtual BOOL	SetItemPWLock(int32 nIndex, BOOL bLock);	
	//������Ʒ�;�
	virtual BOOL	SetItemDurability(int32 nIndex, int32 nDur);
	//������Ʒ�˺���
	virtual BOOL	SetItemDamagePoint(int32 nIndex, int32 nPoint);
	//������Ʒ����;�
	virtual BOOL	SetItemCurMaxDur(int32 nIndex, int32 nDur);
	//������Ʒ�������
	virtual BOOL	SetItemIdent(int32 nIndex);
	//����������ָ����Ʒ����������
	virtual BOOL	SetItemCreator(int32 nIndex, const char *CreatorName);
	//������Ʒ����
	virtual BOOL	SetItemFreeParam(int32 nIndex, uint32 start, int32 type, int32 value);
	//����װ������
	virtual BOOL	AddItemProperty(int32 nIndex, _ITEM_PROPERTY iA);
	//ɾ��װ������
	virtual BOOL	DelItemProperty(int32 nIndex, _ITEM_PROPERTY iA);
	//װ���齫��
	virtual BOOL	SetItemPaiType(int32 nIndex, uchar nPaiType);
	//װ����
	virtual BOOL	ItemLevelBind(int32 nIndex, uint32 nBindLevel);
	virtual BOOL	SetItemScore(int32 nIndex, uint32 nScore);
	//������Ʒ��������
	virtual BOOL	SetItemLayedNum(int32 nIndex, int32 nCount);
	//������Ʒ��������
	virtual BOOL	DecItemLayedNum(int32 nIndex, int32 nCount = 1);
	//������Ʒ��������	
	virtual BOOL	IncItemLayedNum(int32 nIndex, int32 nCount = 1);
	//����װ��
	virtual BOOL	SetEquipFromType(int32 nIndex, uchar nType);
	virtual BOOL	SetItemBeginTime(int32 nIndex);
	virtual BOOL	SetItemGuid(int32 nIndex, SItemGuid *pGUID);
	//����װ��
	virtual BOOL	LockEquip(int32 nIndex);
	//����װ��
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
