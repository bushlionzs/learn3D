
x300620_g_ScriptId =  300620
--���ɼ�����

x300620_g_Leader_Index   = 5

function x300620_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local pos = GetGuildOfficial(sceneId, selfId)
	if pos == x300620_g_Leader_Index then			--�ǰ���  
		if QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) > 0 then	-- ������Խ��������
            GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_GATHER_ISSUE_TIME, x300620_g_ScriptId,MissionId,"OnCallBackEnumerate",targetId)
			return 0
		end
	end

	return 0
end


function x300620_OnCallBackEnumerate( sceneId, selfId,MissionData,MissionId,targetId )


	local CurDaytime = GetDayTime()
	if MissionData ~= CurDaytime then					--�ϴη�����ʱ�䲻�ǽ���
	    --local state = GetQuestStateNM(sceneId,selfId,targetId,MissionId)
		AddQuestTextNM( sceneId, selfId, targetId, MissionId, 3, -1 ) 		-- ��ʾ������Ϣ
		DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
	end
	
	return 0
end

--ѡ������
function x300620_ProcEventEntry( sceneId, selfId, targetId, MissionId )

		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )

		if ret > 0 then	-- ������Խ��������
  			local pos = GetGuildOfficial(sceneId, selfId)
  		
  			if pos ~= x300620_g_Leader_Index then			--���ǰ���
  				return 0
 			end
            AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����������Ϣ		
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
function x300620_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	
 	local level = GetLevel(sceneId,selfId)
	if level < 50 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��50���Ժ���ܷ������ɼ�����");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "�ܱ�Ǹ��50���Ժ���ܷ������ɼ�����" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end
				
  	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_GATHER_ISSUE_TIME, x300620_g_ScriptId,MissionId,"OnReturn")
end

function x300620_OnReturn(sceneId, selfId,MissionData,MissionId,targetId)

	local CurDaytime = GetDayTime()
	if MissionData == CurDaytime then					--�ϴη�����ʱ���ǽ���
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�������ѷ��������ɼ�������������ɣ�")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "�������ѷ��������ɼ�������������ɣ�" 
		Msg2Player(sceneId,selfId,Readme,8,2)
	else
		local title =GetGuildTitle(sceneId, selfId)
		local str = format("%s�����˽���İ��ɼ�����,�Ժ���Ե���ս�����˴���ȡ����",title)
		Msg2Player(sceneId, selfId,str,6,0)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�������˽���İ��ɼ�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "�������˽���İ��ɼ�����,�Ժ���Ե���ս�����˴���ȡ����" 
		Msg2Player(sceneId,selfId,Readme,8,2)
 		local GuildID = GetGuildID(sceneId,selfId)
		SetGuildQuestData(sceneId, GuildID, GD_GUILD_INDEX_GATHER_ISSUE_TIME, CurDaytime)
	end
	
--DispatchQuestEventList(sceneId, selfId, -1)
	
end



