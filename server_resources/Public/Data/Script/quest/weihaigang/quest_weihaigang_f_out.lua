--副本回城脚本(威海港)

x270200_g_ScriptId = 270200
x270200_g_ask ={"回到威海港","确定"}
x270200_g_answer ={"\t你确认要离开此副本，返回威海港吗？"}

function x270200_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x270200_g_ScriptId, x270200_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x270200_g_answer[1])
			AddQuestNumText(sceneId, x270200_g_ScriptId, x270200_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			--local selfcountry =GetCurCountry( sceneId, selfId)
			--if selfcountry ==0 then
					TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
					TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
					NewWorld(sceneId,selfId,15,151,106, 270200)
			--elseif selfcountry ==1 then
			--		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
			--		NewWorld(sceneId,selfId,150,254,117, 270200)
			--elseif selfcountry ==2 then
			--		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
			--		NewWorld(sceneId,selfId,250,254,117, 270200)
			--elseif selfcountry ==3 then
			--		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
			--		NewWorld(sceneId,selfId,350,254,117, 270200)
			--end
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x270200_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x270200_g_ScriptId, x270200_g_ask[1],0,1)
end








