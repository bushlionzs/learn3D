--轮回之地回城脚本

x256011_g_ScriptId = 256011
x256011_g_ask ={"回到王国","确定"}
x256011_g_answer ={"\t生死有命，灾祸常生，所以，你也不必太过沮丧。\n\t你要离开这里，返回王国吗？"}

function x256011_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x256011_g_ScriptId, x256011_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x256011_g_answer[1])
			AddQuestNumText(sceneId, x256011_g_ScriptId, x256011_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            if selfcountry == 0 then
            	NewWorld( sceneId, selfId, 50, 126 + random( 0, 5), 119 + random( 0, 5), 256011)
            elseif selfcountry == 1 then
            	NewWorld( sceneId, selfId, 150, 126 + random( 0, 5), 119 + random( 0, 5), 256011)
            elseif selfcountry == 2 then
            	NewWorld( sceneId, selfId, 250, 126 + random( 0, 5), 138 + random( 0, 5), 256011)
           	elseif selfcountry == 3 then
            	NewWorld( sceneId, selfId, 350, 126 + random( 0, 5), 119 + random( 0, 5), 256011)
            end
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x256011_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x256011_g_ScriptId, x256011_g_ask[1],0,1)
end








