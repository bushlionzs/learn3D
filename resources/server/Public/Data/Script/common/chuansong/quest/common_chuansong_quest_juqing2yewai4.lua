--�ֻ�֮�ػسǽű�

x550544_g_ScriptId = 550544
x550544_g_ask ={"�뿪�˵�","ȷ��"}
x550544_g_answer ={"\t����ǵ���ɼ�˼���ڴ˵�ʱ�ľ���\n\t��Ҫ�뿪������"}

function x550544_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x550544_g_ScriptId, x550544_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x550544_g_answer[1])
			AddQuestNumText(sceneId, x550544_g_ScriptId, x550544_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            NewWorld( sceneId, selfId, selfcountry * 100 + 102, 220 + random( 0, 5), 170 + random( 0, 5), 550544)
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x550544_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x550544_g_ScriptId, x550544_g_ask[1],0,1)
end








