#include "stdafx.h"
#include "LuaSystem.h"
#include "LuaMacro.h"
#include "ScriptCacheMgr.h"
#include "StructScript.h"
#include "BaseTool.h"
#include "LuaFunction.h"
#include "map/map_manager.h"
#include "server_manager.h"

#define LUA_DISABLE_VERIFYFUNCTION
void LuaErrorInfo(LuaPlus::LuaStateOwner& owner)
{
	lua_State* L = owner->GetCState();
	int type = lua_type(L, -1);
	if (type != 4)
		return;
	std::string error = lua_tostring(L, -1);
	std::cout << error;
}

void LuaErrorInfo(lua_State* L)
{
	int type = lua_type(L, -1);
	if (type != 4)
		return;
	std::string error = lua_tostring(L, -1);
	std::cout << error;
}

extern ScriptCache* GetScriptFileData(ScriptID_t scriptid);


BOOL LuaSystem::	Lua_ReloadScriptAlways = TRUE;
BOOL LuaSystem::	Lua_RecordScriptStep = FALSE;
const char *LuaSystem:: Lua_ScriptStepFileName = "SCRIPT_STEP_FILENAME";
const int32 LuaSystem:: Lua_MaxScriptCount = 4096;


int32_t LuaFunction_CallScriptFunction(Lua_State* L)
{
	LuaStack args(L);

	
	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsString())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ScriptID_t	scriptId = Lua_ValueToNumber(L, 1);
	const char* funcname = Lua_ValueToString(L, 2);
	int32		nMapID = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


	LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();

	if (!luaSystem->loadScript(scriptId))
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}
	


	std::string fullfuncname = "x" + std::to_string(scriptId) + "_" + funcname;


	lua_getglobal(L, fullfuncname.c_str());

	if (lua_type(L, -1) != LUA_TFUNCTION)
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}
	int count = Lua_GetTopIndex(L);
	for (int32_t i = 3; i < count; i++)
	{
		switch (Lua_GetValueType(L, i))
		{
		case LUA_TUSERDATA:
			KCheck(FALSE);
			break;

		case LUA_TNIL:
			Lua_PushNil(L);
			break;

		case LUA_TNUMBER:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	num = Lua_ValueToNumber(L, i);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			Lua_PushNumber(L, num);
		}
		break;

		case LUA_TSTRING:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			const char* str = Lua_ValueToString(L, i);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			Lua_PushString(L, str);
		}
		break;

		case LUA_TTABLE:
			KCheck(FALSE);
			break;

		case LUA_TFUNCTION:
		default:
			Lua_PushCFunction(L, Lua_ValueToCFunction(L, i));
			break;
		}
	}
	
	int ret = lua_pcall(L, count - 3, 0, 0);
	if (ret)
	{
		LuaErrorInfo(L);
	}

	return 0;
}

LuaSystem::LuaSystem(void)
{
	__GUARD__;
	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
LuaSystem::~LuaSystem(void)
{
	__GUARD__;
	Release();
	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */

int32_t LuaFunction_Panic(Lua_State* L)
{
	return 0;
}

void LuaSystem::Initialize(void)
{
	__GUARD__;

	mScriptDirectory = "D:\\Khan2\\Bin\\Client\\Public\\Data\\Script\\";

	m_LuaState->OpenLibs();
	m_LuaState->AtPanic(LuaFunction_Panic);
	RegFunction();
	bool bRet = LuaLoadScript("ScriptGlobal.lua");
	KCheck(bRet && "Load ScriptGlobal.lua failed");


	//载入所有脚本,做最大化测试

// 	for( int i = 0; i<g_ScriptFileMgr.GetCount();++i )
// 	{
// 		SFileData* pData = g_ScriptFileMgr.GetFileDataByIndex(i);
// 		ReloadScript(0, pData->GetID());
// 	}

	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void LuaSystem::Release(void)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL LuaSystem::FindFunction(Lua_State *L, char *funcname)
{
	__GUARD__;

	Lua_GetGlobal(L, funcname);
	if(lua_isnil(L, -1))
	{
		Lua_Pop(L, 1);
		return FALSE;
	}
	else
	{
		Lua_Pop(L, 1);
		return TRUE;
	}

	__UNGUARD__;

	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL LuaSystem::VerifyFunction(Lua_State *L, char **funcname)
{
	__GUARD__;

	if(!FindFunction(L, *funcname))
#ifdef LUA_DISABLE_VERIFYFUNCTION
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		char	*pSrc = strchr(*funcname, '_') + 1;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		memmove(*funcname, pSrc, strlen(pSrc) + 1);
		if(!FindFunction(L, *funcname))
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifdef _DEBUG
			char	strBuf[256] = { 0 };
			/*~~~~~~~~~~~~~~~~~~~~~~~~*/

			Lua_GetGlobal(L, LuaSystem::Lua_ScriptStepFileName);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			const char	*filename = Lua_ValueToString(L, 1);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			tsnprintf(strBuf, 256, "cann't find %s in %s", *funcname, filename);
			Lua_Pop(L, 1);

			KCheckEx(0, strBuf);
#endif
			return FALSE;
		}
	}

#else
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifdef _DEBUG
		char	strBuf[256];
		char	*filename = Lua_GetGlobal(L, LuaSystem::Lua_ScriptStepFileName);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		tsnprintf(strBuf, 256, "cann't find %s in %s", *funcname, filename);
		Lua_Pop(L, 1);

		KCheckEx(0, strBuf);
#endif
		return FALSE;
	}
#endif
	return TRUE;

	__UNGUARD__;

	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 LuaSystem::RunScriptFunction(MapID_t nMapID, ScriptID_t scriptid, const char *funcname)
{
	if (!loadScript(scriptid))
	{
		return -1;
	}

	std::string fullfuncname = "x" + std::to_string(scriptid) + "_" + funcname;
	auto luaObj = m_LuaState->GetGlobal(fullfuncname.c_str());
	LuaFunction<int32_t> func(luaObj);
	int v = func();

	
	return v;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 LuaSystem::RunScriptFunction(MapID_t nMapID, ScriptID_t scriptid, const char *funcname, int32 Param0)
{
	if (!loadScript(scriptid))
	{
		return -1;
	}
	std::string fullfuncname = "x" + std::to_string(scriptid) + "_" + funcname;
	auto luaObj = m_LuaState->GetGlobal(fullfuncname.c_str());
	LuaFunction<int32_t> func(luaObj);
	int v = func(Param0);


	return v;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 LuaSystem::RunScriptFunction(MapID_t nMapID, ScriptID_t scriptid, const char *funcname, int32 Param0, int32 Param1)
{
	if (!loadScript(scriptid))
	{
		return -1;
	}
	std::string fullfuncname = "x" + std::to_string(scriptid) + "_" + funcname;
	auto luaObj = m_LuaState->GetGlobal(fullfuncname.c_str());
	LuaFunction<int32_t> func(luaObj);
	int v = func(Param0, Param1);


	return v;
}


int32 LuaSystem::RunScriptFunction(MapID_t nMapID, ScriptID_t scriptid, const char *funcname, int32 Param0, int32 Param1, int32 Param2)
{
	if (!loadScript(scriptid))
	{
		return -1;
	}
	std::string fullfuncname = "x" + std::to_string(scriptid) + "_" + funcname;
	auto luaObj = m_LuaState->GetGlobal(fullfuncname.c_str());
	LuaFunction<int32_t> func(luaObj);
	int v = func(Param0, Param1, Param2);


	return v;
}


int32 LuaSystem::RunScriptFunction(MapID_t nMapID, ScriptID_t scriptid, const char *funcname, int32 Param0, int32 Param1, int32 Param2, int32 Param3)
{
	if (!loadScript(scriptid))
	{
		return -1;
	}
	std::string fullfuncname = "x" + std::to_string(scriptid) + "_" + funcname;
	LuaObject obj = m_LuaState->GetGlobal(fullfuncname.c_str());
	
	

	LuaFunction<int32_t> func = obj;

	
	

	int v = func(Param0, Param1, Param2, Param3);
	return v;
	
}


int32 LuaSystem::RunScriptFunction(MapID_t nMapID, ScriptID_t scriptid, const char *funcname, int32 Param0, int32 Param1, int32 Param2, int32 Param3,int32 Param4)
{
	if (!loadScript(scriptid))
	{
		return -1;
	}
	std::string fullfuncname = "x" + std::to_string(scriptid) + "_" + funcname;
	auto luaObj = m_LuaState->GetGlobal(fullfuncname.c_str());
	LuaFunction<int32_t> func(luaObj);
	
	int v = func(Param0, Param1, Param2, Param3, Param4);
	return v;

}


int32 LuaSystem::RunScriptFunction(MapID_t nMapID, ScriptID_t scriptid, const char *funcname, int32	Param0, int32 Param1, int32	Param2, int32 Param3,int32 Param4,int32	Param5)
{
	
	if (!loadScript(scriptid))
	{
		return -1;
	}
	std::string fullfuncname = "x" + std::to_string(scriptid) + "_" + funcname;
	auto luaObj = m_LuaState->GetGlobal(fullfuncname.c_str());
	LuaFunction<int32_t> func(luaObj);
	int v = func(Param0, Param1, Param2, Param3, Param4, Param5);

	return v;
}


int32 LuaSystem::RunScriptFunction(MapID_t nMapID, ScriptID_t scriptid, const char *funcname, int32 Param0, int32 Param1, int32 Param2, int32 Param3,int32 Param4,int32	Param5,int32 Param6)
{
	if (!loadScript(scriptid))
	{
		return -1;
	}
	std::string fullfuncname = "x" + std::to_string(scriptid) + "_" + funcname;
	auto luaObj = m_LuaState->GetGlobal(fullfuncname.c_str());
	LuaFunction<int32_t> func(luaObj);
	int v = func(Param0, Param1, Param2, Param3, Param4, Param5, Param6);

	return v;
}

int32				LuaSystem::RunScriptFunction(MapID_t nMapID, ScriptID_t idScript, const char* szFunction, int32 Param0, int32 Param1, int32 Param2, int32 Param3, int32 Param4, int32	Param5, int32 Param6, int32 Param7)
{
	assert(false);
	return 0;
}

int32				LuaSystem::RunScriptFunction(MapID_t nMapID, ScriptID_t idScript, const char* szFunction, int32 Param0, int32 Param1, int32 Param2, int32 Param3, int32 Param4, int32	Param5, int32 Param6, int32 Param7, int32 Param8)
{
	assert(false);
	return 0;
}

int32				LuaSystem::RunScriptFunction(MapID_t nMapID, ScriptID_t idScript, const char* szFunction, int32 Param0, int32 Param1, float Param2, float Param3)
{
	if (!loadScript(idScript))
	{
		return -1;
	}
	std::string fullfuncname = "x" + std::to_string(idScript) + "_" + szFunction;
	auto luaObj = m_LuaState->GetGlobal(fullfuncname.c_str());
	LuaFunction<int32_t> func(luaObj);
	int v = func(Param0, Param1, Param2, Param3);

	return v;
}

int32				LuaSystem::RunScriptFunction(MapID_t nMapID, ScriptID_t idScript, const char* szFunction, int32 Param0, int32 Param1, const char* strParam2, const char* strParam3)
{
	assert(false);
	return 0;
}
void LuaSystem::EnterRunStep(MapID_t nMapID, ScriptID_t scriptid, const char *funcname)
{
	
}


void LuaSystem::LeaveRunStep(MapID_t nMapID, ScriptID_t scriptid, const char *funcname)
{
	
}


BOOL LuaSystem::ReloadScript(MapID_t nMapID, ScriptID_t scriptid)
{
	return TRUE;
}



bool LuaSystem::loadScript(uint32_t scriptID)
{
	if (m_ScriptLoaded.count(scriptID))
	{
		return true;
	}

	extern ScriptCacheMgr g_ScriptFileMgr;
	ScriptCache* cache = g_ScriptFileMgr.GetFileData(scriptID);

	if (nullptr == cache)
	{
		return false;
	}

	std::string name = mScriptDirectory + cache->GetFileName();

	int ret = m_LuaState->DoFile(name.c_str());

	if (ret != 0)
	{
		LuaErrorInfo(m_LuaState);
		return false;
	}

	m_ScriptLoaded[scriptID] = name;
	return true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL LuaSystem::LuaLoadScript(const char *strLuaScript)
{
	std::string name = mScriptDirectory + strLuaScript;

	int32_t ret = m_LuaState->DoFile(name.c_str());
	
	if (ret == 0)
		return TRUE;

	LuaErrorInfo(m_LuaState);
	
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL LuaSystem::CheckParamNum(Lua_State *L, int32 nCount)
{
	__LUA_GUARD__;
	if(L == NULL) return FALSE;
	if(Lua_GetTopIndex(L) < nCount) return FALSE;

	return TRUE;
	__LUA_UNGUARD__;
	return FALSE;
}

/*
 =======================================================================================================================
 --接口中获得调用脚本script id
 =======================================================================================================================
 */
ScriptID_t LuaSystem::GetScriptStepId(Lua_State *L)
{
	return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL LuaSystem::IsParamNumber(Lua_State *L, int32 nIndex, char const *szFunctionName)
{
	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL LuaSystem::IsParamString(Lua_State *L, int32 nIndex, char const *szFunctionName)
{
	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void LuaSystem::MarkScriptName(Lua_State *L, char *strScriptName)
{
#if _DEBUG
	if(L == NULL) return;
	if(strScriptName == NULL) return;

	Lua_PushString(L, strScriptName);
	Lua_SetGlobal(L, LuaSystem::Lua_ScriptStepFileName);
#endif
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void LuaSystem::CheckScriptValid(void *pFile, ScriptID_t idScript, const char *szFunctionName)
{
#ifdef _DEBUG
	char strBuf[256] = { 0 };
	tsnprintf(strBuf, 256, "%s,scriptid=%d", szFunctionName, idScript);
	KCheckEx(pFile, strBuf);
#endif
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */

int32 LuaFunction_CallScriptFunction_test(Lua_State *L)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ScriptID_t	scriptId = Lua_ValueToNumber(L, 1);
	const char	*funcname = Lua_ValueToString(L, 2);
	int32		nMapID = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	return 0;
}


void Q_strncpyz(char* dest, const char* src, int32 destsize)
{
	if (!src)
	{
		KCheckEx(src, "null pointer in Q_strncpyz");
		return;
	}

	if (destsize < 1)
	{
		KCheckEx(destsize > 0, "dest buffer is null in Q_strncpyz");
		return;
	}

	strncpy(dest, src, destsize - 1);
	dest[destsize - 1] = 0;
}
