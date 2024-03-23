---------------------------------------------------
-- File: 700028_fuben_qiulongdao_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700028_CSP_FUBENTYPE				= 	0
x700028_CSP_SCRIPTID				=	1
x700028_CSP_TICKCOUNT				= 	2
x700028_CSP_FROMSCENEID				= 	3
x700028_CSP_ISCLOSING				= 	4
x700028_CSP_LEAVECOUNTDOWN			= 	5
x700028_CSP_TEAMID					=	6
x700028_CSP_BACKSCENEX       		=   7
x700028_CSP_BACKSCENEZ      		=   8
x700028_CSP_FUBENLEVEL			=	9

x700028_CSP_KILLCOUNT				=	20
x700028_CSP_FUBEN_SCENE_ID			=	21
x700028_CSP_BOSS_ID					=	22
x700028_CSP_BOSS_FULL_HP			=   23
x700028_CSP_BOSS_LOADMONSTER_START	=   24

x700028_CSP_HUMAN_COUNT				=	240
x700028_CSP_OBJID_START				=	241
x700028_CSP_GUID_START              =   248  --空6个
x700028_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型

x700028_CSP_FUBEN_MODE				=   255 

------------------------Scene System Setting -----------------------------------

x700028_g_ScriptId 					= 700028

x700028_g_SubmitNPC                 =   { type =25001,guid= 150501,x = 72, z=48, facedir =0, title = "" }



-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700028_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)
	
end




function x700028_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700028_ShowTipsToAll(sceneId, str)

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

-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700028_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	
	
	
	
	
    x700028_CreateMonster( sceneId )
	x700028_CreateBoss( sceneId )

	
		
end

function x700028_EnterTick(sceneId, nowTickCount)
	if nowTickCount >= 2 then
		local nBoss2 = GetFubenData_Param(sceneId, x700028_CSP_BOSS_ID )

		
		
		if nBoss2>0 then
			local humancount = GetFuben_PlayerCount(sceneId);
			if humancount>0 then
				local nCurrentHp = GetHp( sceneId, nBoss2 )
				local nFullHp = GetFubenData_Param(sceneId, x700028_CSP_BOSS_FULL_HP )


				if nCurrentHp/nFullHp <0.2 then
					local bCreatedSubMonster = GetFubenData_Param(sceneId, x700028_CSP_BOSS_LOADMONSTER_START+0 )
					if bCreatedSubMonster<=0 then
						x700028_CreateSubMonster(sceneId,0)
						
					end
				elseif nCurrentHp/nFullHp <0.5 then
					
					local bCreatedSubMonster = GetFubenData_Param(sceneId, x700028_CSP_BOSS_LOADMONSTER_START+1)
					if bCreatedSubMonster<=0 then
						x700028_CreateSubMonster(sceneId,1)
						
					end
				elseif nCurrentHp/nFullHp <0.8 then
					local bCreatedSubMonster = GetFubenData_Param(sceneId, x700028_CSP_BOSS_LOADMONSTER_START+2 )
					if bCreatedSubMonster<=0 then
						x700028_CreateSubMonster(sceneId,2)
						
					end
				end
				
			end
		end
	end
end

function x700028_CreateBoss(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700028_CSP_FUBENLEVEL ) ;

	local nFubenType = GetFubenData_Param(sceneId, x700028_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700028_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700028_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700028_g_ScriptId,nIndexFrom,i)
		if idScript == x700028_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700028_g_ScriptId, -1, 21,-1, facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700028_g_ScriptId, -1, 21,-1, facedir)
			
			end

			
				
			SetFubenData_Param(sceneId, x700028_CSP_BOSS_ID, nRet )
			local nFullHp = GetHp( sceneId, nRet )
			SetFubenData_Param(sceneId, x700028_CSP_BOSS_FULL_HP, nFullHp )

			for j=0, 5-1 do
				SetFubenData_Param(sceneId, x700028_CSP_BOSS_LOADMONSTER_START+j, 0 )
			end
			
			break;
			
        end
	end

end



function x700028_CreateSubMonster(sceneId, iIndex)

	
	local bCreatedSubMonster = GetFubenData_Param(sceneId, x700028_CSP_BOSS_LOADMONSTER_START+iIndex )

	if bCreatedSubMonster>0 then
		return 0;
	end

	SetFubenData_Param(sceneId, x700028_CSP_BOSS_LOADMONSTER_START+iIndex, 1 )

	
	local fubenlevel = GetFubenData_Param(sceneId, x700028_CSP_FUBENLEVEL ) ;
	local nFubenType = GetFubenData_Param(sceneId, x700028_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700028_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700028_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700028_g_ScriptId,nIndexFrom,i)
		if idScript == x700028_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
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

	if iIndex==0 then
		strPercent= "20%"
	elseif iIndex==1 then
		strPercent= "50%"
	elseif iIndex==2 then
		strPercent= "80%"
	end

	

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = format("起来！我的勇士们！",strPercent);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);

		DispatchQuestTips(sceneId, humanId);
	end

	
end



---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700028_CreateMonster(sceneId)


    local fubenlevel = GetFubenData_Param(sceneId, x700028_CSP_FUBENLEVEL ) ;
	local nFubenType = GetFubenData_Param(sceneId, x700028_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700028_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700028_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700028_g_ScriptId,nIndexFrom,i)
		if idScript == x700028_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
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
			end
        end
	end


end




function x700028_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700028_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700028_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	
	local objId2 = GetFubenData_Param(sceneId, x700028_CSP_BOSS_ID)
	
	if objId2 == selfId then
		SetFubenData_Param(sceneId, x700028_CSP_BOSS_ID, -1)
		x700028_OnAllMonsterDead( sceneId)
	
		--//--------------------------- 世界喊话 Start--------------------
			--杀死boss1
--			local nowTickCount = GetFubenData_Param(sceneId, x700028_CSP_TICKCOUNT)

--			local nowTime = x700028_g_TickTime* nowTickCount;

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

			
			
--			LuaAllScenceM2Wrold (sceneId,x700028_g_FubenName.."玩家"..strPlayerName.."在"..strKillTime.."杀死"..strBossName, 0, 1)
			

			
			
			--//--------------------------- 世界喊话 end----------------------
	end
end

function x700028_OnAllMonsterDead( sceneId)
	x700028_CreateSubmitNpc( sceneId)
end

function x700028_CreateSubmitNpc( sceneId)
	if x700028_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700028_g_SubmitNPC.type, x700028_g_SubmitNPC.x, x700028_g_SubmitNPC.z, 3, 0, -1, x700028_g_SubmitNPC.guid, -1,-1,x700028_g_SubmitNPC.facedir,  "",x700028_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700028_g_SubmitNPC.type, x700028_g_SubmitNPC.x, x700028_g_SubmitNPC.z, 3, 0, -1, x700028_g_SubmitNPC.guid, -1,-1,x700028_g_SubmitNPC.facedir)
	
	end
	
	--// add for 现金副本
	 x700028_CreateXianJinBoss(sceneId)
	 --// add end
	 
	 CallScriptFunction( 701101, "OnSceneBossDie", sceneId, 0)
	 CallScriptFunction( 701102, "OnSceneBossDie", sceneId, 0)

end

----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700028_CreateXianJinBoss(sceneId)
	
	local nFubenType = GetFubenData_Param(sceneId, x700028_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700028_CSP_FUBEN_MODE)
	if nFubenMode == 0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700028_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700028_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700028_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700028_g_ScriptId,nIndexFrom,i)
		if idScript == x700028_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
			end
			
		end
	end

	x700028_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end




