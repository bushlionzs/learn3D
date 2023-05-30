/*$T MapServer/Server/Item/ItemHelper.cpp GC 1.140 10/10/07 10:07:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Item_Helper.h"
#define MAX_ITEM_RAND_QUOATE	100000000




STSerialHelper::STSerialHelper()
{
	m_SN = 0;
}

STSerialHelper::STSerialHelper( uint32 uiSN )
{
	m_SN = uiSN;
}

STSerialHelper::STSerialHelper( char *pStr )
{
	__GUARD__	KCheck(pStr != NULL);

	m_SN = atoi(pStr);

	__UNGUARD__
}

BOOL STSerialHelper::GetItemTypeStruct( SItemType &it )
{
	it.m_Class = GetItemClass();
	it.m_Index = GetItemIndex();
	it.m_Type = GetItemType();

	return TRUE;
}

SItemType STSerialHelper::GetItemTypeStruct()
{
	SItemType	it;

	it.m_Class = GetItemClass();
	it.m_Index = GetItemIndex();
	it.m_Type = GetItemType();

	return it;
}

eITEM_CLASS STSerialHelper::GetItemClass()
{
	return(eITEM_CLASS) GetClassBySerial(m_SN);
}

void STSerialHelper::SetClass( eITEM_CLASS rh )
{
	m_SN = rh * 1000000 + m_SN % 1000000;
}

uint32 STSerialHelper::GetItemType()
{
	return GetTypeBySerial(m_SN);
}

void STSerialHelper::SetItemType( uint32 uiType )
{
	m_SN = m_SN + (uiType - GetItemType()) * 100;
}

uint32 STSerialHelper::GetItemIndex()
{
	return GetIndexBySerial(m_SN);
}

void STSerialHelper::SetItemIndex( uint32 uiIndex )
{
	m_SN = m_SN + (uiIndex - GetItemIndex());
}
