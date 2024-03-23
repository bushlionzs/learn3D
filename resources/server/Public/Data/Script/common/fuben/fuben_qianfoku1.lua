---------------------------------------------------
-- File: 700097_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700097_CSP_FUBENTYPE				= 	0
x700097_CSP_SCRIPTID				=	1
x700097_CSP_TICKCOUNT				= 	2
x700097_CSP_FROMSCENEID				= 	3
x700097_CSP_ISCLOSING				= 	4
x700097_CSP_LEAVECOUNTDOWN			= 	5
x700097_CSP_TEAMID					=	6
x700097_CSP_BACKSCENEX       		=   7
x700097_CSP_BACKSCENEZ      		=   8
x700097_CSP_FUBENLEVEL			=	9

x700097_CSP_KILLCOUNT				=	20
x700097_CSP_SPECIALMONSTER1			=   21
x700097_CSP_BOSS1					=   22
x700097_CSP_BOSS2					=   23
x700097_CSP_BOSS3					=   24
x700097_CSP_BOSS4					=   25
x700097_CSP_BOSS_COUNT				=   26

x700097_CSP_FUBEN_SCENE_ID			=	27

x700097_CSP_HUMAN_COUNT				=	240
x700097_CSP_OBJID_START				=	241
x700097_CSP_NEXT_SCENE				=   248
x700097_CSP_GUID_START              =   248

x700097_CSP_FUBEN_MODE				=   255 


------------------------Scene System Setting -----------------------------------

x700097_g_ScriptId 					= 700097                    --脚本号

---------------------------- special for fuben -----------------------------
x700097_g_RandomMonsterRate			=	0

x700097_g_SubmitNPC                 =   { type =25075,guid= 150531,x = 57, z=101, facedir =0, title="" }

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700097_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

end

function x700097_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700097_ShowTipsToAll(sceneId, str)

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
function x700097_OnFubenSceneCreated( sceneId )
	
	SetFubenData_Param(sceneId, x700097_CSP_BOSS4, -1);

    x700097_CreateMonster( sceneId )
	x700097_CreateBoss( sceneId )
	x700097_CreateRandomMonster(sceneId)
end

function x700097_EnterTick(sceneId, nowTickCount)
end

function x700097_CreateBoss(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700097_CSP_FUBENLEVEL ) ;
	SetFubenData_Param(sceneId, x700097_CSP_BOSS_COUNT, 0 )


	local nIndexFrom = GetFubenDataPosByScriptID(x700097_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700097_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700097_g_ScriptId,nIndexFrom,i)
		if idScript == x700097_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel then
		    local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700097_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700097_g_ScriptId, -1, 21,-1,facedir)
			end

			if flag == 2 then
				SetFubenData_Param(sceneId, x700097_CSP_SPECIALMONSTER1, nRet )
			end

			if flag==0 then
				SetFubenData_Param(sceneId, x700097_CSP_BOSS1, nRet )
			elseif flag==1 then
				SetFubenData_Param(sceneId, x700097_CSP_BOSS2, nRet )
			elseif flag==2 then
				SetFubenData_Param(sceneId, x700097_CSP_BOSS3, nRet )
			end
        end
	end

end

---------------------------------------------------------------------------------------------------
--创建BOSS2
---------------------------------------------------------------------------------------------------
function x700097_CreateBoss2(sceneId,x,z)

	local fubenlevel = GetFubenData_Param(sceneId, x700097_CSP_FUBENLEVEL ) ;

	local nIndexFrom = GetFubenDataPosByScriptID(x700097_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700097_g_ScriptId )
	
	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700097_g_ScriptId,nIndexFrom,i)
		if idScript == x700097_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel then
		    local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700097_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700097_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700097_CSP_BOSS4, nRet )
        end
	end

end


---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700097_CreateMonster(sceneId)


    local fubenlevel = GetFubenData_Param(sceneId, x700097_CSP_FUBENLEVEL ) ;

	local nIndexFrom = GetFubenDataPosByScriptID(x700097_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700097_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700097_g_ScriptId,nIndexFrom,i)
		if idScript == x700097_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
				if title~="" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir, "",title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				end
            end
        end
	end

end

function x700097_CreateRandomMonster(sceneId)



	local rate = random(0,100)/100;
	if rate>= x700097_g_RandomMonsterRate then
		return 0;
	end



	local fubenlevel = GetFubenData_Param(sceneId, x700097_CSP_FUBENLEVEL ) ;


	
	local bCreated =0;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700097_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700097_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700097_g_ScriptId,nIndexFrom,i)
		if idScript == x700097_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
		        
				local nRet = 0;
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21, -1,facedir, "", title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21, -1,facedir)
				end

				
				if patrolid>=0 then
					SetPatrolId(sceneId, nRet, patrolid)
					
				end
            end
        end
	end

	

end


function x700097_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700097_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700097_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	if nDieCount== x700097_NeedKillMonster_Count then
		--x700097_OnAllMonsterDead( sceneId) 
	end

	local objId1 = GetFubenData_Param(sceneId, x700097_CSP_SPECIALMONSTER1)
	local objId2 = GetFubenData_Param(sceneId, x700097_CSP_BOSS1)
	local objId3 = GetFubenData_Param(sceneId, x700097_CSP_BOSS2)
	local objId4 = GetFubenData_Param(sceneId, x700097_CSP_BOSS3)
	local objId5 = GetFubenData_Param(sceneId, x700097_CSP_BOSS4)

--	--//--------------------------- 世界喊话 Start--------------------
--	
--	local nowTickCount = GetFubenData_Param(sceneId, x700097_CSP_TICKCOUNT)
--
--	local nowTime = x700097_g_TickTime* nowTickCount;
--
--	local nMinute = floor(nowTime/60)
--	local nSec = mod(nowTime,60)
--
--		
--	local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
--	-------- if killed by pet -----------------
--	local nKillerType = GetObjType(sceneId, killerId)
--	
--	if nKillerType== 3 then
--		local nOwnerId = GetOwnerID(sceneId, killerId)
--		strPlayerName = GetName(sceneId, nOwnerId)
--	end
--	--------- end -------------------------------
--	
--	local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--	local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件
--
--	
--	if selfId == objId2 then -- boss flag=0
--		LuaAllScenceM2Wrold (sceneId,"#R“不，我是天命之人，我是神的使者，这不可能！”勃鲁合怎么也没有想到勇士#G"..strPlayerName.."#R带领着队友仅用了#G"..strKillTime.."#R就将自己多年苦心经营的计划全盘毁掉。", 0, 1)
--	end
--
--	if selfId == objId3 then -- boss flag=1
--		LuaAllScenceM2Wrold (sceneId,x700097_g_FubenName.."玩家"..strPlayerName.."在"..strKillTime.."杀死"..strBossName, 0, 1)
--	end

--	if selfId == objId4 then -- boss flag=2
--		LuaAllScenceM2Wrold (sceneId,x700097_g_FubenName.."玩家"..strPlayerName.."在"..strKillTime.."杀死"..strBossName, 0, 1)
--	end

--	if selfId == objId5 then -- boss flag= 变身后的boss
--		LuaAllScenceM2Wrold (sceneId,x700097_g_FubenName.."玩家"..strPlayerName.."在"..strKillTime.."杀死"..strBossName, 0, 1)
--	end
	
	
	--//--------------------------- 世界喊话 end----------------------

	
	if objId1 == selfId then		
		local x,z = GetWorldPos(sceneId,objId1)
		x700097_CreateBoss2(sceneId,x,z)
	end

	if selfId ==objId2 or selfId ==objId3 or selfId ==objId4 or selfId ==objId5 then
		local nCurrentBossCount = GetFubenData_Param(sceneId, x700097_CSP_BOSS_COUNT)
		SetFubenData_Param(sceneId, x700097_CSP_BOSS_COUNT, nCurrentBossCount+1 )
		nCurrentBossCount = nCurrentBossCount +1
		if nCurrentBossCount>=2 then
			x700097_CreateSubmitNpc( sceneId)
		end
	end
end

function x700097_OnAllMonsterDead( sceneId)
	x700097_CreateSubmitNpc( sceneId)
end

function x700097_CreateSubmitNpc( sceneId)
	 if x700097_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700097_g_SubmitNPC.type, x700097_g_SubmitNPC.x, x700097_g_SubmitNPC.z, 3, 0, -1, x700097_g_SubmitNPC.guid, -1,-1,x700097_g_SubmitNPC.facedir,  "", x700097_g_SubmitNPC.title)
	 else
		CreateMonster(sceneId, x700097_g_SubmitNPC.type, x700097_g_SubmitNPC.x, x700097_g_SubmitNPC.z, 3, 0, -1, x700097_g_SubmitNPC.guid, -1,-1,x700097_g_SubmitNPC.facedir)
	 end

	 --// add for 现金副本
	 --x700097_CreateXianJinBoss(sceneId)
	 local nFubenMode = GetFubenData_Param(sceneId, x700097_CSP_FUBEN_MODE)
	 if nFubenMode==1 then
	 	SetGrowPointIntervalContainer(sceneId,541,1)
	 	x700097_ShowTipsToAll(sceneId, "现金宝箱出现！")
	 end
	 --// add end
	 
end

----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700097_CreateXianJinBoss(sceneId)
	local nFubenMode = GetFubenData_Param(sceneId, x700097_CSP_FUBEN_MODE)

	if nFubenMode~=1 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700097_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700097_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700097_g_ScriptId )
	
	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700097_g_ScriptId,nIndexFrom,i)
		if idScript == x700097_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
			end
			
		end
	end

	x700097_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end

---------------------------------------------------------------------------------------------------
--进入区域
---------------------------------------------------------------------------------------------------
function x700097_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700097_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end

