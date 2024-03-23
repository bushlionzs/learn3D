
--MisDescBegin
x300351_g_ScriptId = 300351
x300351_g_LevelLess = 40
--MisDescEnd
x300351_g_BusScriptId = 300354
x300351_g_FatherMissionId = SPOUSE_TASK[1]
x300351_g_FatherMissionName = "����������"
x300351_g_MissionId = SPOUSE_TASK[2]

x300351_g_MissionName ="����������"

function x300351_IsMissionComplete(sceneId, selfId, MissionId) 
  local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
  return GetQuestParam( sceneId, selfId, misIndex, 7 )
end

function x300351_SetMissionData(sceneId, selfId)
		SetQuestData(sceneId, selfId, MD_SPOUSE_MISSION_DATE[1][1], MD_SPOUSE_MISSION_DATE[1][2], MD_SPOUSE_MISSION_DATE[1][3], GetDayOfYear())
end

function x300351_SubmitFatherMissionCheck(sceneId, selfId, NPCId)
	local teamSize = GetTeamSize(sceneId, selfId)
	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	local week = GetWeek()
	local today = GetDayOfYear()
	if week ~=4 and week ~= 6 then
		return "�ܱ�Ǹ��ֻ�����ġ����������ܽ��б�����"   
	end
	
	if HasTeam(sceneId, selfId) ~= 1 then
		return "�ܱ�Ǹ������δ��������޷��ύ������"
	end
	
	if (GetTeamSize(sceneId, selfId) < 2) then
		return "�ܱ�Ǹ�������ڵĶ����г�ԱС��2�ˣ��޷��ύ������";
	end
	
	if (GetTeamSize(sceneId, selfId) > 2) then
		return "�ܱ�Ǹ�������ڵĶ����г�Ա����2�ˣ��޷��ύ������";
	end
	
	-- if GetSex(sceneId, selfId) == 0 then
		
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "�ܱ�Ǹ��ֻ�����Բ����ύ������");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
		-- local Readme = "�ܱ�Ǹ��ֻ�����Բ����ύ������"
		-- Msg2Player(sceneId,selfId,Readme,8,2);
		-- return 
	-- end
	
	if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
		return "�ܱ�Ǹ��������ż������Ч�ľ����ڣ��޷����б�����";
	end
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return "�ܱ�Ǹ�������ڵĶ����г�Ա���Ƿ��޹�ϵ���޷��ύ������";
	end		
	
	if IsHaveQuestNM( sceneId, selfId, x300351_g_FatherMissionId ) ~= 1 then
		return "��û�б������޷��ύ������"
	end
	
	if IsHaveQuestNM( sceneId, targetId, x300351_g_FatherMissionId ) ~= 1 then
		return "������żû�б������޷��ύ������"
	end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300351_g_FatherMissionId )
	if QuestCheckSubmitNM( sceneId, selfId, NPCId, x300351_g_FatherMissionId, misIndex ) <= 0 then
		return "��δ��ɱ������޷��ύ������"
	end
	
	local misIndex = GetQuestIndexByID( sceneId, targetId, x300351_g_FatherMissionId )
	if QuestCheckSubmitNM( sceneId, targetId, NPCId, x300351_g_FatherMissionId, misIndex ) <= 0 then
		return "������żδ��ɱ������޷��ύ������"
	end
	
	return nil
end

--**********************************

--������ں���

--**********************************

function x300351_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300351_g_FatherMissionId )
	if QuestCheckSubmitNM( sceneId, selfId, targetId, x300351_g_FatherMissionId, misIndex ) > 0 then
		local submitRetCode = x300351_SubmitFatherMissionCheck(sceneId, selfId, targetId)
		if submitRetCode ~= nil then
			Msg2Player(sceneId,selfId,submitRetCode,8,2)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, submitRetCode);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return
			--BeginQuestEvent(sceneId)
			--AddQuestText(sceneId,submitRetCode)
			--EndQuestEvent()
			--DispatchQuestDemandInfo(sceneId, selfId, targetId, x300351_g_ScriptId, x300351_g_MissionId,0);
			--return
		end
		local addNextMissionRetCode = x300351_AcceptCheck(sceneId, selfId)
		if addNextMissionRetCode ~= nil then
			Msg2Player(sceneId,selfId,addNextMissionRetCode,8,2)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, addNextMissionRetCode);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return
			--BeginQuestEvent(sceneId)
			--AddQuestText(sceneId,addNextMissionRetCode)
			--EndQuestEvent()
			--DispatchQuestDemandInfo(sceneId, selfId, targetId, x300351_g_ScriptId, x300351_g_MissionId,0);
			--return
		end
		BeginQuestEvent(sceneId)
	--������Ϣ
		-- AddQuestText(sceneId,"#Y�����ޡ������Ͼ�")
		-- AddQuestText(sceneId,"\t��������һ#r")

		--����Ŀ��
		AddQuestText(sceneId,"")
		AddQuestText(sceneId,"#Y�����ޡ�����ˮ��#W#r\t����Ҫ�ܶ���а����@item_13080009#W��������֮���ƣ����������Ѿ����Ҳɵ��ˣ�#r\t������С�����������۵����ӣ�������Ľ�����ˣ��治֪����ʱ��Ҳ�ҵ��۰��ҵ����ӣ�#r\t���������������Ұ�������С������@npc_139818����ɣ����Ѿ��ܾ�û���ְ��ˡ�#r\t�һ�Ϊ���ǵİ�������ף�������Ҹ�������")

		EndQuestEvent()
	  DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300351_g_ScriptId, x300351_g_MissionId);
	  return
	end
	
	local str = "����������һ�뻹δ������񣬼��Ͱ�"
	Msg2Player(sceneId,selfId,str,8,2)
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, str);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)

end

--**********************************

--�о��¼�

--**********************************
--5	��ѭ������	δ��	1
--6	��ѭ��/ѭ������	δ���	2
--7	��ѭ������	�����	3
function x300351_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	if IsMarried(sceneId, selfId) ~= 1 then
		return
	end
	
	if IsHaveQuestNM( sceneId, selfId, x300351_g_FatherMissionId ) == 1 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300351_g_FatherMissionId )
		local state = GetQuestStateNM(sceneId, selfId, targetId, x300351_g_FatherMissionId)
		AddQuestNumText(sceneId, x300351_g_ScriptId, x300351_g_FatherMissionName, state, -1)
		return
	end
	
end



--**********************************

--����������

--**********************************

function x300351_ProcAcceptCheck(sceneId, selfId, NPCId)

	--if HasTeam(sceneId, selfId) == 1 then
		return 1
	--end
end


--**********************************

--���鿴����

--**********************************

function x300351_CheckPushList(sceneId, selfId, NPCId)
	return 1
end

function x300351_CreateBus(sceneId, selfId)
  local PosX,PosZ = GetWorldPos(sceneId, selfId)
	local busType = 31
	local AIType = 3
	local AIScript = 3
	local IamGodImpactId = 1210
	local ObjID = CreateBus(sceneId, busType, PosX, PosZ, AIType, AIScript, x300351_g_BusScriptId, selfId, IamGodImpactId,-1,-1)
end

function x300351_DeleteBus(sceneId, selfId)

	local BusID  =  GetBusId(sceneId, selfId)
	if BusID ~= -1 then
		if (IsObjValid (sceneId,BusID) == 1) and x300351_g_MissionId == GetBusQuestID(sceneId, BusID ) then
			DeleteBus(sceneId, BusID,1)
		end
	end
	
end

function x300351_AcceptCheck(sceneId, selfId)
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
		return "�ܱ�Ǹ��������Ѳ�����Ч�ľ����ڣ��޷���ȡ������";
	end
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return "�ܱ�Ǹ�������ڵĶ����г�Ա���Ƿ��޹�ϵ���޷���ȡ������";
	end		
	
	if GetSex(sceneId, selfId) == 0 then
		return "�ܱ�Ǹ������������һ�������б�����";
	end
	
	local bHaveMission = IsHaveQuest(sceneId, targetId, x300351_g_MissionId)
	if bHaveMission == 1 then
		return "������ż��" .. x300351_g_MissionName .. "���޷���ȡ������"
	end
	
	bHaveMission = IsHaveQuest(sceneId, selfId, x300351_g_MissionId)
	if bHaveMission == 1 then
		return "����" .. x300351_g_MissionName .. "���޷���ȡ������"
	end
	
	if IsBusMember(sceneId, selfId) == 1 then
		return "�����ڻ��ͣ��޷���ȡ������"
	end
			
	return nil
end
	
function x300351_DoAccept( sceneId, selfId )

	local retCode = x300351_AcceptCheck(sceneId, selfId)
	if retCode ~= nil then
		return retCode
	end
	local teamSize = GetTeamSize(sceneId, selfId)
	for i = 0, teamSize - 1 do
		local aId = GetNearTeamMember(sceneId, selfId, i)
		local aName = GetName(sceneId, aId)
		local errorCode = AddQuestNM( sceneId, aId, x300351_g_MissionId )
		if errorCode ~= 1 then
			Msg2Player(sceneId,aId,"�������ʧ�ܣ�",8,2)
		end
		
	end
	x300351_CreateBus(sceneId, selfId)
	
	
	return nil
end

--**********************************

--����

--**********************************
function x300351_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	local str = x300351_DoAccept( sceneId, selfId )
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,8,2)
	end
	
end



--**********************************

--����

--**********************************

function x300351_ProcQuestAbandon(sceneId, selfId, MissionId)
	DelQuestNM( sceneId, selfId, MissionId )
	
	--local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
	local message = "�������˷�������"
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 4, 2);
	
	x300351_DeleteBus(sceneId, selfId)
	
	x300351_SetMissionData(sceneId, selfId)
	
	--����ִ���ʼ�����ż
	local spouseGuid = GetSpouseGUID( sceneId, selfId )
	local spouseName = GetFriendName( sceneId, selfId, tonumber(spouseGuid) )
	SendScriptMail( sceneId, spouseName, MAIL_DELETE_MISSION, x300351_g_MissionId, 1, 0, selfId )
end



--**********************************

--����Ƿ�����ύ

--**********************************

function x300351_CheckSubmit( sceneId, selfId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then
		return 0;
	end
	return 1
end



--**********************************

--�ύ

--**********************************
function x300351_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	local submitRetCode = x300351_SubmitFatherMissionCheck(sceneId, selfId, targetId)
	if submitRetCode ~= nil then
		Msg2Player(sceneId,selfId,submitRetCode,8,2)
		return
	end
	
	local retCode = x300351_AcceptCheck(sceneId, selfId)
	if retCode ~= nil then
		Msg2Player(sceneId,selfId,retCode,8,2)
		return
	end
	local spouseId = GetTeamSceneMember(sceneId, selfId, 0);
	
	local ret = x300351_IsMissionComplete( sceneId, selfId, x300351_g_FatherMissionId )
	if ret > 0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�����������:�����ޡ������Ͼ�");
		EndQuestEvent();
		Msg2Player(sceneId,selfId,"�����������:�����ޡ������Ͼ�",8,2)
		DispatchQuestTips(sceneId, selfId);
		
		DelQuestNM( sceneId, selfId, x300351_g_FatherMissionId )
		local errorCode = AddQuestNM( sceneId, selfId, x300351_g_MissionId )
		if errorCode ~= 1 then
			Msg2Player(sceneId,selfId,"�������ʧ�ܣ�",8,2)
		end
	end

	ret = x300351_IsMissionComplete( sceneId, spouseId, x300351_g_FatherMissionId )
	if ret > 0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�����������:�����ޡ������Ͼ�");
		EndQuestEvent();
		Msg2Player(sceneId,spouseId,"�����������:�����ޡ������Ͼ�",8,2)
		DispatchQuestTips(sceneId, spouseId);
		
		DelQuestNM( sceneId, spouseId, x300351_g_FatherMissionId )
		local errorCode = AddQuestNM( sceneId, spouseId, x300351_g_MissionId )
		if errorCode ~= 1 then
			Msg2Player(sceneId,spouseId,"�������ʧ�ܣ�",8,2)
		end
	end
	x300351_CreateBus(sceneId, selfId)
	return 0
	
end

--**********************************

--ɱ����������

--**********************************

function x300351_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end



--**********************************

--���������¼�

--**********************************

function x300351_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x300351_ProcTiming(sceneId, selfId )
	 
		
end

function x300351_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x300351_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
    
    if MissionId == nil or MissionId < 0 then
        return
    end
    
    if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
        return
    end
    
	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, itemdataId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	
	if NeedNum > 0 then
      	local Num = GetItemCount( sceneId, selfId, itemdataId )
		if Num < NeedNum then --��û���������
			BeginQuestEvent(sceneId)
			local strText = format("�ѵõ�@itemid_%d: %d/%d", itemdataId, Num, NeedNum )
			if strText == nil then
				strText = "";
			end
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
   			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )
  		elseif Num == NeedNum then
			--�Ѿ��������
			BeginQuestEvent(sceneId)
			local strText = format( "�ѵõ��㹻��@itemid_%d: %d/%d", itemdataId, Num, NeedNum )
			if strText == nil then
				strText = "";
			end
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
		end
	end
end
function x300351_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
		return
	end
	
end

function x300351_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x300351_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x300351_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x300351_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x300351_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x300351_QuestLogRefresh( sceneId, selfId, MissionId)

	BeginQuestEvent(sceneId)	
		
	AddQuestLogCustomText( sceneId,
							"����",						-- ����
							"" .. x300351_g_MissionName,        -- ��������
							"  ��#G������С��#W���͵�@npc_139818��",		--����Ŀ��
							"@npc_139818",			--����NPC
							"",               --������
							"��ɽͯ�ڵȴ����ĺ��ӣ���С����ȫ�͵�@npc_139818�������;��С��ֻ�������������ƶ�",	--��������
							"���͹����У�����˫�������뿪����Ŀ���Զ����ʱ����ã����������ʧ�ܣ�#r���ͺ�ֻͯ�����Բ����ύ����"					--����С��ʾ
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
end

function x300351_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	x300351_QuestLogRefresh( sceneId, selfId, MissionId );
end

function x300351_CheckSubmitNPC( sceneId,selfId,idScript,idMission,npcGUID )
	if IsHaveQuestNM( sceneId, selfId, x300351_g_FatherMissionId ) == 0 then
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