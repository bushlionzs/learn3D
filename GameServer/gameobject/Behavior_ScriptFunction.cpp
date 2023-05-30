/*$T MapServer/Server/AI/Behavior_ScriptFunction.cpp GC 1.140 10/10/07 10:07:19 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Object.h"
#include "Pet.h"
#include "Character.h"
#include "Monster.h"
#include "Player.h"
#include "Behavior_Character.h"
#include "Behavior_Monster.h"
#include "Behavior_Player.h"
#include "Behavior_Pet.h"
#include "TabDefine.h"
#include "BaseTool.h"
#include "map/game_map.h"
#include "Behavior_ScriptFunction.h"

enum eBHSTATE
{
	SIDLE		= ESTATE_IDLE,
	SAPPROACH	= ESTATE_APPROACH,
	SATTACK		= ESTATE_COMBAT,
	SFOLLOW		= ESTATE_TEAMFOLLOW,
	SRETURN		= ESTATE_GOHOME,
	SPATROL		= ESTATE_PATROL,
	SFLEE		= ESTATE_FLEE,
	SPELLSECTION	= ESTATE_NUMBER + 1,
	ONBESPELLSECTION,
	ONDAMAGESECTION,
	ONDEADSECTION,
	ERRORCMD,
};

BHSFuncMap	g_BehaviorFuncTab[] = { REGISTERAISFUNC(BehaviorStateStartPatrol) };

BHSMacroMap	g_BehaviorMacroTab[] =
{
	"SIDLE",
	SIDLE,
	"SAPPROACH",
	SAPPROACH,
	"SFLEE",
	SFLEE,
	"SATTACK",
	SATTACK,
	"SFOLLOW",
	SFOLLOW,
	"SPATROL",
	SPATROL,
	"SRETURN",
	SRETURN,
	"SKILLSECTION",
	SPELLSECTION,
	"ONBESKILLSECTION",
	ONBESPELLSECTION,
	"ONDAMAGESECTION",
	ONDAMAGESECTION,
	"ONDEADSECTION",
	ONDEADSECTION,
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */

const PLAISFunc Name2FuncPtr(const char *funcName)
{
	__GUARD__ for(int32 i = 0; i < sizeof(g_BehaviorFuncTab) / sizeof(BHSFuncMap); ++i)
	{
		if(strcmp(funcName, g_BehaviorFuncTab[i].funcname) == 0)
		{
			return g_BehaviorFuncTab[i].Func;
		}
	}

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const char *Ptr2FuncName(const PLAISFunc FuncPtr)
{
	__GUARD__ for(int32 i = 0; i < sizeof(g_BehaviorFuncTab) / sizeof(BHSFuncMap); ++i)
	{
		if(FuncPtr == g_BehaviorFuncTab[i].Func)
		{
			return g_BehaviorFuncTab[i].funcname;
		}
	}

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const int32 Name2Macro(const char *MacroName)
{
	__GUARD__ for(int32 i = 0; i < sizeof(g_BehaviorMacroTab) / sizeof(BHSMacroMap); ++i)
	{
		if(strcmp(MacroName, g_BehaviorMacroTab[i].Macroname) == 0)
		{
			return g_BehaviorMacroTab[i].MacroID;
		}
	}

	__UNGUARD__ return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateGetHP(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pChar)
	{
		return INVALID_ID;
	}

	if(pChar->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		return pChar->GetHP() * 100 / pChar->GetMaxHP();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateGetMP(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pChar)
	{
		return INVALID_ID;
	}

	if(pChar->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		return pChar->GetMP() * 100 / pChar->GetMaxHP();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateGetLevel(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	KCheck(pChar);
	if(!pChar)
	{
		return INVALID_ID;
	}

	if(pChar->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		return pChar->GetLevel();
	}

	return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateGetEMP(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pChar)
	{
		return INVALID_ID;
	}

	if(pChar->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	*pEnemy = ((Behavior_Monster *) pChar->GetAIObj())->GetNextTarget();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pEnemy) return pEnemy->GetMP() * 100 / pEnemy->GetMaxMP();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateGetEHP(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pChar)
	{
		return INVALID_ID;
	}

	if(pChar->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	*pEnemy = ((Behavior_Monster *) pChar->GetAIObj())->GetNextTarget();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pEnemy) return pEnemy->GetHP() * 100 / pEnemy->GetMaxHP();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateGetEProfession(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pChar)
	{
		return INVALID_ID;
	}

	if(pChar->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		return((Player *) pChar)->GetProfession();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateGetELevel(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pChar)
	{
		return 0;
	}

	if(pChar->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	*pEnemy = ((Behavior_Monster *) pChar->GetAIObj())->GetNextTarget();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pEnemy) return pEnemy->GetLevel();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateGetESex(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pChar)
	{
		return INVALID_ID;
	}

	if(pChar->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	*pCurEnemy = ((Monster *) pChar)->GetMonsterAI()->GetNextTarget();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pCurEnemy && pCurEnemy->GetObjType() == Object::OBJECT_CLASS_PLAYER)
		{
			return((Player *) pCurEnemy)->GetSex();
		}
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateGetEPK(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	return INVALID_ID;	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateGetEnemyNum(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pChar)
	{
		return INVALID_ID;
	}

	if(pChar->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		return((Monster *) pChar)->GetMonsterAI()->GetThreatCount();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateToFlee(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pChar)
	{
		return INVALID_ID;
	}

	if(pChar->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Behavior_Monster::SAICommand	command;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		command.commandType = Behavior_Monster::E_COMMAND_TYPE_TOFLEE;
		command.param[0] = param0;
		command.param[1] = param1;
		command.param[2] = param2;
		((Monster *) pChar)->GetMonsterAI()->PushCommand(command);
	}

	return 1;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateToSkill(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pChar)
	{
		KCheck(NULL && "BehaviorStateToSkill...pChar=NULL...");
		return INVALID_ID;
	}

	if(pChar->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	*pCurEnemy = ((Monster *) pChar)->GetMonsterAI()->GetNextTarget();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(!pCurEnemy)
		{
			return INVALID_ID;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Behavior_Character	*pAIChar = pChar->GetAIObj();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(!pAIChar)
		{
			KCheck(NULL && "BehaviorStateToSkill...pAIChar=NULL...");
			return INVALID_ID;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		OPT_RESULT		oResult = pAIChar->BHV_UseSpell
			(
				param0,
				pCurEnemy->GetID(),
				pCurEnemy->GetGLPos()->m_fX,
				pCurEnemy->GetGLPos()->m_fZ,
				INVALID_ID
			);
		Behavior_Monster	*pBehavior_Monster = ((Monster *) pChar)->GetMonsterAI();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pBehavior_Monster)
		{
			pBehavior_Monster->SetSpellID(param0);
			pBehavior_Monster->SetSpellErrorCode(oResult);
		}
		else
		{
			KCheck(NULL && "BehaviorStateToSkill...pBehavior_Monster=NULL...");
			return INVALID_ID;
		}

		if(oResult == OR_OK)
		{
			return 1;
		}
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateToSummon(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pChar)
	{
		return INVALID_ID;
	}

	if(pChar->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		if(INVALID_ID == param1 || INVALID_ID == param2)
		{
			param1 = (int32) (pChar->GetGLPos()->m_fX);
			param2 = (int32) (pChar->GetGLPos()->m_fZ);
		}
		((Monster *) pChar)->GetMonsterAI()->SummonTeammate(param1, param2, param0);
		return 1;
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateToSpeak(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateSetPatrolID(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateStartPatrol(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pChar)
	{
		KCheck(NULL && "BehaviorStateStartPatrol...pChar=NULL...");
		return INVALID_ID;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object	*pObj = ((Object *) pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pChar->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Behavior_Monster	*pBehavior_Monster = ((Monster *) pChar)->GetMonsterAI();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pBehavior_Monster)
		{
			pBehavior_Monster->StartPatrol();
		}
	}

	return 1;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateChangeTemplate(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pChar)
	{
		KCheck(NULL && "BehaviorStateStartPatrol...pChar=NULL...");
		return INVALID_ID;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object	*pObj = ((Object *) pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pChar->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Behavior_Monster	*pBehavior_Monster = ((Monster *) pChar)->GetMonsterAI();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pBehavior_Monster)
		{
			pBehavior_Monster->ChangeAITemplete(param0);
		}
	}

	return 1;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateHaveBuff(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateHaveBuffOfLogic(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	

	return INVALID_ID;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateRandomAttack(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pChar)
	{
		KCheck(NULL && "BehaviorStateRandomAttack...pChar=NULL...");
		return INVALID_ID;
	}

	if(pChar->GetObjType() != Object::OBJECT_CLASS_MONSTER)
	{
		KCheck(NULL && "BehaviorStateRandomAttack...pChar!=OBJ_TYPE_MONSTER...");
		return INVALID_ID;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Behavior_Monster	*pMonsterAI = (Behavior_Monster *) pChar->GetAIObj();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pMonsterAI);
	pMonsterAI->RandomAttack(param0);
	return 1;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 AIS_AttackSpecialProfession(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pChar)
	{
		KCheck(NULL && "AIS_AttackSpecialProfession...pChar=NULL...");
		return INVALID_ID;
	}

	if(pChar->GetObjType() != Object::OBJECT_CLASS_MONSTER)
	{
		KCheck(NULL && "AIS_AttackSpecialProfession...pChar!=OBJ_TYPE_MONSTER...");
		return INVALID_ID;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Behavior_Monster	*pMonsterAI = (Behavior_Monster *) pChar->GetAIObj();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pMonsterAI);
	pMonsterAI->AttackSpecialProfession(param0, param1);
	return 1;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BehaviorStateUseSkillToSpecialProfession(Character *pChar, int32 param0, int32 param1, int32 param2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pChar)
	{
		KCheck(NULL && "BehaviorStateRandomAttack...pChar=NULL...");
		return INVALID_ID;
	}

	if(pChar->GetObjType() != Object::OBJECT_CLASS_MONSTER)
	{
		KCheck(NULL && "BehaviorStateRandomAttack...pChar!=OBJ_TYPE_MONSTER...");
		return INVALID_ID;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Behavior_Monster	*pMonsterAI = (Behavior_Monster *) pChar->GetAIObj();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pMonsterAI);
	return pMonsterAI->UseSpellToSpecialProfession(param0, param1);
	__UNGUARD__ return INVALID_ID;
}
