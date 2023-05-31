/*$T MapServer/Server/Script/LuaSystem.h GC 1.140 10/10/07 10:07:52 */

/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __LUASCRIPT_LUASYSTEM_H_
#define __LUASCRIPT_LUASYSTEM_H_

#include "TypeDefine.h"
#include "LuaStack.h"
#include "IntegerHashMap.h"
#include "LuaScriptVM.h"
#include "LuaPlus.h"
int32_t LuaFunction_CallScriptFunction(Lua_State* L);

class LuaSystem
{
/*
-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/
public:
	LuaSystem(void);
	~LuaSystem(void);

/*
-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/
public:
	void				Initialize(void);
	void				Release(void);
		
	void				RegFunction(void);
	BOOL				FindFunction(Lua_State *L, char *szFunction);
	BOOL				VerifyFunction(Lua_State *L, char **szFunction);

	void				EnterRunStep(MapID_t nMapID,ScriptID_t idScript, const char *szFunction);
	void				LeaveRunStep(MapID_t nMapID,ScriptID_t idScript, const char *szFunction);

	BOOL				ReloadScript(MapID_t nMapID,ScriptID_t idScript);
	void *				GetScriptByID(ScriptID_t idScript);
	BOOL				AddScript(ScriptID_t idScript, void *pData);

/*
-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/
public:
	BOOL				LuaLoadScript(const char *strLuaScript);

/*
-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/
public:
	static BOOL			CheckParamNum(Lua_State *L, int32 nCount);
	static BOOL			IsParamNumber(Lua_State *L, int32 nIndex, const char *szFunctionName);
	static BOOL			IsParamString(Lua_State *L, int32 nIndex, const char *szFunctionName);
	static ScriptID_t	GetScriptStepId(Lua_State *L);
	static void			MarkScriptName(Lua_State *L, char *strScriptName);
	static void			CheckScriptValid(void *pFile, ScriptID_t idScript, const char *szFunctionName);

/*
-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/
public:
	int32				RunScriptFunction(MapID_t nMapID, ScriptID_t idScript, const char *szFunction );
	int32				RunScriptFunction(MapID_t nMapID, ScriptID_t idScript, const char *szFunction, int32 Param0);
	int32				RunScriptFunction(MapID_t nMapID, ScriptID_t idScript, const char *szFunction, int32 Param0, int32 Param1);
	int32				RunScriptFunction(MapID_t nMapID, ScriptID_t idScript, const char *szFunction, int32 Param0, int32 Param1, int32 Param2);
	int32				RunScriptFunction(MapID_t nMapID, ScriptID_t idScript, const char *szFunction, int32 Param0, int32 Param1, int32 Param2, int32 Param3);
	int32				RunScriptFunction(MapID_t nMapID, ScriptID_t idScript, const char *szFunction, int32 Param0, int32 Param1, int32 Param2, int32 Param3,int32 Param4);
	int32				RunScriptFunction(MapID_t nMapID, ScriptID_t idScript, const char *szFunction, int32 Param0, int32 Param1, int32 Param2, int32 Param3,int32 Param4,int32	Param5);
	int32				RunScriptFunction(MapID_t nMapID, ScriptID_t idScript, const char *szFunction, int32 Param0, int32 Param1, int32 Param2, int32 Param3,int32 Param4,int32	Param5,int32 Param6);
	int32				RunScriptFunction(MapID_t nMapID, ScriptID_t idScript, const char *szFunction, int32 Param0, int32 Param1, int32 Param2, int32 Param3,int32 Param4,int32	Param5,int32 Param6,int32 Param7);
	int32				RunScriptFunction(MapID_t nMapID, ScriptID_t idScript, const char *szFunction, int32 Param0, int32 Param1, int32 Param2, int32 Param3,int32 Param4,int32	Param5,int32 Param6,int32 Param7,int32 Param8);
	int32				RunScriptFunction(MapID_t nMapID, ScriptID_t idScript, const char *szFunction, int32 Param0, int32 Param1, float Param2, float Param3);
	int32				RunScriptFunction(MapID_t nMapID, ScriptID_t idScript, const char *szFunction, int32 Param0, int32 Param1, const char *strParam2,const char *strParam3);

	bool loadScript(uint32_t scriptID);
private:

	LuaPlus::LuaStateOwner m_LuaState;
	std::unordered_map<uint32_t, std::string>			m_ScriptLoaded;

	std::string mScriptDirectory;

public:
	static BOOL				Lua_ReloadScriptAlways;
	static BOOL				Lua_RecordScriptStep;

	static const char*		Lua_ScriptStepFileName;
	static const int32		Lua_MaxScriptCount;
};
#endif
