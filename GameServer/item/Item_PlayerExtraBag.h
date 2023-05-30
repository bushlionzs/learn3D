/*$T MapServer/Server/Item/PlayerExtraBag.h GC 1.140 10/10/07 10:07:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */

//扩展背包中的物品

#ifndef _HUMAN_ITEM_EXTRABAG_H_
#define _HUMAN_ITEM_EXTRABAG_H_
#include "Item_Container.h"
#include "Item_PlayerBaseContainer.h"
class	PlayerArchive;

class	Player;

class PlayerExtraBag :
	public PlayerBaseContainer
{
	Item			*m_pExtraBagItem;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual BOOL	Init(const SItemContainerInit *pInit);

	virtual BOOL	IsInContainer(uint32 uBagIndex);

	virtual BOOL	IsCanUse();

	virtual BOOL	IsValid();

	virtual int32	GetContainerSize();

	virtual Item	*GetItem(const int32 nIndex);

/*
-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/
private:
	BOOL	SetDBDirty(int32 OffSet);

};
#endif
