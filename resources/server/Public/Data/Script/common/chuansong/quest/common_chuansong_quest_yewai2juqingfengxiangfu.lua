--�⵽�ڷ��踮�ű�

x550553_g_ScriptId = 550553
x550553_g_ask ={"ǰ�����յķ��踮","ȷ��"}
x550553_g_answer ={"��Խ�����֮�ţ�����ǰ�����յķ��踮��"}

function x550553_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x550553_g_ScriptId, x550553_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x550553_g_answer[1])
			AddQuestNumText(sceneId, x550553_g_ScriptId, x550553_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            NewWorld( sceneId, selfId,503, 105 + random( 0, 2), 66 + random( 0, 2), 550553)
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x550553_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x550553_g_ScriptId, x550553_g_ask[1],0,1)
end








