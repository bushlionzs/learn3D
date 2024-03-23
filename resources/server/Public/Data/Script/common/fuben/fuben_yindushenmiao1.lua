--【队伍】迷雾长廊

x700087_CSP_FUBENTYPE				= 	0
x700087_CSP_SCRIPTID				=	1
x700087_CSP_TICKCOUNT				= 	2
x700087_CSP_BACKSCENEID				= 	3
x700087_CSP_ISCLOSING				= 	4
x700087_CSP_LEAVECOUNTDOWN			= 	5
x700087_CSP_TEAMID					=	6
x700087_CSP_TICKTIME				=	7
x700087_CSP_HOLDTIME				=	8
x700087_CSP_FUBENLEVEL				=	9

x700087_CSP_FUBEN_SCENE_ID			=	10
x700087_CSP_CLOSETICK				=	11
x700087_CSP_TICKCOUNT_ADD			=	12
x700087_CSP_TICKCOUNT_SUB			=	13
x700087_CSP_B_TOPLIST_ABLE			=	14

x700087_CSP_AREA_ID					=	20
x700087_CSP_AREA_FLAG				=	21
x700087_CSP_FUBEN_START				=	238
x700087_CSP_XIANJINBOSS				=	239
x700087_CSP_HUMAN_COUNT				=	240
x700087_CSP_PLAYER_ENTER_START		=	241

x700087_CSP_LAST_TICKOUNT			=	247
x700087_CSP_GUID_START              =   248  --空6个
x700087_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型0 -- 普通1 -- 试练2 -- 英雄
x700087_CSP_FUBEN_MODE				=   255

------------------------------------------------------
x700087_CSP_GAME_STEP				=	27
x700087_CSP_BOSS1_HP				=	28
x700087_CSP_BOSS2_HP				=	29

x700087_CSP_BOSS1_ID				=	50
x700087_CSP_BOSS2_ID				=	51
x700087_CSP_MONSTER_A				=	60
x700087_CSP_MONSTER_B				=	90
x700087_CSP_MONSTER_B_HP			=	120
------------------------------------------------------

x700087_g_ScriptId 					= 700087
x700087_g_MissionId					= 6608
--x700087_g_ExitPos					= { sceneId = {50,50,50,50}, x=100, z=100, scriptId=x700087_g_ScriptId }					  
x700087_g_NextFuben					= 45

x700087_g_DestPos					= { {left=154, top=157, right=156, bottom=159}, {left=183, top=131, right=185, bottom=133} }

-- buff
x700087_g_MonsterB_BuffId			= 13517

x700087_g_MonsterACount				= 21
x700087_g_MonsterBCount				= 4

x700087_g_SubmitNPC                 = {type =28521,guid= 150565,x = 80, z=209, facedir =135, title = ""}
x700087_g_LeaveNPC                 = 150562

x700087_g_Talk_A					= "札兰丁的印度神庙就在这北印度丛林中，请速去讨伐！"										
x700087_g_Talk_B					= "印度是诸神保佑的国度，你们必将失败！"										
x700087_g_Talk_C					= "擅入谷内者死！"										
x700087_g_Talk_D					= "在我面前，你就是一个丑陋的侏儒！"										
x700087_g_Talk_E					= "夜叉之地，有来无去！"										

-- 当副本创建成功时, (初始化操作在这进行)
function x700087_OnFubenSceneCreated( sceneId )
--@param sceneId: 副本场景Id

	local humancount = GetFuben_PlayerCount(sceneId)
	SetFubenData_Param(sceneId, x700087_CSP_HUMAN_COUNT, humancount)
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i)
		SetFubenData_Param(sceneId, x700087_CSP_PLAYER_ENTER_START+i, humanId)
	end
	
	SetFubenData_Param(sceneId, x700087_CSP_XIANJINBOSS, -1 )
	
	SetFubenData_Param(sceneId, x700087_CSP_FUBEN_START, 0 )
	SetFubenData_Param(sceneId, x700087_CSP_GAME_STEP, 0)
	SetFubenData_Param(sceneId, x700087_CSP_BOSS1_HP, 0)
	SetFubenData_Param(sceneId, x700087_CSP_BOSS2_HP, 0)
	SetFubenData_Param(sceneId, x700087_CSP_BOSS2_HP+1, 0)
	
	SetFubenData_Param(sceneId, x700087_CSP_BOSS1_ID, -1)
	SetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID, -1)
	for i = 1, 6 do
		SetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID+i, -1)
	end
	
	for i = x700087_CSP_MONSTER_A, x700087_CSP_MONSTER_A+x700087_g_MonsterACount do
		SetFubenData_Param(sceneId, i, -1)
	end
	for i = x700087_CSP_MONSTER_B, x700087_CSP_MONSTER_B+x700087_g_MonsterBCount do
		SetFubenData_Param(sceneId, i, -1)
	end
	for i = x700087_CSP_MONSTER_B_HP, x700087_CSP_MONSTER_B_HP+x700087_g_MonsterBCount do
		SetFubenData_Param(sceneId, i, 0)
	end
	
	x700087_CreateBoss1(sceneId)
	x700087_CreateBoss2(sceneId)
	x700087_CreateMonsterA(sceneId)
	x700087_CreateMonsterB(sceneId)
end

-- 副本心跳接口
function x700087_EnterTick(sceneId, nowTickCount)
--@param sceneId: 副本场景Id
--@param nowTickCount: 第几次心跳
	
	if nowTickCount == 5 then
		NpcTalk(sceneId, FindMonsterByGUID(sceneId, x700087_g_LeaveNPC), x700087_g_Talk_A,  -1)
	end
	
	-- boss 1 传送
	if random(1,10) == 1 then
		local boss1 = GetFubenData_Param(sceneId, x700087_CSP_BOSS1_ID)
		if boss1 ~= -1 then
		
			local hp = GetFubenData_Param(sceneId, x700087_CSP_BOSS1_HP)
			local curhp = GetHp(sceneId, boss1)
			if curhp < hp then
				SetFubenData_Param(sceneId, x700087_CSP_BOSS1_HP, curhp)
		
				local playerId = x700087_GetAnyPlayer(sceneId)
				if playerId ~= -1  and IsPlayerStateNormal(sceneId,playerId) == 1 then
				
					local Num =  GetNearObjCount(sceneId, playerId,10,1, boss1)  
					
					for i = 0, Num-1 do
						local humanObjId = GetNearPlayerMember(sceneId, playerId,i)
						
						if humanObjId ~= -1 and IsPlayerStateNormal(sceneId,playerId) == 1  then
						
							--local b = CheckThreat(sceneId, humanObjId, boss1)
							--if b == 0 then
								local pos = x700087_g_DestPos[random(1,2)]
								NpcTalk(sceneId, boss1, x700087_g_Talk_D,  -1)
								SetPos(sceneId, humanObjId,random(pos.left, pos.right), random(pos.top, pos.bottom))
								break
							--end
						end
					end
				end
			end
		end
	end
	
	-- boss 2 分身
	local boss2 = GetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID)
	if boss2 ~= -1 then
		local max_hp = GetFubenData_Param(sceneId, x700087_CSP_BOSS2_HP)
		local hp = GetHp(sceneId, boss2)
		if hp < max_hp*0.5 then
			x700087_CreateSubBoss(sceneId, boss2)
		end
	end
	
	for i = 1, 2 do
		local subboss2 = GetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID+i)
		if subboss2 ~= -1 then
			local max_hp = GetFubenData_Param(sceneId, x700087_CSP_BOSS2_HP+1)
			local hp = GetHp(sceneId, subboss2)
			if hp < max_hp*0.25 then
				x700087_CreateSubBoss2(sceneId, subboss2, i)
			end
		end
	end
	
	-- a
	for i = 0, x700087_g_MonsterBCount do
		local mb = GetFubenData_Param(sceneId, x700087_CSP_MONSTER_B+i)
		if mb ~= -1 then
			local hp = GetFubenData_Param(sceneId, x700087_CSP_MONSTER_B_HP+i)
			local curhp = GetHp(sceneId, mb)
			
			if curhp < hp then
				SetFubenData_Param(sceneId, x700087_CSP_MONSTER_B_HP+i, curhp)
				if random(1,20) == 1 then
					local playerId = x700087_GetAnyPlayer(sceneId)
					
					if playerId ~= -1 then
						local Num =  GetNearObjCount(sceneId, playerId, 10, 0, mb)  
						
						for i = 0, Num-1 do
				
							local monsterId = GetNearMonster(sceneId, playerId,i)
							
							if x700087_IsMonsterA(sceneId, monsterId) ~= -1 then
								NpcTalk(sceneId, monsterId, x700087_g_Talk_B,  -1)
								break
							end
						end
					end
				end
			end
		end
	end
end

-- 点NPC时的DefaultEvent， 这个接口必须有。但是不处理逻辑， 空函数
function x700087_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nIndex)
end

function x700087_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	SetFubenData_Param(sceneId, x700087_CSP_AREA_ID, zoneId)
	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700087_CSP_FUBEN_START)
		if BossId ~= 1 then
			return --TEST
		end
		SetFubenData_Param(sceneId, x700087_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700087_g_MissionId, x700087_g_ScriptId)
		
	else
	 	CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700087_g_MissionId, x700087_g_ScriptId)
	end
end	
---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700087_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )
	EnterAreaEventListHideNM(sceneId, selfId)
	SetFubenData_Param(sceneId, x700087_CSP_AREA_ID, -1)
end

--区域定时器
---------------------------------------------------------------------------------------------------
function x700087_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	local zoneId = GetFubenData_Param(sceneId, x700087_CSP_AREA_ID )
	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700087_CSP_FUBEN_START)
		if BossId ~= 1 then
			return --TEST
		end
		local flag = GetFubenData_Param(sceneId, x700087_CSP_AREA_FLAG)
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700087_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700087_g_MissionId, x700087_g_ScriptId)
		
	else
	 	--CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700087_g_MissionId, x700087_g_ScriptId)
	end
end

-- 死亡通知
function x700087_OnDie(sceneId, selfId, killerId)
	
	local objId1 = GetFubenData_Param(sceneId, x700087_CSP_BOSS1_ID)
	local objId2 = GetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID)
	local subboss1 = GetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID+1)
	local subboss2 = GetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID+2)
	local subboss3 = GetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID+3)
	local subboss4 = GetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID+4)
	local subboss5 = GetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID+5)
	local subboss6 = GetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID+6)
	
	local is_end = 0
	
	local xianjinboss = GetFubenData_Param(sceneId, x700087_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	if objId1 == selfId then
		SetFubenData_Param(sceneId, x700087_CSP_BOSS1_ID, -1)
		--x700087_ShowTipsToAll(sceneId, "成功击杀梵达曼")	
		objId1 = -1
	elseif objId2 == selfId then
		SetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID, -1)
		objId2 = -1
		is_end = 1
	elseif subboss1  == selfId then
		SetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID+1, -1)
		subboss1 = -1
		is_end = 1
	elseif subboss2  == selfId then
		SetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID+2, -1)
		subboss2 = -1
		is_end = 1
	elseif subboss3  == selfId then
		SetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID+3, -1)
		subboss3 = -1
		is_end = 1
	elseif subboss4  == selfId then
		SetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID+4, -1)
		subboss4 = -1
		is_end = 1
	elseif subboss5  == selfId then
		SetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID+5, -1)
		subboss5 = -1
		is_end = 1
	elseif subboss6  == selfId then
		SetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID+6, -1)
		subboss6 = -1
		is_end = 1
	else
		local idx = x700087_IsMonsterB(sceneId, selfId)
		if idx ~= -1 then
			SetFubenData_Param(sceneId, idx, -1)
			x700087_ShowTipsToAll(sceneId, x700087_g_Talk_C)
			--NpcTalk(sceneId, nMonsterId, x700087_g_Talk_C,  -1)
			
			local playerId = x700087_GetAnyPlayer(sceneId)
			if playerId ~= -1 then
				local Num =  GetNearObjCount(sceneId, playerId, 10, 0, selfId)  
				
				local n = 1
				for i = 0, Num-1 do
					if n > 4 then
						break
					end
					
					local monsterId = GetNearMonster(sceneId, playerId,i)
					
					if x700087_IsMonsterA(sceneId, monsterId) ~= -1 then
					
						n = n+1
						SendSpecificImpactToUnit(sceneId, monsterId,monsterId,monsterId, x700087_g_MonsterB_BuffId,0 )
					end
				end
			end
		end
	end 
	
	if is_end == 1 and objId2 == -1 and subboss1 == -1 and subboss2 == -1 and subboss3 == -1 
		and subboss4 == -1  and subboss5 == -1 and subboss6 == -1 then
		
		x700087_ShowTipsToAll(sceneId, "成功击杀沙陀罗，副本完成。")
		
		x700087_OnFubenEnd(sceneId)
		
		-- 挑战副本任务
		CallScriptFunction(701116,"OnSceneBossDie", sceneId, 0)
		CallScriptFunction(701117,"OnSceneBossDie", sceneId, 0)
	end
end

--被攻击时
--function x700087_OnDamage(sceneId, selfId, killerId)
--
--	for i = x700087_CSP_MONSTER_B, x700087_CSP_MONSTER_B+3 do
--		local objId = GetFubenData_Param(sceneId, i)
--		if objId ~= -1 and random(1,100) <= 5 then
--			NpcTalk(sceneId, nMonsterId, x700087_g_Talk_B,  -1)
--		end
--	end
--	
--end


--通知所有玩家
function x700087_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId)

	for i = 0, humancount - 1 do
	
		local humanId = GetFuben_PlayerObjId(sceneId, i)
		Msg2Player(sceneId, humanId, str, 8, 3)
	end
end

-- 创建Boss 1
function x700087_CreateBoss1(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700087_CSP_FUBEN_TYPE )
	
    local fubenlevel = GetFubenData_Param(sceneId, x700087_CSP_FUBENLEVEL )

	local nIndexFrom = GetFubenDataPosByScriptID(x700087_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700087_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700087_g_ScriptId,nIndexFrom,i)
		if idScript == x700087_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 1 and flag3 == fubentype then
		
			local nRet = 0;
			if title ~="" then
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700087_g_ScriptId, -1, 21,-1,facedir, "",title)
			else
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700087_g_ScriptId, -1, 21,-1,facedir)
			end
			
			SetFubenData_Param(sceneId, x700087_CSP_BOSS1_ID, nRet )
			local hp = GetHp(sceneId, nRet)
			SetFubenData_Param(sceneId, x700087_CSP_BOSS1_HP, hp)
        end
	end
end

-- 创建Boss 2
function x700087_CreateBoss2(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700087_CSP_FUBEN_TYPE )
	
    local fubenlevel = GetFubenData_Param(sceneId, x700087_CSP_FUBENLEVEL )

	local nIndexFrom = GetFubenDataPosByScriptID(x700087_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700087_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700087_g_ScriptId,nIndexFrom,i)
		if idScript == x700087_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 2 and flag3 == fubentype then
		
			local nRet = 0;
			if title ~="" then
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700087_g_ScriptId, -1, 21,-1,facedir, "",title)
			else
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700087_g_ScriptId, -1, 21,-1,facedir)
			end
			
			SetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID, nRet )
			local hp = GetHp(sceneId, nRet)
			SetFubenData_Param(sceneId, x700087_CSP_BOSS2_HP, hp )
        end
	end
end

--创建Monster A
function x700087_CreateMonsterA(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700087_CSP_FUBEN_TYPE )
	
    local fubenlevel = GetFubenData_Param(sceneId, x700087_CSP_FUBENLEVEL )

	local nIndexFrom = GetFubenDataPosByScriptID(x700087_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700087_g_ScriptId )
	
	local idx = 0
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700087_g_ScriptId,nIndexFrom,i)
		if idScript == x700087_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 3 and flag3 == fubentype then
		
			for j=0,count -1 do

				local rx = random(-r,r)
				local x = x1 + rx
				local rz = random(-r,r)
				local z = z1 + rz
				
				local nRet = 0;
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700087_g_ScriptId, -1, 21,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700087_g_ScriptId, -1, 21,-1,facedir)
				end
				
				SetFubenData_Param(sceneId, x700087_CSP_MONSTER_A+idx, nRet )
				idx = idx + 1
			end
        end
	end
end

--创建Monster B
function x700087_CreateMonsterB(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700087_CSP_FUBEN_TYPE )
	
    local fubenlevel = GetFubenData_Param(sceneId, x700087_CSP_FUBENLEVEL )

	local nIndexFrom = GetFubenDataPosByScriptID(x700087_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700087_g_ScriptId )
	
	local idx = 0
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700087_g_ScriptId,nIndexFrom,i)
		if idScript == x700087_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 4 and flag3 == fubentype then
		
			for j=0,count -1 do

				local rx = random(-r,r)
				local x = x1 + rx
				local rz = random(-r,r)
				local z = z1 + rz
				
				local nRet = 0;
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700087_g_ScriptId, -1, 21,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700087_g_ScriptId, -1, 21,-1,facedir)
				end
				
				SetFubenData_Param(sceneId, x700087_CSP_MONSTER_B+idx, nRet )
				
				local hp = GetHp(sceneId, nRet)
				SetFubenData_Param(sceneId, x700087_CSP_MONSTER_B_HP+idx, hp )
				idx = idx + 1
			end
        end
	end
end

--创建boss 2 分身
function x700087_CreateSubBoss(sceneId, objId)
	local fubentype = GetFubenData_Param(sceneId, x700087_CSP_FUBEN_TYPE )
	
	local x, z = GetWorldPos( sceneId, objId)
	
	NpcTalk(sceneId, objId, x700087_g_Talk_E,  -1)
	DeleteMonster(sceneId, objId)
	
	local fubenlevel = GetFubenData_Param(sceneId, x700087_CSP_FUBENLEVEL )

	local nIndexFrom = GetFubenDataPosByScriptID(x700087_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700087_g_ScriptId )
	
	local idx = 0
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700087_g_ScriptId,nIndexFrom,i)
		if idScript == x700087_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 5 and flag3 == fubentype then
			for j=0,count -1 do

				local rx = random(-r,r)
				x = x + rx
				local rz = random(-r,r)
				z = z + rz
				
				local nRet = 0;
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700087_g_ScriptId, -1, 21,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700087_g_ScriptId, -1, 21,-1,facedir)
				end
				
				SetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID+1+idx, nRet)
				
				local hp = GetHp(sceneId, nRet)
				SetFubenData_Param(sceneId, x700087_CSP_BOSS2_HP+1, hp )
			
				idx = idx + 1
			end
        end
	end
	
	SetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID, -1)
	
end

function x700087_CreateSubBoss2(sceneId, objId, ii)
	local fubentype = GetFubenData_Param(sceneId, x700087_CSP_FUBEN_TYPE )
	
	local x, z = GetWorldPos( sceneId, objId)
	
	NpcTalk(sceneId, objId, x700087_g_Talk_E,  -1)
	DeleteMonster(sceneId, objId)
	
	local fubenlevel = GetFubenData_Param(sceneId, x700087_CSP_FUBENLEVEL )

	local nIndexFrom = GetFubenDataPosByScriptID(x700087_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700087_g_ScriptId )
	
	local idx = 0
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700087_g_ScriptId,nIndexFrom,i)
		if idScript == x700087_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 6 and flag3 == fubentype then
			for j=0,count -1 do

				local rx = random(-r,r)
				x = x + rx
				local rz = random(-r,r)
				z = z + rz
				
				local nRet = 0;
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700087_g_ScriptId, -1, 21,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700087_g_ScriptId, -1, 21,-1,facedir)
				end
				
				SetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID+1+2*ii+idx, nRet)
				idx = idx + 1
			end
        end
	end
	
	SetFubenData_Param(sceneId, x700087_CSP_BOSS2_ID+ii, -1)
	
end

function x700087_GetAnyPlayer(sceneId)

	local humancount = GetFuben_PlayerCount(sceneId)
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i)
		playerId = GetFubenData_Param(sceneId, x700087_CSP_PLAYER_ENTER_START+i)
		if playerId ~= -1 and IsPlayerStateNormal(sceneId,playerId) == 1 then
			return playerId
		end
	end
	return -1
end

function x700087_IsMonsterA(sceneId, monsterId)
	for i = x700087_CSP_MONSTER_A, x700087_CSP_MONSTER_A+x700087_g_MonsterACount do
		local id = GetFubenData_Param(sceneId, i)
		if id ~= -1 and id == monsterId then
			return i
		end
	end
	
	return -1
end

function x700087_IsMonsterB(sceneId, monsterId)
	for i = x700087_CSP_MONSTER_B, x700087_CSP_MONSTER_B+x700087_g_MonsterBCount do
		local id = GetFubenData_Param(sceneId, i)
		if id ~= -1 and id == monsterId then
			return i
		end
	end
	
	return -1
end

function x700087_OnFubenEnd(sceneId)
	local humancount = GetFuben_PlayerCount(sceneId);
	for ii = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, ii);
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,65 )
	end	
	
	SetFubenData_Param(sceneId, x700087_CSP_FUBEN_START, 1 )
	--x700087_CreateSubmitNpc(sceneId)
		--// add for 现金副本
	 x700087_CreateXianJinBoss(sceneId)
	 --// add end
end

-- 完成任务
function x700087_CreateSubmitNpc( sceneId)

	local npc = x700087_g_SubmitNPC
	
	if npc.title~= "" then
		CreateMonster(sceneId, npc.type, npc.x, npc.z, 3, 0, -1, npc.guid, -1,-1,npc.facedir, "", npc.title)
	else
		CreateMonster(sceneId, npc.type, npc.x, npc.z, 3, 0, -1, npc.guid, -1,-1,npc.facedir)
	end
end

--创建现金boss
function x700087_CreateXianJinBoss(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700087_CSP_FUBEN_TYPE )
	if fubentype ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700087_CSP_FUBEN_MODE)

	if nFubenMode == 0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700087_CSP_FUBENLEVEL )
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700087_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700087_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700087_g_ScriptId,nIndexFrom,i)
		if idScript == x700087_g_ScriptId and monsterFlag == 7 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700087_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700087_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700087_CSP_XIANJINBOSS, nRet )
		end
	end

	x700087_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end