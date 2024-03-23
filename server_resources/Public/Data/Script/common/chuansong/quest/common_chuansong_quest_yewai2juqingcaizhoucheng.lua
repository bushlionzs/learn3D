--外到内蔡州城脚本

x550554_g_ScriptId = 550554
x550554_g_ask ={"前往昔日的蔡州城","确定"}
x550554_g_answer ={"穿越这记忆之门，可以前往昔日的蔡州城。"}

function x550554_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x550554_g_ScriptId, x550554_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x550554_g_answer[1])
			AddQuestNumText(sceneId, x550554_g_ScriptId, x550554_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            NewWorld( sceneId, selfId,504, 111 + random( 0, 2), 81 + random( 0, 2), 550554)
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x550554_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x550554_g_ScriptId, x550554_g_ask[1],0,1)
end








