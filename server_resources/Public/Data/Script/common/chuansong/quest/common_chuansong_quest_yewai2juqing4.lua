--�⵽���������ű�

x550550_g_ScriptId = 550550
x550550_g_ask ={"ǰ�����յ�������","ȷ��"}
x550550_g_answer ={"��Խ�����֮�ţ�����ǰ�����յ���������"}

function x550550_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x550550_g_ScriptId, x550550_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x550550_g_answer[1])
			AddQuestNumText(sceneId, x550550_g_ScriptId, x550550_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            NewWorld( sceneId, selfId, selfcountry * 100 + 56, 39 + random( 0, 5), 125 + random( 0, 5), 550550)
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x550550_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x550550_g_ScriptId, x550550_g_ask[1],0,1)
end








