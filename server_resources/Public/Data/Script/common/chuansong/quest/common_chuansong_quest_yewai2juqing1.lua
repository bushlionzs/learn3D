--�⵽�����ղ��ű�

x550547_g_ScriptId = 550547
x550547_g_ask ={"ǰ�����յ����ղ�","ȷ��"}
x550547_g_answer ={"\t��Խ�����֮�ţ�����ǰ�����յ����ղ���"}

function x550547_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x550547_g_ScriptId, x550547_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x550547_g_answer[1])
			AddQuestNumText(sceneId, x550547_g_ScriptId, x550547_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            NewWorld( sceneId, selfId, selfcountry * 100 + 53, 90 + random( 0, 5), 186 + random( 0, 5), 550547)
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x550547_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x550547_g_ScriptId, x550547_g_ask[1],0,1)
end








