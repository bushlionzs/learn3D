---------------------------------------------------
-- File: 700024_fuben_HUDI_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700024_CSP_FUBENTYPE				= 	0
x700024_CSP_SCRIPTID				=	1
x700024_CSP_TICKCOUNT				= 	2
x700024_CSP_FROMSCENEID				= 	3
x700024_CSP_ISCLOSING				= 	4
x700024_CSP_LEAVECOUNTDOWN			= 	5
x700024_CSP_TEAMID					=	6
x700024_CSP_BACKSCENEX       		=   7
x700024_CSP_BACKSCENEZ      		=   8
x700024_CSP_FUBENLEVEL				=	9
x700024_CSP_AREA_FLAG				=	19
x700024_CSP_AREA_ID					=	20
x700024_CSP_BOSS_ID					=   21
x700024_CSP_BOSS1_ID				=   22
x700024_CSP_BOSS2_ID				=   23


x700024_CSP_FUBEN_SCENE_ID			=	24


x700024_CSP_GUTMONSTER1_ID			=	25
x700024_CSP_GUTMONSTER2_ID			=	26

x700024_CSP_GUTMONSTER1_TALK		=	28
x700024_CSP_GUTMONSTER2_TALK		=	29

x700024_CSP_XIAOBIN_COUNT			=	39
x700024_CSP_XIAOBIN_LEAVECOUNT		=	40
x700024_CSP_XIAOBIN_ID_START		=	41		--8只
x700024_CSP_XIAOBIN2_COUNT			=	99
x700024_CSP_XIAOBIN2_LEAVECOUNT		=	100
x700024_CSP_XIAOBIN2_ID_START		=	101		--6只

x700024_CSP_BOSS1_FLAG				=	200
x700024_CSP_BOSS2_FLAG				=	201

x700024_CSP_XIANJINBOSS				=	239

x700024_CSP_HUMAN_COUNT				=	240
x700024_CSP_OBJID_START				=	241

x700024_CSP_GUID_START              =   248  --空6个
x700024_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型
x700024_CSP_FUBEN_MODE				=   255 



------------------------Scene System Setting -----------------------------------

x700024_g_ScriptId 					= 700024
x700024_g_MissionId					= 6608

x700024_g_SubmitNPC                 =   { type =25007,guid= 150507,x = 54, z=71, facedir =0, title="" }


										
x700024_g_Shark_FinalX					=	55
x700024_g_Shark_FinalZ					=	60







-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700024_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)
end


function x700024_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	SetFubenData_Param(sceneId, x700024_CSP_AREA_ID, zoneId)
	--@param sceneId: 场景Id
	--@param selfId: 玩家ObjId (宠物进入EnterArea也会触发这个时间)
	--@param zoneId: 区域Id
	--@param MissionId: 任务id\
	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700024_CSP_BOSS_ID)
		if BossId ~= -2 then
			return --TEST
		end
		SetFubenData_Param(sceneId, x700024_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700024_g_MissionId, x700024_g_ScriptId)

	elseif zoneId == 1 then
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700024_g_MissionId, x700024_g_ScriptId)
	elseif zoneId == 2 then
		local monId = GetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER2_ID) 
		if monId == -1 then
			x700024_CreateGutMonster2(sceneId)
		end
	elseif zoneId == 3 then
		local monId = GetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER1_ID) 
		if monId == -1 then
			x700024_CreateGutMonster1(sceneId)
		end
	end

end	
---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700024_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )
	EnterAreaEventListHideNM(sceneId, selfId)
	SetFubenData_Param(sceneId, x700024_CSP_AREA_ID, -1)
	--print("x700024_ProcAreaLeaved"..zoneId)
--@param sceneId: 场景Id
--@param selfId: 玩家ObjId (宠物进入EnterArea也会触发这个时间)
--@param zoneId: 区域Id
--@param MissionId: 任务id

	
end


---------------------------------------------------------------------------------------------------
--区域定时器
---------------------------------------------------------------------------------------------------
function x700024_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	local zoneId = GetFubenData_Param(sceneId, x700024_CSP_AREA_ID )
	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700024_CSP_BOSS_ID)
		if BossId ~= -2 then
			return --TEST
		end
		local flag = GetFubenData_Param(sceneId, x700024_CSP_AREA_FLAG)
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700024_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700024_g_MissionId, x700024_g_ScriptId)

	elseif zoneId == 1 then
		--CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700024_g_MissionId, x700024_g_ScriptId)
	end
end
--//add end


function x700024_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700024_ShowTipsToAll(sceneId, str)

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
function x700024_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	SetFubenData_Param(sceneId, x700024_CSP_XIAOBIN_COUNT, -1 ) 
	SetFubenData_Param(sceneId, x700024_CSP_XIAOBIN_ID_START, -1 ) 
	SetFubenData_Param(sceneId, x700024_CSP_XIAOBIN2_COUNT, -1 ) 
	SetFubenData_Param(sceneId, x700024_CSP_XIAOBIN2_ID_START, -1 ) 

	SetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER1_ID, -1 ) 
	SetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER2_ID, -1 ) 
	
	SetFubenData_Param(sceneId, x700024_CSP_BOSS1_ID, -1 ) 
	SetFubenData_Param(sceneId, x700024_CSP_BOSS2_ID, -1 ) 
	SetFubenData_Param(sceneId, x700024_CSP_BOSS_ID, -1 ) 
	
	SetFubenData_Param(sceneId, x700024_CSP_XIANJINBOSS, -1 )
	
	SetFubenData_Param(sceneId, x700024_CSP_BOSS1_FLAG, 0 ) 
	SetFubenData_Param(sceneId, x700024_CSP_BOSS2_FLAG, 0 ) 
	
	SetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER1_TALK, 0 ) 
	SetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER2_TALK, 0 ) 

	--x700024_ShowTipsToAll(sceneId, "副本说明")
	
   	x700024_CreateMonster( sceneId )
   	x700024_CreateMonster1( sceneId )
   	x700024_CreateMonster2( sceneId )

end

function x700024_EnterTick(sceneId, nowTickCount)
	
	
	local xiaobinCount = GetFubenData_Param(sceneId, x700024_CSP_XIAOBIN_LEAVECOUNT ) 
	local flag1 = GetFubenData_Param(sceneId, x700024_CSP_BOSS1_FLAG ) 
	local bossId1 = GetFubenData_Param(sceneId, x700024_CSP_BOSS1_ID ) 
	local nGutId1 = GetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER1_ID ) 
	
	local talk1 = GetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER1_TALK) 
	if nGutId1 >= 0 and talk1 == 0 then
		NpcTalk(sceneId, nGutId1, "要速去通报张士诚将军，有人前来阻挠我们夺取玉玺。",  -1)
		SetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER1_TALK, 1) 
	end
	
	if nGutId1 >= 0 and bossId1 == -1 then
		
		local x,z = GetWorldPos(sceneId,nGutId1)
		if flag1 == 0 then
			
			if z <= 155 then
				if xiaobinCount == 0 then
					
					SetMonsterCamp(sceneId,nGutId1,21)
					--print("SetCurCamp",z,ret)
					--SetFubenData_Param(sceneId, x700024_CSP_BOSS1_ID, -2 ) --不需要再创建此BOSS
				else
					SetFubenData_Param(sceneId, x700024_CSP_BOSS1_FLAG, 1 ) --不需要再创建此BOSS
				end
			else
				if xiaobinCount == 0 then
					SetMonsterCamp(sceneId,nGutId1,21)
				end
			end
		else
			if z <= 60 then
				DeleteMonster(sceneId,nGutId1)
				SetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER1_ID, -2) 
				x700024_CreateBoss1(sceneId)
			end
		end
	end
	
	

	local xiaobin2Count = GetFubenData_Param(sceneId, x700024_CSP_XIAOBIN2_LEAVECOUNT ) 
	
	--print("x700024_EnterTick",nowTickCount,xiaobinCount,xiaobin2Count)
	local flag2 = GetFubenData_Param(sceneId, x700024_CSP_BOSS2_FLAG ) 
	local bossId2 = GetFubenData_Param(sceneId, x700024_CSP_BOSS2_ID ) 
	local nGutId2 = GetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER2_ID ) 
	
	local talk2 = GetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER2_TALK, 0 ) 
	if nGutId2 >= 0 and talk2 == 0 then
		NpcTalk(sceneId, nGutId2, "要速去通报张士诚将军，有人前来阻挠我们夺取玉玺。",  -1)
		SetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER2_TALK, 1) 
	end
	
	
	if nGutId2 >= 0 and bossId2 == -1 then
		local x,z = GetWorldPos(sceneId,nGutId2)
		if flag2 == 0 then
			if z <= 78 then
				if xiaobin2Count == 0 then
					SetMonsterCamp(sceneId,nGutId2,21)
					--SetFubenData_Param(sceneId, x700024_CSP_BOSS2_ID, -2 ) --不需要再创建此BOSS
				else
					SetFubenData_Param(sceneId, x700024_CSP_BOSS2_FLAG, 1 ) --不需要再创建此BOSS
				end
			else
				if xiaobin2Count == 0 then
					SetMonsterCamp(sceneId,nGutId2,21)
				end
			end
		else
			if z <= 60 then
				DeleteMonster(sceneId,nGutId2)
				SetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER2_ID, -2 ) 
				x700024_CreateBoss2(sceneId)
			end
		end
	end
	

            
	
end
function x700024_CreateGutMonster1(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700024_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700024_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700024_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700024_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700024_g_ScriptId,nIndexFrom,i)
		if idScript == x700024_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
		    --20号阵营，不攻击
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 20,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 20,-1,facedir)
			
			end
			SetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER1_ID, nRet ) ;
			SetPatrolId(sceneId, nRet, 0)
			--NpcTalk(sceneId, nRet, "要速去通报张士诚将军，有人前来阻挠我们夺取玉玺。",  -1)
			return
        end
	end

end
function x700024_CreateGutMonster2(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700024_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700024_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700024_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700024_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700024_g_ScriptId,nIndexFrom,i)
		if idScript == x700024_g_ScriptId and monsterFlag == 5 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
		    --20号阵营，不攻击
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 20,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 20,-1,facedir)
			
			end
			SetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER2_ID, nRet ) ;
			SetPatrolId(sceneId, nRet, 1)
			--NpcTalk(sceneId, nRet, "要速去通报张士诚将军，有人前来阻挠我们夺取玉玺。",  -1)
			return
        end
	end

end
function x700024_CreateBoss(sceneId)
	local fubenlevel = GetFubenData_Param(sceneId, x700024_CSP_FUBENLEVEL )

	local nFubenType = GetFubenData_Param(sceneId, x700024_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700024_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700024_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700024_g_ScriptId,nIndexFrom,i)
		if idScript == x700024_g_ScriptId and monsterFlag == 8 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1,facedir)
			
			end
			SetFubenData_Param(sceneId, x700024_CSP_BOSS_ID, nRet )
		end
	end

end

function x700024_CreateBoss1(sceneId)

	local fubenlevel = GetFubenData_Param(sceneId, x700024_CSP_FUBENLEVEL )

	local nFubenType = GetFubenData_Param(sceneId, x700024_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700024_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700024_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700024_g_ScriptId,nIndexFrom,i)
		if idScript == x700024_g_ScriptId and monsterFlag == 6 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1,facedir)
			
			end
			SetFubenData_Param(sceneId, x700024_CSP_BOSS1_ID, nRet )
			
        end
	end

end
function x700024_CreateBoss2(sceneId)
	local fubenlevel = GetFubenData_Param(sceneId, x700024_CSP_FUBENLEVEL )

	local nFubenType = GetFubenData_Param(sceneId, x700024_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700024_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700024_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700024_g_ScriptId,nIndexFrom,i)
		if idScript == x700024_g_ScriptId and monsterFlag == 7 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1,facedir)
			
			end
			SetFubenData_Param(sceneId, x700024_CSP_BOSS2_ID, nRet )
			--SetPatrolId(sceneId, nRet, 1)
        end
	end

end
---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700024_CreateMonster(sceneId) --创建小怪


    local fubenlevel = GetFubenData_Param(sceneId, x700024_CSP_FUBENLEVEL ) ;

	local nCount = 0
	local nFubenType = GetFubenData_Param(sceneId, x700024_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700024_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700024_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700024_g_ScriptId,nIndexFrom,i)
		if idScript == x700024_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
		        local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1, facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1, facedir)
				
				end
				
            end
        end
	end



end


---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700024_CreateMonster1(sceneId) --触发小兵1


    local fubenlevel = GetFubenData_Param(sceneId, x700024_CSP_FUBENLEVEL ) ;

	local nCount = 0
	local nFubenType = GetFubenData_Param(sceneId, x700024_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700024_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700024_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700024_g_ScriptId,nIndexFrom,i)
		if idScript == x700024_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
		        local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1, facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1, facedir)
				
				end
				SetFubenData_Param(sceneId, x700024_CSP_XIAOBIN_ID_START+nCount, nRet ) ;
				nCount = nCount+1
            end
        end
	end
	SetFubenData_Param(sceneId, x700024_CSP_XIAOBIN_COUNT, nCount ) 
	SetFubenData_Param(sceneId, x700024_CSP_XIAOBIN_LEAVECOUNT, nCount ) 
	--SetFubenData_Param(sceneId, x700024_CSP_MONSTER_KILL_COUNT, 0 )

end

---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700024_CreateMonster2(sceneId) --触发小兵2


    local fubenlevel = GetFubenData_Param(sceneId, x700024_CSP_FUBENLEVEL ) ;

	local nCount = 0
	local nFubenType = GetFubenData_Param(sceneId, x700024_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700024_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700024_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700024_g_ScriptId,nIndexFrom,i)
		if idScript == x700024_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
		        local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1, facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1, facedir)
				
				end
				SetFubenData_Param(sceneId, x700024_CSP_XIAOBIN2_ID_START+nCount, nRet ) ;
				nCount = nCount+1
            end
        end
	end
	SetFubenData_Param(sceneId, x700024_CSP_XIAOBIN2_LEAVECOUNT, nCount ) ;
	SetFubenData_Param(sceneId, x700024_CSP_XIAOBIN2_COUNT, nCount ) 
	--SetFubenData_Param(sceneId, x700024_CSP_MONSTER_KILL_COUNT, 0 )

end


function x700024_OnDie(sceneId, selfId, killerId)
	local xianjinboss = GetFubenData_Param(sceneId, x700024_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	local nXiaobinCount = GetFubenData_Param(sceneId, x700024_CSP_XIAOBIN_COUNT ) ;
	local nLeaveXiaobinCount = GetFubenData_Param(sceneId, x700024_CSP_XIAOBIN_LEAVECOUNT ) ;
	for i=0, nXiaobinCount-1 do
		local nObjMonsterId = GetFubenData_Param(sceneId, x700024_CSP_XIAOBIN_ID_START+i );
		if nObjMonsterId>=0 then
			if nObjMonsterId== selfId then
				SetFubenData_Param(sceneId, x700024_CSP_XIAOBIN_ID_START+i, -1 );
				nLeaveXiaobinCount = nLeaveXiaobinCount - 1
				SetFubenData_Param(sceneId, x700024_CSP_XIAOBIN_LEAVECOUNT, nLeaveXiaobinCount )
				break
			end
		end
	end

	local nXiaobin2Count = GetFubenData_Param(sceneId, x700024_CSP_XIAOBIN2_COUNT ) ;
	local nLeaveXiaobin2Count = GetFubenData_Param(sceneId, x700024_CSP_XIAOBIN2_LEAVECOUNT ) ;
	for i=0, nXiaobin2Count-1 do
		local nObjMonsterId = GetFubenData_Param(sceneId, x700024_CSP_XIAOBIN2_ID_START+i );
		if nObjMonsterId>=0 then
			if nObjMonsterId== selfId then
				SetFubenData_Param(sceneId, x700024_CSP_XIAOBIN2_ID_START+i, -1 );
				nLeaveXiaobin2Count = nLeaveXiaobin2Count - 1
				SetFubenData_Param(sceneId, x700024_CSP_XIAOBIN2_LEAVECOUNT, nLeaveXiaobin2Count )
				break
			end
		end
	end

	local bossId1 = GetFubenData_Param(sceneId, x700024_CSP_BOSS1_ID )
	local bossId2 = GetFubenData_Param(sceneId, x700024_CSP_BOSS2_ID )
	local bossId = GetFubenData_Param(sceneId, x700024_CSP_BOSS_ID )
	local gut1 = GetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER1_ID )
	local gut2 = GetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER2_ID )
	if bossId1 == selfId then
		SetFubenData_Param(sceneId, x700024_CSP_BOSS1_ID, -2 )
		if bossId2 == -1 and gut2 == -2 then
			x700024_CreateBoss(sceneId)
		end
	elseif bossId2 == selfId then
		SetFubenData_Param(sceneId, x700024_CSP_BOSS2_ID, -2 )
		if bossId1 == -1 and gut1 == -2 then
			x700024_CreateBoss(sceneId)
		end
	elseif gut1 == selfId then
		SetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER1_ID, -2 )
		if bossId2 == -2 then
			x700024_CreateBoss(sceneId)
		end
	elseif gut2 == selfId then
		SetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER2_ID, -2 )
		if bossId1 == -2 then
			x700024_CreateBoss(sceneId)
		end
	end
	
	bossId = GetFubenData_Param(sceneId, x700024_CSP_BOSS_ID )
	bossId1 = GetFubenData_Param(sceneId, x700024_CSP_BOSS1_ID )
	bossId2 = GetFubenData_Param(sceneId, x700024_CSP_BOSS2_ID )
	if bossId1 == -2 and bossId2 == -2 and bossId == -1 then
		x700024_CreateBoss(sceneId)
	end
	
	bossId1 = GetFubenData_Param(sceneId, x700024_CSP_BOSS1_ID )
	bossId2 = GetFubenData_Param(sceneId, x700024_CSP_BOSS2_ID )
	bossId = GetFubenData_Param(sceneId, x700024_CSP_BOSS_ID )
	gut1 = GetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER1_ID )
	gut2 = GetFubenData_Param(sceneId, x700024_CSP_GUTMONSTER2_ID )
	
	if gut1 == -2 and gut2 == -2 and bossId1 == -1 and bossId2 == -1 and bossId == -1 then
		x700024_CreateBoss(sceneId)
	end
	
	
	if bossId == selfId then
		SetFubenData_Param(sceneId, x700024_CSP_BOSS_ID, -2 )
		x700024_ShowTipsToAll(sceneId, "成功击杀盐帮帮主张士诚，副本完成。")
		x700024_OnFubenEnd( sceneId)
	end

end

function x700024_OnFubenEnd( sceneId)
	--x700024_CreateSubmitNpc( sceneId)
	--// add for 现金副本
	x700024_CreateXianJinBoss(sceneId)
	
	local humancount = GetFuben_PlayerCount(sceneId);
	for ii = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, ii);
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,56 )
	end	
end

function x700024_CreateSubmitNpc( sceneId)
	if x700024_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700024_g_SubmitNPC.type, x700024_g_SubmitNPC.x, x700024_g_SubmitNPC.z, 3, 0, -1, x700024_g_SubmitNPC.guid, -1,-1,x700024_g_SubmitNPC.facedir,  "",x700024_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700024_g_SubmitNPC.type, x700024_g_SubmitNPC.x, x700024_g_SubmitNPC.z, 3, 0, -1, x700024_g_SubmitNPC.guid, -1,-1,x700024_g_SubmitNPC.facedir)
	
	end
	 --// add end

	 CallScriptFunction( 701107, "OnSceneBossDie", sceneId, 0)

	 local bKillShark = GetFubenData_Param(sceneId, x700024_CSP_B_KILL_SHARK);

	 if bKillShark<=0 then
		CallScriptFunction( 701108, "OnSceneBossDie", sceneId, 0)
	 end
end

----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700024_CreateXianJinBoss(sceneId)
	local nFubenType = GetFubenData_Param(sceneId, x700024_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700024_CSP_FUBEN_MODE)

	if nFubenMode ==0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700024_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700024_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700024_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700024_g_ScriptId,nIndexFrom,i)
		if idScript == x700024_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700024_CSP_XIANJINBOSS, nRet )
		end
	end

	x700024_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end

