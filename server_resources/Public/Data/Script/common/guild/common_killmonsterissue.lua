
x300618_g_ScriptId =  300618
--���ɱ������

x300618_g_Leader_Index   = 5


function x300618_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
		local pos = GetGuildOfficial(sceneId, selfId)
  		if pos == x300618_g_Leader_Index then			--�ǰ���
  			if QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) > 0 then	-- ������Խ��������
  				GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_KILL_ISSUE_TIME, x300618_g_ScriptId,MissionId,"OnCallBackEnumerate",targetId)

				return 1
			end
		end

	return 0
end

function x300618_OnCallBackEnumerate( sceneId, selfId,MissionData , MissionId,targetId )

	local CurDaytime = GetDayTime()
	if MissionData ~= CurDaytime then					--�ϴη�����ʱ�䲻�ǽ���
		AddQuestTextNM( sceneId, selfId, targetId, MissionId, 3, -1 ) 		-- ��ʾ������Ϣ
		DispatchQuestEventList(sceneId,selfId,targetId)
	end
	return 0
end

--ѡ������
function x300618_ProcEventEntry( sceneId, selfId, targetId, MissionId )
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )

		if ret > 0 then	-- ������Խ��������
		
  			local pos = GetGuildOfficial(sceneId, selfId)
  		
  			if pos ~= x300618_g_Leader_Index then			--���ǰ���
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
function x300618_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
 	local level = GetLevel(sceneId,selfId)
	if level < 70 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��70���Ժ���ܷ������ɱ������");
		EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			local Readme = "�ܱ�Ǹ��70���Ժ���ܷ������ɱ������"
			Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end
   GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_KILL_ISSUE_TIME, x300618_g_ScriptId,MissionId,"OnReturn")
end

function x300618_OnReturn(sceneId, selfId,MissionData,MissionId,targetId)

	local CurDaytime = GetDayTime()
	if MissionData == CurDaytime then					--�ϴη�����ʱ���ǽ���
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�������Ѿ����������ɱ�֣�����������ɣ�")
		EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			local Readme = "�������Ѿ����������ɱ�֣�����������ɣ�"
			Msg2Player(sceneId,selfId,Readme,8,2)
	else
		local title =GetGuildTitle(sceneId, selfId)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�������˽���İ��ɱ������!")
		EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			local str = format("%s�����˽���İ��ɱ������,�Ժ���Ե���ս�����˴���ȡ����",title)
			Msg2Player(sceneId, selfId,str,6,0)

 		local GuildID = GetGuildID(sceneId,selfId)
		SetGuildQuestData(sceneId, GuildID, GD_GUILD_INDEX_KILL_ISSUE_TIME, CurDaytime)
	end
	
	--DispatchQuestEventList(sceneId, selfId, -1)
	
end



