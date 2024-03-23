
--MisDescBegin
x300350_g_ScriptId = 300350
x300350_g_LevelLess = 40
--MisDescEnd

x300350_g_MissionId = SPOUSE_TASK[1]
x300350_g_FatherMissionId = SPOUSE_TASK[3]
x300350_g_FatherMissionName = "����������"
x300350_g_MissionName ="����������"
x300350_g_MissionItem = 13080009

function x300350_IsMissionComplete(sceneId, selfId, MissionId) 
  local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
  return GetQuestParam( sceneId, selfId, misIndex, 7 )
end
function x300350_SetMissionData(sceneId, selfId)
		SetQuestData(sceneId, selfId, MD_SPOUSE_MISSION_DATE[1][1], MD_SPOUSE_MISSION_DATE[1][2], MD_SPOUSE_MISSION_DATE[1][3], GetDayOfYear())
end

function x300350_SubmitFatherMissionCheck(sceneId, selfId, NPCId)
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
	
	if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
		return "�ܱ�Ǹ��������ż������Ч�ľ����ڣ��޷����б�����";
	end
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return "�ܱ�Ǹ�������ڵĶ����г�Ա���Ƿ��޹�ϵ���޷��ύ������";
	end		
	
	if GetSex(sceneId, selfId) == 0 then
		return "�ܱ�Ǹ��ֻ�����Բ����ύ������";
	end
	
	if IsHaveQuestNM( sceneId, selfId, x300350_g_FatherMissionId ) ~= 1 then
		return "��û�б������޷��ύ������"
	end
	
	if IsHaveQuestNM( sceneId, targetId, x300350_g_FatherMissionId ) ~= 1 then
		return "������żû�б������޷��ύ������"
	end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300350_g_FatherMissionId )
	if GetQuestParam( sceneId, selfId, misIndex, 1 )  <= 0 then
		return "��δ��ɱ������޷��ύ������"
	end
	
	local misIndex = GetQuestIndexByID( sceneId, targetId, x300350_g_FatherMissionId )
	if GetQuestParam( sceneId, targetId, misIndex, 1 ) <= 0 then
		return "������żδ��ɱ������޷��ύ������"
	end
	
	return nil
end

--**********************************

--������ں���

--**********************************
function x300350_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )
	if IsHaveQuestNM( sceneId, selfId, x300350_g_FatherMissionId ) == 1 then
		
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300350_g_FatherMissionId )
		if GetQuestParam( sceneId, selfId, misIndex, 1 ) == 1 then
			local submitRetCode = x300350_SubmitFatherMissionCheck(sceneId, selfId, targetId)
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
				--DispatchQuestDemandInfo(sceneId, selfId, targetId, x300350_g_ScriptId, x300350_g_MissionId,0);
				--return
			end
			BeginQuestEvent(sceneId)
		--������Ϣ
			AddQuestText(sceneId,"")
			AddQuestText(sceneId,"")
	
			--����Ŀ��
			AddQuestText(sceneId,"")
			AddQuestText(sceneId,"#Y�����ޡ�������ӳ#W#r\t��ϲ������ɫ������ˡ��������񡿣�ף�������޶��˰�ͷ���ϣ��������룡���Ǹ����ǵĽ����������£�#r")
	
			local level = GetLevel(sceneId, selfId)
			local ExpBonus = 1000 *0.4*level*10
			--if ExpBonus > 0 then
				AddQuestExpBonus(sceneId, ExpBonus);
			--end
			
			EndQuestEvent()
		  DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300350_g_ScriptId, x300350_g_MissionId);
		  return
		else
			local str = "����û����� ������Ҫ�ӰѾ��� ..."
			Msg2Player(sceneId,selfId,str,8,2)
			return
			--BeginQuestEvent(sceneId)
			--AddQuestText(sceneId,str)
			--EndQuestEvent()
			--DispatchQuestDemandInfo(sceneId, selfId, targetId, x300350_g_ScriptId, x300350_g_MissionId,0);
			--return
		end
	end
	if IsHaveQuestNM( sceneId, targetId, x300350_g_MissionId ) ~= 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y�����ޡ������Ͼ�")
		AddQuestText(sceneId,"\t���ã�ÿ�ܵ����ģ���������������������С��������񡿡�����������һ��������������ɡ����������ȫ������������ܹ���ý�����#r\t�ڴ󶼵Ķ��Ÿ�����������һ����ɫ��ˮ����#r\t��˵�õ���ˮ�������»��ܵ�����ף����#r\t�����@npc_72044���ɼ�5����ˮ����������@npc_140002���������ռ����а������ˮ��������ˮ�����������Ϳ��Եõ��������ǰ���ף����")
		local level = GetLevel(sceneId, selfId)
		local ExpBonus = 1000 *0.4*10* level
		AddQuestText(sceneId,"#Y�������ݣ�#W#r����ֵ��" .. ExpBonus.."��")
		EndQuestEvent(sceneId)   
		DispatchQuestInfo(sceneId, selfId, targetId, x300350_g_MissionId, x300350_g_ScriptId)
	end
	
end

--**********************************

--�о��¼�

--**********************************
--5	��ѭ������	δ��	1
--6	��ѭ��/ѭ������	δ���	2
--7	��ѭ������	�����	3
function x300350_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	if IsMarried(sceneId, selfId) ~= 1 then
		return
	end
	local state = GetQuestStateNM(sceneId, selfId, targetId, x300350_g_MissionId)
	if IsHaveQuestNM( sceneId, selfId, x300350_g_MissionId ) == 1 then
		return
	end
	if IsHaveQuestNM( sceneId, selfId, SPOUSE_TASK[2] ) == 1 then
		return
	end
	
	if IsHaveQuestNM( sceneId, selfId, x300350_g_FatherMissionId ) == 1 then
		state = GetQuestStateNM(sceneId, selfId, targetId, x300350_g_FatherMissionId)
		AddQuestNumText(sceneId, MissionId, x300350_g_FatherMissionName, state, -1)
		return
	end
	AddQuestNumText(sceneId, MissionId, x300350_g_MissionName, state, -1)
	
end



--**********************************

--����������

--**********************************

function x300350_ProcAcceptCheck(sceneId, selfId, NPCId)

	--if HasTeam(sceneId, selfId) == 1 then
		return 1
	--end
end


--**********************************

--���鿴����

--**********************************

function x300350_CheckPushList(sceneId, selfId, NPCId)
	return 1
end

function x300350_SendAcceptMissionMsg(sceneId, selfId, MissionId)
	local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
	local message = format("�����������񣺡����ޡ������Ͼ�", MissionName);
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 4, 2);
end

function x300350_DoAccept( sceneId, selfId )

	local week = GetWeek()
	local today = GetDayOfYear()
	if week ~= 4 and week ~= 6 then
		return"�ܱ�Ǹ��ֻ�����ġ����������ܽ��б�����"    
	end
	
	if 1 == IsQuestFullNM(sceneId, selfId) then
			return "�ܱ�Ǹ�����������Ѿ����ˣ��޷���ȡ������"
	end
	if HasTeam(sceneId, selfId) ~= 1 then
		return "�ܱ�Ǹ������δ��������޷���ȡ������"
	end
	
	local teamSize = GetTeamSize(sceneId, selfId)
	
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
	
	if 1 == IsQuestFullNM(sceneId, targetId) then
			return "�ܱ�Ǹ������ż�������Ѿ����ˣ��޷���ȡ������"
	end
	
	local completeDay = GetQuestData(sceneId, selfId, MD_SPOUSE_MISSION_DATE[1][1], MD_SPOUSE_MISSION_DATE[1][2],MD_SPOUSE_MISSION_DATE[1][3])
	if completeDay == today then
		return "�ܱ�Ǹ���������Ѿ��ɹ���ȡ����ɹ�������"
	end
	
	completeDay = GetQuestData(sceneId, targetId, MD_SPOUSE_MISSION_DATE[1][1], MD_SPOUSE_MISSION_DATE[1][2],MD_SPOUSE_MISSION_DATE[1][3])
	if completeDay == today then
		return "������ż��ȡ�˱����񣬽����޷���ȡ������"
	end
	
	
	
	local bHaveMission = IsHaveQuest(sceneId, targetId, x300350_g_MissionId)
	if bHaveMission == 1 then
		return "������ż�б������޷���ȡ������"
	end
		
	if AddQuestNM( sceneId, selfId, x300350_g_MissionId ) ~= 1 then
		return "���������ʧ�ܣ��޷���ȡ������"
	end
	x300350_SetMissionData(sceneId, selfId)
	x300350_SendAcceptMissionMsg( sceneId, selfId, x300350_g_MissionId )
	
	if AddQuestNM( sceneId, targetId, x300350_g_MissionId ) ~= 1 then
		return "������ż�������ʧ�ܣ��޷���ȡ������"
	end
	x300350_SetMissionData(sceneId, targetId)
	x300350_SendAcceptMissionMsg( sceneId, targetId, x300350_g_MissionId )
	
	return nil
end

--**********************************

--����

--**********************************
function x300350_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	local str = x300350_DoAccept( sceneId, selfId )
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,8,2)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,str);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		
	end
	
end



--**********************************

--����

--**********************************

function x300350_ProcQuestAbandon(sceneId, selfId, MissionId)
	DelQuestNM( sceneId, selfId, MissionId )
	
	--local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
	local message = "�������˷�������"
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 4, 2);
	
	x300350_SetMissionData(sceneId, selfId)
	
	--����ִ���ʼ�����ż
	local spouseGuid = GetSpouseGUID( sceneId, selfId )
	local spouseName = GetFriendName( sceneId, selfId, tonumber(spouseGuid) )
	SendScriptMail( sceneId, spouseName, MAIL_DELETE_MISSION, x300350_g_MissionId, 0, 0, selfId )
end



--**********************************

--����Ƿ�����ύ

--**********************************

function x300350_CheckSubmit( sceneId, selfId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then
		return 0;
	end
	return 1
end


function x300350_CalculateEXP(level)
	local ExpBonus = 1000 *0.4*10* level
	if ExpBonus > 0 then
		return ExpBonus
	end
	return 0
end
--**********************************

--�ύ

--**********************************
function x300350_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	local retCode = x300350_SubmitFatherMissionCheck(sceneId, selfId, targetId)
	if retCode ~= nil then
		Msg2Player(sceneId,selfId,retCode,8,2)
		return
	end
	local spouseId = GetTeamSceneMember(sceneId, selfId, 0);
	local level = GetLevel(sceneId, selfId)
	local ExpBonus = x300350_CalculateEXP(level)
	local ret = x300350_IsMissionComplete( sceneId, selfId, x300350_g_FatherMissionId )
	if ret > 0 then
		AddExp(sceneId, selfId, ExpBonus);	
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "����������񣺡���������");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "���#R����"..ExpBonus.."��#o�Ľ���");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		local Readme ="����������񣺡���������#r���#R����"..ExpBonus.."��#o�Ľ���"
		Msg2Player(sceneId,selfId,Readme,8,2)
		DelQuestNM( sceneId, selfId, x300350_g_FatherMissionId )
		x300350_SetMissionData(sceneId, selfId)
	end

	local ret = x300350_IsMissionComplete( sceneId, spouseId, x300350_g_FatherMissionId )
	if ret > 0 then
		local level = GetLevel(sceneId, spouseId)
		local ExpBonus = x300350_CalculateEXP(level)
		AddExp(sceneId, spouseId, ExpBonus);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "����������񣺡���������");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, spouseId);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "���#R����"..ExpBonus.."��#o�Ľ���");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, spouseId);
		local Readme ="����������񣺡���������#r���#R����"..ExpBonus.."��#o�Ľ���"
		Msg2Player(sceneId,spouseId,Readme,8,2)
		DelQuestNM( sceneId, spouseId, x300350_g_FatherMissionId )
		x300350_SetMissionData(sceneId, spouseId)
	end
	
end



--**********************************

--ɱ����������

--**********************************

function x300350_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end



--**********************************

--���������¼�

--**********************************

function x300350_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x300350_ProcTiming(sceneId, selfId )
	 
		
end

function x300350_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x300350_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId, nChangeType)
    
  if MissionId == nil or MissionId < 0 then
      return
  end
  
  if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
      return
  end
  
  if itemdataId ~= x300350_g_MissionItem then
  	return
  end
    
	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, itemdataId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	
	if 1 == nChangeType then -- ɾ��������Ʒ
		local Num = GetItemCount( sceneId, selfId, itemdataId )
		SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )
		if Num < NeedNum then
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
		end
		x300350_RefreshItemNum( sceneId, selfId, MissionId)
		return
	end
	
	if NeedNum > 0 then
		local Num = GetItemCount( sceneId, selfId, itemdataId )
		if Num < NeedNum then --��û���������
            if nChangeType == 0 then --ɾ����Ʒ������ʾ
                BeginQuestEvent(sceneId)
                local strText = format("#Y�����Ʒ#G#{_ITEM%d}#Y: %d/%d", itemdataId, Num, NeedNum )
                if strText == nil then
                    strText = "";
                end
                AddQuestText( sceneId, strText )
                EndQuestEvent( sceneId )
                DispatchQuestTips( sceneId, selfId )
            end
			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
		elseif Num == NeedNum then
			--�Ѿ��������
            if nChangeType == 0 then --ɾ����Ʒ������ʾ
                BeginQuestEvent(sceneId)
                local strText = format( "#Y����ɻ����Ʒ#G#{_ITEM%d}#Y: %d/%d", itemdataId, Num, NeedNum )
                if strText == nil then
                    strText = "";
                end
                AddQuestText( sceneId, strText )
                EndQuestEvent( sceneId )
                DispatchQuestTips( sceneId, selfId )
                SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
            end
			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
		end
	x300350_RefreshItemNum( sceneId, selfId, MissionId)
	end
end
function x300350_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
		return
	end
	
end

function x300350_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x300350_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x300350_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x300350_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x300350_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x300350_RefreshItemNum( sceneId, selfId, MissionId)
	x300350_QuestLogRefresh( sceneId, selfId, MissionId)
end

function x300350_QuestLogRefresh( sceneId, selfId, MissionId)
	BeginQuestEvent(sceneId)
	local level = GetLevel(sceneId, selfId)
	local ExpBonus = 1000 *0.4*10* level
    if ExpBonus > 0 then
		AddQuestExpBonus(sceneId,  ExpBonus);
	end
		
	if MissionId == nil or MissionId < 0 then
        return
    end
    
    if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
        return
    end
    
	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, x300350_g_MissionItem )
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local curNum = GetQuestParam(sceneId, selfId, misIndex, ObjIndex)
	local szTarget = "(" .. curNum .. "/" .. NeedNum .. ")"
	AddQuestLogCustomText( sceneId,
							"����",						-- ����
							"" .. x300350_g_MissionName,        -- ��������
							"  ȥ@npc_72044�ɼ�@item_13080009������@npc_140002" .. szTarget,		--����Ŀ��
							"@npc_140002",			--����NPC
							"",               --������
							"\t�ڴ󶼵Ķ��Ÿ�����������һ����ɫ��ˮ����#r\t��˵�õ���ˮ�������»��ܵ�����ף����#r\t�����@npc_72044���ɼ�5����ˮ����������@npc_140002���������ռ����а������ˮ��������ˮ�����������Ϳ��Եõ��������ǰ���ף����",	--��������
							"���������񡿽��е����������У�����������ż��Ӱ���룬��������������ȡ���ύ����"					--����С��ʾ
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
end

function x300350_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	x300350_QuestLogRefresh( sceneId, selfId, MissionId );
end

function x300350_CheckSubmitNPC( sceneId,selfId,idScript,idMission,npcGUID )
	if IsHaveQuestNM( sceneId, selfId, x300350_g_FatherMissionId ) == 0 then
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