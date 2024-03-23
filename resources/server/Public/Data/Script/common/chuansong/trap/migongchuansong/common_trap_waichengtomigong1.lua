--外城到迷宫1层
x552008_g_ScriptId = 552008
x552008_g_ask ={"前往迷宫一层","确定"}
x552008_g_answer ={"\t你确认要前往本国迷宫一层吗？"}

function x552008_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x552008_g_ScriptId, x552008_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x552008_g_answer[1])
			AddQuestNumText(sceneId, x552008_g_ScriptId, x552008_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
           --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            local BusId = GetBusId(sceneId, selfId)
			if selfcountry == 0 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 104,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 104, 115 + random( 0, 5), 162 + random( 0, 5), 552008)
					DeleteBus(sceneId, BusId,0)	
				else
            		
                   NewWorld( sceneId, selfId, selfcountry * 100 + 104, 115 + random( 0, 5), 162 + random( 0, 5), 552008)
            	end
			elseif selfcountry ==1 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 204,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 104, 90 + random( 0, 5), 109 + random( 0, 5), 552008)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 104, 90 + random( 0, 5), 109 + random( 0, 5), 552008)
				end
			elseif selfcountry ==2 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 304,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 104, 126 + random( 0, 5), 121 + random( 0, 5), 552008)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 104, 126 + random( 0, 5), 121 + random( 0, 5), 552008)
				end
			elseif selfcountry ==3 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 404,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 104, 157 + random( 0, 5), 121 + random( 0, 5), 552008)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 104, 157 + random( 0, 5), 121 + random( 0, 5), 552008)
				end
			end
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x552008_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x552008_g_ScriptId, x552008_g_ask[1],0,1)
end
