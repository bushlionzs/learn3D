---------------------------------------------------
-- File: 新囚龙岛第一环
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
x700028_CSP_FUBENLEVEL				=	9

x700028_CSP_KILLCOUNT				=	20
x700028_CSP_FUBEN_SCENE_ID			=	21


x700028_CSP_CURRENTSTEP				=	23
x700028_CSP_CURRENTSTEP_TICKCOUNT	=	24
x700028_CSP_MONSTER_COUNT			=	25
x700028_CSP_BOSS_ID					=	26

x700028_CSP_AREA_ID					=	28
x700028_CSP_AREA_FLAG				=	29


x700028_CSP_XIANJINBOSS				=	239


x700028_CSP_HUMAN_COUNT				=	240
x700028_CSP_OBJID_START				=	241
x700028_CSP_NEXT_SCENE				=   247
x700028_CSP_GUID_START              =   248
x700028_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型
x700028_CSP_FUBEN_MODE				=   255 
------------------------Scene System Setting -----------------------------------

x700028_g_ScriptId 					= 700028 
x700028_g_MissionId					= 6608
---------------------------- special for fuben -----------------------------

x700028_g_TimeIntervalTab 			= {1,30,30,30,36,36,36}   --最后一个为BOSS
	

--返回王城
function x700028_TeleportWangCheng(sceneId, selfId)
		local selfcountry =GetCurCountry( sceneId, selfId)
        TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
        TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
		if selfcountry == 0 then
        	NewWorld( sceneId, selfId, selfcountry * 100 + 50, 75 + random( 0, 5), 180 + random( 0, 5), x700028_g_ScriptId)
		elseif selfcountry ==1 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 75 + random( 0, 5), 180 + random( 0, 5), x700028_g_ScriptId)
		elseif selfcountry ==2 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 181 + random( 0, 5), 76 + random( 0, 5), x700028_g_ScriptId)
		elseif selfcountry ==3 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 181 + random( 0, 5), 76 + random( 0, 5), x700028_g_ScriptId)
		end
end
-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700028_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

	
end

-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700028_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	--print("x700028_OnFubenSceneCreated")

	SetFubenData_Param(sceneId, x700028_CSP_CURRENTSTEP, 1)
	SetFubenData_Param( sceneId, x700028_CSP_BOSS_ID, -2)
	SetFubenData_Param( sceneId, x700028_CSP_MONSTER_COUNT, 0)
	SetFubenData_Param(sceneId, x700028_CSP_XIANJINBOSS, -1 )
	
	x700028_CreateRawMonster(sceneId)
end


function x700028_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	--print("x700091_ProcAreaEntered",zoneId)
	SetFubenData_Param(sceneId, x700028_CSP_AREA_ID, zoneId)
	--@param sceneId: 场景Id
	--@param selfId: 玩家ObjId (宠物进入EnterArea也会触发这个时间)
	--@param zoneId: 区域Id
	--@param MissionId: 任务id\
	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700028_CSP_BOSS_ID)
		if BossId ~= -1 then
			return --TEST
		end
		SetFubenData_Param(sceneId, x700028_CSP_AREA_FLAG,1)
		--print("BossId",BossId)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700028_g_MissionId, x700028_g_ScriptId)
	else
	 	CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700028_g_MissionId, x700028_g_ScriptId)
	end

end	
---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700028_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )
	EnterAreaEventListHideNM(sceneId, selfId)
	SetFubenData_Param(sceneId, x700028_CSP_AREA_ID, -1)
	--print("x700028_ProcAreaLeaved"..zoneId)
--@param sceneId: 场景Id
--@param selfId: 玩家ObjId (宠物进入EnterArea也会触发这个时间)
--@param zoneId: 区域Id
--@param MissionId: 任务id

	
end


---------------------------------------------------------------------------------------------------
--区域定时器
---------------------------------------------------------------------------------------------------
function x700028_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	local zoneId = GetFubenData_Param(sceneId, x700028_CSP_AREA_ID )
	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700028_CSP_BOSS_ID)
		if BossId ~= -1 then
			return --TEST
		end
		local flag = GetFubenData_Param(sceneId, x700028_CSP_AREA_FLAG)
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700028_CSP_AREA_FLAG,1)
		--print("BossId",BossId)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700028_g_MissionId, x700028_g_ScriptId)
	else
	 	--CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700028_g_MissionId, x700028_g_ScriptId)
	end
end
--//add end



function x700028_EnterTick(sceneId, nowTickCount)
	--print("x700028_EnterTick",nowTickCount)
	local nCurrentStep = GetFubenData_Param(sceneId, x700028_CSP_CURRENTSTEP)

	if nCurrentStep<=0 then
		return
	end

	local nLen = getn(x700028_g_TimeIntervalTab)

	if nCurrentStep> nLen then
		return
	end
	
	
	local nCurrentStepTickCount = GetFubenData_Param(sceneId, x700028_CSP_CURRENTSTEP_TICKCOUNT)+1;
	SetFubenData_Param(sceneId, x700028_CSP_CURRENTSTEP_TICKCOUNT, nCurrentStepTickCount)
	
	local nNextStepTime = x700028_g_TimeIntervalTab[nCurrentStep];
	--print(nowTickCount,nCurrentStep)
	if nCurrentStepTickCount>=nNextStepTime then
		SetFubenData_Param(sceneId, x700028_CSP_CURRENTSTEP_TICKCOUNT, 0)
		SetFubenData_Param(sceneId, x700028_CSP_CURRENTSTEP,nCurrentStep+1 )
		
		if nCurrentStep< nLen then
			x700028_CreateMonster( sceneId, nCurrentStep )
		else
			x700028_CreateBoss(sceneId)
		end
    
	end
end
--print("700028")

function x700028_CreateBoss(sceneId)

	--print("x700028_CreateBoss")
	local fubenlevel = GetFubenData_Param(sceneId, x700028_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700028_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700028_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700028_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700028_g_ScriptId,nIndexFrom,i)
		if idScript == x700028_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel  and nFubenType == flag3 then                                            
		    local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700028_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700028_g_ScriptId, -1, 21,-1,facedir)
			end

			SetFubenData_Param( sceneId, x700028_CSP_BOSS_ID, nRet)
			SetPatrolId(sceneId, nRet, flag2)
			break;
        end
	end

	
end

function x700028_CreateRawMonster(sceneId)

	local nCount = GetFubenData_Param(sceneId, x700028_CSP_MONSTER_COUNT ) 
	
	local fubenlevel = GetFubenData_Param(sceneId, x700028_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700028_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700028_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700028_g_ScriptId )
	
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700028_g_ScriptId,nIndexFrom,i)
		if idScript == x700028_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel  and nFubenType == flag3 then
		    local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
			end
			
			--SetPatrolId(sceneId, nRet, flag2)
    	end
	end
        
	
	
end

---------------------------------------------------------------------------------------------------
--创建一小波怪物
---------------------------------------------------------------------------------------------------
function x700028_CreateMonster(sceneId, nStep)

	local nCount = GetFubenData_Param(sceneId, x700028_CSP_MONSTER_COUNT ) 
	
	local fubenlevel = GetFubenData_Param(sceneId, x700028_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700028_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700028_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700028_g_ScriptId )
	
	local num = 0
	for i = 0,nDataCount-1 do
		if num >= 6 then
			return
		end
			
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700028_g_ScriptId,nIndexFrom,i)
		if idScript == x700028_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do
			    local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
                
                local monId= 0
				if title~="" then
					monId= CreateMonster(sceneId, type, x, z, ai, aiscript, x700028_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					monId= CreateMonster(sceneId, type, x, z, ai, aiscript, x700028_g_ScriptId, -1, 21,-1,facedir)
									
				end
				num = num + 1
				SetPatrolId(sceneId, monId, flag2)
				
				nCount = nCount+1
				
				--print("nCount",nCount)
				SetFubenData_Param(sceneId, x700028_CSP_MONSTER_COUNT, nCount ) 
			end
        end
	end
	
end

function x700028_OnFubenEnd( sceneId)
	x700028_CreateXianJinBoss(sceneId)
	local humancount = GetFuben_PlayerCount(sceneId);
	for ii = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, ii);
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,50 )
	end	
end

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
		if idScript == x700028_g_ScriptId and monsterFlag == 10 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700028_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700028_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700028_CSP_XIANJINBOSS, nRet )
		end
	end

	x700028_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end



function x700028_OnDie(sceneId, selfId, killerId)

	local xianjinboss = GetFubenData_Param(sceneId, x700028_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	
	--print("x700028_OnDie------")
	local bossid = GetFubenData_Param(sceneId, x700028_CSP_BOSS_ID)
	local country = GetCurCountry(sceneId, selfId)	
	if bossid== selfId then
		--print("boss die",bossid,selfId)
		SetFubenData_Param(sceneId, x700028_CSP_BOSS_ID, -1)
		x700028_OnFubenEnd( sceneId)
		x700028_ShowTipsToAll(sceneId, "成功击杀亦难出，副本完成。") 
	else
		local nCurMonsterCount = GetFubenData_Param(sceneId, x700028_CSP_MONSTER_COUNT)-1 
		--print("nCurMonsterCount",nCurMonsterCount)
		SetFubenData_Param(sceneId, x700028_CSP_MONSTER_COUNT, nCurMonsterCount)
		if nCurMonsterCount==0 then
			x700028_OnAllMonsterDead( sceneId)
		end
	end	
	
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



function x700028_OnAllMonsterDead( sceneId)
	local nCurrentStep = GetFubenData_Param(sceneId, x700028_CSP_CURRENTSTEP)

	if nCurrentStep<=0 then
		return
	end

	local nLen = getn(x700028_g_TimeIntervalTab)

	if nCurrentStep> nLen then
		return
	end
	
	local nNextStepTime = x700028_g_TimeIntervalTab[nCurrentStep];
	
	SetFubenData_Param(sceneId, x700028_CSP_CURRENTSTEP_TICKCOUNT, nNextStepTime-1)
	
	--print("x700028_OnAllMonsterDead")

end

function x700028_ProcAccept( sceneId, selfId )
	--print("x700028_ProcAccept")
	--700081_NextLoopFuben( sceneId, selfId, nScriptId )
	CallScriptFunction(700081,"NextLoopFuben", sceneId, selfId, x700028_g_ScriptId)
	
	
	--local index = x700081_GetNextLoopIndex(sceneId, nScriptId)
	--CallScriptFunction(700081,"OnRequestEnterFuben", sceneId, selfId, 0, index)

end


function x700028_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
	--print("x700028_ProcQuestAccept")
end

function x700028_ProcAcceptCheck(sceneId, selfId, NPCId)
	--print("x700028_ProcAcceptCheck")
end