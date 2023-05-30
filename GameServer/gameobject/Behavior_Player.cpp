/*$T MapServer/Server/AI/Behavior_Player.cpp GC 1.140 10/10/07 10:07:19 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "map/game_map.h"
#include "TabDefine.h"
#include "BaseTool.h"

#include "Character.h"
#include "Player.h"
#include "Behavior_Player.h"
#include "gameobject/ObjectManager.h"
#include "map/server_map_path.h"
#include "Pet.h"
#include "map/map_info.h"
#include "Behavior_Monster.h"
#include "Behavior_Pet.h"
#include "Monster.h"
#include "Behavior_Helper.h"
#include "Object.h"
#include "data/data_manager.h"
#include "share/TAB/TabDefine_Map_Quest.h"
#include "ScriptCacheMgr.h"
#include "script/LuaSystem.h"
#include "ScriptDef.h"
#include "item/Item_Base.h"
#include "item/Item_Interface.h"
#include "server_manager.h"
#include "CharActionDelegator.h"

extern ScriptCache* GetScriptFileData(ScriptID_t scriptid);

Behavior_Player::Behavior_Player(void)
{
	m_TeamFollowCheckTick = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Behavior_Player::~Behavior_Player(void)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Player::Init(Character *pCharacter)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bResult = Behavior_Character::Init(pCharacter);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!bResult) return FALSE;

	m_TeamFollowCheckTick = 0;
	m_paramAI_UseSpell.Clear();
	m_paramAI_UseItem.Clear();
	m_nSettleTime = 0;
	m_baHead = TRUE;
	m_nIndexOfPassed = 0;
	m_nIndexOfMoveTo = 0;
	m_PatrolScriptID = -1;
	m_bPause = TRUE;
	m_bCircle = TRUE;
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::Clear(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Behavior_Character:: Clear();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_TargetList.clear();

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::Event_OnBeSpell(Character *pCharacter, int32 nGoodEffect)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::Event_OnDamage(int32 nDamage, Character *pAttacker)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::Event_OnBeHeal(Character *pCharacter, int32 nHeal)
{
	__GUARD__ if(pCharacter)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32		i;
		Character	*apTarget[MAX_THREAT_COUNT];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		memset(apTarget, 0, sizeof(apTarget));

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32				count = 0;
		auto it = m_TargetList.begin();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(; it != m_TargetList.end(); ++it)
		{
			if(INVALID_ID != it->first)
			{
				apTarget[count++] = (Character *) it->second;
			}
		}

		if(0 == count) return;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nThreat = nHeal / count;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(i = 0; i < count; ++i)
		{
			KCheck(apTarget[i]);
			if(apTarget[i]->GetObjType() != Object::OBJECT_CLASS_MONSTER)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~*/
				char	szMsg[32] = { 0 };
				/*~~~~~~~~~~~~~~~~~~~~~~*/

				tsnprintf_s(szMsg, 32, "apTarget[%d] isnot a monster.", i);
				KCheckEx(apTarget[i]->GetObjType() == Object::OBJECT_CLASS_MONSTER, szMsg);
			}

			if(apTarget[i]->GetMapID_i() == GetCharacter()->GetMapID_i())
				((Behavior_Monster *) apTarget[i]->GetAIObj())->ModThreatByPtr(pCharacter, nThreat);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::AddTargetToList(Character *pChar)
{
	__GUARD__ if(NULL == pChar) return;

	if(pChar->GetObjType() != Object::OBJECT_CLASS_MONSTER) return;
	if(!pChar->IsActiveObj() || !pChar->IsAlive()) return;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uCount = m_TargetList.size();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(uCount == MAX_THREAT_COUNT) return;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pTarget = (Character *) getTarget(pChar->GetID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pTarget)
	{
		addTarget(pChar->GetID(), pChar);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::RemoveTargetFromList(Character *pChar)
{
	if(pChar)
	{
		m_TargetList.erase(pChar->GetID());
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::StartPatrol()
{
	__GUARD__ if(ESTATE_DEAD == GetBehavior_State()->GetStateID())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player	*pPlayer = (Player *) GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pPlayer)
	{
		KCheck(FALSE && NULL == pPlayer);
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = pPlayer->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		KCheck(FALSE && NULL == pMap);
		return;
	}

	if(pPlayer->IsMoving())
	{
		BHV_Stop();
	}

	/*
	 * m_nIndexOfPassed = pPlayer->GetCurrentPathNode();
	 * ;
	 * m_nIndexOfMoveTo = pPatrolPathMgr->GetPatrolPoint ;
	 * ( ;
	 * patrolPathIndex, ;
	 * m_nIndexOfPassed, ;
	 * m_baHead, ;
	 * Tar, ;
	 * m_nSettleTime, ;
	 * m_PatrolScriptID, ;
	 * m_bCircle ;
	 * );
	 * ;
	 * pMap->GetMapInfo()->VerifyPos(&Tar);
	 * *if(pMap->GetMapInfo()->IsCanGo(Tar)) ;
	 * { ;
	 * Move(&Tar);
	 * *} ;
	 * else ;
	 * { ;
	 * QLogSystem::SLOW_LOG ;
	 * ( ;
	 * SLOW_LOG_SERVER, ;
	 * "AIHuman::StartPatrol cannot go to posX = %f, posZ = %f \n", ;
	 * Tar.m_fX, ;
	 * Tar.m_fZ ;
	 * );
	 * *}
	 */
	ChangeState(ESTATE_PATROL);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::StopPatrol(void)
{
	__GUARD__ if(ESTATE_DEAD == GetBehavior_State()->GetStateID())
	{
		return;
	}

	BHV_Stop();

	m_nIndexOfPassed = 0;
	m_nIndexOfMoveTo = 0;

	ChangeState(ESTATE_IDLE);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::PausePatrol(void)
{
	__GUARD__ if(ESTATE_DEAD == GetBehavior_State()->GetStateID())
	{
		return;
	}

	m_bPause = TRUE;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::ResumePatrol(void)
{
	__GUARD__ if(ESTATE_DEAD == GetBehavior_State()->GetStateID())
	{
		return;
	}

	m_bPause = FALSE;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::Event_OnDie(Object *pKiller)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ObjID_t	idKiller = INVALID_ID;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pKiller != NULL)
	{
		idKiller = pKiller->GetID();
	}

	ChangeState(ESTATE_DEAD);

	After_Die(idKiller);

	ClearTargetList();

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::OnEvent_ReliveInfoChanged(void)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::OnEvent_CallOfInfoChanged(void)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::AcceptCallOf(void)
{
	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::RefuseCallOf(void)
{
	 return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_DieResult(int32 nResultCode)
{
	 return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_CallOfResult(int32 nResultCode)
{
	 return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_Jump(int32 nLogicCount)
{
	Character* pCharacter = GetCharacter();

	KCheck(pCharacter != NULL && pCharacter->GetObjType() == Object::OBJECT_CLASS_PLAYER);

	if(pCharacter == NULL)
		return OR_NULL_POINTER;

	if(!(pCharacter->IsActiveObj()))
		return OR_CHARACTER_IS_UNACTIVE;

	return OR_OK;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_MoodState(int32 nMoodState)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pCharacter = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pCharacter != NULL);
	if(pCharacter == NULL) return OR_NULL_POINTER;
	if(!(pCharacter->IsActiveObj())) return OR_CHARACTER_IS_UNACTIVE;

	pCharacter->SetMoodState(nMoodState);

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::Validate_Event(Object *pTarget)
{
	__GUARD__ if(pTarget == NULL) return OR_NO_TARGET;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pCharacter = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pCharacter)
	{
		KCheck(NULL && "AIHuman::Validate_Event...pCharacter = NULL!!!");
		return OR_NULL_POINTER;
	}

	if(IsObjCharacter(pTarget->GetObjType()))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	*pChar = (Character *) pTarget;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pChar->IsDie()) return OR_TARGET_DIE;

		//如果是玩家自己,返回OK
		if(pCharacter == pTarget )return OR_OK;

	}

	/*~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bRadius;
	float	fErrorDist = 2.f;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	bRadius = GetCharacter()->IsInValidRadius(pTarget, MAX_SERVER_DEFAULT_EVENT_DIST + fErrorDist);
	if(bRadius == FALSE)
	{
		return OR_OUT_RANGE;
	}

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::Relive(int32 nResultCode)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_Idle(void)
{
	if(!(GetCharacter()->IsActiveObj())) 
		return OR_CHARACTER_IS_UNACTIVE;

	ForceInterruptAllSpell();
	((Player *) GetCharacter())->interruptCurrentAbilityOpera();

	/*~~~~~~~~~~~~~~~~~~~~~*/
	OPT_RESULT oResult = BHV_Stop();
	/*~~~~~~~~~~~~~~~~~~~~~*/

	ChangeState(ESTATE_IDLE);
	return oResult;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_Stall(void)
{
	__GUARD__ if(!(GetCharacter()->IsActiveObj())) return OR_CHARACTER_IS_UNACTIVE;

	/*~~~~~~~~~~~~~~~~~~~~~~*/
	OPT_RESULT oResult = BHV_Stall();
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	return oResult;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_Move
(
	int32		nHandleID,
	uint16		wNumTargetPos,
	const GLPos *paTargetPos,
	int32		nStopLogicCount,
	const GLPos *paCurPos,
	ObjID_t		nSenderID
)
{
	__GUARD__ if(!(GetCharacter()->IsActiveObj())) return OR_CHARACTER_IS_UNACTIVE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	OPT_RESULT oResult = BHV_Move(nHandleID, wNumTargetPos, paTargetPos, nStopLogicCount, paCurPos, nSenderID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ORT_SUCCEEDED(oResult))
	{
		m_paramAI_UseSpell.AutoSpell_CleanUp();
		m_paramAI_UseSpell.QueueSpell_CleanUp();

		TeamMemeberToMove();
	}

	return oResult;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::Baby_Go(const GLPos *paTargetPos)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Player::CheckQuestSubmitNPCIfNecessary(ScriptID_t idEvent, Object *pTarget)
{
	 return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_UseSpell
(
	ObjID_t idSkill,
	ObjID_t idTarget,
	float	fTargetX,
	float	fTargetZ,
	float	fDir,
	GUID_t	guidTarget,
	int32	iHurtDelayTime,
	BOOL	bChildSkill
)
{
	if (!(GetCharacter()->IsActiveObj())) return OR_CHARACTER_IS_UNACTIVE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellTargetingAndDepletingParams& rParams = GetCharacter()->GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rParams.SetActivatedScript(INVALID_ID);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	OPT_RESULT oResult = BHV_UseSpell(idSkill, idTarget, fTargetX, fTargetZ, iHurtDelayTime, fDir, guidTarget);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_paramAI_UseSpell.m_fQueueTargetDirection = fDir;
	m_paramAI_UseSpell.m_iHurtDelayTime = iHurtDelayTime;
	if (OR_OK == oResult)
	{
		ChangeState(ESTATE_COMBAT);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SpellTemplateData const* pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(idSkill);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (NULL == pSkillTemplate)
		{
			return OR_OK;
		}

		if (pSkillTemplate->CanInterruptAutoShot())
		{
			ForceInterruptAutoSpell();
		}

		if (FALSE == IsEnterCombatState(idSkill, idTarget))
		{
			PushSpellToQueue
			(
				idSkill,
				idTarget,
				fTargetX,
				fTargetZ,
				iHurtDelayTime,
				fDir,
				guidTarget,
				bChildSkill
			);
		}
	}
	else
	{
		return oResult;
	}

	return oResult;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_UseItem
(
	ID_t		nBagIndex,
	ObjID_t		nTargetObj,
	const GLPos &posTarget,
	SHorseGuid&guidTargetPet,
	ID_t		nTargetItem
)
{
	__GUARD__ if(!(GetCharacter()->IsActiveObj())) return OR_CHARACTER_IS_UNACTIVE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	OPT_RESULT oResult = BHV_UseItem(nBagIndex, nTargetObj, posTarget, guidTargetPet, nTargetItem);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(OR_OK == oResult)
	{
		ChangeState(ESTATE_COMBAT);
		PushItemToQueue(nBagIndex, nTargetObj, posTarget, guidTargetPet, nTargetItem);
	}
	else
	{
		//((Player *) GetCharacter())->SendOperateResultMsg(oResult);
	}

	return oResult;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_UseAbility(void)
{
	__GUARD__ if(!(GetCharacter()->IsActiveObj())) return OR_CHARACTER_IS_UNACTIVE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	OPT_RESULT oResult = BHV_UseSkill();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(OR_OK != oResult)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Player	*pPlayer = static_cast<Player *>(GetCharacter());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pPlayer)
		{
			pPlayer->SendOperateResultMsg(oResult, 0);
			pPlayer->reset_AbilityOpera();
		}
	}

	return oResult;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_DefaultEvent(ObjID_t idNPC)
{
	__GUARD__;
	
	//检查指针
	Character *pCharacter = GetCharacter();
	KCheck(pCharacter != NULL);
	if(pCharacter == NULL) 
		return OR_NULL_POINTER;

	//检查是否激活
	if(!(GetCharacter()->IsActiveObj()))
	{
		return OR_CHARACTER_IS_UNACTIVE;
	}

	//检查否存活
	if(!GetCharacter()->IsAlive())
	{
		return OR_DIE;
	}

	//是否随伍跟随
	if(ESTATE_TEAMFOLLOW == GetBehavior_State()->GetStateID())
	{
		return OR_TEAM_FOLLOW_STATE;
	}

	//场景例行检查
	KCheck(pCharacter->GetMap());
	KCheck(pCharacter->GetMap()->GetObjManager());

	//检查NPC
	Object *pNPC = pCharacter->GetMap()->GetObjManager()->GetObj(idNPC);
	if(!pNPC)
		return OR_CANNOT_FIND_NPC;

	//检查NPC类型不为玩家
	if(pNPC->GetObjType() == Object::OBJECT_CLASS_PLAYER) 
		return OR_OK;

	//如果类型为怪物
	if(pNPC->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		Behavior_Monster *pBehavior_Monster = (Behavior_Monster *) (((Monster *) pNPC)->GetAIObj());
		if(!pBehavior_Monster)
		{
			KCheck(NULL && "AIHuman::PushCommand_DefaultEvent...pBehavior_Monster=NULL...");
			return OR_NULL_POINTER;
		}

		//如果是护送NPC，不管
		if(TRUE == pBehavior_Monster->IsConvoyNPC())
		{
			return OR_OK;
		}

		//如果是NPC是寻路无法打断的，则不处理
		if( ((Monster *) pNPC)->GetPatrolNoBreak() == 0 )
		{
			//如果NPC处于IDLE状态或是寻路状态，执行停止
			int32 nBState = pBehavior_Monster->GetBehavior_State()->GetStateID();
			if( ESTATE_IDLE == nBState ||  ESTATE_PATROL == nBState )
			{
				pBehavior_Monster->StartService();
				pBehavior_Monster->BHV_Stop();
			}
		}

		
	}

	


	//以下执行相关脚本
	ScriptID_t idScript = pNPC->GetScriptID();
	if(idScript <= 0 )
	{
		if(pNPC->GetObjType() == Object::OBJECT_CLASS_MONSTER)
		{
			Monster	*pMonster = (Monster *) pNPC;
			NPC_QUEST *pQuest = DataManager::GetSingletonPtr()->getNpcQuest(pMonster->GetGUID());
			if(pQuest != NULL)
			{
				if(pQuest->m_EventCount == 0 && pQuest->m_QuestCount == 0)
				{
					pCharacter->GetMap()->OnNpcDefaultDialog( (Player *) pCharacter, pNPC->GetID(), pMonster->GetGUID() );
				}
				else
				{
					pCharacter->GetMap()->OnNpcEventList( (Player *) pCharacter, pNPC->GetID(), pMonster->GetGUID() );
				}
			}
		}

		return OR_OK;
	}
	else
	{
		if( idScript > 0 )
		{
			ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction( pCharacter->GetMap()->MapID(), idScript, DEF_PROC_EVENT_ENTRY_FN, 
																	 (int32) pCharacter->GetMap()->MapID(), 
																	 (int32) pCharacter->GetID(), 
																	 (int32) pNPC->GetID() );
		}
	}

	return OR_OK;
	__UNGUARD__;
	return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_EventRequest(ObjID_t idNPC, ScriptID_t idEvent, int32 exIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pCharacter = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pCharacter != NULL);
	if(pCharacter == NULL) return OR_NULL_POINTER;
	if(!(GetCharacter()->IsActiveObj())) return OR_CHARACTER_IS_UNACTIVE;

	KCheck(pCharacter->GetMap());
	KCheck(pCharacter->GetMap()->GetObjManager());

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object	*pNPC = pCharacter->GetMap()->GetObjManager()->GetObj(idNPC);
	OPT_RESULT oRes = Validate_Event(pNPC);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(oRes != OR_OK)
	{
		return oRes;
	}

	/*~~~~~~~~~~~~~~~~~~~~~*/
	int32	bVerifyEvent = 0;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	if(pNPC->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Monster		*pMonster = (Monster *) pNPC;
		NPC_QUEST	*pQuest = DataManager::GetSingleton().getNpcQuest(pMonster->GetGUID());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pQuest)
		{
			for(int32 i = 0; i < pQuest->m_EventCount; i++)
			{
				if(pQuest->m_EventList[i] == idEvent)
				{
					bVerifyEvent = 1;
					break;
				}
			}

			if(bVerifyEvent == 0)
			{
				for(int32 i = 0; i < pQuest->m_QuestCount; i++)
				{
					if(pQuest->m_QuestList[i] == idEvent)
					{
						bVerifyEvent = 2;
						break;
					}
				}
			}

			if(bVerifyEvent == 0)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				ScriptID_t	_checkScriptId = ((Player *) pCharacter)->GetRuntimeData(RT_EVENT_REQUEST_QUEST_SCRIPT_ID);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(_checkScriptId != idEvent) return OR_INVALID_TARGET;
			}
		}
	}

	if(bVerifyEvent == 1)
	{
		ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
			(
				pCharacter->GetMap()->MapID(),
				idEvent,
				DEF_PROC_EVENT_ENTRY_FN,
				pCharacter->GetMap()->MapID(),
				pCharacter->GetID(),
				pNPC->GetID(),
				idEvent,
				exIndex
			);

		return OR_OK;
	}
	else if(bVerifyEvent == 2 || bVerifyEvent == 0)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		_QUEST_DATA_t	*pData = DataManager::GetSingletonPtr()->getQuestByID(idEvent);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pData)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			BOOL	bRunByScript = FALSE;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pData->nScriptID >= 100000)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				ScriptCache	*pSFileData = GetScriptFileData(pData->nScriptID);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(pSFileData)
				{
					ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
						(
							pCharacter->GetMap()->MapID(),
							pData->nScriptID,
							DEF_PROC_EVENT_ENTRY_FN,
							pCharacter->GetMap()->MapID(),
							pCharacter->GetID(),
							pNPC->GetID(),
							idEvent,
							exIndex
						);
					bRunByScript = TRUE;
				}
			}

			if(bRunByScript == FALSE)
			{
				ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
					(
						pCharacter->GetMap()->MapID(),
						QUEST_SCRIPTID,
						DEF_PROC_EVENT_ENTRY_FN,
						pCharacter->GetMap()->MapID(),
						pCharacter->GetID(),
						pNPC->GetID(),
						idEvent,
						exIndex
					);
			}
		}

		return OR_OK;
	}

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_QuestAccept(ObjID_t idNPC, ScriptID_t idQuestScript)
{
	__GUARD__;

    Character	*pCharacter = GetCharacter();

	KCheck(pCharacter != NULL);

	if( pCharacter == NULL)
        return OR_NULL_POINTER;
	if( !( GetCharacter()->IsActiveObj() ) )
        return OR_CHARACTER_IS_UNACTIVE;

	KCheck(pCharacter->GetMap());
	KCheck(pCharacter->GetMap()->GetObjManager());

	KCheck(pCharacter->GetObjType() == Object::OBJECT_CLASS_PLAYER);

	ObjID_t		_checkNPCId = ((Player *) pCharacter)->GetRuntimeData(RT_EVENT_REQUEST_NPCID);
    // 如果调用的LuaFunction_DispatchQuestInfoNM，那么_checkScriptId与idQuestScript肯定一致，都是任务ID参数，
    // 如果是LuaFunction_DispatchQuestInfo，那么会根据任务ID参数决定_checkScriptId，大于0就是任务ID，否则是脚本ID
	ScriptID_t	_checkScriptId = ((Player *) pCharacter)->GetRuntimeData(RT_EVENT_REQUEST_QUEST_SCRIPT_ID);
	((Player *) pCharacter)->SetRuntimeData(RT_EVENT_REQUEST_NPCID, 0);
	((Player *) pCharacter)->SetRuntimeData(RT_EVENT_REQUEST_QUEST_SCRIPT_ID, 0);

	if(_checkNPCId != idNPC)
        return OR_ERROR;
    if( _checkScriptId != idQuestScript)
	{
        // 只有调用LuaFunction_DispatchQuestInfo且任务ID>0才会走到这里
		// 只有一种情况会走到这里：LuaFunction_DispatchQuestInfo的任务ID参数>0时且脚本ID与之不同
        // 根据任务ID到任务表查找任务
		_QUEST_DATA_t	*pData = DataManager::GetSingletonPtr()->getQuestByID(_checkScriptId);

		if( pData == 0 || pData->nScriptID != idQuestScript)
		{
			pData = DataManager::GetSingletonPtr()->getQuestByID(idQuestScript);
			if(!pData || pData->nScriptID != _checkScriptId)
			{
				return OR_ERROR;
			}
		}
	}

	if(idNPC == pCharacter->GetID())
	{
		// LuaFunction_DispatchQuestInfo的NPCId参数如果是selfId会执行到这里，罕见的情况，脚本id必须填有效的任务ID，否则会出错
		_QUEST_DATA_t	*pData = DataManager::GetSingletonPtr()->getQuestByID(idQuestScript);

		if(pData)
		{
			if(!pCharacter->GetMap()->OnAcceptQuestCheck((Player *) pCharacter, idQuestScript))
			{
				return OR_ERROR;
			}

			if(pData->nScriptID >= 100000)
			{
				// 如果该任务有脚本
				BOOL		bRunByScript = FALSE;
				ScriptCache	*pSFileData = GetScriptFileData(pData->nScriptID);

				if(pSFileData)
				{
					ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
						(
							pCharacter->GetMap()->MapID(),
							pData->nScriptID,
							DEF_PROC_QUEST_ACCEPT_FN,
							pCharacter->GetMap()->MapID(),
							pCharacter->GetID(),
							(int32) idNPC,
							idQuestScript
						);
					bRunByScript = TRUE;
				}

				if(bRunByScript == FALSE)
				{
					ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
						(
							pCharacter->GetMap()->MapID(),
							pData->nScriptID,
							DEF_PROC_QUEST_ACCEPT_FN,
							pCharacter->GetMap()->MapID(),
							pCharacter->GetID(),
							(int32) idNPC,
							idQuestScript
						);
				}

				return OR_OK;
			}
			else
			{
				ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
					(
						pCharacter->GetMap()->MapID(),
						QUEST_SCRIPTID,
						DEF_PROC_QUEST_ACCEPT_FN,
						pCharacter->GetMap()->MapID(),
						pCharacter->GetID(),
						(int32) idNPC,
						idQuestScript
					);

				return OR_OK;
			}
		}

		return OR_DEFAULT_ERROR;
	}
	else if(idNPC != INVALID_ID)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object	*pNPC = pCharacter->GetMap()->GetObjManager()->GetObj(idNPC);
		OPT_RESULT oRes = Validate_Event(pNPC);

		if(oRes != OR_OK)
		{
			return oRes;
		}

		int32	bVerifyEvent = 0;

		if(pNPC->GetObjType() == Object::OBJECT_CLASS_MONSTER)
		{
			// 根据NPC的GUID查找obj_quest.tab
			Monster		*pMonster = (Monster *) pNPC;
			NPC_QUEST	*pQuest = DataManager::GetSingletonPtr()->getNpcQuest(pMonster->GetGUID());

			if(pQuest)
			{
				for(int32 i = 0; i < pQuest->m_EventCount; i++)
				{
					if(pQuest->m_EventList[i] == idQuestScript)
					{
						bVerifyEvent = 1;
						break;
					}
				}

				if(bVerifyEvent == 0)
				{
					for(int32 i = 0; i < pQuest->m_QuestCount; i++)
					{
						if(pQuest->m_QuestList[i] == idQuestScript)
						{
							bVerifyEvent = 2;
							break;
						}
					}
				}
			}
		}

		

		if(bVerifyEvent == 1)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	ret = ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
				(
					pCharacter->GetMap()->MapID(),
					idQuestScript,
					DEF_PROC_ACCEPT_CHECK_FN,
					pCharacter->GetMap()->MapID(),
					pCharacter->GetID(),
					(int32) pNPC->GetID()
				);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(ret > 0)
			{
				ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
					(
						pCharacter->GetMap()->MapID(),
						idQuestScript,
						DEF_PROC_ACCEPT_FN,
						pCharacter->GetMap()->MapID(),
						pCharacter->GetID()
					);
			}

			return OR_OK;
		}
		else if(bVerifyEvent == 2 || bVerifyEvent == 0)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			_QUEST_DATA_t	*pData = DataManager::GetSingletonPtr()->getQuestByID(idQuestScript);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pData)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
				BOOL	bRunByScript = FALSE;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(pData->nScriptID >= 100000)
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					ScriptCache	*pSFileData = GetScriptFileData(pData->nScriptID);
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					if(pSFileData)
					{
						ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
							(
								pCharacter->GetMap()->MapID(),
								pData->nScriptID,
								DEF_PROC_QUEST_ACCEPT_FN,
								pCharacter->GetMap()->MapID(),
								pCharacter->GetID(),
								(int32) pNPC->GetID(),
								idQuestScript
							);
						bRunByScript = TRUE;
					}
				}

				if(bRunByScript == FALSE)
				{
					ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
						(
							pCharacter->GetMap()->MapID(),
							QUEST_SCRIPTID,
							DEF_PROC_QUEST_ACCEPT_FN,
							pCharacter->GetMap()->MapID(),
							pCharacter->GetID(),
							(int32) pNPC->GetID(),
							idQuestScript
						);
				}
			}
		}
		else
			return OR_VARIFY_EVENT_ERROR;
	}
	else
	{
		if( idQuestScript <= 0 )
			return OR_ERROR;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	ret = ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
			(
				pCharacter->GetMap()->MapID(),
				idQuestScript,
				DEF_PROC_ACCEPT_CHECK_FN,
				pCharacter->GetMap()->MapID(),
				pCharacter->GetID(),
				-1
			);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(ret > 0)
		{
			ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
				(
					pCharacter->GetMap()->MapID(),
					idQuestScript,
					DEF_PROC_ACCEPT_FN,
					pCharacter->GetMap()->MapID(),
					pCharacter->GetID()
				);
		}

		return OR_OK;
	}

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_QuestAbandon(ScriptID_t idQuestScript)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pCharacter = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pCharacter != NULL);
	if(pCharacter == NULL) return OR_NULL_POINTER;
	if(!(GetCharacter()->IsActiveObj())) return OR_CHARACTER_IS_UNACTIVE;

	KCheck(pCharacter->GetMap());

	if(idQuestScript >= 100000)
	{
		ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
			(
				(int32) pCharacter->GetMap()->MapID(),
				idQuestScript,
				DEF_PROC_QUEST_ABANDON_FN,
				(int32) pCharacter->GetMap()->MapID(),
				(int32) pCharacter->GetID(),
				-1
			);
	}
	else
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		_QUEST_DATA_t	*pData = DataManager::GetSingletonPtr()->getQuestByID(idQuestScript);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pData)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			BOOL	bRunByScript = FALSE;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pData->nScriptID >= 100000)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				ScriptCache	*pSFileData = GetScriptFileData(pData->nScriptID);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(pSFileData)
				{
					ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
						(
							(int32) pCharacter->GetMap()->MapID(),
							pData->nScriptID,
							DEF_PROC_QUEST_ABANDON_FN,
							(int32) pCharacter->GetMap()->MapID(),
							(int32) pCharacter->GetID(),
							(int32) idQuestScript
						);
					bRunByScript = TRUE;
				}
			}

			if(bRunByScript == FALSE)
			{
				ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
					(
						(int32) pCharacter->GetMap()->MapID(),
						QUEST_SCRIPTID,
						DEF_PROC_QUEST_ABANDON_FN,
						(int32) pCharacter->GetMap()->MapID(),
						(int32) pCharacter->GetID(),
						idQuestScript
					);
			}
		}
	}

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_QuestRefuse(ObjID_t idNPC, ScriptID_t idQuestScript)
{
	__GUARD__ if(!(GetCharacter()->IsActiveObj())) return OR_CHARACTER_IS_UNACTIVE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pCharacter = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pCharacter != NULL);
	if(pCharacter == NULL) return OR_NULL_POINTER;

	KCheck(pCharacter->GetMap());
	KCheck(pCharacter->GetMap()->GetObjManager());

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object	*pNPC = pCharacter->GetMap()->GetObjManager()->GetObj(idNPC);
	OPT_RESULT oRes = Validate_Event(pNPC);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(oRes != OR_OK)
	{
		return oRes;
	}

	if(pNPC->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Monster		*pMonster = (Monster *) pNPC;
		NPC_QUEST	*pQuest = DataManager::GetSingletonPtr()->getNpcQuest(pMonster->GetGUID());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pQuest != NULL)
		{
			for(int32 i = 0; i < pQuest->m_EventCount; i++)
			{
				ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
					(
						pCharacter->GetMap()->MapID(),
						pQuest->m_EventList[i],
						DEF_PROC_ENUM_EVENT_FN,
						pCharacter->GetMap()->MapID(),
						pCharacter->GetID(),
						pNPC->GetID(),
						-1
					);
			}
		}
	}

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_QuestSubmit(ObjID_t idNPC, ScriptID_t idQuestScript, uint32 uSelectRadioID)
{
	__GUARD__;

    if( !( GetCharacter()->IsActiveObj() ) )
        return OR_CHARACTER_IS_UNACTIVE;

	Character	*pCharacter = GetCharacter();

	KCheck(pCharacter != NULL);
	if(pCharacter == NULL)
        return OR_NULL_POINTER;

	KCheck(pCharacter->GetMap());
	KCheck(pCharacter->GetMap()->GetObjManager());

	Object	*pNPC = pCharacter->GetMap()->GetObjManager()->GetObj( idNPC);
	OPT_RESULT oRes = Validate_Event(pNPC);

	if(oRes != OR_OK)
	{
		return oRes;
	}

	ObjID_t		_checkNPCId = ((Player *) pCharacter)->GetRuntimeData(RT_EVENT_REQUEST_NPCID);
	ScriptID_t	_checkScriptId = ((Player *) pCharacter)->GetRuntimeData(RT_EVENT_REQUEST_QUEST_SCRIPT_ID);
	((Player *) pCharacter)->SetRuntimeData(RT_EVENT_REQUEST_NPCID, 0);
	((Player *) pCharacter)->SetRuntimeData(RT_EVENT_REQUEST_QUEST_SCRIPT_ID, 0);

	if(_checkNPCId != idNPC || _checkScriptId != idQuestScript)
	{
		/*~~~~~~~~~~~~~~~~~~~*/
		BOOL	bError = FALSE;
		/*~~~~~~~~~~~~~~~~~~~*/

		if(_checkNPCId != idNPC) bError = TRUE;

		if(!bError)
		{
			if(_checkScriptId != idQuestScript)
			{
				_QUEST_DATA_t	*pData = DataManager::GetSingletonPtr()->getQuestByID(_checkScriptId);

				if(!pData || pData->nScriptID != idQuestScript)
				{
					pData = DataManager::GetSingletonPtr()->getQuestByID(idQuestScript);
					if(!pData || pData->nScriptID != _checkScriptId)
					{
						bError = TRUE;
					}
				}
			}
		}

		if(bError)
		{
			return OR_OK;;
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~*/
	int32	bVerifyEvent = 0;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	if(pNPC->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Monster		*pMonster = (Monster *) pNPC;
		NPC_QUEST	*pQuest = DataManager::GetSingletonPtr()->getNpcQuest(pMonster->GetGUID());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pQuest)
		{
			for(int32 i = 0; i < pQuest->m_EventCount; i++)
			{
				if(pQuest->m_EventList[i] == idQuestScript)
				{
					bVerifyEvent = 1;
					break;
				}
			}

			if(bVerifyEvent == 0)
			{
				for(int32 i = 0; i < pQuest->m_QuestCount; i++)
				{
					if(pQuest->m_QuestList[i] == idQuestScript)
					{
						bVerifyEvent = 2;
						break;
					}
				}
			}
		}
	}

	if(CheckQuestSubmitNPCIfNecessary(idQuestScript, pNPC) == FALSE) return OR_OK;

	if(bVerifyEvent == 1)
	{
		if( idQuestScript <= 0 )
			return OR_OK;

		ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
			(
				pCharacter->GetMap()->MapID(),
				idQuestScript,
				DEF_PROC_QUEST_SUBMIT_FN,
				pCharacter->GetMap()->MapID(),
				pCharacter->GetID(),
				pNPC->GetID(),
				uSelectRadioID,
				-1
			);
		return OR_OK;
	}
	else if(bVerifyEvent == 2 || bVerifyEvent == 0)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		_QUEST_DATA_t	*pData = DataManager::GetSingletonPtr()->getQuestByID(idQuestScript);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pData)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			BOOL	bRunByScript = FALSE;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pData->nScriptID >= 100000)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				ScriptCache	*pSFileData = GetScriptFileData(pData->nScriptID);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(pSFileData)
				{
					ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
						(
							pCharacter->GetMap()->MapID(),
							pData->nScriptID,
							DEF_PROC_QUEST_SUBMIT_FN,
							pCharacter->GetMap()->MapID(),
							pCharacter->GetID(),
							pNPC->GetID(),
							uSelectRadioID,
							idQuestScript
						);
					bRunByScript = TRUE;
				}
			}

			if(bRunByScript == FALSE)
			{
				ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
					(
						pCharacter->GetMap()->MapID(),
						QUEST_SCRIPTID,
						DEF_PROC_QUEST_SUBMIT_FN,
						pCharacter->GetMap()->MapID(),
						pCharacter->GetID(),
						pNPC->GetID(),
						uSelectRadioID,
						idQuestScript
					);
			}

			return OR_OK;
		}
	}

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_QuestContinue(ObjID_t idNPC, ScriptID_t idQuestScript)
{
	__GUARD__;

    if(!(GetCharacter()->IsActiveObj()))
        return OR_CHARACTER_IS_UNACTIVE;

	Character	*pCharacter = GetCharacter();

	KCheck(pCharacter != NULL);
	if(pCharacter == NULL)
        return OR_NULL_POINTER;

	KCheck(pCharacter->GetMap());
	KCheck(pCharacter->GetMap()->GetObjManager());

	if(idNPC != INVALID_ID)
	{
		// 根据npcId找到对应的Object
		Object	*pNPC = pCharacter->GetMap()->GetObjManager()->GetObj(idNPC);
		OPT_RESULT oRes = Validate_Event(pNPC);

		if(oRes != OR_OK)
		{
			return oRes;
		}

		BOOL	bVerifyEvent = FALSE;

		if(pNPC->GetObjType() == Object::OBJECT_CLASS_MONSTER)
		{
			// 根据NPC找到obj_quest.tab中队应的数据
			Monster		*pMonster = (Monster *) pNPC;
			NPC_QUEST	*pQuest = DataManager::GetSingletonPtr()->getNpcQuest(pMonster->GetGUID());

			if(pQuest)
			{
				for(int32 i = 0; i < pQuest->m_EventCount; i++)
				{
					if(pQuest->m_EventList[i] == idQuestScript)
					{
                        // 如果绑定了脚本
						bVerifyEvent = TRUE;
						break;
					}
				}
			}
		}

		if(bVerifyEvent)
		{
			if( idQuestScript <= 0 )
				return OR_OK;

            // 调用绑定的脚本
			ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction( pCharacter->GetMap()->MapID(),idQuestScript,
					"OnContinue", pCharacter->GetMap()->MapID(), pCharacter->GetID(),
					pNPC->GetID() );
		}
	}
	else
	{
		if( idQuestScript <= 0 )
			return OR_OK;

		ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction(pCharacter->GetMap()->MapID(), idQuestScript,
				"OnContinue", pCharacter->GetMap()->MapID(),pCharacter->GetID() );
	}// 调用DispatchQuestDemandInfo参数指定的脚本

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_TeamFollow()
{
	 return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::PushCmd_StopTeamFollow()
{
	 return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Player::GetFollowPos(GLPos &Pos, const GLPos *pStartPos, const GLPos *pEndPos, float fDist)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pStartPos);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pEndPos);
	KCheck(fDist);

	Pos.m_fX = (pStartPos->m_fX - pEndPos->m_fX) / fDist + pEndPos->m_fX;
	Pos.m_fZ = (pStartPos->m_fZ - pEndPos->m_fZ) / fDist + pEndPos->m_fZ;

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::FollowMove(Player *pPlayer, GLPos *pPos, float fDist)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Player::StartTeamFollow(void)
{
	

	return OR_OK;


}

OPT_RESULT Behavior_Player::StopTeamFollow(void)
{
	return OR_OK;
}

void Behavior_Player::Combat_Logic(uint32 uTime)
{
	Character* pCharacter = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pCharacter != NULL);
	if (pCharacter == NULL) return;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character& rMe = *pCharacter;
	GLPos	position;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	position.m_fX = position.m_fZ = 0.0f;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellID_t	nCurrentSkill = INVALID_ID;
	SpellID_t	nAutoActivedSkill = m_paramAI_UseSpell.m_nAutoShotSpell;
	SpellID_t	nQueuedSkill = m_paramAI_UseSpell.m_nQueuedSpell;
	SpellID_t	nChildSkill = m_paramAI_UseSpell.m_nChildSpell;
	ID_t		BagIndex = m_paramAI_UseItem.m_BagIndex;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (INVALID_ID != BagIndex)
	{
		
	}
	else if (INVALID_ID != nChildSkill)
	{
		if (FALSE == rMe.CanUseSkillNow(nChildSkill))
		{
			return;
		}

		if (FALSE == CheckTargetValid(nChildSkill, m_paramAI_UseSpell.m_nChildSpellTargetObjID))
		{
			m_paramAI_UseSpell.ChildSpell_CleanUp();
			return;
		}

		if (FALSE == rMe.IsSpellCooldowned(nChildSkill))
		{
			m_paramAI_UseSpell.ChildSpell_CleanUp();
			return;
		}

		if (FALSE == pCharacter->CanUseThisSpellInThisStatus(nChildSkill))
		{
			m_paramAI_UseSpell.ChildSpell_CleanUp();
			return;
		}

		BHV_UseSpell_i
		(
			nChildSkill,
			m_paramAI_UseSpell.m_nChildSpellTargetObjID,
			m_paramAI_UseSpell.m_ChildSpellPosition.m_fX,
			m_paramAI_UseSpell.m_ChildSpellPosition.m_fZ,
			m_paramAI_UseSpell.m_iHurtDelayTime,
			0.f,
			INVALID_ID
		);
		m_paramAI_UseSpell.ChildSpell_CleanUp();
	}
	else if (INVALID_ID != nQueuedSkill)
	{
		if (FALSE == rMe.CanUseSkillNow(nQueuedSkill))
		{
			return;
		}

		if (FALSE == CheckTargetValid(nQueuedSkill, m_paramAI_UseSpell.m_nQueueTargetObjID))
		{
			m_paramAI_UseSpell.Clear();

			ChangeState(ESTATE_IDLE);

			return;
		}

		if (FALSE == rMe.IsSpellCooldowned(nQueuedSkill))
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SpellTemplateData const* pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(nQueuedSkill);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if (NULL == pSkillTemplate)
			{
				m_paramAI_UseSpell.QueueSpell_CleanUp();
				return;
			}

			if (INVALID_ID == pSkillTemplate->GetProfession())
			{
				m_paramAI_UseSpell.QueueSpell_CleanUp();
				return;
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Player* pPlayer = static_cast<Player*>(GetCharacter());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			/*if (NULL != pPlayer)
			{
				pPlayer->SendOperateResultMsg(OR_COOL_DOWNING);
			}*/

			m_paramAI_UseSpell.QueueSpell_CleanUp();
			return;
		}

		if (FALSE == pCharacter->CanUseThisSpellInThisStatus(nQueuedSkill))
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Player* pPlayer = static_cast<Player*>(GetCharacter());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			/*if (NULL != pPlayer)
			{
				pPlayer->SendOperateResultMsg(OR_U_CANNT_DO_THIS_RIGHT_NOW);
			}*/

			m_paramAI_UseSpell.QueueSpell_CleanUp();
			return;
		}

		BHV_UseSpell_i
		(
			nQueuedSkill,
			m_paramAI_UseSpell.m_nQueueTargetObjID,
			m_paramAI_UseSpell.m_QueueTargetPosition.m_fX,
			m_paramAI_UseSpell.m_QueueTargetPosition.m_fZ,
			m_paramAI_UseSpell.m_iHurtDelayTime,
			m_paramAI_UseSpell.m_fQueueTargetDirection,
			m_paramAI_UseSpell.m_guidQueueTarget
		);
		m_paramAI_UseSpell.QueueSpell_CleanUp();
	}
	else if (INVALID_ID != nAutoActivedSkill)
	{
		if (FALSE == rMe.CanUseSkillNow(nAutoActivedSkill))
		{
			return;
		}

		if (FALSE == CheckTargetValid(nAutoActivedSkill, m_paramAI_UseSpell.m_nAutoShotTargetObjID))
		{
			m_paramAI_UseSpell.Clear();

			ChangeState(ESTATE_IDLE);

			return;
		}

		if (FALSE == rMe.IsSpellCooldowned(nAutoActivedSkill))
		{
			return;
		}

		if (FALSE == pCharacter->CanUseThisSpellInThisStatus(nAutoActivedSkill))
		{
			return;
		}

		/*~~~~~~~~~~~~~*/
		int32	nRet = 0;
		/*~~~~~~~~~~~~~*/

		nRet = BHV_UseSpell_i
		(
			m_paramAI_UseSpell.m_nAutoShotSpell,
			m_paramAI_UseSpell.m_nAutoShotTargetObjID,
			position.m_fX,
			position.m_fZ,
			m_paramAI_UseSpell.m_iHurtDelayTime,
			m_paramAI_UseSpell.m_fQueueTargetDirection,
			INVALID_ID
		);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character* pTarget = (Character*)
			(pCharacter->GetMap()->GetObjManager()->GetObj(m_paramAI_UseSpell.m_nAutoShotTargetObjID));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (pTarget && OR_OK == nRet && pCharacter->IsEnemy(pTarget))
		{
		}
		else
		{
			m_paramAI_UseSpell.AutoSpell_CleanUp();
		}
	}
	else
	{
		if (FALSE == rMe.CanUseSkillNow(INVALID_ID))
		{
			return;
		}

		ChangeState(ESTATE_IDLE);
		return;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::Patrol_Logic(uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Player	*pPlayer = (Player *) GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pPlayer)
	{
		KCheck(FALSE && NULL == pPlayer);
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = pPlayer->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		KCheck(FALSE && NULL == pMap);
		return;
	}

	if(m_bPause)
	{
		if(pPlayer->IsMoving())
		{
			BHV_Stop();
		}

		return;
	}

	if(!pPlayer->IsMoving())
	{
		if(m_nSettleTime > 0)
		{
			m_nSettleTime -= pPlayer->GetLogicTime();
			return;
		}

		m_nIndexOfPassed = pPlayer->GetCurrentPathNode();

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		PatrolRoadsPointMgr	*pPatrolPathMgr = pMap->GetPatrolPathMgr();
		int32		patrolPathIndex = pPlayer->GetPatrolID();
		GLPos	Tar;
		GLPos	CurPos = *(pPlayer->GetGLPos());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		m_nIndexOfMoveTo = pPatrolPathMgr->GetPatrolRoadsPoint
			(
				patrolPathIndex,
				m_nIndexOfPassed,
				m_baHead,
				Tar,
				m_nSettleTime,
				m_PatrolScriptID,
				m_bCircle,
				&CurPos
			);

		pPlayer->SetCurrentPathNode(m_nIndexOfMoveTo);

		pMap->GetMapInfo()->VerifyPos(&Tar);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
		OPT_RESULT oResult = BHV_Move(&Tar);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(OR_OK != oResult && OR_LIMIT_MOVE != oResult)
		{
			GetCharacter()->DirectMoveTo(&Tar);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::Dead_Logic(uint32 uTime)
{
	__GUARD__ if(m_paramAI_Dead.m_AutoTimer.CountingTimer(uTime))
	{
		Relive(CITY_POS_RELIVE);
	}

	if(!GetCharacter()->IsDie())
	{
		ChangeState(ESTATE_IDLE);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::TeamFollow_Logic(uint32 uTime)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Player::CheckTargetValid(SpellID_t nSkillID, ObjID_t TargetID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(nSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSkillTemplate)
	{
		return FALSE;
	}

	if(pSkillTemplate->GetSelectType() != SELECT_TYPE_CHARACTER)
	{
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object	*pObj = GetCharacter()->GetSpecificObjInSameSceneByID(TargetID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj)
	{
		return FALSE;
	}

	if(FALSE == IsObjCharacter(pObj->GetObjType()))
	{
		return FALSE;
	}

	

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pCharacter = (Character *) pObj;
	int32		nState = pSkillTemplate->GetTargetMustInSpecialState();
	BOOL		bMustAlive = 0 == nState || -1 == nState;
	BOOL		bMustDead = 1 == nState || -1 == nState;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pCharacter)
	{
		return FALSE;
	}

	if(!pCharacter->IsActiveObj())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bAlive = pCharacter->IsAlive();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bAlive && bMustAlive)
	{
		return TRUE;
	}
	else if(!bAlive && bMustDead)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::ForceInterruptAllSpell(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pCharacter = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pCharacter != NULL);
	if(pCharacter == NULL) return;
	m_paramAI_UseSpell.Clear();
	GetGlobalActionDelegator().InterruptCurrentAction(*pCharacter);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::ForceInterruptAutoSpell(void)
{
	__GUARD__ m_paramAI_UseSpell.AutoSpell_CleanUp();

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::TeamMemeberToMove(void)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Player::IsEnterCombatState(ObjID_t idSkill, ObjID_t idTarget)
{
	Character* pCharacter = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pCharacter != NULL);
	if (pCharacter == NULL) return FALSE;

	if (INVALID_ID == idSkill)
	{
		m_paramAI_UseSpell.Clear();
		return FALSE;
	}

	if (FALSE == pCharacter->IsAlive())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellTemplateData const* pSkill = DataManager::GetSingletonPtr()->getSpellTemplate(idSkill);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pSkill)
	{
		return FALSE;
	}


	if (pSkill->IsAutoShotSkill())
	{
		m_paramAI_UseSpell.m_nAutoShotSpell = idSkill;
		m_paramAI_UseSpell.m_nAutoShotTargetObjID = idTarget;

		return TRUE;
	}

	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::PushSpellToQueue
(
	ObjID_t idSkill,
	ObjID_t idTarget,
	float	fTargetX,
	float	fTargetZ,
	int32	iHurtDelayTime,
	float	fDir,
	GUID_t	guidTarget,
	BOOL	bChildSkill
)
{
	SpellTemplateData const* pSkill = DataManager::GetSingletonPtr()->getSpellTemplate(idSkill);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pSkill)
	{
		return;
	}

	if (NULL != m_pCharacter)
	{
		SpellTargetingAndDepletingParams	rParams = m_pCharacter->GetTargetingAndDepletingParams();

		if (FALSE == GetGlobalActionDelegator().CanDoNextAction(*m_pCharacter))
		{
			if (idSkill == rParams.GetActivatedSpell())
			{
				return;
			}
		}

		if (pSkill->CanInterruptAutoShot())
		{
			m_paramAI_UseSpell.AutoSpell_CleanUp();
		}

		if (bChildSkill)
		{
			m_paramAI_UseSpell.m_nChildSpell = idSkill;
			m_paramAI_UseSpell.m_nChildSpellTargetObjID = idTarget;
			m_paramAI_UseSpell.m_ChildSpellPosition.m_fX = fTargetX;
			m_paramAI_UseSpell.m_ChildSpellPosition.m_fZ = fTargetZ;
		}
		else
		{
			m_paramAI_UseSpell.m_nQueuedSpell = idSkill;
			m_paramAI_UseSpell.m_nQueueTargetObjID = idTarget;
			m_paramAI_UseSpell.m_fQueueTargetDirection = fDir;
			m_paramAI_UseSpell.m_QueueTargetPosition.m_fX = fTargetX;
			m_paramAI_UseSpell.m_QueueTargetPosition.m_fZ = fTargetZ;
			m_paramAI_UseSpell.m_guidQueueTarget = guidTarget;
			m_paramAI_UseSpell.m_iHurtDelayTime = iHurtDelayTime;
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::PushItemToQueue
(
	ID_t		nBagIndex,
	ObjID_t		nTargetObj,
	const GLPos &posTarget,
	SHorseGuid&guidTargetPet,
	ID_t		nTargetItem
)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::After_Die(ObjID_t idKiller)
{
	LeaveTeam_After_Die();
	RleasePet_After_Die();
	CanRelive_After_Die();
	Stall_After_Die();

	Penalty_After_Die(idKiller);
	Wedding_After_Die();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::LeaveTeam_After_Die()
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::RleasePet_After_Die()
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::CanRelive_After_Die()
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::Penalty_After_Die(ObjID_t idKiller)
{
	__GUARD__ return;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Player::Stall_After_Die(void)
{
	
}


void Behavior_Player::Exchange_After_Die(void)
{
}


void Behavior_Player::PunishmentType_After_Die(int32 &nPenaltyID, ObjID_t idKiller)
{
	
}

void Behavior_Player::Punishment_Exp_After_Die(const SDiePenaltyInfo *pPenaltyInfo, Player *pPlayer)
{
	
}


void Behavior_Player::Punishment_Money_After_Die(const SDiePenaltyInfo *pPenaltyInfo, Player *pPlayer)
{
}

void Behavior_Player::Punishment_EquipDur_After_Die(const SDiePenaltyInfo *pPenaltyInfo, Player *pPlayer)
{
	
}


void Behavior_Player::Punishment_ItemDrop_After_Die(const SDiePenaltyInfo *pPenaltyInfo, Player *pPlayer)
{
	
}

void Behavior_Player::Punishment_EquipDrop_After_Die(const SDiePenaltyInfo *pPenaltyInfo, Player *pPlayer)
{
	
}


void Behavior_Player::Wedding_After_Die(void)
{
	
}
