--ʦͽ����
x310304_g_ScriptId = 310304
x310304_g_MissionType = {
EnterPos = 1,
UseItem = 2,
KillMonster = 3
}
x310304_g_LookAtPosId = 82052
x310304_g_MissionId = {
{id = 9525,type = x310304_g_MissionType.EnterPos},
{id = 9526,type = x310304_g_MissionType.UseItem},
{id = 9527,type = x310304_g_MissionType.KillMonster}
}

x310304_g_UseItemPos = {
{id = 82053, x = 129, z = 228},
{id = 82054, x = 191, z = 220},
{id = 82055, x = 35, z = 162}
}
x310304_g_MissionName = "��ʦͽ��ʦͽ����"
x310304_g_areaId = 3
x310304_g_MasterDistance = 15
x310304_g_MissionItem = 12030029
x310304_g_FirstMissionId = x310304_g_MissionId[1].id
x310304_g_SecondMissionId = x310304_g_MissionId[2].id
x310304_g_ThirdMissionId = x310304_g_MissionId[3].id
x310304_g_LimitTimes = 1
x310304_g_Monster = {
{level = 50, monster = 3230},
{level = 55, monster = 3231},
{level = 60, monster = 3232},
{level = 65, monster = 3233},
{level = 70, monster = 3234},
{level = 75, monster = 3235},
{level = 80, monster = 3236}
}

x310304_g_MonsterAI = 6
x310304_g_MonsterAliveTime = 10*60*1000
x310304_g_GoodBadValue = 2000
x310304_g_ExpRate = 30000
function x310304_GetMonsterId(level)
	local id = -1
	for i, item in x310304_g_Monster do
		if level >= item.level then
			id = item.monster
		end
	end
	return id
end

function x310304_GetMissionTimes(sceneId, selfId)
	if GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3]) ~= GetDayOfYear() then
		return 0
	else
		return GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3])
	end
end

function x310304_HaveWhichMission(sceneId, selfId)
	for i, item in x310304_g_MissionId do
		if IsHaveQuestNM( sceneId, selfId, item.id ) == 1 then
			return item.id
		end
	end
	return -1
end

function x310304_HaveDoneWhichMission(sceneId, selfId)
	for i, item in x310304_g_MissionId do
		if IsHaveQuestNM( sceneId, selfId, item.id ) == 1 then
			local misIndex = GetQuestIndexByID( sceneId, selfId, item.id )
			if GetQuestParam( sceneId, selfId, misIndex, 7 ) == 1 then
				return item.id
			end
		end
	end
	return -1
end

function x310304_GetMissionType(sceneId, selfId)
	for i, item in x310304_g_MissionId do
		if IsHaveQuestNM( sceneId, selfId, item.id ) == 1 then
			return item.type
		end
	end
	return -1
end

function x310304_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	local level = GetLevel(sceneId, selfId)
	
	if level < 20 then
		return
	end
	MissionId = x310304_g_FirstMissionId
	local state = 8
	local haveMissionId = x310304_HaveWhichMission(sceneId, selfId)
	local haveDoneMissionId = x310304_HaveDoneWhichMission(sceneId, selfId)
	if haveMissionId > 0 then
		state = 6
		MissionId = haveMissionId
	end
	
	if haveDoneMissionId > 0 then
		state = 7
	end
	AddQuestNumText(sceneId, MissionId, x310304_g_MissionName, state, -1)
	
end

function x310304_GetMasterObjId(sceneId, selfId)
	if nil ~= x310304_IsMasterHere(sceneId, selfId) then
		return -1
	end
	local teamSize = GetTeamSize(sceneId, selfId)
	local nMasterObjId = -1
	for i = 0, teamSize - 1 do
		local targetId = GetTeamMemberId(sceneId, selfId, i)
		if 1 == IsInDist(sceneId, selfId, targetId, x310304_g_MasterDistance) then
			if 1 == GetObjType(sceneId, targetId) and 1 == IsMaster(sceneId, selfId, targetId) then
				nMasterObjId = targetId
			end
		end
	end
	
	return nMasterObjId
	
end

function x310304_IsMasterHere(sceneId, selfId)
	local teamSize = GetTeamSize(sceneId, selfId)
	if (teamSize < 2) then
		return "��Ķ����в���2�ˣ��޷����б�����";
	end
	
	local isMasterHere = 0
	for i = 0, teamSize - 1 do
		local targetId = GetTeamMemberId(sceneId, selfId, i)
		if 1 == IsInDist(sceneId, selfId, targetId, x310304_g_MasterDistance) then
			if 1 == GetObjType(sceneId, targetId) and 1 == IsMaster(sceneId, selfId, targetId) then
				isMasterHere = 1
			end
		end
	end
	
	if 0 == isMasterHere then
		return "���ʦ�����ڶ����л��߲��ڸ������޷����б�����";
	end
	return nil
end

function x310304_IsCanSubmit( sceneId, selfId )
	local teamSize = GetTeamSize(sceneId, selfId)
	if (teamSize < 2) then
		return "��Ķ����в���2�ˣ��޷��ύ������";
	end
	
	local isMasterHere = 0
	for i = 0, teamSize - 1 do
		local targetId = GetTeamMemberId(sceneId, selfId, i)
		if 1 == IsInDist(sceneId, selfId, targetId, x310304_g_MasterDistance) then
			if 1 == GetObjType(sceneId, targetId) and 1 == IsMaster(sceneId, selfId, targetId) then
				isMasterHere = 1
			end
		end
	end
	
	if 0 == isMasterHere then
		return "���ʦ�����ڶ����л��߲��ڸ������޷��ύ������";
	end
	return nil
end

function x310304_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )
	local haveMissionId = x310304_HaveWhichMission(sceneId, selfId)
	local haveDoneMissionId = x310304_HaveDoneWhichMission(sceneId, selfId)
	if haveDoneMissionId > 0 then
		local str = x310304_IsCanSubmit( sceneId, selfId )
		if str ~= nil then
			Msg2Player(sceneId,selfId,str,8,2)
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return
		end
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"\t��ϲ���������ʦͽ����")
		local exp = x310304_CalculateExp(sceneId, selfId)
		local szAward = "\n#Y�������ݣ�\n#W����ֵ:"..exp.."��"
		AddQuestText(sceneId, szAward)
		EndQuestEvent()
		DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x310304_g_ScriptId, MissionId);
		return
	end
	if haveMissionId > 0 then
		BeginQuestEvent(sceneId)
		if x310304_g_MissionType.EnterPos == x310304_GetMissionType(sceneId, selfId) then
			AddQuestText(sceneId,"#Y��ô��ͻ����ˣ�����һ����û����������")
		else
			AddQuestText(sceneId,"#Y�㻹û���������")
		end
		EndQuestEvent()
		DispatchQuestDemandInfo(sceneId, selfId, targetId, x310304_g_ScriptId, MissionId,0);
	  return
	end
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"#Yʦͽ����")
	local str = format("\t�ܸ�������ʦͽ������һ���������\n\t������������в��ٵ��˳�û���д���˵����Щ������ʵ�����˺��������Ĺƻ�Ż�ƵƵ���ҡ�\n\tΪ��Ū�����࣬����ʦͽ����ǰȥ���һ����Σ�\n\tʦ���������������ͽ�ܻ�þ��齱����ʦ��ÿ��1��ͽ��������񶼻���%s������ͽ��ÿ��ֻ�ɽ�%s������ʦ��û�����񣬵�ʦ��������ͽ����ߣ�ͽ�ܲ��ܽ�������", x310304_g_GoodBadValue, x310304_g_LimitTimes)
	AddQuestText(sceneId,str)
	AddQuestText(sceneId,"#Y����Ŀ�꣺")
	local target = "\t#W��ʥɽ��´���о���Ȼ��ʹ�����̲�ɱ��ͷ�졣"
	AddQuestText(sceneId,target)
	AddQuestText(sceneId,"#Y��������")
	local exp = x310304_CalculateExp(sceneId, selfId)
	AddQuestText(sceneId,format("\t#Wͽ�ܻ�þ��飺ͽ�ܵȼ�*%s��", x310304_g_ExpRate))
	AddQuestText(sceneId,format("\t#Wʦ�����������%s��", x310304_g_GoodBadValue))
	EndQuestEvent()

	DispatchQuestInfo(sceneId, selfId, targetId, x310304_g_FirstMissionId, -1)
end

function x310304_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	local str = x310304_DoAccept( sceneId, selfId )
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return
	end
	
	local masterObjId = x310304_GetMasterObjId(sceneId, selfId)
	local szPrenticeName = GetName(sceneId, selfId)
	local szMsg = format("%s������ʦͽ��������Э��������񣬻�������������", szPrenticeName)
	
	Msg2Player(sceneId, masterObjId, szMsg, 8, 2)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, szMsg);
	EndQuestEvent();
	DispatchQuestTips(sceneId, masterObjId);
	
end

function x310304_DoAccept( sceneId, selfId )
	
	local level = GetLevel(sceneId, selfId)
	
	if level >= 50 and 0 >= IsHavePrentice(sceneId, selfId) then
		return "�㻹����ʦ��,����ͽ��֮���������Ұɡ�"
	end
	
	if 1 == IsHavePrentice(sceneId, selfId) then
		return "�������ͽ������ȡ������";
	end
	
	local teamSize = GetTeamSize(sceneId, selfId)
	if (teamSize < 2) then
		return "��Ķ����в���2�ˣ��޷���ȡ������";
	end
	
	local isMasterHere = 0
	for i = 0, teamSize - 1 do
		local targetId = GetTeamMemberId(sceneId, selfId, i)
		if 1 == IsInDist(sceneId, selfId, targetId, x310304_g_MasterDistance) then
			if 1 == GetObjType(sceneId, targetId) and 1 == IsMaster(sceneId, selfId, targetId) then
				isMasterHere = 1
			end
		end
	end
	
	if 0 == isMasterHere then
		return "���ʦ�����ڶ����л��߲��ڸ������޷���ȡ������";
	end
	
	if IsQuestFullNM(sceneId, selfId) == 1 then
		return "�ܱ�Ǹ����������Ѿ����ˣ��޷���ȡ������"
	end
	
	if x310304_GetMissionTimes(sceneId, selfId) >= x310304_g_LimitTimes then
		return format("�ܱ�Ǹ�����յ���������Ѿ��ﵽ%s�Σ��޷���ȡ������", x310304_g_LimitTimes)
	end
	local errorCode = AddQuestNM( sceneId, selfId, x310304_g_FirstMissionId )
	if errorCode ~= 1 then
		return "�������ʧ�ܣ�"
	end
	
	if GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3]) ~= GetDayOfYear() then
		SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3], GetDayOfYear())
		SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3], 1)
	else
		local times = GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3])
		times = times + 1
		SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3], times)
	end
	
	GamePlayScriptLog(sceneId, selfId, 1291)
	return nil
end

function x310304_CalculateExp(sceneId, selfId)
	local level = GetLevel(sceneId, selfId)
	local exp = level * x310304_g_ExpRate
	return exp
end

function x310304_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	local haveMissionId = x310304_HaveWhichMission(sceneId, selfId)
	local missionType = x310304_GetMissionType(sceneId, selfId)
	if missionType < 0 then
		return
	end
	
	local str = x310304_IsCanSubmit( sceneId, selfId )
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return
	end
	
	if x310304_g_MissionType.KillMonster == missionType then
		
		if GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3]) ~= GetDayOfYear() then
			SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3], GetDayOfYear())
			SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3], 1)
		end
		
		DelQuestNM( sceneId, selfId, haveMissionId )
		--ʦ������
		local masterObjId = x310304_GetMasterObjId(sceneId, selfId)
		local value = GetPlayerGoodBadValue(sceneId, masterObjId)
		value = value + x310304_g_GoodBadValue
		SetPlayerGoodBadValue(sceneId, masterObjId, value)
		local str = format("���ͽ���������������%d��������", x310304_g_GoodBadValue)
		Msg2Player(sceneId,masterObjId,str,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, masterObjId);
		--ͽ�ܽ���
		local exp = x310304_CalculateExp(sceneId, selfId)
		AddExp(sceneId, selfId, exp);
		str = format("���������������%d�㾭��Ľ�����", exp)
		Msg2Player(sceneId,selfId,str,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		GamePlayScriptLog(sceneId, selfId, 1292)
	else
		DelQuestNM( sceneId, selfId, haveMissionId )
		AddQuestNM( sceneId, selfId, x310304_g_SecondMissionId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, x310304_g_SecondMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		SetQuestByIndex( sceneId, selfId, misIndex, 6, random(1,3) )
	end
end

function x310304_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
		return
	end
	
end

function x310304_ProcAreaEntered( sceneId, selfId, areaId, MissionId )
	if areaId ~= x310304_g_areaId then
		return
	end
	local misIndex
	local missionType = x310304_GetMissionType(sceneId, selfId)
	local missionId = x310304_HaveWhichMission(sceneId, selfId)
	if missionType == x310304_g_MissionType.EnterPos then
		misIndex = GetQuestIndexByID( sceneId, selfId, missionId )
		if 1 == GetQuestParam( sceneId, selfId, misIndex, 7 ) then
			return
		end
		
		local ret = x310304_IsMasterHere(sceneId, selfId)
		if nil ~= ret then
			Msg2Player(sceneId,selfId,ret,8,2)
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, ret);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return
		end
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )
	else
		return
	end
	
	if missionId > 0 and 1 ~= GetQuestParam( sceneId, selfId, misIndex, 7 ) then
		
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
		local str = "#Y�����ϣ������ύ�����ˡ�"
		Msg2Player(sceneId,selfId,str,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
	end
end

function x310304_ProcTiming( sceneId, selfId )

end

--����뿪һ�� area ʱ����
function x310304_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )

end

function x310304_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId, nChangeType)
	if MissionId == nil or MissionId < 0 then
      return
  end
  
  if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
      return
  end
  
  if itemdataId ~= x310304_g_MissionItem then
  	return
  end
  
  local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
  if 1 == nChangeType then --ɾ����Ʒ
  	if x310304_g_MissionType.UseItem == GetQuestParam( sceneId, selfId, misIndex, 6 ) then
			SetQuestByIndex( sceneId, selfId, misIndex, 6, GetQuestParam( sceneId, selfId, misIndex, 6 ) - 1 )
		end
  else
		if x310304_g_MissionType.BuyItem == GetQuestParam( sceneId, selfId, misIndex, 6 ) then
			SetQuestByIndex( sceneId, selfId, misIndex, 6, GetQuestParam( sceneId, selfId, misIndex, 6 ) + 1 )
		end
	end
	
end

function x310304_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	local haveMissionId = x310304_HaveWhichMission(sceneId, selfId)
	local missionType = x310304_GetMissionType(sceneId, selfId)
	
	if haveMissionId <= 0 then
		return
	end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, haveMissionId )
	
	if x310304_g_MissionType.UseItem ~= missionType and x310304_g_MissionType.KillMonster ~= missionType then
		return
	end
	
	if x310304_g_MissionType.KillMonster == missionType and GetQuestParam( sceneId, selfId, misIndex, 7 ) == 1 then
		return
	end
	
	local scene = 50
	local nCountry = GetCurCountry(sceneId,selfId)
	if 100*nCountry+scene ~= sceneId then --û���ҵ����������Ϣ
		return 0
	end
	local posIndex = GetQuestParam( sceneId, selfId, misIndex, 6 )
	local posx = x310304_g_UseItemPos[posIndex].x
	local posz = x310304_g_UseItemPos[posIndex].z
	local radii = 10
	
	local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )
	
	if posx > 0 then --��Ҫ���ص�
		local distanceRet = radii * radii - (posx - PlayerPosX) * (posx - PlayerPosX) - (posz - PlayerPosZ) * (posz - PlayerPosZ)
		if distanceRet <= 0 then
			local strText = format("�ܱ�Ǹ�����ﲻ��ʹ�ø���Ʒ���뵽@sceneid_%d(%d,%d)��ʹ��!", sceneId, posx, posz )
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText)
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId, selfId)
			return 0
		end
	end
	
	local ret = x310304_IsMasterHere(sceneId, selfId)
	if nil ~= ret then
			Msg2Player(sceneId,selfId,ret,8,2)
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, ret);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return
	end

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, "ǰ����������Ŀ��")
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId, selfId)
	
	local masterObjId = x310304_GetMasterObjId(sceneId, selfId)
	local masterLevel = GetLevel(sceneId, masterObjId)
	local monsterId = x310304_GetMonsterId(masterLevel)
	
	if monsterId > 0 then
	CreateMonster(sceneId, monsterId, PlayerPosX , PlayerPosZ, x310304_g_MonsterAI, -1, -1, -1, 21, x310304_g_MonsterAliveTime);
	end
	--ɾ����Ʒ
	EraseItem(sceneId, selfId, BagIndex)

	--����Ч��
	if impactId ~= -1 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, impactId, 0);
	end
	
	if x310304_g_MissionType.UseItem == missionType then
		DelQuestNM( sceneId, selfId, haveMissionId )
		AddQuestNM( sceneId, selfId, x310304_g_ThirdMissionId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, x310304_g_ThirdMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, monsterId )
		SetQuestByIndex( sceneId, selfId, misIndex, 6, posIndex )
	elseif x310304_g_MissionType.KillMonster == missionType then
		SetQuestByIndex( sceneId, selfId, misIndex, 5, monsterId )
	end
	
	return 1
end

function x310304_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	
	local HumanNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
	for i = 0, HumanNum-1 do
		local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
    if humanObjId ~= -1 then
    	local haveMissionId = x310304_HaveWhichMission(sceneId, humanObjId)
    	local missionType = x310304_GetMissionType(sceneId, humanObjId)
    	if IsPlayerStateNormal(sceneId, humanObjId) > 0 and GetHp(sceneId, humanObjId) > 0 and haveMissionId > 0 and x310304_g_MissionType.KillMonster == missionType then	--��������ӵ������
					local misIndex = GetQuestIndexByID( sceneId, humanObjId, haveMissionId )
					if GetQuestParam( sceneId, humanObjId, misIndex, 5 ) == objdataId then
						local ret = x310304_IsMasterHere(sceneId, humanObjId)
						if nil ~= ret then
							Msg2Player(sceneId,humanObjId,ret,8,2)
							BeginQuestEvent(sceneId);
							AddQuestText(sceneId, ret);
							EndQuestEvent();
							DispatchQuestTips(sceneId, humanObjId);
						else
							SetQuestByIndex( sceneId, humanObjId, misIndex, 0, 1 )
							SetQuestByIndex( sceneId, humanObjId, misIndex, 7, 1 )
						end
					end
			end
    end
  end
	
end

function x310304_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	local szMissionTarget = ""
	local szAward = ""
	local missionType = x310304_GetMissionType(sceneId, selfId)
	local missionId = x310304_HaveWhichMission(sceneId, selfId)
	if missionType == x310304_g_MissionType.EnterPos then
		local misIndex = GetQuestIndexByID( sceneId, selfId, missionId )
		local curNum = GetQuestParam( sceneId, selfId, misIndex, 0 )
		local szTarget1 = format("  ��ʥɽ��´@npc_%s",x310304_g_LookAtPosId)
		szMissionTarget = szTarget1.." �� "..curNum.." / 1"
	elseif missionType == x310304_g_MissionType.UseItem then
		local misIndex = GetQuestIndexByID( sceneId, selfId, missionId )
		local curNum = 0
		local posIndex = GetQuestParam( sceneId, selfId, misIndex, 6 )
		local szTarget1 = format("  ������#G�ӻ���#W�������̺�ȥָ���ص�ʹ��@item_%s@npc_%s",x310304_g_MissionItem,x310304_g_UseItemPos[posIndex].id)
		szMissionTarget = szTarget1.." �� "..curNum.." / 1"
	elseif missionType == x310304_g_MissionType.KillMonster then
		local misIndex = GetQuestIndexByID( sceneId, selfId, missionId )
		local curNum = GetQuestParam( sceneId, selfId, misIndex, 0 )
		local szTarget1 = format("  ɱ���о�ͷĿ")
		szMissionTarget = szTarget1.." �� "..curNum.." / 1"
	end
	local exp = x310304_CalculateExp(sceneId, selfId)
	szAward = "#W\n#Y�������ݣ�\n#W����ֵ:"..exp.."��"
	BeginQuestEvent(sceneId)

	AddQuestLogCustomText( sceneId,
							"",						-- ����
							"",        -- ��������
							szMissionTarget,		--����Ŀ��
							"",			--����NPC
							szAward,               --������
							"",	--��������
							""					--����С��ʾ
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
end

function x310304_ProcQuestAbandon(sceneId, selfId, MissionId)

	DelQuestNM( sceneId, selfId, MissionId )
	
	local message = "��������ʦͽ����"
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 4, 2);
	
	if GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3]) ~= GetDayOfYear() then
		SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3], GetDayOfYear())
		SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3], 1)
	end
end