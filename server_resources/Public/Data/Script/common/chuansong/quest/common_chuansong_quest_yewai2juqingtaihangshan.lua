--�⵽��̫��ɽ�ű�

x550552_g_ScriptId = 550552
x550552_g_ask ={"ǰ�����յ�̫��ɽ","ȷ��"}
x550552_g_answer ={"��Խ�����֮�ţ�����ǰ�����յ�̫��ɽ��"}

function x550552_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x550552_g_ScriptId, x550552_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x550552_g_answer[1])
			AddQuestNumText(sceneId, x550552_g_ScriptId, x550552_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            NewWorld( sceneId, selfId,502, 150 + random( 0, 2), 39 + random( 0, 2), 550552)
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x550552_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x550552_g_ScriptId, x550552_g_ask[1],0,1)
end








