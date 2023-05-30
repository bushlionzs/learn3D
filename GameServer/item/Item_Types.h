/*$T MapServer/Server/Item/ItemTypes.h GC 1.140 10/10/07 10:07:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _ITEM_TYPES_H_
#define _ITEM_TYPES_H_

#include "TypeDefine.h"

#define MAX_MONSTER_DROPBOX	10

struct MONSTER_DROPCONTENT
{
	MONSTER_DROPCONTENT()
	{
		m_nItemValue = 0;
		m_nCycle = 0;
		m_nItemValue = 0;
		m_pDropContent = NULL;
	}
	int32	m_nItemValue;
	int32	m_nCycle;
	int32	m_nItemCount;
	int32	*m_pDropContent;
};

struct SMonsterDropBoxs
{
	SMonsterDropBoxs()
	{
		memset(m_DropBox, 0, sizeof(int32) * MAX_MONSTER_DROPBOX);
	}
	int32	m_DropBox[MAX_MONSTER_DROPBOX];
};

struct MONSTER_DROPS
{
	MONSTER_DROPS()
	{
		m_nDropNum = 0;
		memset(m_DropItem, 0, sizeof(int32) * MAX_MONSTER_DROPBOX);
	}
	int32	m_nDropNum;
	int32	m_DropItem[MAX_MONSTER_DROPBOX];
};

#define MAX_DROPBOX_CARRAGE	100
#define ITEMBOX_DROP_RANGE	10
#define MAX_ITEM_TABLE_QUALITYS 10
#define MAX_ITEM_TABLE_VALUES	10
#define MAX_MONSTER_VALUE	100000000
#define MAX_ITEM_BOX_POOL	5000
#define MAX_OBJ_ITEM_POOL	5000
#define MAX_ATT_COUNT		1000

#endif
