--撒马尔罕到迷宫5层
x552013_g_ScriptId = 552013
x552013_g_ask ={"前往迷宫五层","确定"}
x552013_g_answer ={"\t你确认要前往本国迷宫五层吗？"}

function x552013_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x552013_g_ScriptId, x552013_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x552013_g_answer[1])
			AddQuestNumText(sceneId, x552013_g_ScriptId, x552013_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
           --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            local BusId = GetBusId(sceneId, selfId)
			if selfcountry == 0 then
				if BusId ~=-1 then
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                    ReadyBusChangeScene(sceneId, 108,BusId)
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 108, 70 + random( 0, 5), 72 + random( 0, 5), 552013)
					DeleteBus(sceneId, BusId,0)	
				else
            		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 108, 70 + random( 0, 5), 72 + random( 0, 5), 552013)
            	end
			elseif selfcountry ==1 then
				if BusId ~=-1 then
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                    ReadyBusChangeScene(sceneId, 208,BusId)
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 108, 141 + random( 0, 5), 77 + random( 0, 5), 552013)
					DeleteBus(sceneId, BusId,0)	
				else
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 108, 141 + random( 0, 5), 77 + random( 0, 5), 552013)
				end
			elseif selfcountry ==2 then
				if BusId ~=-1 then
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                    ReadyBusChangeScene(sceneId, 308,BusId)
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 108, 168 + random( 0, 5), 132 + random( 0, 5), 552013)
					DeleteBus(sceneId, BusId,0)	
				else
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 108, 168 + random( 0, 5), 132 + random( 0, 5), 552013)
				end
			elseif selfcountry ==3 then
				if BusId ~=-1 then
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                    ReadyBusChangeScene(sceneId, 408,BusId)
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 108, 106 + random( 0, 5), 165 + random( 0, 5), 552013)
					DeleteBus(sceneId, BusId,0)	
				else
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 108, 106 + random( 0, 5), 165 + random( 0, 5), 552013)
				end
			end
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x552013_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x552013_g_ScriptId, x552013_g_ask[1],0,1)
end
