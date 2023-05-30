/*$T MapServer/Server/Item/ItemManager.h GC 1.140 10/10/07 10:07:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _ITEM_MANAGER_H_
#define _ITEM_MANAGER_H_

#include "TypeDefine.h"
#include "script/LuaSystem.h"
//#include "LogDefine.h"

class	Map;
class	Player;
struct _CREATEITEM_INIT;

class ItemManager
{
private:
	BOOL	CreateEquipFromTable_i(SItemType it, SItem &item);
	BOOL	CreateGemFromTable_i(SItemType it, SItem &item);
	BOOL	CreateGemFromTable_i(uint32 TableIndex, SItem &item);
	BOOL	CreateMedicFromTable_i(SItemType it, SItem &item);
	BOOL	CreateQuestFromTable_i(SItemType it, SItem &item);
	BOOL	CreateExtraBagFromTable_i(SItemType it, SItem &item);
	BOOL	CreateEquipFromTable_i(SItem &item, _CREATEITEM_INIT *pInit);
	BOOL	CreateGemFromTable_i(SItem &item, _CREATEITEM_INIT *pInit);
	BOOL	CreateMedicFromTable_i(SItem &item, _CREATEITEM_INIT *pInit);
	BOOL	CreateQuestFromTable_i(SItem &item, _CREATEITEM_INIT *pInit);
	BOOL	CreateExtraBagFromTable_i(SItem &item, _CREATEITEM_INIT *pInit);

public:
	BOOL	Init();
	int32	GenItemSN();
	BOOL	GenItemGuid(SItemGuid &ig);
	BOOL	CreateItem(SItemType it, SItem &item);
	BOOL	CreateItem(uint32 ItemSerial, SItem &item);
	BOOL	CreateItem(SItem &item, _CREATEITEM_INIT *pInit = NULL);

private:
	FastLock	m_Lock;
	int32		m_nLastGenItemSerial;
	ID_t		m_WorldId;
	ID_t		m_ServerId;
	ItemSerialKeyMK	*m_pSerialMK = nullptr;
};

extern ItemManager	*g_pItemMgr;
#endif
