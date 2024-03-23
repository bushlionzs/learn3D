--MisDescBegin
x310070_g_ScriptId 	  = 310070

--��������
x310070_g_MissionName = "�����ˡ��ٵ��ɰ�"
-- ������Ϣ
x310070_g_MissionInfo = "\t@npc_%d�ɹ���һ��#G%s#W�������æȥ���������͵���վ���Ա���վ����Ʒת�˵��ʹ��ڿ⡣������������#G����ƥ�������ʹ��ſڴ��Ĵ�Ԫ������#W�������һ���˻���������ʹ�á�\n\t�ڹ��ڵ������¶�Ҫ���ģ�Ψ�ְ첻�ò��£������˻ʶ���\n\tע�������#Gÿ��19��30~24��00#W���ţ�#G�ȼ���40������#W����ҿ�����ȡ����\n"
-- ������ʾ
x310070_g_MissionHelp = "\t#G������ڻ��͵Ĺ��������߻���Զ��������5���ӣ��������ͻ�ʧ�ܡ�\n\t�뾡����ɰɣ�������ɵĻ���͢�������ཱ���ġ�"
-- ����Ŀ��
x310070_g_MissionTarget = "  �����͵�@npc_139235����"
x310070_g_NPCName = "@npc_139235"
x310070_TargetNPCList	=	{139109, 139110, 139111, 139112, 139113}
x310070_g_MissionComment = "\t����ʮ����ʥ���ٵ�֮�գ��Ҵ�Ԫ�ʵ�����Զ����ʮ·�ɰ��Ѿ�����̤����ղ��ԺӦ�Ӳ�Ͼ�����ܹ���һ�����룬�ͷ��㵽��δ�Ӵ��ĸ�·�ɰ촦�����ҽ����Ǿ��׸��ʵ۱��µ��������͵�������վ��������վת�˵��ʹ��ڿ⡣\n\tע�������#Gÿ��19��30~24��00#W���ţ�#G�ȼ���40������#G�ģ�����û�нӹ��������ҿ�����ȡ����"


--MisDescEnd



x310070_g_MinLevel = 40


x310070_TargetList ={ "���Ϲ���", "��ɽ���", "���", "�Ϲ�����", "�Ͻ�ʥ��" }
x310070_g_BusScriptId = 310071

x310070_g_BusId = { 16,17,18,19,20 }
x310070_g_MissionId = 8080
x310070_g_MissionAcceptTime1 = { 1170, 1440 }	

function x310070_ProcAcceptChecked( sceneId, selfId )
	--local week = GetWeek()
	--if week == 0 then
		--local year, month, day = GetYearMonthDay()
		local minspan = GetMinOfDay();
		--if day>7 and day <=14 then
			if minspan >= x310070_g_MissionAcceptTime1[1] and minspan < x310070_g_MissionAcceptTime1[2] then
				return 1
			end
		--end
	--end
	return -1
end

function x310070_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
  	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then		-- ���û���������
		
		local playerLevel = GetLevel( sceneId, selfId);
		if( playerLevel >= x310070_g_MinLevel ) then
			local  missionState = GetQuestStateNM(sceneId, selfId, targetId, MissionId)
			AddQuestTextNM(sceneId, selfId, targetId, MissionId, missionState);
		end
		
	end

	return 0
end


--��ʾ������Ϣ
function x310070_DispatchMissionInfo( sceneId, selfId, NPCId, index)
	BeginQuestEvent( sceneId);
		--������Ϣ
		AddQuestText(sceneId, "#Y"..x310070_g_MissionName);
		AddQuestText(sceneId, format(x310070_g_MissionInfo, x310070_TargetNPCList[index], x310070_TargetList[index]))

		--����Ŀ��
		AddQuestText( sceneId, "#Y����Ŀ�꣺")
		AddQuestText( sceneId, "����ƥ��ȫ���͵�@npc_139235��")
		--��ʾ��Ϣ
		if x310070_g_MissionHelp ~= "" then
			AddQuestText(sceneId, "#Y������ʾ��")
			AddQuestText(sceneId, x310070_g_MissionHelp )
		end
		
		--������Ϣ
		
		--�����ҵ�ǰ�ȼ�
		local playerLevel = GetLevel( sceneId, selfId);
		--��ȡ����
		local experience = playerLevel*1680
		AddQuestExpBonus( sceneId, experience);
      --AddQuestItemBonus(sceneId, 12110204, 1)
	  AddQuestMoneyBonus2(sceneId, playerLevel*100 )

	EndQuestEvent(sceneId);
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x310070_g_ScriptId, x310070_g_MissionId, 1);
end

function x310070_DispatchComment(sceneId, selfId, targetId)
	BeginQuestEvent( sceneId);
		AddQuestText(sceneId, "#Y"..x310070_g_MissionName);
		AddQuestText(sceneId, x310070_g_MissionComment);
		local playerLevel = GetLevel( sceneId, selfId);
		local experience = playerLevel*1680
		AddQuestExpBonus( sceneId, experience);
   -- AddQuestItemBonus(sceneId, 12110204, 1)
	AddQuestMoneyBonus2(sceneId, playerLevel*100 )
	EndQuestEvent(sceneId);
	DispatchQuestInfoNM(sceneId, selfId, targetId, x310070_g_ScriptId, x310070_g_MissionId);
end


--�������ť������������ִ�д˽ű�
function x310070_ProcEventEntry( sceneId, selfId, targetId, MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
		local day = GetQuestData(sceneId, selfId, MD_YUNYOU_DATE[1], MD_YUNYOU_DATE[2], MD_YUNYOU_DATE[3])
	
		if day ~= GetDayOfYear() then
			SetQuestData(sceneId, selfId, MD_YUNYOU_DATE[1], MD_YUNYOU_DATE[2], MD_YUNYOU_DATE[3], 0)
		end
		x310070_DispatchComment(sceneId, selfId, targetId)
	else
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then 	-- �������������
				--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) 					-- ��ʾ�����Ϣ
				x310070_ProcQuestSubmit( sceneId, selfId, targetId, -1, MissionId )
			else
				QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) 				-- ��ʾ����δ�����Ϣ
			end

	end
		  
end


--**********************************
--����
--**********************************
function x310070_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if IsBusMember(sceneId, selfId) > 0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�ܱ�Ǹ�������в���������");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������в���������",8,2)
		return 
	end

	if IsTeamFollow(sceneId, selfId) == 1 then
		local Readme = "��Ӹ���״̬�²����Խӻ�������"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_TIESAN ) > 0 then
		local Readme = "������������������Խӻ�������"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 
	end
		
	if x310070_ProcAcceptChecked( sceneId, selfId ) < 0 then
			local strText = "�����ÿ��19��30~24��00�ٰ�"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,strText,8,2)
			return 
	end	

	local day = GetQuestData(sceneId, selfId, MD_YUNYOU_DATE[1], MD_YUNYOU_DATE[2], MD_YUNYOU_DATE[3])

	if day ~= 0 then

		local strText = "������Ѿ��ӹ���������������"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,strText,8,2)
		return
	end

	local isFull = IsQuestFullNM( sceneId, selfId )

	if isFull > 0 then	
		local strText = "�����������������ʧ��"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		return
	end

	local index = random(1, 5)
	SetQuestData(sceneId, selfId, MD_YUNYOU_RAND[1], MD_YUNYOU_RAND[2], MD_YUNYOU_RAND[3], index)
	
	--���ǰ������
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 0--���ǰ������û��ֱ�ӷ���
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 0--���ǰ������û��ֱ�ӷ���
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return 0--���ǰ������û��ֱ�ӷ���
		end
	end
	
	--���󴴽�bus
	local busObjId = CallScriptFunction( x310070_g_BusScriptId, "OnCreateBus", sceneId, selfId ,MissionId, x310070_g_BusId[index])
		
end

function x310070_OnCreateBusOK(sceneId, selfId, busObjId,targetId,MissionId)

	if busObjId > 0 then
		local ret = AddQuestNM( sceneId, selfId, MissionId ) -- ������������

		if ret > 0 then
			x310070_DispatchMissionInfo( sceneId, selfId, targetId, index);	

			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )	
			SetQuestByIndex( sceneId, selfId, misIndex, 1, GetLevel(sceneId, selfId) )

			SetQuestData(sceneId, selfId, MD_YUNYOU_DATE[1], MD_YUNYOU_DATE[2], MD_YUNYOU_DATE[3], GetDayOfYear())
			SetQuestParam( sceneId, selfId, MissionId, 7, 1 )

				local message = "�����������񣺡����ˡ��ٵ��ɰ�"
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				Msg2Player(sceneId,selfId, message,4,2)

				GamePlayScriptLog(sceneId, selfId, 361)

		elseif ret == -2 then
			local strText = "�����������������ʧ��"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			  	
			if (IsObjValid (sceneId,busObjId) ~= 1) or GetBusQuestID(sceneId, busObjId) ~= MissionId then
				return
			end
			DeleteBus(sceneId, busObjId,1)
		elseif ret == -1 then
			local strText = "��������,�������ʧ��"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			if (IsObjValid (sceneId,busObjId) ~= 1) or GetBusQuestID(sceneId, busObjId) ~= MissionId then
				return
			end
			DeleteBus(sceneId, busObjId,1)
		else
			local strText = "�������ʧ��"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			if (IsObjValid (sceneId,busObjId) ~= 1) or GetBusQuestID(sceneId, busObjId) ~= MissionId then
				return
			end
			DeleteBus(sceneId, busObjId,1)
		end
	end
		
end

--�������
--����1����ɹ���0��������ʧ��
function x310070_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

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

	local Readme = "��ϲ����ɻ�����ƥ����"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	Msg2Player(sceneId,selfId,Readme,8,2)

	DelQuest( sceneId, selfId, MissionId)

	GamePlayScriptLog(sceneId, selfId, 362)
	
	local BusID  =  GetBusId(sceneId, selfId)
	if BusID ~= -1 then
		--���BUS������
		DeleteBus(sceneId, BusID,1)
	end 
	
	CallScriptFunction( 310072, "PushAfterMission", sceneId, selfId ,targetId, level, index) 
	
	return 0
	
end


--********************************************************************
--����
--********************************************************************
function x310070_ProcQuestAbandon( sceneId, selfId,MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
		return
	end
	DelQuest( sceneId, selfId, MissionId)
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


function x310070_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
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
function x310070_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	local bHaveMission = IsHaveQuestNM(sceneId, selfId,MissionId );
		if bHaveMission > 0 then
		
		local index = GetQuestData(sceneId, selfId, MD_YUNYOU_RAND[1], MD_YUNYOU_RAND[2], MD_YUNYOU_RAND[3])	
			BeginQuestEvent(sceneId)			
		    AddQuestLogCustomText( sceneId,
									"",							-- ����
									x310070_g_MissionName,      -- ��������
									x310070_g_MissionTarget,	--����Ŀ��
									x310070_g_NPCName,			--����NPC
									"",      --������
									format(x310070_g_MissionInfo, x310070_TargetNPCList[index], x310070_TargetList[index]),		--��������
									x310070_g_MissionHelp							--����С��ʾ
									)
      AddQuestExpBonus(sceneId, GetLevel(sceneId, selfId)*1680)
      --AddQuestItemBonus(sceneId, 12110204, 1)
	  AddQuestMoneyBonus2(sceneId, GetLevel(sceneId, selfId)*100 )
			EndQuestEvent(sceneId)
			DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		end
end
