---------------------------------------------------
-- File: 
-- Author: Peng Lin
-- Created: 2010-03-18
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700027_CSP_FUBENTYPE				= 	0
x700027_CSP_SCRIPTID				=	1
x700027_CSP_TICKCOUNT				= 	2
x700027_CSP_FROMSCENEID				= 	3
x700027_CSP_ISCLOSING				= 	4
x700027_CSP_LEAVECOUNTDOWN			= 	5
x700027_CSP_TEAMID					=	6
x700027_CSP_TICKTIME				=	7
x700027_CSP_HOLDTIME				=	8
x700027_CSP_FUBENLEVEL				=	9

x700027_CSP_AREA_ID					=	20
x700027_CSP_AREA_FLAG				=	21
x700027_B_CREATE_RANDOMBOSS			=	230
x700027_CSP_RANDOM_BOSS_ID			=	231
x700027_RANDOMBOSS_FLAG				=	232

x700027_CSP_BOSS_ID					=   233
x700027_CSP_XIANJINBOSS				=	239
x700027_CSP_HUMAN_COUNT				=	240
x700027_CSP_PLAYER_ENTER_START		=	241

x700027_CSP_LAST_TICKOUNT			=	247
x700027_CSP_GUID_START				=   248
x700027_CSP_FUBEN_TYPE				=	254	--三种类型 0:普通(队伍),1:试练,2:英雄
x700027_CSP_FUBEN_MODE				=   255
------------------------Scene System Setting -----------------------------------

x700027_g_ScriptId 					= 700027
x700027_g_MissionId					= 6608
-------------------------fuben data begin-----------------------

  
x700027_g_RandomBossRate			=   1--0.5

x700027_g_RandomMonsterRate			=	0.05

                  
-------------------------fuben data end-----------------------

----------------------------------------------------------
--处理点击对话npc的事件
----------------------------------------------------------
function x700027_ProcEventEntry(sceneId,selfId,targetId)

end

-------------------------------------------------------------------------------
--当副本创建成功时， 开始刷怪和npc
-------------------------------------------------------------------------------
function x700027_OnFubenSceneCreated( sceneId )
	 
	for i = 20,239 do
		SetFubenData_Param(sceneId, i,-1)
	end

	x700027_CreateMonster(sceneId)
	x700027_CreateBoss(sceneId)

end

---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700027_CreateMonster(sceneId)

    local fubenlevel = GetFubenData_Param(sceneId, x700027_CSP_FUBENLEVEL ) ;
	local nFubenType = GetFubenData_Param(sceneId, x700027_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700027_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700027_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700027_g_ScriptId,nIndexFrom,i)
		if idScript == x700027_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do
            	local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				
				end
				
				SetPatrolId(sceneId, nRet, patrolid)
			end
        end
	end


end

function x700027_CreateBoss(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700027_CSP_FUBENLEVEL ) ;

	local nFubenType = GetFubenData_Param(sceneId, x700027_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700027_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700027_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700027_g_ScriptId,nIndexFrom,i)
		if idScript == x700027_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700027_g_ScriptId, -1, 21,-1, facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700027_g_ScriptId, -1, 21,-1, facedir)
			
			end

			SetFubenData_Param(sceneId, x700027_CSP_BOSS_ID, nRet )
			SetPatrolId(sceneId, nRet, patrolid)
			
        end
	end

end


function x700027_OnDie(sceneId, selfId, killerId)
	local xianjinboss = GetFubenData_Param(sceneId, x700027_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	
	
	
	local bossid = GetFubenData_Param(sceneId, x700027_CSP_BOSS_ID)
	
	if bossid == selfId then
		SetFubenData_Param(sceneId, x700027_CSP_BOSS_ID, -1)
		x700027_OnFubenEnd( sceneId)
		x700027_ShowTipsToAll(sceneId, "成功击杀平经高，副本完成。")
	end
	
end

function x700027_OnFubenEnd( sceneId)
	x700027_CreateXianJinBoss(sceneId)
	local humancount = GetFuben_PlayerCount(sceneId);
	for ii = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, ii);
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,63 )
	end	
end
----------------------------------------------------------
--创建现金boss
----------------------------------------------------------
function x700027_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	local zoneId = GetFubenData_Param(sceneId, x700027_CSP_AREA_ID )
	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700027_CSP_BOSS_ID)
		print("BossId",BossId)
		if BossId ~= -1 then
			return --TEST
		end
		local flag = GetFubenData_Param(sceneId, x700027_CSP_AREA_FLAG)
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700027_CSP_AREA_FLAG,1)
		print("x700027_ProcAreaEntered",x700027_g_ScriptId)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700027_g_MissionId, x700027_g_ScriptId)
		
	else
	 	--CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700027_g_MissionId, x700027_g_ScriptId)
	end
end

--//add end
function x700027_EnterTick(sceneId, nowTickCount)
end

function x700027_CreateXianJinBoss(sceneId)
	
	local nFubenType = GetFubenData_Param(sceneId, x700027_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700027_CSP_FUBEN_MODE)
	if nFubenMode == 0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700027_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700027_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700027_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700027_g_ScriptId,nIndexFrom,i)
		if idScript == x700027_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700027_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700027_g_ScriptId, -1, 21,-1,facedir)
			end
			SetPatrolId(sceneId, nRet, patrolid)
			SetFubenData_Param(sceneId, x700027_CSP_XIANJINBOSS, nRet )
		end
	end

	x700027_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end

function x700027_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId);

	--通知玩家
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId,str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, humanId);
	end
end



function x700027_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	SetFubenData_Param(sceneId, x700027_CSP_AREA_ID, zoneId)
	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700027_CSP_BOSS_ID)
		print("BossId",BossId)
		if BossId ~= -1 then
			return --TEST
		end
		SetFubenData_Param(sceneId, x700027_CSP_AREA_FLAG,1)
		--print("x700027_ProcAreaEntered",x700027_g_ScriptId)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700027_g_MissionId, x700027_g_ScriptId)
		
	else
	 	CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700027_g_MissionId, x700027_g_ScriptId)
	end
end	
---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700027_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )
	EnterAreaEventListHideNM(sceneId, selfId)
	SetFubenData_Param(sceneId, x700027_CSP_AREA_ID, -1)
end