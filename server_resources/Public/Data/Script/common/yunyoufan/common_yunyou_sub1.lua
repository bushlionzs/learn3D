
x310072_g_SubMission			=	{ 
									{ MissionId=8081, 
										MissionName = "�����ˡ��ٵ��ɰ�", 
										MissionTarget = "  �ѿ������͵�@npc_139109��", 
										MissionInfo = "\t���Ѿ��ӵ����ͣ���������ĵ��������Ǹ��㱸�µ�������ȥ@npc_139109�����ܹ�Ʒ�ɣ�",
										MissionHelp = "\t������ڻ��͵Ĺ��������߻���Զ��������5���ӣ��������ͻ�ʧ�ܡ��뾡����ɰɣ�������ɵĻ���͢�������ཱ���ġ�", 
										NpcName="@npc_139109"
									}, 
									{ MissionId=8082, 
										MissionName = "�����ˡ��ٵ��ɰ�", 
										MissionTarget = "  �ѿ������͵�@npc_139110��", 
										MissionInfo = "\t���Ѿ��ӵ����ͣ���������ĵ��������Ǹ��㱸�µ�������ȥ@npc_139110�����ܹ�Ʒ�ɣ�",
										MissionHelp = "\t������ڻ��͵Ĺ��������߻���Զ��������5���ӣ��������ͻ�ʧ�ܡ��뾡����ɰɣ�������ɵĻ���͢�������ཱ���ġ�", 
										NpcName="@npc_139110"
									}, 
									{ MissionId=8083, 
										MissionName = "�����ˡ��ٵ��ɰ�", 
										MissionTarget = "  �ѿ������͵�@npc_139111��", 
										MissionInfo = "\t���Ѿ��ӵ����ͣ���������ĵ��������Ǹ��㱸�µ�������ȥ@npc_139111�����ܹ�Ʒ�ɣ�",
										MissionHelp = "\t������ڻ��͵Ĺ��������߻���Զ��������5���ӣ��������ͻ�ʧ�ܡ��뾡����ɰɣ�������ɵĻ���͢�������ཱ���ġ�", 
										NpcName="@npc_139111"
									}, 
									{ MissionId=8084, 
										MissionName = "�����ˡ��ٵ��ɰ�", 
										MissionTarget = "  �ѿ������͵�@npc_139112��", 
										MissionInfo = "\t���Ѿ��ӵ����ͣ���������ĵ��������Ǹ��㱸�µ�������ȥ@npc_139112�����ܹ�Ʒ�ɣ�",
										MissionHelp = "\t������ڻ��͵Ĺ��������߻���Զ��������5���ӣ��������ͻ�ʧ�ܡ��뾡����ɰɣ�������ɵĻ���͢�������ཱ���ġ�", 
										NpcName="@npc_139112"
									}, 
									{ MissionId=8085, 
										MissionName = "�����ˡ��ٵ��ɰ�", 
										MissionTarget = "  �ѿ������͵�@npc_139113��", 
										MissionInfo = "\t���Ѿ��ӵ����ͣ���������ĵ��������Ǹ��㱸�µ�������ȥ@npc_139113�����ܹ�Ʒ�ɣ�",
										MissionHelp = "\t������ڻ��͵Ĺ��������߻���Զ��������5���ӣ��������ͻ�ʧ�ܡ��뾡����ɰɣ�������ɵĻ���͢�������ཱ���ġ�", 
										NpcName="@npc_139113"
									}
								}


 
x310072_g_BusScriptId = 310071

x310072_g_ScriptId = 310072
x310072_g_BusId = { 21,22,23,24,25 }

function x310072_PushAfterMission(sceneId, selfId , target, level, index)

	local isFull = IsQuestFullNM( sceneId, selfId )

	if isFull > 0 then	
		local strText = "�����������������ʧ��"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		return
	end
	
	local busObjId = CallScriptFunction( x310072_g_BusScriptId, "OnCreateBus", sceneId, selfId ,x310072_g_SubMission[index].MissionId, x310072_g_BusId[index])
end

function x310072_OnCreateBusOK(sceneId, selfId, busObjId,targetId,MissionId,index)

	if busObjId < 0 then
		local strText = "�޷������ڳ����������ʧ��"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		return
	end
	
	--���ǰ������
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, x310072_g_SubMission[index].MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return
		end
	end

	local ret = AddQuestNM( sceneId, selfId, x310072_g_SubMission[index].MissionId ) -- ������������

	if ret <0 then
		if (IsObjValid (sceneId,busObjId) ~= 1) or GetBusQuestID(sceneId, busObjId) ~= x310072_g_SubMission[index].MissionId then
				return
		end
		DeleteBus(sceneId, busObjId,1)
		if ret == -2 then
			local strText = "�����������������ʧ��"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		elseif ret == -1 then
			local strText = "��������,�������ʧ��"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		else
			local strText = "�������ʧ��"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
		return
	end

	GamePlayScriptLog(sceneId, selfId, 371)

	SetQuestParam( sceneId, selfId, x310072_g_SubMission[index].MissionId, 7, 1 )

	local misIndex = GetQuestIndexByID( sceneId, selfId, x310072_g_SubMission[index].MissionId )	
	SetQuestByIndex( sceneId, selfId, misIndex, 1, GetLevel(sceneId, selfId) )

	BeginQuestEvent( sceneId);
		--������Ϣ
		AddQuestText(sceneId, "#Y"..(x310072_g_SubMission[index].MissionName));
		AddQuestText(sceneId, x310072_g_SubMission[index].MissionInfo)

		--����Ŀ��
		AddQuestText( sceneId, "#Y����Ŀ�꣺")
		AddQuestText( sceneId, x310072_g_SubMission[index].MissionTarget)
		--��ʾ��Ϣ
		if x310072_g_SubMission[index].MissionHelp ~= "" then
			AddQuestText(sceneId, "#Y������ʾ��")
			AddQuestText(sceneId, x310072_g_SubMission[index].MissionHelp )
		end

	
		--��ȡ����
		local experience = level*1680
		AddQuestExpBonus( sceneId, experience);
		--AddQuestItemBonus(sceneId, 12110204, 1)
		AddQuestMoneyBonus2(sceneId, level*100 )

	EndQuestEvent(sceneId);
	DispatchQuestInfoNM(sceneId, selfId, target, x310072_g_ScriptId, x310072_g_SubMission[index].MissionId, 1);

end

function x310072_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
  	
end


--�������ť������������ִ�д˽ű�
function x310072_ProcEventEntry( sceneId, selfId, targetId, MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- ���û���������
		
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then 	-- �������������
				--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) 					-- ��ʾ�����Ϣ
				x310072_ProcQuestSubmit( sceneId, selfId, targetId, -1, MissionId )
			else
				QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) 				-- ��ʾ����δ�����Ϣ
			end

	end
		  
end


--**********************************
--����
--**********************************
function x310072_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	
end


--**********************************
--����
--**********************************
function x310072_ProcAccept( sceneId, selfId )
	
end

--�������
--����1����ɹ���0��������ʧ��
function x310072_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	--�ڳ��Ƿ�����Ч����
	local valid = IsValidMyselfBus(sceneId, selfId, MissionId)

	if valid == 0 then
		local Readme = "�����͵�������̫Զ�ˣ��޷��ύ����"
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local level = GetQuestParam( sceneId, selfId, misIndex, 1 )

	local index = GetQuestData(sceneId, selfId, MD_YUNYOU_RAND[1], MD_YUNYOU_RAND[2], MD_YUNYOU_RAND[3])

	local Readme = "��ϲ����ɻ���������"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	Msg2Player(sceneId,selfId,Readme,8,2)

	DelQuest( sceneId, selfId, MissionId)
	GamePlayScriptLog(sceneId, selfId, 372)
	
	local BusID  =  GetBusId(sceneId, selfId)
	if BusID ~= -1 then
		--���BUS������
		DeleteBus(sceneId, BusID,1)
	end 
	
	CallScriptFunction( 310073, "PushAfterMission", sceneId, selfId ,targetId, level, index)  
	
	return 0
	
end


--********************************************************************
--����
--********************************************************************
function x310072_ProcQuestAbandon( sceneId, selfId,MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
		return
	end

	DelQuestNM( sceneId, selfId, MissionId)
	local message = "�����������񣺡����ˡ��ٵ��ɰ�"
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId,selfId, message,4,2)

	SetQuestData(sceneId, selfId, MD_YUNYOU_DATE[1], MD_YUNYOU_DATE[2], MD_YUNYOU_DATE[3], GetDayOfYear())
  	
  	local BusID  =  GetBusId(sceneId, selfId)
	if (IsObjValid (sceneId,BusID) ~= 1) or GetBusQuestID(sceneId, BusID) ~= MissionId then
				return
	end
  	if BusID ~= -1 then
     	--���BUS������
  		DeleteBus(sceneId, BusID,1)
  	end

end


function x310072_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
		return
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local submitGuid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	local  missionState = GetQuestStateNM(sceneId, selfId, npcId, MissionId)
	if npcGuid == submitGuid then	--�����NPC�����ֺ�������NPC��������ͬ������Ҳ�жϹ���
		AddQuestTextNM( sceneId, selfId, npcId, MissionId, missionState, -1 ) -- ��ʾ������Ϣ
	end
end



---------------------------------------------------------------------------------------------------
--������־ˢ��
function x310072_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	local bHaveMission = IsHaveQuestNM(sceneId, selfId,MissionId );
		if bHaveMission > 0 then
			local index = GetQuestData(sceneId, selfId, MD_YUNYOU_RAND[1], MD_YUNYOU_RAND[2], MD_YUNYOU_RAND[3])

			if x310072_g_SubMission[index].MissionId ~= MissionId then
				return
			end

			BeginQuestEvent(sceneId)			
		    AddQuestLogCustomText( sceneId,
									"",							-- ����
									x310072_g_SubMission[index].MissionName,      -- ��������
									x310072_g_SubMission[index].MissionTarget,	--����Ŀ��
									x310072_g_SubMission[index].NpcName,			--����NPC
									"",      --������
									x310072_g_SubMission[index].MissionInfo,		--��������
									x310072_g_SubMission[index].MissionHelp							--����С��ʾ
									)
      AddQuestExpBonus(sceneId, GetLevel(sceneId, selfId)*1680)
     -- AddQuestItemBonus(sceneId, 12110204, 1)
	  AddQuestMoneyBonus2(sceneId, GetLevel(sceneId, selfId)*100 )
			EndQuestEvent(sceneId)
			DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		end
end
