--边塞到迷宫3层
x552010_g_ScriptId = 552010
x552010_g_ask ={"前往迷宫三层","确定"}
x552010_g_answer ={"\t你确认要前往本国迷宫三层吗？"}

function x552010_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x552010_g_ScriptId, x552010_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x552010_g_answer[1])
			AddQuestNumText(sceneId, x552010_g_ScriptId, x552010_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
           --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            local BusId = GetBusId(sceneId, selfId)
			if selfcountry == 0 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 106,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 106, 103 + random( 0, 5), 161 + random( 0, 5), 552010)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 106, 103 + random( 0, 5), 161 + random( 0, 5), 552010)
            	end
			elseif selfcountry ==1 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 206,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 106, 126 + random( 0, 5), 153 + random( 0, 5), 552010)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 106, 126 + random( 0, 5), 153 + random( 0, 5), 552010)
				end
			elseif selfcountry ==2 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 306,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 106, 77 + random( 0, 5), 122 + random( 0, 5), 552010)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 106, 77 + random( 0, 5), 122 + random( 0, 5), 552010)
				end
			elseif selfcountry ==3 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 406,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 106, 109 + random( 0, 5), 126 + random( 0, 5), 552010)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 106, 109 + random( 0, 5), 126 + random( 0, 5), 552010)
				end
			end
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x552010_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x552010_g_ScriptId, x552010_g_ask[1],0,1)
end
