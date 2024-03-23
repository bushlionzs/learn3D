--�����顿����ɭ��

x700088_CSP_FUBENTYPE				= 	0
x700088_CSP_SCRIPTID				=	1
x700088_CSP_TICKCOUNT				= 	2
x700088_CSP_BACKSCENEID				= 	3
x700088_CSP_ISCLOSING				= 	4
x700088_CSP_LEAVECOUNTDOWN			= 	5
x700088_CSP_TEAMID					=	6
x700088_CSP_TICKTIME				=	7
x700088_CSP_HOLDTIME				=	8
x700088_CSP_FUBENLEVEL				=	9

x700088_CSP_FUBEN_SCENE_ID			=	10
x700088_CSP_CLOSETICK				=	11
x700088_CSP_TICKCOUNT_ADD			=	12
x700088_CSP_TICKCOUNT_SUB			=	13
x700088_CSP_B_TOPLIST_ABLE			=	14
x700088_CSP_AREA_ID					=   20
x700088_CSP_AREA_FLAG				=	21
x700088_CSP_XIANJINBOSS				=	239
x700088_CSP_HUMAN_COUNT				=	240
x700088_CSP_PLAYER_ENTER_START		=	241

x700088_CSP_LAST_TICKOUNT			=	247
x700088_CSP_GUID_START              =   248  --��6��
x700088_CSP_FUBEN_TYPE				=	254	--��������ͨ��Ӣ�ۣ���������0 -- ��ͨ1 -- ����2 -- Ӣ��
x700088_CSP_FUBEN_MODE				=   255

------------------------------------------------------

x700088_CSP_BOSS1_ID				=	50

------------------------------------------------------

x700088_g_ScriptId 					= 700088
x700088_g_MissionId					= 6608
--x700088_g_ExitPos					= { sceneId = {50,50,50,50}, x=100, z=100, scriptId=x700088_g_ScriptId }					  
x700088_g_NextFuben					= 46

x700088_g_Run_Count					= 15

x700088_g_SubmitNPC                 = {type =28522,guid= 150566,x = 92, z=30, facedir =270, title = ""}
x700088_g_LeaveNPC                 = 150563

x700088_g_Talk_A					= "��˵ӵ�в���֮�����������ǹ���룬���Ҽ�����һ���ܹ��ݿ������Ľ������ܣ�"				
x700088_g_Talk_B					= "���ҿ��ڣ��û������ĸ�����Щ�ɣ�"								
x700088_g_Talk_C					= "���㳢���ҵ�������"						
x700088_g_Talk_D					= "�����Ǽ��ס�����������������ʹ��"	

									  
-- �����������ɹ�ʱ, (��ʼ�������������)
function x700088_OnFubenSceneCreated( sceneId )
--@param sceneId: ��������Id
	
	local humancount = GetFuben_PlayerCount(sceneId)
	SetFubenData_Param(sceneId, x700088_CSP_HUMAN_COUNT, humancount)
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i)
		SetFubenData_Param(sceneId, x700088_CSP_PLAYER_ENTER_START+i, humanId)
	end
	
	SetFubenData_Param(sceneId, x700088_CSP_BOSS1_ID, -1)
	SetFubenData_Param(sceneId, x700088_CSP_XIANJINBOSS, -1 )

	x700088_CreateBoss1(sceneId)
	x700088_CreateMonster(sceneId)
end

-- ���������ӿ�
function x700088_EnterTick(sceneId, nowTickCount)
--@param sceneId: ��������Id
--@param nowTickCount: �ڼ�������

	if nowTickCount == 5 then
		NpcTalk(sceneId, FindMonsterByGUID(sceneId, x700088_g_LeaveNPC), x700088_g_Talk_A,  -1)
	end
end

-- ��NPCʱ��DefaultEvent�� ����ӿڱ����С����ǲ������߼��� �պ���
function x700088_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nIndex)
end

function x700088_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	SetFubenData_Param(sceneId, x700088_CSP_AREA_ID, zoneId)
	if zoneId == 0 then  --����
		local BossId = GetFubenData_Param(sceneId, x700088_CSP_BOSS1_ID)
		if BossId ~= -1 then
			return --TEST
		end
		SetFubenData_Param(sceneId, x700088_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700088_g_MissionId, x700088_g_ScriptId)
		
	else
	 	CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700088_g_MissionId, x700088_g_ScriptId)
	end
end	
---------------------------------------------------------------------------------------------------
--�뿪����
---------------------------------------------------------------------------------------------------
function x700088_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )
	EnterAreaEventListHideNM(sceneId, selfId)
	SetFubenData_Param(sceneId, x700088_CSP_AREA_ID, -1)
end

--����ʱ��
---------------------------------------------------------------------------------------------------
function x700088_ProcTiming(sceneId, selfId, ScriptId, MissionId)	
	local zoneId = GetFubenData_Param(sceneId, x700088_CSP_AREA_ID )
	if zoneId == 0 then  --����
		local BossId = GetFubenData_Param(sceneId, x700088_CSP_BOSS1_ID)
		if BossId ~= -1 then
			return --TEST
		end
		local flag = GetFubenData_Param(sceneId, x700088_CSP_AREA_FLAG)
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700088_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700088_g_MissionId, x700088_g_ScriptId)
		
	else
	 	--CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700088_g_MissionId, x700088_g_ScriptId)
	end
end

-- ����֪ͨ
function x700088_OnDie(sceneId, selfId, killerId)
	
	local xianjinboss = GetFubenData_Param(sceneId, x700088_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	local objId1 = GetFubenData_Param(sceneId, x700088_CSP_BOSS1_ID)

	if objId1 == selfId then
		SetFubenData_Param(sceneId, x700088_CSP_BOSS1_ID, -1)
		x700088_ShowTipsToAll(sceneId, "�ɹ���ɱ���а����������������ɡ�")
		
		x700088_OnFubenEnd(sceneId)
		
		-- ��ս��������
		CallScriptFunction(701116,"OnSceneBossDie", sceneId, 1)
		CallScriptFunction(701117,"OnSceneBossDie", sceneId, 1)
	end
end


--֪ͨ�������z
function x700088_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId)

	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i)
		Msg2Player(sceneId, humanId, str, 8, 3)
	end
end

-- ����Boss 1
function x700088_CreateBoss1(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700088_CSP_FUBEN_TYPE )
	local flag = 1
	if fubentype == 1 then
		flag = flag + 100
	elseif fubentype == 2 then
		flag = flag + 200
	end
	
    local fubenlevel = GetFubenData_Param(sceneId, x700088_CSP_FUBENLEVEL )

	local nIndexFrom = GetFubenDataPosByScriptID(x700088_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700088_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700088_g_ScriptId,nIndexFrom,i)
		
		if idScript == x700088_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 1 and flag3 == fubentype then
		
			local nRet = 0
			if title ~="" then
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700088_g_ScriptId, -1, 21,-1,facedir, "",title)
			else
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700088_g_ScriptId, -1, 21,-1,facedir)
			end
			
			SetFubenData_Param(sceneId, x700088_CSP_BOSS1_ID, nRet )
        end
	end
end

--����Monster
function x700088_CreateMonster(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700088_CSP_FUBEN_TYPE )
	
    local fubenlevel = GetFubenData_Param(sceneId, x700088_CSP_FUBENLEVEL )

	local nIndexFrom = GetFubenDataPosByScriptID(x700088_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700088_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700088_g_ScriptId,nIndexFrom,i)
		if idScript == x700088_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 4 and flag3 == fubentype then
		
			for j=0,count -1 do

				local nRet = 0;
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700088_g_ScriptId, -1, 21,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700088_g_ScriptId, -1, 21,-1,facedir)
				end
			end
        end
	end
end

function x700088_OnFubenEnd(sceneId)
	--x700088_CreateSubmitNpc(sceneId)
		--// add for �ֽ𸱱�
	x700088_CreateXianJinBoss(sceneId)
	 --// add end
	 local humancount = GetFuben_PlayerCount(sceneId);
	for ii = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, ii);
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,66 )
	end	
end

-- �������
function x700088_CreateSubmitNpc( sceneId)

	local npc = x700088_g_SubmitNPC
	
	if npc.title~= "" then
		CreateMonster(sceneId, npc.type, npc.x, npc.z, 3, 0, -1, npc.guid, -1,-1,npc.facedir, "", npc.title)
	else
		CreateMonster(sceneId, npc.type, npc.x, npc.z, 3, 0, -1, npc.guid, -1,-1,npc.facedir)
	end
end

--�����ֽ�boss
function x700088_CreateXianJinBoss(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700088_CSP_FUBEN_TYPE )
	if fubentype ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700088_CSP_FUBEN_MODE)

	if nFubenMode == 0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700088_CSP_FUBENLEVEL )
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700088_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700088_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700088_g_ScriptId,nIndexFrom,i)
		if idScript == x700088_g_ScriptId and monsterFlag == 9 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700088_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700088_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700088_CSP_XIANJINBOSS, nRet )
		end
	end

	x700088_ShowTipsToAll(sceneId, "����������֣�")
end