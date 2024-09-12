#include "OgreHeader.h"
#include "application_util.h"

#include "DefineItem.h"
#include "GameTableData.h"
#include "GameTableDefine.h"
#include "GameTableManager.h"
#include "KTable.h"
#include <StructCommandScript.h>
#include <KObjectManager.h>
#include <kplayer.h>
#include <GameDataCharacter.h>



const char* getItemIcon(uint32 idTable)
{

	int32 nItemClass = INVALID_ID;
	nItemClass = GetClassBySerial(idTable);

	switch (nItemClass)
	{
		// 武器WEAPON、防具DEFENCE、饰物ADORN
	case ICLASS_EQUIP:
	{
		const CGameTable* pItem_EquipTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_EQUIP_VISUAL);
		_TABLE_ITEM_EQUIP_VISUAL* info =
			(_TABLE_ITEM_EQUIP_VISUAL*)pItem_EquipTable->GetFieldDataByIndex(idTable);

		if (info == nullptr)
		{
			return nullptr;
		}

		return info->szIcon;

	}
	break;

	// 原料
	case ICLASS_MATERIAL:
		// 药品
	case ICLASS_COMITEM:
	{
		const _TABLE_ITEM_MEDIC* pMedic = NULL;

		// 打开数据表
//			TABLE_DEFINEHANDLE( s_pItem_Medic, TABLE_ITEM_MEDIC );
		const CGameTable* pItem_MedicTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_MEDIC);
		if (NULL == pItem_MedicTable)
		{
			return NULL;
		}

		pMedic = (const _TABLE_ITEM_MEDIC*)pItem_MedicTable->GetFieldDataByIndex((uint32)idTable);
		if (NULL == pMedic)
			return NULL;

		return pMedic->szIcon;
	}
	break;

	// 任务物品
	case ICLASS_TASKITEM:
	{
		const _TABLE_ITEM_TASK* pTask = NULL;

		// 打开数据表
//			TABLE_DEFINEHANDLE( s_pItem_Task, TABLE_ITEM_TASK );
		const CGameTable* pItem_TaskTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_TASK);
		if (NULL == pItem_TaskTable)
		{
			return NULL;
		}

		pTask = (const _TABLE_ITEM_TASK*)pItem_TaskTable->GetFieldDataByIndex((uint32)idTable);
		if (NULL == pTask)
			return NULL;

		return pTask->szIcon;
	}
	break;

	// 宝石
	case ICLASS_GEM:
	{
		const _TABLE_ITEM_GEM* pGem = NULL;

		//打开数据表
//			TABLE_DEFINEHANDLE( s_pItem_Gem, TABLE_ITEM_GEM );
		const CGameTable* pItem_GemTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_GEM);
		if (NULL == pItem_GemTable)
		{
			return NULL;
		}

		//搜索纪录
		pGem = (const _TABLE_ITEM_GEM*)pItem_GemTable->GetFieldDataByIndex((uint32)idTable);
		if (NULL == pGem)
			return NULL;

		return pGem->szIcon;
	}
	break;

	case ICLASS_EXTRABAG:
	{
		const _TABLE_ITEM_EXTBAG* pExtraBagMap = NULL;


		// 打开数据表
//			TABLE_DEFINEHANDLE( s_pItem_ExtraBage_Map, TABLE_ITEM_EXTBAG );
		const CGameTable* pItem_ExtraBage_MapTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_EXTBAG);
		if (NULL == pItem_ExtraBage_MapTable)
		{
			return NULL;
		}

		pExtraBagMap = (const _TABLE_ITEM_EXTBAG*)pItem_ExtraBage_MapTable->GetFieldDataByIndex((uint32)idTable);
		if (NULL == pExtraBagMap)
			return NULL;

		return pExtraBagMap->szIcon;
	}
	break;

	default:
	{
		return nullptr;
	}
	break;
	};	// switch

	return nullptr;
}

bool getItemInfo(uint32_t id, ItemData& data)
{
	int32 nItemClass = INVALID_ID;
	nItemClass = GetClassBySerial(id);

	switch (nItemClass)
	{
		// 武器WEAPON、防具DEFENCE、饰物ADORN
	case ICLASS_EQUIP:
	{
		const CGameTable* pItem_EquipTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_EQUIP_VISUAL);
		_TABLE_ITEM_EQUIP_VISUAL* info =
			(_TABLE_ITEM_EQUIP_VISUAL*)pItem_EquipTable->GetFieldDataByIndex(id);

		if (info == nullptr)
		{
			return false;
		}

		data.icon = info->szIcon;
		data.title = info->szName;
		data.desc = info->szDes;
		data.type = info->szType;
		return true;
	}
	break;

	// 原料
	case ICLASS_MATERIAL:
		// 药品
	case ICLASS_COMITEM:
	{
		const _TABLE_ITEM_MEDIC* pMedic = NULL;

		// 打开数据表
//			TABLE_DEFINEHANDLE( s_pItem_Medic, TABLE_ITEM_MEDIC );
		const CGameTable* pItem_MedicTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_MEDIC);
		if (NULL == pItem_MedicTable)
		{
			return NULL;
		}

		pMedic = (const _TABLE_ITEM_MEDIC*)pItem_MedicTable->GetFieldDataByIndex(id);
		if (NULL == pMedic)
			return NULL;

		data.icon = pMedic->szIcon;
		data.title = pMedic->szName;
		data.desc = pMedic->szDesc;
		return true;
	}
	break;

	// 任务物品
	case ICLASS_TASKITEM:
	{
		const _TABLE_ITEM_TASK* pTask = NULL;

		// 打开数据表
//			TABLE_DEFINEHANDLE( s_pItem_Task, TABLE_ITEM_TASK );
		const CGameTable* pItem_TaskTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_TASK);
		if (NULL == pItem_TaskTable)
		{
			return NULL;
		}

		pTask = (const _TABLE_ITEM_TASK*)pItem_TaskTable->GetFieldDataByIndex(id);
		if (NULL == pTask)
			return NULL;

		data.icon = pTask->szIcon;
		data.title = pTask->szName;
		data.desc = pTask->szDesc;
		return true;
	}
	break;

	// 宝石
	case ICLASS_GEM:
	{
		const _TABLE_ITEM_GEM* pGem = NULL;

		//打开数据表
//			TABLE_DEFINEHANDLE( s_pItem_Gem, TABLE_ITEM_GEM );
		const CGameTable* pItem_GemTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_GEM);
		if (NULL == pItem_GemTable)
		{
			return NULL;
		}

		//搜索纪录
		pGem = (const _TABLE_ITEM_GEM*)pItem_GemTable->GetFieldDataByIndex(id);
		if (NULL == pGem)
			return NULL;

		data.icon = pGem->szIcon;
		data.title = pGem->szName;
		data.desc = pGem->szDesc;
		return true;
	}
	break;

	case ICLASS_EXTRABAG:
	{
		const _TABLE_ITEM_EXTBAG* pExtraBagMap = NULL;


		// 打开数据表
//			TABLE_DEFINEHANDLE( s_pItem_ExtraBage_Map, TABLE_ITEM_EXTBAG );
		const CGameTable* pItem_ExtraBage_MapTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_EXTBAG);
		if (NULL == pItem_ExtraBage_MapTable)
		{
			return NULL;
		}

		pExtraBagMap = (const _TABLE_ITEM_EXTBAG*)pItem_ExtraBage_MapTable->GetFieldDataByIndex(id);
		if (NULL == pExtraBagMap)
			return NULL;

		data.icon = pExtraBagMap->szIcon;
		data.title = pExtraBagMap->szName;
		data.desc = pExtraBagMap->szDesc;
		return true;
	}
	break;

	default:

	break;
	};	// switch

	return false;
}

std::string transformImageName(const char* name)
{
	std::string tmp;

	auto pos = strstr(name, "image:");

	if (pos - name > 5)
	{
		tmp.assign(name + 4, pos - name - 4);
		tmp.pop_back();
		tmp.push_back('/');
		tmp += pos + 6;
	}

	return tmp;
}


bool FormatQuestString(String& strConvert)
{
	/* 唯一标记,主要用于生成唯一的Link供UI使用。 */
	static uint32 nOnlyFlag = 0;
	bool bConvert = false;
	char szNum[32] = { 0 };
	size_t nPos = 0;

	//add for mission optimize begin

	nPos = strConvert.find("&&");

	if (0 == nPos && strConvert.size() > 2)//resolve string id
	{
		size_t nPosEnd = strConvert.find("$$");

		String strDisKey = "";
		if (nPosEnd != String::npos && strConvert.size() > 4)
		{
			strDisKey = strConvert.substr(2, nPosEnd - 2);
		}
		else
		{
			strDisKey = strConvert.substr(2);
		}

		//String strDis = UI_SYSTEM_PTR->ParserString_NoVarParam(strDisKey.c_str());

		//todo
		String strDis = strDisKey;
		if (!strDis.empty())//找到key值
		{
			if (nPosEnd != String::npos)//替换参数
			{
				size_t nPosParamBegin = strConvert.find("$$");
				size_t nPosParamEnd = String::npos;
				String strParamValue = "";
				size_t nFindFormat_s = String::npos;//支持%s替换
				size_t nFindFormat_d = String::npos;//支持%d替换
				while (nPosParamBegin != String::npos)
				{
					nPosParamEnd = strConvert.find("$$", nPosParamBegin + 2);

					if (nPosParamEnd != String::npos)
					{
						strParamValue = strConvert.substr(nPosParamBegin + 2, nPosParamEnd - (nPosParamBegin + 2));
					}
					else
					{
						strParamValue = strConvert.substr(nPosParamBegin + 2);
					}

					nFindFormat_s = strDis.find("%s");
					nFindFormat_d = strDis.find("%d");

					if (nFindFormat_s == String::npos && nFindFormat_d == String::npos)
					{
						break;
					}
					if (nFindFormat_s != String::npos &&
						(nFindFormat_d == String::npos || nFindFormat_s < nFindFormat_d))
					{
						strDis.replace(nFindFormat_s, 2, strParamValue);
					}

					if (nFindFormat_d != String::npos &&
						(nFindFormat_s == String::npos || nFindFormat_d < nFindFormat_s))
					{
						strDis.replace(nFindFormat_d, 2, strParamValue);
					}

					nPosParamBegin = nPosParamEnd;//下标移到下一个$$											
				}
			}
			strConvert = strDis;
		}
	}
	nPos = strConvert.find("@itemid_");

	while (nPos != String::npos)
	{
		String strItemIndex = strConvert.substr(nPos + 8);
		int32 nItemIndex = atoi(strItemIndex.c_str());

		memset(szNum, 0, sizeof(szNum));
		itoa(nItemIndex, szNum, 10);

		String strItemName;
		ItemData itemData;
		getItemInfo(nItemIndex, itemData);
		LPCTSTR szStr = itemData.title.c_str();
		if (szStr)
		{
			strItemName = szStr;
		}
		strConvert = strConvert.substr(0, nPos) + strItemName + strItemIndex.substr(strlen(szNum));
		nPos = strConvert.find("@itemid_");
		bConvert = true;
	}


	while (nPos != String::npos)
	{
		strConvert = strConvert.substr(0, nPos) + "#r" + strConvert.substr(nPos + 2);
		nPos = strConvert.find("\\n");
		bConvert = true;
	}


	nPos = strConvert.find("\\t");

	while (nPos != String::npos)
	{
		strConvert = strConvert.substr(0, nPos) + "    " + strConvert.substr(nPos + 2);
		nPos = strConvert.find("\\t");
		bConvert = true;
	}



		/* 解析由脚本中传过来的字符串中的"\t" */
		nPos = strConvert.find(0x9);

	while (nPos != String::npos)
	{
		strConvert = strConvert.substr(0, nPos) + "    " + strConvert.substr(nPos + 1);
		nPos = strConvert.find(0x9);
		bConvert = true;
	}


	TABLE_DEFINEHANDLE(s_pSceneDBC, TABLE_SCENE_DEFINE);

	nPos = strConvert.find("@sceneid_");
	while (nPos != String::npos)
	{
		String strSceneIndex = strConvert.substr(nPos + 9);
		int32 nSceneIndex = atoi(strSceneIndex.c_str());

		memset(szNum, 0, sizeof(szNum));
		itoa(nSceneIndex, szNum, 10);

		const _TABLE_SCENE_DEFINE* pSceneDef = (const _TABLE_SCENE_DEFINE*)s_pSceneDBC->GetFieldDataByLine(nSceneIndex);

		if (pSceneDef)
			strConvert = strConvert.substr(0, nPos) + pSceneDef->szName + strSceneIndex.substr(strlen(szNum));
		nPos = strConvert.find("@sceneid_");
		bConvert = true;
	}

	auto* myself = KObjectManager::GetSingleton().getMySelf();
	
	if (nullptr == myself) return FALSE;

	KCharatcterBaseData* pMySelfData = myself->GetCharacterData();

	if (NULL == pMySelfData) return FALSE;

	nPos = strConvert.find("@myname");

	while (nPos != String::npos)
	{
		strConvert = strConvert.substr(0, nPos) + pMySelfData->Get_Name() + strConvert.substr(nPos + 7);
		nPos = strConvert.find("@myname");
		bConvert = true;
	}


		/* @item_12345 =>#G#{_ITEM12345}#W */
		nPos = strConvert.find("@item_");

	while (nPos != String::npos)
	{
		String strItemIndex = strConvert.substr(nPos + 6);
		int32 nItemIndex = atoi(strItemIndex.c_str());

		memset(szNum, 0, sizeof(szNum));
		itoa(nItemIndex, szNum, 10);

		/*
		 * string strItemName = OBJECT_MANAGER_PTR->GetItemNameByTBIndex( nItemIndex );
		 */
		char strTemp[256] = { 0 };

		snprintf(strTemp, 256, "#G#{_ITEM%d_%d}", nItemIndex, nOnlyFlag++);
		strConvert = strConvert.substr(0, nPos) + String(strTemp) + strItemIndex.substr(strlen(szNum));
		nPos = strConvert.find("@item_");
		bConvert = true;
	}

		/* @npcname_12345 => 王五 */
		nPos = strConvert.find("@npcname_");

	while (nPos != String::npos)
	{
		String strIndex = strConvert.substr(nPos + 9);
		int32 nIndex = atoi(strIndex.c_str());

		memset(szNum, 0, sizeof(szNum));
		itoa(nIndex, szNum, 10);

		TABLE_DEFINEHANDLE(s_pNpc, TABLE_SCENEMAP_NPC);

		/* scenemap_npc.tab */
		const _TABLE_SCENEMAP_NPC* pNpc = (const _TABLE_SCENEMAP_NPC*)(s_pNpc->GetFieldDataByIndex(nIndex));

		if (pNpc)
		{
			strConvert = strConvert.substr(0, nPos) + String(pNpc->szNpcUIName) + strIndex.substr(strlen(szNum));
		}
		else
		{
			break;
		}

		nPos = strConvert.find("@npcname_");
		bConvert = true;
	}


		/* @npc_22222=>#aB{npc_22222}#c00CCFFFF王五#aE */
		nPos = strConvert.find("@npc_");

	while (nPos != String::npos)
	{
		String strIndex = strConvert.substr(nPos + 5);
		int32 nIndex = atoi(strIndex.c_str());

		memset(szNum, 0, sizeof(szNum));
		itoa(nIndex, szNum, 10);

		TABLE_DEFINEHANDLE(s_pNpc, TABLE_SCENEMAP_NPC);

		/* scenemap_npc.tab */
		const _TABLE_SCENEMAP_NPC* pNpc = (const _TABLE_SCENEMAP_NPC*)(s_pNpc->GetFieldDataByIndex(nIndex));

		if (pNpc)
		{
			char strTemp[256] = { 0 };

			if (pNpc->nNPCType != 3)
			{
				snprintf(strTemp, 256, "{npc_%llu_%d}%s", pNpc->nIndex, nOnlyFlag++, pNpc->szNpcUIName);
			}
			else
			{
				snprintf(strTemp, 256, "{npc_%llu_%d}%s", pNpc->nIndex, nOnlyFlag++, pNpc->szNpcName);
			}

			strConvert = strConvert.substr(0, nPos) + String(strTemp) + strIndex.substr(strlen(szNum));
		}
		else
		{
			break;
		}

		nPos = strConvert.find("@npc_");
		bConvert = true;
	}


		/* @npcsp_李四_22222 =>#aB{npc_22222}#c00CCFFFF李四#aE */
		nPos = strConvert.find("@npcsp_");

	while (nPos != String::npos)
	{
		int32 nOldPos = (int32)nPos;
		String strNew = strConvert.substr(nPos + 7);

		nPos = strNew.find_first_of("_");

		/* 到尾部了，退出 */
		if (nPos == String::npos) break;

		/* 解析名称与索引 */
		String strName = strNew.substr(0, nPos);
		String strIndex = strNew.substr(nPos + 1, strNew.length());

		/* index */
		int32 nIndex = atoi(strIndex.c_str());

		memset(szNum, 0, sizeof(szNum));
		itoa(nIndex, szNum, 10);

		int32 nLen = (int32)(strName.length() + strlen(szNum) + 1);

		TABLE_DEFINEHANDLE(s_pNpc, TABLE_SCENEMAP_NPC);

		/* scenemap_npc.tab */
		const _TABLE_SCENEMAP_NPC* pNpc = (const _TABLE_SCENEMAP_NPC*)(s_pNpc->GetFieldDataByIndex(nIndex));

		if (pNpc)
		{
			char strTemp[256] = { 0 };

			snprintf(strTemp, 256, "#aB{npc_%llu_%d}%s#aE", pNpc->nIndex, nOnlyFlag++, strName.c_str());

			strConvert = strConvert.substr(0, nOldPos) + String(strTemp) + strNew.substr(nLen);
		}
		else
		{
			break;
		}

		nPos = strConvert.find("@npcsp_");
		bConvert = true;
	}


	return bConvert;
}

bool getEventItemInfo(
	const servermessage::EventItem* item,
	EventData& result)
{
	std::string str;
	size_t index = -1;

	auto itemType = item->item_type();

	result.type = itemType;

	switch (itemType)
	{
	case EVENT_ITEM_TYPE_SCRIPT_ID:
		result.desc = item->scriptstr();
		break;

	case EVENT_ITEM_TYPE_TEXT:
		str = item->scriptstr();
		if (0 == str.find_first_of("&&"))	/* string::npos != strPos && */
		{
			index = str.length();
			str = str.substr(2, index - 4);
			index = atoi(str.c_str());

			/* 读表取值 */
			TABLE_DEFINEHANDLE(s_pNpcInfoDBC, TABLE_QUEST_INFO) const _TABLE_QUEST_INFO* pNpcInfo =
				(const _TABLE_QUEST_INFO*)(s_pNpcInfoDBC->GetFieldDataByIndex((int32)index));

			if (pNpcInfo != NULL) str = pNpcInfo->szDefault;
		}

		FormatQuestString(str);
		result.desc = str;
		break;

	default:
		assert(false);
		return false;
		break;
	}

	return true;
}

bool replaceUIDesc(String& desc, std::vector<UIDesc>& buttonlist)
{
	uint32_t i = 0;

	uint32_t size = desc.size();
	//#aB{npc_125038_0}#aE
	enum
	{
		DescState_None  = 0,
		DescState_Begin = 1,
		DescState_LeftBracket = 2,
		DescState_RightBracket = 3,

	};

	bool link = false;

	std::string strProperty;
	std::string strCaption;
	std::string strContent;
	auto state = DescState_None;
	uint32_t index = 1;
	while (i < size)
	{
		switch (state)
		{
		case DescState_None:
			if (desc[i] == '#')
			{
				state = DescState_Begin;
				if (desc[i + 1] != 'a' ||
					desc[i + 2] != 'B')
				{
					return false;
				}
				i += 3;
				strCaption.clear();
				continue;
			}
			else
			{
				strContent.push_back(desc[i]);
			}
			break;
		case DescState_Begin:
			if (desc[i] == '{')
			{
				state = DescState_LeftBracket;
				strProperty.clear();
			}
			else
			{
				strCaption.push_back(desc[i]);
			}
			break;
		case DescState_LeftBracket:
			if (desc[i] == '}')
			{
				state = DescState_RightBracket;
			}
			else
			{
				strProperty.push_back(desc[i]);
			}
			break;
		case DescState_RightBracket:
			if (desc[i] == '#')
			{
				if (desc[i + 1] != 'a' ||
					desc[i + 2] != 'E')
				{
					return false;
				}
				strContent += "[window = 'DynamicButton_" + std::to_string(index++) += "']";
				state = DescState_None;
				buttonlist.emplace_back();
				buttonlist.back().attachment = strProperty;
				buttonlist.back().caption = strCaption;
				i += 3;
				continue;
			}
			else
			{
				strCaption.push_back(desc[i]);
			}
			break;
		}
		i++;
	}
	desc = strContent;
	return true;
}
