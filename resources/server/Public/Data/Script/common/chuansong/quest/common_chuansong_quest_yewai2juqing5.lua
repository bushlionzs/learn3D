--�⵽�ھ�ӹ�ؽű�

x550551_g_ScriptId = 550551
x550551_g_ask ={"ǰ�����յľ�ӹ��","ȷ��"}
x550551_g_answer ={"��Խ�����֮�ţ�����ǰ�����յľ�ӹ�ء�"}

function x550551_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x550551_g_ScriptId, x550551_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x550551_g_answer[1])
			AddQuestNumText(sceneId, x550551_g_ScriptId, x550551_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            NewWorld( sceneId, selfId, selfcountry * 100 + 57, 71 + random( 0, 5), 62 + random( 0, 5), 550551)
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x550551_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x550551_g_ScriptId, x550551_g_ask[1],0,1)
end








