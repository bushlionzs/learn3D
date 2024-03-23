--古道到迷宫2层
x552009_g_ScriptId = 552009
x552009_g_ask ={"前往迷宫二层","确定"}
x552009_g_answer ={"\t你确认要前往本国迷宫二层吗？"}

function x552009_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x552009_g_ScriptId, x552009_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x552009_g_answer[1])
			AddQuestNumText(sceneId, x552009_g_ScriptId, x552009_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
           --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            local BusId = GetBusId(sceneId, selfId)
			if selfcountry == 0 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 105,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 105, 141 + random( 0, 5), 154 + random( 0, 5), 552009)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 105, 141 + random( 0, 5), 154 + random( 0, 5), 552009)
            	end
			elseif selfcountry ==1 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 205,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 105, 121 + random( 0, 5), 158 + random( 0, 5), 552009)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 105, 121 + random( 0, 5), 158 + random( 0, 5), 552009)
				end
			elseif selfcountry ==2 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 305,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 105, 72 + random( 0, 5), 134 + random( 0, 5), 552009)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 105, 72 + random( 0, 5), 134 + random( 0, 5), 552009)
				end
			elseif selfcountry ==3 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 405,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 105, 119 + random( 0, 5), 121 + random( 0, 5), 552009)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 105, 119 + random( 0, 5), 121 + random( 0, 5), 552009)
				end
			end
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x552009_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x552009_g_ScriptId, x552009_g_ask[1],0,1)
end
