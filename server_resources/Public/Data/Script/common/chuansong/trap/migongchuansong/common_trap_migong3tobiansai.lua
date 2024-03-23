--迷宫3层到边塞

x552002_g_ScriptId = 552002
x552002_g_ask ={"前往边塞","确定"}
x552002_g_answer ={"\t你确认要前往王国边塞吗？"}

function x552002_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x552002_g_ScriptId, x552002_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x552002_g_answer[1])
			AddQuestNumText(sceneId, x552002_g_ScriptId, x552002_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
           --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            local BusId = GetBusId(sceneId, selfId)
			if selfcountry == 0 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 51,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 51, 52 + random( 0, 5), 100 + random( 0, 5), 552002)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 51, 52 + random( 0, 5), 100 + random( 0, 5), 552002)
            	end
			elseif selfcountry ==1 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 151,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 51, 201 + random( 0, 5), 95 + random( 0, 5), 552002)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 51, 201 + random( 0, 5), 95 + random( 0, 5), 552002)
				end
			elseif selfcountry ==2 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 251,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 51, 43 + random( 0, 5), 146 + random( 0, 5), 552002)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 51, 43 + random( 0, 5), 146 + random( 0, 5), 552002)
				end
			elseif selfcountry ==3 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 351,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 51, 217 + random( 0, 5), 149 + random( 0, 5), 552002)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 51, 217 + random( 0, 5), 149 + random( 0, 5), 552002)
				end
			end
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x552002_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x552002_g_ScriptId, x552002_g_ask[1],0,1)
end
