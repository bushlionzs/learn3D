--�Թ�3�㵽��

x552006_g_ScriptId = 552006
x552006_g_ask ={"ǰ����","ȷ��"}
x552006_g_answer ={"\t��ȷ��Ҫǰ������"}
x552006_g_Notice = "���ĵȼ�������#R40��#Y���޷�����󶼣�"

function x552006_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		local Level = GetLevel(sceneId, selfId)
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x552006_g_ScriptId, x552006_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x552006_g_answer[1])
			AddQuestNumText(sceneId, x552006_g_ScriptId, x552006_g_ask[2],0,2)
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
                  
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end					
						   if Level >= 40 then
						   ReadyBusChangeScene(sceneId, 0,BusId)
                   NewWorld( sceneId, selfId, 0, 68 + random( 0, 5), 66 + random( 0, 5), 552006)
					         DeleteBus(sceneId, BusId,0)	
					    elseif Level < 40 then
					   		   Msg2Player(sceneId,selfId,"#Y"..x552006_g_Notice.."#W",4,3)
					   	end
				else
            		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
				       	if Level >= 40 then
                   NewWorld( sceneId, selfId, 0, 68 + random( 0, 5), 66 + random( 0, 5), 552006)
                elseif Level < 40 then
					   		   Msg2Player(sceneId,selfId,"#Y"..x552006_g_Notice.."#W",4,3)
					   	  end
            	end
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x552006_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x552006_g_ScriptId, x552006_g_ask[1],0,1)
end
