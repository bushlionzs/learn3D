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
	//��Ʒ�Ƿ���������
	virtual BOOL	IsInContainer(uint32 uBagIndex);
	//��������ת��Ϊ��������
	virtual uint32	ConIndex2BagIndex(uint32 uConIndex);
	//��������ת��Ϊ��������
	virtual uint32	BagIndex2ConIndex(uint32 uBagIndex);

protected:
	//װ�����
	virtual BOOL	AddHole(int32 nIndex);
	//װ����
	virtual BOOL	Bind(int32 nIndex, uchar bindType);
	//װ������
	virtual BOOL	ItemLevelup(int32 nIndex, int32 nLevel);
	//װ����������
	virtual BOOL	EquipHonorBindLevelup(int32 nIndex, int32 nLevel);
	//����װ������(װ���������װ����)
	virtual BOOL	SetItemProperty(int32 nIndex, int32 nAtt, _ITEM_PROPERTY iA);
	//װ���齫��
	virtual BOOL	SetItemPaiType(int32 nIndex, uchar nPaiType);
	//������Ʒ�˺���
	virtual BOOL	SetItemDamagePoint(int32 nIndex, int32 nPoint);
	//������Ʒ����;�
	virtual BOOL	SetItemCurMaxDur(int32 nIndex, int32 nDur);
	//����������ָ��λ��(nIndex)������Ʒ����(�޸ĵ�������)
	virtual BOOL	SetItemValue(int32 nIndex, SItem *pItem);
	//����������ָ����Ʒ�󶨷�ʽΪBIND_NORMAL
	virtual BOOL	SetItemBind(int32 nIndex);
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
	//����������ָ��λ��(nIndex)������Ʒָ��(�޸ĵ���һ��ָ��)
	virtual BOOL	SetItem(const int32 nIndex, const Item *pItem);
	//������Ʒ��������
	virtual BOOL	SetItemLayedNum(int32 nIndex, int32 nCount);
	//������Ʒ��������
	virtual BOOL	DecItemLayedNum(int32 nIndex, int32 nCount = 1);
	//������Ʒ��������	
	virtual BOOL	IncItemLayedNum(int32 nIndex, int32 nCount = 1);
	//ɾ����Ʒ
	virtual BOOL	EraseItem(uint32 uIndex);
	//������Ʒ�;�
	virtual BOOL	SetItemDurability(int32 nIndex, int32 nDur);
	//װ����Ƕ��ʯ
	virtual BOOL	AddGemInfo(int32 nIndex, int32 GemIndex, uint32 GemHolePos);
	//��ʯ��ж
	virtual BOOL	DelGemInfo(int32 nIndex, int32 GemIndex);
	//װ����
	virtual BOOL	ItemLevelBind(int32 nIndex, uint32 nBindLevel);
	virtual BOOL	SetItemScore(int32 nIndex, uint32 nScore);
	//����װ��
	virtual BOOL	SetEquipFromType(int32 nIndex, uchar nType);
	//������Ʒ��
	virtual BOOL	SetItemPWLock(int32 nIndex, BOOL bLock);
	//����װ��
	virtual BOOL	LockEquip(int32 nIndex);
	//����װ��
	virtual BOOL	UnLockEquip(int32 nIndex);
	virtual BOOL	SetDBDirty(int32 OffSet);

protected:
	uint32			m_DBOffSet;

};
#endif
