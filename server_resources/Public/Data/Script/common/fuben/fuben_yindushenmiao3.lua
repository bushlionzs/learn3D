--�����顿ӡ������

x700089_CSP_FUBENTYPE				= 	0
x700089_CSP_SCRIPTID				=	1
x700089_CSP_TICKCOUNT				= 	2
x700089_CSP_BACKSCENEID				= 	3
x700089_CSP_ISCLOSING				= 	4
x700089_CSP_LEAVECOUNTDOWN			= 	5
x700089_CSP_TEAMID					=	6
x700089_CSP_TICKTIME				=	7
x700089_CSP_HOLDTIME				=	8
x700089_CSP_FUBENLEVEL				=	9

x700089_CSP_FUBEN_SCENE_ID			=	10
x700089_CSP_CLOSETICK				=	11
x700089_CSP_TICKCOUNT_ADD			=	12
x700089_CSP_TICKCOUNT_SUB			=	13
x700089_CSP_B_TOPLIST_ABLE			=	14
x700089_CSP_AREA_ID					=   20
x700089_CSP_AREA_FLAG				=	21
x700089_CSP_HUMAN_COUNT				=	240
x700089_CSP_PLAYER_ENTER_START		=	241

x700089_CSP_LAST_TICKOUNT			=	247
x700089_CSP_GUID_START              =   248  --��6��
x700089_CSP_FUBEN_TYPE				=	254	--��������ͨ��Ӣ�ۣ���������0 -- ��ͨ1 -- ����2 -- Ӣ��
x700089_CSP_FUBEN_MODE				=   255

------------------------------------------------------
x700089_CSP_BOSS_C_HP				=	25
x700089_CSP_BOSS_C2_HP				=	26
x700089_CSP_BOSS2_HP				=	27

x700089_CSP_BOSS1_FLAG				=	30
x700089_CSP_BOSS2_FLAG				=	32
x700089_CSP_BOSS2_TIME				=	33

x700089_CSP_BOSS1_ID				=	50
x700089_CSP_BOSS2_ID				=	51
x700089_CSP_BOSS_C_ID				=	52
x700089_CSP_BOSS_D_ID				=	54

x700089_CSP_MONSTER_A				=	60
x700089_CSP_MONSTER_B				=	120

x700089_B_CREATE_RANDOMBOSS			=	230
x700089_CSP_RANDOM_BOSS_ID			=	231
x700089_RANDOMBOSS_FLAG				=	232

x700089_CSP_XIANJINBOSS				=	239
------------------------------------------------------
x700089_g_MissionId					= 6608
x700089_g_ScriptId 					= 700089

--x700089_g_ExitPos					= { sceneId = {50,50,50,50}, x=100, z=100, scriptId=x700089_g_ScriptId }

-- buff
x700089_g_MonsterB_BuffId			= 13517
x700089_g_Boss2_BuffId1				= {13218,9520}
x700089_g_Boss2_BuffId2				= {13219,9561}
x700089_g_Boss2_BuffId3				= {13220,9601}
x700089_g_Boss2_BuffId4				= {13221,9641}
x700089_g_Boss2_BuffId5				= {13222,9656}


x700089_g_MonsterACount				= 60
x700089_g_MonsterBCount				= 10

x700089_g_RandomMonsterRate			= 0.1                       --����boss���ּ���
x700089_g_RandomMonsterRateZHOUSANFAN			= 67                      --����boss���ּ��� �ٷ�֮��!
		
x700089_g_SubmitNPC                 = {type =28523,guid= 150567,x = 30, z=100, facedir =180, title = ""}
x700089_g_LeaveNPC                 = 150564

x700089_g_Talk_A					= "ע���Ǹ��Ĵ��ε���ҹ�棬�����������Ļ�ҹ��ħ��������"										
x700089_g_Talk_B					= "���㳢���һ�������ζ��"											
x700089_g_Talk_C					= "���������Ӳ���������ս��"												
x700089_g_Talk_D					= "�����������������ӣ�"
						  
						  
-- �����������ɹ�ʱ, (��ʼ�������������)
function x700089_OnFubenSceneCreated( sceneId )
--@param sceneId: ��������Id
	
	local humancount = GetFuben_PlayerCount(sceneId)
	SetFubenData_Param(sceneId, x700089_CSP_HUMAN_COUNT, humancount)
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i)
		SetFubenData_Param(sceneId, x700089_CSP_PLAYER_ENTER_START+i, humanId)
	end
	SetFubenData_Param(sceneId, x700089_CSP_XIANJINBOSS, -1 )
	SetFubenData_Param(sceneId, x700089_CSP_BOSS_C_HP, 0)
	SetFubenData_Param(sceneId, x700089_CSP_BOSS_C2_HP, 0)
	SetFubenData_Param(sceneId, x700089_CSP_BOSS2_HP, 0)
	
	SetFubenData_Param(sceneId, x700089_CSP_BOSS1_FLAG, 0)
	SetFubenData_Param(sceneId, x700089_CSP_BOSS2_FLAG, 0)
	SetFubenData_Param(sceneId, x700089_CSP_BOSS2_TIME, 0)
	
	SetFubenData_Param(sceneId, x700089_CSP_BOSS1_ID, -1)
	SetFubenData_Param(sceneId, x700089_CSP_BOSS2_ID, -1)
	
	SetFubenData_Param(sceneId, x700089_CSP_BOSS_C_ID, -1)
	SetFubenData_Param(sceneId, x700089_CSP_BOSS_C_ID+1, -1)
	SetFubenData_Param(sceneId, x700089_CSP_BOSS_D_ID, -1)
	
	for i = x700089_CSP_MONSTER_A, x700089_CSP_MONSTER_A+x700089_g_MonsterACount do
		SetFubenData_Param(sceneId, i, -1)
	end
	for i = x700089_CSP_MONSTER_B, x700089_CSP_MONSTER_B+x700089_g_MonsterBCount do
		SetFubenData_Param(sceneId, i, -1)
	end
	
	SetFubenData_Param(sceneId, x700089_B_CREATE_RANDOMBOSS, 0)
	SetFubenData_Param(sceneId, x700089_CSP_RANDOM_BOSS_ID, -1)
	SetFubenData_Param(sceneId, x700089_RANDOMBOSS_FLAG, 0)

	x700089_CreateBoss2(sceneId)
	x700089_CreateMonsterA(sceneId)
	x700089_CreateMonsterB(sceneId)
	x700089_CreateMonsterC(sceneId)
end

-- ���������ӿ�
function x700089_EnterTick(sceneId, nowTickCount)
--@param sceneId: ��������Id
--@param nowTickCount: �ڼ�������

	if nowTickCount == 5 then
		NpcTalk(sceneId, FindMonsterByGUID(sceneId, x700089_g_LeaveNPC), x700089_g_Talk_A,  -1)
	end
	
	-- boss 1
	local objc1 = GetFubenData_Param(sceneId, x700089_CSP_BOSS_C_ID)
	local objc2 = GetFubenData_Param(sceneId, x700089_CSP_BOSS_C_ID+1)
	local boss1_flag = GetFubenData_Param(sceneId, x700089_CSP_BOSS1_FLAG)
	local objd = GetFubenData_Param(sceneId, x700089_CSP_BOSS_D_ID)
	
	if boss1_flag == 0 then
		if objc1 ~= -1 and objc2 ~= -1 then
			local hp1 = GetHp(sceneId, objc1)
			local hp2 = GetHp(sceneId, objc2)
			local max_hp1 = GetFubenData_Param(sceneId, x700089_CSP_BOSS_C_HP)
			local max_hp2 = GetFubenData_Param(sceneId, x700089_CSP_BOSS_C2_HP)
			if hp1 < max_hp1 or hp2 <max_hp2 then
				x700089_CreateMonsterD(sceneId)
				SetFubenData_Param(sceneId, x700089_CSP_BOSS1_FLAG, 1)
			end
		end
	elseif boss1_flag == 1 and objd ~= -1 then
		if mod(nowTickCount, 3) == 0 then
			NpcTalk(sceneId, objd, "����������������������ͨ�����Ⱥ���������֣�",  -1)
		end
			
		local x, z = GetWorldPos( sceneId, objd)
		if x >= 56 and x <= 66 and z >= 50 and z <= 66 then
			SetFubenData_Param(sceneId, x700089_CSP_BOSS1_FLAG, 2)
			DeleteMonster(sceneId, objd)
			SetFubenData_Param(sceneId, x700089_CSP_BOSS_D_ID, -1)
			
			if objc1 ~= -1 and objc2 ~= -1 then
			
				DeleteMonster(sceneId, objc1)
				DeleteMonster(sceneId, objc2)
				
				SetFubenData_Param(sceneId, x700089_CSP_BOSS_C_ID, -1)
				SetFubenData_Param(sceneId, x700089_CSP_BOSS_C_ID+1, -1)
				
				x700089_CreateBoss1(sceneId)
			end
		end		
	end
	
	-- boss 2 buff
	local boss2 = GetFubenData_Param(sceneId, x700089_CSP_BOSS2_ID)
	local boss2_flag = GetFubenData_Param(sceneId, x700089_CSP_BOSS2_FLAG)
	local boss2_time = GetFubenData_Param(sceneId, x700089_CSP_BOSS2_TIME)
	if boss2_flag == 0 then
		if boss2 ~= -1 then
			local hp = GetHp(sceneId, boss2)
			local max_hp = GetFubenData_Param(sceneId, x700089_CSP_BOSS2_HP)
			if hp < max_hp then
				SetFubenData_Param(sceneId, x700089_CSP_BOSS2_FLAG, 1)
				SetFubenData_Param(sceneId, x700089_CSP_BOSS2_TIME, nowTickCount)
			end
		end
	elseif boss2_flag == 1 then
		if nowTickCount - boss2_time > 6 then
			NpcTalk(sceneId, boss2, "�Ҹо�������ԴԴ���ϵ�ӿ��",  -1)
			SendSpecificImpactToUnit(sceneId, boss2,boss2,boss2, x700089_g_Boss2_BuffId1[1],0 )
			SendSpecificImpactToUnit(sceneId, boss2,boss2,boss2, x700089_g_Boss2_BuffId1[2],0 )
			SetFubenData_Param(sceneId, x700089_CSP_BOSS2_FLAG, 2)
		end
	elseif boss2_flag == 2 then
		if nowTickCount - boss2_time > 12 then
			NpcTalk(sceneId, boss2, "�Ҹо�������ԴԴ���ϵ�ӿ��",  -1)
			CancelSpecificImpact(sceneId, boss2, x700089_g_Boss2_BuffId1[1])
			CancelSpecificImpact(sceneId, boss2, x700089_g_Boss2_BuffId1[2])
			SendSpecificImpactToUnit(sceneId, boss2,boss2,boss2, x700089_g_Boss2_BuffId2[1],0 )
			SendSpecificImpactToUnit(sceneId, boss2,boss2,boss2, x700089_g_Boss2_BuffId2[2],0 )
			SetFubenData_Param(sceneId, x700089_CSP_BOSS2_FLAG, 3)
		end
	elseif boss2_flag == 3 then
		if nowTickCount - boss2_time > 18 then
			NpcTalk(sceneId, boss2, "�Ҹо�������ԴԴ���ϵ�ӿ��",  -1)
			CancelSpecificImpact(sceneId, boss2, x700089_g_Boss2_BuffId2[1])
			CancelSpecificImpact(sceneId, boss2, x700089_g_Boss2_BuffId2[2])
			SendSpecificImpactToUnit(sceneId, boss2,boss2,boss2, x700089_g_Boss2_BuffId3[1],0 )
			SendSpecificImpactToUnit(sceneId, boss2,boss2,boss2, x700089_g_Boss2_BuffId3[2],0 )
			SetFubenData_Param(sceneId, x700089_CSP_BOSS2_FLAG, 4)
		end
	elseif boss2_flag == 4 then
		if nowTickCount - boss2_time > 24 then
			NpcTalk(sceneId, boss2, "�Ҹо�������ԴԴ���ϵ�ӿ��",  -1)
			CancelSpecificImpact(sceneId, boss2, x700089_g_Boss2_BuffId3[1])
			CancelSpecificImpact(sceneId, boss2, x700089_g_Boss2_BuffId3[2])
			SendSpecificImpactToUnit(sceneId, boss2,boss2,boss2, x700089_g_Boss2_BuffId4[1],0 )
			SendSpecificImpactToUnit(sceneId, boss2,boss2,boss2, x700089_g_Boss2_BuffId4[2],0 )
			SetFubenData_Param(sceneId, x700089_CSP_BOSS2_FLAG, 5)
		end
	elseif boss2_flag == 5 then
		if nowTickCount - boss2_time > 30 then
			NpcTalk(sceneId, boss2, "�Ҹо�������ԴԴ���ϵ�ӿ��",  -1)
			CancelSpecificImpact(sceneId, boss2, x700089_g_Boss2_BuffId4[1])
			CancelSpecificImpact(sceneId, boss2, x700089_g_Boss2_BuffId4[2])
			SendSpecificImpactToUnit(sceneId, boss2,boss2,boss2, x700089_g_Boss2_BuffId5[1],0 )
			SendSpecificImpactToUnit(sceneId, boss2,boss2,boss2, x700089_g_Boss2_BuffId5[2],0 )
			SetFubenData_Param(sceneId, x700089_CSP_BOSS2_FLAG, 6)
		end
	end
end

-- ��NPCʱ��DefaultEvent�� ����ӿڱ����С����ǲ������߼��� �պ���
function x700089_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nIndex)
end

-- ��������
function x700089_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	SetFubenData_Param(sceneId, x700089_CSP_AREA_ID, zoneId)
	if zoneId == 0 then  --����
		local BossId = GetFubenData_Param(sceneId, x700089_CSP_BOSS2_ID)
		if BossId ~= -1 then
			return --TEST
		end
		SetFubenData_Param(sceneId, x700089_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700089_g_MissionId, x700089_g_ScriptId,1)
		
	elseif zoneId == 1 then
	 	CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700089_g_MissionId, x700089_g_ScriptId)
	end
end

--�뿪����
function x700089_ProcAreaLeaved(sceneId, selfId, zoneId, MissionId)
	EnterAreaEventListHideNM(sceneId, selfId)
	SetFubenData_Param(sceneId, x700089_CSP_AREA_ID, -1)
end

--����ʱ��
---------------------------------------------------------------------------------------------------
function x700089_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	local zoneId = GetFubenData_Param(sceneId, x700089_CSP_AREA_ID )
	if zoneId == 0 then  --����
		local BossId = GetFubenData_Param(sceneId, x700089_CSP_BOSS2_ID)
		if BossId ~= -1 then
			return --TEST
		end
		local flag = GetFubenData_Param(sceneId, x700089_CSP_AREA_FLAG)
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700089_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700089_g_MissionId, x700089_g_ScriptId,1)
		
	elseif zoneId == 1 then
	 	--CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700089_g_MissionId, x700089_g_ScriptId)
	end
end

-- ����֪ͨ
function x700089_OnDie(sceneId, selfId, killerId)
	
	local objId1 = GetFubenData_Param(sceneId, x700089_CSP_BOSS1_ID)
	local objId2 = GetFubenData_Param(sceneId, x700089_CSP_BOSS2_ID)
	local objc1 = GetFubenData_Param(sceneId, x700089_CSP_BOSS_C_ID)
	local objc2 = GetFubenData_Param(sceneId, x700089_CSP_BOSS_C_ID+1)
	local objd = GetFubenData_Param(sceneId, x700089_CSP_BOSS_D_ID)
	local boss1_flag = GetFubenData_Param(sceneId, x700089_CSP_BOSS1_FLAG)


	local xianjinboss = GetFubenData_Param(sceneId, x700089_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	
	if objId1 == selfId then
		SetFubenData_Param(sceneId, x700089_CSP_BOSS1_ID, -1)
		--x700089_ShowTipsToAll(sceneId, "��¥������")
		
		if objId2 == -1 and boss1_flag == 2 then
			CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnFubuenCompleted", sceneId)
		end
	elseif objId2 == selfId then
		
		SetFubenData_Param(sceneId, x700089_CSP_BOSS2_ID, -1)
		x700089_ShowTipsToAll(sceneId, "���������ˣ�������ɣ����˳�������")
		
		x700089_OnFubenEnd(sceneId)
		
		-- ��ս��������
		CallScriptFunction(701116,"OnSceneBossDie", sceneId, 2)
		CallScriptFunction(701117,"OnSceneBossDie", sceneId, 2)
		
		if objId1 == -1 and boss1_flag == 2 then
			CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnFubuenCompleted", sceneId)
		end
	elseif objc1 == selfId then
		SetFubenData_Param(sceneId, x700089_CSP_BOSS_C_ID, -1)
	elseif objc2 == selfId then
		SetFubenData_Param(sceneId, x700089_CSP_BOSS_C_ID+1, -1)
	elseif objd == selfId then
		SetFubenData_Param(sceneId, x700089_CSP_BOSS_D_ID, -1)
	else
	
		local ret = x700089_IsMonsterB(sceneId, selfId)
		if ret ~= -1 then
			SetFubenData_Param(sceneId, ret, -1)
			x700089_ShowTipsToAll(sceneId, x700089_g_Talk_B)
			--NpcTalk(sceneId, nMonsterId, x700089_g_Talk_B,  -1)
			
			local playerId = x700089_GetAnyPlayer(sceneId)
			if playerId ~= -1 then
				local Num =  GetNearObjCount(sceneId, playerId, 10, 0, selfId)  
				
				local n = 1
				for i = 0, Num-1 do
					if n > 4 then
						break
					end
					
					local monsterId = GetNearMonster(sceneId, playerId,i)
					
					if x700089_IsMonsterA(sceneId, monsterId) ~= -1 then
						n = n+1
						SendSpecificImpactToUnit(sceneId, monsterId,monsterId,monsterId, x700089_g_MonsterB_BuffId,0 )
					end
				end
			end
			return
		end
	end
	
	local bCreateRandomboss = GetFubenData_Param(sceneId, x700089_B_CREATE_RANDOMBOSS)
	if bCreateRandomboss>0 then
		local nRandomBossId = GetFubenData_Param(sceneId, x700089_CSP_RANDOM_BOSS_ID)
		if nRandomBossId==selfId then
			--//--------------------------- ���纰�� Start--------------------
			--ɱ��Random boss
			
			
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
				strCountryName = "¥��"
			elseif nCountry==1 then
				strCountryName = "��ɽ"
			elseif nCountry==2 then
				strCountryName = "����"
			elseif nCountry==3 then
				strCountryName = "�ػ�"
			end

			local strHorseName = ""

			local nHorseFlag = GetFubenData_Param(sceneId, x700089_RANDOMBOSS_FLAG);
			local fubenlevel = GetFubenData_Param(sceneId, x700089_CSP_FUBENLEVEL )
			
			if fubenlevel < 50 then
				if nHorseFlag==0 then
					strHorseName = "�ױ�"
				elseif nHorseFlag==1 then
					strHorseName = "����"
				elseif nHorseFlag==2 then
					strHorseName = "���"
				elseif nHorseFlag==3 then
					strHorseName = "����"
				end
			elseif fubenlevel < 70 then
				if nHorseFlag==0 then
					strHorseName = "��ʨ"
				elseif nHorseFlag==1 then
					strHorseName = "ѱ¹"
				elseif nHorseFlag==2 then
					strHorseName = "���"
				elseif nHorseFlag==3 then
					strHorseName = "��Ϭ"
				end
			elseif fubenlevel < 80 then
				if nHorseFlag==0 then
					strHorseName = "���ݻ�"
				elseif nHorseFlag==1 then
					strHorseName = "��ţ"
				elseif nHorseFlag==2 then
					strHorseName = "���"
				elseif nHorseFlag==3 then
					strHorseName = "����"
				end
			elseif fubenlevel < 95 then
				if nHorseFlag==0 then
					strHorseName = "���"
				elseif nHorseFlag==1 then
					strHorseName = "Ӧ��"
				elseif nHorseFlag==2 then
					strHorseName = "����"
				elseif nHorseFlag==3 then
				strHorseName = "����"
				end
			elseif fubenlevel < 130 then
				if nHorseFlag==0 then
					strHorseName = "��"
				elseif nHorseFlag==1 then
					strHorseName = "�Ϸ�"
				elseif nHorseFlag==2 then
					strHorseName = "���"
				elseif nHorseFlag==3 then
					strHorseName = "����"
				end
			else
				if nHorseFlag==0 then
					strHorseName = "��"
				elseif nHorseFlag==1 then
					strHorseName = "�Ϸ�"
				elseif nHorseFlag==2 then
					strHorseName = "���"
				elseif nHorseFlag==3 then
					strHorseName = "����"
				end
			end


			local strMapName = "ӡ�Ⱥ�"
			
			LuaAllScenceM2Wrold (sceneId,strCountryName.."��"..strPlayerName.."�����"..strMapName.."�ľ��ս�񣬾�츶���"..strHorseName.."��Ķ��ӣ�", 5, 1)

		end
	end
end

--֪ͨ�������
function x700089_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId)

	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i)
		Msg2Player(sceneId, humanId, str, 8, 3)
	end
end

-- ����Boss 1
function x700089_CreateBoss1(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700089_CSP_FUBEN_TYPE )
	
    local fubenlevel = GetFubenData_Param(sceneId, x700089_CSP_FUBENLEVEL )

	local nIndexFrom = GetFubenDataPosByScriptID(x700089_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700089_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700089_g_ScriptId,nIndexFrom,i)
		if idScript == x700089_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 1 and flag3 == fubentype then
		
			local nRet = 0;
			if title ~="" then
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700089_g_ScriptId, -1, 21,-1,facedir, "",title)
			else
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700089_g_ScriptId, -1, 21,-1,facedir)
			end
			
			x700089_ShowTipsToAll(sceneId, "��¥�޺���ɹ�")
			--NpcTalk(sceneId, nRet, "��¥�޺���ɹ�",  -1)
			SetFubenData_Param(sceneId, x700089_CSP_BOSS1_ID, nRet )
        end
	end
end

-- ����Boss 2
function x700089_CreateBoss2(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700089_CSP_FUBEN_TYPE )
	
    local fubenlevel = GetFubenData_Param(sceneId, x700089_CSP_FUBENLEVEL )

	local nIndexFrom = GetFubenDataPosByScriptID(x700089_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700089_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700089_g_ScriptId,nIndexFrom,i)
		if idScript == x700089_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 2 and flag3 == fubentype then
		
			local nRet = 0;
			if title ~="" then
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700089_g_ScriptId, -1, 21,-1,facedir, "",title)
			else
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700089_g_ScriptId, -1, 21,-1,facedir)
			end
			
			local hp = GetHp(sceneId, nRet)
			SetFubenData_Param(sceneId, x700089_CSP_BOSS2_HP, hp )
			SetFubenData_Param(sceneId, x700089_CSP_BOSS2_ID, nRet )
        end
	end
end

--����Monster A
function x700089_CreateMonsterA(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700089_CSP_FUBEN_TYPE )
	
    local fubenlevel = GetFubenData_Param(sceneId, x700089_CSP_FUBENLEVEL )

	local nIndexFrom = GetFubenDataPosByScriptID(x700089_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700089_g_ScriptId )
	
	local idx = 0
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700089_g_ScriptId,nIndexFrom,i)
		if idScript == x700089_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 3 and flag3 == fubentype then
		
			for j=0,count -1 do

				local rx = random(-r,r)
				local x = x1 + rx
				local rz = random(-r,r)
				local z = z1 + rz
				
				local nRet = 0;
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700089_g_ScriptId, -1, 21,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700089_g_ScriptId, -1, 21,-1,facedir)
				end
				
				SetFubenData_Param(sceneId, x700089_CSP_MONSTER_A+idx, nRet )
				idx = idx + 1
			end
        end
	end
end

--����Monster B
function x700089_CreateMonsterB(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700089_CSP_FUBEN_TYPE )
	
    local fubenlevel = GetFubenData_Param(sceneId, x700089_CSP_FUBENLEVEL )

	local nIndexFrom = GetFubenDataPosByScriptID(x700089_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700089_g_ScriptId )
	
	local idx = 0
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700089_g_ScriptId,nIndexFrom,i)
		if idScript == x700089_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 4 and flag3 == fubentype then
		
			for j=0,count -1 do

				local rx = random(-r,r)
				local x = x1 + rx
				local rz = random(-r,r)
				local z = z1 + rz
				
				local nRet = 0;
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700089_g_ScriptId, -1, 21,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700089_g_ScriptId, -1, 21,-1,facedir)
				end
				
				SetFubenData_Param(sceneId, x700089_CSP_MONSTER_B+idx, nRet )
				idx = idx + 1
			end
        end
	end
end

--���� c
function x700089_CreateMonsterC(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700089_CSP_FUBEN_TYPE )
	
	local fubenlevel = GetFubenData_Param(sceneId, x700089_CSP_FUBENLEVEL )

	local nIndexFrom = GetFubenDataPosByScriptID(x700089_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700089_g_ScriptId )
	
	local idx = 0
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700089_g_ScriptId,nIndexFrom,i)
		if idScript == x700089_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 5 and flag3 == fubentype then
		
			for j=0,count -1 do

				local rx = random(-r,r)
				local x = x1 + rx
				local rz = random(-r,r)
				local z = z1 + rz
				local nRet = 0;
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700089_g_ScriptId, -1, 21,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700089_g_ScriptId, -1, 21,-1,facedir)
				end
				
				SetFubenData_Param(sceneId, x700089_CSP_BOSS_C_ID+idx, nRet )
				
				local hp = GetHp(sceneId, nRet)
				SetFubenData_Param(sceneId, x700089_CSP_BOSS_C_HP+idx, hp )
				idx = idx + 1
			end
        end
	end
end

--���� d
function x700089_CreateMonsterD(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700089_CSP_FUBEN_TYPE )
	
	local fubenlevel = GetFubenData_Param(sceneId, x700089_CSP_FUBENLEVEL )

	local nIndexFrom = GetFubenDataPosByScriptID(x700089_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700089_g_ScriptId )
	
	local idx = 0
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700089_g_ScriptId,nIndexFrom,i)
		if idScript == x700089_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and monsterFlag == 6 and flag3 == fubentype then
		
			for j=0,count -1 do

				local rx = random(-r,r)
				local x = x1 + rx
				local rz = random(-r,r)
				local z = z1 + rz
				
				local nRet = 0;
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700089_g_ScriptId, -1, 21,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700089_g_ScriptId, -1, 21,-1,facedir)
				end
				
				SetFubenData_Param(sceneId, x700089_CSP_BOSS_D_ID+idx, nRet )
				
				SetPatrolId(sceneId, nRet, 0)
				idx = idx + 1
			end
        end
	end
end

function x700089_GetAnyPlayer(sceneId)

	local humancount = GetFuben_PlayerCount(sceneId)
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i)
		playerId = GetFubenData_Param(sceneId, x700089_CSP_PLAYER_ENTER_START+i)
		if playerId ~= -1 and IsPlayerStateNormal(sceneId,playerId) == 1 then
			return playerId
		end
	end
	return -1
end

function x700089_IsMonsterA(sceneId, monsterId)
	for i = x700089_CSP_MONSTER_A, x700089_CSP_MONSTER_A+x700089_g_MonsterACount do
		local id = GetFubenData_Param(sceneId, i)
		if id ~= -1 and id == monsterId then
			return i
		end
	end
	
	return -1
end

function x700089_IsMonsterB(sceneId, monsterId)
	for i = x700089_CSP_MONSTER_B, x700089_CSP_MONSTER_B+x700089_g_MonsterBCount do
		local id = GetFubenData_Param(sceneId, i)
		if id ~= -1 and id == monsterId then
			return i
		end
	end
	
	return -1
end

function x700089_OnFubenEnd(sceneId)
	--x700089_CreateSubmitNpc(sceneId)
		--// add for �ֽ𸱱�
	x700089_CreateXianJinBoss(sceneId)
	 --// add end
	 
	x700089_CreateRandomMonster(sceneId)
	
	CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnFubuenCompleted", sceneId)
	
	local humancount = GetFuben_PlayerCount(sceneId);
	for ii = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, ii);
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,67 )
	end	
	--x700089_ShowTipsToAll(sceneId, "������ɣ����˳�������")
end

-- �������
function x700089_CreateSubmitNpc( sceneId)

	local npc = x700089_g_SubmitNPC
	
	if npc.title~= "" then
		CreateMonster(sceneId, npc.type, npc.x, npc.z, 3, 0, -1, npc.guid, -1,-1,npc.facedir, "", npc.title)
	else
		CreateMonster(sceneId, npc.type, npc.x, npc.z, 3, 0, -1, npc.guid, -1,-1,npc.facedir)
	end
end

--�����ֽ�boss
function x700089_CreateXianJinBoss(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700089_CSP_FUBEN_TYPE )
	if fubentype ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700089_CSP_FUBEN_MODE)

	if nFubenMode == 0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700089_CSP_FUBENLEVEL )
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700089_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700089_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700089_g_ScriptId,nIndexFrom,i)
		if idScript == x700089_g_ScriptId and monsterFlag == 7 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700089_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700089_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700089_CSP_XIANJINBOSS, nRet )
		end
	end

	x700089_ShowTipsToAll(sceneId, "����������֣�")
end

function x700089_CreateRandomMonster(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700089_CSP_FUBEN_TYPE )
	if fubentype ~= 0 then
		return
	end
	
	local rate = random(0,100)/100;
	local nStdRate = x700089_g_RandomMonsterRate
	local nFubenMode = GetFubenData_Param(sceneId, x700089_CSP_FUBEN_MODE)
	if nFubenMode ==1 then
		nStdRate = nStdRate*3
	end
	
	if(nFubenMode ~= 2) then
		if rate>= nStdRate then
			return 0
		end
	else
		rate = random(1,100)
		if(rate > x700089_g_RandomMonsterRateZHOUSANFAN) then
			return 0
		end
	end
	

	local nFlag = random(0,3)

	

	local fubenlevel = GetFubenData_Param(sceneId, x700089_CSP_FUBENLEVEL )
	local nIndexFrom = GetFubenDataPosByScriptID(x700089_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700089_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700089_g_ScriptId,nIndexFrom,i)
		
		if idScript == x700089_g_ScriptId and monsterFlag == 8+nFlag and levelmin <= fubenlevel and levelmax >= fubenlevel then
			local nBossID =0;
			if title~="" then
				nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700089_g_ScriptId, -1, 21,-1,facedir,  "",title)
			else
				nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700089_g_ScriptId, -1, 21,-1,facedir)
			
			end
			SetFubenData_Param(sceneId, x700089_B_CREATE_RANDOMBOSS, 1)
			SetFubenData_Param(sceneId, x700089_RANDOMBOSS_FLAG, nFlag)
			SetFubenData_Param(sceneId, x700089_CSP_RANDOM_BOSS_ID, nBossID)
		end
	end

	x700089_ShowTipsToAll(sceneId, "ս�����֣�")

end
