--匈牙利到迷宫7层
x552017_g_ScriptId = 552017
x552017_g_ask ={"前往迷宫七层","确定"}
x552017_g_answer ={"\t你确认要前往本国迷宫七层吗？"}

function x552017_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x552017_g_ScriptId, x552017_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x552017_g_answer[1])
			AddQuestNumText(sceneId, x552017_g_ScriptId, x552017_g_ask[2],0,2)
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
                    ReadyBusChangeScene(sceneId, 110,BusId)
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 110, 199.4 + random( 0, 5), 167.4 + random( 0, 5), 552017)
					DeleteBus(sceneId, BusId,0)	
				else
            		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 110, 199.4 + random( 0, 5), 167.4 + random( 0, 5), 552017)
            	end
			elseif selfcountry ==1 then
				if BusId ~=-1 then
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                    ReadyBusChangeScene(sceneId, 210,BusId)
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 110, 83 + random( 0, 5), 66 + random( 0, 5), 552017)
					DeleteBus(sceneId, BusId,0)	
				else
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 110, 83 + random( 0, 5), 66 + random( 0, 5), 552017)
				end
			elseif selfcountry ==2 then
				if BusId ~=-1 then
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                    ReadyBusChangeScene(sceneId, 310,BusId)
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 110, 196.3 + random( 0, 5), 180 + random( 0, 5), 552017)
					DeleteBus(sceneId, BusId,0)	
				else
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 110, 196.3 + random( 0, 5), 180 + random( 0, 5), 552017)
				end
			elseif selfcountry ==3 then
				if BusId ~=-1 then
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                    ReadyBusChangeScene(sceneId, 410,BusId)
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 110, 60 + random( 0, 5), 125 + random( 0, 5), 552017)
					DeleteBus(sceneId, BusId,0)	
				else
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, selfcountry * 100 + 110, 60 + random( 0, 5), 125 + random( 0, 5), 552017)
				end
			end
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x552017_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x552017_g_ScriptId, x552017_g_ask[1],0,1)
end
