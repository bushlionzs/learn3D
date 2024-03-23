--外到内克烈部脚本

x550549_g_ScriptId = 550549
x550549_g_ask ={"前往昔日的克烈部","确定"}
x550549_g_answer ={"穿越这记忆之门，可以前往昔日的克烈部。"}

function x550549_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x550549_g_ScriptId, x550549_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x550549_g_answer[1])
			AddQuestNumText(sceneId, x550549_g_ScriptId, x550549_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            NewWorld( sceneId, selfId, selfcountry * 100 + 54, 176 + random( 0, 5), 117 + random( 0, 5), 550549)
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x550549_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x550549_g_ScriptId, x550549_g_ask[1],0,1)
end








