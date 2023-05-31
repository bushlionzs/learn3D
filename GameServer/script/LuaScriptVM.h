/*$T MapServer/Server/Base/LuaScriptVM.h GC 1.140 10/10/09 10:07:20 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef KhanLuaScript_H
#define KhanLuaScript_H


#include <string.h>
#include "LuaPlus.h"
#ifndef __linux
#ifdef LUASCRIPTVM_EXPORTS
#define _LUAVM	__declspec(dllexport)
#else
#define _LUAVM	__declspec(dllimport)
#endif
#else
#define _LUAVM
#endif
namespace	Lua
{
class _LUAVM	ScriptVM
{
	enum LuaErrorCode
	{
		lecCreateError		= 1,
		lecScriptLenError	= 2,
		lecScriptCompileError	= 3,
		lecScriptExecuteError	= 4,
		lecScriptNotNumberError = 10,
		lecScriptNotStringError = 11,
		lecScriptNotTableError	= 12,
		lecScriptStatesIsNil	= 20
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	ScriptVM(void);
	~	ScriptVM(void);

	bool 	Initialize(int nstacksize = 0);
	void	Release();

	// 注册函数
	bool	RegisterFunction(char *FuncName, void *Func);
	
	// 加载脚本
	bool	Load(char *FileName);
	bool	LoadBuffer(unsigned char *pBuffer, unsigned long dwLen);

	// 执行脚本函数相关
	void	RunScriptFunctionEnter(int *pIndex);
	bool	RunScriptFunction(char *, int);			/* 0 */
	bool	RunScriptFunction(char *, int, int);		/* 1 */
	bool	RunScriptFunction(char *, int, int, int);	/* 2 */
	bool	RunScriptFunction(char *, int, int, int, int);	/* 3 */
	bool	RunScriptFunction(char *, int, int, int, int, int);			/* 4 */
	bool	RunScriptFunction(char *, int, int, int, int, int, int);		/* 5 */
	bool	RunScriptFunction(char *, int, int, int, int, int, int, int);		/* 6 */
	bool	RunScriptFunction(char *, int, int, int, int, int, int, int, int);	/* 7 */
	bool	RunScriptFunction(char *, int, int, int, int, int, int, int, int, int); /* 8 */
	bool	RunScriptFunction(char *, int, int, int, float, float);			/* 9 */
	bool	RunScriptFunction(char *, int, int, int, const char *, const char *);	/* 10 */
	void	RunScriptFunctionLeave(int nIndex);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	static void	ReadRootPath(char *lpPathName);
	static void	GetFullPath(char *lpPathName, char *lpFileName);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	// 执行脚本
	bool	ExecuteCode();

	void	OnInitialize();
	void	OnScriptError(int Error);
	void	OnScriptError(int, int);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Lua_State	*m_LuaState;
};
}
#endif
