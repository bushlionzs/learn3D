--莫斯科到迷宫6层
x552015_g_ScriptId = 552015
x552015_g_ask ={"前往迷宫六层","确定"}
x552015_g_answer ={"\t你确认要前往本国迷宫六层吗？"}

function x552015_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x552015_g_ScriptId, x552015_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x552015_g_answer[1])
			AddQuestNumText(sceneId, x552015_g_ScriptId, x552015_g_ask[2],0,2)
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
                    ReadyBusChangeScene(sceneId, 109,BusId)
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 109, 121 + random( 0, 5), 159 + random( 0, 5), 552015)
					DeleteBus(sceneId, BusId,0)	
				else
            		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 109, 121 + random( 0, 5), 159 + random( 0, 5), 552015)
            	end
			elseif selfcountry ==1 then
				if BusId ~=-1 then
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                    ReadyBusChangeScene(sceneId, 209,BusId)
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 109, 125 + random( 0, 5), 57 + random( 0, 5), 552015)
					DeleteBus(sceneId, BusId,0)	
				else
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 109, 125 + random( 0, 5), 57 + random( 0, 5), 552015)
				end
			elseif selfcountry ==2 then
				if BusId ~=-1 then
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                    ReadyBusChangeScene(sceneId, 309,BusId)
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 109, 61 + random( 0, 5), 78 + random( 0, 5), 552015)
					DeleteBus(sceneId, BusId,0)	
				else
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 109, 61 + random( 0, 5), 78 + random( 0, 5), 552015)
				end
			elseif selfcountry ==3 then
				if BusId ~=-1 then
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                    ReadyBusChangeScene(sceneId, 409,BusId)
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 109, 84 + random( 0, 5), 80 + random( 0, 5), 552015)
					DeleteBus(sceneId, BusId,0)	
				else
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 109, 84 + random( 0, 5), 80 + random( 0, 5), 552015)
				end
			end
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x552015_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x552015_g_ScriptId, x552015_g_ask[1],0,1)
end
