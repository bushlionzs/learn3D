/*$T MapServer/Server/Script/LuaMacro.h GC 1.140 10/10/07 10:07:52 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _LUASCRIPT_LUAMACRO_H_
#define _LUASCRIPT_LUAMACRO_H_
#define LUA_ASSERT(expression) assert(expression)
namespace	LuaScript
{
#ifdef __WINDOWS__
#define BEGMAPDEFINE(FUNCNAME) \
	{ \
		const char	strFuncName[] = FUNCNAME; \
		_NET_TRY \
		{ \
			Map	*pMap = (Map *) (g_pMapManager->GetMap(mapId)); \
			KCheckEx(pMap, "地图ID错误 "##FUNCNAME); \
			if(pMap) \
			{ \
				KCheck(KGetCurrentTID() == pMap->m_ThreadID); \
			}
#define ENDMAPDEFINE \
} \
_NET_CATCH \
{ \
	QLogSystem::QUICK_LOG(QUICK_LOG_ERROR, "ERROR: ENDMAPDEFINE (%s)", strFuncName); \
	if(mapId > 0 && mapId < MAX_SCENE) \
	{ \
		for(int32 i = 0; i < LuaStack::RunStack[mapId].m_nCurrentStep; i++) \
		{ \
			QLogSystem::QUICK_LOG \
				( \
					QUICK_LOG_ERROR, \
					"Stack:%d %s", \
					LuaStack::RunStack[mapId].m_StackStep[i].m_idScriptStep, \
					LuaStack::RunStack[mapId].m_StackStep[i].m_strFunctionStep \
				); \
		} \
	} \
} \
}

#define BEGCHARCTERDEFINE(FUNCNAME) \
	{ \
		const char	strFuncName[] = FUNCNAME; \
		_NET_TRY \
		{ \
			Map	*pMap = (Map *) (g_pMapManager->GetMap(mapId)); \
			KCheckEx(pMap, "地图ID错误 "##FUNCNAME); \
			if(pMap) \
			{ \
				KCheck(KGetCurrentTID() == pMap->m_ThreadID); \
				Object	*pObj = (Object *) (pMap->GetObjManager()->GetObj(selfId)); \
				KCheckEx(pObj, "selfId错误 "##FUNCNAME); \
				if(pObj && IsObjCharacter(pObj->GetObjType())) \
				{ \
					Character	*pCharacter = (Character *) pObj; \
					KCheckEx(pCharacter, "Obj到Obj_Character类型转换失败 "##FUNCNAME); \
					if(pCharacter) \
					{ \
					}
#define ENDCHARCTERDEFINE \
} \
} \
} \
_NET_CATCH \
{ \
QLogSystem::QUICK_LOG(QUICK_LOG_ERROR, "ERROR: ENDCHARCTERDEFINE(%s)", strFuncName); \
if(mapId > 0 && mapId < MAX_SCENE) \
{ \
for(int32 i = 0; i < LuaStack::RunStack[mapId].m_nCurrentStep; i++) \
{ \
	QLogSystem::QUICK_LOG \
		( \
			QUICK_LOG_ERROR, \
			"Stack:%d %s", \
			LuaStack::RunStack[mapId].m_StackStep[i].m_idScriptStep, \
			LuaStack::RunStack[mapId].m_StackStep[i].m_strFunctionStep \
		); \
} \
} \
} \
}

#define BEGPLAYERDEFINE(FUNCNAME) \
	{ \
		const char	strFuncName[] = FUNCNAME; \
		_NET_TRY \
		{ \
			Map	*pMap = (Map *) (g_pMapManager->GetMap(mapId)); \
			KCheckEx(pMap, "地图ID错误 "##FUNCNAME); \
			if(pMap) \
			{ \
				KCheck(KGetCurrentTID() == pMap->m_ThreadID); \
				Object	*pObj = (Object *) (pMap->GetObjManager()->GetObj(selfId)); \
				KCheckEx(pObj, "selfId错误 "##FUNCNAME); \
				if(pObj && IsObjCharacter(pObj->GetObjType())) \
				{ \
					Character	*pCharacter = (Character *) pObj; \
					KCheckEx(pCharacter, "Obj到Obj_Character类型转换失败 "##FUNCNAME); \
					if(pCharacter && pCharacter->GetObjType() == Object::OBJECT_CLASS_PLAYER) \
					{ \
						Player	*pPlayer = (Player *) pCharacter; \
						KCheckEx(pPlayer, "Obj_Character到Obj_Human类型转换失败 "##FUNCNAME); \
						if(pPlayer) \
						{ \
						}
#define ENDPLAYERDEFINE \
} \
} \
} \
} \
_NET_CATCH \
{ \
QLogSystem::QUICK_LOG(QUICK_LOG_ERROR, "ERROR: ENDPLAYERDEFINE(%s)", strFuncName); \
if(mapId > 0 && mapId < MAX_SCENE) \
{ \
for(int32 i = 0; i < LuaStack::RunStack[mapId].m_nCurrentStep; i++) \
{ \
QLogSystem::QUICK_LOG \
	( \
		QUICK_LOG_ERROR, "Stack:%d %s", LuaStack::RunStack[mapId].m_StackStep[i].m_idScriptStep, LuaStack::RunStack[ \
			mapId].m_StackStep[i].m_strFunctionStep \
	); \
} \
} \
} \
}

#define BEGMONSTERDEFINE(FUNCNAME) \
	{ \
		const char	strFuncName[] = FUNCNAME; \
		_NET_TRY \
		{ \
			Map	*pMap = (Map *) (g_pMapManager->GetMap(mapId)); \
			KCheckEx(pMap, "地图ID错误 "##FUNCNAME); \
			if(pMap) \
			{ \
				KCheck(KGetCurrentTID() == pMap->m_ThreadID); \
				Object	*pObj = (Object *) (pMap->GetObjManager()->GetObj(selfId)); \
				KCheckEx(pObj, "selfId错误 "##FUNCNAME); \
				if(pObj && IsObjCharacter(pObj->GetObjType())) \
				{ \
					Character	*pCharacter = (Character *) pObj; \
					KCheckEx(pCharacter, "Obj到Obj_Character类型转换失败 "##FUNCNAME); \
					if(pCharacter && pCharacter->GetObjType() == Object::OBJECT_CLASS_MONSTER) \
					{ \
						Monster *pMonster = (Monster *) pCharacter; \
						KCheckEx(pMonster, "Obj_Character到Obj_Monster类型转换失败 "##FUNCNAME); \
						if(pMonster) \
						{ \
						}
#define ENDMONSTERDEFINE \
} \
} \
} \
} \
_NET_CATCH \
{ \
QLogSystem::QUICK_LOG(QUICK_LOG_ERROR, "ERROR: ENDMONSTERDEFINE(%s)", strFuncName); \
if(mapId > 0 && mapId < MAX_SCENE) \
{ \
for(int32 i = 0; i < LuaStack::RunStack[mapId].m_nCurrentStep; i++) \
{ \
QLogSystem::QUICK_LOG \
	( \
		QUICK_LOG_ERROR, "Stack:%d %s", LuaStack::RunStack[mapId].m_StackStep[i].m_idScriptStep, LuaStack::RunStack[ \
			mapId].m_StackStep[i].m_strFunctionStep \
	); \
} \
} \
} \
}

#define BEGBUSDEFINE(FUNCNAME) \
	{ \
		const char	strFuncName[] = FUNCNAME; \
		_NET_TRY \
		{ \
			Map	*pMap = (Map *) (g_pMapManager->GetMap(mapId)); \
			KCheckEx(pMap, "地图ID错误 "##FUNCNAME); \
			if(pMap) \
			{ \
				KCheck(KGetCurrentTID() == pMap->m_ThreadID); \
				Object	*pObj = (Object *) (pMap->GetObjManager()->GetObj(selfId)); \
				KCheckEx(pObj, "selfId错误 "##FUNCNAME); \
				if(pObj && IsObjCharacter(pObj->GetObjType())) \
				{ \
					Character	*pCharacter = (Character *) pObj; \
					KCheckEx(pCharacter, "Obj到Obj_Character类型转换失败 "##FUNCNAME); \
					if(pCharacter && pCharacter->GetObjType() == Object::OBJECT_CLASS_BUS) \
					{ \
						Bus	*pBus = (Bus *) pCharacter; \
						KCheckEx(pBus, "Obj_Character到Obj_Bus类型转换失败 "##FUNCNAME); \
						if(pBus) \
						{ \
						}
#define ENDBUSDEFINE \
} \
} \
} \
} \
_NET_CATCH \
{ \
QLogSystem::QUICK_LOG(QUICK_LOG_ERROR, "ERROR: ENDBUSDEFINE(%s)", strFuncName); \
if(mapId > 0 && mapId < MAX_SCENE) \
{ \
for(int32 i = 0; i < LuaStack::RunStack[mapId].m_nCurrentStep; i++) \
{ \
QLogSystem::QUICK_LOG \
	( \
		QUICK_LOG_ERROR, "Stack:%d %s", LuaStack::RunStack[mapId].m_StackStep[i].m_idScriptStep, LuaStack::RunStack[ \
			mapId].m_StackStep[i].m_strFunctionStep \
	); \
} \
} \
} \
}

#define __LUA_GUARD__ \
	{ \
		try \
		{
#define __LUA_UNGUARD__ \
} \
catch(...) \
{ \
	QLogSystem::SLOW_LOG(SLOW_LOG_SERVERERROR, "Lua Error %s %d %s", __FILE__, __LINE__, __FUNCTION__); \
} \
}

#elif __LINUX__
#define BEGMAPDEFINE(FUNCNAME) \
	{ \
		const char	strFuncName[] = FUNCNAME; \
		_NET_TRY \
		{ \
			Map	*pMap = (Map *) (g_pMapManager->GetMap(mapId)); \
			KCheckEx(pMap, "地图ID错误 "FUNCNAME); \
			if(pMap) \
			{ \
				KCheck(KGetCurrentTID() == pMap->m_ThreadID); \
			}
#define ENDMAPDEFINE \
} \
_NET_CATCH \
{ \
	QLogSystem::QUICK_LOG(QUICK_LOG_ERROR, "ERROR: ENDMAPDEFINE(%s)", strFuncName); \
	if(mapId > 0 && mapId < MAX_SCENE) \
	{ \
		for(int32 i = 0; i < LuaStack::RunStack[mapId].m_nCurrentStep; i++) \
		{ \
			QLogSystem::QUICK_LOG \
				( \
					QUICK_LOG_ERROR, \
					"Stack:%d %s", \
					LuaStack::RunStack[mapId].m_StackStep[i].m_idScriptStep, \
					LuaStack::RunStack[mapId].m_StackStep[i].m_strFunctionStep \
				); \
		} \
	} \
} \
}

#define BEGCHARCTERDEFINE(FUNCNAME) \
	{ \
		const char	strFuncName[] = FUNCNAME; \
		_NET_TRY \
		{ \
			Map	*pMap = (Map *) (g_pMapManager->GetMap(mapId)); \
			KCheckEx(pMap, "地图ID错误 "FUNCNAME); \
			if(pMap) \
			{ \
				KCheck(KGetCurrentTID() == pMap->m_ThreadID); \
				Object	*pObj = (Object *) (pMap->GetObjManager()->GetObj(selfId)); \
				KCheckEx(pObj, "selfId错误 "FUNCNAME); \
				if(pObj && IsObjCharacter(pObj->GetObjType())) \
				{ \
					Character	*pCharacter = (Character *) pObj; \
					KCheckEx(pCharacter, "Obj到Obj_Character类型转换失败 "FUNCNAME); \
					if(pCharacter) \
					{ \
					}
#define ENDCHARCTERDEFINE \
} \
} \
} \
_NET_CATCH \
{ \
QLogSystem::QUICK_LOG(QUICK_LOG_ERROR, "ERROR: ENDCHARCTERDEFINE(%s)", strFuncName); \
if(mapId > 0 && mapId < MAX_SCENE) \
{ \
for(int32 i = 0; i < LuaStack::RunStack[mapId].m_nCurrentStep; i++) \
{ \
	QLogSystem::QUICK_LOG \
		( \
			QUICK_LOG_ERROR, \
			"Stack:%d %s", \
			LuaStack::RunStack[mapId].m_StackStep[i].m_idScriptStep, \
			LuaStack::RunStack[mapId].m_StackStep[i].m_strFunctionStep \
		); \
} \
} \
} \
}

#define BEGPLAYERDEFINE(FUNCNAME) \
	{ \
		const char	strFuncName[] = FUNCNAME; \
		_NET_TRY \
		{ \
			Map	*pMap = (Map *) (g_pMapManager->GetMap(mapId)); \
			KCheckEx(pMap, "地图ID错误 "FUNCNAME); \
			if(pMap) \
			{ \
				KCheck(KGetCurrentTID() == pMap->m_ThreadID); \
				Object	*pObj = (Object *) (pMap->GetObjManager()->GetObj(selfId)); \
				KCheckEx(pObj, "selfId错误 "FUNCNAME); \
				if(pObj && IsObjCharacter(pObj->GetObjType())) \
				{ \
					Character	*pCharacter = (Character *) pObj; \
					KCheckEx(pCharacter, "Obj到Obj_Character类型转换失败 "FUNCNAME); \
					if(pCharacter && pCharacter->GetObjType() == Object::OBJECT_CLASS_PLAYER) \
					{ \
						Player	*pPlayer = (Player *) pCharacter; \
						KCheckEx(pPlayer, "Obj_Character到Obj_Human类型转换失败 "FUNCNAME); \
						if(pPlayer) \
						{ \
						}
#define ENDPLAYERDEFINE \
} \
} \
} \
} \
_NET_CATCH \
{ \
QLogSystem::QUICK_LOG(QUICK_LOG_ERROR, "ERROR: ENDPLAYERDEFINE(%s)", strFuncName); \
if(mapId > 0 && mapId < MAX_SCENE) \
{ \
for(int32 i = 0; i < LuaStack::RunStack[mapId].m_nCurrentStep; i++) \
{ \
QLogSystem::QUICK_LOG \
	( \
		QUICK_LOG_ERROR, "Stack:%d %s", LuaStack::RunStack[mapId].m_StackStep[i].m_idScriptStep, LuaStack::RunStack[ \
			mapId].m_StackStep[i].m_strFunctionStep \
	); \
} \
} \
} \
}

#define BEGMONSTERDEFINE(FUNCNAME) \
	{ \
		const char	strFuncName[] = FUNCNAME; \
		_NET_TRY \
		{ \
			Map	*pMap = (Map *) (g_pMapManager->GetMap(mapId)); \
			KCheckEx(pMap, "地图ID错误 "FUNCNAME); \
			if(pMap) \
			{ \
				KCheck(KGetCurrentTID() == pMap->m_ThreadID); \
				Object	*pObj = (Object *) (pMap->GetObjManager()->GetObj(selfId)); \
				KCheckEx(pObj, "selfId错误 "FUNCNAME); \
				if(pObj && IsObjCharacter(pObj->GetObjType())) \
				{ \
					Character	*pCharacter = (Character *) pObj; \
					KCheckEx(pCharacter, "Obj到Obj_Character类型转换失败 "FUNCNAME); \
					if(pCharacter && pCharacter->GetObjType() == Object::OBJECT_CLASS_MONSTER) \
					{ \
						Monster *pMonster = (Monster *) pCharacter; \
						KCheckEx(pMonster, "Obj_Character到Obj_Monster类型转换失败 "FUNCNAME); \
						if(pMonster) \
						{ \
						}
#define ENDMONSTERDEFINE \
} \
} \
} \
} \
_NET_CATCH \
{ \
QLogSystem::QUICK_LOG(QUICK_LOG_ERROR, "ERROR: ENDMONSTERDEFINE(%s)", strFuncName); \
if(mapId > 0 && mapId < MAX_SCENE) \
{ \
for(int32 i = 0; i < LuaStack::RunStack[mapId].m_nCurrentStep; i++) \
{ \
QLogSystem::QUICK_LOG \
	( \
		QUICK_LOG_ERROR, "Stack:%d %s", LuaStack::RunStack[mapId].m_StackStep[i].m_idScriptStep, LuaStack::RunStack[ \
			mapId].m_StackStep[i].m_strFunctionStep \
	); \
} \
} \
} \
}

#define BEGBUSDEFINE(FUNCNAME) \
	{ \
		const char	strFuncName[] = FUNCNAME; \
		_NET_TRY \
		{ \
			Map	*pMap = (Map *) (g_pMapManager->GetMap(mapId)); \
			KCheckEx(pMap, "地图ID错误 "FUNCNAME); \
			if(pMap) \
			{ \
				KCheck(KGetCurrentTID() == pMap->m_ThreadID); \
				Object	*pObj = (Object *) (pMap->GetObjManager()->GetObj(selfId)); \
				KCheckEx(pObj, "selfId错误 "FUNCNAME); \
				if(pObj && IsObjCharacter(pObj->GetObjType())) \
				{ \
					Character	*pCharacter = (Character *) pObj; \
					KCheckEx(pCharacter, "Obj到Obj_Character类型转换失败 "FUNCNAME); \
					if(pCharacter && pCharacter->GetObjType() == Object::OBJECT_CLASS_BUS) \
					{ \
						Bus	*pBus = (Bus *) pCharacter; \
						KCheckEx(pBus, "Obj_Character到Obj_Bus类型转换失败 "FUNCNAME); \
						if(pBus) \
						{ \
						}
#define ENDBUSDEFINE \
} \
} \
} \
} \
_NET_CATCH \
{ \
QLogSystem::QUICK_LOG(QUICK_LOG_ERROR, "ERROR: ENDBUSDEFINE(%s)", strFuncName); \
if(mapId > 0 && mapId < MAX_SCENE) \
{ \
for(int32 i = 0; i < LuaStack::RunStack[mapId].m_nCurrentStep; i++) \
{ \
QLogSystem::QUICK_LOG \
	( \
		QUICK_LOG_ERROR, "Stack:%d %s", LuaStack::RunStack[mapId].m_StackStep[i].m_idScriptStep, LuaStack::RunStack[ \
			mapId].m_StackStep[i].m_strFunctionStep \
	); \
} \
} \
} \
}

#define __LUA_GUARD__ \
	{ \
		try \
		{
#define __LUA_UNGUARD__ \
} \
catch(...) \
{ \
	QLogSystem::SLOW_LOG(SLOW_LOG_SERVERERROR, "Lua Error %s %d %s", __FILE__, __LINE__, __PRETTY_FUNCTION__); \
} \
}
#endif
#define LUA_RETURNERROR_0 \
	{ \
		return 0; \
	}
#define LUA_RETURNERROR_1 \
	{ \
		Lua_PushNumber(L, -1); \
		return 1; \
	}
#define LUA_RETURNERROR_2 \
	{ \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		return 2; \
	}
#define LUA_RETURNERROR_3 \
	{ \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		return 3; \
	}
#define LUA_RETURNERROR_4 \
	{ \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		return 4; \
	}
#define LUA_RETURNERROR_5 \
	{ \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		return 5; \
	}
#define LUA_RETURNERROR_6 \
	{ \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		return 6; \
	}
#define LUA_RETURNERROR_7 \
	{ \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		return 7; \
	}
#define LUA_RETURNERROR_8 \
	{ \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		return 8; \
	}
#define LUA_RETURNERROR_9 \
	{ \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		Lua_PushNumber(L, -1); \
		return 9; \
	}

#define LUA_CHECKPARAMNUM_ER0(a)	{ if(LuaSystem::CheckParamNum(L, (a)) == FALSE) LUA_RETURNERROR_0; }
#define LUA_CHECKPARAMNUM_ER1(a)	{ if(LuaSystem::CheckParamNum(L, (a)) == FALSE) LUA_RETURNERROR_1; }
#define LUA_CHECKPARAMNUM_ER2(a)	{ if(LuaSystem::CheckParamNum(L, (a)) == FALSE) LUA_RETURNERROR_2; }
#define LUA_CHECKPARAMNUM_ER3(a)	{ if(LuaSystem::CheckParamNum(L, (a)) == FALSE) LUA_RETURNERROR_3; }
#define LUA_CHECKPARAMNUM_ER4(a)	{ if(LuaSystem::CheckParamNum(L, (a)) == FALSE) LUA_RETURNERROR_4; }
#define LUA_CHECKPARAMNUM_ER5(a)	{ if(LuaSystem::CheckParamNum(L, (a)) == FALSE) LUA_RETURNERROR_5; }
#define LUA_CHECKPARAMNUM_ER6(a)	{ if(LuaSystem::CheckParamNum(L, (a)) == FALSE) LUA_RETURNERROR_6; }
#define LUA_CHECKPARAMNUM_ER7(a)	{ if(LuaSystem::CheckParamNum(L, (a)) == FALSE) LUA_RETURNERROR_7; }
#define LUA_CHECKPARAMNUM_ER8(a)	{ if(LuaSystem::CheckParamNum(L, (a)) == FALSE) LUA_RETURNERROR_8; }
#define LUA_CHECKPARAMNUM_ER9(a)	{ if(LuaSystem::CheckParamNum(L, (a)) == FALSE) LUA_RETURNERROR_9; }
}
#pragma warning(disable : 4244)
void	Q_strncpyz(char* dest, const char* src, int32 destsize);
#endif
