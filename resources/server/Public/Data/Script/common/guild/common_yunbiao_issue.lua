--����ڳ����񷢲�
--MisDescBegin
x300607_g_ScriptId =  300607
x300607_g_MissionName = "����᡿�ټ�"
--MisDescEnd


x300607_g_Leader_Index = 5


function x300607_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
 	  	local pos = GetGuildOfficial(sceneId, selfId)
      	if pos == x300607_g_Leader_Index then			--�ǰ���
  			if QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) > 0 then	-- ���û���������	-- ������Խ��������
  				--GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_YUNBIAO_SSUE_TIME, x300607_g_ScriptId,MissionId,"OnCallBackEnumerate",targetId)
				AddQuestTextNM( sceneId, selfId, targetId, MissionId, 3, -1 )	 -- ��ʾ������Ϣ
				return 1
			end
		end
end

--function x300607_OnCallBackEnumerate( sceneId, selfId,MissionData,MissionId,targetId )
--
--	local CurDaytime = GetDayTime()
--	if MissionData ~= CurDaytime then					--�ϴη�����ʱ�䲻�ǽ���
--	    --local state = GetQuestStateNM(sceneId,selfId,targetId,MissionId)
--		AddQuestTextNM( sceneId, selfId, targetId, MissionId, 3, -1 ) 		-- ��ʾ������Ϣ
--		DispatchQuestEventList(sceneId,selfId,targetId)
--		return 0
--	end
--
--	return 0
--end

--ѡ������
function x300607_ProcEventEntry( sceneId, selfId, targetId, MissionId )
                                   
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
		if ret > 0 then	-- ������Խ��������
  			local pos = GetGuildOfficial(sceneId, selfId)
  			if pos ~= x300607_g_Leader_Index then			--���ǰ���
  				return 0
 			end         
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y����᡿����ټ�")
			AddQuestText(sceneId,"\t������ͨ���ң���ȫ�����Ա�����ټ���Ϣ�����Է�ͬ����������������ߣ����Է���������״̬��ͬ���򲻻������������ߡ�\n\t�˹���ÿ��ֻ��ʹ��һ�Ρ�")
			AddQuestText( sceneId, "")
			EndQuestEvent()
			DispatchQuestInfo(sceneId, selfId, targetId, MissionId, -1)
		else
			local strText = "δ֪�����޷����µ�����"
			if ret == -1 then
				strText = "�ȼ����㣬�޷����µ�����"
			elseif ret == -2 then
				strText = "�ȼ����ߣ��޷����µ�����"
			elseif ret == -3 then
				strText = "��Ǯ���㣬�޷����µ�����"
			elseif ret == -4 then
				strText = "�����Ǳ�����ң��޷����µ�����"
			elseif ret == -5 then
				strText = "ְҵ���Ͳ������޷����µ�����"
			elseif ret == -6 then
				strText = "��Ӫ�������޷����µ�����"
			end
			BeginQuestEvent(sceneId)
			--AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
		
end

--**********************************
--����
--**********************************
function x300607_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
  			GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_YUNBIAO_SSUE_TIME, x300607_g_ScriptId,MissionId,"OnReturn")
end


function x300607_OnReturn(sceneId, selfId,MissionData,MissionId,targetId)
	local CurDaytime = GetDayTime()
	if MissionData == CurDaytime then					--�ϴη�����ʱ���ǽ���
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ������᡿����ټ�ÿ��ֻ�ܽ���һ�Σ�")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "�ܱ�Ǹ������᡿����ټ�ÿ��ֻ�ܽ���һ�Σ�"
		Msg2Player(sceneId,selfId,Readme,8,2)
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "����᡿����ټ������ɹ��������ֵ��ǻᾡ�������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "����᡿����ټ������ɹ��������ֵ��ǻᾡ�������"
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		--������д��־
		GamePlayScriptLog(sceneId,selfId,871)

 		local GuildID = GetGuildID(sceneId,selfId)
		SetGuildQuestData(sceneId, GuildID, GD_GUILD_INDEX_YUNBIAO_SSUE_TIME, CurDaytime)
		RecruitGuildConvoy(sceneId, selfId)
	end	
	
	--DispatchQuestEventList(sceneId, selfId, -1)
end



