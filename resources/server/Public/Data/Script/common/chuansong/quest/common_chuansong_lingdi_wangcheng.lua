--领地回城脚本

x300271_g_ScriptId = 300271
x300271_g_ask ={"回到王城南门","确定"}
x300271_g_answer ={"\t你要离开这里，返回王城南门吗？"}

function x300271_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
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

--列举事件

--**********************************

function x300271_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x300271_g_ScriptId, x300271_g_ask[1],0,1)
end








