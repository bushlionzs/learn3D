--【队伍】贺兰山谷

x700084_CSP_FUBENTYPE				= 	0
x700084_CSP_SCRIPTID				=	1
x700084_CSP_TICKCOUNT				= 	2
x700084_CSP_BACKSCENEID				= 	3
x700084_CSP_ISCLOSING				= 	4
x700084_CSP_LEAVECOUNTDOWN			= 	5
x700084_CSP_TEAMID					=	6
x700084_CSP_TICKTIME				=	7
x700084_CSP_HOLDTIME				=	8
x700084_CSP_FUBENLEVEL				=	9

x700084_CSP_FUBEN_SCENE_ID			=	10
x700084_CSP_CLOSETICK				=	11
x700084_CSP_TICKCOUNT_ADD			=	12
x700084_CSP_TICKCOUNT_SUB			=	13
x700084_CSP_B_TOPLIST_ABLE			=	14

x700084_CSP_AREA_ID					=   200
x700084_CSP_AREA_FLAG				=   201
x700084_CSP_XIANJINBOSS				=	239
x700084_CSP_HUMAN_COUNT				=	240
x700084_CSP_PLAYER_ENTER_START		=	241

x700084_CSP_LAST_TICKOUNT			=	247
x700084_CSP_GUID_START              =   248  --空6个
x700084_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型0 -- 普通1 -- 试练2 -- 英雄
x700084_CSP_FUBEN_MODE				=   255

------------------------------------------------------

x700084_CSP_BOSS1_ID				=	50

------------------------------------------------------
x700084_g_MissionId					=  6608
x700084_g_ScriptId 					= 700084

--x700084_g_ExitPos					= { sceneId = {50,50,50,50}, x=100, z=100, scriptId=x700084_g_ScriptId }					  
x700084_g_NextFuben					= 46

x700084_g_Run_Count					= 15

x700084_g_SubmitNPC                 = {type =28507,guid= 150574,x = 40, z=200, facedir =45, title = ""}
x700084_g_LeaveNPC                 = 150563
x700084_g_MissionId					= 6608
x700084_g_Talk_A					= "夏王墓是我西夏开国之主李元昊的陵墓，请你速去消灭盗墓贼完颜洪烈，让我家先人的陵墓完好无损！我在此先行谢过！"				
x700084_g_Talk_B					= "向我开炮，让火力来的更猛烈些吧！"								
x700084_g_Talk_C					= "让你尝尝我的厉害！"						
x700084_g_Talk_D					= "朋友们坚持住，由我来治愈你的伤痛！"	

									  
-- 当副本创建成功时, (初始化操作在这进行)
function x700084_OnFubenSceneCreated( sceneId )
--@param sceneId: 副本场景Id
	
	local humancount = GetFuben_PlayerCount(sceneId)
	SetFubenData_Param(sceneId, x700084_CSP_HUMAN_COUNT, humancount)
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i)
		SetFubenData_Param(sceneId, x700084_CSP_PLAYER_ENTER_START+i, humanId)
	end
	
	SetFubenData_Param(sceneId, x700084_CSP_BOSS1_ID, 0)
	SetFubenData_Param(sceneId, x700084_CSP_AREA_FLAG, 0)
	

	x700084_CreateBoss1(sceneId)
	x700084_CreateMonster(sceneId)
end

-- 副本心跳接口
function x700084_EnterTick(sceneId, nowTickCount)
--@param sceneId: 副本场景Id
--@param nowTickCount: 第几次心跳

	if nowTickCount == 5 then
		NpcTalk(sceneId, FindMonsterByGUID(sceneId, x700084_g_LeaveNPC), x700084_g_Talk_A,  -1)
	end
end

-- 点NPC时的DefaultEvent， 这个接口必须有。但是不处理逻辑， 空函数
function x700084_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nIndex)
end

-- 进入区域
function x700084_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

	SetFubenData_Param(sceneId, x700084_CSP_AREA_ID, zoneId)

	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700084_CSP_BOSS1_ID)
		if BossId ~= -1 then
			return --TEST
		end
		SetFubenData_Param(sceneId, x700084_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700084_g_MissionId, x700084_g_ScriptId)
		
	else
	 	CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700084_g_MissionId, x700084_g_ScriptId)
	end
end

--离开区域
function x700084_ProcAreaLeaved(sceneId, selfId, zoneId, MissionId)
	EnterAreaEventListHideNM(sceneId, selfId)
	SetFubenData_Param(sceneId, x700084_CSP_AREA_ID, -1)
end

--区域定时器
---------------------------------------------------------------------------------------------------

function x700084_ProcTiming(sceneId, selfId, ScriptId, MissionId)	


	local zoneId = GetFubenData_Param(sceneId, x700084_CSP_AREA_ID)
	if zoneId == 0 then
		
		local BossId = GetFubenData_Param(sceneId, x700084_CSP_BOSS1_ID)
		if BossId ~= -1 then
			return --TEST
		end
		
		local flag = GetFubenData_Param(sceneId, x700084_CSP_AREA_FLAG)
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700084_CSP_AREA_FLAG,1)
		
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700084_g_MissionId, x700084_g_ScriptId)
	--elseif zoneId == 1 then
		--CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700084_g_MissionId, x700084_g_ScriptId)
	end
end

-- 死亡通知
function x700084_OnDie(sceneId, selfId, killerId)
	local xianjinboss = GetFubenData_Param(sceneId, x700084_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	local objId1 = GetFubenData_Param(sceneId, x700084_CSP_BOSS1_ID)

	if objId1 == selfId then
		SetFubenData_Param(sceneId, x700084_CSP_BOSS1_ID, -1)
		x700084_ShowTipsToAll(sceneId, "成功击杀胡沙虎，副本完成。")
		
		x700084_OnFubenEnd(sceneId)
		
		-- 挑战副本任务
		CallScriptFunction(701116,"OnSceneBossDie", sceneId, 1)
		CallScriptFunction(701117,"OnSceneBossDie", sceneId, 1)
	end
end


--通知所有玩家z
function x700084_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId)

	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i)
		Msg2Player(sceneId, humanId, str, 8, 3)
	end
end

-- 创建Boss 1
function x700084_CreateBoss1(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700084_CSP_FUBEN_TYPE )
	local flag = 1
	if fubentype == 1 then
		flag = flag + 100
	elseif fubentype == 2 then
		flag = flag + 200
	end
	
    local fubenlevel = GetFubenData_Param(sceneId, x700084_CSP_FUBENLEVEL )

	local nIndexFrom = GetFubenDataPosByScriptID(x700084_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700084_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700084_g_ScriptId,nIndexFrom,i)
		
		if idScript == x700084_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 1 and flag3 == fubentype then
		
			local nRet = 0
			if title ~="" then
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700084_g_ScriptId, -1, 21,-1,facedir, "",title)
			else
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700084_g_ScriptId, -1, 21,-1,facedir)
			end
			
			SetFubenData_Param(sceneId, x700084_CSP_BOSS1_ID, nRet )
        end
	end
end

--创建Monster
function x700084_CreateMonster(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700084_CSP_FUBEN_TYPE )
	
    local fubenlevel = GetFubenData_Param(sceneId, x700084_CSP_FUBENLEVEL )

	local nIndexFrom = GetFubenDataPosByScriptID(x700084_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700084_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700084_g_ScriptId,nIndexFrom,i)
		if idScript == x700084_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 4 and flag3 == fubentype then
		
			for j=0,count -1 do

				local nRet = 0;
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700084_g_ScriptId, -1, 21,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700084_g_ScriptId, -1, 21,-1,facedir)
				end
			end
        end
	end
end

function x700084_OnFubenEnd(sceneId)
	--x700084_CreateSubmitNpc(sceneId)
		--// add for 现金副本
	x700084_CreateXianJinBoss(sceneId)
	 --// add end
	 local humancount = GetFuben_PlayerCount(sceneId);
	for ii = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, ii);
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,53 )
	end	
end

-- 完成任务
function x700084_CreateSubmitNpc( sceneId)

	local npc = x700084_g_SubmitNPC
	
	if npc.title~= "" then
		CreateMonster(sceneId, npc.type, npc.x, npc.z, 3, 0, -1, npc.guid, -1,-1,npc.facedir, "", npc.title)
	else
		CreateMonster(sceneId, npc.type, npc.x, npc.z, 3, 0, -1, npc.guid, -1,-1,npc.facedir)
	end
end

--创建现金boss
function x700084_CreateXianJinBoss(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700084_CSP_FUBEN_TYPE )
	if fubentype ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700084_CSP_FUBEN_MODE)

	if nFubenMode == 0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700084_CSP_FUBENLEVEL )
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700084_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700084_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700084_g_ScriptId,nIndexFrom,i)
		if idScript == x700084_g_ScriptId and monsterFlag == 9 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700084_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700084_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700084_CSP_XIANJINBOSS, nRet )
		end
	end

	x700084_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end