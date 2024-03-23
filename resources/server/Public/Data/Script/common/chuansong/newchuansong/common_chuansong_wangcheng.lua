--迷宫回城脚本

x550000_g_ScriptId = 550000
x550000_g_ask ={"回到王城","确定"}
x550000_g_answer ={"\t你确认要离开剧场返回王城吗？"}

function x550000_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x550000_g_ScriptId, x550000_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x550000_g_answer[1])
			AddQuestNumText(sceneId, x550000_g_ScriptId, x550000_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
			if selfcountry == 0 then
            NewWorld( sceneId, selfId, selfcountry * 100 + 50, 128 + random( 0, 5), 38 + random( 0, 5), 550000)
			elseif selfcountry ==1 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 128 + random( 0, 5), 31 + random( 0, 5), 550000)
			elseif selfcountry ==2 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 127 + random( 0, 5), 210 + random( 0, 5), 550000)
			elseif selfcountry ==3 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 127 + random( 0, 5), 223 + random( 0, 5), 550000)
			end
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x550000_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x550000_g_ScriptId, x550000_g_ask[1],0,1)
end
