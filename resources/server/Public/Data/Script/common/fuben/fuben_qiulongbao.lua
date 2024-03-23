---------------------------------------------------
-- File: 700004_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700004_CSP_FUBENTYPE				= 	0
x700004_CSP_SCRIPTID				=	1
x700004_CSP_TICKCOUNT				= 	2
x700004_CSP_FROMSCENEID				= 	3
x700004_CSP_ISCLOSING				= 	4
x700004_CSP_LEAVECOUNTDOWN			= 	5
x700004_CSP_TEAMID					=	6
x700004_CSP_BACKSCENEX       		=   7
x700004_CSP_BACKSCENEZ      		=   8
x700004_CSP_FUBENLEVEL				=	9
x700004_CSP_AREA_FLAG				=	19
x700004_CSP_AREA_ID					=	20
x700004_CSP_SLEEPDRAGON_ID			=	21		--睡龙ID
x700004_CSP_DRAGON_ID				=	22		--龙ID




x700004_CSP_EFFIGY_ID1				=	32		--雕像ID
x700004_CSP_EFFIGY_ID2				=	33		--雕像ID
x700004_CSP_EFFIGY_ID3				=	34		--雕像ID
x700004_CSP_EFFIGY_ID4				=	35		--雕像ID
x700004_CSP_EFFIGY_ID5				=	36		--雕像ID
x700004_CSP_EFFIGY_ID6				=	37		--雕像ID

x700004_CSP_BOSS_ID					=	38		--雕像ID
x700004_CSP_PATROL_MONSTER_COUNT    =   40
x700004_CSP_DRAGONEGG_NUM			=	49    	--龙蛋个数
x700004_CSP_DRAGONEGG_STARTID		=	50		--龙ID
x700004_CSP_FUBEN_FINISH			=	100		--副本是否结束

x700004_CSP_DRAGONEGG_TICK			=	108		--prev create egg tick
x700004_CSP_DRAGONEGG_FLAG			=	109		--create 龙蛋 FLAG
x700004_CSP_EFFIGYDRAGON_FLAG1			=	110		--
x700004_CSP_EFFIGYDRAGON_FLAG2			=	111		--
x700004_CSP_EFFIGYDRAGON_FLAG3			=	112		--

x700004_RANDOM_BOSS_ID				=	233
x700004_RANDOMBOSS_FLAG				=	234
x700004_CSP_CREATE_EGG_FLAG			=	236

x700004_CSP_XIANJINBOSS				=	239


x700004_CSP_HUMAN_COUNT				=	240
x700004_CSP_OBJID_START				=	241

x700004_CSP_GUID_START              =   248  --空6个
x700004_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型

x700004_CSP_FUBEN_MODE				=   255 

------------------------Scene System Setting -----------------------------------

x700004_g_ScriptId 					= 700004
x700004_g_MissionId					= 6608

------------------------- special for fuben-------------------
x700004_g_OneTime_Child_Count		=	2                       --龙蛋每次刷出小龙数量
x700004_g_Max_Child_Count			=	20                      --龙蛋刷出的小龙同时存在的最大个数
x700004_g_BuffId					=	13503                   --龙蛋被打破后，小龙boss获得的buffid

x700004_g_RandomMonsterRate						= 0.1                       --隐藏boss出现几率
x700004_g_RandomMonsterRateZHOUSANFAN			= 67                      --隐藏boss出现几率 百分之几!


x700004_g_TimeDriverList			= {2,2,2,12,12,12,12,12,12,1}
-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------
--返回王城
function x700004_TeleportWangCheng(sceneId, selfId)
		local selfcountry =GetCurCountry( sceneId, selfId)
        TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
        TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
		if selfcountry == 0 then
        	NewWorld( sceneId, selfId, selfcountry * 100 + 50, 75 + random( 0, 5), 180 + random( 0, 5), x700004_g_ScriptId)
		elseif selfcountry ==1 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 75 + random( 0, 5), 180 + random( 0, 5), x700004_g_ScriptId)
		elseif selfcountry ==2 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 181 + random( 0, 5), 76 + random( 0, 5), x700004_g_ScriptId)
		elseif selfcountry ==3 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 181 + random( 0, 5), 76 + random( 0, 5), x700004_g_ScriptId)
		end
end
			

function x700004_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)
	if nFlag == 2 then
		x700004_TeleportWangCheng(sceneId, selfId)
	end
end


function x700004_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700004_ShowTipsToAll(sceneId, str)

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
function x700004_OnFubenSceneCreated( sceneId )

	SetFubenData_Param(sceneId, x700004_CSP_AREA_ID, 0 )
	
	SetFubenData_Param(sceneId, x700004_CSP_EFFIGY_ID1, -1 )
	SetFubenData_Param(sceneId, x700004_CSP_EFFIGY_ID2, -1 )
	SetFubenData_Param(sceneId, x700004_CSP_EFFIGY_ID3, -1 )
	SetFubenData_Param(sceneId, x700004_CSP_EFFIGY_ID4, -1 )
	SetFubenData_Param(sceneId, x700004_CSP_EFFIGY_ID5, -1 )
	SetFubenData_Param(sceneId, x700004_CSP_EFFIGY_ID6, -1 )
	SetFubenData_Param(sceneId, x700004_CSP_SLEEPDRAGON_ID, -1 )

	SetFubenData_Param(sceneId, x700004_CSP_BOSS_ID, -1 )
	
	SetFubenData_Param(sceneId, x700004_CSP_CREATE_EGG_FLAG, 0 )
	SetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_NUM, 0) 
	
	SetFubenData_Param(sceneId, x700004_CSP_EFFIGYDRAGON_FLAG1, 0) 
	SetFubenData_Param(sceneId, x700004_CSP_EFFIGYDRAGON_FLAG2, 0) 
	SetFubenData_Param(sceneId, x700004_CSP_EFFIGYDRAGON_FLAG3, 0) 
	
	SetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_FLAG, 0) 
	
	SetFubenData_Param(sceneId, x700004_CSP_XIANJINBOSS, -1 )
	
	for i = 0,x700004_g_Max_Child_Count-1 do
		SetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_STARTID + i, -1) 
	end			

	x700004_CreateMonster( sceneId )
	x700004_CreatePatrolMonster( sceneId )
	x700004_CreateEffigy(sceneId)
	x700004_CreateSleepDragonBoss(sceneId)
	x700004_CreateBoss( sceneId )
    
		
end



function x700004_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	--print("x700091_ProcAreaEntered"..zoneId.." "..MissionId)
	SetFubenData_Param(sceneId, x700004_CSP_AREA_ID, zoneId)
	--@param sceneId: 场景Id
	--@param selfId: 玩家ObjId (宠物进入EnterArea也会触发这个时间)
	--@param zoneId: 区域Id
	--@param MissionId: 任务id\
		--print("x700004_ProcAreaEntered=",zoneId)
	if zoneId == 1 then  --出口
	
		local BossId = GetFubenData_Param(sceneId, x700004_CSP_BOSS_ID )
		if BossId ~= -1 then
			return
		end
		SetFubenData_Param(sceneId, x700004_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, 0, x700004_g_MissionId, x700004_g_ScriptId, 1) --0为出口
		
	elseif zoneId == 2 then   --入口
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, 1, x700004_g_MissionId, x700004_g_ScriptId)
	elseif zoneId == 3 then   --龙产龙蛋
		SetFubenData_Param(sceneId, x700004_CSP_AREA_ID, 3 )
		
		if GetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_FLAG) ~= 2 then
			SetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_FLAG,1)
		end
	elseif zoneId == 4 then   --删掉雕像，创建两怪
		SetFubenData_Param(sceneId, x700004_CSP_AREA_ID, 4 )
		local flag = GetFubenData_Param(sceneId, x700004_CSP_EFFIGYDRAGON_FLAG1) 
		if flag == 1 then
			return
		end
		
		SetFubenData_Param(sceneId, x700004_CSP_EFFIGYDRAGON_FLAG1, 1) 
		x700004_CreateEffigyDragon(sceneId,12)
		--x700004_CreateEffigyDragon(sceneId,12)
	elseif zoneId == 5 then   --删掉雕像，创建两怪
		SetFubenData_Param(sceneId, x700004_CSP_AREA_ID, 5 )
		local flag = GetFubenData_Param(sceneId, x700004_CSP_EFFIGYDRAGON_FLAG2) 
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700004_CSP_EFFIGYDRAGON_FLAG2, 1) 
		x700004_CreateEffigyDragon(sceneId,13)
		--x700004_CreateEffigyDragon(sceneId,13)
	elseif zoneId == 6 then   --删掉雕像，创建两怪
		SetFubenData_Param(sceneId, x700004_CSP_AREA_ID, 6 )
		local flag = GetFubenData_Param(sceneId, x700004_CSP_EFFIGYDRAGON_FLAG3) 
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700004_CSP_EFFIGYDRAGON_FLAG3, 1) 
		x700004_CreateEffigyDragon(sceneId,14)
		--x700004_CreateEffigyDragon(sceneId)

	end
end	
---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700004_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )
	EnterAreaEventListHideNM(sceneId, selfId)
	--print("x700004_ProcAreaLeaved",zoneId)
	SetFubenData_Param(sceneId, x700004_CSP_AREA_ID, -1 )
--@param sceneId: 场景Id
--@param selfId: 玩家ObjId (宠物进入EnterArea也会触发这个时间)
--@param zoneId: 区域Id
--@param MissionId: 任务id
end

function x700004_EnterTick(sceneId, nowTickCount)
	--print("x700004_EnterTick",nowTickCount)
	local flag = GetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_FLAG)
	if flag == 1 then
	
		--x700004_CSP_DRAGONEGG_NUM			=	49    	--龙蛋个数
		--x700004_CSP_DRAGONEGG_STARTID		=	50		--龙ID
		local alldead = 1
		local num = GetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_NUM)
		--print("x700004_EnterTick111111111",nowTickCount,num)
		if num >= 10 then
			local sleepDragonId = GetFubenData_Param(sceneId, x700004_CSP_SLEEPDRAGON_ID)
			if sleepDragonId ~= -1 and sleepDragonId ~= -2 then
				SetFubenData_Param(sceneId, x700004_CSP_SLEEPDRAGON_ID, -2)
				DeleteMonster(sceneId,sleepDragonId)
				x700004_CreateDragonBoss(sceneId)
				SetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_FLAG,2)
			end
		end
		for i = 0,num-1 do
			local id = GetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_STARTID + i)
			if id ~= -1 and id ~= -2 then
				alldead = 0
				break
			end
		end
		
		local drageonId = GetFubenData_Param(sceneId, x700004_CSP_DRAGON_ID) 		
		if drageonId < 0 then
			return
		end
		if alldead == 1 then
			SetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_TICK, nowTickCount )
			x700004_CreateDragonEgg(sceneId)
		else
			local prevTick = GetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_TICK)
			if nowTickCount - prevTick >= 2 then		--tick
				x700004_CreateDragonEgg(sceneId)
				SetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_TICK, nowTickCount )
			end
		end
	end
	
	
	
end
---------------------------------------------------------------------------------------------------
--区域定时器
---------------------------------------------------------------------------------------------------
function x700004_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	local zoneId = GetFubenData_Param(sceneId, x700004_CSP_AREA_ID )
	if zoneId == 1 then  --出口
	
		local BossId = GetFubenData_Param(sceneId, x700004_CSP_BOSS_ID )
		if BossId ~= -1 then
			return
		end
		
		local flag = GetFubenData_Param(sceneId, x700004_CSP_AREA_FLAG)
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700004_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, 0, x700004_g_MissionId, x700004_g_ScriptId, 1) --0为出口
		
	elseif zoneId == 2 then   --入口
		--CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700004_g_MissionId, x700004_g_ScriptId)
	end
end


function x700004_CreateBoss(sceneId)  
	
	local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL ) ;

	local nFubenType = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		if idScript == x700004_g_ScriptId and monsterFlag == 7 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir)
				
			end
			SetFubenData_Param(sceneId, x700004_CSP_BOSS_ID  , nRet ) 
			
        end
	end

end

function x700004_CreateEffigy(sceneId)    --雕像


	local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL ) ;

	local nFubenType = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		if idScript == x700004_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, camp,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, camp,-1,facedir)
			end
			
			--print("x700004_CreateEffigy", nRet)
			for j = 0,6-1 do
				local eff = GetFubenData_Param(sceneId, x700004_CSP_EFFIGY_ID1 + j  ) 
				
				if eff == -1 then
					--print("x700004_CreateEffigy J",j,nRet)
					SetFubenData_Param(sceneId, x700004_CSP_EFFIGY_ID1 + j , nRet ) 
					break
				end
			end
		end
	end

end

---------------------------------------------------------------------------------------------------
--创建BOSS2
---------------------------------------------------------------------------------------------------
function x700004_CreateSleepDragonBoss(sceneId)   --睡龙
	local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		if idScript == x700004_g_ScriptId and monsterFlag == 5 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, camp,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, camp,-1,facedir)
			
			end
			SetFubenData_Param(sceneId, x700004_CSP_SLEEPDRAGON_ID, nRet ) ;
		
			return
		
        end
	end
end
function x700004_CreateDragonBoss(sceneId)   

	local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		if idScript == x700004_g_ScriptId and monsterFlag == 6 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir)
			
			end
			SetFubenData_Param(sceneId, x700004_CSP_DRAGON_ID, nRet ) ;
		
			return
		
        end
	end
end
function x700004_CreateLittleDragon(sceneId, nflag)   --小龙，每次两个
	if flag == nil then
		flag = 3
	end
	--print("x700004_CreateLittleDragon",nflag)
	--SetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_FLAG, 1 )
	local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		--if idScript == x700004_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		if idScript == x700004_g_ScriptId and monsterFlag == nflag and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
			--print("======================",flag,levelmin,levelmax)
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir)
			
			end
			--print("x700004_CreateLittleDragon--",nRet)
			--return
		end
	end


end
function x700004_CreateDragonEgg(sceneId)   --龙蛋  --每次一个


	local EggPosTab = {
					 	{ x = 66.4123, z= 69.5},
 						{ x = 68.4852, z= 69.5},
 						{ x = 70.4854, z= 69.5},
 						{ x = 72.5395, z= 69.5},
 						{ x = 74.5973, z= 69.5},
					}
	local ranIndex = random(1,5)
	local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )
	local index = 0
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		if idScript == x700004_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
		    --x = EggPosTab[ranIndex].x
		    --z = EggPosTab[ranIndex].z
		   
			
			local eggNum = GetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_NUM ) 
			
			if index == eggNum then
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir)
				end
				
				SetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_STARTID + eggNum, nRet ) 
				eggNum = eggNum + 1
				SetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_NUM, eggNum) 
				return
			end
			index = index + 1
			
		
        end
	end


end
---------------------------------------------------------------------------------------------------
--创建Monster


function x700004_CreateEffigyDragon(sceneId,flag)  --删除雕像，创建小龙

	local nStart = GetFubenData_Param(sceneId, x700004_CSP_EFFIGY_ID1)
	local nID = 0
	local index = 0
	for i=0, 6 - 1 do
		nID = GetFubenData_Param(sceneId, x700004_CSP_EFFIGY_ID1 + i)
		if nID ~= -1 then
			index = i
			break
		end
	end
	
	--local index = i
	if nID ~= -1 then
		
		DeleteMonster(sceneId, nID)
		SetFubenData_Param(sceneId, x700004_CSP_EFFIGY_ID1 + index, -1)
		
		local nID2 = GetFubenData_Param(sceneId, x700004_CSP_EFFIGY_ID1 + index + 1)
		DeleteMonster(sceneId, nID2)
		SetFubenData_Param(sceneId, x700004_CSP_EFFIGY_ID1 + index + 1, -1)
		
		x700004_CreateLittleDragon(sceneId,flag)
		
		--print("index",index,flag,nID,nID2)
	end
end

---------------------------------------------------------------------------------------------------
function x700004_GetDragonEggID(sceneId)  --龙蛋创建小怪
	local eggNum = GetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_NUM ) 
	local nStart = GetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_STARTID)
	local nID = 0
	for i=0, eggNum - 1 do
		nID = GetFubenData_Param(sceneId, x700004_CSP_DRAGONEGG_STARTID + i)
		if nID ~= -1 then
			return x700004_CSP_DRAGONEGG_STARTID + i
		end
	end
	return 0
end

--function x700004_CreateEggDragon(sceneId)  --删除龙蛋，创建小龙
--	print("x700004_CreateEggDragon")
--	local startId = x700004_GetDragonEggID(sceneId)
--	if startId == -1 then
--		return
--	end
--	
--	--删除龙蛋
--	SetFubenData_Param(sceneId, startId, -1)
--	local MonId = GetFubenData_Param(sceneId, startId)
--	DeleteMonster(sceneId, MonId)
--
--	x700004_CreateLittleDragon(sceneId)
--end

---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700004_CreatePatrolMonster(sceneId)
	--print("x700004_CreatePatrolMonster")
	local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL ) ;

	local nCount =0;
	local nFubenType = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )
	
	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		if idScript == x700004_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x1 + rx
                local rz = random(-r,r)
                local z = z1 + rz
		        local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir)
				
				end
				SetPatrolId(sceneId, nRet, flag2)
				
            end
        end
	end
	
	SetFubenData_Param(sceneId, x700004_CSP_PATROL_MONSTER_COUNT, nCount ) 

end
--print("ttttttttttttttt")
function x700004_CreateMonster(sceneId)

	--print("x700004_CreateMonster")
    local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL ) ;
	local nFubenType = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )

	--print("nDataCount kkkkkkkkkkkkk",nDataCount,nFubenType,fubenlevel)
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		if idScript == x700004_g_ScriptId then
			--print("=====================================================",idScript,monsterFlag,fubenlevel,flag3,count,nFubenType)
		end
		if idScript == x700004_g_ScriptId  and monsterFlag == 0  and nFubenType == flag3 then
			--print("sssssssssssss",idScript,monsterFlag,fubenlevel,flag3,count,nFubenType)
		end
		if idScript == x700004_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
			--print("aaaaaaaaaa",idScript,monsterFlag,fubenlevel,flag3,count,nFubenType)
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
				if title~="" then
					CreateMonster(sceneId, type, x, z, 9, aiscript, -1, -1, 21,-1,facedir,  "",title)
				else
					CreateMonster(sceneId, type, x, z, 9, aiscript, -1, -1, 21,-1,facedir)
									
				end
				
				--print("x700004_CreateMonster--------------------------")
			end
        end
	end

end


function x700004_CreateRandomMonster(sceneId)
	local nFubenType = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end

	local rate = random(0,100)/100;
	local nStdRate = x700004_g_RandomMonsterRate
	local nFubenMode = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_MODE)
	if nFubenMode ==1 then
		nStdRate = nStdRate*3
	end
	
	if(nFubenMode ~= 2) then
		if rate>= nStdRate then
			return 0;
		end
	else			--ZHOUSANFAN --Jerry Huang
		rate = random(1,100)
		if(rate > x700004_g_RandomMonsterRateZHOUSANFAN) then
			return 0;
		end
	end

	local nFlag = random(0,3)

	

	local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL ) ;
	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		--if flag == nFlag then
		
		
			if idScript == x700004_g_ScriptId and monsterFlag == 8+nFlag and levelmin <= fubenlevel and levelmax >= fubenlevel  and flag3 == nFubenType then
				local nBossID =0;
				if title~="" then
					nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir)
				
				end
				--print("Random BossID",nBossID, title)
				SetFubenData_Param(sceneId, x700004_RANDOMBOSS_FLAG, nFlag)
				SetFubenData_Param(sceneId, x700004_RANDOM_BOSS_ID, nBossID)
			end
		--end
	end

	x700004_ShowTipsToAll(sceneId, "战神再现！")

end

function x700004_OnFubenEnd( sceneId)
	x700004_CreateXianJinBoss(sceneId)
	x700004_CreateRandomMonster(sceneId)
	CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnFubuenCompleted", sceneId)
	local humancount = GetFuben_PlayerCount(sceneId);
	for ii = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, ii);
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,52 )
	end	
	x700004_ShowTipsToAll(sceneId, "战胜三头凶蛟，副本完成，请退出副本。")
end

function x700004_OnDie(sceneId, selfId, killerId)


	local drageonId = GetFubenData_Param(sceneId, x700004_CSP_DRAGON_ID) 
	if drageonId == selfId then
		SetFubenData_Param(sceneId, x700004_CSP_DRAGON_ID, -2) 
	end


	for i = x700004_CSP_DRAGONEGG_STARTID,x700004_CSP_DRAGONEGG_STARTID+x700004_CSP_DRAGONEGG_NUM do
		local eggId = GetFubenData_Param(sceneId, i)
		if eggId == selfId then
			SetFubenData_Param(sceneId, i, -2)
		end
	end
	
	
	local xianjinboss = GetFubenData_Param(sceneId, x700004_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	
	local nMonId = GetFubenData_Param(sceneId, x700004_CSP_BOSS_ID)
	if nMonId == selfId then
		SetFubenData_Param(sceneId, x700004_CSP_BOSS_ID, -1)
		x700004_OnFubenEnd( sceneId)
	end
	
	
	local nRandomBossId = GetFubenData_Param(sceneId, x700004_RANDOM_BOSS_ID)

	if nRandomBossId >= 0 then
		if nRandomBossId==selfId then
			--//--------------------------- 世界喊话 Start--------------------
			--杀死Random boss
			
			
			-------- if killed by pet -----------------
			local nKillerType = GetObjType(sceneId, killerId)
			local nOwnerId = killerId
			if nKillerType== 3 then
				nOwnerId = GetOwnerID(sceneId, killerId)
				
			end
			--------- end -------------------------------
			local strPlayerName = GetName(sceneId, nOwnerId)
			
			local nCountry = GetCurCountry( sceneId, nOwnerId )
			local strCountryName = "";
			if nCountry==0 then
				strCountryName = "楼兰"
			elseif nCountry==1 then
				strCountryName = "天山"
			elseif nCountry==2 then
				strCountryName = "昆仑"
			elseif nCountry==3 then
				strCountryName = "敦煌"
			end

			local strHorseName = ""

			local nHorseFlag = GetFubenData_Param(sceneId, x700004_RANDOMBOSS_FLAG);
			local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL )
			
			if fubenlevel < 50 then
				if nHorseFlag==0 then
					strHorseName = "凶豹"
				elseif nHorseFlag==1 then
					strHorseName = "奔羚"
				elseif nHorseFlag==2 then
					strHorseName = "天鹅"
				elseif nHorseFlag==3 then
					strHorseName = "河马"
				end
			elseif fubenlevel < 70 then
				if nHorseFlag==0 then
					strHorseName = "烈狮"
				elseif nHorseFlag==1 then
					strHorseName = "驯鹿"
				elseif nHorseFlag==2 then
					strHorseName = "瑞鹤"
				elseif nHorseFlag==3 then
					strHorseName = "铁犀"
				end
			elseif fubenlevel < 80 then
				if nHorseFlag==0 then
					strHorseName = "剑齿虎"
				elseif nHorseFlag==1 then
					strHorseName = "蛮牛"
				elseif nHorseFlag==2 then
					strHorseName = "凤凰"
				elseif nHorseFlag==3 then
					strHorseName = "猛犸"
				end
			elseif fubenlevel < 95 then
				if nHorseFlag==0 then
					strHorseName = "虬龙"
				elseif nHorseFlag==1 then
					strHorseName = "应龙"
				elseif nHorseFlag==2 then
					strHorseName = "暴龙"
				elseif nHorseFlag==3 then
				strHorseName = "奎龙"
				end
			elseif fubenlevel < 130 then
				if nHorseFlag==0 then
					strHorseName = "狻猊"
				elseif nHorseFlag==1 then
					strHorseName = "毕方"
				elseif nHorseFlag==2 then
					strHorseName = "梼杌"
				elseif nHorseFlag==3 then
					strHorseName = "饕餮"
				end
			else
				if nHorseFlag==0 then
					strHorseName = "狻猊"
				elseif nHorseFlag==1 then
					strHorseName = "毕方"
				elseif nHorseFlag==2 then
					strHorseName = "梼杌"
				elseif nHorseFlag==3 then
					strHorseName = "饕餮"
				end
			end



			local strMapName = "囚龙堡"
			
			LuaAllScenceM2Wrold (sceneId,strCountryName.."的"..strPlayerName.."打败了"..strMapName.."的九旄战神，九旄丢下"..strHorseName.."落荒而逃！", 5, 1)
			
			
			--//--------------------------- 世界喊话 end----------------------
		end
	end

	
	
	
end

----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700004_CreateXianJinBoss(sceneId)

	local nFubenType = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_MODE)

	if nFubenMode ==0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )
	
	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		if idScript == x700004_g_ScriptId and monsterFlag == 20 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700004_CSP_XIANJINBOSS, nRet )
		end
	end

	x700004_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end






