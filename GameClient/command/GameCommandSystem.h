/*$T Client/Game/Command/GameCommandSystem.h GC 1.140 08/23/09 04:52:40 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


/*
 * ;
 * 游戏命令系统 ;
 * ;
 */
#ifndef _GAME_COMMAND_SYS_H_
#define _GAME_COMMAND_SYS_H_

#include "GameCommandDefine.h"
#include <OgreSingleton.h>
class CGameCommandSystem :
	public Singleton<CGameCommandSystem>
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	CGameCommandSystem(void);
	virtual						~CGameCommandSystem(void);

	static CGameCommandSystem	&GetSingleton(void);
	static CGameCommandSystem	*GetSingletonPtr(void);

	KHAN_RETURN_RESULT			Initialize(void);
	void						Release(void);
	KHAN_RETURN_RESULT			Update(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	/* 注册命令处理接口 */
	void	CommandHandleRegister(
		const STRING &strCommand, 
		HANDLE_COMMAND_FUNC funHandle, 
		uint32 uOwnerData = NULL);

	/* 处理所有的命令 */
	void	ProcessAllCommand(void);

	/* 立即处理的命令 */
	void	ProcessDirectCommand(GAME_COMMAND_ID id);

	/* 清空命令队列 */
	void	ClearAllCommand(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	// 模板形式
	template<typename T>
	void AddCommand(T id, const std::vector<STRING> &vParam);

	template<typename T>
	void AddCommand(T id);

	template<typename T, typename T1>
	void AddCommand(T id, T1 arg1);

	template<typename T, typename T1, typename T2>
	void AddCommand(T id, T1 arg1, T2 arg2);

	template<typename T, typename T1, typename T2, typename T3>
	void AddCommand(T id, T1 arg1, T2 arg2, T3 arg3);

	template<typename T, typename T1, typename T2, typename T3, typename T4>
	void AddCommand(T id, T1 arg1, T2 arg2, T3 arg3, T4 arg4);

	template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
	void AddCommand(T id, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5);

	template<typename T> BOOL SetCommandData(sCommand& command, T id);
	/* 产生事件 */
	template<> inline BOOL SetCommandData(sCommand& command, GAME_COMMAND_ID id);
	/* Push 事件用事件名 */
	template<> inline BOOL SetCommandData(sCommand& command, const STRING & id);
	template<> inline BOOL SetCommandData(sCommand& command, STRING id);
	template<typename T> LPCSTR ArgCast(LPSTR arg, size_t size, T val);
	template<> inline LPCSTR ArgCast(LPSTR arg, size_t size, int32 val);
	template<> inline LPCSTR ArgCast(LPSTR arg, size_t size, uint32 val);
	template<> inline LPCSTR ArgCast(LPSTR arg, size_t size, FLOAT val);
	template<> inline LPCSTR ArgCast(LPSTR arg, size_t size, LPCSTR val);
	template<> inline LPCSTR ArgCast(LPSTR arg, size_t size, LPSTR val);
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	/* 添加一条命令 */
	void	_AddCommand(const sCommand &command);

	/* 执行一条命令 */
	void	_ProcessCommand(const sCommand &command);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	std::map<STRING, sCommandData *>			m_CommandMap_Name;	/* 通过名称索引 */
	std::map<GAME_COMMAND_ID, sCommandData *>	m_CommandMap_ID;	/* 通过ID索引 */

	std::list<sCommand>							m_CommandList;		/* 命令队列 */
	std::list<sCommand>							m_CommandDelayList; /* 慢速命令队列 */

	uint32 m_dwLastTickCount;
};	/* class */

template<typename T>
void CGameCommandSystem::AddCommand(T id, const std::vector<STRING> &vParam)
{
	sCommand command;
	if (FALSE == SetCommandData(command, id)) 
		return;

	command.m_ValueVector = vParam;

	_AddCommand(command);
}

template<typename T>
void CGameCommandSystem::AddCommand(T id)
{
	sCommand command;
	if (FALSE == SetCommandData(command, id)) 
		return;

	_AddCommand(command);
}

template<typename T, typename T1>
void CGameCommandSystem::AddCommand(T id, T1 arg1)
{
	sCommand command;
	if (FALSE == SetCommandData(command, id)) 
		return;

	CHAR szTemp[32] = {0};

	command.m_ValueVector.push_back(ArgCast(szTemp, sizeof(szTemp), arg1));

	_AddCommand(command);
}

template<typename T, typename T1, typename T2>
void CGameCommandSystem::AddCommand(T id, T1 arg1, T2 arg2)
{
	sCommand command;
	if (FALSE == SetCommandData(command, id)) 
		return;

	CHAR szTemp[32] = {0};

	command.m_ValueVector.push_back(ArgCast(szTemp, sizeof(szTemp), arg1));
	command.m_ValueVector.push_back(ArgCast(szTemp, sizeof(szTemp), arg2));

	_AddCommand(command);
}

template<typename T, typename T1, typename T2, typename T3>
void CGameCommandSystem::AddCommand(T id, T1 arg1, T2 arg2, T3 arg3)
{
	sCommand command;
	if (FALSE == SetCommandData(command, id)) 
		return;

	CHAR szTemp[32] = {0};

	command.m_ValueVector.push_back(ArgCast(szTemp, sizeof(szTemp), arg1));
	command.m_ValueVector.push_back(ArgCast(szTemp, sizeof(szTemp), arg2));
	command.m_ValueVector.push_back(ArgCast(szTemp, sizeof(szTemp), arg3));

	_AddCommand(command);
}

template<typename T, typename T1, typename T2, typename T3, typename T4>
void CGameCommandSystem::AddCommand(T id, T1 arg1, T2 arg2, T3 arg3, T4 arg4)
{
	sCommand command;
	if (FALSE == SetCommandData(command, id)) 
		return;

	CHAR szTemp[32] = {0};

	command.m_ValueVector.push_back(ArgCast(szTemp, sizeof(szTemp), arg1));
	command.m_ValueVector.push_back(ArgCast(szTemp, sizeof(szTemp), arg2));
	command.m_ValueVector.push_back(ArgCast(szTemp, sizeof(szTemp), arg3));
	command.m_ValueVector.push_back(ArgCast(szTemp, sizeof(szTemp), arg4));

	_AddCommand(command);
}

template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
void CGameCommandSystem::AddCommand(T id, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5)
{
	sCommand command;
	if (FALSE == SetCommandData(command, id)) 
		return;

	CHAR szTemp[32] = {0};

	command.m_ValueVector.push_back(ArgCast(szTemp, sizeof(szTemp), arg1));
	command.m_ValueVector.push_back(ArgCast(szTemp, sizeof(szTemp), arg2));
	command.m_ValueVector.push_back(ArgCast(szTemp, sizeof(szTemp), arg3));
	command.m_ValueVector.push_back(ArgCast(szTemp, sizeof(szTemp), arg4));
	command.m_ValueVector.push_back(ArgCast(szTemp, sizeof(szTemp), arg5));

	_AddCommand(command);
}

template<> inline BOOL CGameCommandSystem::SetCommandData(sCommand& command, GAME_COMMAND_ID id)
{
	if(m_CommandMap_ID.find(id) == m_CommandMap_ID.end()) 
		return FALSE;
	command.m_pCommandData = m_CommandMap_ID[id];
	return TRUE;
}

template<> inline BOOL CGameCommandSystem::SetCommandData(sCommand& command, const STRING & id)
{
	if(m_CommandMap_Name.find(id) == m_CommandMap_Name.end()) 
		return FALSE;
	command.m_pCommandData = m_CommandMap_Name[id];
	return TRUE;
}

template<> inline BOOL CGameCommandSystem::SetCommandData(sCommand& command, STRING id)
{
	return SetCommandData<const STRING &>(command, id);
}

template<typename T> inline LPCSTR CGameCommandSystem::ArgCast(LPSTR arg, size_t size, T val)
{
	return ArgCast(arg, size, static_cast<int32>(val));
}

template<> inline LPCSTR CGameCommandSystem::ArgCast(LPSTR arg, size_t size, int32 val)
{
	_snprintf(arg, size, "%d", val);
	return arg;
}

template<> inline LPCSTR CGameCommandSystem::ArgCast(LPSTR arg, size_t size, uint32 val)
{
	return ArgCast(arg, size, (int32)val);
}

template<> inline LPCSTR CGameCommandSystem::ArgCast(LPSTR arg, size_t size, FLOAT val)
{
	_snprintf(arg, size, "%f", val);
	return arg;
}

template<> inline LPCSTR CGameCommandSystem::ArgCast(LPSTR arg, size_t size, LPCSTR val)
{
	return val;
}

template<> inline LPCSTR CGameCommandSystem::ArgCast(LPSTR arg, size_t size, LPSTR val)
{
	return val;
}

#define COMMAND_SYS		CGameCommandSystem::GetSingleton()
#define COMMAND_SYS_PTR CGameCommandSystem::GetSingletonPtr()
#endif /* _GAME_COMMAND_SYS_H_ */
