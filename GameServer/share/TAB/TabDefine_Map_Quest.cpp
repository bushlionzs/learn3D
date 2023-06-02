#include "stdafx.h"
#include "TabDefine_Map.h"
#include "filedef.h"
#include "ScriptCacheMgr.h"

#include "TAB.h"

#include "SplitStringLevelOne.h"
#include "SplitStringLevelTwo.h"

#include "TabDefine_Map_Quest.h"


using namespace TAB;

_SCENE_MAP_NPC_TBL	g_SceneMapNpcTbl;
_NPC_QUEST_TBL	g_NpcQuestTbl;
_QUESTIONS_DATA g_QuestionDataTable;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
TableInit_Map_Quest::TableInit_Map_Quest()
{}

TableInit_Map_Quest::~TableInit_Map_Quest()
{}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TableInit_Map_Quest::Init()
{
	Init_NPCPaoPaoIndexTable();
	Init_NPCQuestTable();
	LoadSceneMapNPCTable();
	LoadQuestionsAndAnswersTable();
	LoadQuestDengmiTable();
	LoadQuestWulongTable();
	LoadQuestQuizTable();
	LoadQuestShituTable();

	return TRUE;
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Quest::Init_NPCPaoPaoIndexTable()
{
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//__GUARD__ TABFile	ThirdFile(0);
	//BOOL			ret = ThirdFile.OpenFromTXT(FILE_NPCPAOPAOINDEXTBL);
	//int32			iTableCount = ThirdFile.GetRecordsNum();
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//KCheck(iTableCount <= MAXTYPE_NUMBER);

	//memset((void *) &g_NPCPaoPaoIndexTab, -1, sizeof(SNPCPaoPaoIndexTab));
	//g_NPCPaoPaoIndexTab.m_iCount = iTableCount;

	///*~~~~~~~~~~~~~~~*/
	//int32	nIndex = 0;
	///*~~~~~~~~~~~~~~~*/

	//for(int32 i = 0; i < iTableCount; ++i)
	//{
	//	nIndex = ThirdFile.Search_Posistion(i, 0)->iValue;
	//	g_NPCPaoPaoIndexTab.m_NPCPaoPaoIndex[i].m_iDataIndex = nIndex;
	//	g_NPCPaoPaoIndexTab.m_NPCPaoPaoIndex[i].m_nBaseIndex = ThirdFile.Search_Posistion(i, 2)->iValue;
	//	g_NPCPaoPaoIndexTab.m_NPCPaoPaoIndex[i].m_nIndexStep = ThirdFile.Search_Posistion(i, 1)->iValue;
	//}

	//__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Quest::Init_NPCQuestTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum NpcQuestTab
	{
		NpcType					= 0,
		NpcName					= 1,
		NpcDefaultDialog			= 2,
		NpcDialogScript				= 3,
		NpcEventList				= 4,
		NpcQuestList				= 5,
	};
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_NPC_QUEST);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && iTableCount < MAXTYPE_NUMBER);
	g_NpcQuestTbl.m_Table = new NPC_QUEST[iTableCount];
	g_NpcQuestTbl.m_Count = iTableCount;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iType;
	char	EventList[NPC_EVENT_LENGTH] = { 0 };
	char	Event[16] = { 0 };
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		iType = ThirdFile.Search_Posistion(i, NpcType)->iValue;

		g_NpcQuestTbl.m_Table[i].m_Type = iType;
		g_NpcQuestTbl.m_Table[i].m_ScriptID = ThirdFile.Search_Posistion(i, NpcDialogScript)->iValue;
		KCheck(g_NpcQuestTbl.m_Table[i].m_ScriptID <= 0 || g_NpcQuestTbl.m_Table[i].m_ScriptID >= 100000);

		memset(Event, 0, sizeof(Event));
		strncpy(EventList, ThirdFile.Search_Posistion(i, NpcEventList)->pString, NPC_EVENT_LENGTH);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iEventListLength = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(EventList[0] != '\0') iEventListLength = (int32) strlen(EventList);

		KCheckEx(iEventListLength < NPC_EVENT_LENGTH, "EventList超过长度!");

		/*~~~~~~~~~~~~~~~~~~~~*/
		int32	EventLength = 0;
		int32	EventIndex = 0;
		/*~~~~~~~~~~~~~~~~~~~~*/

		g_NpcQuestTbl.m_Table[i].m_EventCount = 0;
		for(int EventOffSet = 0; EventOffSet <= iEventListLength && iEventListLength > 0; EventOffSet++)
		{
			if(EventOffSet < iEventListLength)
			{
				if(EventList[EventOffSet] != '|')
				{
					if(EventLength >= 12) KCheckEx(FALSE, "格式错误!");

					Event[EventLength++] = EventList[EventOffSet];
				}
				else
				{
					g_NpcQuestTbl.m_Table[i].m_EventList[EventIndex++] = atoi(Event);
					g_NpcQuestTbl.m_Table[i].m_EventCount++;
					EventLength = 0;
					memset(&Event, 0, sizeof(Event));
				}
			}
			else
			{
				g_NpcQuestTbl.m_Table[i].m_EventList[EventIndex++] = atoi(Event);
				g_NpcQuestTbl.m_Table[i].m_EventCount++;
			}
		}

		memset(Event, 0, sizeof(Event));
		strncpy(EventList, ThirdFile.Search_Posistion(i, NpcQuestList)->pString, NPC_EVENT_LENGTH);

		iEventListLength = 0;
		if(EventList[0] != '\0') iEventListLength = (int32) strlen(EventList);

		EventLength = 0;
		EventIndex = 0;
		memset(Event, 0, 16);

		KCheckEx(iEventListLength < NPC_EVENT_LENGTH, "QuestList超过长度!");

		g_NpcQuestTbl.m_Table[i].m_QuestCount = 0;
		for(int EventOffSet = 0; EventOffSet <= iEventListLength && iEventListLength > 0; EventOffSet++)
		{
			if(EventOffSet < iEventListLength)
			{
				if(EventList[EventOffSet] != '|')
				{
					if(EventLength >= 12) KCheckEx(FALSE, "格式错误!");

					Event[EventLength++] = EventList[EventOffSet];
				}
				else
				{
					g_NpcQuestTbl.m_Table[i].m_QuestList[EventIndex++] = atoi(Event);
					g_NpcQuestTbl.m_Table[i].m_QuestCount++;
					EventLength = 0;
					memset(&Event, 0, sizeof(Event));
				}
			}
			else
			{
				g_NpcQuestTbl.m_Table[i].m_QuestList[EventIndex++] = atoi(Event);
				g_NpcQuestTbl.m_Table[i].m_QuestCount++;
			}
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Quest::LoadSceneMapNPCTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum SceneMapNpc
	{
		NpcIndex				= 0,
		NpcSceneID				= 1,
		NpcName					= 2,
		NpcPosX					= 4,
		NpcPosZ					= 5
	};
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_SCENEMAP_NPC);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_SceneMapNpcTbl.m_Table = new SCENE_MAP_NPC_t[iTableCount];
	g_SceneMapNpcTbl.m_Count = iTableCount;

	for(int32 i = 0; i < iTableCount; i++)
	{
		g_SceneMapNpcTbl.m_Table[i].m_Index = ThirdFile.Search_Posistion(i, NpcIndex)->iValue;
		g_SceneMapNpcTbl.m_Table[i].m_SceneID = ThirdFile.Search_Posistion(i, NpcSceneID)->iValue;
		strncpy
		(
			g_SceneMapNpcTbl.m_Table[i].m_Name,
			ThirdFile.Search_Posistion(i, NpcName)->pString,
			NPC_NAME_LEN
		);
		g_SceneMapNpcTbl.m_Table[i].m_PosX = ThirdFile.Search_Posistion(i, NpcPosX)->fValue;
		g_SceneMapNpcTbl.m_Table[i].m_PosZ = ThirdFile.Search_Posistion(i, NpcPosZ)->fValue;
	}

	__UNGUARD__
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Quest::LoadQuestionsAndAnswersTable()
{
	/*~~~~~~~~~~~~*/
	enum QuestionsIndex { QI_Index, QI_Type, };
	/*~~~~~~~~~~~~*/

	enum AnswersIndex { AI_Index, AI_Answer1, AI_Answer2, };

	TABFile Questins(0);
	TABFile Answers(0);

	BOOL ret = Questins.OpenFromTXT(FILE_MENTAL_GAME_QUESTIONS);
	if(ret != TRUE)
	{
		KCheck(FALSE && "InitQuestionsTable failed, please check it.");
		return;
	}

	ret = Answers.OpenFromTXT(FILE_MENTAL_GAME_ANSWERS);
	if(ret != TRUE)
	{
		KCheck(FALSE && "InitAnswersTable failed, please check it.");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableQues = Questins.GetRecordsNum();
	int32	iTableColumnQues = Questins.GetFieldsNum();
	int32	iTableAns = Answers.GetRecordsNum();
	int32	iTableColumnAns = Answers.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableQues > 0);
	KCheck(iTableQues == iTableAns);
	KCheck(iTableColumnQues == 7);
	KCheck(iTableColumnAns == 3);

	g_QuestionDataTable.m_QuestionData = new _QUESTIONS_t[iTableQues];
	g_QuestionDataTable.m_QuestionDataCount = iTableQues;

	memset(g_QuestionDataTable.m_QuestionData, 0, sizeof(_QUESTIONS_t) * iTableQues);

	for(int32 i = 0; i < iTableQues; ++i)
	{
		g_QuestionDataTable.m_QuestionData[i].nIndex = Questins.Search_Posistion(i, QI_Index)->iValue;
		g_QuestionDataTable.m_QuestionData[i].nType = Questins.Search_Posistion(i, QI_Type)->iValue;
		g_QuestionDataTable.m_QuestionData[i].nAnswerIndex1 = Answers.Search_Posistion(i, AI_Answer1)->iValue;
		g_QuestionDataTable.m_QuestionData[i].nAnswerIndex2 = Answers.Search_Posistion(i, AI_Answer2)->iValue;
	}
}

static void _LoadQuestDengmiTable(QUEST_DENGMI_ATTR& attr, const char* pathName)
{
	__GUARD__ enum QuestDengmiData { ID = 0, Desc, Answer1, Answer2, Answer3, Answer4, Answer, };
	TABFile DBFile(0);
	BOOL	ret = DBFile.OpenFromTXT(pathName);

	KCheckEx(ret, FILE_QUEST_DENGMI_INFO);

	int32	iTableCount = DBFile.GetRecordsNum();
	int32	iColumnCount = DBFile.GetFieldsNum();

	KCheck(iTableCount >= 0 && iTableCount < MAX_QUEST_DENGMI_COUNT);

	memset((void *) &attr, 0, sizeof(attr));

	attr.m_Count = iTableCount;

	KCheck(Answer < iColumnCount);

	for(int32 i = 0; i < iTableCount; ++i)
	{
		attr.m_TableExt[i].m_ID = DBFile.Search_Posistion(i, ID)->iValue;
		KCheck(attr.m_TableExt[i].m_ID == i);
		strncpy
			(
			attr.m_TableExt[i].m_Desc,
			DBFile.Search_Posistion(i, Desc)->pString,
			MAX_QUEST_DENGMI_DESC
			);
		strncpy
			(
			attr.m_TableExt[i].m_strAnswer1,
			DBFile.Search_Posistion(i, Answer1)->pString,
			MAX_QUEST_DENGMI_ANSWER
			);
		strncpy
			(
			attr.m_TableExt[i].m_strAnswer2,
			DBFile.Search_Posistion(i, Answer2)->pString,
			MAX_QUEST_DENGMI_ANSWER
			);
		strncpy
			(
			attr.m_TableExt[i].m_strAnswer3,
			DBFile.Search_Posistion(i, Answer3)->pString,
			MAX_QUEST_DENGMI_ANSWER
			);
		strncpy
			(
			attr.m_TableExt[i].m_strAnswer4,
			DBFile.Search_Posistion(i, Answer4)->pString,
			MAX_QUEST_DENGMI_ANSWER
			);
		attr.m_TableExt[i].m_nAnswer = DBFile.Search_Posistion(i, Answer)->iValue;
		KCheck
			(
			attr.m_TableExt[i].m_nAnswer >= 1
			&&	attr.m_TableExt[i].m_nAnswer <= 4
			);
	}

	attr.m_Count = iTableCount;

	__UNGUARD__
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Quest::LoadQuestDengmiTable()
{
	//_LoadQuestDengmiTable(g_QuestDengmiAttrTbl, FILE_QUEST_DENGMI_INFO);
}

void TableInit_Map_Quest::LoadQuestQuizTable()
{
	//_LoadQuestDengmiTable(g_QuestQuizAttrTbl, FILE_QUEST_QUIZ_INFO);
}

void TableInit_Map_Quest::LoadQuestShituTable()
{
	/*__GUARD__ enum QuestShituData { ID = 0, Desc, Answer1, Answer2, Answer3, Answer4, Answer};
	TABFile DBFile(0);
	BOOL	ret = DBFile.OpenFromTXT(FILE_QUEST_SHITU_INFO);

	KCheckEx(ret, FILE_QUEST_SHITU_INFO);

	int32	iTableCount = DBFile.GetRecordsNum();
	int32	iColumnCount = DBFile.GetFieldsNum();

	KCheck(iTableCount >= 0 && iTableCount < MAX_QUEST_DENGMI_COUNT);

	memset((void *) &g_QuestShituAttrTbl, 0, sizeof(g_QuestShituAttrTbl));

	g_QuestShituAttrTbl.m_Count = iTableCount;

	KCheck(Answer < iColumnCount);

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_QuestShituAttrTbl.m_TableExt[i].m_ID = DBFile.Search_Posistion(i, ID)->iValue;
		strncpy
			(
			g_QuestShituAttrTbl.m_TableExt[i].m_Desc,
			DBFile.Search_Posistion(i, Desc)->pString,
			MAX_QUEST_DENGMI_DESC
			);
		strncpy
			(
			g_QuestShituAttrTbl.m_TableExt[i].m_strAnswer1,
			DBFile.Search_Posistion(i, Answer1)->pString,
			MAX_QUEST_DENGMI_ANSWER
			);
		strncpy
			(
			g_QuestShituAttrTbl.m_TableExt[i].m_strAnswer2,
			DBFile.Search_Posistion(i, Answer2)->pString,
			MAX_QUEST_DENGMI_ANSWER
			);
		strncpy
			(
			g_QuestShituAttrTbl.m_TableExt[i].m_strAnswer3,
			DBFile.Search_Posistion(i, Answer3)->pString,
			MAX_QUEST_DENGMI_ANSWER
			);
		strncpy
			(
			g_QuestShituAttrTbl.m_TableExt[i].m_strAnswer4,
			DBFile.Search_Posistion(i, Answer4)->pString,
			MAX_QUEST_DENGMI_ANSWER
			);
		g_QuestShituAttrTbl.m_TableExt[i].m_nAnswer = DBFile.Search_Posistion(i, Answer)->iValue;
		KCheck
			(
			g_QuestShituAttrTbl.m_TableExt[i].m_nAnswer >= 1
			&&	g_QuestShituAttrTbl.m_TableExt[i].m_nAnswer <= 4
			);
	}

	g_QuestShituAttrTbl.m_Count = iTableCount;

	__UNGUARD__*/
}


const CGameTable* TableInit_Map_Quest::getTable(int nTable)
{
	switch (nTable)
	{
	case TABLE_QUEST_INFO:
		
	case TABLE_QUEST_LIST:
		return nullptr;
	}

	return nullptr;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Quest::LoadQuestWulongTable()
{
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//__GUARD__ enum QuestWulongData { ID = 0, Type, Desc, Answer1, Answer2, Answer3, Answer4, Answer, };
	//TABFile DBFile(0);
	//BOOL	ret = DBFile.OpenFromTXT(FILE_QUEST_WULONG_INFO);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//KCheckEx(ret, FILE_QUEST_WULONG_INFO);

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//int32	iTableCount = DBFile.GetRecordsNum();
	//int32	iColumnCount = DBFile.GetFieldsNum();
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//KCheck(iTableCount >= 0);

	///*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//int32	iFirstTableCount = 0;
	//int32	iSecTableCount = 0;
	///*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//for(int32 i = 0; i < iTableCount; ++i)
	//{
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//	int32	type = DBFile.Search_Posistion(i, Type)->iValue;
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//	if(0 == type)
	//	{
	//		KCheck(iFirstTableCount < QUEST_WULONGCIDIAN_TABLE::MAX_QUEST_WULONG_ATTR_COUNT);
	//		g_QuestWulongAttrTbFirst.m_Table[iFirstTableCount].m_ID = DBFile.Search_Posistion
	//			(
	//				i,
	//				ID
	//			)->iValue;
	//		strncpy
	//		(
	//			g_QuestWulongAttrTbFirst.m_Table[iFirstTableCount].m_Desc,
	//			DBFile.Search_Posistion(i, Desc)->pString,
	//			QUEST_WULONGCIDIAN_ATTR::MAX_QUEST_WULONG_DESC
	//		);
	//		strncpy
	//		(
	//			g_QuestWulongAttrTbFirst.m_Table[iFirstTableCount].m_strAnswer1,
	//			DBFile.Search_Posistion(i, Answer1)->pString,
	//			QUEST_WULONGCIDIAN_ATTR::MAX_QUEST_WULONG_ANSWER
	//		);
	//		strncpy
	//		(
	//			g_QuestWulongAttrTbFirst.m_Table[iFirstTableCount].m_strAnswer2,
	//			DBFile.Search_Posistion(i, Answer2)->pString,
	//			QUEST_WULONGCIDIAN_ATTR::MAX_QUEST_WULONG_ANSWER
	//		);
	//		strncpy
	//		(
	//			g_QuestWulongAttrTbFirst.m_Table[iFirstTableCount].m_strAnswer3,
	//			DBFile.Search_Posistion(i, Answer3)->pString,
	//			QUEST_WULONGCIDIAN_ATTR::MAX_QUEST_WULONG_ANSWER
	//		);
	//		strncpy
	//		(
	//			g_QuestWulongAttrTbFirst.m_Table[iFirstTableCount].m_strAnswer4,
	//			DBFile.Search_Posistion(i, Answer4)->pString,
	//			QUEST_WULONGCIDIAN_ATTR::MAX_QUEST_WULONG_ANSWER
	//		);
	//		g_QuestWulongAttrTbFirst.m_Table[iFirstTableCount].m_nAnswer = DBFile.Search_Posistion
	//			(
	//				i,
	//				Answer
	//			)->iValue;
	//		++iFirstTableCount;
	//	}
	//	else
	//	{
	//		KCheck(iSecTableCount < QUEST_WULONGCIDIAN_TABLE::MAX_QUEST_WULONG_ATTR_COUNT);
	//		g_QuestWulongAttrTbSec.m_Table[iSecTableCount].m_ID = DBFile.Search_Posistion(i, ID)->iValue;
	//		strncpy
	//		(
	//			g_QuestWulongAttrTbSec.m_Table[iSecTableCount].m_Desc,
	//			DBFile.Search_Posistion(i, Desc)->pString,
	//			QUEST_WULONGCIDIAN_ATTR::MAX_QUEST_WULONG_DESC
	//		);
	//		strncpy
	//		(
	//			g_QuestWulongAttrTbSec.m_Table[iSecTableCount].m_strAnswer1,
	//			DBFile.Search_Posistion(i, Answer1)->pString,
	//			QUEST_WULONGCIDIAN_ATTR::MAX_QUEST_WULONG_ANSWER
	//		);
	//		strncpy
	//		(
	//			g_QuestWulongAttrTbSec.m_Table[iSecTableCount].m_strAnswer2,
	//			DBFile.Search_Posistion(i, Answer2)->pString,
	//			QUEST_WULONGCIDIAN_ATTR::MAX_QUEST_WULONG_ANSWER
	//		);
	//		strncpy
	//		(
	//			g_QuestWulongAttrTbSec.m_Table[iSecTableCount].m_strAnswer3,
	//			DBFile.Search_Posistion(i, Answer3)->pString,
	//			QUEST_WULONGCIDIAN_ATTR::MAX_QUEST_WULONG_ANSWER
	//		);
	//		strncpy
	//		(
	//			g_QuestWulongAttrTbSec.m_Table[iSecTableCount].m_strAnswer4,
	//			DBFile.Search_Posistion(i, Answer4)->pString,
	//			QUEST_WULONGCIDIAN_ATTR::MAX_QUEST_WULONG_ANSWER
	//		);
	//		g_QuestWulongAttrTbSec.m_Table[iSecTableCount].m_nAnswer = DBFile.Search_Posistion
	//			(
	//				i,
	//				Answer
	//			)->iValue;
	//		++iSecTableCount;
	//	}
	//}

	//g_QuestWulongAttrTbFirst.m_Count = iFirstTableCount;
	//g_QuestWulongAttrTbSec.m_Count = iSecTableCount;

	//__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __SCRIPT_QUEST_DATA::InitTable(uint32 nMaxCount)
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	Clear();
	/*~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __SCRIPT_QUEST_DATA::Clear(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__;
	IntegerHashMap::IDTableIterator	it = m_IDTable.Begin();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	while(it != m_IDTable.End())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		VEC_QUESTDATA	*pVecQuestData = (VEC_QUESTDATA *) (it->second);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pVecQuestData)
		{
			delete pVecQuestData;
		}

		++it;
	}

	m_IDTable.Clear();
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL __SCRIPT_QUEST_DATA::Add(uint32 nIdEvent, void *pData)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pData);
	VEC_QUESTDATA	*pVecQuestData = (VEC_QUESTDATA *) m_IDTable.Get(nIdEvent);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pVecQuestData)
	{
		pVecQuestData->push_back(pData);
		return TRUE;
	}
	else
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		VEC_QUESTDATA	*pNewQuestData = new VEC_QUESTDATA;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pNewQuestData);
		pNewQuestData->push_back(pData);

		m_IDTable.Add(nIdEvent, pNewQuestData);

		return TRUE;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL __SCRIPT_QUEST_DATA::Have(uint32 nIdEvent)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ VEC_QUESTDATA *pVecQuestData = (VEC_QUESTDATA *) m_IDTable.Get(nIdEvent);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pVecQuestData)
		return TRUE;
	else
		return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL __SCRIPT_QUEST_DATA::Find(uint32 nIdEvent, uint32 nNPCGUID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ VEC_QUESTDATA *pVecQuestData = (VEC_QUESTDATA *) m_IDTable.Get(nIdEvent);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pVecQuestData)
	{
		for(int32 i = 0; i < pVecQuestData->size(); ++i)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			_QUEST_DATA_t	*pData = (_QUEST_DATA_t *) pVecQuestData->at(i);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pData);
			if(pData->nSubmitNPCGUID == nNPCGUID) return TRUE;
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareNpcQuestTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	NPC_QUEST	*pTB1 = (NPC_QUEST *) pArg1;
	NPC_QUEST	*pTB2 = (NPC_QUEST *) pArg2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pTB1->m_Type > pTB2->m_Type)
		return 1;
	else if(pTB1->m_Type < pTB2->m_Type)
		return -1;
	else
		return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
NPC_QUEST *_NPC_QUEST_TBL::Get(int32 NpcType)
{
	/*~~~~~~~~~~~~~~~*/
	NPC_QUEST	tb;
	/*~~~~~~~~~~~~~~~*/

	tb.m_Type = NpcType;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	NPC_QUEST	*pResult = (NPC_QUEST *) bsearch
		(
			&tb,
			m_Table,
			m_Count,
			sizeof(NPC_QUEST),
			(int32(*) (const void *, const void *)) CompareNpcQuestTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult) return pResult;

	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareQuestKillMonsterTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_KILLMONSTER_t	*pTB1 = (_QUEST_KILLMONSTER_t *) pArg1;
	_QUEST_KILLMONSTER_t	*pTB2 = (_QUEST_KILLMONSTER_t *) pArg2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pTB1->nQuestIndex > pTB2->nQuestIndex)
		return 1;
	else if(pTB1->nQuestIndex < pTB2->nQuestIndex)
		return -1;
	else
		return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
_QUEST_KILLMONSTER_t *__QUEST_KILLMONSTER::Get(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_KILLMONSTER_t	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.nQuestIndex = nIndex;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_KILLMONSTER_t	*pResult = (_QUEST_KILLMONSTER_t *) bsearch
		(
			&tb,
			m_QuestKillMonster,
			m_nQuestKillMonsterCount,
			sizeof(_QUEST_KILLMONSTER_t),
			(int32(*) (const void *, const void *)) CompareQuestKillMonsterTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult) return pResult;

	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareQuestLookItemTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_LOOKITEM_t	*pTB1 = (_QUEST_LOOKITEM_t *) pArg1;
	_QUEST_LOOKITEM_t	*pTB2 = (_QUEST_LOOKITEM_t *) pArg2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pTB1->nQuestIndex > pTB2->nQuestIndex)
		return 1;
	else if(pTB1->nQuestIndex < pTB2->nQuestIndex)
		return -1;
	else
		return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
_QUEST_LOOKITEM_t *__QUEST_LOOKITEM::Get(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_LOOKITEM_t	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.nQuestIndex = nIndex;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_LOOKITEM_t	*pResult = (_QUEST_LOOKITEM_t *) bsearch
		(
			&tb,
			m_QuestLookItem,
			m_nQuestLookItemCount,
			sizeof(_QUEST_LOOKITEM_t),
			(int32(*) (const void *, const void *)) CompareQuestLookItemTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult) return pResult;

	return 0;
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareQuestHuSongTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_HUSONG_t *pTB1 = (_QUEST_HUSONG_t *) pArg1;
	_QUEST_HUSONG_t *pTB2 = (_QUEST_HUSONG_t *) pArg2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pTB1->nQuestIndex > pTB2->nQuestIndex)
		return 1;
	else if(pTB1->nQuestIndex < pTB2->nQuestIndex)
		return -1;
	else
		return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
_QUEST_HUSONG_t *__QUEST_HUSONG::Get(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~*/
	_QUEST_HUSONG_t tb;
	/*~~~~~~~~~~~~~~~*/

	tb.nQuestIndex = nIndex;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_HUSONG_t *pResult = (_QUEST_HUSONG_t *) bsearch
		(
			&tb,
			m_QuestHuSong,
			m_nQuestHuSongCount,
			sizeof(_QUEST_HUSONG_t),
			(int32(*) (const void *, const void *)) CompareQuestHuSongTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult) return pResult;

	return 0;
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareQuestDataTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_DATA_t	*pTB1 = (_QUEST_DATA_t *) pArg1;
	_QUEST_DATA_t	*pTB2 = (_QUEST_DATA_t *) pArg2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pTB1->nQuestID > pTB2->nQuestID)
		return 1;
	else if(pTB1->nQuestID < pTB2->nQuestID)
		return -1;
	else
		return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
_QUEST_DATA_t *__QUEST_DATA::Get(int32 nQuestID)
{
	/*~~~~~~~~~~~~~~~*/
	_QUEST_DATA_t	tb;
	/*~~~~~~~~~~~~~~~*/

	tb.nQuestID = nQuestID;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_DATA_t	*pResult = (_QUEST_DATA_t *) bsearch
		(
			&tb,
			m_QuestData,
			m_nQuestDataCount,
			sizeof(_QUEST_DATA_t),
			(int32(*) (const void *, const void *)) CompareQuestDataTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult) return pResult;

	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareQuestEnterAreaTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_ENTERAREA_t	*pTB1 = (_QUEST_ENTERAREA_t *) pArg1;
	_QUEST_ENTERAREA_t	*pTB2 = (_QUEST_ENTERAREA_t *) pArg2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pTB1->nQuestIndex > pTB2->nQuestIndex)
		return 1;
	else if(pTB1->nQuestIndex < pTB2->nQuestIndex)
		return -1;
	else
		return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
_QUEST_ENTERAREA_t *__QUEST_ENTERAREA::Get(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_ENTERAREA_t	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.nQuestIndex = nIndex;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_ENTERAREA_t	*pResult = (_QUEST_ENTERAREA_t *) bsearch
		(
			&tb,
			m_QuestEnterArea,
			m_nQuestEnterAreaCount,
			sizeof(_QUEST_ENTERAREA_t),
			(int32(*) (const void *, const void *)) CompareQuestEnterAreaTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult) return pResult;

	return 0;
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareQuestDeliveryTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_DELIVERY_t	*pTB1 = (_QUEST_DELIVERY_t *) pArg1;
	_QUEST_DELIVERY_t	*pTB2 = (_QUEST_DELIVERY_t *) pArg2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pTB1->nQuestIndex > pTB2->nQuestIndex)
		return 1;
	else if(pTB1->nQuestIndex < pTB2->nQuestIndex)
		return -1;
	else
		return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
_QUEST_DELIVERY_t *__QUEST_DELIVERY::Get(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_DELIVERY_t	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.nQuestIndex = nIndex;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_DELIVERY_t	*pResult = (_QUEST_DELIVERY_t *) bsearch
		(
			&tb,
			m_QuestDelivery,
			m_nQuestDeliveryCount,
			sizeof(_QUEST_DELIVERY_t),
			(int32(*) (const void *, const void *)) CompareQuestDeliveryTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult) return pResult;

	return 0;
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareQuestUseItemTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_USEITEM_t	*pTB1 = (_QUEST_USEITEM_t *) pArg1;
	_QUEST_USEITEM_t	*pTB2 = (_QUEST_USEITEM_t *) pArg2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pTB1->nQuestIndex > pTB2->nQuestIndex)
		return 1;
	else if(pTB1->nQuestIndex < pTB2->nQuestIndex)
		return -1;
	else
		return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
_QUEST_USEITEM_t *__QUEST_USEITEM::Get(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_USEITEM_t	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.nQuestIndex = nIndex;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_USEITEM_t	*pResult = (_QUEST_USEITEM_t *) bsearch
		(
			&tb,
			m_QuestUseItem,
			m_nQuestUseItemCount,
			sizeof(_QUEST_USEITEM_t),
			(int32(*) (const void *, const void *)) CompareQuestUseItemTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult) return pResult;

	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareSceneMapNpcTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SCENE_MAP_NPC_t *pTB1 = (SCENE_MAP_NPC_t *) pArg1;
	SCENE_MAP_NPC_t *pTB2 = (SCENE_MAP_NPC_t *) pArg2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pTB1->m_Index > pTB2->m_Index)
		return 1;
	else if(pTB1->m_Index < pTB2->m_Index)
		return -1;
	else
		return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SCENE_MAP_NPC_t *_SCENE_MAP_NPC_TBL::Get(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~*/
	SCENE_MAP_NPC_t tb;
	/*~~~~~~~~~~~~~~~*/

	tb.m_Index = nIndex;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SCENE_MAP_NPC_t *pResult = (SCENE_MAP_NPC_t *) bsearch
		(
			&tb,
			m_Table,
			m_Count,
			sizeof(SCENE_MAP_NPC_t),
			(int32(*) (const void *, const void *)) CompareSceneMapNpcTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult) return pResult;

	return 0;
}
