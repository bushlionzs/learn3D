--�ֻ�֮�ػسǽű�

x550541_g_ScriptId = 550541
x550541_g_ask ={"�뿪�˵�","ȷ��"}
x550541_g_answer ={"\t����ǵ���ɼ�˼���ڴ˵�ʱ�ľ���\n\t��Ҫ�뿪������"}

function x550541_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x550541_g_ScriptId, x550541_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x550541_g_answer[1])
			AddQuestNumText(sceneId, x550541_g_ScriptId, x550541_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            NewWorld( sceneId, selfId, selfcountry * 100 + 99, 25 + random( 0, 5), 150 + random( 0, 5), 550541)
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x550541_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x550541_g_ScriptId, x550541_g_ask[1],0,1)
end








