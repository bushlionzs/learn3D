---------------------------------------------------
-- File: 700019_fuben_HUOSHANMUDI_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700019_CSP_FUBENTYPE				= 	0
x700019_CSP_SCRIPTID				=	1
x700019_CSP_TICKCOUNT				= 	2
x700019_CSP_FROMSCENEID				= 	3
x700019_CSP_ISCLOSING				= 	4
x700019_CSP_LEAVECOUNTDOWN			= 	5
x700019_CSP_TEAMID					=	6
x700019_CSP_BACKSCENEX       		=   7
x700019_CSP_BACKSCENEZ      		=   8
x700019_CSP_FUBENLEVEL			=	9

x700019_CSP_KILLCOUNT				=	20
x700019_CSP_BOSS_ID					=   21
x700019_CSP_FUBEN_SCENE_ID			=	22

x700019_CSP_SMALL_BOSS1_ID			=	40
x700019_CSP_SMALL_BOSS2_ID			=	45
x700019_CSP_SMALL_BOSS3_ID			=	50
x700019_CSP_SMALL_BOSS4_ID			=	55
x700019_CSP_SMALL_BOSS5_ID			=	60

x700019_CSP_HUMAN_COUNT				=	240
x700019_CSP_OBJID_START				=	241
x700019_CSP_GUID_START              =   248
------------------------Scene System Setting -----------------------------------

x700019_g_ScriptId 					= 700019

x700019_g_SubmitNPC                 =   { type =25013,guid= 150513,x = 95, z=87, facedir =0, title = "" }





function x700019_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

	
end


-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700019_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id

	for i=x700019_CSP_SMALL_BOSS1_ID, x700019_CSP_SMALL_BOSS1_ID+30 do
		SetFubenData_Param(sceneId, i, -1);
	end
	
	x700019_CreateBoss( sceneId )
	x700019_CreateSmallBoss(sceneId)
    x700019_CreateMonster( sceneId )
		
	
end

function x700019_EnterTick(sceneId, nowTickCount)
end


function x700019_CreateBoss(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700019_CSP_FUBENLEVEL ) ;

	
	local nIndexFrom = GetFubenDataPosByScriptID(x700019_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700019_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700019_g_ScriptId,nIndexFrom,i)
		if idScript == x700019_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then
			
		    local nRet = 0;
			if title ~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700019_g_ScriptId, -1, 21,-1,facedir, "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700019_g_ScriptId, -1, 21,-1,facedir)
			end
			
			SetFubenData_Param(sceneId, x700019_CSP_BOSS_ID, nRet )
			break;
			
        end
	end

end

function x700019_CreateSmallBoss(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700019_CSP_FUBENLEVEL ) ;

	
	local nIndexFrom = GetFubenDataPosByScriptID(x700019_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700019_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700019_g_ScriptId,nIndexFrom,i)
		if idScript == x700019_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel then
		    
			local nRet = 0;
			if title ~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700019_g_ScriptId, -1, 21,-1,facedir, "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700019_g_ScriptId, -1, 21,-1,facedir)
			end

			if flag==0 then
				SetFubenData_Param(sceneId, x700019_CSP_SMALL_BOSS1_ID, nRet )
			elseif flag==1 then
				SetFubenData_Param(sceneId, x700019_CSP_SMALL_BOSS2_ID, nRet )
			elseif flag==2 then
				SetFubenData_Param(sceneId, x700019_CSP_SMALL_BOSS3_ID, nRet )
			elseif flag==3 then
				SetFubenData_Param(sceneId, x700019_CSP_SMALL_BOSS4_ID, nRet )
			elseif flag==4 then
				SetFubenData_Param(sceneId, x700019_CSP_SMALL_BOSS5_ID, nRet )
			end
        end
	end

end

function x700019_CreateOneSubBoss(sceneId,nBossIndex,x,z)
	local fubenlevel = GetFubenData_Param(sceneId, x700019_CSP_FUBENLEVEL ) ;

	local nObjId = GetFubenData_Param(sceneId, nBossIndex ) ;

	
	local nIndexFrom = GetFubenDataPosByScriptID(x700019_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700019_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700019_g_ScriptId,nIndexFrom,i)
		if idScript == x700019_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			for j=1, 4 do
				local rx = random(-r,r)
                local tx = x + rx
                local rz = random(-r,r)
                local tz = z + rz
				

				local nRet = 0;
				if title ~="" then
					nRet = CreateMonster(sceneId, type, tx, tz, ai, aiscript, x700019_g_ScriptId, -1, 21,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, tx, tz, ai, aiscript, x700019_g_ScriptId, -1, 21,-1,facedir)
				end
			
				SetFubenData_Param(sceneId, nBossIndex+j, nRet )
			
			end
        end
	end

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = "怪物分裂"
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end
end

function x700019_CreateTwoSubBoss(sceneId,nBossIndex,x,z)

	local fubenlevel = GetFubenData_Param(sceneId, x700019_CSP_FUBENLEVEL ) ;

	local nObjId = GetFubenData_Param(sceneId, nBossIndex ) ;

	
	local nIndexFrom = GetFubenDataPosByScriptID(x700019_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700019_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700019_g_ScriptId,nIndexFrom,i)
		if idScript == x700019_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel then
			
			for j=1, 2 do
				local rx = random(-r,r)
				local tx = x + rx
				local rz = random(-r,r)
				local tz = z + rz
				
				local nRet = 0;
				if title ~="" then
					nRet = CreateMonster(sceneId, type, tx, tz, ai, aiscript, -1, -1, 21,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, tx, tz, ai, aiscript, -1, -1, 21,-1,facedir)
				end
			
			end
        end
	end

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = "怪物再次分裂"
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end
end

function x700019_OnSubBossDie(sceneId,nBossIndex,x,z)
	
	if nBossIndex<x700019_CSP_SMALL_BOSS1_ID or nBossIndex>x700019_CSP_SMALL_BOSS1_ID+30 then
		return
	end
	
	

	

	if mod((nBossIndex-x700019_CSP_SMALL_BOSS1_ID),5)==0 then
		
		x700019_CreateOneSubBoss(sceneId,nBossIndex,x,z)
		
	else
		x700019_CreateTwoSubBoss(sceneId,nBossIndex,x,z)
	end
		
end




---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700019_CreateMonster(sceneId)


    local fubenlevel = GetFubenData_Param(sceneId, x700019_CSP_FUBENLEVEL ) ;

	local nIndexFrom = GetFubenDataPosByScriptID(x700019_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700019_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700019_g_ScriptId,nIndexFrom,i)
		if idScript == x700019_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x1 + rx
                local rz = random(-r,r)
                local z = z1 + rz
		       
				local nRet = 0;
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700019_g_ScriptId, -1, 21,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700019_g_ScriptId, -1, 21,-1,facedir)
				end
            end
        end
	end

end


function x700019_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700019_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700019_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	
	local objId1 = GetFubenData_Param(sceneId, x700019_CSP_BOSS_ID)

	
	if objId1 == selfId then
		SetFubenData_Param(sceneId, x700019_CSP_BOSS_ID,-1)
		x700019_OnAllMonsterDead( sceneId)		
		
--		--//--------------------------- 世界喊话 Start--------------------
--			--杀死boss1
--			local nowTickCount = GetFubenData_Param(sceneId, x700019_CSP_TICKCOUNT)
--
--			local nowTime = x700019_g_TickTime* nowTickCount;
--
--			local nMinute = floor(nowTime/60)
--			local nSec = mod(nowTime,60)
--
--				
--			local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
--			-------- if killed by pet -----------------
--			local nKillerType = GetObjType(sceneId, killerId)
--			--PrintStr(nKillerType)
--			if nKillerType== 3 then
--				local nOwnerId = GetOwnerID(sceneId, killerId)
--				strPlayerName = GetName(sceneId, nOwnerId)
--			end
--			--------- end -------------------------------
--
--			local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--			local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件
--
--			
--			
--			LuaAllScenceM2Wrold (sceneId,"#G"..strPlayerName.."#R带领着队伍仅用了#G"..strKillTime.."#R就清除了所有的怪物，古迹沉重的大门在一阵轰鸣中重新关闭……", 0, 1)
--			
--			
--			--//--------------------------- 世界喊话 end----------------------
	end


	local objId1 = GetFubenData_Param(sceneId, x700019_CSP_SMALL_BOSS1_ID)
	local objId2 = GetFubenData_Param(sceneId, x700019_CSP_SMALL_BOSS2_ID)
	local objId3 = GetFubenData_Param(sceneId, x700019_CSP_SMALL_BOSS3_ID)
	local objId4 = GetFubenData_Param(sceneId, x700019_CSP_SMALL_BOSS4_ID)
	local objId5 = GetFubenData_Param(sceneId, x700019_CSP_SMALL_BOSS5_ID)


	for i=x700019_CSP_SMALL_BOSS1_ID, x700019_CSP_SMALL_BOSS1_ID+30 do
		local nObjId = GetFubenData_Param(sceneId, i);
		if nObjId>=0 and IsObjValid(sceneId,nObjId) == 1 then
			if nObjId==selfId then
				local x,z =GetWorldPos(sceneId,nObjId)
				SetFubenData_Param(sceneId, i,-1);
				x700019_OnSubBossDie(sceneId,i,x,z)
			end
		end
	end

	
end

function x700019_OnAllMonsterDead( sceneId)
	x700019_CreateSubmitNpc( sceneId)
end

function x700019_CreateSubmitNpc( sceneId)
	if x700019_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700019_g_SubmitNPC.type, x700019_g_SubmitNPC.x, x700019_g_SubmitNPC.z, 3, 0, -1, x700019_g_SubmitNPC.guid, -1,-1, x700019_g_SubmitNPC.facedir,  "",x700019_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700019_g_SubmitNPC.type, x700019_g_SubmitNPC.x, x700019_g_SubmitNPC.z, 3, 0, -1, x700019_g_SubmitNPC.guid, -1,-1, x700019_g_SubmitNPC.facedir)
	
	end
end






