
--MisDescBegin
x300352_g_ScriptId = 300352
x300352_g_LevelLess = 40
--MisDescEnd

x300352_g_FatherMissionId = SPOUSE_TASK[2]
x300352_g_FatherMissionName = "����������"
x300352_g_MissionId = SPOUSE_TASK[3]
x300352_g_MissionName ="����������"
x300352_g_MissionItem = 13080010

function x300352_IsMissionComplete(sceneId, selfId, MissionId) 
  local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
  return GetQuestParam( sceneId, selfId, misIndex, 7 )
end

function x300352_SetMissionComplete(sceneId, selfId, MissionId) 
  local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
  SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
end


function x300352_SetMissionData(sceneId, selfId)
		SetQuestData(sceneId, selfId, MD_SPOUSE_MISSION_DATE[1][1], MD_SPOUSE_MISSION_DATE[1][2], MD_SPOUSE_MISSION_DATE[1][3], GetDayOfYear())
end

function x300352_SubmitFatherMissionCheck(sceneId, selfId, NPCId)
	local teamSize = GetTeamSize(sceneId, selfId)
	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	if HasTeam(sceneId, selfId) ~= 1 then
		return "�ܱ�Ǹ������δ��������޷��ύ������"
	end
	
	if (GetTeamSize(sceneId, selfId) < 2) then
		return "�ܱ�Ǹ�������ڵĶ����г�ԱС��2�ˣ��޷��ύ������";
	end
	
	if (GetTeamSize(sceneId, selfId) > 2) then
		return "�ܱ�Ǹ�������ڵĶ����г�Ա����2�ˣ��޷��ύ������";
	end
	
	if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
		return "�ܱ�Ǹ��������ż������Ч�ľ����ڣ��޷����б�����";
	end
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return "�ܱ�Ǹ�������ڵĶ����г�Ա���Ƿ��޹�ϵ���޷��ύ������";
	end		
	
	if IsHaveQuestNM( sceneId, selfId, x300352_g_FatherMissionId ) ~= 1 then
		return "��û�б������޷��ύ������"
	end
	
	if IsHaveQuestNM( sceneId, targetId, x300352_g_FatherMissionId ) ~= 1 then
		return "������żû�б������޷��ύ������"
	end
	
	if GetSex(sceneId, selfId) == 0 then
		return "�ܱ�Ǹ��ֻ�����Բ����ύ������";
	end
	
	local BusID  =  GetBusId(sceneId, selfId)
	if BusID == -1 then
		return "������ż�����ͣ�����������ż���ύ��";
	end
	if IsInDist(sceneId, selfId, BusID, 10) ~= 1 then
		return "�����������͵ĺ�̫ͯԶ�ˣ�����·�ˣ�����ԭ�ص�����";
	end
		
	return nil
end

function x300352_DoUseItem( sceneId, selfId )
	if HasTeam(sceneId, selfId) ~= 1 then
		return "�ܱ�Ǹ������δ��������ż����޷�ʹ�ñ���Ʒ��"
	end
	
	if (GetTeamSize(sceneId, selfId) < 2) then
		return "�ܱ�Ǹ�������ڵĶ����г�ԱС��2�ˣ��޷�ʹ�ñ���Ʒ��";
	end
	
	if (GetTeamSize(sceneId, selfId) > 2) then
		return "�ܱ�Ǹ�������ڵĶ����г�Ա����2�ˣ��޷�ʹ�ñ���Ʒ��";
	end

	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
		return "�ܱ�Ǹ��������һ�벻�ڸ���������ʹ�ø���Ʒ��";
	end
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return "�ܱ�Ǹ�������ڵĶ����г�Ա���Ƿ��޹�ϵ���޷�ʹ�ñ���Ʒ��";
	end		
	
	return nil
end

function x300352_AcceptCheck( sceneId, selfId )
	local week = GetWeek()
	local teamSize = GetTeamSize(sceneId, selfId)
	if week ~= 4 and week ~= 6 then
		return "ֻ�����ġ����������ܽ��б�����"
	end
	
	if HasTeam(sceneId, selfId) ~= 1 then
		return "�ܱ�Ǹ������δ�����������ȡ������"
	end
	
	if (GetTeamSize(sceneId, selfId) < 2) then
		return "�ܱ�Ǹ�������ڵĶ����г�ԱС��2�ˣ��޷���ȡ������";
	end
	
	if (GetTeamSize(sceneId, selfId) > 2) then
		return "�ܱ�Ǹ�������ڵĶ����г�Ա����2�ˣ��޷���ȡ������";
	end

	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
		return "�ܱ�Ǹ��������ż������Ч�ľ����ڣ��޷����б�����";
	end
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return "�ܱ�Ǹ�������ڵĶ����г�Ա���Ƿ��޹�ϵ���޷���ȡ������";
	end		
	
	local bHaveMission = IsHaveQuest(sceneId, targetId, x300352_g_MissionId)
	if bHaveMission == 1 then
		return "������ż��" .. x300352_g_MissionName .. "���޷���ȡ������"
	end
	
	bHaveMission = IsHaveQuest(sceneId, selfId, x300352_g_MissionId)
	if bHaveMission == 1 then
		return "����" .. x300352_g_MissionName .. "���޷���ȡ������"
	end
	
	local BusID  =  GetBusId(sceneId, selfId)
	if BusID == -1 then
		return "���������ͣ������޷���ȡ����" .. x300352_g_MissionName
	else
		if 0 >= IsValidMyselfBus(sceneId, selfId, x300352_g_FatherMissionId) then
			return "�����͵�Ŀ�겻�ڸ������޷���ȡ������"
		end
	end
	
	
	
	
	
	BeginAddItem(sceneId)
  AddItem( sceneId, x300352_g_MissionItem, 1 )
  local ret = EndAddItem(sceneId,selfId)
  if ret <= 0 then
  		return "����Ʒ��������������"
  end
  
  BeginAddItem(sceneId)
  AddItem( sceneId, x300352_g_MissionItem, 1 )
  ret = EndAddItem(sceneId,targetId)
  if ret <= 0 then
  		return "����ż����Ʒ��������������ż��Ҫ������Ʒ����"
  end                 
  
	return nil
end

function x300352_DoAccept( sceneId, selfId )
	
	local week = GetWeek()
	
	if week ~= 4 and week ~= 6 then
		return "ֻ�����ġ����������ܽ��б�����"
	end
	
	if HasTeam(sceneId, selfId) ~= 1 then
		return "�ܱ�Ǹ������δ�����������ȡ������"
	end
	
	if (GetTeamSize(sceneId, selfId) < 2) then
		return "�ܱ�Ǹ�������ڵĶ����г�ԱС��2�ˣ��޷���ȡ������";
	end
	
	if (GetTeamSize(sceneId, selfId) > 2) then
		return "�ܱ�Ǹ�������ڵĶ����г�Ա����2�ˣ��޷���ȡ������";
	end

	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
		return "�ܱ�Ǹ��������ż������Ч�ľ����ڣ��޷����б�����";
	end
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return "�ܱ�Ǹ�������ڵĶ����г�Ա���Ƿ��޹�ϵ���޷���ȡ������";
	end		
	
	local today = GetDayOfYear()
	
	for i = 0, teamSize - 1 do
		local targetId = GetNearTeamMember(sceneId, selfId, i)
		local completeDay = GetQuestData(sceneId, targetId, MD_SPOUSE_MISSION_DATE[1][1], MD_SPOUSE_MISSION_DATE[1][2],MD_SPOUSE_MISSION_DATE[1][3])
		if( completeDay == today) then
			return "��������������ȡ�˱����񣬽����޷���ȡ������"
		end
	end
	
	local bHaveMission = IsHaveQuest(sceneId, selfId, x300352_g_MissionId)
	if bHaveMission == 1 then
		return "���Ѿ���ȡ�˱����񣬿�ȥ��ɰɡ�"
	end
	
	for i = 0, teamSize - 1 do
		local targetId = GetNearTeamMember(sceneId, selfId, i)
		local bHaveMission = IsHaveQuest(sceneId, targetId, x300352_g_MissionId)
		if bHaveMission == 1 then
			return "�������������б������޷���ȡ������"
		end
	end

	for i = 0, teamSize - 1 do
		local aId = GetNearTeamMember(sceneId, selfId, i)
		local aName = GetName(sceneId, aId)
		local errorCode = AddQuestNM( sceneId, aId, x300352_g_MissionId )
		if errorCode ~= 1 then
			Msg2Player(sceneId,selfId,"�������ʧ�ܣ�",8,2)
		end
	end

	return nil
end

--**********************************

--������ں���

--**********************************

function x300352_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )
	local retCode = x300352_SubmitFatherMissionCheck(sceneId, selfId, targetId)
	if retCode ~= nil then
		Msg2Player(sceneId,selfId,retCode,8,2)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, retCode);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
		--BeginQuestEvent(sceneId)
		--AddQuestText(sceneId,retCode)
		--EndQuestEvent()
		--DispatchQuestDemandInfo(sceneId, selfId, targetId, x300352_g_ScriptId, MissionId,0);
		--return
	end
	
	BeginQuestEvent(sceneId)
--������Ϣ
	AddQuestText(sceneId,"")
	AddQuestText(sceneId,"")

	--����Ŀ��
	AddQuestText(sceneId,"")
	AddQuestText(sceneId,"#Y�����ޡ����ͺ�ͯ#W#r\tлл���ǰѰ����ͻ�����һ·�������ˡ�#r\t������û��ʲôϡ�������������ҴӲ�˹�����ģ�@item_13080010#W��������ȥ���м��ȼ��������һ��һ����ϲ���ģ�")

	EndQuestEvent()
  DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300352_g_ScriptId, x300352_g_MissionId);
end

--**********************************

--�о��¼�

--**********************************
--5	��ѭ������	δ��	1
--6	��ѭ��/ѭ������	δ���	2
--7	��ѭ������	�����	3
function x300352_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsMarried(sceneId, selfId) ~= 1 then
		return
	end
	if IsHaveQuestNM( sceneId, selfId, x300352_g_FatherMissionId ) == 1 then
		AddQuestNumText(sceneId, x300352_g_ScriptId, x300352_g_FatherMissionName, 7, -1)
	end
	
end



--**********************************

--����������

--**********************************

function x300352_ProcAcceptCheck(sceneId, selfId, NPCId)

	--if HasTeam(sceneId, selfId) == 1 then
		return 1
	--end
end

--**********************************

--����

--**********************************
function x300352_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	local str = x300352_DoAccept( sceneId, selfId )
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,8,2)
	end
	
end



--**********************************

--����

--**********************************

function x300352_ProcQuestAbandon(sceneId, selfId, MissionId)
	DelQuestNM( sceneId, selfId, MissionId )
	
	--local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
	local message = "�������˷�������"
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 4, 2);
	
	DelItem(sceneId, selfId,x300352_g_MissionItem,1)
	
	x300352_SetMissionData(sceneId, selfId)
	
	--����ִ���ʼ�����ż
	local spouseGuid = GetSpouseGUID( sceneId, selfId )
	local spouseName = GetFriendName( sceneId, selfId, tonumber(spouseGuid) )
	SendScriptMail( sceneId, spouseName, MAIL_DELETE_MISSION, x300352_g_MissionId, 0, 0, selfId )
	
end



--**********************************

--����Ƿ�����ύ

--**********************************

function x300352_CheckSubmit( sceneId, selfId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then
		return 0;
	end
	return 1
end



--**********************************

--�ύ

--**********************************
function x300352_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	local submitRetCode = x300352_SubmitFatherMissionCheck(sceneId, selfId, targetId)
	if submitRetCode ~= nil then
		Msg2Player(sceneId,selfId,submitRetCode,8,2)
		return
	end
	
	local retCode = x300352_AcceptCheck(sceneId, selfId)
	if retCode ~= nil then
		Msg2Player(sceneId,selfId,retCode,8,2)
		return
	end

	local spouseId = GetTeamSceneMember(sceneId, selfId, 0);
	
	x300352_SetMissionComplete(sceneId, selfId, x300352_g_FatherMissionId )
	x300352_SetMissionComplete(sceneId, spouseId, x300352_g_FatherMissionId )
	local ret = x300352_IsMissionComplete( sceneId, selfId, x300352_g_FatherMissionId )
	if ret > 0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�����������:�����ޡ����ͺ�ͯ");
		EndQuestEvent();
		Msg2Player(sceneId,selfId,"�����������:�����ޡ����ͺ�ͯ",8,2)
		DispatchQuestTips(sceneId, selfId);
		
		DelQuestNM( sceneId, selfId, x300352_g_FatherMissionId )
		local errorCode = AddQuestNM( sceneId, selfId, x300352_g_MissionId )
		if errorCode ~= 1 then
			Msg2Player(sceneId,selfId,"�������ʧ�ܣ�",8,2)
		end
	end

	ret = x300352_IsMissionComplete( sceneId, spouseId, x300352_g_FatherMissionId )
	if ret > 0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�����������:�����ޡ����ͺ�ͯ");
		EndQuestEvent();
		Msg2Player(sceneId,spouseId,"�����������:�����ޡ����ͺ�ͯ",8,2)
		DispatchQuestTips(sceneId, spouseId);
		
		DelQuestNM( sceneId, spouseId, x300352_g_FatherMissionId )
		local errorCode = AddQuestNM( sceneId, spouseId, x300352_g_MissionId )
		if errorCode ~= 1 then
			Msg2Player(sceneId,spouseId,"�������ʧ�ܣ�",8,2)
		end
	end

	local BusID  =  GetBusId(sceneId, selfId)
	if BusID ~= -1 then
		if (IsObjValid (sceneId,BusID) == 1) and x300352_g_FatherMissionId == GetBusQuestID(sceneId, BusID ) then
			DeleteBus(sceneId, BusID,1)
		end
	end

	BeginAddItem(sceneId)
  AddItem( sceneId, x300352_g_MissionItem, 1 )
  local ret = EndAddItem(sceneId,selfId)
  if ret > 0 then
      AddItemListToPlayer(sceneId,selfId)
  end
  
  BeginAddItem(sceneId)
  AddItem( sceneId, x300352_g_MissionItem, 1 )
  ret = EndAddItem(sceneId,spouseId)
  if ret > 0 then
      AddItemListToPlayer(sceneId,spouseId)
  end
  
	return 0
	
end



--**********************************

--ɱ����������

--**********************************

function x300352_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

--**********************************

--���߸ı�

--**********************************

function x300352_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
end

function x300352_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
		return
	end
	
end

function x300352_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	if IsHaveQuestNM( sceneId, selfId, x300352_g_MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300352_g_MissionId )
	if GetQuestParam( sceneId, selfId, misIndex, 1 ) == 1 then
		return 0
	end
	
	local scene = 0
	local posx = 127
	local posz = 127
	local radii = 10
	if scene == -1 or sceneId ~= scene then --û���ҵ����������Ϣ
		return 0
	end
	
	if posx > 0 then --��Ҫ���ص�
		local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )

		local distanceRet = radii * radii - (posx - PlayerPosX) * (posx - PlayerPosX) - (posz - PlayerPosZ) * (posz - PlayerPosZ)
		if distanceRet <= 0 then
			local strText = format("�ܱ�Ǹ�����ﲻ��ʹ�ø���Ʒ���뵽@sceneid_%d(%d,%d)��ʹ��!", scene, posx, posz )
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText)
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId, selfId)
			return 0
		end
	end
	
	local retCode = x300352_DoUseItem(sceneId, selfId)
	if retCode ~= nil then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, retCode)
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			return
	end

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, "������ų��������̻�")
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId, selfId)
	
	--ɾ����Ʒ
	EraseItem(sceneId, selfId, BagIndex)

	--����Ч��
	if impactId ~= -1 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, impactId, 0);
	end
	
	SetQuestByIndex( sceneId, selfId, misIndex, 1, 1 )
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300352_g_MissionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )

	return 1
	
end

function x300352_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x300352_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x300352_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x300352_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x300352_QuestLogRefresh( sceneId, selfId, MissionId)

	BeginQuestEvent(sceneId)	
	local level = GetLevel(sceneId, selfId)
	local ExpBonus = 1000 *0.4*10* level
	    if ExpBonus > 0 then
			AddQuestExpBonus(sceneId,  ExpBonus);
		end	
	AddQuestLogCustomText( sceneId,
							"����",						-- ����
							"" .. x300352_g_MissionName,        -- ��������
							"  ȥ@npc_72049��ȼ��",		--����Ŀ��
							"@npc_139117",			--����NPC
							"",               --������
							"�����@npc_72049���������İ���һ�����������ӳ�񻨺󣬵�@npc_139117������ȡ������",	--��������
							""					--����С��ʾ
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
end

function x300352_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	x300352_QuestLogRefresh( sceneId, selfId, MissionId );
end

function x300352_CheckSubmitNPC( sceneId,selfId,idScript,idMission,npcGUID )
	if IsHaveQuestNM( sceneId, selfId, x300352_g_FatherMissionId ) == 0 then
		-- ���û���������
		return 0
	end
	for i, npcItem in SPOUSE_NPC do
		if npcItem == npcGUID then
			return 1
		end
	end
	return 0
end