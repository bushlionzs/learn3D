--迷宫1层到外城

x552000_g_ScriptId = 552000
x552000_g_ask ={"前往外城","确定"}
x552000_g_answer ={"\t你确认要前往王国外城吗？"}

function x552000_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x552000_g_ScriptId, x552000_g_ask[1],0,1)
		  	EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x552000_g_answer[1])
			AddQuestNumText(sceneId, x552000_g_ScriptId, x552000_g_ask[2],0,2)
		  	EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
           --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            local BusId = GetBusId(sceneId, selfId)
			if selfcountry == 0 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 58,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 58, 189 + random( 0, 5), 50 + random( 0, 5), 552000)
					DeleteBus(sceneId, BusId,0)	
				else
            		
					
                   NewWorld( sceneId, selfId, selfcountry * 100 + 58, 189 + random( 0, 5), 50 + random( 0, 5), 552000)
            	end
			elseif selfcountry ==1 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 158,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 58, 67 + random( 0, 5), 51 + random( 0, 5), 552000)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 58, 67 + random( 0, 5), 51 + random( 0, 5), 552000)
				end
			elseif selfcountry ==2 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 258,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 58, 190 + random( 0, 5), 205 + random( 0, 5), 552000)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 58, 190 + random( 0, 5), 205 + random( 0, 5), 552000)
				end
			elseif selfcountry ==3 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 358,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 58, 66 + random( 0, 5), 205 + random( 0, 5), 552000)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 58, 66 + random( 0, 5), 205 + random( 0, 5), 552000)
				end
			end
		end
end
			
		

	
	



--**********************************

--列举事件

--**********************************

function x552000_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x552000_g_ScriptId, x552000_g_ask[1],0,1)

end