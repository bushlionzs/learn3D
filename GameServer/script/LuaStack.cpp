/*$T MapServer/Server/Script/LuaStack.cpp GC 1.140 10/10/07 10:07:52 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "LuaStack.h"

namespace	LuaScript
{

/*
 =======================================================================================================================
 =======================================================================================================================
 */
LuaStackStep::LuaStackStep(void)
{
	Reset();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
LuaStackStep::~LuaStackStep(void)
{
	Reset();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void LuaStackStep::Reset(void)
{
	m_idScriptStep = INVALID_ID;
	memset(m_strFunctionStep, 0, MAX_FUNCTION_LENGTH);
}

LuaStack LuaStack::	RunStack[MAX_SCENE];

/*
 =======================================================================================================================
 =======================================================================================================================
 */

LuaStack::LuaStack(void)
{
	m_nCurrentStep = 0;
	for(int32 i = 0; i < MAX_STACK_STEP; i++) m_StackStep[i].Reset();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
LuaStack::~LuaStack(void)
{
	m_nCurrentStep = 0;
	for(int32 i = 0; i < MAX_STACK_STEP; i++) m_StackStep[i].Reset();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void LuaStack::Reset(void)
{
	m_nCurrentStep = 0;
	for(int32 i = 0; i < MAX_STACK_STEP; i++) m_StackStep[i].Reset();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL LuaStack::StepEnter(char *funcname, ScriptID_t scriptid)
{
	if(m_nCurrentStep >= MAX_STACK_STEP)
	{
		printf("Out of lua stack! %d %s", scriptid, funcname);
		return FALSE;
	}

	m_StackStep[m_nCurrentStep].m_idScriptStep = scriptid;
	strncpy(m_StackStep[m_nCurrentStep].m_strFunctionStep, funcname, MAX_FUNCTION_LENGTH - 1);
	m_nCurrentStep++;
	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL LuaStack::StepLeave(void)
{
	if(m_nCurrentStep <= 0)
	{
		printf("Low lua stack! ");
		return FALSE;
	}

	m_nCurrentStep--;
	return TRUE;
}
}