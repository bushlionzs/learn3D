--��ػسǽű�

x300271_g_ScriptId = 300271
x300271_g_ask ={"�ص���������","ȷ��"}
x300271_g_answer ={"\t��Ҫ�뿪�����������������"}

function x300271_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x300271_g_ScriptId, x300271_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x300271_g_answer[1])
			AddQuestNumText(sceneId, x300271_g_ScriptId, x300271_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            NewWorld( sceneId, selfId, selfcountry * 100 + 50, 128 + random( 0, 5), 165 + random( 0, 5), 300271)
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x300271_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x300271_g_ScriptId, x300271_g_ask[1],0,1)
end








