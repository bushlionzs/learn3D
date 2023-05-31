#pragma once
#include "stdafx.h"
#include "SCOperateResult.h"



enum OPERATE_RES_TYPE { ORT_UNKONW = 0, ORT_SYSTEM, ORT_SKILL, };

SCOperateResult::SCOperateResult():
	NetPacket(SC_OPERATE_RESULT)
{

}

SCOperateResult::~SCOperateResult()
{

}

bool SCOperateResult::process()
{
	//if (NULL == OBJECT_MANAGER_PTR->GetMySelf()) return MP_CONTINUE;
	//if (NULL == OBJECT_MANAGER_PTR->GetMySelf()->GetCharacterData()) return MP_CONTINUE;

	//eOPTRESULT	oCode = (eOPTRESULT)(mResultCode);
	//STRING strText = ACTION_SYS_PTR->GetOperateResult(oCode);

	//std::string::size_type nLen = strText.length();
	//if (nLen > 0)
	//{
	//	if (strText.substr(0, 1) == "\"")
	//	{
	//		strText.erase(strText.begin(), strText.begin() + 1);
	//	}

	//	if (strText.substr(strText.size() - 1, 1) == "\"")
	//	{
	//		strText.erase(strText.end() - 1, strText.end());
	//	}
	//}

	//switch (oCode)
	//{
	//case OR_LACK_MANA:			/* MANA不足 */
	//case OR_NOT_ENOUGH_RAGE:	/* 没有足够的怒气值 */
	//{
	//	int32 nProfession = OBJECT_MANAGER_PTR->GetMySelf()->GetCharacterData()->GetProfession();
	//	switch (nProfession)
	//	{
	//	case PROFESSION_WUSHI:			strText = UI_SYSTEM_PTR->ParserString_NoColor_VarParam("OR_NO_ENOUGH_RAGE");	break;
	//	case PROFESSION_JIANXIA:		strText = UI_SYSTEM_PTR->ParserString_NoColor_VarParam("OR_NO_ENOUGH_ENERGY");	break;
	//	case PROFESSION_QISHE:			strText = UI_SYSTEM_PTR->ParserString_NoColor_VarParam("OR_NO_ENOUGH_ARROW");	break;
	//	case PROFESSION_HUOQIANG:		strText = UI_SYSTEM_PTR->ParserString_NoColor_VarParam("OR_NO_ENOUGH_AMMO"); 	break;
	//	case PROFESSION_XIANZHI:		strText = UI_SYSTEM_PTR->ParserString_NoColor_VarParam("OR_NO_ENOUGH_MANA"); 	break;
	//	case PROFESSION_SAMAN:			strText = UI_SYSTEM_PTR->ParserString_NoColor_VarParam("OR_NO_ENOUGH_NIMBUS"); 	break;
	//	case PROFESSION_SHIZIJUN:		strText = UI_SYSTEM_PTR->ParserString_NoColor_VarParam("OR_NO_ENOUGH_RAGE");	break;
	//	case PROFESSION_SHENGHUOSHI:	strText = UI_SYSTEM_PTR->ParserString_NoColor_VarParam("OR_NO_ENOUGH_ENERGY");	break;
	//	case PROFESSION_CIKE:			strText = UI_SYSTEM_PTR->ParserString_NoColor_VarParam("OR_NO_ENOUGH_ARROW");	break;
	//	case PROFESSION_JINWEIJUN:		strText = UI_SYSTEM_PTR->ParserString_NoColor_VarParam("OR_NO_ENOUGH_AMMO");	break;
	//	case PROFESSION_YINXIUSHI:		strText = UI_SYSTEM_PTR->ParserString_NoColor_VarParam("OR_NO_ENOUGH_MANA");	break;
	//	case PROFESSION_LAMA:			strText = UI_SYSTEM_PTR->ParserString_NoColor_VarParam("OR_NO_ENOUGH_NIMBUS");	break;
	//	default:
	//		break;
	//	}
	//}
	//break;

	//case OR_PWD_ErrorMax:
	//{
	//	if (!OBJECT_MANAGER_PTR->GetMySelf()->GetCharacterData()->Get_IsMaxErrorCount())
	//	{
	//		OBJECT_MANAGER_PTR->GetMySelf()->GetCharacterData()->Set_SetMaxErrorCount(TRUE);
	//	}

	//	if (UI_SYSTEM_PTR && UI_SYSTEM_PTR->IsWindowShow("rich_setup"))
	//	{
	//		COMMAND_SYS_PTR->AddCommand(GCD_RICH_SETUP);
	//	}

	//	if (UI_SYSTEM_PTR && UI_SYSTEM_PTR->IsWindowShow("rich_setpassword"))
	//	{
	//		COMMAND_SYS_PTR->AddCommand(GCD_RICH_SET_PASSWORD);
	//	}

	//	if (UI_SYSTEM_PTR && UI_SYSTEM_PTR->IsWindowShow("rich_safeguard"))
	//	{
	//		COMMAND_SYS_PTR->AddCommand(GCD_RICH_SAFE_GUARD);
	//	}
	//}
	//break;

	//case OR_EXP_FULL:			/* 您的经验已经到达上限 */
	//{
	//	/* 判断是否要给出手动升级提示 */
	//	int32 index = GAME_DATA_PTR->SystemTip_GetIndexByType(STT_EXP_MAX_FULL, -1, FALSE);
	//	if (index == -1)
	//	{
	//		GAME_DATA_PTR->SystemTip_AddEventInfo(STT_EXP_MAX_FULL, "你已无法再获得经验。你现在可以选择升级！");
	//		COMMAND_SYS_PTR->AddCommand(GCD_SHOW_SYSTEM_PROMPT);
	//	}
	//}
	//break;

	//default:
	//	break;
	//}

	//if (ORT_SKILL == mResType)
	//{
	//	/* 取消公共CD */
	//	ACTION_SYS_PTR->CancelCommonCoolDown();
	//}

	//if (ORT_SYSTEM == mResType)
	//{
	//	COMMAND_SYS_PTR->AddCommand(GCD_SYSTEM_MESSAGE, strText.c_str());
	//	COMMAND_SYS_PTR->AddCommand(GCD_NEW_DEBUGMESSAGE, strText.c_str());
	//}
	//else
	//{
	//	COMMAND_SYS_PTR->AddCommand(GCD_NEW_DEBUGMESSAGE, strText.c_str());
	//}
	return true;
}

void SCOperateResult::setPlayerId(int32_t id)
{
	mPlayerId = id;
}

void SCOperateResult::setMapId(int32_t id)
{
	mMapId = id;
}

void SCOperateResult::setResType(int32_t type)
{
	mResType = type;
}

void SCOperateResult::setResult(int32_t res)
{
	mResultCode = res;
}