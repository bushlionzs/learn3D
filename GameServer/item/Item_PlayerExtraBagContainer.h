/*$T MapServer/Server/Item/PlayerExtraBagContainer.h GC 1.140 10/10/07 10:07:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */

//��չ��������

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

	//������Ʒ��������
	virtual BOOL	SetItemLayedNum(int32 nIndex, int32 nCount);

	//������Ʒ��������
	virtual BOOL	DecItemLayedNum(int32 nIndex, int32 nCount = 1);

	//������Ʒ��������	
	virtual BOOL	IncItemLayedNum(int32 nIndex, int32 nCount = 1);

	//������Ʒ�;�
	virtual BOOL	SetItemDurability(int32 nIndex, int32 nDur);

	//������Ʒ�˺���
	virtual BOOL	SetItemDamagePoint(int32 nIndex, int32 nPoint);

	//������Ʒ����;�
	virtual BOOL	SetItemCurMaxDur(int32 nIndex, int32 nDur);

	//������Ʒ�������
	virtual BOOL	SetItemIdent(int32 nIndex);

	//������Ʒ����
	virtual BOOL	SetItemFreeParam(int32 nIndex, uint32 start, int32 type, int32 value);

	//����װ������
	virtual BOOL	AddItemProperty(int32 nIndex, _ITEM_PROPERTY iA);

	//ɾ��װ������
	virtual BOOL	DelItemProperty(int32 nIndex, _ITEM_PROPERTY iA);

	//װ����Ƕ��ʯ
	virtual BOOL	AddGemInfo(int32 nIndex, int32 GemIndex, uint32 GemHolePos);

	//��ʯ��ж
	virtual BOOL	DelGemInfo(int32 nIndex, int32 GemIndex);

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

	//װ���齫��
	virtual BOOL	SetItemPaiType(int32 nIndex, uchar nPaiType);

	//װ����
	virtual BOOL	ItemLevelBind(int32 nIndex, uint32 nBindLevel);

	virtual BOOL	SetItemScore(int32 nIndex, uint32 nScore);

	//����װ��
	virtual BOOL	SetEquipFromType(int32 nIndex, uchar nType);

/*
-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/
private:
	BOOL	SetDBDirty(int32 OffSet);

};
#endif
