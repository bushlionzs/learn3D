-- ���԰���� ��Ƥ

x700107_CSP_FUBENTYPE				= 	0
x700107_CSP_SCRIPTID				=	1
x700107_CSP_TICKCOUNT				= 	2
x700107_CSP_BACKSCENEID				= 	3
x700107_CSP_ISCLOSING				= 	4
x700107_CSP_LEAVECOUNTDOWN			= 	5
x700107_CSP_TEAMID					=	6
x700107_CSP_TICKTIME				=	7
x700107_CSP_HOLDTIME				=	8
x700107_CSP_FUBENLEVEL				=	9

x700107_CSP_FUBEN_SCENE_ID			=	10
x700107_CSP_CLOSETICK				=	11
x700107_CSP_TICKCOUNT_ADD			=	12
x700107_CSP_TICKCOUNT_SUB			=	13
x700107_CSP_B_TOPLIST_ABLE			=	14
x700107_CSP_PLAYER_DEAD				=	15


x700107_CSP_HUMAN_COUNT				=	240
x700107_CSP_PLAYER_ENTER_START		=	241

x700107_CSP_LAST_TICKOUNT			=	247
x700107_CSP_GUID_START              =   248  --��6��
x700107_CSP_FUBEN_TYPE				=	254	--��������ͨ��Ӣ�ۣ���������0 -- ��ͨ1 -- ����2 -- Ӣ��
x700107_CSP_FUBEN_MODE				=   255

------------------------------------------------------
x700107_CSP_GAME_NPC				=	49  -- С�׺�
x700107_CSP_GAME_STEP				=	50	-- ��Ϸ��ǰ����
x700107_CSP_BOSS_ID					=	51	-- ��ǰboss
x700107_CSP_MONSTER_COUNT			=	52	-- �������
x700107_CSP_BOSS_HP					=	53
x700107_CSP_CALL_MONSTER			=	54

x700107_CSP_MONSTER_ID				=	100 -- 12 ��
------------------------------------------------------

x700107_g_ScriptId 					= 700107

x700107_g_SubmitNPC                 = {type =55105,guid =150587,x = 70, z=54, facedir =180, title = ""}
x700107_g_SubmitNPC2                 = {type =55107,guid =150592,x = 70, z=54, facedir =180, title = ""} -- С�׺�
x700107_g_LeaveNPC					= 150586

--x700107_g_BuffId1					= 13517	-- �Ա�
--x700107_g_BuffId2					= 13517	-- ��Ѫ

x700107_g_BonusTab	= 	{
							{exp = 40 , shenwang = 0.2 , inh = 0.5 , },		--С��
							{exp = 400, shenwang = 2,    inh = 5, },       --boss
						}

-- ��������
x700107_g_BackMenu = {"�ص������˼�����", "ȷ��"}
x700107_g_BackInfo = "\t��ȷ��Ҫ�뿪�˸��������������˼�������"
x700107_g_BackPos = {
						{57, 127},
						{57, 128},
						{58, 128},
						{58, 129},
						{59, 128},
						{59, 127}
					}
					
-- �����������ɹ�ʱ, (��ʼ�������������)
function x700107_OnFubenSceneCreated( sceneId )
--@param sceneId: ��������Id

	local humancount = GetFuben_PlayerCount(sceneId)
	SetFubenData_Param(sceneId, x700107_CSP_HUMAN_COUNT, humancount)
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i)
		SetFubenData_Param(sceneId, x700107_CSP_PLAYER_ENTER_START+i, humanId)
	end
	
	SetFubenData_Param(sceneId, x700107_CSP_GAME_STEP, 0)
	SetFubenData_Param(sceneId, x700107_CSP_BOSS_ID, -1)
	SetFubenData_Param(sceneId, x700107_CSP_MONSTER_COUNT, 0)
	SetFubenData_Param(sceneId, x700107_CSP_BOSS_HP, 0)
	SetFubenData_Param(sceneId, x700107_CSP_CALL_MONSTER, -1)
	
	local weekIndex = GetWeekIndex()
	local nHumanCount = GetScenePlayerCount( sceneId)
	if nHumanCount > 0 then
	    for i = 0, nHumanCount do
	        local objId = GetScenePlayerObjId( sceneId,i)
	        if objId >= 0 then
	        	SetQuestData(sceneId, objId, MD_FUBEN_HUAPI_FLAG[1], MD_FUBEN_HUAPI_FLAG[2], MD_FUBEN_HUAPI_FLAG[3], 0)
	        end
		end
	end
	
	x700107_CreateSubmitNpc2(sceneId)
end

-- ���������ӿ�
function x700107_EnterTick(sceneId, nowTickCount)
--@param sceneId: ��������Id
--@param nowTickCount: �ڼ�������
	
	if nowTickCount == 1 then
		NpcTalk(sceneId, FindMonsterByGUID(sceneId, x700107_g_LeaveNPC), "��ս�������׶Σ����ܵ�ͨ���ڻ�ӿ����������谭���BOSS�Ľ�������������������ܻ�Կ�Ŷ��",  -1)
	end
	
	local step = GetFubenData_Param(sceneId, x700107_CSP_GAME_STEP)
	local objId = GetFubenData_Param(sceneId, x700107_CSP_BOSS_ID)
	
	if nowTickCount == 2 then
		SetFubenData_Param(sceneId, x700107_CSP_CALL_MONSTER, 0)
		x700107_CreateBoss(sceneId, 0)
	end
	
	if GetFubenData_Param(sceneId, x700107_CSP_CALL_MONSTER) == 0 and objId ~= -1 then
		local maxhp = GetFubenData_Param(sceneId, x700107_CSP_BOSS_HP)
		local hp = GetHp(sceneId, objId)
		if hp/maxhp < 0.7 then
		
			SetFubenData_Param(sceneId, x700107_CSP_CALL_MONSTER, 1)
			x700107_CreateMonster(sceneId, step)
			
			if step == 0 then
				NpcTalk(sceneId, objId, "С���ǣ������ˣ�",  -1)
			elseif step == 1 then
				NpcTalk(sceneId, objId, "С���ǣ����������ɣ�",  -1)
			elseif step == 2 then
				NpcTalk(sceneId, objId, "С���ǣ��ҿ쿸��ס�ˣ�",  -1)
			end
		end
	end
	
	if step == 1 and objId ~= -1 then
	-- �Ա�
	
		local objId1 = GetFubenData_Param(sceneId, x700107_CSP_GAME_NPC)
		local objId2 = FindMonsterByGUID(sceneId, x700107_g_LeaveNPC)
	
	
		local humancount = GetFuben_PlayerCount(sceneId)
		for	i = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, i)
			if humanId ~= -1 and IsPlayerStateNormal(sceneId,humanId) == 1 and IsInDist(sceneId, humanId, objId, 10) == 1 then
				
				local Num = GetNearObjCount(sceneId, humanId, 5, 0, humanId)
				if Num > 0 then
					for j = 0, Num-1 do
						local monsterId = GetNearMonster(sceneId, humanId,j)
						if monsterId ~= objId and IsObjValid(sceneId,monsterId) == 1 and GetHp(sceneId,monsterId) > 0 and objId1 ~= monsterId and objId2 ~= monsterId then
						
							--SendSpecificImpactToUnit(sceneId, humanObjId, humanObjId, humanObjId, x700107_g_BuffId1, 0)
							local hp = GetHp(sceneId, humanId)
							SetHp(sceneId, humanId, -3000)
							
							DeleteMonster(sceneId, monsterId)
							break
						end
					end
				end
			end
		end
	end
	
	if step == 2 and objId ~= -1 then
		local objId1 = GetFubenData_Param(sceneId, x700107_CSP_GAME_NPC)
		local objId2 = FindMonsterByGUID(sceneId, x700107_g_LeaveNPC)
		local maxhp = GetFubenData_Param(sceneId, x700107_CSP_BOSS_HP)
		local hp = GetHp(sceneId, objId)
		if hp/maxhp < 0.7 then
			local humancount = GetFuben_PlayerCount(sceneId)
			for	i = 0, humancount - 1 do
				local humanId = GetFuben_PlayerObjId(sceneId, i)
				if humanId ~= -1 and IsPlayerStateNormal(sceneId,humanId) == 1 then
				
					local Num = GetNearObjCount(sceneId, humanId, 10, 0, objId)
					if Num > 0 then
						for j = 0, Num-1 do
							local monsterId = GetNearMonster(sceneId, humanId,j)
							if monsterId ~= objId and IsObjValid(sceneId,monsterId) == 1 and GetHp(sceneId,monsterId) > 0 and monsterId ~= objId1 and monsterId ~= objId2 then
								local addhp = maxhp*0.3
								if hp+addhp > maxhp*0.8 then
									addhp = maxhp*0.8-hp
								end
								
								SetHp(sceneId, objId, addhp)
								--SendSpecificImpactToUnit(sceneId, monsterId, monsterId, monsterId, x700107_g_BuffId2, 0 )
								break
							end
						end
					end
					break
				end
			end
		end	
	end
end

function x700107_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	AddQuestNumText(sceneId, x700107_g_ScriptId, x700107_g_BackMenu[1],0,1)
end

-- ��NPCʱ��DefaultEvent�� ����ӿڱ����С����ǲ������߼��� �պ���
function x700107_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nIndex)
	if nIndex == 0 then
		BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x700107_g_ScriptId, x700107_g_BackMenu[1],0,1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, NPCId)
	elseif nIndex == 1 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x700107_g_BackInfo)
			AddQuestNumText(sceneId, x700107_g_ScriptId, x700107_g_BackMenu[2],0,2)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, NPCId)
	elseif nIndex == 2 then
        TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
        TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
        local pos = x700107_g_BackPos[random(1, 6)]
		NewWorld( sceneId, selfId, 40, pos[1], pos[2], 700107)
	end
end

-- ��������
function x700107_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	
end

--�뿪����
function x700107_ProcAreaLeaved(sceneId, selfId, zoneId, MissionId)

end

--����ʱ��
---------------------------------------------------------------------------------------------------
function x700107_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	
end

-- ����֪ͨ
function x700107_OnDie(sceneId, selfId, killerId)
	
	if GetFubenData_Param(sceneId, x700107_CSP_BOSS_ID) == selfId then
		local monstercount = GetFubenData_Param(sceneId, x700107_CSP_MONSTER_COUNT)
		for i = 0, monstercount-1 do
			local objId = GetFubenData_Param(sceneId, x700107_CSP_MONSTER_ID+i)
			if objId ~= -1 then
				DeleteMonster(sceneId, objId)
			end
		end
		
		SetFubenData_Param(sceneId, x700107_CSP_MONSTER_COUNT, 0)
		
		local step = GetFubenData_Param(sceneId, x700107_CSP_GAME_STEP)
		if step ~= 2 then
			SetFubenData_Param(sceneId, x700107_CSP_GAME_STEP, step+1)
			x700107_CreateBoss(sceneId, step+1)
			SetFubenData_Param(sceneId, x700107_CSP_CALL_MONSTER, 0)
		else
			SetFubenData_Param(sceneId, x700107_CSP_BOSS_ID, -1)
			x700107_CreateSubmitNpc(sceneId)
			
			x700107_ShowTipsToAll(sceneId, "�ɹ���ɱţħ��������ɣ����˳�������")
		end
		
		local humancount = GetFuben_PlayerCount(sceneId)
		for i = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, i)
			local level =GetLevel( sceneId, humanId)
			local mutli = 1
			if IsHaveSpecificImpact( sceneId, humanId, 7510) == 1 or IsHaveSpecificImpact( sceneId, humanId, 7511) == 1
				or IsHaveSpecificImpact( sceneId, humanId, 9007) == 1 then --˫������
				mutli = mutli+1
			end
			if IsHaveSpecificImpact( sceneId, humanId, 9015) == 1 then
				mutli = mutli+1
			end
			if IsHaveSpecificImpact( sceneId, humanId, 9012) == 1 then --��ނ���
				mutli =  mutli + 0.20
			end
			local inh =  floor(level*x700107_g_BonusTab[2].inh*mutli)
			local refixInh = AddInherenceExp(sceneId, humanId, inh)
			local msg = format("������%d���츳ֵ��",refixInh)
			Msg2Player(sceneId, humanId, msg, 0, 2)
			Msg2Player(sceneId, humanId, msg, 0, 3)
		end
        					
		--x700107_ShowTipsToAll(sceneId, "�ɹ���ɱ")
	else
		local monstercount = GetFubenData_Param(sceneId, x700107_CSP_MONSTER_COUNT)
		for i = 0, monstercount-1 do
			local objId = GetFubenData_Param(sceneId, x700107_CSP_MONSTER_ID+i)
			if objId ~= -1 and objId == selfId then
				SetFubenData_Param(sceneId, x700107_CSP_MONSTER_ID+i, -1)
				
				local humancount = GetFuben_PlayerCount(sceneId)
				for i = 0, humancount - 1 do
					local humanId = GetFuben_PlayerObjId(sceneId, i)
					local level =GetLevel( sceneId, humanId)
					local mutli = 1
					if IsHaveSpecificImpact( sceneId, humanId, 7510) == 1 or IsHaveSpecificImpact( sceneId, humanId, 7511) == 1
						or IsHaveSpecificImpact( sceneId, humanId, 9007) == 1 then --˫������
						mutli = mutli+1
					end
					if IsHaveSpecificImpact( sceneId, humanId, 9015) == 1 then
						mutli = mutli+1
					end
					if IsHaveSpecificImpact( sceneId, humanId, 9012) == 1 then --��ނ���
						mutli =  mutli + 0.20
					end
					local inh =  floor(level*x700107_g_BonusTab[1].inh*mutli)
					local refixInh = AddInherenceExp(sceneId, humanId, inh)
					local msg = format("������%d���츳ֵ��",refixInh)
					Msg2Player(sceneId, humanId, msg, 0, 2)
					Msg2Player(sceneId, humanId, msg, 0, 3)
				end
				return
			end
		end
	end 
end

--֪ͨ�������
function x700107_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId)

	for i = 0, humancount - 1 do
	
		local humanId = GetFuben_PlayerObjId(sceneId, i)
		Msg2Player(sceneId, humanId, str, 8, 3)
	end
end

-- �������
function x700107_CreateSubmitNpc(sceneId)

	local objId = GetFubenData_Param(sceneId, x700107_CSP_GAME_NPC)
	if objId ~= -1 then
		DeleteMonster(sceneId, objId)
	end

	local npc = x700107_g_SubmitNPC
	
	local nRet
	if npc.title~= "" then
		nRet = CreateMonster(sceneId, npc.type, npc.x, npc.z, 3, 0, -1, npc.guid, -1,-1,npc.facedir, "", npc.title)
	else
		nRet = CreateMonster(sceneId, npc.type, npc.x, npc.z, 3, 0, -1, npc.guid, -1,-1,npc.facedir)
	end
	
	x700107_CreateXianJinBoss(sceneId)
end

-- �������
function x700107_CreateSubmitNpc2(sceneId)

	local npc = x700107_g_SubmitNPC2
	
	local nRet
	if npc.title~= "" then
		nRet = CreateMonster(sceneId, npc.type, npc.x, npc.z, 3, 0, -1, npc.guid, -1,-1,npc.facedir, "", npc.title)
	else
		nRet = CreateMonster(sceneId, npc.type, npc.x, npc.z, 3, 0, -1, npc.guid, -1,-1,npc.facedir)
	end
	
	SetFubenData_Param(sceneId, x700107_CSP_GAME_NPC, nRet)
end

-- ����Boss
function x700107_CreateBoss(sceneId, step)
	local fubentype = GetFubenData_Param(sceneId, x700107_CSP_FUBEN_TYPE )
    local fubenlevel = GetFubenData_Param(sceneId, x700107_CSP_FUBENLEVEL )
	local nIndexFrom = GetFubenDataPosByScriptID(x700107_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700107_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700107_g_ScriptId,nIndexFrom,i)
		if idScript == x700107_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == step and flag3 == fubentype then
		
			local nRet = 0;
			if title ~="" then
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700107_g_ScriptId, -1, 21,-1,facedir, "",title)
			else
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700107_g_ScriptId, -1, 21,-1,facedir)
			end
			
			SetFubenData_Param(sceneId, x700107_CSP_BOSS_ID, nRet )
			
			local hp = GetHp(sceneId, nRet)
			SetFubenData_Param(sceneId, x700107_CSP_BOSS_HP, hp )
        end
	end
end

--����Monster
function x700107_CreateMonster(sceneId, step)
	local fubentype = GetFubenData_Param(sceneId, x700107_CSP_FUBEN_TYPE )
    local fubenlevel = GetFubenData_Param(sceneId, x700107_CSP_FUBENLEVEL )
	local nIndexFrom = GetFubenDataPosByScriptID(x700107_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700107_g_ScriptId )
	
	local monstercount = 0
	
	local index = 0
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700107_g_ScriptId,nIndexFrom,i)
		if idScript == x700107_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 3+step and flag3 == fubentype then
		
			for j=0,count -1 do

				local rx = random(-r,r)
				local x = x1 + rx
				local rz = random(-r,r)
				local z = z1 + rz
				
				local nRet = 0
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700107_g_ScriptId, -1, 21,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700107_g_ScriptId, -1, 21,-1,facedir)
				end
				
				SetFubenData_Param(sceneId, x700107_CSP_MONSTER_ID+index, nRet )
				index = index+1
				SetPatrolId(sceneId, nRet, 0)
				monstercount = monstercount+1
			end
        end
	end
	
	SetFubenData_Param(sceneId, x700107_CSP_MONSTER_COUNT, monstercount)
end

--�����ֽ�boss
function x700107_CreateXianJinBoss(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700107_CSP_FUBEN_TYPE )
	if fubentype ~= 0 then
		--return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700107_CSP_FUBEN_MODE)

	if nFubenMode == 0 then
		--return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700107_CSP_FUBENLEVEL )
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700107_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700107_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700107_g_ScriptId,nIndexFrom,i)
		if idScript == x700107_g_ScriptId and monsterFlag == 6 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700107_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700107_g_ScriptId, -1, 21,-1,facedir)
			end
			--SetFubenData_Param(sceneId, x700107_CSP_XIANJINBOSS, nRet )
		end
	end

	--x700107_ShowTipsToAll(sceneId, "����������֣�")
end