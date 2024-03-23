---------------------------------------------------
-- File: 700023_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700023_CSP_FUBENTYPE				= 	0
x700023_CSP_SCRIPTID				=	1
x700023_CSP_TICKCOUNT				= 	2
x700023_CSP_FROMSCENEID				= 	3
x700023_CSP_ISCLOSING				= 	4
x700023_CSP_LEAVECOUNTDOWN			= 	5
x700023_CSP_TEAMID					=	6
x700023_CSP_BACKSCENEX       		=   7
x700023_CSP_BACKSCENEZ      		=   8
x700023_CSP_FUBENLEVEL			=	9

x700023_CSP_KILLCOUNT				=	20
x700023_CSP_FUBEN_SCENE_ID			=	21

x700023_CSP_BOSS_ID					=	22
x700023_CSP_BOSS_IS_DIE				=	23
x700023_CSP_BOSS_FULL_HP			=   24
x700023_CSP_BOSS_LOADMONSTER_START  =   100
		
x700023_CSP_AREA_ID					=   230
x700023_CSP_AREA_FLAG				=	231
x700023_CSP_XIANJINBOSS				=	239

x700023_CSP_HUMAN_COUNT				=	240
x700023_CSP_OBJID_START				=	241

x700023_CSP_GUID_START              =   248  --空6个
x700023_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型

x700023_CSP_FUBEN_MODE				=   255 

------------------------Scene System Setting -----------------------------------

x700023_g_ScriptId 					= 700023
x700023_g_MissionId					= 6608


--返回王城
function x700023_TeleportWangCheng(sceneId, selfId)
		local selfcountry =GetCurCountry( sceneId, selfId)
        TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
        TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
		if selfcountry == 0 then
        	NewWorld( sceneId, selfId, selfcountry * 100 + 50, 75 + random( 0, 5), 180 + random( 0, 5), x700023_g_ScriptId)
		elseif selfcountry ==1 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 75 + random( 0, 5), 180 + random( 0, 5), x700023_g_ScriptId)
		elseif selfcountry ==2 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 181 + random( 0, 5), 76 + random( 0, 5), x700023_g_ScriptId)
		elseif selfcountry ==3 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 181 + random( 0, 5), 76 + random( 0, 5), x700023_g_ScriptId)
		end
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700023_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)
	--print("x700023_ProcEventEntry",nScriptId,nFlag)
	if nFlag == 2 then
		CallScriptFunction(700081,"OnRequestEnterFuben", sceneId, selfId, 0, 22)
	elseif nFlag == 1 then
		x700023_TeleportWangCheng(sceneId, selfId)	
	end
end

function x700023_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end



-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700023_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	
	--x700023_CreateMonster( sceneId )
	SetFubenData_Param(sceneId, x700023_CSP_XIANJINBOSS, -1 )
    x700023_CreateMonster( sceneId )
	x700023_CreateBoss( sceneId )
		
end

function x700023_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	SetFubenData_Param(sceneId, x700023_CSP_AREA_ID, zoneId)
	--print("x700091_ProcAreaEntered"..zoneId.." "..MissionId)
	--@param sceneId: 场景Id
	--@param selfId: 玩家ObjId (宠物进入EnterArea也会触发这个时间)
	--@param zoneId: 区域Id
	--@param MissionId: 任务id\
		--print("x700023_ProcAreaEntered = ",zoneId)
	if zoneId == 1 then
		zoneId = 0
	else
		zoneId = 1
	end
	
	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700023_CSP_BOSS_ID)
		--print("BossId",BossId)
		if BossId ~= -1 then
			return --TEST
		end
		SetFubenData_Param(sceneId, x700023_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700023_g_MissionId, x700023_g_ScriptId)
		--print("1111111111")
	else
	 	CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700023_g_MissionId, x700023_g_ScriptId)
	end


	
	if zoneId == 1 then  --出口
		
	elseif zoneId == 2 then   --入口
		
	elseif zoneId == 3 then   --入口 开门
		
	--elseif zoneId == 4 then   --入口 动态阻挡
		
	end
end	
---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700023_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )
	EnterAreaEventListHideNM(sceneId, selfId)
	SetFubenData_Param(sceneId, x700023_CSP_AREA_ID, -1)
	--print("x700023_ProcAreaLeaved"..zoneId)
--@param sceneId: 场景Id
--@param selfId: 玩家ObjId (宠物进入EnterArea也会触发这个时间)
--@param zoneId: 区域Id
--@param MissionId: 任务id

	
end
function x700023_ShowTipsToAll(sceneId, str)

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
---------------------------------------------------------------------------------------------------
--区域定时器
---------------------------------------------------------------------------------------------------
function x700023_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	local zoneId = GetFubenData_Param(sceneId, x700023_CSP_AREA_ID )
	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700023_CSP_BOSS_ID)
		--print("BossId",BossId)
		if BossId ~= -1 then
			return --TEST
		end
		local flag = GetFubenData_Param(sceneId, x700023_CSP_AREA_FLAG)
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700023_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700023_g_MissionId, x700023_g_ScriptId)
		--print("1111111111")
	elseif zoneId == 1 then
	 	--CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700023_g_MissionId, x700023_g_ScriptId)
	end
end

--//add end
function x700023_EnterTick(sceneId, nowTickCount)
--x700023_CreateBoss(sceneId)
	if nowTickCount >= 2 then
		local nBoss2 = GetFubenData_Param(sceneId, x700023_CSP_BOSS_ID )

		
		
		if nBoss2>0 then
			local humancount = GetFuben_PlayerCount(sceneId);
			if humancount>0 then
				local nCurrentHp = GetHp( sceneId, nBoss2 )
				local nFullHp = GetFubenData_Param(sceneId, x700023_CSP_BOSS_FULL_HP )


				if nCurrentHp/nFullHp <0.2 then
					--print("x700023_EnterTick1")
					local bCreatedSubMonster = GetFubenData_Param(sceneId, x700023_CSP_BOSS_LOADMONSTER_START+0 )
					if bCreatedSubMonster<=0 then
						x700023_CreateSubMonster(sceneId,0)
						
					end
--				elseif nCurrentHp/nFullHp <0.4 then
--					--print("x700023_EnterTick2")
--					local bCreatedSubMonster = GetFubenData_Param(sceneId, x700023_CSP_BOSS_LOADMONSTER_START+1)
--					if bCreatedSubMonster<=0 then
--						x700023_CreateSubMonster(sceneId,1)
--					end
				elseif nCurrentHp/nFullHp <0.5 then
				--print("x700023_EnterTick3")
					local bCreatedSubMonster = GetFubenData_Param(sceneId, x700023_CSP_BOSS_LOADMONSTER_START+2 )
					if bCreatedSubMonster<=0 then
						x700023_CreateSubMonster(sceneId,2)
												
					end
				elseif nCurrentHp/nFullHp <0.8 then
				--print("x700023_EnterTick4")
					local bCreatedSubMonster = GetFubenData_Param(sceneId, x700023_CSP_BOSS_LOADMONSTER_START+3 )
					if bCreatedSubMonster<=0 then
						x700023_CreateSubMonster(sceneId,3)
						
					end
				end
				
			end
		end
	end
end

function x700023_CreateBoss(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700023_CSP_FUBENLEVEL ) ;

	local nFubenType = GetFubenData_Param(sceneId, x700023_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700023_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700023_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700023_g_ScriptId,nIndexFrom,i)
		if idScript == x700023_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700023_g_ScriptId, -1, 21,-1, facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700023_g_ScriptId, -1, 21,-1, facedir)
			
			end

			
				
			SetFubenData_Param(sceneId, x700023_CSP_BOSS_ID, nRet )
			local nFullHp = GetHp( sceneId, nRet )
			SetFubenData_Param(sceneId, x700023_CSP_BOSS_FULL_HP, nFullHp )
			--print("x700023_CreateBoss========",nRet,x,z)
			for j=0, 5-1 do
				--print("x700023_CreateBoss",j,nRet,x,z)
				SetFubenData_Param(sceneId, x700023_CSP_BOSS_LOADMONSTER_START+j, 0 )
			end
			
			break;
			
        end
	end

end


---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700023_CreateMonster(sceneId)

	--print("x700023_CreateMonster")
    local fubenlevel = GetFubenData_Param(sceneId, x700023_CSP_FUBENLEVEL ) ;
	local nFubenType = GetFubenData_Param(sceneId, x700023_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700023_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700023_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700023_g_ScriptId,nIndexFrom,i)
		if idScript == x700023_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x1 + rx
                local rz = random(-r,r)
                local z = z1 + rz
				if title~="" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,  "",title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				
				end
				
				--print("x700023_CreateMonster===========")
			end
        end
	end


end



function x700023_CreateSubMonster(sceneId, iIndex)

	
	local bCreatedSubMonster = GetFubenData_Param(sceneId, x700023_CSP_BOSS_LOADMONSTER_START+iIndex )

	if bCreatedSubMonster>0 then
		return 0;
	end

	SetFubenData_Param(sceneId, x700023_CSP_BOSS_LOADMONSTER_START+iIndex, 1 )

	
	local fubenlevel = GetFubenData_Param(sceneId, x700023_CSP_FUBENLEVEL ) ;
	local nFubenType = GetFubenData_Param(sceneId, x700023_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700023_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700023_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700023_g_ScriptId,nIndexFrom,i)
		if idScript == x700023_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
			 for j=0,count -1 do

                local rx = random(-r,r)
                local x = x1 + rx
                local rz = random(-r,r)
                local z = z1 + rz
		        local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				
				end
				SetPatrolId(sceneId, nRet, 0)
            end
        end
	end

	local strPercent= ""


	

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = format("起来！我的勇士们！");
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);

		DispatchQuestTips(sceneId, humanId);
	end

	
end





function x700023_OnDie(sceneId, selfId, killerId)

	
	local xianjinboss = GetFubenData_Param(sceneId, x700023_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	local nDieCount = GetFubenData_Param(sceneId, x700023_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700023_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	
	local objId2 = GetFubenData_Param(sceneId, x700023_CSP_BOSS_ID)
	
	if objId2 == selfId then
		SetFubenData_Param(sceneId, x700023_CSP_BOSS_ID, -1)
		x700023_OnFubenEnd( sceneId)
		x700023_ShowTipsToAll(sceneId, "成功击杀摩诃末，副本完成。") 
		--//--------------------------- 世界喊话 Start--------------------
			--杀死boss1
--			local nowTickCount = GetFubenData_Param(sceneId, x700023_CSP_TICKCOUNT)

--			local nowTime = x700023_g_TickTime* nowTickCount;

--			local nMinute = floor(nowTime/60)
--			local nSec = mod(nowTime,60)

				
--			local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
--			-------- if killed by pet -----------------
--			local nKillerType = GetObjType(sceneId, killerId)
--			--PrintStr(nKillerType)
--			if nKillerType== 3 then
--				local nOwnerId = GetOwnerID(sceneId, killerId)
--				strPlayerName = GetName(sceneId, nOwnerId)
--			end
--			--------- end -------------------------------
--			local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--			local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件

			
			
--			LuaAllScenceM2Wrold (sceneId,x700023_g_FubenName.."玩家"..strPlayerName.."在"..strKillTime.."杀死"..strBossName, 0, 1)
			

			
			
			--//--------------------------- 世界喊话 end----------------------
	end
end

function x700023_OnFubenEnd( sceneId)
	x700023_CreateXianJinBoss(sceneId)
	
	local humancount = GetFuben_PlayerCount(sceneId);
	for ii = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, ii);
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,51 )
		
		--print("PlayEffect 51",humancount)
	end	
end
----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700023_CreateXianJinBoss(sceneId)
	
	local nFubenType = GetFubenData_Param(sceneId, x700023_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700023_CSP_FUBEN_MODE)
	if nFubenMode == 0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700023_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700023_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700023_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700023_g_ScriptId,nIndexFrom,i)
		if idScript == x700023_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700023_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700023_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700023_CSP_XIANJINBOSS, nRet )
		end
	end

	x700023_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end

