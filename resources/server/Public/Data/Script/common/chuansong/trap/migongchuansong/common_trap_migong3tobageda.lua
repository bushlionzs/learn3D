--�Թ�3�㵽��Ҷ��

x552004_g_ScriptId = 552004
x552004_g_ask ={"ǰ���ݵ�-��Ҷ��","ȷ��"}
x552004_g_answer ={"\t��ȷ��Ҫǰ���ݵ�-��Ҷ����"}

function x552004_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x552004_g_ScriptId, x552004_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x552004_g_answer[1])
			AddQuestNumText(sceneId, x552004_g_ScriptId, x552004_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
           --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            local BusId = GetBusId(sceneId, selfId)
				if BusId ~=-1 then
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                    ReadyBusChangeScene(sceneId, 9,BusId)
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, 9, 169 + random( 0, 5), 44 + random( 0, 5), 552004)
					DeleteBus(sceneId, BusId,0)	
				else
            		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                   NewWorld( sceneId, selfId, 9, 169 + random( 0, 5), 44 + random( 0, 5), 552004)
            	end
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x552004_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x552004_g_ScriptId, x552004_g_ask[1],0,1)
end
