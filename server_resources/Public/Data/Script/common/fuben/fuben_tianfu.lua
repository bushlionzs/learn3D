-- �츳����_����

x710000_CSP_FUBENTYPE				= 	0
x710000_CSP_SCRIPTID				=	1
x710000_CSP_TICKCOUNT				= 	2
x710000_CSP_BACKSCENEID				= 	3
x710000_CSP_ISCLOSING				= 	4
x710000_CSP_LEAVECOUNTDOWN			= 	5
x710000_CSP_TEAMID					=	6
x710000_CSP_TICKTIME				=	7
x710000_CSP_HOLDTIME				=	8
x710000_CSP_FUBENLEVEL				=	9

x710000_CSP_FUBEN_SCENE_ID			=	10
x710000_CSP_CLOSETICK				=	11
x710000_CSP_TICKCOUNT_ADD			=	12
x710000_CSP_TICKCOUNT_SUB			=	13
x710000_CSP_B_TOPLIST_ABLE			=	14
x710000_CSP_PLAYER_DEAD				=	15


x710000_CSP_HUMAN_COUNT				=	240
x710000_CSP_PLAYER_ENTER_START		=	241

x710000_CSP_LAST_TICKOUNT			=	247
x710000_CSP_GUID_START              =   248  --��6��
x710000_CSP_FUBEN_TYPE				=	254	--��������ͨ��Ӣ�ۣ���������0 -- ��ͨ1 -- ����2 -- Ӣ��
x710000_CSP_FUBEN_MODE				=   255

------------------------------------------------------
x710000_CSP_GAME_STEP				=	50	-- ��Ϸ��ǰ����
x710000_CSP_BOSS_TIME				=	51	-- boss��ʼ��ʱ
x710000_CSP_MONSTER_COUNT			=	52	-- �������
x710000_CSP_CURRENT_BOSS			=	53	-- ��ǰboss

x710000_CSP_BOSS_ID					=	100 -- 12 ��
------------------------------------------------------

x710000_g_ScriptId 					= 710000

x710000_g_SubmitNPC                 = {type =47037,guid= 150567,x = 65, z=50, facedir =180, title = ""}
x710000_g_LeaveNPC					= 150571

x710000_g_arrArea					= {Left = 64,Top = 27,Right = 73,Bottom = 35} -- ��̬�赲


-- �����������ɹ�ʱ, (��ʼ�������������)
function x710000_OnFubenSceneCreated( sceneId )
--@param sceneId: ��������Id

	local humancount = GetFuben_PlayerCount(sceneId)
	SetFubenData_Param(sceneId, x710000_CSP_HUMAN_COUNT, humancount)
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i)
		SetFubenData_Param(sceneId, x710000_CSP_PLAYER_ENTER_START+i, humanId)
	end
	
	SetFubenData_Param(sceneId, x710000_CSP_GAME_STEP, 0)
	SetFubenData_Param(sceneId, x710000_CSP_BOSS_TIME, -1)
	SetFubenData_Param(sceneId, x710000_CSP_MONSTER_COUNT, 0)
	SetFubenData_Param(sceneId, x710000_CSP_CURRENT_BOSS, -1)
	
	x710000_CreateBoss(sceneId)
	x710000_CreateMonsterB(sceneId)
end

-- ���������ӿ�
function x710000_EnterTick(sceneId, nowTickCount)
--@param sceneId: ��������Id
--@param nowTickCount: �ڼ�������
	
	local step = GetFubenData_Param(sceneId, x710000_CSP_GAME_STEP)
	
	if step == 1 then
		local index = x710000_SelectBoss(sceneId)
		if index == -1 then
			SetFubenData_Param(sceneId, x710000_CSP_GAME_STEP, 5)
			x710000_ShowTipsToAll(sceneId, "�������")
		else
			SetFubenData_Param(sceneId, x710000_CSP_GAME_STEP, 2)
			SetFubenData_Param(sceneId, x710000_CSP_BOSS_TIME, nowTickCount)
			x710000_CreateOneBoss(sceneId, index)
		end
	elseif step == 2 then
		if GetFubenData_Param(sceneId, x710000_CSP_PLAYER_DEAD) >= 6 then
			local objId = GetFubenData_Param(sceneId, x710000_CSP_CURRENT_BOSS)
			if objId ~= -1 then
				NpcTalk(sceneId, objId, "������һ��ų�������ǵı���̫����ʧ���ˣ�",  -1)
			end
			
			SetFubenData_Param(sceneId, x710000_CSP_GAME_STEP, 5)
		elseif GetFubenData_Param(sceneId, x710000_CSP_BOSS_TIME)+24 <= nowTickCount then
			local objId = GetFubenData_Param(sceneId, x710000_CSP_CURRENT_BOSS)
			if objId ~= -1 then
				NpcTalk(sceneId, objId, "���ǻ�������ϰ��",  -1)
			end
			
			SetFubenData_Param(sceneId, x710000_CSP_GAME_STEP, 5)
		end
	elseif step == 3 then
		if random(1, 100) < 30 then
			NpcTalk(sceneId, FindMonsterByGUID(sceneId, x710000_g_LeaveNPC), "�г���Ϣ���г���Ϣ��",  -1)
			
			SetFubenData_Param(sceneId, x710000_CSP_GAME_STEP, 4)
			x710000_CreateMonsterA(sceneId)
		else
			SetFubenData_Param(sceneId, x710000_CSP_GAME_STEP, 1)
		end
	--elseif step == 4 then
	elseif step == 5 then
		local objId = GetFubenData_Param(sceneId, x710000_CSP_CURRENT_BOSS)
		if objId ~= -1 then
			DeleteMonster(sceneId, objId)
			SetFubenData_Param(sceneId, x710000_CSP_CURRENT_BOSS, -1)
		end
	end
end

-- ��NPCʱ��DefaultEvent�� ����ӿڱ����С����ǲ������߼��� �պ���
function x710000_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nIndex)
		if nIndex == 0 then
			if GetFubenData_Param(sceneId, x710000_CSP_GAME_STEP) == 5 then
				BeginQuestEvent(sceneId)
				AddQuestNumText(sceneId, 710000, "�ص�����",0,1)
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId)
			end
		elseif nIndex == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t��ȷ��Ҫ�뿪�˸���������������")
			AddQuestNumText(sceneId, 710000, "ȷ��",0,2)
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif nIndex == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
			if selfcountry == 0 then
				NewWorld( sceneId, selfId, selfcountry * 100 + 50, 75 + random( 0, 5), 180 + random( 0, 5), 710000)
			elseif selfcountry ==1 then
				NewWorld( sceneId, selfId, selfcountry * 100 + 50, 75 + random( 0, 5), 180 + random( 0, 5), 710000)
			elseif selfcountry ==2 then
				NewWorld( sceneId, selfId, selfcountry * 100 + 50, 181 + random( 0, 5), 76 + random( 0, 5), 710000)
			elseif selfcountry ==3 then
				NewWorld( sceneId, selfId, selfcountry * 100 + 50, 181 + random( 0, 5), 76 + random( 0, 5), 710000)
			end
		end
end

-- ��������
function x710000_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	if GetFubenData_Param(sceneId, x710000_CSP_GAME_STEP) == 0 then
		SetFubenData_Param(sceneId, x710000_CSP_GAME_STEP, 1)
		
		x710000_CreateSubmitNpc( sceneId)
		NpcTalk(sceneId, FindMonsterByGUID(sceneId, x710000_g_LeaveNPC), "���ǽ���12�����ܴ�ʦ���б���, �������Ǽ����������, ף���Ǻ��ˣ�",  -1)
		
		AddSceneTempImpassable(sceneId,x710000_g_arrArea.Left,x710000_g_arrArea.Top,x710000_g_arrArea.Right,x710000_g_arrArea.Bottom)
		
		local humancount = GetFuben_PlayerCount(sceneId)
		for	i = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, i)
			CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, humanId, 30)
			CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, humanId, 31)
		end
	end
end

--�뿪����
function x710000_ProcAreaLeaved(sceneId, selfId, zoneId, MissionId)

end

--����ʱ��
---------------------------------------------------------------------------------------------------
function x710000_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	
end

-- ����֪ͨ
function x710000_OnDie(sceneId, selfId, killerId)
	
	if GetFubenData_Param(sceneId, x710000_CSP_CURRENT_BOSS) == selfId then
		if GetFubenData_Param(sceneId, x710000_CSP_GAME_STEP) == 2 then
			SetFubenData_Param(sceneId, x710000_CSP_GAME_STEP, 3)
			SetFubenData_Param(sceneId, x710000_CSP_CURRENT_BOSS, -1)
			x710000_ShowTipsToAll(sceneId, "�ɹ���ɱ")
		end
	else
		if GetFubenData_Param(sceneId, x710000_CSP_GAME_STEP) == 4 then
			local monstercount = GetFubenData_Param(sceneId, x710000_CSP_MONSTER_COUNT)
			SetFubenData_Param(sceneId, x710000_CSP_MONSTER_COUNT, monstercount-1)
			
			if monstercount == 1 then
				SetFubenData_Param(sceneId, x710000_CSP_GAME_STEP, 1)
			end
		end
	end 
end

--֪ͨ�������
function x710000_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId)

	for i = 0, humancount - 1 do
	
		local humanId = GetFuben_PlayerObjId(sceneId, i)
		Msg2Player(sceneId, humanId, str, 8, 3)
	end
end

-- �������
function x710000_CreateSubmitNpc( sceneId)

	local npc = x710000_g_SubmitNPC
	
	local nRet
	if npc.title~= "" then
		nRet = CreateMonster(sceneId, npc.type, npc.x, npc.z, 3, 0, -1, npc.guid, -1,-1,npc.facedir, "", npc.title)
	else
		nRet = CreateMonster(sceneId, npc.type, npc.x, npc.z, 3, 0, -1, npc.guid, -1,-1,npc.facedir)
	end
	
	SetPatrolId(sceneId, nRet, 1)
end

-- ����Boss
function x710000_CreateBoss(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x710000_CSP_FUBEN_TYPE )
    local fubenlevel = GetFubenData_Param(sceneId, x710000_CSP_FUBENLEVEL )
	local nIndexFrom = GetFubenDataPosByScriptID(x710000_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x710000_g_ScriptId )
	
	local idx = 0
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x710000_g_ScriptId,nIndexFrom,i)
		if idScript == x710000_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 0 and flag3 == fubentype then
		
			local nRet = 0;
			if title ~="" then
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x710000_g_ScriptId, -1, -1,-1,facedir, "",title)
			else
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x710000_g_ScriptId, -1, -1,-1,facedir)
			end
			
			SetFubenData_Param(sceneId, x710000_CSP_BOSS_ID+idx, nRet )
			idx = idx+1
        end
	end
end

-- ѡ��һ��boss
function x710000_SelectBoss(sceneId)
	local boss = {}
	for i = 0, 11 do
		boss[i+1] = GetFubenData_Param(sceneId, x710000_CSP_BOSS_ID+i)
	end
	
	local ret = -1
	local i = random(1, 12)
	local j = i
	repeat
		if boss[i] ~= -1 then
			ret = i
			break
		end
		
		i = i+1
		if i == 13 then
			i = 1
		end
	until j ~= i
	
	return ret
end

-- ����һ��boss
function x710000_CreateOneBoss(sceneId, index)

	-- ɾ�����ܴ�ʦ
	local obj = GetFubenData_Param(sceneId, x710000_CSP_BOSS_ID+index-1)
	if obj == -1 then
		return
	end
	DeleteMonster(sceneId, obj)

	local fubentype = GetFubenData_Param(sceneId, x710000_CSP_FUBEN_TYPE )
    local fubenlevel = GetFubenData_Param(sceneId, x710000_CSP_FUBENLEVEL )
	local nIndexFrom = GetFubenDataPosByScriptID(x710000_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x710000_g_ScriptId )
	
	local rnd = random(0,2)
	local idx = 1
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x710000_g_ScriptId,nIndexFrom,i)
		if idScript == x710000_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == rnd and flag3 == fubentype then
			if  index == idx then
				for j=0,count -1 do

					local nRet = 0;
					if title ~="" then
						nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x710000_g_ScriptId, -1, 21,-1,facedir, "",title)
					else
						nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x710000_g_ScriptId, -1, 21,-1,facedir)
					end
					
					SetFubenData_Param(sceneId, x710000_CSP_CURRENT_BOSS, nRet)
					
					SetPatrolId(sceneId, nRet, 0)
				end
				return
			else
				idx = idx+1
			end
        end
	end
end

--����Monster A
function x710000_CreateMonsterA(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x710000_CSP_FUBEN_TYPE )
    local fubenlevel = GetFubenData_Param(sceneId, x710000_CSP_FUBENLEVEL )
	local nIndexFrom = GetFubenDataPosByScriptID(x710000_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x710000_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x710000_g_ScriptId,nIndexFrom,i)
		if idScript == x710000_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 3 and flag3 == fubentype then
		
			for j=0,count -1 do

				local rx = random(-r,r)
				local x = x1 + rx
				local rz = random(-r,r)
				local z = z1 + rz
				
				local nRet = 0
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x710000_g_ScriptId, -1, 21,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x710000_g_ScriptId, -1, 21,-1,facedir)
				end
				
				SetPatrolId(sceneId, nRet, 0)
				
				local monstercount = GetFubenData_Param(sceneId, x710000_CSP_MONSTER_COUNT)
				SetFubenData_Param(sceneId, x710000_CSP_MONSTER_COUNT, monstercount+1)
			end
        end
	end
end

--����Monster B
function x710000_CreateMonsterB(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x710000_CSP_FUBEN_TYPE )
    local fubenlevel = GetFubenData_Param(sceneId, x710000_CSP_FUBENLEVEL )
	local nIndexFrom = GetFubenDataPosByScriptID(x710000_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x710000_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x710000_g_ScriptId,nIndexFrom,i)
		if idScript == x710000_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 4 and flag3 == fubentype then
		
			for j=0,count -1 do
				local nRet = 0;
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x710000_g_ScriptId, -1, -1,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x710000_g_ScriptId, -1, -1,-1,facedir)
				end
			end
        end
	end
end