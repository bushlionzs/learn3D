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
x700023_CSP_BOSS1_ID				=	22
x700023_CSP_BOSS2_ID				=	23
x700023_CSP_BOSS1_FULL_HP			=	24
x700023_CSP_BOSS1_LOADMONSTER		=   25
x700023_CSP_BOSS3_ID				=	26
x700023_CSP_BOSS3_FLAG				=	27

x700023_CSP_CHILD_COUNT				=	40
x700023_CSP_CHILD_ID_START			=	41

x700023_CSP_PATROL_MONSTER_COUNT	=	70
x700023_CSP_PATROL_MONSTER_FULL_HP	=	71
x700023_CSP_PATROL_MONSTER_START	=	72

x700023_CSP_HUMAN_COUNT				=	240
x700023_CSP_OBJID_START				=	241

x700023_CSP_GUID_START              =   248  --空6个
x700023_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型

x700023_CSP_FUBEN_MODE				=   255 

------------------------Scene System Setting -----------------------------------

x700023_g_ScriptId 					= 700023

------------------------- special for fuben-------------------
x700023_g_OneTime_Child_Count		=	2                       --龙蛋每次刷出小龙数量
x700023_g_Max_Child_Count			=	20                      --龙蛋刷出的小龙同时存在的最大个数
x700023_g_BuffId					=	13503                   --龙蛋被打破后，小龙boss获得的buffid


x700023_g_SubmitNPC                 =   { type =25003,guid= 150503,x = 98, z=25, facedir =0, title = "" }



-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700023_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)
	
end


function x700023_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
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

-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700023_OnFubenSceneCreated( sceneId )
	

	SetFubenData_Param(sceneId, x700023_CSP_BOSS3_FLAG,-1) 

	x700023_CreateMonster( sceneId )
	x700023_CreateBoss( sceneId )
    x700023_CreatePatrolMonster( sceneId )

	
		
end



function x700023_EnterTick(sceneId,nowTickCount)

	if nowTickCount >= 2 then
		local nBoss1 = GetFubenData_Param(sceneId, x700023_CSP_BOSS1_ID )
		
		if nBoss1>=0 then
			local humancount = GetFuben_PlayerCount(sceneId);
			if humancount>0 then
				local nCurrentHp = GetHp( sceneId, nBoss1 )
				local nFullHp = GetFubenData_Param(sceneId, x700023_CSP_BOSS1_FULL_HP )
				
				local bCreatedSubMonster = GetFubenData_Param(sceneId, x700023_CSP_BOSS1_LOADMONSTER )
				
				if nFullHp>0 then
					if nCurrentHp/nFullHp <0.9 then
						if bCreatedSubMonster<=0 then
							x700023_CreateBoss2(sceneId)
						end
					end
				end
			end
		end
	end

	local nBoss3Flag = GetFubenData_Param(sceneId, x700023_CSP_BOSS3_FLAG) ;
	if nBoss3Flag>0 then
		if mod(nowTickCount,6) ==0 then  --每30秒
			x700023_CreateChildDragon(sceneId, x700023_g_OneTime_Child_Count)
		end
	end

	local nCount = GetFubenData_Param(sceneId, x700023_CSP_PATROL_MONSTER_COUNT)
	local nCount_dup = nCount;
	local nFullHp = GetFubenData_Param(sceneId, x700023_CSP_PATROL_MONSTER_FULL_HP)
	for i=0, nCount-1 do
		local nObjId = GetFubenData_Param(sceneId, x700023_CSP_PATROL_MONSTER_START+i)
		if nObjId>=0 then
			local nCurrentHp = GetHp( sceneId, nObjId )
			if nCurrentHp/nFullHp<=0.2 then
				SetFubenData_Param(sceneId, x700023_CSP_PATROL_MONSTER_START+i,-1)
				
				local x,z =GetWorldPos(sceneId,nObjId)
				DeleteMonster( sceneId,nObjId )
				x700023_CreateChangeMonster(sceneId,x,z)
				
			end
		end
	end

	for i=0, nCount-1 do
		local nObjId = GetFubenData_Param(sceneId, x700023_CSP_PATROL_MONSTER_START+i)
		
		if nObjId ==-1 then
		
			x700023_ArrayDeleteByIndex(sceneId,x700023_CSP_PATROL_MONSTER_START,nCount,i)
			nCount_dup = nCount_dup -1;
			
		end
	end

	SetFubenData_Param(sceneId, x700023_CSP_PATROL_MONSTER_COUNT,nCount_dup )

	
end

function x700023_ArrayDeleteByIndex(sceneId,arrayId,arrayLen, index)
	if arrayLen< index+1 then
		return
	end

	if arrayLen<=0 or index<0 then
		return
	end

	for i=index, arrayLen-2 do
		local nNextValue = GetFubenData_Param(sceneId, arrayId+i+1)
		SetFubenData_Param(sceneId, arrayId+i,nNextValue)
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
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700023_g_ScriptId, -1, 21,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700023_g_ScriptId, -1, 21,-1,facedir)
				
			end
			if flag ==0 then
				SetFubenData_Param(sceneId, x700023_CSP_BOSS1_ID, nRet ) ;
				local nFullHp = GetHp( sceneId, nRet )
				SetFubenData_Param(sceneId, x700023_CSP_BOSS1_FULL_HP, nFullHp )
				SetFubenData_Param(sceneId, x700023_CSP_BOSS1_LOADMONSTER, 0 )
			elseif flag ==1 then
				SetFubenData_Param(sceneId, x700023_CSP_BOSS2_ID, nRet ) ;
			end
        end
	end

end

---------------------------------------------------------------------------------------------------
--创建BOSS2
---------------------------------------------------------------------------------------------------
function x700023_CreateBoss2(sceneId)

	local bCreatedSubMonster = GetFubenData_Param(sceneId, x700023_CSP_BOSS1_LOADMONSTER )

	if bCreatedSubMonster>0 then
		return 0;
	end

	

	local fubenlevel = GetFubenData_Param(sceneId, x700023_CSP_FUBENLEVEL ) ;
	local nFubenType = GetFubenData_Param(sceneId, x700023_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700023_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700023_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700023_g_ScriptId,nIndexFrom,i)
		if idScript == x700023_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700023_g_ScriptId, -1, 21,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700023_g_ScriptId, -1, 21,-1,facedir)
			
			end
			SetFubenData_Param(sceneId, x700023_CSP_BOSS3_ID, nRet ) ;
			SetFubenData_Param(sceneId, x700023_CSP_BOSS3_FLAG, 1 ) ;
			break;
        end
	end

	SetFubenData_Param(sceneId, x700023_CSP_BOSS1_LOADMONSTER, 1 )

	local humancount = GetFuben_PlayerCount(sceneId);
	
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = "龙蛋出现";
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end
end


---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700023_CreateChildDragon(sceneId, nCount)  --龙蛋创建小怪

	local nCurrentChildCount = GetFubenData_Param(sceneId, x700023_CSP_CHILD_COUNT ) ;
	if (nCurrentChildCount+nCount)>x700023_g_Max_Child_Count then
		return
	end

	

    local fubenlevel = GetFubenData_Param(sceneId, x700023_CSP_FUBENLEVEL ) ;

	local iFlag =0
	local nFubenType = GetFubenData_Param(sceneId, x700023_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700023_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700023_g_ScriptId )
	
	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700023_g_ScriptId,nIndexFrom,i)
		if idScript == x700023_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,nCount -1 do

                local rx = random(-r,r)
                local x = x1 + rx
                local rz = random(-r,r)
                local z = z1 + rz
		        local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700023_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700023_g_ScriptId, -1, 21,-1,facedir)
				
				end
				SetFubenData_Param(sceneId, x700023_CSP_CHILD_ID_START+nCurrentChildCount+iFlag, nRet)
				iFlag = iFlag+1
				SetPatrolId(sceneId, nRet, 2)
            end
			break;
        end
	end

	SetFubenData_Param(sceneId, x700023_CSP_CHILD_COUNT, nCurrentChildCount+nCount)

	local humancount = GetFuben_PlayerCount(sceneId);
	
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = format("%d怪物出现， 地图上总%d 只",nCount,nCurrentChildCount+nCount);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end

end
---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700023_CreatePatrolMonster(sceneId)
	local fubenlevel = GetFubenData_Param(sceneId, x700023_CSP_FUBENLEVEL ) ;

	local nCount =0;
	local nFubenType = GetFubenData_Param(sceneId, x700023_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700023_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700023_g_ScriptId )
	
	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700023_g_ScriptId,nIndexFrom,i)
		if idScript == x700023_g_ScriptId and monsterFlag == 5 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x1 + rx
                local rz = random(-r,r)
                local z = z1 + rz
		        local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700023_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700023_g_ScriptId, -1, 21,-1,facedir)
				
				end
				SetPatrolId(sceneId, nRet, 0)
				SetFubenData_Param(sceneId, x700023_CSP_PATROL_MONSTER_START + nCount, nRet ) 
				if nCount ==0 then
					local nFullHp = GetHp( sceneId, nRet )
					SetFubenData_Param(sceneId,x700023_CSP_PATROL_MONSTER_FULL_HP, nFullHp ) 
				end
				nCount = nCount +1;
            end
        end
	end
	
	SetFubenData_Param(sceneId, x700023_CSP_PATROL_MONSTER_COUNT, nCount ) 

end

function x700023_CreateChangeMonster(sceneId, x, z)
	 local fubenlevel = GetFubenData_Param(sceneId, x700023_CSP_FUBENLEVEL ) ;
	local nFubenType = GetFubenData_Param(sceneId, x700023_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700023_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700023_g_ScriptId )
	
	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700023_g_ScriptId,nIndexFrom,i)
		if idScript == x700023_g_ScriptId and monsterFlag == 6 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
			if title~="" then
				CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,  "",title)
			else
				CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				
			end
			break
            
        end
	end

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = "一个小怪变身"
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end
end

function x700023_CreateMonster(sceneId)


    local fubenlevel = GetFubenData_Param(sceneId, x700023_CSP_FUBENLEVEL ) ;
	local nFubenType = GetFubenData_Param(sceneId, x700023_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700023_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700023_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700023_g_ScriptId,nIndexFrom,i)
		if idScript == x700023_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
				if title~="" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,  "",title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
									
				end
			end
        end
	end

end


function x700023_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700023_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700023_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;

	local objId1 = GetFubenData_Param(sceneId, x700023_CSP_BOSS1_ID )
	local objId2 = GetFubenData_Param(sceneId, x700023_CSP_BOSS2_ID ) ;
	if selfId ==objId1 then
		SetFubenData_Param(sceneId, x700023_CSP_BOSS1_ID,-1 )
	elseif selfId ==objId2 then
		SetFubenData_Param(sceneId, x700023_CSP_BOSS2_ID,-1 )
		x700023_CreateSubmitNpc( sceneId)

		--//--------------------------- 世界喊话 Start--------------------
			--杀死最终boss
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

	local objId3 = GetFubenData_Param(sceneId, x700023_CSP_BOSS3_ID ) ;
	
	local nBoss3Flag = GetFubenData_Param(sceneId, x700023_CSP_BOSS3_FLAG) ;
	if nBoss3Flag>0 then

		if objId3== selfId then
			SetFubenData_Param(sceneId, x700023_CSP_BOSS3_ID, -1 ) ;
			SetFubenData_Param(sceneId, x700023_CSP_BOSS3_FLAG, 0) ;
			if objId1>=0 then
				SendSpecificImpactToUnit(sceneId, objId1,objId1,objId1, x700023_g_BuffId,0 )
			end
		end
	end
	
	
	local nCurrentChildCount = GetFubenData_Param(sceneId, x700023_CSP_CHILD_COUNT ) ;
	

	for i=0, nCurrentChildCount-1 do
		local nChildObjId = GetFubenData_Param(sceneId, x700023_CSP_CHILD_ID_START+i )
		if nChildObjId==selfId then
			SetFubenData_Param(sceneId, x700023_CSP_CHILD_COUNT, nCurrentChildCount-1 ) ;
			for j=i,nCurrentChildCount-2 do
				local nNextObjId = GetFubenData_Param(sceneId, x700023_CSP_CHILD_ID_START+j+1 )
				SetFubenData_Param(sceneId, x700023_CSP_CHILD_ID_START+j,nNextObjId )
			end
			SetFubenData_Param(sceneId, x700023_CSP_CHILD_ID_START+nCurrentChildCount-1,-1 )
			break;
		end
	end


	local nCount = GetFubenData_Param(sceneId, x700023_CSP_PATROL_MONSTER_COUNT)
	

	for i=0, nCount-1 do
		local nObjId = GetFubenData_Param(sceneId, x700023_CSP_PATROL_MONSTER_START+i)
		
		if nObjId ==selfId then
			SetFubenData_Param(sceneId, x700023_CSP_PATROL_MONSTER_START+i,-1)
			x700023_ArrayDeleteByIndex(sceneId,x700023_CSP_PATROL_MONSTER_START,nCount,i)
			SetFubenData_Param(sceneId, x700023_CSP_PATROL_MONSTER_COUNT,nCount-1 )
		end
	end

	
	
	
end

function x700023_OnAllMonsterDead( sceneId)
	--x700023_CreateSubmitNpc( sceneId)
end

function x700023_CreateSubmitNpc( sceneId)

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = "副本完成，可以进入下一环了"
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end

	if x700023_g_SubmitNPC.title~="" then

		CreateMonster(sceneId, x700023_g_SubmitNPC.type, x700023_g_SubmitNPC.x, x700023_g_SubmitNPC.z, 3, 0, -1, x700023_g_SubmitNPC.guid, -1,-1,x700023_g_SubmitNPC.facedir,  "",x700023_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700023_g_SubmitNPC.type, x700023_g_SubmitNPC.x, x700023_g_SubmitNPC.z, 3, 0, -1, x700023_g_SubmitNPC.guid, -1,-1,x700023_g_SubmitNPC.facedir)
	
	end

	--// add for 现金副本
	 x700023_CreateXianJinBoss(sceneId)
	 --// add end

	 CallScriptFunction( 701101, "OnSceneBossDie", sceneId, 1)
	 CallScriptFunction( 701102, "OnSceneBossDie", sceneId, 1)
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

	if nFubenMode ==0 then
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
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
			end
			
		end
	end

	x700023_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end






