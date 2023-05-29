/*$T MapServer/Server/Base/ScriptDef.h GC 1.140 10/10/07 10:07:21 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __SCRIPTDEF_H__
#define __SCRIPTDEF_H__

#define GUILD_CONVOY_SCRIPT_ID								(300608)

#define BANGHUIDASAI_CHUANSONG								(300641)
#define BANGHUIDASAI_BAOMING								(300642)

#define GUILD_BATTLE_SCRIPT_ID								(300643)
#define KING_BATTLE_SCRIPT_ID								(300813)
#define KING_SIGNUP_SCRIPTID								(300815)
#define GUILD_CONTEND_SCRIPT_ID								(300615)

#define ZHUQUE_BATTLE_SCRIPT_ID								(310113)		//朱雀战场脚本
#define ZHUQUE_SIGNUP_SCRIPTID								(310114)		//朱雀报名脚本
#define ZHUQUE_TRANS_SCRIPTID								(310115)		//朱雀传送脚本

#define QINGLONG_BATTLE_SCRIPT_ID							(310110)		//青龙战场脚本
#define QINGLONG_SIGNUP_SCRIPTID							(310111)		//青龙报名脚本
#define QINGLONG_TRANS_SCRIPTID								(310112)		//青龙传送脚本

#define LAIRD_BATTLE_SCRIPT_ID								(300918)		//据点战场脚本
#define LAIRD_SIGNUP_SCRIPTID								(300919)		//据点报名脚本
#define LAIRD_TRANS_SCRIPTID								(300920)		//据点传送脚本
#define LAIRD_PLAYERAID_SCRIPTID							(300941)		//据点外援脚本

#define BUS_SCRIPT											(310080)
#define GOLD_SHOP_SCRIPT									(560888)
#define GET_AWARD_SCRIPT									(561103)
#define QUERY_AWARD_SCRIPT									(561101)
#define DEL_CHAR_SCRIPTID									(561102)
#define FUBEN_SCRIPT_BIWU									(700005)
#define ABILITY_LOGIC_SCRIPT								(701601)
#define GEM_COMPOUND_SCRIPT									(701602)
#define CHANGE_SCENE_SCRIPT_ID								(800021)
#define COUNTRY_CHANGE_SCENE_SCRIPT_ID						(800021)
#define GUILD_CONVOY_CHANGE_SCENE_SCRIPT_ID					(800021)
#define GUILD_CONVOKE_CHANGE_SCENE_SCRIPT_ID				(800021)
#define SUBTRAIN_EXPRATE_SCRIPT								(800025)
#define SUBTRAIN_MONEYRATE_SCRIPT							(800026)
#define SCENE_SCRIPTID										(888888)
#define SCRIPT_MAIL											(888889)
#define QUEST_SCRIPTID										(888891)
#define SCRIPT_ID_BEASTIE_CAPTURE							(888893)
#define ABILITY_SKILL_SCRIPT								(890000)
#define ZHILIJINGSAI_KEJU									(920001)
#define COUNTRY_BATTLE_LITE_SCRIPT_ID						(310150)

#define WORLD_SHOP_SELL_SCRIPT								(800054)
#define WORLD_SHOP_BUY_SCRIPT								(800053)
#define WORLD_BANK_RETATE_SCRIPT							(800055)

#define PVP2V2_BATTLE_SIGNUP_SCRIPT_ID						(303000)
#define PVP2V2_BATTLE_FLOW_SCRIPT_ID						(303001)

#define MPVP2V2_BATTLE_SIGNUP_SCRIPT_ID						(303100)		// 跨服 2v2 战场 by rj 2010-9-21
#define MPVP2V2_BATTLE_FLOW_SCRIPT_ID						(303101)

#define PVP6V6_BATTLE_SIGNUP_SCRIPT_ID						(303005)
#define PVP6V6_BATTLE_FLOW_SCRIPT_ID						(303006)

#define ENCRYPT_MANAGER_SCRIPT_ID							(800100)
#define DATI_MANAGER_SCRIPT_ID								(300824)
#define STOCK_REGISTER_SCRIPT								(310351)
#define STOCK_MANAGER_SCRIPT								(310350)
#define TOPLIST_SCRIPT										(888888)
#define EQUIP_BLUE_INTENSIFY_SCRIPT							(800088)
#define GUILD_DELATE_SCRIPT									(300828)

#define KING_ZHAOJI_SCRIPT_ID								(300808)

//场景相关
#define DEF_PROC_MAP_INIT_FN								("ProcMapInit")
#define DEF_PROC_MAP_TIMER_FN								("ProcMapTimer")
#define DEF_PROC_MAP_QUIT_FN								("ProcMapQuit")
#define DEF_PROC_MAP_PLAYER_FIRSTENTER_FN					("ProcMapPlayerFirstEnter")
#define DEF_PROC_MAP_PLAYER_ENTER_FN						("ProcMapPlayerEnter")
#define DEF_PROC_MAP_PLAYER_ENTERFINISHED_FN				("ProcMapPlayerEnterFinished")
#define DEF_PROC_MAP_PLAYER_NEWCONNECTENTER_FN				("ProcMapPlayerNewConnectEnter")
#define DEF_PROC_MAP_PLAYER_LEAVE_FN						("ProcMapPlayerLeave")
#define DEF_PROC_MAP_PLAYER_LEVELUP_FN						("ProcMapPlayerLevelUp")
#define DEF_PROC_MAP_PLAYER_DIE_FN							("ProcMapPlayerDie")
#define DEF_PROC_MAP_PLAYER_RELIVE_FN						("ProcMapPlayerRelive")
#define DEF_PROC_MAP_NOTIFY_FN								("ProcMapNotify")
#define DEF_PROC_MAP_ACCEPTQUESTCHECK_FN					("ProcAcceptQuestCheck")
#define DEF_PROC_MAP_NPCDEFAULTDIALOG_FN					("ProcNpcDefaultDialog")
#define DEF_PROC_MAP_NPCDEFAULTQUESTEVENTLIST_FN			("ProcNpcDefaultQuestEventList")
#define DEF_PROC_MAP_ON_ADDMASTERSUCCEED					("ProcMapOnAddMasterSucceed")
#define DEF_PROC_MAP_ON_ADDPRENTICESUCCEED					("ProcMapOnAddPrenticeSucceed")
#define DEF_PROC_MAP_ON_FRIENDPOINTADD						("ProcMapOnFriendPointAdd")

//任务及NPC对话相关
#define DEF_PROC_ENUM_EVENT_FN								("ProcEnumEvent")
#define DEF_PROC_EVENT_ENTRY_FN								("ProcEventEntry")
#define DEF_PROC_QUEST_ATTACH_FN							("ProcQuestAttach")
#define DEF_PROC_QUEST_OBJECT_KILLED_FN						("ProcQuestObjectKilled")
#define DEF_PROC_QUEST_ITEM_CHANGED_FN						("ProcQuestItemChanged")
#define DEF_PROC_HORSE_CHANGED_FN							("ProcQuestHorseChanged")
#define DEF_PROC_AREA_ENTERED_FN							("ProcAreaEntered")
#define DEF_PROC_AREA_LEAVED_FN								("ProcAreaLeaved")
#define DEF_PROC_QUEST_ACCEPT_FN							("ProcQuestAccept")
#define DEF_PROC_QUEST_ABANDON_FN							("ProcQuestAbandon")
#define DEF_PROC_QUEST_SUBMIT_FN							("ProcQuestSubmit")
#define DEF_PROC_ACCEPT_CHECK_FN							("ProcAcceptCheck")
#define DEF_PROC_QUESTLOGREFRESH_FN							("ProcQuestLogRefresh")
#define DEF_PROC_ACCEPT_FN									("ProcAccept")
#define DEF_PROC_TIMING_FN									("ProcTiming")

//杂项
#define DEF_MAP_CLEARBUSQUESTDATA							("OnClearBusQuestData")
#define DEF_MAP_FUBENENTERPRISON							("FubenEnterPrison")
#define DEF_MAP_ONANSWERFUBENDATI							("OnAnswerFubenDati")
#define DEF_MAP_SAVEENCRYPTARITH							("SaveEncryptArith")
#define DEF_MAP_SAVEDATIRESULT								("SaveDatiResult")
#define DEF_MAP_GETENCRYPTARITH								("GetEncryptArith")
#define DEF_MAP_GETDATIRESULT								("GetDatiResult")
#define DEF_MAP_ONCLIENTGETDATI								("OnClientGetDati")
#define DEF_MAP_ONDUEL_RESULT								("OnDuelResult")
#define DEF_AGREE_ZHAOJI									("OnAgreeZhaoJi")

//相关检查
#define DEF_MAP_CAN_MOVEPETTOBANK							("CanMovePetToBank")
#define DEF_MAP_CAN_LOCKPET									("CanLockPet")
#define DEF_MAP_CAN_LOCKEQUIP								("CanLockEquip")
#define DEF_MAP_CHECK_PVP2V2DATA							("OnCheckpvp2v2Data")
#define DEF_MAP_CHECKQUESTSUBMITNPC							("OnCheckQuestSubmitNPC")

//生活技能相关
#define DEF_ABILITY_CHECK									("AbilityCheck")
#define DEF_ABILITY_CONSUME									("AbilityConsume")
#define DEF_ABILITY_PRODUCE									("AbilityProduce")
#define DEF_ABILITY_SUCCESSFUL_CHECK						("CheckForResult")
#define DEF_ABILITY_GAIN_EXPERIENCE							("GainExperience")
#define DEF_ABILITY_CALC_QUALITY							("CalcQuality")

//珠宝镶嵌
#define DEF_GEM_COUNT_CHECK									("TooManyGems")
#define DEF_IS_GEM_FIT_EQUIP								("IsGemFitEquip")
#define DEF_GEM_CONFLICT_CHECK								("IsGemConflict")
#define DEF_GEM_EMBED_PROCESS								("EmbedProc")
#define DEF_GEM_COMPOUND									("GemCompound")

//代练
#define DEF_SUBTRAIN_EXPRATE								("SubTrainExpRate")
#define DEF_SUBTRAIN_MONEYRATE								("SubTrainMoneyRate")
#define DEF_INTO_BUS_FUNC_NAME								("OnIntoBusEvent")
#define DEF_LEAVE_BUS_FUNC_NAME								("OnLeaveBusEvent")
#define DEF_CREATE_BUS_OK									("OnCreateBusOK")

//时间相关
#define DEF_BUS_TICK_FUNC_NAME								("OnTime")
#define DEF_DELAY_AFTER_CREATE_TIMER						("OnDelayTime")
#define DEF_BUS_LIFE_TIME_OUT_FUNC							("OnLifeTimeOut")
#define DEF_BUS_WAIT_TIME_OUT_FUNC							("OnWaitTimeOut")
#define DEF_BUS_STOP_WHEN_OWNER_FAR_AWAY					("OnBusStopWhenOwnerFarAway")
#define DEF_BUS_ENTERSCENE_FUNC_NAME						("OnBusEnterScene")

#define DEF_GUILD_DELATE_RET								("OnGuildDelateRet")
#define DEF_GUILD_CONVOY_CHANGE_SCENE_FUNC_NAME				("OnGuildConvoyChangeScene")
#define DEF_GUILD_CONVOY_CLEAR_MEMBER_QUEST_FUNC_NAME		("OnGuildConvoyClearMemberQuest")
#define DEF_GUILD_CONVOY_SUBMIT_QUEST_FUNC_NAME				("OnGuildConvoySubmitQuest")
#define DEF_GUILD_CONVOKE_CHANGE_SCENE_FUNC_NAME			("OnGuildConvokeChangeScene")

//帮会战
#define DEF_GUILD_BATTLE_DEFAULT_EVENT						("OnBattleStateEvent")
#define DEF_GUILD_BATTLE_ENTERSCENEERROR					("OnGuildBattleTransError")
#define DEF_GUILD_BATTLE_QUERYBATTLESIGNUP					("OnQueryBattleSignup")
#define DEF_GUILD_BATTLE_BATTLESIGNUP						("OnBattleSignup")
#define DEF_GUILD_BATTLE_SETMATCHINFO						("OnSetGuildBattleMatchInfo")
#define DEF_GUILD_BATTLE_SYNCTIME							("OnSyncGuildBattleTime")
#define DEF_GUILD_BATTLE_CHANGE_SCENE_FUNC_NAME				("OnGuildBattleChangeScene")
#define DEF_GUILD_BATTLE_MATCH_ODD_FUNC_NAME				("OnGuildBattleMatchOdd")
#define DEF_GUILD_BATTLE_ON_RIDE_HORSE_FUNC_NAME			("OnRideHorse")

//国王争夺战
#define DEF_KING_BATTLE_DEFAULT_EVENT						("OnBattleStateEvent")
#define DEF_KING_BATTLE_CHANGE_SCENE_FUNC_NAME				("OnKingBattleChangeScene")
#define DEF_KING_BATTLE_ENTERSCENE_ERROR					("OnKingBattleTransError")
#define DEF_KING_BATTLE_SIGNUP_RESULT_FUNC_NAME				("OnKingBattleSignupResult")
#define DEF_KING_BATTLE_QUERY_SIGNUP_STATE_FUNC_NAME		("OnQueryKingBattleSignupState")
#define DEF_KING_BATTLE_ASK_PLAYER_ENTER_SCENE				("OnKingBattleAskPlayerEnterScene")
#define DEF_KING_BATTLE_SETMATCHINFO						("OnSetKingBattleMatchInfo")
#define DEF_KING_BATTLE_SYNCTIME							("OnSyncKingBattleTime")
#define DEF_KING_BATTLE_ASK_ENTER_KING_BATTLE				("AskEnterKingBattle")
#define DEF_KING_BATTLE_QUERY_CURRENT_GUILD					("OnQueryCurrentGuild")

//屠城战
#define DEF_COUNTRY_BATTLE_LITE_STATE						("OnCountryBattleLiteState")
#define DEF_COUNTRY_BATTLE_LITE_ASK_PLAYER_ENTER_SCENE		("OnCountryBattleLiteAskPlayerEnterScene")
#define DEF_COUNTRY_BATTLE_LITE_CHANGE_SCENE_FUNC_NAME		("OnCountryBattleLiteChangeScene")
#define DEF_COUNTRY_BATTLE_SETMATCHINFO						("OnSetCountryBattleLiteMatchInfo")
#define DEF_COUNTRY_BATTLE_LITE_ASK_ENTER					("AskEnterCountryBattleLite")
#define DEF_COUNTRY_BATTLE_LITE_ASK_KINGISSUE				("AskCountryBattleLite_KingIssue")
#define DEF_COUNTRY_BATTLE_SYNC_KILLCOUT					("OnCountryBattleLiteSyncKillCout")

//2v2战场
#define DEF_PVP2V2_BATTLE_MATCHINFO							("OnBattleMatchInfo")
#define DEF_PVP2V2_BATTLE_BATTLESCENETRANS					("OnPVP2v2BattleChangeScene")
#define DEF_PVP2V2_BATTLE_BATTLESCENETRANS_ERROR			("OnPVP2v2BattleTransError")
#define DEF_PVP2V2_BATTLE_SYNCTIME							("OnSyncBattleTime")
#define DEF_PVP2V2_BATTLE_STATE								("OnBattleState")
#define DEF_PVP2V2_BATTLE_MATCHOOD							("OnBattleMatchOOD")
#define DEF_PVP2V2_BATTLE_QUERY_SIGNUP_RESULT				("OnQuerySignupResult")
#define DEF_PVP2V2_BATTLE_SIGNUP_RESULT						("OnSignupResult")
#define DEF_PVP2V2_BATTLE_ASK_ENTER							("AskBattleSceneEnter")

//跨服 2v2 战场 by rj 2010-9-21
#define DEF_MPVP2V2_BATTLE_MATCHINFO						("OnMBattleMatchInfo")
#define DEF_MPVP2V2_BATTLE_BATTLESCENETRANS					("OnMPVP2v2BattleChangeScene")
#define DEF_MPVP2V2_BATTLE_BATTLESCENETRANS_ERROR			("OnMPVP2v2BattleTransError")
#define DEF_MPVP2V2_BATTLE_SYNCTIME							("OnMSyncBattleTime")
#define DEF_MPVP2V2_BATTLE_STATE							("OnMBattleState")
#define DEF_MPVP2V2_BATTLE_MATCHOOD							("OnMBattleMatchOOD")
#define DEF_MPVP2V2_BATTLE_QUERY_SIGNUP_RESULT				("OnMQuerySignupResult")
#define DEF_MPVP2V2_BATTLE_SIGNUP_RESULT					("OnMSignupResult")

//6v6战场
#define DEF_PVP6V6_BATTLE_SETTEAMA							("OnPVP6v6SetTeamA")
#define DEF_PVP6V6_BATTLE_SETTEAMB							("OnPVP6v6SetTeamB")
#define DEF_PVP6V6_BATTLE_SETLEAVEFLAG						("OnPVP6v6SetLevelFlag")
#define DEF_PVP6V6_BATTLE_BATTLESCENETRANS					("OnPVP6v6BattleChangeScene")
#define DEF_PVP6V6_BATTLE_BATTLESCENETRANS_ERROR			("OnPVP6v6BattleTransError")
#define DEF_PVP6V6_BATTLE_SYNCTIME							("OnSyncBattleTime")
#define DEF_PVP6V6_BATTLE_STATE								("OnBattleState")
#define DEF_PVP6V6_BATTLE_MATCHOOD							("OnBattleMatchOOD")
#define DEF_PVP6V6_BATTLE_QUERY_SIGNUP_RESULT				("OnQuerySignupResult")
#define DEF_PVP6V6_BATTLE_SIGNUP_RESULT						("OnSignupResult")
#define DEF_PVP6V6_BATTLE_ASK_ENTER							("AskBattleSceneEnter")

//朱雀
#define DEF_ZHUQUE_BATTLE_DEFAULT_EVENT						("OnBattleStateEvent")
#define DEF_ZHUQUE_BATTLE_CHANGE_SCENE_FUNC_NAME			("OnZhuQueBattleChangeScene")
#define DEF_ZHUQUE_BATTLE_ENTERSCENE_ERROR					("OnZhuQueBattleTransError")
#define DEF_ZHUQUE_BATTLE_SIGNUP_RESULT_FUNC_NAME			("OnZhuQueBattleSignupResult")
#define DEF_ZHUQUE_BATTLE_QUERY_SIGNUP_STATE_FUNC_NAME		("OnQueryZhuQueBattleSignupState")
#define DEF_ZHUQUE_BATTLE_ASK_PLAYER_ENTER_SCENE			("OnZhuQueBattleAskPlayerEnterScene")
#define DEF_ZHUQUE_BATTLE_SETMATCHINFO						("OnSetZhuQueBattleMatchInfo")
#define DEF_ZHUQUE_BATTLE_SYNCTIME							("OnSyncZhuQueBattleTime")
#define DEF_ZHUQUE_BATTLE_ASK_ENTER_ZHUQUE 					("AskEnterZhuQueBattle")
#define DEF_ZHUQUE_BATTLE_QUERY_CURRENT_GUILD				("OnQueryCurrentGuild")
#define DEF_ZHUQUE_BATTLE_SETENTERSCENEFLAG					("SetBattleEnterSceneFlag")
#define DEF_ZHUQUE_BATTLE_SIGNUP_INSTEAD					("OnSignupInstead")

//青龙
#define DEF_QINGLONG_BATTLE_DEFAULT_EVENT					("OnBattleStateEvent")
#define DEF_QINGLONG_BATTLE_CHANGE_SCENE_FUNC_NAME			("OnQingLongBattleChangeScene")
#define DEF_QINGLONG_BATTLE_ENTERSCENE_ERROR				("OnQingLongBattleTransError")
#define DEF_QINGLONG_BATTLE_SIGNUP_RESULT_FUNC_NAME			("OnQingLongBattleSignupResult")
#define DEF_QINGLONG_BATTLE_QUERY_SIGNUP_STATE_FUNC_NAME	("OnQueryQingLongBattleSignupState")
#define DEF_QINGLONG_BATTLE_ASK_PLAYER_ENTER_SCENE			("OnQingLongBattleAskPlayerEnterScene")
#define DEF_QINGLONG_BATTLE_SETMATCHINFO					("OnSetQingLongBattleMatchInfo")
#define DEF_QINGLONG_BATTLE_SYNCTIME						("OnSyncQingLongBattleTime")
#define DEF_QINGLONG_BATTLE_ASK_ENTER_ZHUQUE 				("AskEnterQingLongBattle")
#define DEF_QINGLONG_BATTLE_QUERY_CURRENT_GUILD				("OnQueryCurrentGuild")
#define DEF_QINGLONG_BATTLE_SETENTERSCENEFLAG				("SetBattleEnterSceneFlag")
#define DEF_QINGLONG_BATTLE_SIGNUP_INSTEAD					("OnSignupInstead")

//据点
#define DEF_LAIRD_BATTLE_DEFAULT_EVENT						("OnBattleStateEvent")
#define DEF_LAIRD_BATTLE_CHANGE_SCENE_FUNC_NAME				("OnLairdBattleChangeScene")
#define DEF_LAIRD_BATTLE_ENTERSCENE_ERROR					("OnLairdBattleTransError")
#define DEF_LAIRD_BATTLE_SIGNUP_RESULT_FUNC_NAME			("OnLairdBattleSignupResult")
#define DEF_LAIRD_BATTLE_QUERY_SIGNUP_STATE_FUNC_NAME		("OnQueryLairdBattleSignupState")
#define DEF_LAIRD_BATTLE_ASK_PLAYER_ENTER_SCENE				("OnLairdBattleAskPlayerEnterScene")
#define DEF_LAIRD_BATTLE_SETMATCHINFO						("OnSetLairdBattleMatchInfo")
#define DEF_LAIRD_BATTLE_SETMATCHINFO_PLAYERAID0			("OnSetLairdBattleMatchInfo_PlayerAid0")
#define DEF_LAIRD_BATTLE_SETMATCHINFO_PLAYERAID1			("OnSetLairdBattleMatchInfo_PlayerAid1")
#define DEF_LAIRD_BATTLE_SYNCTIME							("OnSyncLairdBattleTime")
#define DEF_LAIRD_BATTLE_ASK_ENTER_ZHUQUE 					("AskEnterLairdBattle")
#define DEF_LAIRD_BATTLE_QUERY_CURRENT_GUILD				("OnQueryCurrentGuild")
#define DEF_LAIRD_BATTLE_SETENTERSCENEFLAG					("SetBattleEnterSceneFlag")
#define DEF_LAIRD_BATTLE_SIGNUP_INSTEAD						("OnSignupInstead")
#define DEF_LAIRD_BATTLE_RET_PLAYERAID_SIGNUPQUERY			("OnPlayerAidSignupQuery")
#define DEF_LAIRD_BATTLE_RET_PLAYERAID_SIGNUPEXECUTE		("OnPlayerAidSignupExecute")
#define DEF_LAIRD_BATTLE_PLAYERAID_BEGIN					("ProcPlayerAidBegin")
#define DEF_LAIRD_BATTLE_PLAYERAID_ADD						("ProcAddPlayerAid")
#define DEF_LAIRD_BATTLE_PLAYERAID_END						("ProcPlayerAidEnd")
#define DEF_LAIRD_BATTLE_PLAYERAID_SYNC_LW					("ProcPlayerAidSyncLw")
#define DEF_LAIRD_BATTLE_PLAYERAID_SYNC_HI					("ProcPlayerAidSyncHi")
#define DEF_LAIRD_BATTLE_SYNC_LAIRDINFO						("ProcSyncLairdInfo")
#define DEF_LAIRD_BATTLE_PLAYER_SYNC_LAIRDINFO				("ProcPlayerSyncLairdInfo")
#define DEF_LAIRD_BATTLE_EVENT_LAIRDLEVELUP					("ProcLairdLevelup")
//加密相关
#define DEF_COUNTRY_BETRAY_RESULT							("OnCountryBetrayResult")
#define DEF_ENCRYPT_MANAGER									("OnEncryptManager")
#define DEF_CHECK_ENCRYPT									("OnCheckEncrypt")
#define DEF_MAKE_KICK_TIME									("MakeKickTime")
#define DEF_D0_LOGIN_ANSWER									("DoLoginAnswer")
#define DEF_SWITCH_DAY_CHECK								("OnSwitchDayCheck")

//排行榜相关
#define DEF_TOPLIST_MENTAL									("OnTopListMental")
#define DEF_TOPLIST_GMCOMMAND								("OnTopListGMCommand")

//骑乘相关
#define DEF_ON_MAP_HORSE_CAPTURE							("OnMapHorseCaptureSuccesss")

//装备相关
#define DEF_ON_EQUIP_BLUE_INTENSIFY							("OnEquipBlueIntensify")
#define DEF_ON_EQUIP_BLUE_RESET								("OnEquipBlueReset")

#endif
